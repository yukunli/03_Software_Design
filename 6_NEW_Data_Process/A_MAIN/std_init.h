#ifndef STD_INIT_H_
#define STD_INIT_H_

#include "ConstData_Table.h"
#define UINT8 unsigned char
#define UINT16 unsigned int
#define STATUS_SUCCESS True
#define STATUS_FAIL False

#define SAMP_COUNT_MAX  421

#define SAME_FRE 156250  //采用频率设定为156.25khz


#define  CYCLE_NUM   10	  //一次操作CYCLE_NUM 个周期的数据

#define  BUF_SIZE1   420  // Sample1 buffer size
#define  BUF_SIZE2   350  // Sample2 buffer size
#define  BUF_SIZE3   300  // Sample3 buffer size
#define  BUF_SIZE4   200  // Sample3 buffer size

typedef enum {True,False} identi_bool;

typedef struct STRSampleTable
{
	int SamTable1[SAMP_COUNT_MAX];
	int SamTable2[SAMP_COUNT_MAX];
	int SamTable3[SAMP_COUNT_MAX];
	int SamTable4[SAMP_COUNT_MAX];
}STRSampleTable;

typedef struct STRSampleValue
{
	float SamValue1[BUF_SIZE1];
	float SamValue2[BUF_SIZE2];
	float SamValue3[BUF_SIZE3];
	float SamValue4[BUF_SIZE4];
}STRSampleValue;


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

typedef struct
{
	float L17Value;
	float L19Value;
	float L22Value;
	float temperature;
}LabView_Data;
#endif /*STD_INIT_H_*/
