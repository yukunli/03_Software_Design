#ifndef STD_INIT_H_
#define STD_INIT_H_

#include "ConstData_Table.h"
#define  GLOBAL_Q  16
#include "IQmathLib.h"
#define UINT8 unsigned char
#define UINT16 unsigned int
#define STATUS_SUCCESS True
#define STATUS_FAIL False

#define SAMP_COUNT_MAX  300

#define SAME_FRE 120  //����Ƶ���趨Ϊ120khz


#define  CYCLE_NUM 10	  //һ�β���CYCLE_NUM �����ڵ�����
#define  BUF_SIZE1   300  // Sample1 buffer size
#define  BUF_SIZE2   200  // Sample2 buffer size
#define  BUF_SIZE3   150  // Sample3 buffer size


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
	float SamValue1[SAMP_COUNT_MAX];
	float SamValue2[SAMP_COUNT_MAX];
	float SamValue3[SAMP_COUNT_MAX];
	float SamValue4[SAMP_COUNT_MAX];
}STRSampleValue;

//3·���������������ͨ���Ծ������Ľ���������
typedef struct 
{
	_iq24 DAL_OutPut1[BUF_SIZE1+LOWFILT_SIZE-1];
    _iq24 DAL_OutPut2[BUF_SIZE2+LOWFILT_SIZE-1];
	_iq24 DAL_OutPut3[BUF_SIZE3+LOWFILT_SIZE-1];
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
