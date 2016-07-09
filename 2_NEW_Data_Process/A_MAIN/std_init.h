#ifndef STD_INIT_H_
#define STD_INIT_H_


#define UINT8 unsigned char
#define UINT16 unsigned int
#define STATUS_SUCCESS True
#define STATUS_FAIL False

#define SAMP_COUNT_MAX  420

#define SAME_FRE 210  //采用频率设定为210khz

#if SAME_FRE == 210
#define  CYCLE_NUM 10	  //一次操作CYCLE_NUM 个周期的数据
#define  BUF_SIZE1   420  // Sample1 buffer size
#define  BUF_SIZE2   350  // Sample2 buffer size
#define  BUF_SIZE3   300  // Sample3 buffer size
#define  LOWFILT_SIZE 37
#endif

typedef enum {True,False} identi_bool;

typedef struct STRSampleTable
{
	UINT16 SamTable1[SAMP_COUNT_MAX];
	UINT16 SamTable2[SAMP_COUNT_MAX];
	UINT16 SamTable3[SAMP_COUNT_MAX];
	UINT16 SamTable4[SAMP_COUNT_MAX];
}STRSampleTable;

typedef struct STRSampleValue
{
	float SamValue1[SAMP_COUNT_MAX];
	float SamValue2[SAMP_COUNT_MAX];
	float SamValue3[SAMP_COUNT_MAX];
	float SamValue4[SAMP_COUNT_MAX];
}STRSampleValue;

//3路互相关运算结果做低通线性卷积运算的结果存放数组
typedef struct 
{
	float DAL_OutPut1[BUF_SIZE1+LOWFILT_SIZE];
    float DAL_OutPut2[BUF_SIZE2+LOWFILT_SIZE];
	float DAL_OutPut3[BUF_SIZE3+LOWFILT_SIZE];
}STRDalOutPut;


typedef struct
{
	float Water_b;  //截距参数
	float Water_k;	//斜率参数
	float PID_Kp;	//pid的kp参数
	float PID_Ki;	//pid的ki参数
	float PID_Kd;	//pid的kd参数
}Water_Param;
typedef struct
{
	float WaterValue;	//物料水分值
	float SoonWaterValue;	//瞬时水分值
	float temperature;	//温度
}Water_Value;

#endif /*STD_INIT_H_*/
