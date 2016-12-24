### -*- coding: utf-8 -*-  
import DLIA_simulink as ds
import re
import os
import string
from scipy import signal  
import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib
import random
#设置字体文件，否则不能显示中文  
myfont = matplotlib.font_manager.FontProperties(fname='c:\\windows\\fonts\\simsun.ttc') #,fontproperties=myfont

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
global Filter_Size
Filter_Size = 62

#正交锁相放大器
global sinwave
global coswave
global longsinwave
global longcoswave
sinwave = []
coswave = []
longsinwave = []
longcoswave = []
global Frehz
global Buf_size

global Filter_SampleBuffer1
Filter_SampleBuffer1 = []

global Filter_SampleBuffer2
Filter_SampleBuffer2 = []
global DAL_OutPut
DAL_OutPut = []

def drawpicture(listdate,bufsize = None):
	global Buf_size
	lenth2 = len(listdate)
	print "listdate is "+ str(lenth2)
	if bufsize == None:
		figure3 = plt.plot(range(0,lenth2), listdate, '--bo')
	else:
		figure3 = plt.plot(range(0,bufsize), listdate, '--bo')
	plt.ylabel(u'幅值/V',fontproperties=myfont,fontsize='13')
	plt.grid(True)
	plt.title('listdate')
	plt.show()
def SinCosTab(SincosFre,Fs,buf_size):
    """
    sincosFre: 参考序列的频率
    Fs : 参考序列采样的频率
    buf_size : 参考序列的长度
    """
    global sinwave
    global coswave
    global longsinwave
    global longcoswave
    cycle_point = Fs/SincosFre   #获得一个周期的信号采样点，采用频率为Fs
    del sinwave
    del coswave
    del longsinwave
    del longcoswave
    sinwave = []
    coswave = []
    longsinwave = []
    longcoswave = []
    for i in range(0,cycle_point):
        theta = i* 6.283185/cycle_point   
        sinwave.append(math.sin(theta))
        coswave.append(math.cos(theta))
        
    for i in range(buf_size):
        longsinwave.append(sinwave[(i)%(cycle_point)])
        longcoswave.append(coswave[(i)%(cycle_point)])
    
    
#数字低通滤波器        
def LinearConvolution(CrossDate,LOWFILT_SIZE,filter_xishu,Outputdata):
    
    Output = []  #输出序列
    h = []       #滤波器系数序列
    Input = []   #输入序列
    
    hn = LOWFILT_SIZE
    
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
            LL -= 1
        Output[LL] += Input[0]*h[i]   #Input[0]*h[]
        m -= 1 

    LL = m   #此时，m 为yn-hn, 即419
    for j in range(1,xn-1):
        Output[LL] +=  h[0]*Input[j]
        LL -=1
    Output[LL] += Input[0]*h[0]
 
    drawpicture(Output)
    return Output

def DalProcess(bufsize,singledata =[]):

    global SampleBuffer2
    global SampleBuffer1
    global Buf_size
    global Frehz
    
    Channel_Date = singledata
    
    for k in range(0,Buf_size):
        temp1 = 0;
        temp2 = 0;
        for j in range(0,Buf_size-k):
            temp1 += Channel_Date[j]*longsinwave[j+k]
            temp2 += Channel_Date[j]*longcoswave[j+k]
        SampleBuffer1[k] = temp1/(Buf_size-k)
        SampleBuffer2[k] = temp2/(Buf_size-k)

    print "SampleBuffer1 after dal\N"
##    drawpicture(SampleBuffer1)
    print "SampleBuffer2 after dal\N"
##    drawpicture(SampleBuffer2)
    
    print "ditonglvbo SampleBuffer1:\n"
    for kk in range(0,Buf_size):
        
        temp1 = SampleBuffer1[kk]
        temp2 = SampleBuffer2[kk]
        Cross_OutPut[kk]=2*math.sqrt((temp1*temp1)+(temp2*temp2))

if __name__ == '__main__' :

    global Buf_size
    initial_value = 0
    
    

    #产生5kHz,幅值0,001v, 采用频率为100Khz,数据长度为400，均值为0，方差为0.001信号，
    single_f = 5000
    single_A = 0.1
    single_fs = 100000
    single_dataleth = 800
    noise_j = 0
    noise_f = math.sqrt(0.001)

    Buf_size = single_dataleth
    #数字锁相运算中间变量
    Channel_Date = [ initial_value for i in range(Buf_size)]
    Cross_OutPut = [ initial_value for i in range(Buf_size)]
        
    SampleBuffer1 = [ initial_value for i in range(Buf_size)]
    SampleBuffer2 = [ initial_value for i in range(Buf_size)]
    
    srcdata = ds.OccureDate(single_f,single_A,single_fs,single_dataleth,noise_j,noise_f)

    SinCosTab(single_f,single_fs,single_dataleth)
    print 'dlia resule'
    DalProcess(single_dataleth,srcdata)
    
    DAL_OutPut = LinearConvolution(Cross_OutPut,Filter_Size,Filter,DAL_OutPut)

    ##DAL_OutPut的绘制
    #取样时间数组点（0-1000ms）
    sumnum = 0
    t = np.arange(0, 1.0, 1.0/single_fs)
    longth = len(DAL_OutPut)
    for i in range(longth):
        t[i] = t[i]*1000
        
    plt.plot(t[:longth], DAL_OutPut)
    plt.ylabel(u'幅值/V',fontproperties=myfont,fontsize='13')
    plt.xlabel(u"                                                                                时间/ms",fontproperties=myfont,fontsize='13')
    plt.grid(True)
    plt.show()
##    print DAL_OutPut
    for i in range(62,longth-62):
        sumnum += DAL_OutPut[i]
    junzhi = sumnum/(longth-124)
    print junzhi
    print (0.1-junzhi)/0.1*100
    
##    #正交分量，同相分量频谱绘制
##    plt.subplot(212)
##    scrdatalist = SampleBuffer1
##    N = len(SampleBuffer1)
##    
##    xf = np.fft.fft(SampleBuffer1)
##    xf_abs = np.fft.fftshift(abs(xf))
##        
##    axis_xf = np.linspace(-N/2,N/2-1,num=N)
##    #____________________
##    plt.xlabel(u"                                                                                频率/Hz",fontproperties=myfont,fontsize='13')
##    plt.ylabel(u"幅值/dB",fontproperties=myfont,fontsize='13')
##    
##    plt.title(u"同相相关的信号频谱",fontproperties=myfont,fontsize='14')
##    plt.plot(axis_xf,xf_abs)
##    
##
##    plt.subplot(211) 
##    xf2 = np.fft.fft(SampleBuffer2)
##    xf_abs2 = np.fft.fftshift(abs(xf2))
##        
##    axis_xf2 = np.linspace(-N/2,N/2-1,num=N)
##    plt.plot(axis_xf2,xf_abs2)
##    plt.xlabel(u"                                                                                时间/ms",fontproperties=myfont,fontsize='13')
##    plt.ylabel(u"幅值/dB",fontproperties=myfont,fontsize='13')
##    plt.title(u"正交相关的信号频谱",fontproperties=myfont,fontsize='14')
##    plt.show()

    
