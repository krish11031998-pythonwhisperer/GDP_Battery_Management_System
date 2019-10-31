import time
import serial
num = 0
ser = serial.Serial('/dev/ttyACM0',9600)
ser.flushInput()
counter = ['60','70','80','90','100']
while(num!=5):
    ser.write(counter[num])
    print(counter[num])
    time.sleep(1)
    num+=1
ser.close