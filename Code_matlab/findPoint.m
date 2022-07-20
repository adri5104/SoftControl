function [x,y] = findPoint(rgb,color, debug)
    
    if nargin < 3
        debug = 'x';
    end

    switch color
        case 'b'   
            [BW, ~] = imageThresholdBlue(rgb);
        case 'p'
            [BW, ~] = imageThresholdPurple(rgb);
        case 'g'
            [BW, ~] = imageThresholdPurple(rgb);
    end

    % Detectamos las regiones
    [misRegiones,mserCC] = detectMSERFeatures(BW);
    
    % Filtramos por excentricidad
    stats = regionprops('table',mserCC,'Eccentricity');
    eccentricityIdx = stats.Eccentricity < 0.55;
    misRegiones = misRegiones(eccentricityIdx);

    % Comprobamos numero de regiones detectadas
    if misRegiones.Count > 0

        x = misRegiones.Location(1,1);
        y = misRegiones.Location(1,2);

    else
        rgb22

        x = -1;
        y = -1;

    end
 
    if debug == 'y'
        figure;
        
        %imshow(rgb);
        pause(0.2);
        imshow(BW);
        hold on;
        pause(0.2);
        plot(misRegiones);
        text(x,y, color);
        pause(0.2) 
    end
end

