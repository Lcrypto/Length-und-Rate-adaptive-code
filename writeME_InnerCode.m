function outputFileName = writeME_InnerCode(liftedMatrix, circSize, filename, proto)
varNodes = size(liftedMatrix, 2);
checkNodes = size(liftedMatrix, 1);
if nargin < 4
    proto = zeros(checkNodes, varNodes);
    for i=1:checkNodes
        x = 0;
        for j=1:varNodes
            if isempty(liftedMatrix{i, j})
                continue
            end
            proto(i, j) = x + 1;
            x = mod(x + 1, 3);
        end
    end
end
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
        if (isempty(liftedMatrix{i,j}))
            fprintf(liftedMatrixFileName, '-1\t');
        else
            a = liftedMatrix{i,j};
            fprintf(liftedMatrixFileName, '%d', a(1));
            if length(a) > 1
                fprintf(liftedMatrixFileName, '&%d', a(2:end));
            end
            fprintf(liftedMatrixFileName, '\t');
        end
    end
    fprintf(liftedMatrixFileName, '\n');
end
for i=1:checkNodes
    for j=1:varNodes
        fprintf(liftedMatrixFileName, '%d\t', proto(i, j));
    end
    fprintf(liftedMatrixFileName, '\n');
end
fclose(liftedMatrixFileName);
end

