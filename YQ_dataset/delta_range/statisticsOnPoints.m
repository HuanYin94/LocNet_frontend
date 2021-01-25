function [ imageOne ] = statisticsOnPoints( xyzs, elevations)
%STATISTICSONPOINTS Summary of this function goes here
%   Detailed explanation goes here

    % our dataset, Yuquan South

    len = length(elevations);
    
    N = 15;     
    b= 80;

    minDist = 1;
    maxDist = 41;
     
    imageCount = zeros(N, b);
    imageOne = zeros(N, b);

    pointRingLast = zeros(2, N);
    
    for i = 1 : 1 : len
        
        % do not filter this time
%         % filter points outside (3, 80)
%         % 5 is 
%         if rs(1, i) > 80 || rs(1, i) < 3
%             continue;
%         end
      
        ring = ringJudge(elevations(1,i));
        
        if ring == -1
           continue; 
        end
        
        % init
        if pointRingLast(:, ring) == zeros(2, 1)          
            pointRingLast(:, ring) = xyzs(1:2, i);   % xy-dis only try
            continue;
        end
       
        
        % get the delta-distance one by one
        distance = norm(pointRingLast(:, ring) - xyzs(1:2, i));
        
        % meter to center-meter
        distance = distance * 100;
        
        bucket = distanceJudge(distance, minDist, maxDist, b);
                
        % ++
           if bucket > 0       
           iCount = imageCount(ring, bucket);
           imageCount(ring, bucket) = iCount + 1;
           end
           
        % Replace one by one
        pointRingLast(:, ring) = xyzs(1:2, i);
        
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

