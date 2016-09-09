#ifndef DATA_PROCESS_H_
#define DATA_PROCESS_H_
#include "std_init.h"
extern void LinearConvolution(const unsigned int buf_size,const unsigned int h_Size,_iq24 *x,const _iq24 *h,_iq24 *y);

extern void DAL_Process(float * Channel_Date,const unsigned int Buf_size,_iq24 *Cross_OutPutt );
extern void Data_Trans(float * Trans_data,Uint16 Buf_size,char * Trans_result);
extern float Single_AmpValue(_iq24 * DAL_OutPut,const Uint16 count_size );
extern float Moisture_FITcalcu(float* MeasureDal,Uint16 Buf_size1,float* Refer1Dal,Uint16 Buf_size2,float* Refer2Dal,Uint16 Buf_size3,char FIT_Mode);

#endif /*DATA_PROCESS_H_*/
