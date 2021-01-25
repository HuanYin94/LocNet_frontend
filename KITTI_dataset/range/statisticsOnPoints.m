function [ imageOne ] = statisticsOnPoints( xyzs, azimuths, rs)
%STATISTICSONPOINTS Summary of this function goes here
%   Detailed explanation goes here
    
    azimuths = rad2deg(azimuths);

    len = length(azimuths);
    
    % for KITTI
    N = 64;     
    b= 80;

    % meter
    minDist = 1;
    maxDist = 81;
     
    imageCount = zeros(N, b);
    imageOne = zeros(N, b);
    
    
    % KITTI dataset is different form ours, ring by ring
    % so the ring judge is also different
    
    % from the first ring
    ring = 1;
    
    for i = 2 : 1 : len
       
        % if new ring comes ?
        if i > 1
           ringFlag = newRingJudge(azimuths(1, i-1), azimuths(1, i)); 
           
           if ringFlag == 1
                test(ring, :) = [ring, i];
                ring = ring + 1;
                continue;  % the first of the ring is calculated
           end
        end
        
        % filter the underground point
        if xyzs(3, i) < -3
            continue;
        end
        
        % Range get
        distance = norm(xyzs(1:2, i));
        
        bucket = distanceJudge(distance, minDist, maxDist, b);
        
        % ++
       if bucket > 0          
           iCount = imageCount(ring, bucket);
           imageCount(ring, bucket) = iCount + 1;
       end
        
    end
        
    % normalization of each ring !
    
    for i = 1 : 1 : N
        
        sumRing = 0;
        
        for m = 1 : 1 : b
           sumRing = sumRing + imageCount(i, m);  
        end
        
        for m = 1: 1 : b
           imageOne(i, m) = imageCount(i, m) / sumRing;
        end
    end


end

