function [ imageCells ] = binsToImageCells( path )
%STATISTICS Summary of this function goes here
%   Detailed explanation goes here
    
    fileExt = '*.bin';
    files = dir(fullfile(path,fileExt));  
    
    
    len = size(files,1); 
    
    for i = 1 : 1 : len
        
        fileName = strcat(path,files(i,1).name)

        xyz = readVelodyne(fileName);

        [azimuth,elevation,r] = cart2sph(xyz(1,:), xyz(2,:), xyz(3,:));

        % azimuth is used in KITTI dataset, not the elevation angle
        % because of the unregular elevation and the regular azimuth
        
        imageOne = statisticsOnPoints(xyz, azimuth, r);
        
        imageCells{i} = imageOne;
        
        image(imageOne*255);
        
        
    end;  



end

