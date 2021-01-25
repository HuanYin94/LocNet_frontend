function [ Ring ] = ringJudge( elevation )
%RINGJUDGE Summary of this function goes here
%   Detailed explanation goes here

    % standards +- 0.01
    
    if elevation <= -0.2608 && elevation >= -0.2628
        Ring = 15;
        return;
    end
    
    if elevation <= -0.1910 && elevation >= -0.1930
        Ring = 14;
        return;
    end

    if elevation <= -0.1561 && elevation >= -0.1581
        Ring = 13;
        return;
    end
    
    if elevation <= -0.1212 && elevation >= -0.1232 
        Ring = 12;
        return;
    end
    
    if elevation <= -0.0863 && elevation >= -0.0883
        Ring = 11;
        return;
    end
    
    if elevation <= -0.0514 && elevation >= -0.0534
        Ring = 10;
        return;
    end
    
    if elevation <= -0.0165 && elevation >= -0.0185
        Ring = 9;
        return;
    end
    
    if elevation <= 0.0185 && elevation >= 0.0165
        Ring = 8;
        return;
    end
    
    if elevation <= 0.0534 && elevation >= 0.0514
        Ring = 7;
        return;
    end
    
    if elevation <= 0.0883 && elevation >= 0.0863
        Ring = 6;
        return;
    end

    if elevation <= 0.1232 && elevation >= 0.1212
        Ring = 5;
        return;
    end
    
    if elevation <= 0.1581 && elevation >= 0.1561
        Ring = 4;
        return;
    end
    
    if elevation <= 0.1930 && elevation >= 0.1910
        Ring = 3;
        return;
    end
    
    if elevation <= 0.2279  && elevation >= 0.2259
        Ring = 2;
        return;
    end
    
    if elevation <= 0.2628 && elevation >= 0.2608
        Ring = 1;
        return;
    end
    
    Ring = -1;
    
end

