import serial
import GDA_upload as gda
import csv_creater as csv_c

filedir = '/home/pi/Downloads'
ser = serial.Serial('/dev/ttyACM0',9600)
s = []
continue_counter = 1

def upload_csv(arr):
    new_filedir = csv_c.create_csv(filedir,arr,1)
    gda.upload('Cell_Data.csv',new_filedir,'text/x-csv')

while (continue_counter ==  1):
    read_serial = ser.readline()
    value = float(read_serial)
    if(value!=0):
        s.append(value)
    elif(value == 0):
        continue_counter = 0
        upload_csv(s)
        break
    else:
        print('Something weird has happened')