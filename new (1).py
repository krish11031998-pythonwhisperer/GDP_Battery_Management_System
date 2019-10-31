import time
import serial
num = 0
while(1):
    ser = serial.Serial(port='/dev/ttyACM0',baudrate=9600,parity=serial.PARITY_NONE,
                    stopbits = serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS,
                    timeout=1)
    ser.flushInput()
    for i in range(0,5):
        counter = "60\n"
        ser.write(counter)
        time.sleep(1)
    ser.close