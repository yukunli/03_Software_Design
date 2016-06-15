
/*
 created by li Danny
 Date:/ 2015/12/20
*/

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"
#include "DATA_Process.h"
#include "ConstData_Table.h"
#include "AD7656.h"
#include "std_init.h"
// Global variable for this example

//3·���������������ͨ���Ծ������Ľ���������
float DAL_OutPut1[BUF_SIZE1+LOWFILT_SIZE]={0};
float DAL_OutPut2[BUF_SIZE2+LOWFILT_SIZE]={0};
float DAL_OutPut3[BUF_SIZE3+LOWFILT_SIZE]={0};

/*****************************************************
 * �������ܣ����Ծ��
 * ������ڣ�
 */
void LinearConvolution(unsigned int xn,unsigned int hn,float *x,float *h,float *y)
{
	unsigned int i,j,m,LL;
	unsigned int yn = 0;   //�������y�ĳ���
	yn = xn + hn -1;
	for(i=0;i<yn;i++) 
	{
		y[i]=0;  //��������ʼ��
	}
	m = yn - 1;
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

/*******************************************************
 * �������� SINCOS_TAB
 * �������ܣ��������Ҳο���������
 ******************************************************/
void SINCOS_TAB(float * Sin_tab,float *Cos_tab,unsigned int cycle_point)
{
	unsigned int i = 0;
	float theta = 0;
	for(i = 0; i < cycle_point; i++)
	{
		theta = i* 6.283185/cycle_point;   //2pi = 6.283185, 
		Sin_tab[i] = sin(theta)+1.0;
		Cos_tab[i] = cos(theta)+1.0;
	}
}
/****************************************************
 * �������� DAL_Process
 * ��������: ��������Ŵ������㣬ֻ���һ��ͨ����������
 ****************************************************/
void DAL_Process(float *Channel_Date, unsigned int Buf_size, float *Low_filter, float *DAL_OutPut)
{
	register int k = 0,j = 0;
	float temp1 = 0,temp2 = 0;
	float Cross_OutPut[2*BUF_SIZE1-1];       //3·����������ο��������������������Ľ���������
	float SampleBuffer1[2*BUF_SIZE1-1]={0};
	float SampleBuffer2[2*BUF_SIZE1-1]={0};
	float sinwave[BUF_SIZE1/CYCLE_NUM] = {0};
	float coswave[BUF_SIZE1/CYCLE_NUM] = {0};
	
	SINCOS_TAB(sinwave,coswave,Buf_size/CYCLE_NUM);
	/*
	float testsinwave[BUF_SIZE1] = {0};
	float testcoswave[BUF_SIZE1] = {0};
	for(k = 0;k < Buf_size;k++)
	{
		testsinwave[k] = sinwave[k%42];
		testcoswave[k] = coswave[k%42];
	}
	*/
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
		temp1 = SampleBuffer1[2*Buf_size-1-k];
		temp2 = SampleBuffer2[2*Buf_size-1-k];
		Cross_OutPut[2*Buf_size-1-k]=2*sqrt(temp1*temp1+temp2*temp2);	 
	}
  	//*******************************************
  	LinearConvolution(Buf_size,LOWFILT_SIZE,Cross_OutPut,Low_filter,DAL_OutPut);  //���Ծ��
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
 	register int i,j;

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
 	int i = 0;
	float tempdata = 0;
	for(i = 60;i <= Buf_size-20; i++)
	{
		tempdata += DAL_OutPut[i];		
	}
	
	return tempdata/(BUF_SIZE1-60-19);
 }

//-------------------------------------------------
//no more
//-------------------------------------------------
