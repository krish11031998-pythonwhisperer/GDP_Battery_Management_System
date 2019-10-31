import csv
import os
from pathlib import Path
import voltage_divider as vd

def check_dir(filedir):
    config = Path(filedir)
    if(config.is_file()):
        return 1
    else:
        return 0

def voltage_div(data):
    for q in range(0,len(data))
        if(data[0] == 68.0):
            i = 1
            arr = []
            while(data[i] !=69.0):
                arr.append(data[i])
                i+=1
            arr = vd.voltage_fr_VD(arr,1)
            for i in range(0,17):
                data[i+1] = arr[i]
        elif(data[17] == 68.0):
            i = 18
            arr = []
            while (data[i] > 6.0):
                arr.append(data[i])
                i+=1
            arr = vd.voltage_fr_VD(arr,2)
            for i in range(0,17):
                data[i+18] = arr[i]
    return(data)

def create_csv(filedir,data_arr,i):
    data_arr = voltage_div(data_arr)
    new_filedir = filedir+"/Battery_Pack_"+str(i)+".csv"
    file_check = check_dir(new_filedir)
    if(file_check == 0):
        with open(new_filedir,"w") as battcsv:
            wr = csv.writer(battcsv,dialect='excel')
            # if(len(data_arr)>40):
            #     arr = []
            #     for i in range(0,len(data_arr)):
            #         if(i%40!=0):
            #             arr.append(data_arr[i])
            #         elif(i%40 == 0):
            wr.writerow(data_arr)
            
            else:
                wr.writerow(data_arr)
        return(new_filedir)
    elif(file_check == 1):
        data_arr = voltage_div(data_arr)
        with open(new_filedir,"a") as battcsv:
            wr = csv.writer(battcsv,dialect = 'excel')
            # if(len(data_arr)>40):
            #     arr = []
            #     for i in range(0,len(data_arr)):
            #         if(i%40!=0):
            #             arr.append(data_arr[i])
            #         elif(i%40 == 0):
            wr.writerow(data_arr)
            else:
                wr.writerow(data_arr)
        return(new_filedir)
    

