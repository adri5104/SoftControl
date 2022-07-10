classdef Robot < handle
    properties (Access = public)
        SerialDevice;
        NumValvulas;
        millisSendedToValves;
    end

    methods
        %function this = Robot(SerialPort_,BaudRate_, num)
        %    %Constructor
        %    this.SerialPort = SerialPort_;
        %    this.BaudRate = BaudRate_;
        %    this.SerialDevice = SerialPort_;
        %    configureTerminator(this.SerialDevice,"CR/LF", "LF");
        %    this.NumValvulas = num;
        %    flush(this.SerialDevice);
        %    this.millisSendedToValves = [0 0 0 0 0 0 0 0 0 ];
        %end

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