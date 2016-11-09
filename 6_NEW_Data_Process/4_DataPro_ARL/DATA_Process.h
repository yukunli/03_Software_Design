#ifndef DATA_PROCESS_H_
#define DATA_PROCESS_H_


extern void LinearConvolution(const unsigned int buf_size,const unsigned int hn,float *x,const float *h,float *y);
extern float Calcu_AMP(float *Samplelist,Uint16 Buf_size,const Uint16 Filer_size);
extern float sortandaverage(float * valuelist,const unsigned char longnum);
extern void FIR_Filter(const unsigned int xn,const float*x, const unsigned int hn, const float*h, float * y);
 
extern void Data_Trans(float * Trans_data,Uint16 Buf_size,char * Trans_result);
extern float Moisture_FITcalcu(float* MeasureDal,Uint16 Buf_size1,float* Refer1Dal,Uint16 Buf_size2,float* Refer2Dal,Uint16 Buf_size3,char FIT_Mode);

#endif /*DATA_PROCESS_H_*/
