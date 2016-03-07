#ifndef DATA_PROCESS_H_
#define DATA_PROCESS_H_

#define  BUF_SIZE1   390  // Sample1 buffer size
#define  BUF_SIZE2   432  // Sample2 buffer size
#define  BUF_SIZE3   368  // Sample 3buffer size
#define  LOWFILT_SIZE 36

// Global variable for this example
//3路待测信号采样序列（原始数据存放数组）
extern float SampleValue1[450];
extern float SampleValue2[450];
extern float SampleValue3[450];
extern Uint16 array_index;
extern volatile unsigned char Sdata[BUF_SIZE2*2];


//3路互相关运算结果做低通线性卷积运算的结果存放数组
extern float DAL_OutPut1[BUF_SIZE1+LOWFILT_SIZE];
extern float DAL_OutPut2[BUF_SIZE2+LOWFILT_SIZE];
extern float DAL_OutPut3[BUF_SIZE3+LOWFILT_SIZE];
//3路低通线性卷积运算的结果平均值
extern float Ever_VolOut1[20];
extern float Ever_VolOut2[20];
extern float Ever_VolOut3[20];

extern void LinearConvolution(unsigned int xn,unsigned int hn,float *x,float *h,float *y);
extern void DAL_Process(float * Channel_Date,unsigned int Buf_size,float * stand_sinwave,float* stand_coswave,float * Low_filter,float * DAL_OutPut );
extern void Data_Trans(float * Trans_data,Uint16 Buf_size,char * Trans_result);
extern float Single_Result(float * DAL_OutPut,Uint16 Buf_size );
#endif /*DATA_PROCESS_H_*/
