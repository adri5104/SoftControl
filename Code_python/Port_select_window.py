from ast import Lambda
import tkinter as tk
from tkinter import StringVar, ttk
import serial.tools.list_ports
from tkinter import messagebox



class PortSelect(tk.Toplevel):
    def __init__(self, parent):
        super().__init__(parent)
        
        self.mySerialObject = serial.Serial()

        self.geometry('300x250')
        self.title('Port selection window')

        # Menubutton variable
        self.selected_port = tk.StringVar()
        self.selected_port.trace("w", self.menu_item_selected)

        self.Disp = ttk.Label(self)
        
        self.Disp.pack()
        

        # create the menu button
        self.create_menu_button()
        
        self.create_connect_button()
        
        self.status = -1
        
        self.closeButton = ttk.Button(self, text= "close", command=  self.close ).pack()
        
        self.text = StringVar()
        self.text.set("Non connected")
        self.Disp.config(textvariable=self.text)
        
    def getStatus(self):
        return self.status
    
    def close(self):
        self.status = -1	
    
    
    def menu_item_selected(self, *args):
        """ handle menu selected event """
        
        print(self.selected_port.get())
        
    def connect_button_pressed(self, *args):   
        serialObject = serial.Serial()
        serialObject.port = self.selected_port.get()
        serialObject.baudrate = 9600
        
        #str(self.selected_port.get())
        try:
            serialObject.open()
        except:
            self.Disp.config(textvariable=self.text)
            messagebox.showinfo("Error", "Error opening port")
        
        else:
            messagebox.showinfo("xd", "Puerto abierto correctamente")
            self.mySerialObject = serialObject
            self.status = 1
        
        print("xd")
        
    def create_menu_button(self):
       

        # create the Menubutton
        menu_button = ttk.Menubutton(
            self,
            text='Select a available port')

        # create a new menu instance
        menu = tk.Menu(menu_button, tearoff=0)
        ports = serial.tools.list_ports.comports()
        portList = []
        for onePort in ports:
            portList.append(str(onePort))
            
        for x in range(0,len(portList)):
            menu.add_radiobutton(
                label=portList[x],
                value=portList[x].rpartition(' -')[0],
                variable=self.selected_port)

        # associate menu with the Menubutton
        menu_button["menu"] = menu

        menu_button.pack(expand=True)
        
    def create_connect_button(self):
        
        connect_button = ttk.Button(self, text= "Conectar", command= self.connect_button_pressed)
        connect_button.pack()
     
    def getSerialObject(self):
        if self.status == 1: 
            return self.mySerialObject   
        




    
        

    



