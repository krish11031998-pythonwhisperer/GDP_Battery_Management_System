import serial
import GDA_upload as gda
import csv_creater as csv_c
from time import sleep
import numpy as np

varVolt = 1.121e-05
varProcess = 1e-8
Pc = 0.0
G = 0.0
P = 1.0
Xp = 0.0
Zp = 0.0
Xe = 0.0


filedir = '/home/pi/Downloads'
ser = serial.Serial('/dev/ttyACM0',9600)
s = []
continue_counter = 1
counter = 1
BP1 = []
BP2 = []
BP3 = []
BP4 = []
def upload_csv(arr,i):
    upload_filedir = csv_c.create_csv(filedir,arr,i)
    gda.upload('Battery_Pack_'+str(i)+'.csv',upload_filedir,'text/x-csv')

def KLF(float value):
    Pc = P+varProcess
    G = Pc/(Pc + varVolt)
    P = (1 - G)*Pc
    Xp = Xe
    Zp = Xp
    Xe = G*(voltage - Zp) + Xp
    return Xe


while (continue_counter ==  1): 
    read_serial = ser.readline()
    print(read_serial)
    value = float(read_serial)
    if(counter <= 20 and value!=0):
        BP1.append(value)
        counter+=1
    elif(counter <= 40 and value!=0):
        BP2.append(value)
        counter+=1
    elif(counter<= 60 and value!=0):
        value = float(read_serial)
        BP3.append(value)
        counter+=1
    elif(counter<= 80 and value!=0):
        value = float(read_serial)
        BP4.append(value)
        counter+=1
    elif(counter<=88 and value!=0):
        value = float(read_serial)
        if(counter<=82):
            BP1.append(KLF(value))
        if(counter<=84):
            BP2.append(KLF(value))
        if(counter<=86):
            BP3.append(KLF(value))
        if(counter<=88):
            BP4.append(KLF(value))
    elif(counter<=89 and value!=0):
        cuurent = float(read.serial)
        BP1.append(current)
        BP2.append(current)
        BP3.append(current)
        BP4.append(current)
    elif(counter == 90):
        acc = float(read_serial)
        BP1.append(acc)
        BP2.append(acc)
        BP3.append(acc)
        BP4.append(acc) 
    elif(value == 0):
        upload_csv(np.asarray(BP1,dtype=float),1)
        BP1 = []
        sleep(2)
        upload_csv(np.asarray(BP2,dtype=float),2)
        BP2 = []
        sleep(2)
        upload_csv(np.asarray(BP3,dtype=float),3)
        BP3 = []
        sleep(2)
        upload_csv(np.asarray(BP4,dtype=float),4)
        BP4 = []
        sleep(2)
        counter = 1
        continue_counter == 1
    else:
        print('Something is wrong')
