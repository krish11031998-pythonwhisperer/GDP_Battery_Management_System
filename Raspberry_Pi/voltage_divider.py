# -*- coding: utf-8 -*-
"""
Created on Tue Apr 30 23:23:59 2019

@author: kv1g15
"""

def voltage_fr_VD(board,voltage):
    cal_vol = []
    if(board == 1):
        R1 = [150,237,390,510,120,220,220,237,237,390,150,390,390,390,100,1000]
        R2 = [510,150,130,120,22,33,27,24,22,33,114,27,22,51,51]
        for i in range(len(voltage)):
            cal_vol[i] = ((R1[i]+R2[i])*voltage[i])/R2[i]
        return(cal_vol)
    elif(board == 2):
        R1 = [18,122,6.2,20,33,20,33,5.1,22,22,12,16,20,18,15,15]
        R2 = [390,510,150,510,10,33,100,22,120,150,100,150,220,220,200,220]
        for i in range(len(voltage)):
            cal_vol[i] = ((R1[i]+R2[i])*voltage[i])/R2[i]
        return(cal_vol)
    elif(board == 3):
        R1 = [12,22,27,20,18,22,6.2,20,33,20,33,5.1,22,22,12,16]
        R2 = [200,390,510,390,390,510,150,510,10,33,100,22,120,150,100,150]
        for i in range(len(voltage)):
            cal_vol[i] = ((R1[i]+R2[i])*voltage[i])/R2[i]
        return(cal_vol)
    elif(board == 4):
        R1 = [80,18,15,15,12,22,27,20,18,22,6.2,20,33,20,33,5.1]
        R2 = [220,220,200,220,200,390,510,390,390,510,150,510,10,33,100,22]
        for i in range(len(voltage)):
            cal_vol[i] = ((R1[i]+R2[i])*voltage[i])/R2[i]
        return(cal_vol)        
    elif(board == 5):
        R1 = [22,22,12,16,20,18,15,15,12,22,27,20,18,22,6.2,20]
        R2 = [120,150,100,150,220,220,200,220,200,390,510,390,390,510,150,510]
        for i in range(len(voltage)):
            cal_vol[i] = ((R1[i]+R2[i])*voltage[i])/R2[i]
        return(cal_vol)
        