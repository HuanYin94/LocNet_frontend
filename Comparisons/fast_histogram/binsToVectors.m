function [ vectors ] = binsToVectors( path )
%BINSTOVECTOR Summary of this function goes here
%   Detailed explanation goes here

    fileExt = '*.bin';
    files = dir(fullfile(path,fileExt));  
      
    len = size(files,1); 
    
    for i = 1 : 1 : len
        tic
        fileName = strcat(path,files(i,1).name)
        xyz = readVelodyne(fileName);
       
        vectors(i, :) = statisticsOnRange(xyz);
        toc
    end


end

