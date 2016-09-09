
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
 * �������ܣ����Ծ��
 * ������ڣ�
 */
void LinearConvolution(const unsigned int buf_size,const unsigned int h_Size,_iq24 *x,const _iq24 *h,_iq24 *y)
{
	//
	unsigned int i = 0,j = 0,m = 0,LL = 0;
	unsigned int x_Size = 0,y_Size = 0;   //�������y�ĳ���
	x_Size = buf_size;
	y_Size = x_Size + h_Size -1;
	
	m = y_Size - 1;
	for(i = 0; i< h_Size;i++ )
	{
		LL = m;
		for(j = 1; j< x_Size; j++)
		{
			y[LL]+= _IQ24mpy(h[i],x[j]);
			LL--;
		}
		y[LL] += _IQ24mpy(x[0],h[i]);
		m--;
	}
	LL = m;
	for(j = 1; j< x_Size-1; j++)
	{
		y[LL]+= _IQ24mpy(h[0],x[j]);
		LL--;
	}
	y[LL]+= _IQ24mpy(x[0],h[0]);
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
		Sin_tab[i] = sin(theta);
		Cos_tab[i] = cos(theta);
	}
}
/****************************************************
 * �������� DAL_Process
 * ��������: ��������Ŵ������㣬ֻ���һ��ͨ����������
 ****************************************************/
void DAL_Process(float *Channel_Date, const unsigned int Buf_size, _iq24 *Cross_OutPut)
{
	unsigned int k = 0,j = 0;
	float temp1 = 0,temp2 = 0;
	float SampleBuffer1[BUF_SIZE1]={0};
	float SampleBuffer2[BUF_SIZE1]={0};
	float *sinwave = NULL;
	float *coswave = NULL;
	//ѡ��һ�����ڵĲο�����
	if(BUF_SIZE1 == Buf_size)
	{
		sinwave = sin_wave1;
		coswave = cos_wave1;
	}
	else if(BUF_SIZE2 == Buf_size)
	{
		sinwave = sin_wave2;
		coswave = cos_wave2;
	} 
	else
	{
		sinwave = sin_wave3;
		coswave = cos_wave3;
	}
	
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
	}/*
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
	*/
	for(k = 0;k < Buf_size; k++)
	{
		temp1 = SampleBuffer1[k];    //ע������Խ�����⣬K=0ʱ�����
		temp2 = SampleBuffer2[k];
		Cross_OutPut[k]= _IQ24(2*sqrt(temp1*temp1+temp2*temp2));	 
	}
}

/*************************************************************
 * �������ܣ� �����ս���ˮ�ֺ���
 * ��ڲ����� ����ͨ�����α�ͨ��1���α�ͨ��2���ź�,��size, ��Ϸ�ʽ
 * ����ֵ��   �ս��ϵ�ˮ�ְٷֺ���
 ****************************************************/
float Moisture_FITcalcu(float* MeasureDal,Uint16 Buf_size1,float* Refer1Dal,Uint16 Buf_size2,float* Refer2Dal,Uint16 Buf_size3,char FIT_Mode)
{
	float Measure_Amp,Refer1_Amp,Refer2_Amp,Ratio,water_content;
	water_content = 0;
	//Measure_Amp = Single_AmpValue(MeasureDal,Buf_size1);
	//Refer1_Amp = Single_AmpValue(Refer1Dal,Buf_size2);
	//Refer2_Amp = Single_AmpValue(Refer2Dal,Buf_size3);
	//Ratio = Measure_Amp/(Refer1_Amp+Refer2_Amp);
	
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
/****************************************************
 * ��������: DATA trans
 * ��ڲ���: DAL_OutPut,
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
  * Function�� get the voltal of the process resule
  * Inlet parameter: DAL_OutPut and the size of DAL_OutPut
  * Outlet parameter: the amplitude of the DAL_OutPut.
  ****************************************************/
 float Single_AmpValue(_iq24 * DAL_OutPut,const Uint16 count_size )
 {
 	int i = 0;
	float tempdata = 0;
	for(i = 70;i < count_size-70; i++)
	{
		tempdata += DAL_OutPut[i];		
	}
	return _IQ24toF(tempdata)/(count_size-140);  //ȡ��100����������100������ƽ��ֵ
 }

//-------------------------------------------------
//no more
//-------------------------------------------------

