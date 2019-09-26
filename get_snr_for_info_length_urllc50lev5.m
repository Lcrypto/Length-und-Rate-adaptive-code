function [ebno, esno] =  get_snr_for_info_length_urllc50lev5(infoLength, curCodeRate)
persistent EsNo50;
persistent EsNo50len;
persistent EsNo50All;
persistent gEsNo50All;
if isempty(EsNo50)
    load('urllc50lev5.mat');
    EsNo50 = urllc1e5.esno;
    EsNo50len = urllc1e5.len;
    EsNo50All = zeros(EsNo50len(end), 1) + repmat(max(EsNo50), EsNo50len(end), 1);
    
    
    for rateId = 1:1
        for i=1:length(EsNo50len)-1
            for j=EsNo50len(i):EsNo50len(i + 1)
                EsNo50All(j, rateId) = (EsNo50(i, rateId) * (EsNo50len(i + 1) - j)...
                    + EsNo50(i + 1, rateId) * (j - EsNo50len(i))) / ...
                    (EsNo50len(i + 1) - EsNo50len(i));
            end
        end
    end
    rates = {'0p33', '0p25', '0p20', '0p17'};
    gEsNo50All = zeros(EsNo50len(end), 4) + 10;
    for rateId = 1:length(rates)
        fid = fopen(['it50r', rates{rateId}, 'w15_2.txt'], 'r');
        all_data0 = fscanf(fid,'%f');
        fclose(fid);
        all_data = reshape(all_data0, 2, length(all_data0)/2).';
        for i=1:length(all_data0) / 2
            gEsNo50All(all_data(i, 1), rateId) = all_data(i, 2);
        end
        for i=2:EsNo50len(end)
            gEsNo50All(i, rateId) = min(gEsNo50All(i, rateId), gEsNo50All(i - 1, rateId));
        end
    end
end

coderates = [1/3, 1/4, 1/5, 1/6];
coderate = find(coderates == curCodeRate);
%% 1 - 1/3; 2 - 1/4; 3 - 1/5, 4 - 1/6


myEsno = 10;
msuEsno = 10;
if (coderate == 1)
    if (infoLength > EsNo50len(end))
        msuEsno = EsNo50All(end, coderate);
    else
        msuEsno = EsNo50All(infoLength, coderate);
    end
end
if (infoLength > EsNo50len(end))
    myEsno = gEsNo50All(end, coderate);
else
    myEsno = gEsNo50All(infoLength, coderate);
end
esno = min(myEsno, msuEsno);
ebno = esno - 10*log10(2*coderates(coderate));
end