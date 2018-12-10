import serial 
import numpy  
import matplotlib.pyplot as plt 
from drawnow import *
from Conecta import Arduino

T1= []
U1=[]

plt.ion() 
cnt=0

def makeFig(): 
    plt.ylim(10,90)                                 
    plt.title('My Live Streaming Sensor Data')      
    plt.grid(True)                                  
    plt.ylabel('Temperatura ')                           
    plt.plot(T1, 'ro-', label='Graus C')       
    plt.legend(loc='upper left')                    
    plt2=plt.twinx()                                
    plt.ylim(10,100)                           
    plt2.plot(U1, 'b^-', label='Umidade ') 
    plt2.set_ylabel('Unidade Um')                    
    plt2.ticklabel_format(useOffset=False)           
    plt2.legend(loc='upper right')                  
    

while True: # While loop that loops forever
    ArduinoCnx = Arduino('COM3', 9600, 2)
    arduinoString = ArduinoCnx.cmdToSerial("T1U1\n") 
    arduinoString = str(arduinoString, 'utf-8')
    arduinoString = arduinoString.replace("\n", "")
    dataArray = arduinoString.split(";")   
    temp = float( dataArray[0])            
    P =    float( dataArray[1])            
    T1.append(temp)                     
    U1.append(P)                     
    drawnow(makeFig)                       
    plt.pause(.000001)                     
    cnt=cnt+1
    if(cnt>50):                            
        T1.pop(0)                       
        U1.pop(0)
