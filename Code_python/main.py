import tkinter as tk
from tkinter import ttk
from tkinter import StringVar, ttk
from tkinter import messagebox
import serial.tools.list_ports
import Utiles
import Port_select_window


root = tk.Tk()
root.title("LIETM")
root.iconbitmap('./assets/logo.ico')

window_width = 800
window_height = 800
window_width_small = 400 
window_height_small = 400



def port_select_pressed():
    aux = Port_select_window.PortSelect(root)
    aux.grab_set()

# get the screen dimension
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

# find the center point
center_x = int(screen_width/2 - window_width / 2)
center_y = int(screen_height/2 - window_height / 2)

# set the position of the window to the center of the screen
root.geometry(f'{window_width}x{window_height}+{center_x}+{center_y}')
root.resizable(False,False)



port_select = ttk.Button(root, text="Select Port", command=port_select_pressed)
port_select.pack()



root.mainloop()