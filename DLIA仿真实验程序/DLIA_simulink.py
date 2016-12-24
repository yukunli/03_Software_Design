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

global datalist
datalist=[]

global inum
inum = 0


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
global t

#设置字体文件，否则不能显示中文  
myfont = matplotlib.font_manager.FontProperties(fname='c:\\windows\\fonts\\simsun.ttc') #,fontproperties=myfont

def drawpicture(srcdate,ydata):
    """
    srcdata : 做图的数据
    ylabel : Y坐标的名称
    """
    lenth = len(srcdate)
    print "srcdate is "+ str(lenth)
    
    figure1 = plt.plot(ydata, srcdate) #, '--bo'
    plt.xlabel(u"时间/ms",fontproperties=myfont)
    plt.ylabel(u"幅值/V",fontproperties=myfont)
    #plt.title(title,fontproperties=myfont)
    plt.show()
        
def OccureDate(f,A,fs,N,noise_mu,noise_sigma):
    """
    f ：信号频率
    A : 信号的幅值（V）
    fs : 信号采样频率
    N: 采样的数据长度
    noise_mu: 高斯噪声的均值
    noise_sigma: 高斯噪声的标准差
        
    """
    global datalist
    global t
    xx = []

    #取样时间数组点（0-1000ms）
    t = np.arange(0, 1.0, 1.0/fs)
    
    ##频率为f的正弦信号
    x = np.sin(2*np.pi*f*t)
    x = x[:N]  
    
    ##叠加随机噪声，均值为 noise_mu，标准差为noise_sigma
    x1 = [random.gauss(noise_mu,noise_sigma) for i in range(N)]
    
    for i in range(N):
        xx.append(x[i]*A+x1[i] )
        t[i] = t[i]*1000
        
    drawpicture(xx,t[:N])
    return xx

      
def drawCross_OutPut():
    lenth2 = len(Cross_OutPut)
    print "lenth2 is "+ str(lenth2)
    #Cross_OutPut[300] = 0
    figure2 = plt.plot(range(0,lenth2), Cross_OutPut) #, '--bo'
    plt.ylabel('value(v)')
    plt.title('Cross_OutPut')
    plt.show()
    


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
            #print LL    #LL 第一次从480 -》62，第二次从479-》61，最后一次从420-》
            LL -= 1
        Output[LL] += Input[0]*h[i]   #Input[0]*h[]
##        print LL
        m -= 1 

    LL = m   #此时，m 为yn-hn, 即419
    print 'LL='+str(LL)
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
    
    SinCosTab(Frehz,Buf_size)
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
    drawpicture(SampleBuffer1)
    print "SampleBuffer2 after dal\N"
    drawpicture(SampleBuffer2)
    
    print "ditonglvbo SampleBuffer1:\n"
    for kk in range(0,Buf_size):
        
        temp1 = SampleBuffer1[kk]
        temp2 = SampleBuffer2[kk]
        Cross_OutPut[kk]=2*math.sqrt((temp1*temp1)+(temp2*temp2))

def drawfft(scrdatalist):
    """
    """
    #频谱绘制
    N = len(scrdatalist)
    print N
    xf = np.fft.rfft(scrdatalist)/N
    print len(xf)
    xf_abs = 20*np.log10(np.clip(np.abs(xf), 1e-20, 1e100))      #y轴数据
    print len(xf_abs)
    axis_xf = np.linspace(0,50000,num=N/2+1)    #x轴数据
    print len(axis_xf)   
    plt.title(u'正弦频谱图',fontproperties=myfont)
    plt.xlabel(u"频率/Hz",fontproperties=myfont)
    plt.ylabel(u"幅值/dB",fontproperties=myfont)
    plt.plot(axis_xf,xf_abs)
    plt.show()
    
    
if __name__ == '__main__' :
    
    
    global Frehz
    global Buf_size
    global Fs
    global t
    sumnum = 0
    initial_value = 0
    Buf_size = 400
    Frehz = 100000
    #数字锁相运算中间变量
    Channel_Date = [ initial_value for i in range(Buf_size)]
    Cross_OutPut = [ initial_value for i in range(Buf_size)]
        
    SampleBuffer1 = [ initial_value for i in range(Buf_size)]
    SampleBuffer2 = [ initial_value for i in range(Buf_size)]
    
    #产生5kHz,幅值0,001v, 采用频率为100Khz,数据长度为400，均值为0，方差为0.001信号，
    single_f = 5000
    single_A = 0.1
    single_fs = 100000
    single_dataleth = 400
    noise_j = 0
    noise_f = math.sqrt(0.001)
    
    srcdata = OccureDate(single_f,single_A,single_fs,single_dataleth,noise_j,noise_f)
    #drawfft(srcdata)
 



    #频谱绘制
    plt.subplot(212)
    scrdatalist = srcdata
    N = len(scrdatalist)
    print N
##    xf = np.fft.rfft(scrdatalist)/N
##    print len(xf)
##    xf_abs = 20*np.log10(np.clip(np.abs(xf), 1e-20, 1e100))      #y轴数据
##    print len(xf_abs)
##    axis_xf = np.linspace(0,single_fs/2,num=N/2+1)    #x轴数据
##    print len(axis_xf)   
    #plt.title(u'正弦频谱图',fontproperties=myfont)
    #_______________________
    xf = np.fft.fft(scrdatalist)
    xf_abs = np.fft.fftshift(abs(xf))
        
    axis_xf = np.linspace(-N/2,N/2-1,num=N)
    #____________________
    plt.xlabel(u"                                                                                频率/Hz",fontproperties=myfont,fontsize='13')
    plt.ylabel(u"幅值/dB",fontproperties=myfont,fontsize='13')
    
    plt.title(u"待测信号频谱图",fontproperties=myfont,fontsize='14')
    plt.plot(axis_xf,xf_abs)
    

    plt.subplot(211) 
    figure1 = plt.plot(t[:N], scrdatalist) #, '--bo'
    plt.xlabel(u"                                                                                时间/ms",fontproperties=myfont,fontsize='13')
    plt.ylabel(u"幅值/V",fontproperties=myfont,fontsize='13')
    plt.title(u"待测信号时域图",fontproperties=myfont,fontsize='14')
    plt.show()

  

















    
    
    
