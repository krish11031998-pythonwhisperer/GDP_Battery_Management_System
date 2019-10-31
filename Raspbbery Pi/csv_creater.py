import csv
import os
from pathlib import Path

def check_dir(filedir):
    config = Path(filedir)
    if(config.is_file()):
        return 1
    else:
        return 0

def create_csv(filedir,data_arr,i):
    new_filedir = filedir+"/Battery_Pack_"+str(i)+".csv"
    file_check = check_dir(new_filedir)
    if(file_check == 0):
        with open(new_filedir,"w") as battcsv:
            wr = csv.writer(battcsv,dialect='excel')
            if(len(data_arr)>90):
                arr = []
                for i in range(0,len(data_arr)):
                    if(i%90!=0):
                        arr.append(data_arr[i])
                    elif(i%90 == 0):
                        wr.writerow(arr)
                        arr = []
            else:
                wr.writerow(data_arr)
        return(new_filedir)
    elif(file_check == 1):
        with open(new_filedir,"a") as battcsv:
            wr = csv.writer(battcsv,dialect = 'excel')
            if(len(data_arr)>90):
                arr = []
                for i in range(0,len(data_arr)):
                    if(i%90!=0):
                        arr.append(data_arr[i])
                    elif(i%90 == 0):
                        wr.writerow(arr)
                        arr = []
            else:
                wr.writerow(data_arr)
        return(new_filedir)
    

