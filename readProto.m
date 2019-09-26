function [liftedMatrix, bigProto, circSize, liftedMatrixCell] = readProto(filename)
fid = fopen(filename, 'r');
[n] = fscanf(fid, '%d', 1);
[m] = fscanf(fid, '%d', 1);
liftedMatrix = zeros(m, n);
bigProto = zeros(m, n);
circSize = 1;
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
            liftedMatrix(i,curPos) = str2num(tline{j}) - 1;
            bigProto(i,curPos) = str2num(tline{j});
            curPos = curPos + 1;
        end
    end
end
fclose(fid);
liftedMatrixCell = cell(m, n);
for i = 1:m    
    for j = 1:n
        if liftedMatrix(i,j) == -1
            continue
        end
        liftedMatrixCell{i,j} = liftedMatrix(i, j);
    end
end