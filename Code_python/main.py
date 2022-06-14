from re import S
import serial.tools.list_ports
#from Utiles import open_serial_port
def close_serial_port(serialObject):
    serialObject.close()

_flag_serial_correctly_open = -1
userReading = 0


serialObject = serial.Serial()
serialObject.baudrate = 9600
serialObject.port = 'COM13'
serialObject.open()

while True:
    if serialObject.in_waiting:
        packet = serialObject.readline()
        print(packet.decode('utf'))    

    

        
            
        


