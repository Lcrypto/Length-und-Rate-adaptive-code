function [liftedMatrix, baseMatrix, circSize] = readLiftedME(inputFileName)
in = fopen(inputFileName, 'r');
[n] = fscanf(in, '%d', [1]);
[m] = fscanf(in, '%d', [1]);
[circSize] = fscanf(in, '%d', [1]);
liftedMatrix = cell(m, n);
for  i = 1:m
    a = fgetl(in);
    tline = strsplit(a);
    while (length(tline) < n)
        a = fgetl(in);
        tline = strsplit(a);
    end
    curPos = 1;
    for j = 1:length(tline)
        if (length(tline{j}) > 0)
            liftedMatrix{i,curPos} = conv(tline{j});
            curPos = curPos + 1;
        end
    end
end
fclose(in);
for i =1:m
    for j= 1:n
        baseMatrix(i,j) = length(liftedMatrix{i,j}); 
    end
end
end

function res = conv(s)
res=[];
if (s(1) == '-')
    return;
end
res = str2num(strrep(s, '&', ' '));
end

