import serial
import smbus2
import time
import GDA_upload as gda
import csv_creater as csv_c
from time import sleep
import numpy as np
data = []
filedir = '/home/pi/Downloads'
ser = serial.Serial('/dev/ttyACM0',9600)
#ser1 = serial.Serial('/dev/ttyACM1',9600)
def upload_csv(arr,i):
    upload_filedir = csv_c.create_csv(filedir,arr,i)
    # gda.upload('Battery_Pack_'+str(i)+'.csv',upload_filedir,'text/x-csv')
x = 1.0
while True:
    if(x!=11031998):
        try:
            x = float(ser.readline())
            print(x)
            if(x!=0 or x!=110319978):
                data.append(x)
        except:
            print("There was an error")
    else:
        sleep(1)
        print("Now printing the array \n")
        for i in range(0,len(data),38):
            BP = data[i:i+38]
            upload_csv(BP,1)
        x = 1
    
#for i in range(0,len(data)):
#    print(data[i])
