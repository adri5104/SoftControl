import serial.tools.list_ports

def select_port():
    ports = serial.tools.list_ports.comports()
    portList = []
    for onePort in ports:
        portList.append(str(onePort))
        print(str(onePort))
    val = input("select Port: COM")

    for x in range(0,  len(portList)):
        if portList[x].startswith("COM" + str(val)):
            portVar = "COM" + str(val)
            print("Has seleccionado:\n" + portList[x])
            return portVar
        
    print("This serial port doesnt exist")
    return -1

def select_baudrate():
    print("Please, select baudrate\n")
    baudrate = input("Baudrate: ")
    return baudrate

def open_serial_port(serialObject):
    myPort = select_port()
    if myPort == -1:
        return -1

    myBaudrate = select_baudrate()
    
    serialObject.baudrate = 9600
    serialObject.port = 'COM13'
    
    try:
        serialObject.open()
    except:
        print("Port dont work")
        return -1
    else:
        print("Puerto abierto correctamente")
        return 0
    
    
    
def close_serial_port(serialObject):
    serialObject.close()
   
mySerial = serial.Serial()
_flag_serial_correctly_open =  open_serial_port(mySerial)
13

