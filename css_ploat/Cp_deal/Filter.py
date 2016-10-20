### -*- coding: utf-8 -*-  
  
import re
import os
import string
from scipy import signal  
import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

Filter = [
      0.002829352627, 0.003547752276, 0.004316083156, 0.005131774116, 0.005991730373,
   0.006892347243, 0.007829532959,  0.00879873056, 0.009794953279,  0.01081281994,
    0.01184659451,  0.01289023552,  0.01393744349,  0.01498171408,  0.01601639949,
    0.01703476161,  0.01803003438,  0.01899549179,  0.01992449909,  0.02081058547,
    0.02164749801,  0.02242926694,  0.02315025777,  0.02380523272,  0.02438939176,
    0.02489842847,  0.02532857284,   0.0256766174,   0.0259399619,  0.02611663193,
    0.02620530128,  0.02620530128,  0.02611663193,   0.0259399619,   0.0256766174,
    0.02532857284,  0.02489842847,  0.02438939176,  0.02380523272,  0.02315025777,
    0.02242926694,  0.02164749801,  0.02081058547,  0.01992449909,  0.01899549179,
    0.01803003438,  0.01703476161,  0.01601639949,  0.01498171408,  0.01393744349,
    0.01289023552,  0.01184659451,  0.01081281994, 0.009794953279,  0.00879873056,
   0.007829532959, 0.006892347243, 0.005991730373, 0.005131774116, 0.004316083156,
   0.003547752276, 0.002829352627]

#画曲线

def drawpicture(listdate1,listdate2):
    
    lenth1 = len(listdate1)
    plt.subplot(211)
    plt.plot(range(0,lenth1), listdate1, '--bo')
    plt.ylabel('value(V)')
    plt.title('listdate1')
    
    lenth2 = len(listdate2)
    plt.subplot(212)
    plt.plot(range(0,lenth2), listdate2, '--bo')
    plt.ylabel('value(V)')
    plt.title('listdate2')
    plt.show()
    
#数字低通滤波器		
def LinearConvolution(CrossDate,filter_xishu):
    
    Output = []  #输出序列
    h = []       #滤波器系数序列
    Input = []   #输入序列
    
    h = filter_xishu
    hn = len(filter_xishu)
    Input = CrossDate
    xn = len(CrossDate)
    yn = xn+hn-1    #以xn = 420, hn = 62为例，yn = 481
    m = 0

    Output = [initial_value for i in range(yn)] #初始化y
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
