
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

//3·���������������ͨ���Ծ������Ľ���������
float DAL_OutPut1[BUF_SIZE1+LOWFILT_SIZE]={0};
float DAL_OutPut2[BUF_SIZE2+LOWFILT_SIZE]={0};
float DAL_OutPut3[BUF_SIZE3+LOWFILT_SIZE]={0};

////3·��ͨ���Ծ������Ľ��ƽ��ֵ
//float Ever_VolOut1[20]={0,0};
//float Ever_VolOut2[20]={0,0};
//float Ever_VolOut3[20]={0,0};

/*****************************************************
 * �������ܣ����Ծ��
 * ������ڣ�
 */
void LinearConvolution(unsigned int xn,unsigned int hn,float *x,float *h,float *y)
{
	unsigned int i,j,m,LL;
	unsigned int yn;   //�������y�ĳ���
	yn=xn+hn-1;
	for(i=0;i<yn;i++) y[i]=0;  //��������ʼ��
	m=yn-1;
	for(i=hn-1;i>0;i--)      //��*h��Ϊ������
	{
		LL=m;
		for(j=xn-1;j>0;j--)  //����x[n]��1~(xn-1)��h[i]��һ���
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
 * Function: ��������Ŵ�������
 */
void DAL_Process(float * Channel_Date,unsigned int Buf_size,float * stand_sinwave,float * stand_coswave,float * Low_filter,float * DAL_OutPut)
{
	int k,j;
	float temp1,temp2;
	float * Cross_OutPut; //3·����������ο��������������������Ľ���������
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
  	LinearConvolution(Buf_size,36,Cross_OutPut,Low_filter,DAL_OutPut);  //���Ծ��
}

/*************************************************************
 * �������ܣ� �����ս���ˮ�ֺ���
 * ��ڲ����� ����ͨ�����α�ͨ��1���α�ͨ��2���ź�,��size, ��Ϸ�ʽ
 * ����ֵ��   �ս��ϵ�ˮ�ְٷֺ���
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
		case '1':  // �������
			break;
		case '2':  // �ֶ��������
			break;
		case '3':  // ָ�����	
			break;
		default :
			break;
	}
	return water_content;
}
/*
 * ��������: DATA trans
 * ��ڲ���: DAL_OutPut,
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
  * Function�� get the voltal of the process resule
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
