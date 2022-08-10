function [data] = calibracion(NUM_POSICIONES, camPar, DEBUG)

if nargin < 2
    DEBUG = 'x';
end

% Algunos parametros
PRESION_MAX = 700;
PRESION_MIN = 0;
COM = 'COM22';
BAUDIOS = 9600;
NUM_SEGMENTOS = 3;
GRADOS_LIBERTAD = 9;    
TIEMPO_DESINFLADO = 2;
CAMARA_YZ = 4;
CAMARA_XZ = 2;
millis2send_ = ones(NUM_SEGMENTOS);
millisdesinflar = "w,1,-2000,-2000,-2000,-2000,-2000,-2000,-2000,-2000,-2000";

% Comienzo script

% Configuracion camaras
cam_yz = webcam(CAMARA_YZ);
cam_xz = webcam(CAMARA_XZ);

% Calculamos poses de las camaras
[rot_yz, trans_yz] = findCameraPose(cam_yz, camPar);
[rot_xz, trans_xz] = findCameraPose(cam_xz, camPar);

% Creamos objeto serial
try
    obj = serialport(COM,BAUDIOS);
catch
    disp("ERROR: COM no funciona");
    delete(cam1);
    return;
end

configureTerminator(obj,"CR/LF", "LF");

% Desinflamos
writeline(obj,millisdesinflar);
pause(TIEMPO_DESINFLADO);

% Para cada posicion
for i = 1:NUM_POSICIONES
    string2send = "w,1";
    
    % Se determina que vejiga se queda sin hinchar de cada segmento
    sin_hinchar = round(2* rand(1, NUM_SEGMENTOS) + 1); 
    millis2send_ = ones(NUM_SEGMENTOS);

    for j = 1:NUM_SEGMENTOS
        for k = 1:3
            if sin_hinchar(j) == k
                millis2send_(j,k) = 0;
            else    
                millis2send_(j,k) = round((PRESION_MAX - PRESION_MIN) * rand(1:1) + PRESION_MIN);
            end
        
        end
    end

    millis2send = diag(ones(NUM_SEGMENTOS));
    millis2send(1:3) = millis2send_(1,:);
    millis2send(4:6) = millis2send_(2,:);
    millis2send(7:9) = millis2send_(3,:);    
    
    for j = 1:GRADOS_LIBERTAD
        string2send = string2send + "," +  num2str( millis2send(j));
    end
    
    %Se guarda el num de dato
    data.all(i,1) = i;
    
    % Guardamos la combinacion de presiones enviada
    for j = 2:GRADOS_LIBERTAD + 1
        data.inputs(i,j) = millis2send(j-1);
    end
    
    %Movemos a posicion indicada
    writeline(obj, string2send);
    pause(max(millis2send)/1000);
    
    %Aqui tomariamos las foto
    img_yz = snapshot(cam_yz);
    img_name_yz = "cam_yz" + num2str(i) + ".jpeg";
    imwrite(img_yz, img_name_yz, 'jpeg');

    img_xz = snapshot(cam_xz);
    img_name_xz = "cam_xz" + num2str(i) + ".jpeg";
    imwrite(img_xz, img_name_xz, 'jpeg');

    %buscamos las marcas en la imagen yz
    blue_yz = findPoint(img_yz, 'b'); 
    data.img_points.yz.blue(i,1:2) = blue_yz;
    close();
    green_yz = findPoint(img_yz, 'g');
    data.img_points.yz.green(i,1:2) = green_yz;

    %buscamos las marcas en la imagen xz
    blue_xz = findPoint(img_xz, 'b'); 
    data.img_points.xz.blue(i,1) = blue_xz(1);
    data.img_points.xz.blue(i,2) = blue_xz(2);

    close();
    green_xz = findPoint(img_xz, 'g');
    data.img_points.xz.green(i,1:2) = green_xz;

    % Calculamos los puntos reales en el sistema de coordenadas de las
    % camaras

    xy = pointsToWorld(camPar.Intrinsics, rot_yz, trans_yz, blue_yz);
    xz = pointsToWorld(camPar.Intrinsics, rot_xz, trans_xz, blue_xz);
    blue = getCoordinates(xy, xz);
    data.outputs.blue(i,1:3) = blue;

    xy = pointsToWorld(camPar.Intrinsics, rot_yz, trans_yz, green_yz);
    xz = pointsToWorld(camPar.Intrinsics, rot_xz, trans_xz, green_xz);
    green = getCoordinates(xy, xz);
    data.outputs.green(i,1:3) = green;
        
    writeline(obj,millisdesinflar)
    pause(TIEMPO_DESINFLADO);
end

delete(cam_yz);
delete(cam_xz)
if DEBUG ~= 'y'
delete(obj);
end
end