import serial
import GDA_upload as gda
import csv_creater as csv_c
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
    

while (continue_counter ==  1):
    try:
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
            BP3.append(value)
            counter+=1
        elif(counter<= 80 and value!=0):
            value = float(read_serial)
            BP4.append(value)
            counter+=1
        elif(counter <=86 and value!=0):
            B1.append(value)
            counter+=1
        elif(counter <=92 and value!=0):
            B2.append(value)
            counter+=1
        elif(counter <=98 and value!=0):
            B3.append(value)
            counter+=1
        elif(counter <=104 and value!=0):
            B4.append(value)
            counter+=1
        elif(counter <=105 and value!=0):
            B1.append(value)
            B2.append(value)
            B3.append(value)
            B4.append(value)
            counter+=1
        elif(counter <=106 and value!=0):
            B1.append(value)
            B2.append(value)
            B3.append(value)
            B4.append(value)
            counter= 1
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
            sleep(1)
            counter = 1
            continue_counter == 1
        else:
            print('Something is wrong')
    except:
        print("ERROR")
