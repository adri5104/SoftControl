function writeOneValveMillis(serialDevice,valv, millis)
            if millis > 0
                writeline(serialDevice, "f," + int2str(valv) + "," + int2str(millis));
            else
                writeline(serialDevice, "e" + int2str(valv) + "," + int2str(-millis));
            end

           
end