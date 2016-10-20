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

Filter1 = [-0.001638296875, 0.001976465574, 0.002134647453, 0.002753725043, 0.003676692024,
   0.004842206836, 0.006222689059, 0.007803681307, 0.009575296193,  0.01152345072,
    0.01362994872,  0.01586939767,  0.01821359247,  0.02062819339,   0.0230763685,
    0.02551575191,  0.02790359221,  0.03019426391,  0.03234416991,   0.0343089737,
    0.03604891896,  0.03752631322,   0.0387105532,  0.03957502544,  0.04010182992,
     0.0402783975,  0.04010182992,  0.03957502544,   0.0387105532,  0.03752631322,
    0.03604891896,   0.0343089737,  0.03234416991,  0.03019426391,  0.02790359221,
    0.02551575191,   0.0230763685,  0.02062819339,  0.01821359247,  0.01586939767,
    0.01362994872,  0.01152345072, 0.009575296193, 0.007803681307, 0.006222689059,
   0.004842206836, 0.003676692024, 0.002753725043, 0.002134647453, 0.001976465574,
  -0.001638296875]

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


#设置字体文件，否则不能显示中文  
myfont = matplotlib.font_manager.FontProperties(fname='c:\\windows\\fonts\\simsun.ttc')  #fontproperties=myfont

def drawpicture(listdate,bufsize = None):
	global Buf_size
	lenth2 = len(listdate)
	print "listdate is "+ str(lenth2)
	if bufsize == None:
		figure3 = plt.plot(range(0,lenth2), listdate, '--bo')
	else:
		figure3 = plt.plot(range(0,bufsize), listdate, '--bo')
	plt.ylabel('value(mv)')
	plt.title('listdate')
	plt.show()

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
##                        if(inum == 460):
##                                break                            
        ##print datalist
        lenth = len(datalist)
        print lenth
        print datalist[lenth-1]
        
def OccureDate():

    global datalist
    global Buf_size
    global Frehz
    global fz1
    global fz2
    global Fs
    f = Frehz        #信号频率Hz
    A = 2000         #信号的幅值（mv）
    fs=Fs           #采样频率 hz
    
    N = Buf_size    #采样点数
    xx = []  
    n = [2*math.pi*f*t/fs for t in range(N)]  
    x = [A*math.sin(i-0.1) for i in n]
    print"原始信号x[]：\n"
    drawpicture(x,N)
    x1 = [500*math.sin(i*10)-30 for i in n]
    
    #另一路正弦信号
    n2 = [2*math.pi*fz1*t/fs for t in range(N)]  
    x2 = [500*math.sin(i) for i in n2]
##    #另一路正弦信号
##    n3 = [2*math.pi*fz2*t/fs for t in range(N)]  
##    x3 = [300*math.sin(i) for i in n3]
##    drawpicture(x1,N)
    for i in range(len(x)):
        xx.append(x[i]+ x2[i])   ##+ x2[i]+ x3[i]
    print "加噪声后的待测信号xx[]:\n"
    datalist = xx


def drawsamplevalue(listdate):
    global Buf_size
    templist = []
    lenth2 = len(listdate)
    print "listdate is "+ str(lenth2)
    for i in range(0,Buf_size):
        templist.append(listdate[i])
    
    figure3 = plt.plot(range(0,Buf_size), templist, '--bo')
    
    plt.ylabel('value(v)')
    plt.title('listdate')
    plt.show()   
	
def drawCross_OutPut():
	lenth2 = len(Cross_OutPut)
	print "lenth2 is "+ str(lenth2)
	#Cross_OutPut[300] = 0
	figure2 = plt.plot(range(0,lenth2), Cross_OutPut, '--bo')
	plt.ylabel('value(v)')
	plt.title('Cross_OutPut')
	plt.show()
	
def Dal_vpp():
        global datalist
        MAXvalue = []
        MINvalue = []
        index = 0
        Winlist = [0,0,0,0,0]
        sumvalue2 = 0
        sumvalue1 = 0
        for i in range(len(datalist)-5):
                Winlist[0] = datalist[i]
                Winlist[1] = datalist[i+1]
                Winlist[2] = datalist[i+2]
                Winlist[3] = datalist[i+3]
                Winlist[4] = datalist[i+4]

                ##比较[2]是不是最大的
                if Winlist[2]> Winlist[0] and Winlist[2]> Winlist[1] and Winlist[2]> Winlist[3] and Winlist[2]> Winlist[4]:
                      MAXvalue.append(Winlist[2])
                elif Winlist[2]< Winlist[0] and Winlist[2]< Winlist[1] and Winlist[2]< Winlist[3] and Winlist[2]< Winlist[4]:
                        MINvalue.append(Winlist[2])
        print MAXvalue
        figure4 = plt.plot(range(0,len(MAXvalue)), MAXvalue, '--bo')
        plt.show()
        ##处理MAXvalue MINvalue，排序比较，去掉最大值和最小值
        MAXlen = len(MAXvalue)
        for k in range(MAXlen):
                for j in range(k+1,MAXlen):
                        if MAXvalue[k]< MAXvalue[j]:
                                tt = MAXvalue[j]
                                MAXvalue[j] = MAXvalue[k]
                                MAXvalue[k] = tt

        print MAXvalue
        for i in range(1,MAXlen-1):
                sumvalue1 += MAXvalue[i]
        print"MAXvalue: \n"
        Vtop = sumvalue1/(MAXlen-2)
        print Vtop
        print '\n'
        MINlen = len(MINvalue)
        for k in range(MINlen):
                for j in range(k+1,MINlen):
                        if MINvalue[k]< MINvalue[j]:
                                tt = MINvalue[j]
                                MINvalue[j] = MINvalue[k]
                                MINvalue[k] = tt
        print MINvalue
        for i in range(1,MINlen-1):
                sumvalue2 += MINvalue[i]
        print"MINvalue: \n"
        Vbottom = sumvalue2/(MINlen-2)
        print Vbottom
        print '\n'
        ##计算幅值
        print  (Vtop-Vbottom)/2
if __name__ == '__main__' :
	
	
        global Frehz
        global Buf_size
        global fz1
        global fz2
        global Fs
        sumnum = 0
        Buf_size = 300
        Frehz = 6000
        fz1 = 50000
        Fs = 210000
    
##------------------------------
##        OccureDate()
##------------------------------    
        read_singledata('sample3')
##------------------------------
        drawsamplevalue(datalist)
        #频谱绘制
        N = len(datalist)
        xf = np.fft.fft(datalist)
        xf_abs = np.fft.fftshift(abs(xf))
##        axis_xf = np.linspace(-N/2,N/2-1,num=N)
        axis_xf = np.linspace(0,N,num=N)
        plt.title(u'频率为5Hz的正弦频谱图',fontproperties=myfont)
        plt.plot(axis_xf,xf_abs)
        plt.axis('tight')
        plt.show()
        Dal_vpp()



















	
	
	
