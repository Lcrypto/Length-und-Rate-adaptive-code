%
%Copyright(c) 2014, Vorobyev Ilya und  Vasiliy Usatyuk 
%All rights reserved.
%Redistribution and use in source and binary forms, with or without
%modification, are permitted provided that the following conditions are met :
%*Redistributions of source code must retain the above copyright
%notice, this list of conditions and the following disclaimer.
%* Redistributions in binary form must reproduce the above copyright
%notice, this list of conditions and the following disclaimer in the
%documentation and / or other materials provided with the distribution.
%* Neither the name of the <organization> nor the
%names of its contributors may be used to endorse or promote products
%derived from this software without specific prior written permission.
%THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
%ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
%WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
%DISCLAIMED.IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
%DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
%(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
%LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
%ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
%(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
%SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
%
clear all
delete(gcp('nocreate'))
degreeOfParallel = 2; %set number of threads 
%parpool(degreeOfParallel); % uncoment this line and change 115 line to 114
% to run multitread
errBlocksInSim = 200; %number of block errors
NEXPinSim = 1e6;      
iterationsInModelling = 50; % iteration of decoder
discreteLifting = 1;
maxCirc = 2;
attemptsInLift = [20, 20, 20, 20];
liftPen = -1;
ferLevel = -5;
fastDecMode = 1;  % use floar point or fix-point decoder 
shiftToRec = zeros(1, 100);
multilabelingSeeds = 1:2:15; % initial seed for cyclic group a= multilabelingSeeds*2^n
% find start matrix
[~, bigProto, startCirc, liftedMatrix] = readProto('check.txt');

layered = 0; % use layer message scheduller 
[rows, cols] = size(bigProto);
codeRates = [1/3]; % rate
rowsCollection = [16];      %number of check nodes in protograph
punByRates = [2, 2, 2, 2];           %number of punctured circulants per each rate
shortByRates = [0, 0, 0, 0];         %number of shortened circulant per each rate

scales = {[1    1	0.95	0.85	0.8	0.75], [1	1	0.95	0.85	0.8	0.75], ...
    [1	1	0.95	0.85	0.8	0.75], [1	1	0.95	0.85	0.8	0.75]};
offsets = {0.25, 0.25, 0.25, 0.25}; % scale values in decoder for variable node
                                    %to broke trapping sets and improve
                                    %decoder perfomance

columnsCollection = cols + (rowsCollection - rows);
%Lifting
folderNameLabel = 'Labeling';
folderForMatrices = ['matrices_from_', mfilename];
mkdir(folderForMatrices);
folderNameToSaveCurrentProgress = sprintf('%dx%d',rows, cols);
if ~exist(folderNameToSaveCurrentProgress, 'dir')
    mkdir(sprintf('%dx%d',rows, cols));
end
%veriffied rate
for i = 1:length(codeRates)
    assert(codeRates(i) == (columnsCollection(i) - rowsCollection(i) - shortByRates(i)) /...
        (columnsCollection(i) - punByRates(i) - shortByRates(i)), 'CodeRate mismatch');
end
%
maxInfoLength = 16; % max information length

%circSizesForCheck = 2.^(0:100); %[0:maxLog2CircSize]
%circSizesForCheck = circSizesForCheck(circSizesForCheck > startCirc & ...
%    circSizesForCheck <= circSize);

%upGirth = [8, 8, 8, 8, 8, 8, 8, 8, 8]; % check girth 
upGirth = [4, 4, 4, 4, 4, 4, 4, 4, 4];
%infoLengthForCheck = [1, 2, 4, 8, 16, 32, 64, 128] ...
%    * (cols -  rows - shortByRates(1));
%[1, 2, 4, 8, 16, 32, 48, 64, 80, 96, 112, 128, 160, 192, 224, 256]

%%Parameters In Procedurd
difLiftForGivenProto = degreeOfParallel * 2;

% auxiliari

protosForSimulations = cell(1, 1);

V2CmsgBitWidth = 8; %bit wise for quantize fast decoder for message from Variable to Check nodes
C2VmsgBitWidth = 6; %bit wise for quantize fast decoder check nodes to Variable nodes
llrScale = 3.7;     %scale to translate float value to fix point values
decoder_type = 7;%3 - minSum, 5 - adjusted, 7- BP ; type of decoder
debug = 1;       %verbose


for multilabelingSeed = multilabelingSeeds
    indexRateDone = 0;
    curRateLiftedMatrix = {};
    circSizesForCheck = multilabelingSeed * 2.^[0:10];
    circSizesForCheck = circSizesForCheck((circSizesForCheck <= 384) & (circSizesForCheck > 1));
    infoLengthForCheck = circSizesForCheck * (cols - rows - shortByRates(1));
    %%
    while indexRateDone < length(codeRates)
        
        proto = bigProto(end - rowsCollection(indexRateDone + 1) + 1:end, end - columnsCollection(indexRateDone + 1) + 1:end);
        prevRateLiftedMatrix = curRateLiftedMatrix;
        curRateLiftedMatrix = liftedMatrix(end - rowsCollection(indexRateDone + 1) + 1:end, end - columnsCollection(indexRateDone + 1) + 1:end);
        [rows, cols] = size(proto);
        infoNodes = setdiff(1:cols, 1:rows);
        parityNodes = 1:rows;
        shortNodes = infoNodes(1:shortByRates(indexRateDone + 1));
        notShortInfoNodes = setdiff(infoNodes, shortNodes);
        punctNodes = notShortInfoNodes(max(end - punByRates(indexRateDone + 1) + 1, 1):end);
        punctNodes = [punctNodes, parityNodes(end - (punByRates(indexRateDone + 1) - length(punctNodes)) + 1:end)];
        
        
        
        
        rateId = indexRateDone + 1;
        
        fprintf('Simulation is starting \n');
        
        bestBlersForAllCircs = 1.23 * ones(1, length(circSizesForCheck));
        
        
        
        allCurLiftedMatrices = cell(rows, cols, difLiftForGivenProto);
        
        for circSizeId = 1:length(circSizesForCheck)
               
            curCircSize = circSizesForCheck(circSizeId);
            filename = printFileForLabelingLDPC(curRateLiftedMatrix, prevRateLiftedMatrix, shortNodes);
            seedArray = randi(1e5, 1, difLiftForGivenProto);
            
            localBlers = cell(1, difLiftForGivenProto);
            tic;
            %parfor liftingId=1:difLiftForGivenProto % if you have multitread uncomment
            for liftingId=1:difLiftForGivenProto
                command = sprintf('.\\%s\\simpleModLabelingWithFixedAndCycleCost.exe --file %s --startCirc %d --endCirc %d --fixedValues 1 --seed %d --numberOfAttemptsForOneStep %d --numberOfAttemptsForFirstMatrix %d --givenFirstMatrix %d --DISCRETE_LIFTING %d --maxCirc %d --upGirth %d --LIFT_PEN %f 2>nul',...
                 folderNameLabel,filename, max(multilabelingSeed, curCircSize / 2), curCircSize , seedArray(liftingId), attemptsInLift(rateId), attemptsInLift(rateId), curCircSize ~= multilabelingSeed, discreteLifting, maxCirc, upGirth(circSizeId), liftPen);
                %here you can use different type of lifting with EMD, ACE,
                %MacKay-Smarandache-Vontobel upper bound
                %tic
                system(command);
                %toc
                
                inputFileName = sprintf('out_seed%d.txt', seedArray(liftingId));
                movefile(inputFileName, [folderForMatrices, '\\', inputFileName]);
                inputFileName = [folderForMatrices, '\\', inputFileName];
                transformFileForSimLDPC(inputFileName, curRateLiftedMatrix, shortNodes);
                
                maxBler(liftingId) = 0;
                curLiftedMatrix = {};
                protoInfoLen = (columnsCollection(indexRateDone + 1) - rowsCollection(indexRateDone + 1) - shortByRates(indexRateDone + 1));
                lengthsToCheck = infoLengthForCheck((infoLengthForCheck > (curCircSize / 2 * protoInfoLen)) & (infoLengthForCheck <= (curCircSize * protoInfoLen)));
                curBlers = ones(1, length(lengthsToCheck));
                for lengthId=1:length(lengthsToCheck)
                    configFilename = make_config(punctNodes, shortNodes, scales{indexRateDone + 1}, offsets{indexRateDone + 1}, ...
                        V2CmsgBitWidth, C2VmsgBitWidth, llrScale, debug, decoder_type, iterationsInModelling, errBlocksInSim, inputFileName, fastDecMode);
                    
                    iterationHash = liftingId * length(punctNodes) + lengthId;
                    curSeed = iterationHash * 333 + 213;
                    curSetInfoLength = lengthsToCheck(lengthId);
                    curSetCodeLength =  round(curSetInfoLength / codeRates(rateId));
                    
                    if (ferLevel == -5) && (iterationsInModelling == 50)
                        [curEbNo, curEsNo] = get_snr_for_info_length_urllc50lev5(curSetInfoLength, codeRates(rateId));
                        %tables for default SNR values 
                    else
                        error('where I should take snr from?');
                    end
                    
                    fileWithRes = [inputFileName, '_results'];
                    command = sprintf('ldpc_platform.exe %s --length %d --filename_mother_matrix %s --discreteLifting %d --blockErrorLimit %d --EsNos %f --liftingOffset 0 --user_attempt 1 --atempt_count 1 --file_result %s --NEXP %d 1>nul 2>nul',...
                        configFilename, curSetInfoLength, inputFileName, discreteLifting, errBlocksInSim, curEsNo - shiftToRec(circSizeId), fileWithRes, NEXPinSim);
                    
                    %tic
                    system(command);
                    %toc
                    fid = fopen(fileWithRes, 'r');
                    all_data = fscanf(fid,'%f');
                    bler = all_data(end);
                    fclose(fid);
                    [curLiftedMatrix, ~, ~] = readLiftedME(inputFileName);
                    maxBler(liftingId) = max(maxBler(liftingId), bler);
                    curBlers(lengthId) = bler;
                end
                localBlers{liftingId} = curBlers;
                allCurLiftedMatrices(:,:,liftingId) = curLiftedMatrix;
            end
            toc;
            delete(sprintf(['%s/lifting', num2str(cols), 'x', num2str(rows), '*.txt'],folderNameLabel));
            delete(sprintf('%s/out_seed*',folderForMatrices));
            [minMaxBler, bestLiftingId] = min(maxBler);
            localBlerForCurrentProto(circSizeId) = minMaxBler;
            curRateLiftedMatrix = allCurLiftedMatrices(:,:,bestLiftingId);
            fprintf('CircSize = %4d\t', curCircSize);
            fprintf('minMaxBler = %5.7f\t', minMaxBler);
            fprintf('Blers = %5.7f\n', localBlers{bestLiftingId});
        end
        res = comparator(bestBlersForAllCircs(1:end), localBlerForCurrentProto(1:end));
        if (res == 2)
            
            bestBlersForAllCircs = localBlerForCurrentProto;
        end
        for u = 1:size(proto,1)
            for v = 1:size(proto,2)
                liftedMatrix{end - size(proto,1) + u, end - size(proto,2) + v} = curRateLiftedMatrix{u, v};
            end
        end
        save(sprintf('%s/protoAndBestLift%d.mat',folderNameToSaveCurrentProgress, indexRateDone+1),'proto','bestBlersForAllCircs');
        
        %%
       
            writeME_InnerCode(curRateLiftedMatrix, circSizesForCheck(end), ['proto48x20w15circ1a=', num2str(multilabelingSeed), '.txt']);
      
        
        indexRateDone = indexRateDone + 1;
    end
end
