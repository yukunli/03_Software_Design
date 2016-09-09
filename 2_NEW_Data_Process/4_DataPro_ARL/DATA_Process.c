
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
 * 函数功能：线性卷积
 * 函数入口：
 */
void LinearConvolution(const unsigned int buf_size,const unsigned int hn,float *x,const float *h,float *y)
{
	
	unsigned int i = 0,j = 0,m = 0,LL = 0;
	unsigned int yn = 0;   //输出序列y的长度
	yn = (2*buf_size-1) + hn -1;
	for(i=0;i<yn;i++) 
	{
		y[i]=0;  //输出数组初始化
	}
	m = yn - 1;
	for(i=hn-1;i>0;i--)      //将*h作为被乘数
	{
		LL=m;
		for(j=buf_size-1;j>0;j--)  //数组x[n]的1~(xn-1)与h[i]逐一相乘
		{
			y[LL]+=h[i]*x[j];
			LL--;
		}
		y[LL]+=x[0]*h[i];
		m--;
	}
	LL=m;
	for(j = buf_size-1;j>0;j--)
	{
		y[LL]+=h[0]*x[j];
		LL--;
	}
	y[LL]+=x[0]*h[0];
}

/*******************************************************
 * 函数名： SINCOS_TAB
 * 函数功能：正弦余弦参考序列生成
 ******************************************************/
void SINCOS_TAB(float * Sin_tab,float *Cos_tab,unsigned int cycle_point)
{
	unsigned int i = 0;
	float theta = 0;
	for(i = 0; i < cycle_point; i++)
	{
		theta = i* 6.283185/cycle_point;   //2pi = 6.283185, 
		Sin_tab[i] = sin(theta);
		Cos_tab[i] = cos(theta);
	}
}
/****************************************************
 * 函数名： DAL_Process
 * 函数功能: 数字锁相放大器运算，只针对一个通道进行运算
 ****************************************************/
void DAL_Process(float *Channel_Date, const unsigned int Buf_size, float *Cross_OutPut)
{
	unsigned int k = 0,j = 0;
	float temp1 = 0,temp2 = 0;
	
	//float Cross_OutPut[2*BUF_SIZE1-1];       //3路采样序列与参考正弦序列做互相关运算的结果存放数组
	float SampleBuffer1[2*BUF_SIZE1-1]={0};
	float SampleBuffer2[2*BUF_SIZE1-1]={0};
	float sinwave[42] = {0};
	float coswave[42] = {0};/*
	float *SampleBuffer11 = NULL;
	float *SampleBuffer21 = NULL;
	float *Cross_OutPut1 = NULL;
	float *sinwave1 = NULL;
	float *coswave1 = NULL;*/
	/*
	sinwave = (float *)malloc((Buf_size/CYCLE_NUM)*sizeof(float));
	coswave = (float *)malloc((Buf_size/CYCLE_NUM)*sizeof(float));
	SampleBuffer1 = (float *)malloc((2*Buf_size-1)*sizeof(float));
	SampleBuffer2 = (float *)malloc((2*Buf_size-1)*sizeof(float));
	Cross_OutPut = (float *)malloc((2*Buf_size-1)*sizeof(float));
	if((NULL == sinwave)||(NULL == coswave)||(NULL == SampleBuffer1)||(NULL == SampleBuffer2)||(NULL == Cross_OutPut))
	{
		Send_msg("\n malloc failed!\n");
	}
	*/
	//产生一个周期的参考序列
	SINCOS_TAB(sinwave,coswave,Buf_size/CYCLE_NUM);
	
	for(k = 0; k < Buf_size; k++)
	{
		temp1 = 0;
		temp2 = 0;
		for(j = 0;j < Buf_size-k; j++)
		{
			temp1 += Channel_Date[j]*sinwave[(j+k)%(Buf_size/CYCLE_NUM)];
			temp2 += Channel_Date[j]*coswave[(j+k)%(Buf_size/CYCLE_NUM)];
		}
		SampleBuffer1[Buf_size-1-k] = temp1/(Buf_size-k);
		SampleBuffer2[Buf_size-1-k] = temp2/(Buf_size-k);
	}
	
	for(k = 0; k < Buf_size; k++)
	{
		temp1 = 0;
		temp2 = 0;
		for(j = 0;j < Buf_size-k; j++)
		{
			temp1 += Channel_Date[j+k]*sinwave[j%(Buf_size/CYCLE_NUM)];
			temp2 += Channel_Date[j+k]*coswave[j%(Buf_size/CYCLE_NUM)];
		}
		SampleBuffer1[Buf_size-1+k] = temp1/(Buf_size-k);
		SampleBuffer2[Buf_size-1+k] = temp2/(Buf_size-k);
	}
	
	for(k = 0;k < 2*Buf_size-1; k++)
	{
		temp1 = SampleBuffer1[2*Buf_size-2-k];    //注意数组越界问题，K=0时的情况
		temp2 = SampleBuffer2[2*Buf_size-2-k];
		Cross_OutPut[2*Buf_size-2-k]=2*sqrt(temp1*temp1+temp2*temp2);	 
	}/*
	free(sinwave);
	free(sinwave);
	free(SampleBuffer1);
	free(SampleBuffer1);
	free(Cross_OutPut);*/
  	//低通滤波器
  	//LinearConvolution(Buf_size,LOWFILT_SIZE,Cross_OutPut,Low_Filter1,DAL_OutPut);  //线性卷积
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
	Measure_Amp = Single_AmpValue(MeasureDal,Buf_size1);
	Refer1_Amp = Single_AmpValue(Refer1Dal,Buf_size2);
	Refer2_Amp = Single_AmpValue(Refer2Dal,Buf_size3);
	Ratio = Measure_Amp/(Refer1_Amp+Refer2_Amp);
	
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

/****************************************************
  * Function： get the voltal of the process resule
  * Inlet parameter: DAL_OutPut and the size of DAL_OutPut
  * Outlet parameter: the amplitude of the DAL_OutPut.
  ****************************************************/
 float Single_AmpValue(float * DAL_OutPut,const Uint16 count_size )
 {
 	int i = 0;
	float tempdata = 0;
	for(i = 100;i < count_size-100; i++)
	{
		tempdata += DAL_OutPut[i];		
	}
	return tempdata/(count_size-200);  //取第60个数到倒数19个数的平均值
 }

//-------------------------------------------------
//no more
//-------------------------------------------------

