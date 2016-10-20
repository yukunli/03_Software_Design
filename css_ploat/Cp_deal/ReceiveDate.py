### -*- coding: utf-8 -*-  

import serial
import numpy as np
import time

from GetData import get_data
import Filter
import ProcessVPP
import matplotlib.pyplot as plt
import math
import matplotlib

gesture = 'Sample'
Samp1Value = []
Samp2Value = []
Samp3Value = []

Filt1Value = []
Filt2Value = []
Filt3Value = []

ser = serial.Serial('COM10',256000)

print 'ok!'

##Data Frame : oxfe 0xfe 0xaa

while(1):
    try:
        line = ser.readline()
    except:
        ser.close()
        print 'Something is wrong!'
        exit()
    print len(line)
    
    ##读取数据
    if(len(line)!= 0):
        print 'the value num is '+ str(len(line)/6)
        i = 0
        while i < len(line):
            Samp1,Samp2,Samp3 = get_data(line[i:i+6])
            i += 6
            Samp1Value.append(Samp1)
            Samp2Value.append(Samp2)
            Samp3Value.append(Samp3)
            
        print Samp3Value   
        a = np.array(Samp1Value)
        string = gesture+str(1)+".txt"
        np.savetxt(string,a)
        print"Sample 1 saved ! the lenth is " +str(len(Samp1Value))

        a = np.array(Samp2Value)
        string = gesture+str(2)+".txt"
        np.savetxt(string,a)
        print"Sample 2 saved ! the lenth is " +str(len(Samp2Value))

        a = np.array(Samp3Value)
        string = gesture+str(3)+".txt"
        np.savetxt(string,a)
        print"Sample 3 saved ! the lenth is " +str(len(Samp3Value))

        ##经过低通或高通滤波器
        Filt1Value = np.convolve(Samp1Value,Filter)
        Filt2Value = np.convolve(Samp2Value,Filter)
        Filt3Value = np.convolve(Samp3Value,Filter)

        ##画波形曲线
        Filter.drawpicture(Samp1Value,Filt1Value)
        Filter.drawpicture(Samp2Value,Filt2Value)
        Filter.drawpicture(Samp3Value,Filt3Value)

        ##求幅值
        ProcessVPP.Dal_vpp(Filt1Value)
        ProcessVPP.Dal_vpp(Filt2Value)
        ProcessVPP.Dal_vpp(Filt3Value)
        
        
    if line == 'FF':
        ser.close()
        print 'finish~'
