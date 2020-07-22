function genProfileCollection = geant4GenerationProfile(eventCollection, isPlot, isProfile)
um = 1.;
keV = 1.;
ps = 1.;
s = 1e12 * ps;
eV = 1e-3 * keV;
mm = 1e3 * um;
m = 1e3 * mm;
m3 = m^3;
MeV = 1e3 * keV;
kBinWidth = 3 * um;
kEH = 4.43 * eV;
kGENTIME = 1 * ps;

genProfileCollection = struct('genProfile', {}, 'Axis', {});
comptE = [];
photE = [];
eTrackLength = [];
RaylCnt = 0;
eBremECnt = 0;
tranmitCnt = 0;

%% Tragetory Visualization
if isPlot == true
    for iEvent = 1:size(eventCollection,2)
        if eventCollection(iEvent).TrackNum == 1
            continue;
        end
        if strcmp(track.Particle, 'gamma,')
            % The following command is only available after MATLAB 2016b
            plot3(track.X,track.Y,track.Z,'--*','Color','g','MarkerIndices',1, 'DisplayName', 'Gamma');
            axis tight
            hold on
        end
        if strcmp(track.Particle, 'e-,')
            % The following command is only available after MATLAB 2016b
            plot3(track.X,track.Y,track.Z,'-o','Color','b','MarkerSize',10,'MarkerFaceColor','#D9FFFF', 'DisplayName', 'e-');
            axis manual
            hold on
        end
    end
    hold off
    legend();
    savefig("Trajectory " + string(iEvent) + ".fig");
end

for iEvent = 1:size(eventCollection,2)
    if eventCollection(iEvent).TrackNum == 1
        tranmitCnt = transmitCnt + 1;
        continue;
    end
    for iTrack = 1: eventCollection(iEvent).TrackNum
%% Collect Statistical Information
        track = eventCollection(iEvent).Track{iTrack};
        if strcmp(track.Particle, 'e-,')
            eTrackLength(end + 1) = track.TrackLeng(track.StepNum);
        end
        for iStep = 1:track.StepNum
            if strcmp(track.Proc{iStep}, 'compt')
                comptE(end + 1) = track.KinE(iStep - 1) - track.KinE(iStep) - track.dE(iStep);
            end
            if strcmp(track.Proc{iStep}, 'phot')
                photE(end + 1) = track.KinE(iStep - 1) - track.KinE(iStep);
            end
            if strcmp(track.Proc{iStep}, 'Rayl')
                RaylCnt = RaylCnt + 1;
            end
            if strcmp(track.Proc{iStep}, 'eBrem')
                eBremECnt = eBremECnt + 1;
            end
            if strcmp(track.Proc{iStep}, 'eBrem')
                eBremECnt = eBremECnt + 1;
            end
        end
        
%% Generation Profile
        if isProfile ~= true
            continue;
        end
% Collect Tragectories
        trackCollection = cell(0);
        for iTrack = 1: eventCollection(iEvent).TrackNum
            track = eventCollection(iEvent).Track{iTrack};
            if strcmp(track.Particle, 'e-,')
                t = zeros(track.StepNum,4);
                t(:,1) = track.X(1:track.StepNum) * mm;
                t(:,2) = track.Y(1:track.StepNum) * mm;
                t(:,3) = track.Z(1:track.StepNum) * mm;
                t(:,4) = track.dE(1:track.StepNum)* MeV;
                trackCollection{end + 1} = t;
            end
        end
% Mesh the space
        posMin = [  min(min(trackCollection{:}(:,1))), ...
            min(min(trackCollection{:}(:,2))), ...
            min(min(trackCollection{:}(:,3))) ] * um;
        posMax = [  max(max(trackCollection{:}(:,1))), ...
            max(max(trackCollection{:}(:,2))), ...
            max(max(trackCollection{:}(:,3))) ] * um;
        posOffset = (posMin + posMax) / 2 * um;
        posRange = (posMax - posMin) * um;
        NumBin = ceil(posRange / kBinWidth);
        Axis = cell(1,3);
        for iAxis = 1:3
            Axis{iAxis} = linspace( posMin(iAxis), posMax(iAxis), NumBin(iAxis) );
        end
% Categorize vertices
        E_lost = zeros(NumBin(1), NumBin(2), NumBin(3));
        for iTrack = 1:size(trackCollection,2)
            for iStep = 1:size(trackCollection{iTrack},2)
                loc = zeros(3);
                for iAxis = 1:3
                    [val, loc(iAxis)] = min(abs(Axis{iAxis} - trackCollection{iTrack}(iStep,iAxis)));
                end
                E_lost(loc(1), loc(2), loc(3)) = E_lost(loc(1), loc(2), loc(3)) + trackCollection{iTrack}(iStep,4);
            end
        end
        genProfile = E_lost / kEH / ( kBinWidth^3 / m3 ) / (kGENTIME / s);
        genProfileCollection{end + 1}.genProfile = genProfile;
        genProfileCollection{end}.Axis = Axis;
    end
end
    %% Plot
    h = histogram(photE * MeV, 'BinWidth',10 * keV);
    title('Electron Energy Distribution of Photoelectric Process');
    legend("std: " + string(std(h.Data)) + " mean: " + string(mean(h.Data)) + " count: " + string(size(h.Data,2));
    savefig('photHist.fig')
    h = histogram(comptE * MeV, 'BinWidth',10 * keV);
    title('Electron Energy Distribution of Compton Process');
    legend("std: " + string(std(h.Data)) + " mean: " + string(mean(h.Data)) + " count: " + string(size(h.Data,2));
    savefig('comptHist.fig')
    h = histogram(eTrackLength * mm, 'BinWidth',5 * um);
    title('Electron Track Length Distribution');
    legend("std: " + string(std(h.Data)) + " mean: " + string(mean(h.Data)) + " count: " + string(size(h.Data,2));
    savefig('trackLenHist.fig');
    RaylCnt
    eBremECnt
    transmitCnt
