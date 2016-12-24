
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as pl
import matplotlib
import math
import random


##import pylab as pl
#设置字体文件，否则不能显示中文  
myfont = matplotlib.font_manager.FontProperties(fname='c:\\windows\\fonts\\simsun.ttc') #,fontproperties=myfont
#数字信号的频率
Frs = 5000
#信号的幅值
A = 0.1
#数字信号的采样频率 N=20
sampling_rate = 100000
#FFT的长度，即数据长度
fft_size = 400

#噪声：均值为 noise_mu，标准差为noise_sigma
noise_mu = 0
noise_sigma = 0.001

#取样时间数组点（0-1000ms）
t = np.arange(0, 1.0, 1.0/sampling_rate)
print t
xx = []
#计算出波形数据,
x = np.sin(2*np.pi*Frs*t)
##叠加随机噪声，均值为noise_mu，标准差为noise_sigma
x1 = [random.gauss(noise_mu,noise_sigma) for i in range(len(t))]
for i in range(len(x)):
    xx.append(x[i]*A + x1[i])
    t[i] = t[i]*1000

xs = xx[:fft_size]
print len(xs)

xf = np.fft.rfft(xs)/fft_size
freqs = np.linspace(0, sampling_rate/2, fft_size/2+1)
xfp = 20*np.log10(np.clip(np.abs(xf), 1e-20, 1e100))

pl.figure(figsize=(8,4))

pl.subplot(211)
pl.plot(t[:fft_size], xx[:fft_size])
pl.xlabel(u"时间/ms",fontproperties=myfont)
pl.ylabel(u"幅值/V",fontproperties=myfont)
#pl.title(u"5kHz的波形和频谱",fontproperties=myfont)

pl.subplot(212)
pl.plot(freqs, xfp)
pl.xlabel(u"频率/Hz",fontproperties=myfont)
pl.ylabel(u"幅值/dB",fontproperties=myfont)
pl.subplots_adjust(hspace=0.4)
pl.show()
