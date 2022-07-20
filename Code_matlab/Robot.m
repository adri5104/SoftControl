classdef Robot < handle
    properties (Access = public)
        SerialDevice;
        NumValvulas;
        millisSendedToValves;
        tiempo_desinflado = 1000;
    end

    methods
        function this = Robot(SerialDevice_)
            this.SerialDevice = SerialDevice_
        end

        function outputArg = method1(this,inputArg)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            outputArg = this.Property1 + inputArg;
        end

        function millis = getMillis(this)

            write(this.SerialDevice, 'r', "char");
            millis = str2double(readline(this.SerialDevice));
            
        end
 
        
        % Se envia presion a una valvula en concreto
        function writeOneValveMillis(this, valv, millis)
            if millis > 0
                writeline(this.SerialDevice, "f," + int2str(valv) + "," + int2str(millis));
            else
                writeline(this.SerialDevice, "e" + int2str(valv) + "," + int2str(-millis));
            end

            this.millisSendedToValves(valv) = this.millisSendedToValves(valv) + millis;
        end

        function millis = getMillisSended(this)
            millis = this.millisSendedToValves;

        end

        


    end
end