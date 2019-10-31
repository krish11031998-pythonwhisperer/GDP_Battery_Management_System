import serial
import GDA_upload as gda
import csv_creater as csv_c
import voltage_divider as vd
from time import sleep
import numpy as np

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
    
def data_append(x):
    counter = 1
    if(x==1):
        while(counter<= 20):
            read_serial = ser.readline()
            print(read_serial)
            BP1.append(float(read_serial))
            counter +=1
    elif(x==2):
        while(counter<= 20):
            read_serial = ser.readline()
            print(read_serial)
            BP2.append(float(read_serial))
            counter +=1
    elif(x==3):
        while(counter<= 20):
            read_serial = ser.readline()
            print(read_serial)
            BP3.append(float(read_serial))
            counter +=1
    elif(x==4):
        while(counter<= 20):
            read_serial = ser.readline()
            print(read_serial)
            BP4.append(float(read_serial))
            counter +=1
    else:
        print("Wrong index")

while (continue_counter ==  1): 
    read_serial = ser.readline()
    print(read_serial)
    value = float(read_serial)
    if(value == 69 and value!=0):
        data_append(2)
    elif(value == 68 and value!=0):
        data_append(2)
    elif(counter == 70 and value!=0):
        data_append(3)
    elif(counter== 71 and value!=0):
        data_append(4)
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
