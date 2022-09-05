function pos2pos(obj,data, pos1,pos2)
    
    millis1 = data.inputs(pos1,:);
    millis2 = data.inputs(pos2,:);
    
    for i = 1:9
        millis2send(i) = millis2(i) - millis1(i)
        if millis2send(i) < 0
            millis2send(i) = millis2send(i) - 300;
        end
    end

    string2send = "w,1";
    for j = 1:9
        string2send = string2send + "," +  num2str( millis2send(j));
    end

    writeline(obj, string2send);

end