
/*
 created by li Danny
 Date:/ 2015/12/20
*/

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"
#include "stdlib.h"
#include "AD9833.H"
#include "DATA_Process.h"
#include "ConstData_Table.h"
#include "std_init.h"
#include "hmi_user_uart.h"
// Global variable for this example

/*****************************************************
 * 函数功能：线性卷积
 * 函数入口：信号的长度
 *         滤波器长度
 *         输入信号数组指针
 *         滤波器系数
 *         输出信号数组指针
 */
void LinearConvolution(const unsigned int buf_size,const unsigned int hn,float *x,const float *h,float *y)
{	
	unsigned int i = 0,j = 0,m = 0,LL = 0;
	unsigned int xn = 0,yn = 0;   //输出序列y的长度
	xn = 2*buf_size-1;
	yn = xn + hn -1;
	for(i=0;i<yn;i++) 
	{
		y[i]=0;  //输出数组初始化
	}
	m = yn - 1;
	for(i = 0; i< hn;i++ )
	{
		LL = m;
		for(j = 1; j< xn; j++)
		{
			y[LL]+=h[i]*x[j];
			LL--;
		}
		y[LL]+=x[0]*h[i];
		m--;
	}
	LL = m;
	for(j = 1; j< xn-1; j++)
	{
		y[LL]+=h[0]*x[j];
		LL--;
	}
	y[LL]+=x[0]*h[0];
	
}

/*******************************************************
 * 函数名： SINCOS_TAB
 * 函数功能：正弦余弦参考序列生成
 * 输入参数：
 *     sin_tab ：存储正弦值的数组
 *     cos_tab： 存储余弦值的数组
 *     cycle_point: F/Fs
 ******************************************************/
void SINCOS_TAB(float *Sin_tab,float *Cos_tab,const unsigned int cycle_point)
{
	unsigned int i = 0;
	float theta = 0;
	for(i = 0; i < cycle_point; i++)
	{
		theta = i*6.283185/cycle_point;   //2pi = 6.283185, 
		Sin_tab[i] = sin(theta);
		Cos_tab[i] = cos(theta);
	}
}
/****************************************************
 * 函数名： DAL_Process
 * 函数功能: 数字锁相放大器运算，只针对一个通道进行运算
 * 参数： Cross_OutPut：3路采样序列与参考正弦序列做互相关运算的结果存放数组
 ****************************************************/
void DAL_Process(float *Channel_Date, const unsigned int Buf_size,const unsigned int Cy_Point,const float*sinwave,const float*coswave,float *Cross_OutPut)
{
	unsigned int k = 0,j = 0;
	float temp1 = 0,temp2 = 0;
	float SampleBuffer1[2*BUF_SIZE1]={0};   //实际长度为2*Buf_size -1
	float SampleBuffer2[2*BUF_SIZE1]={0};
	//float  sinwave[30]  = {0};
	//float  coswave[30]  = {0};
	//产生一个周期的参考序列
	
	//SINCOS_TAB(sinwave,coswave,Cy_Point);
	
	//相关运算
	for(k = 0; k < Buf_size; k++)
	{
		temp1 = 0;
		temp2 = 0;
		for(j = 0;j < Buf_size-k; j++)
		{
			temp1 += Channel_Date[j]*sinwave[(j+k)%Cy_Point];
			temp2 += Channel_Date[j]*coswave[(j+k)%Cy_Point];
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
			temp1 += Channel_Date[j+k]*sinwave[j%Cy_Point];
			temp2 += Channel_Date[j+k]*coswave[j%Cy_Point];
		}
		SampleBuffer1[Buf_size-1+k] = temp1/(Buf_size-k);
		SampleBuffer2[Buf_size-1+k] = temp2/(Buf_size-k);
	}
	
	for(k = 0;k < 2*Buf_size-1; k++)
	{
		temp1 = SampleBuffer1[2*Buf_size-2-k];    //注意数组越界问题，K=0时的情况
		temp2 = SampleBuffer2[2*Buf_size-2-k];
		Cross_OutPut[2*Buf_size-2-k] = 4*sqrt(temp1*temp1 + temp2*temp2); 
	}
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
	for(i = 70;i < count_size-70; i++)
	{
		tempdata += DAL_OutPut[i];		
	}
	return tempdata/(count_size-140);  //取第100个数到倒数100个数的平均值
 }

//-------------------------------------------------
//no more
//-------------------------------------------------

