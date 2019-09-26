function [liftedMatrix, innerCodeProto, circSize, liftedMatrixCell] = readInnerCode(filename)
fid = fopen(filename, 'r');
[n] = fscanf(fid, '%d', 1);
[m] = fscanf(fid, '%d', 1);
[circSize] = fscanf(fid, '%d', 1);
liftedMatrix = zeros(m, n);
innerCodeProto = zeros(m, n);
for  i = 1:m
    a = fgetl(fid);
    tline = strsplit(a);
    while (length(tline) < n)
        a = fgetl(fid);
        tline = strsplit(a);
    end
    curPos = 1;
    for j = 1:length(tline)
        if (~isempty(tline{j}))
            liftedMatrix(i,curPos) = str2num(tline{j});
            curPos = curPos + 1;
        end
    end
end
nonStandardInnerCode = 1;
i = 1;
while i <= m
    a = [];
    while isempty(a)
        a = fgetl(fid);
    end
    if (~ischar(a))
        nonStandardInnerCode = 0;
        break;
    end
    
    tline = strsplit(a);
    if (length(tline) < n)
        continue;
    end
    curPos = 1;
    for j = 1:length(tline)
        if (~isempty(tline{j}))
            innerCodeProto(i,curPos) = str2num(tline{j});
            curPos = curPos + 1;
        end
    end
    i = i + 1;
end
fclose(fid);
if ~nonStandardInnerCode
    for i = 1:m
        x = 0;
        for j= 1:n
            if liftedMatrix(i,j) == -1
                continue
            end
            innerCodeProto(i,j) = x + 1;
            x = mod(x + 1, 3);
        end
    end
end
for i = 1:m    
    x = 0;
    for j = 1:n
        if liftedMatrix(i,j) == -1
            continue
        end
        liftedMatrix(i,j) = mod(liftedMatrix(i, j), circSize);
        x = mod(x + 1, 3);
    end
end
liftedMatrixCell = cell(m, n);
for i = 1:m    
    for j = 1:n
        if liftedMatrix(i,j) == -1
            continue
        end
        liftedMatrixCell{i,j} = liftedMatrix(i, j);
    end
end