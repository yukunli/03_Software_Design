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
myfont = matplotlib.font_manager.FontProperties(fname='c:\\windows\\fonts\\fzshjw_0.ttf')
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
    A = 1        #信号的幅值（mv）
    fs=Fs           #采样频率 hz
    
    N = Buf_size    #采样点数
    xx = []  
    n = [2*math.pi*f*t/fs for t in range(N)]  
    x = [A*math.sin(i) for i in n]
    print"原始信号x[]：\n"
    drawpicture(x,N)
    x1 = [50*math.sin(i*10)-30 for i in n]
    x11= [random.gauss(0,0.2) for i in range(N)]
    #另一路正弦信号
    n2 = [2*math.pi*fz1*t/fs for t in range(N)]  
    x2 = [500*math.sin(i) for i in n2]
    #另一路正弦信号
    n3 = [2*math.pi*fz2*t/fs for t in range(N)]  
    x3 = [300*math.sin(i) for i in n3]
    drawpicture(x1,N)
    for i in range(len(x)):
        xx.append(x[i] + x11[i])   ##+ x2[i]+ x3[i]
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

#####################################Output 计算了从61->1
    LL = m   #此时，m 为yn-hn, 即419
    print 'LL='+str(LL)
    for j in range(1,xn-1):
        Output[LL] +=  h[0]*Input[j]
        LL -=1
    Output[LL] += Input[0]*h[0]
 
    drawpicture(Output)
    return Output

    
def SinCosTab(SincosFre,buf_size):
    global Fs
    cycle_point = Fs/SincosFre   #获得一个周期的信号采样点，采用频率为Fs
    
    for i in range(0,cycle_point):
            
        theta = i* 6.283185/cycle_point   
        sinwave.append(math.sin(theta)+0.0)
        coswave.append(math.cos(theta)+0.0)
        
    for i in range(buf_size):
        longsinwave.append(sinwave[(i)%(cycle_point)])
        longcoswave.append(coswave[(i)%(cycle_point)])
            

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

	
if __name__ == '__main__' :
	
	
        global Frehz
        global Buf_size
        global fz1
        global fz2
        global Fs
        sumnum = 0
        Buf_size = 200
        Frehz = 6000
        fz1 = 4
        fz2 = 1
        Fs = 120000
        initial_value = 0
        Channel_Date = [ initial_value for i in range(Buf_size)]
        Cross_OutPut = [ initial_value for i in range(Buf_size)]
        SampleBuffer1 = [ initial_value for i in range(Buf_size)]
        SampleBuffer2 = [ initial_value for i in range(Buf_size)]
    
##------------------------------
        OccureDate()
##------------------------------    
##        read_singledata('sample2')
##------------------------------
        drawsamplevalue(datalist)
        DalProcess(Buf_size,datalist)
##	print "long sinwave: \n"
##	drawpicture(longsinwave)
##	print "longcoswave: \n"
##	drawpicture(longcoswave)	
        drawCross_OutPut()
        DAL_OutPut = LinearConvolution(Cross_OutPut,Filter_Size,Filter,DAL_OutPut)
        for i in range(100,len(DAL_OutPut)-100):
                sumnum += DAL_OutPut[i]
        print sumnum/(len(DAL_OutPut)-200)

        



















	
	
	
