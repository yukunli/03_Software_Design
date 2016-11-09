### -*- coding: utf-8 -*-  
  
  
import re
import os
import string
from scipy import signal  
import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib
import random

import fdacoefs

datalist = []
c= []

def read_singledata(filestr):
        global datalist
        datalist=[]
        file_data = open('.\\'+filestr+'.txt','r')   ##sample_table3 sample_Value2  DAL_OutPut3
        lines = file_data.readlines()
        file_data.close()
        inum = 0
        for item in lines:

                pattern = re.match(r'.*\[.*\] = (-?\d.*)\n',item)
               
                if pattern:
                        inum += 1
                        datalist.append(string.atof(''.join(list(pattern.groups(1)))))

        lenth = len(datalist)
        print lenth
        print datalist[lenth-1]

def drawpicture(listdate1):
    lenth2 = len(listdate1)
    print "listdate is "+ str(lenth2)
	
    figure3 = plt.plot(range(0,lenth2), listdate1, '--bo')
    plt.ylabel('value(mv)')
    plt.title('listdate')
    plt.show()
#FIR数字低通滤波器设计    
def FIRFilter(coludata, filterxishu):
        temp = 0
        Output = []  #输出序列
        h = filterxishu       #滤波器系数序列
        Input = coludata   #输入序列
        hn = len(filterxishu)
        xn = len(coludata)
        yn = xn+hn-1
        print hn
        print yn
##        Output = [0 for i in range(yn)] #初始化y

        for k in range(xn,yn):
                Input.append(0)

        for i in range(hn-1,yn):
                for j in range(0,hn):
                        temp += h[j]*Input[i-j]
                        
                Output[yn -i] = temp
                temp = 0
        
        return Output[:xn]

#数字低通滤波器		
def LinearConvolution(ColuDate,filter_xishu):

    Output = []  #输出序列
    h = []       #滤波器系数序列
    Input = []   #输入序列
    
   
    h = filter_xishu
    hn = len(filter_xishu)
    Input = ColuDate
    xn = len(ColuDate)
    yn = xn+hn-1    #以xn = 420, hn = 62为例，yn = 481
    m = 0

    Output = [0 for i in range(yn)] #初始化y
    m = yn-1
    for i in range(1,hn):   # 1-> hn-1
        LL = m
        for j in range(1,xn):  # 1-> xn-1
            Output[LL] += h[i]* Input[j]  
            #print LL    #LL 第一次从480 -》62，第二次从479-》61，最后一次从420-》
            LL -= 1
        Output[LL] += Input[0]*h[i]   #Input[0]*h[]
##        print LL
        m -= 1 

#####################################Output 计算了从61->1
    LL = m   #此时，m 为yn-hn, 即419
    print 'LL='+str(LL)
    for j in range(1,xn-1):
        Output[LL] +=  h[0]*Input[j]
        LL -=1
    Output[LL] += Input[0]*h[0]
 
    return Output
##----------------------------------------------
read_singledata("s1")

drawpicture(datalist)

##c = np.convolve(fdacoefs.real32_T,datalist)
##c =LinearConvolution(datalist,fdacoefs.real32_T)
c = FIRFilter(datalist,fdacoefs.real32_T)
drawpicture(c)


