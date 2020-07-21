function track = getTrack(fid)
kTRACKHEADER = 'G4WT0 > *********************************************************************************************************';
kTRACKTAIL = 'G4WT0 > -->';
kTRACKTAILLENG = 32;
kParticleFormatSpec = '%*s%*s%*s%*s%*s Particle = %s';
kParentIDFormatSpec = '%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s Parent ID = %d';
kVertexFormatSpec = '%*s%*s%d%f%f%f%f%f%f%f';
kBUFFERSIZE = 10;

isEOF = skipLine(fid, kTRACKHEADER);
if(isEOF == 1)
    track = {};
    return 
end
l = fgetl(fid);
track.Particle  = sscanf(l, kParticleFormatSpec, [1 kBUFFERSIZE]);
track.IsParent  = 1 - sscanf(l, kParentIDFormatSpec);
track.StepNum   = 1;
track.X         = zeros(1,kBUFFERSIZE);
track.Y         = zeros(1,kBUFFERSIZE);
track.Z         = zeros(1,kBUFFERSIZE);
track.KinE      = zeros(1,kBUFFERSIZE);
track.dE        = zeros(1,kBUFFERSIZE);
track.StepLeng  = zeros(1,kBUFFERSIZE);
track.TrackLeng = zeros(1,kBUFFERSIZE);
fgetl(fid); fgetl(fid); fgetl(fid);
while true
    l = fgetl(fid);
    if size(l,2) < kTRACKTAILLENG | isempty(strfind(l, kTRACKTAIL)) == false
        break;
    end
    vertexInfo = sscanf(l,kVertexFormatSpec,[1,8]);
    step = vertexInfo(1) + 1;
    track.StepNum = step;
    track.X(step) = vertexInfo(2);
    track.Y(step) = vertexInfo(3);
    track.Z(step) = vertexInfo(4);
    track.KinE(step) = vertexInfo(5);
    track.dE(step) = vertexInfo(6);
    track.StepLeng(step) = vertexInfo(7);
    track.TrackLeng(step) = vertexInfo(8);
end