function [outArg] = filtro_dataset_segmento_roto(data, segmento)

% Funcion que filtra un dataset para, en caso de que se rompa una seccion
% de vejigas, este no quede inutilizado.
% El argumento "segmento" (1 - 9), indica que hilera de vejigas hay que
% filtrar.

% Se devuelve un dataset identico en el cual se han eliminado los indices
% en los cuales se hace uso de la hilera defectuosa

j = 1;

% Recorremos el dataset
for i = 1:data.nummuestras
    if data.inputs(i,segmento) == 0

        % Si llegamos aqui es que el dato se ha aceptado
        outArg.inputs(j, 1:9) = data.inputs(i, 1:9);
        outArg.outputs(j,1:6) = data.outputs(i, 1:6);
        outArg.index(j) = j;    
        j = j  + 1;
    
    else 

        continue
    end


end

outArg.nummuestras = j - 1;
outArg.pmax = data.pmax;
outArg.pmin =data.pmin;
outArg.temp_amb =data.temp_amb;
outArg.presion_presostato =data.presion_presostato;
outArg.controlporcentual =data.controlporcentual;
outArg.maxRpressure =data.maxRpressure;
