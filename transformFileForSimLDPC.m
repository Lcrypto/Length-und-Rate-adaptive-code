function [] = transformFileForSimLDPC(filename, curRateLiftedMatrix, shortNodes)
[~, ~, circSize, liftedMatrixCell] = readInnerCode(filename);
for x = shortNodes
    liftedMatrixCell = [liftedMatrixCell(:, 1:x-1) curRateLiftedMatrix(:, x), liftedMatrixCell(:, x:end)];
end
varNodes = size(liftedMatrixCell, 2);
checkNodes = size(liftedMatrixCell, 1);
seedLocal = randi(100000);
protoFileName = 'MyMatrices\nested';
outputFileName = strcat(protoFileName, int2str(varNodes),'x',int2str(checkNodes),  'SEED',int2str(seedLocal) ,'.txt');
if ~isempty(filename)
    outputFileName = filename;
end
liftedMatrixFileName = fopen(outputFileName, 'w');
fprintf(liftedMatrixFileName, '%d\t%d\t%d \n', varNodes, checkNodes,  circSize);
for i=1:checkNodes
    for j=1:varNodes
        if (isempty(liftedMatrixCell{i,j}))
            fprintf(liftedMatrixFileName, '-1\t');
        else
            a = liftedMatrixCell{i,j};
            fprintf(liftedMatrixFileName, '%d', a(1));
            if length(a) > 1
                fprintf(liftedMatrixFileName, '&%d', a(2:end));
            end
            fprintf(liftedMatrixFileName, '\t');
        end
    end
    fprintf(liftedMatrixFileName, '\n');
end
fclose(liftedMatrixFileName);
end
