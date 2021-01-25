function [ flag ] = newRingJudge( azimuth1, azimuth2)
%NEWRINGJUDGE Summary of this function goes here
%   Detailed explanation goes here

    % 0 is included, belongs to the new ring

    % rad2deg bug fixed
    
    if azimuth1 < 0 && azimuth2 >=0 && (azimuth2 - azimuth1) < 100
        flag = 1;
    else
        flag = 0;
    end
    
    

end

