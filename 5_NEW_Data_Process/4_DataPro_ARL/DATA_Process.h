#ifndef DATA_PROCESS_H_
#define DATA_PROCESS_H_
extern void SINCOS_TAB(float *Sin_tab,float *Cos_tab,const unsigned int cycle_point);
extern void LinearConvolution(const unsigned int buf_size,const unsigned int hn,float *x,const float *h,float *y);
extern void DAL_Process(float *Channel_Date, const unsigned int Buf_size,const unsigned int Cy_Point,const float*sinwave,const float*coswave, float *Cross_OutPut);
extern void Data_Trans(float * Trans_data,Uint16 Buf_size,char * Trans_result);
extern float Single_AmpValue(float * DAL_OutPut,const Uint16 count_size );
extern float Moisture_FITcalcu(float* MeasureDal,Uint16 Buf_size1,float* Refer1Dal,Uint16 Buf_size2,float* Refer2Dal,Uint16 Buf_size3,char FIT_Mode);

#endif /*DATA_PROCESS_H_*/
