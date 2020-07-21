function isEOF = skipLine(fid, kEVENTHEADER)
    isEOF = 0;
    while true
        l = fgetl(fid);
        if l == -1
            isEOF = 1;
            break
        end
        if isempty(strfind(l,kEVENTHEADER)) == false
            break;
        end
    end
end