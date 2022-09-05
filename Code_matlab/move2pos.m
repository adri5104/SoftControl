function move2pos(obj, data, pos, net)
    PMAX = 500;

    if nargin < 4


    
   
    string2send = "w,1";
    for j = 1:9
        string2send = string2send + "," +  num2str( data.inputs(pos, j));
    end

    writeline(obj, string2send);
    

    else
        millis2send = net(pos)'
        string2send = "w,1";
        for j = 1:9
            if millis2send(j) > PMAX
                millis2send(j) = PMAX;
            end
                

            string2send = string2send + "," +  num2str( data.inputs(pos, j));
        end
    writeline(obj, string2send);
    
end