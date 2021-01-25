function [ bucket ] = distanceJudge( distance, minDist, maxDist, b)
%RANGEJUDGE Summary of this function goes here
%   Detailed explanation goes here

    distBucket = (maxDist - minDist) / b;
    
    if distance > minDist && distance < maxDist
        % from .cpp of laserScan_Similarity
       for i = 0 : 1 : b
           if distance >= (minDist + i*distBucket) && distance <= (minDist + (i+1)*distBucket)
                bucket = i + 1;
           end
       end
       
    else
        bucket = -1;
    end
        
end

