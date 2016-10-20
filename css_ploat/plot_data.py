

import re
import os
import string
import matplotlib.pyplot as plt

global sinwave
global coswave
global datalist
sinwave = []
coswave = []
datalist=[]


def ploat_data(filestr):
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
                        if(inum == 460):
                                break                
                        
        ##print datalist
        lenth = len(datalist)
        print lenth
        print datalist[lenth-1]
        figure1 = plt.plot(range(0,lenth), datalist, '--bo')
        plt.ylabel('value(mv)')
        plt.show()
        del datalist

ploat_data('sample1')   #
ploat_data('sample2') #
ploat_data('sample3') #
ploat_data('dout1')
ploat_data('dout2')
ploat_data('dout3')

