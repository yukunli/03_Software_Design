#ifndef STD_INIT_H_
#define STD_INIT_H_

#include "ConstData_Table.h"
#include <math.h>
//#include "C28x_FPU_FastRTS.h"
#define UINT8 unsigned char
#define UINT16 unsigned int
#define STATUS_SUCCESS True
#define STATUS_FAIL False

#define SAMP_COUNT_MAX  421

#define SAME_FRE 120  //����Ƶ���趨Ϊ120khz

#define  BUF_SIZE1   420  // Sample1 buffer size
#define  BUF_SIZE2   300  // Sample2 buffer size
#define  BUF_SIZE3   330  // Sample3 buffer size
#define  BUF_SIZE4   100  // Sample3 buffer size

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

//3·���������������ͨ���Ծ������Ľ���������
typedef struct 
{
	float DAL_OutPut1[2*BUF_SIZE1+LOWFILT_SIZE-1];
    float DAL_OutPut2[2*BUF_SIZE2+LOWFILT_SIZE-1];
	float DAL_OutPut3[2*BUF_SIZE3+LOWFILT_SIZE-1];
}STRDalOutPut;


typedef struct
{
	float Water_b;  //�ؾ����
	float Water_k;	//б�ʲ���
	float PID_Kp;	//pid��kp����
	float PID_Ki;	//pid��ki����
	float PID_Kd;	//pid��kd����
}Water_Param;

typedef struct
{
	float WaterValue;	//����ˮ��ֵ
	float SoonWaterValue;	//˲ʱˮ��ֵ
	float temperature;	//�¶�
}Water_Value;

typedef struct
{
	float L17Value;
	float L19Value;
	float L22Value;
	float temperature;
}LabView_Data;
#endif /*STD_INIT_H_*/
