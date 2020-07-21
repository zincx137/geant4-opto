% Data Structure
% event:
% event.ID         {1, ..., kNUMOFEVENT}
% event.TrackNum 1
% event.Track      [] track itself is a struct. Store track info
% 
% track:
% track.Particle
% track.IsParent
% track.StepNum  *How many steps in this track. NB start from 1
% track.X
% track.Y
% track.Z
% track.KinE
% dE
% StepLeng
% TrackLeng
function eventCollection = geant4Formatter(kFILENAME)
fid = fopen(kFILENAME);
EventNum = 0;
eventCollection = struct('ID', {}, 'TrackNum', {}, 'Track', {});
while true
    track = getTrack(fid);
    if isempty(track) == true
        eventCollection(EventNum) = event;
        break;
    end
    if track.IsParent == true
        if EventNum > 0
            eventCollection(EventNum) = event;
        end
        EventNum = EventNum + 1;
        event.ID = EventNum;
        event.TrackNum = 1;
        event.Track = {track};
    else
        event.TrackNum = event.TrackNum + 1;        
        event.Track{1, event.TrackNum} = track;
    end
end
fclose(fid);
