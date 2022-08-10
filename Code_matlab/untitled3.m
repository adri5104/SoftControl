% Algunos parametros
PRESION_MAX = 2000;
PRESION_MIN = 100;
COM = 'COM22';
BAUDIOS = 9600;
NUM_SEGMENTOS = 3;
TIEMPO_DESINFLADO = 5;
CAMARA_YZ = 4;
CAMARA_XZ = 2;
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


    disp(sin_hinchar);
    disp(millis2send_);
    disp(millis2send);