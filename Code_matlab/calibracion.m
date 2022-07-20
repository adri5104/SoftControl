function [data] = calibracion(NUM_POSICIONES, DEBUG)

if nargin < 2
    DEBUG = 'x';
end



PRESION_MAX = 1000
PRESION_MIN = 0
COM = 'COM22'
BAUDIOS = 9600
GRADOS_LIBERTAD = 9
TIEMPO_DESINFLADO = 2000;
CAM1_NAME = 'XiaoMi USB 2.0 Webcam'; %webcamlist




% Comienzo script

% Configuracion camara
cam1 = webcam(CAM1_NAME);

if DEBUG ~= 'y'
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
    desinflar(obj, TIEMPO_DESINFLADO);
    pause(TIEMPO_DESINFLADO);
end

% Para cada posicion
for i = 1:NUM_POSICIONES
    
    millis2send = round((PRESION_MAX)*rand(GRADOS_LIBERTAD,1) + PRESION_MIN);
    string2send = "w,1";
    
    for j = 1:GRADOS_LIBERTAD
        string2send = string2send + "," +  num2str( millis2send(j));
    end
    
    %Se guarda el num de dato
    data.all(i,1) = i;
    
    % Guardamos la combinacion de presiones enviada
    for j = 2:GRADOS_LIBERTAD + 1
        data.inputs(i,j) = millis2send(j-1);
    end

    if DEBUG ~= 'y'
        %Movemos a posicion indicada
        writeline(obj, string2send);
        pause(2);
    end

    %Aqui tomariamos foto
    img = snapshot(cam1);
    img_name = "cam1_" + num2str(i) + ".jpeg";
    imwrite(img, img_name, 'jpeg');

    if DEBUG == 'y'
        subplot(2,1,1);
    end
    
    % Encontramos marca azul
    [x,y] = findPoint(img, 'b', DEBUG);    

    % La guardamos
    data.outputs.blue(i,1) = x; data.outputs.blue(i,2) = y;
    

    close();

    % Encontramos marca rosa
    [x,y] = findPoint(img, 'p');    

    % La guardamos
    data.outputs.purple(i,1) = x; data.outputs.purple(i,2) = y;
    close();

    % Encontramos marca verde
    [x,y] = findPoint(img, 'g');    

    % La guardamos
    data.outputs.green(i,1) = x; data.outputs.purple(i,2) = y;
    close();
    

    if DEBUG ~= 'y'
        	desinflar(obj, TIEMPO_DESINFLADO);
            pause(TIEMPO_DESINFLADO);
    end
    
       
    


end

delete(cam1);
if DEBUG ~= 'y'
delete(obj);
end
end