
/*
 created by li Danny
 Date:/ 2015/12/20
*/

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "stdlib.h"
#include "math.h"
#include "DATA_Process.h"
#include "ConstData_Table.h"
#include "std_init.h"
#include "hmi_user_uart.h"
// Global variable for this example

/*****************************************************
 * 函数功能：求信号幅值
 * 函数入口：
 */
float Calcu_AMP(float * Samplelist,Uint16 Buf_size)
{
	float maxvalue[11] = {0,0,0,0,0,0,0,0,0,0,0};
	float minvalue[11] = {0,0,0,0,0,0,0,0,0,0,0};
	static unsigned char lenth = 5;
	unsigned int index = 0;
	unsigned int i = 0,k = 0;
	float maxsum = 0;
	float minsum = 0;
	
	for(index = 0; index<Buf_size-lenth; index++)
	{
		if((Samplelist[index+2] > Samplelist[index+0]) && (Samplelist[index+2] > Samplelist[index+1])&& (Samplelist[index+2] > Samplelist[index+3])&& (Samplelist[index+2] > Samplelist[index+4]) )
		{
			maxvalue[i] = Samplelist[index+2];
			i++;
			index +=10;
		}
		else if( (Samplelist[index+2] < Samplelist[index+0]) && (Samplelist[index+2] < Samplelist[index+1])&& (Samplelist[index+2] < Samplelist[index+3])&& (Samplelist[index+2] < Samplelist[index+4]))
		{
			minvalue[k] = Samplelist[index+2];
			k++;
			index +=10;
		}
	}
	//处理minvalue和maxvalue
	maxsum = sortandaverage(maxvalue);
	minsum = sortandaverage(minvalue);
	//计算幅值
	return (maxsum-minsum)/2;
}

float sortandaverage(float * valuelist)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int count = 0;
	float temp = 0;
	
	for(i = 0;i<11;i++)
	{
		if (valuelist[i]!=0)
		{
			count++;
		}
	}
	for(i = 0;i<count;i++)
	{
		for(j = i+1; j< count;j++)
		{
			if(valuelist[i] < valuelist[j])
			{
				temp = valuelist[j];
				valuelist[j] = valuelist[i];
				valuelist[i] = temp;
			}
		}
	}
	temp = 0;
	//计算平均值（去掉最大值和最小值）
	for(i = 1;i< count-1;i++)
	{
		temp += valuelist[i];
	}
	return temp/(count-2);
}
/*************************************************************
 * 函数功能： 计算烧结料水分含量
 * 入口参数： 测量通道，参比通道1，参比通道2的信号,及size, 拟合方式
 * 返回值：   烧结料的水分百分含量
 ****************************************************/
float Moisture_FITcalcu(float* MeasureDal,Uint16 Buf_size1,float* Refer1Dal,Uint16 Buf_size2,float* Refer2Dal,Uint16 Buf_size3,char FIT_Mode)
{
	float Measure_Amp,Refer1_Amp,Refer2_Amp,Ratio,water_content;
	water_content = 0;
//	Measure_Amp = Single_AmpValue(MeasureDal,Buf_size1);
//	Refer1_Amp = Single_AmpValue(Refer1Dal,Buf_size2);
//	Refer2_Amp = Single_AmpValue(Refer2Dal,Buf_size3);
//	Ratio = Measure_Amp/(Refer1_Amp+Refer2_Amp);
	
//	Print_data[0]=(unsigned char)((Uint16)(Measure_Amp*100)>>8);
//	Print_data[1]=(unsigned char)((Uint16)(Measure_Amp*100)&0x00ff);
//	Print_data[2]=(unsigned char)((Uint16)(Refer1_Amp*100)>>8);
//	Print_data[3]=(unsigned char)((Uint16)(Refer1_Amp*100)&0x00ff);
//	Print_data[4]=(unsigned char)((Uint16)(Refer2_Amp*100)>>8);
//	Print_data[5]=(unsigned char)((Uint16)(Refer2_Amp*100)&0x00ff);
//	Print_data[6]=(unsigned char)((Uint16)(Ratio*100)>>8);
//	Print_data[7]=(unsigned char)((Uint16)(Ratio*100)&0x00ff);
	
	switch(FIT_Mode)
	{
		case '1':  // 三次拟合
			break;
		case '2':  // 分段线性拟合
			break;
		case '3':  // 指数拟合	
			break;
		default :
			break;
	}
	return water_content;
}
/****************************************************
 * 函数功能: DATA trans
 * 入口参数: DAL_OutPut,
 ****************************************************/
 void Data_Trans(float * Trans_data,Uint16 Buf_size,char * Trans_result)
 {
 	register int i,j;

	for(i=0;i<Buf_size;i++)
	{
		j=2*i;
		Trans_result[j]=(unsigned char)((Uint16)(Trans_data[i]*10)>>8);
		Trans_result[j+1]=(unsigned char)((Uint16)(Trans_data[i]*10)&0x00ff);	
	}
 }


//-------------------------------------------------
//no more
//-------------------------------------------------

