function [ imageOne ] = statisticsOnPoints( xyzs, elevations)
%STATISTICSONPOINTS Summary of this function goes here
%   Detailed explanation goes here

    % our dataset, Yuquan South
    % Range only, in robio

    len = length(elevations);
    
    N = 15;     
    b= 80;

    minDist = 1;
    maxDist = 81;
     
    imageCount = zeros(N, b);
    imageOne = zeros(N, b);
    
    for i = 1 : 1 : len
       
        ring = ringJudge(elevations(1,i));
        
        if ring == -1
           continue; 
        end
        
        % get the distance , meter directly
        distance = norm(xyzs(1:2, i));
        
        bucket = distanceJudge(distance, minDist, maxDist, b);
                
        % ++
           if bucket > 0       
           iCount = imageCount(ring, bucket);
           imageCount(ring, bucket) = iCount + 1;
           end
           
        
    end
    
    
    % normalization of each ring !
    % or the whole point cloud ?
    
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

