#ifndef DATA_PROCESS_H_
#define DATA_PROCESS_H_

extern float Calcu_AMP(float * Samplelist,Uint16 Buf_size);
extern float sortandaverage(float * valuelist);

extern void Data_Trans(float * Trans_data,Uint16 Buf_size,char * Trans_result);
extern float Moisture_FITcalcu(float* MeasureDal,Uint16 Buf_size1,float* Refer1Dal,Uint16 Buf_size2,float* Refer2Dal,Uint16 Buf_size3,char FIT_Mode);

#endif /*DATA_PROCESS_H_*/
