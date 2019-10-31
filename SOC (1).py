import pandas as pd
import numpy as np
import sklearn
import csv
import matplotlib.pyplot as plt

data = pd.read_csv('C:\Users\kv1g15\Downloads\Book1.csv')
vol_data = data.iloc[1:180,0].values
time_data = data.iloc[1:180,1].values

arr = []
for i in time_data:
    arr.append(100 -((i- time_data.min())*100/time_data.max()))
    
r = np.array(arr)
#r1 = np.append(time_data,vol_data,axis=1)
#r_final = np.append(r1,r,axis=1)

def find_SOC(x):
    for i in range(len(vol_data)):
        if(x < vol_data[i]):
            print(i,r[i])
            continue
        else:
            break
    return r[i-1]


SOC = find_SOC(3.6)
print(SOC)
plt.plot(time_data,r)
#with open('C:\Users\kv1g15\Downloads\Book1_changed.csv','wb') as csvfile:
    