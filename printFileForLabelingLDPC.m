function outputFileName = printFileForLabelingLDPC(givenLiftedMatrix, fixedLiftedMatrix, shortNodes, noEIRA)
if nargin <= 3
    noEIRA = 0;
end
[checkNodesProto, varNodesProto] = size(givenLiftedMatrix);

degs = zeros(1, varNodesProto);
for i=1:checkNodesProto
    for j=1:varNodesProto
        if (~isempty(givenLiftedMatrix{i, j}))
            degs(j) = degs(j) + 1;
        end
    end
end
[checkNodesLiftedMatrix, varNodesLiftedMatrix] = size(fixedLiftedMatrix);
seedLocal = randi(100000);
protoFileName = 'Labeling\lifting';
outputFileName = strcat(protoFileName, int2str(varNodesProto),'x',int2str(checkNodesProto),  'SEED',int2str(seedLocal) ,'.txt');
labeledMatrixFileName = fopen(outputFileName, 'w');
fprintf(labeledMatrixFileName, '%d\t%d \n', varNodesProto - length(shortNodes), checkNodesProto);
for i=1:checkNodesProto
    for j=1:varNodesProto
        if (sum(j == shortNodes) > 0)
            continue
        end
        if (i >= (checkNodesProto - checkNodesLiftedMatrix) + 1) && (j >= (varNodesProto - varNodesLiftedMatrix)+ 1)
            a = fixedLiftedMatrix{i   - (checkNodesProto - checkNodesLiftedMatrix),j  - (varNodesProto - varNodesLiftedMatrix)};
            if (isempty(a))
                fprintf(labeledMatrixFileName, '-1\t');
            else
                fprintf(labeledMatrixFileName, '%d', a(1));
                if length(a) > 1
                    fprintf(labeledMatrixFileName, '&%d', a(2:end));
                end
                fprintf(labeledMatrixFileName, '\t');
            end
        else
            a = givenLiftedMatrix{i,j};
            if (isempty(a))
                fprintf(labeledMatrixFileName, '-1\t');
            else
                fprintf(labeledMatrixFileName, '%d', a(1));
                if length(a) > 1
                    fprintf(labeledMatrixFileName, '&%d', a(2:end));
                end
                fprintf(labeledMatrixFileName, '\t');
            end
        end
    end
    fprintf(labeledMatrixFileName, '\n');
end
fprintf(labeledMatrixFileName, '\n');
if (checkNodesLiftedMatrix > 0)
    for i=1:checkNodesProto
        for j=1:varNodesProto
            if (sum(j == shortNodes) > 0)
                continue
            end
            if (i >= (checkNodesProto - checkNodesLiftedMatrix)+ 1) && (j >= (varNodesProto - varNodesLiftedMatrix)+ 1)
                a = fixedLiftedMatrix{i   - (checkNodesProto - checkNodesLiftedMatrix),...
                    j - (varNodesProto - varNodesLiftedMatrix)};
                if (isempty(a))
                    fprintf(labeledMatrixFileName, '0\t');
                else
                    fprintf(labeledMatrixFileName, '%d', 1);
                    if length(a) > 1
                        fprintf(labeledMatrixFileName, '&%d', ones(1,length(a) - 1));
                    end
                    fprintf(labeledMatrixFileName, '\t');
                end
            else
                a = givenLiftedMatrix{i,j};
                if ((~isempty(a)) && (j <= (checkNodesProto - checkNodesLiftedMatrix)))
                    fprintf(labeledMatrixFileName, '1\t');
                else
                    fprintf(labeledMatrixFileName, '0\t');
                end
            end
        end
        fprintf(labeledMatrixFileName, '\n');
    end
else
    raptor = find(degs > 1, 1) - 1;
    eira = checkNodesProto - raptor;
    for i=1:checkNodesProto
        for j=1:varNodesProto
            if (sum(j == shortNodes) > 0)
                continue
            end            
            a = givenLiftedMatrix{i,j};
            if ((~isempty(a)) && (j <= checkNodesProto))
                if ((((j == checkNodesProto) && (i ~= 1 + raptor) && (i < checkNodesProto) && (i > raptor))) || ...
                    ((i <= raptor) && (j ~= i)))
                    fprintf(labeledMatrixFileName, '0\t');
                else
                    fprintf(labeledMatrixFileName, '1\t');
                end
            else
                fprintf(labeledMatrixFileName, '0\t');
            end
        end
        fprintf(labeledMatrixFileName, '\n');
    end
end
fclose(labeledMatrixFileName);
end