#ifndef DATA_PROCESS_H_
#define DATA_PROCESS_H_

#define SAME_FRE 210  //采用频率设定为210khz

#if SAME_FRE == 210
#define  CYCLE_NUM 10
#define  BUF_SIZE1   420  // Sample1 buffer size
#define  BUF_SIZE2   350  // Sample2 buffer size
#define  BUF_SIZE3   300  // Sample3 buffer size
#define  LOWFILT_SIZE 37
#endif

// Global variable for this example
//3路待测信号采样序列（原始数据存放数组）
extern Uint16 array_index;
extern volatile unsigned char Sdata[BUF_SIZE2*2];


//3路互相关运算结果做低通线性卷积运算的结果存放数组
extern float DAL_OutPut1[BUF_SIZE1+LOWFILT_SIZE];
extern float DAL_OutPut2[BUF_SIZE2+LOWFILT_SIZE];
extern float DAL_OutPut3[BUF_SIZE3+LOWFILT_SIZE];


extern void LinearConvolution(unsigned int xn,unsigned int hn,float *x,float *h,float *y);
extern void DAL_Process(float * Channel_Date,unsigned int Buf_size,float * Low_filter,float * DAL_OutPut );
extern void Data_Trans(float * Trans_data,Uint16 Buf_size,char * Trans_result);
extern float Single_Amplitude(float * DAL_OutPut,Uint16 Buf_size );
extern float Moisture_FITcalcu(float* MeasureDal,Uint16 Buf_size1,float* Refer1Dal,Uint16 Buf_size2,float* Refer2Dal,Uint16 Buf_size3,char FIT_Mode);

#endif /*DATA_PROCESS_H_*/
