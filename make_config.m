function [configFilename] = make_config(punctNodes, shortNodes, scales, offsets,V2CmsgBitWidth, C2VmsgBitWidth, llrScale, ...
                            debug, decoder_type, iterationsInModelling, errBlocksInSim, inputFileName, fastDecMode)
configFilename = [inputFileName, '_config'];


fid = fopen(configFilename, 'w');
fprintf(fid, 'lastPunchNodes = %d\n', length(punctNodes));
fprintf(fid, 'firstShortNodes = %d\n', length(shortNodes));
fprintf(fid, 'separateScaleForPuncNodes = 0\n');
fprintf(fid, 'liftingOffset = 0\n');
fprintf(fid, 'debug = %d\n', debug);
fprintf(fid, 'decType = %d\n', decoder_type);
fprintf(fid, 'iter_decoder = %d\n', iterationsInModelling);
fprintf(fid, 'blockErrorLimit = %d\n', errBlocksInSim);
fprintf(fid, 'scaleCollection = %s\n', join(scales,','));
fprintf(fid, 'offsetCollection = %s\n', join(offsets,','));
fprintf(fid, 'V2CmsgBitWidth = %d\n', V2CmsgBitWidth);
fprintf(fid, 'C2VmsgBitWidth = %d\n', C2VmsgBitWidth);
fprintf(fid, 'llrScale = %0.2f\n', llrScale);
fprintf(fid, 'fastDecMode = %d\n', fastDecMode);

fclose(fid);
end

function [res] = join(a, del)
if (length(a) > 0)
    res = num2str(a(1), 2);
end
for i=2:length(a)
    res = [res, del, num2str(a(i), 2)];
end
end