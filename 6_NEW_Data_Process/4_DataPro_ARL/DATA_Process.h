#ifndef DATA_PROCESS_H_
#define DATA_PROCESS_H_

#include "std_init.h"

extern void LinearConvolution(const unsigned int buf_size,const unsigned int hn,float *x,const float *h,float *y);
extern float Calcu_AMP(float *Samplelist,Uint16 Buf_size,const Uint16 Filer_size);
float sortandaverage(float * valuelist,const unsigned char longnum);
extern void FIR_Filter(const unsigned int xn,const float*x, const unsigned int hn, const float*h, float * y);
 
extern float Moisture_FITcalcu(float Tdata, Fit_Param* Param, const char FIT_Mode);
extern float Correct_Moisture(float measuvalue, float corr_k,float corr_b);
#endif /*DATA_PROCESS_H_*/
