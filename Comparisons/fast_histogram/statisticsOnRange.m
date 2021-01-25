function [ vector ] = statisticsOnRange( xyz )
%STATISTICSONRANGE Summary of this function goes here
%   Detailed explanation goes here

    minDist = 0;
    maxDist = 80;
    b = 80;
    
    vector = zeros(1, b);
    
    count = 1;
    for i=1:length(xyz)
        
        if xyz(3,i) < -5   % some points filtered
           continue;
        end
        
        Range(count,:) = (xyz(1,i)^2 + xyz(2,i)^2 + xyz(3,i)^2).^0.5;
        count = count + 1;    
    end
    
    % statistics
    for i=1:length(Range)
       
        bucket = distanceJudge(Range(i,:), minDist, maxDist, b);
        
        if bucket > 0
           vector(1, bucket) =  vector(1, bucket) + 1;
        end
      
    end
    
    % normalization
    for i =1:b
       vector(1, i) = vector(1, i) / length(Range); 
    end
    

end

