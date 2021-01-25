function [ imageCells ] = binsToImageCells( path )
%STATISTICS Summary of this function goes here
%   Detailed explanation goes here
    
%     fileExt = '*.bin';
    fileExt = '*.ply';
    files = dir(fullfile(path,fileExt));  
    
    
    len = size(files,1); 
       
%     for i = 1 : 1 : len
% loop exps
    for i = 0 : 1 : 39566
%         fileName = strcat(path,files(i,1).name)
%         xyz = readVelodyne(fileName);

        fileName = [path, int2str(i), '.ply'];
        disp(fileName);

%         tic
        xyz = pcread(fileName);
        xyz = xyz.Location;
        xyz = xyz';
        
        [azimuth,elevation,r] = cart2sph(xyz(1,:), xyz(2,:), xyz(3,:));

        % azimuth not used
        % azimuth is down simple
        
        imageOne = statisticsOnPoints(xyz, elevation);
        
        
%         toc;
%         imageCells{i} = imageOne;
        imageCells{i+1} = imageOne;

        image(imageOne*255);
        
        
    end;  



end

