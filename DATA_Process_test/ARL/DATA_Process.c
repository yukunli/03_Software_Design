
/*
 created by li Danny
 Date:/ 2015/12/20
*/
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"
#include "DATA_Process.h"
#include "ConstData_Table.h"
#include "stdio.h"
#include "AD7656.h"
// Global variable for this example

Uint16 array_index=0;
volatile unsigned char Print_data[8]={0,0};

//3路互相关运算结果做低通线性卷积运算的结果存放数组
float DAL_OutPut1[BUF_SIZE1+LOWFILT_SIZE]={0};
float DAL_OutPut2[BUF_SIZE2+LOWFILT_SIZE]={0};
float DAL_OutPut3[BUF_SIZE3+LOWFILT_SIZE]={0};

////3路低通线性卷积运算的结果平均值
//float Ever_VolOut1[20]={0,0};
//float Ever_VolOut2[20]={0,0};
//float Ever_VolOut3[20]={0,0};

/*****************************************************
 * 函数功能：线性卷积
 * 函数入口：
 */
void LinearConvolution(unsigned int xn,unsigned int hn,float *x,float *h,float *y)
{
	unsigned int i,j,m,LL;
	unsigned int yn;   //输出序列y的长度
	yn=xn+hn-1;
	for(i=0;i<yn;i++) y[i]=0;  //输出数组初始化
	m=yn-1;
	for(i=hn-1;i>0;i--)      //将*h作为被乘数
	{
		LL=m;
		for(j=xn-1;j>0;j--)  //数组x[n]的1~(xn-1)与h[i]逐一相乘
		{
			y[LL]+=h[i]*x[j];
			LL--;
		}
		y[LL]+=x[0]*h[i];
		m--;
	}
	LL=m;
	for(j=xn-1;j>0;j--)
	{
		y[LL]+=h[0]*x[j];
		LL--;
	}
	y[LL]+=x[0]*h[0];
}

/*
 * Function: 数字锁相放大器运算
 */
void DAL_Process(float * Channel_Date,unsigned int Buf_size,float * stand_sinwave,float * stand_coswave,float * Low_filter,float * DAL_OutPut)
{
	int k,j;
	float temp1,temp2;
	float * Cross_OutPut; //3路采样序列与参考正弦序列做互相关运算的结果存放数组
	float SampleBuffer1[450]={0};
	float SampleBuffer2[450]={0};
	for(k=0;k <BUF_SIZE1;k++)
	{
		temp1 = 0;
		temp2 = 0;
		SampleBuffer1[BUF_SIZE1-1-k] = 0;
		SampleBuffer2[BUF_SIZE1-1-k] = 0;
		for(j = 0;j < BUF_SIZE1-k;j++)
		{
			temp1 += Channel_Date[j]*stand_sinwave[j+k];
			temp2 += Channel_Date[j]*stand_coswave[j+k];
		}
		SampleBuffer1[BUF_SIZE1-1-k] = temp1/(BUF_SIZE1-k);
		SampleBuffer2[BUF_SIZE1-1-k] = temp2/(BUF_SIZE1-k);
	}

	for(k=0;k<BUF_SIZE1;k++)
	{
		temp1 =SampleBuffer1[BUF_SIZE1-1-k];
		temp2 =SampleBuffer2[BUF_SIZE1-1-k];
		Cross_OutPut[BUF_SIZE1-1-k]=2*sqrt(temp1*temp1+temp2*temp2);	 
	}
  	//*******************************************
  	LinearConvolution(Buf_size,36,Cross_OutPut,Low_filter,DAL_OutPut);  //线性卷积
}

/*************************************************************
 * 函数功能： 计算烧结料水分含量
 * 入口参数： 测量通道，参比通道1，参比通道2的信号,及size, 拟合方式
 * 返回值：   烧结料的水分百分含量
 */
float Moisture_FITcalcu(float* MeasureDal,Uint16 Buf_size1,float* Refer1Dal,Uint16 Buf_size2,float* Refer2Dal,Uint16 Buf_size3,char FIT_Mode)
{
	float Measure_Amp,Refer1_Amp,Refer2_Amp,Ratio,water_content;
	water_content = 0;
	Measure_Amp = Single_Amplitude(MeasureDal,Buf_size1);
	Refer1_Amp = Single_Amplitude(Refer1Dal,Buf_size2);
	Refer2_Amp = Single_Amplitude(Refer2Dal,Buf_size3);
	Ratio = Measure_Amp/(Refer1_Amp+Refer2_Amp);
	
	Print_data[0]=(unsigned char)((Uint16)(Measure_Amp*100)>>8);
	Print_data[1]=(unsigned char)((Uint16)(Measure_Amp*100)&0x00ff);
	Print_data[2]=(unsigned char)((Uint16)(Refer1_Amp*100)>>8);
	Print_data[3]=(unsigned char)((Uint16)(Refer1_Amp*100)&0x00ff);
	Print_data[4]=(unsigned char)((Uint16)(Refer2_Amp*100)>>8);
	Print_data[5]=(unsigned char)((Uint16)(Refer2_Amp*100)&0x00ff);
	Print_data[6]=(unsigned char)((Uint16)(Ratio*100)>>8);
	Print_data[7]=(unsigned char)((Uint16)(Ratio*100)&0x00ff);
	
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
/*
 * 函数功能: DATA trans
 * 入口参数: DAL_OutPut,
 */
 void Data_Trans(float * Trans_data,Uint16 Buf_size,char * Trans_result)
 {
 	int i,j;

	for(i=0;i<Buf_size;i++)
	{
		j=2*i;
		Trans_result[j]=(unsigned char)((Uint16)(Trans_data[i]*10)>>8);
		Trans_result[j+1]=(unsigned char)((Uint16)(Trans_data[i]*10)&0x00ff);	
	}

 }

/*
  * Function： get the voltal of the process resule
  * Inlet parameter: DAL_OutPut and the size of DAL_OutPut
  * Outlet parameter: the amplitude of the DAL_OutPut.
  */
 float Single_Amplitude(float * DAL_OutPut,Uint16 Buf_size )
 {
 	int i;
	float tempdata=0;
	for(i=60;i<Buf_size;i++)
	{
		tempdata+=DAL_OutPut[i];		
	}
	
	return tempdata/(BUF_SIZE1-60);
 }

//------------------------
//no more
//-------------------------------------------------
