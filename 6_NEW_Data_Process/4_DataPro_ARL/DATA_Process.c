
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
 * �������ܣ�Filter FIR
 * ������ڣ��źŵĳ���
 *         �˲�������
 *         �����ź�����ָ��
 *         �˲���ϵ��
 *         ����ź�����ָ��
 */
 void FIR_Filter(const unsigned int xn,const float*x, const unsigned int hn, const float*h, float * y)
 {
 	float temp = 0;
 	unsigned int yn = 0;
 	unsigned int i = 0,j = 0;
 	yn = xn+hn-1;
 	
 	for(i = 0;i<hn;i++)
 	{
 		y[i] = 0;
 	}
 	
 	for(i = hn-1; i< yn; i++)
 	{
 		for(j = 0;j<hn; j++)
 		{
 			if((i-j)< xn)
 			{
 				temp += h[j]*(x[i-j]);
 			}
 			else
 			{
 				temp +=0;
 			}
 			
 		}
 		y[yn-i] = temp;
 	}
 	
 }
 
 
/*****************************************************
 * �������ܣ����Ծ��
 * ������ڣ��źŵĳ���
 *         �˲�������
 *         �����ź�����ָ��
 *         �˲���ϵ��
 *         ����ź�����ָ��
 */
void LinearConvolution(const unsigned int buf_size,const unsigned int hn,float *x,const float *h,float *y)
{	
	unsigned int i = 0,j = 0,m = 0,LL = 0;
	unsigned int xn = 0,yn = 0;   //�������y�ĳ���
	xn = buf_size;
	yn = xn + hn -1;
	for(i=0;i<yn;i++) 
	{
		y[i]=0;  //��������ʼ��
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
/*****************************************************
 * �������ܣ����źŷ�ֵ
 * ������ڣ��������ڵ���ʽ��
 * ��ڲ�����
 * 	     �����ź�����
 *      �����ź����еĳ���
 *      �˲������еĳ���
 * ��ע��maxvalue��minvalue����Ĵ�Сȡ����һ�β����������źŵķ�ֵ����
 */
float Calcu_AMP(float * Samplelist,Uint16 Buf_size,const Uint16 Filer_size)
{
	float maxvalue[21] = {0};
	float minvalue[21] = {0};
	static unsigned char lenth = 7;  //�Ƚϴ��ĳ���Ϊ7�� 
	unsigned int index = 0;
	unsigned int i = 0,k = 0;
	float maxsum = 0;
	float minsum = 0;
	unsigned char pp_num = 21;  //maxvalue����ĳ���
	//��ʼ������ maxvalue �� minvalue
	for(index = 0; index < pp_num; index++ )
	{
		maxvalue[index] = 0;
		minvalue[index] = 0;
	}
	//���������еķ��ֵ��ѹ��ȥ������ͷ����β������Ϊ Filer_size ������
	for(index = Filer_size; index < Buf_size-lenth-Filer_size; index++)
	{
		if((Samplelist[index+3] > Samplelist[index+0]) && (Samplelist[index+3] > Samplelist[index+6])&& 
		(Samplelist[index+3] > Samplelist[index+1])&& (Samplelist[index+3] > Samplelist[index+5]) &&  
		(Samplelist[index+3] > Samplelist[index+2])&& (Samplelist[index+3] > Samplelist[index+4]))
		{
			maxvalue[i] = Samplelist[index+3];
			i++;
			index +=4;
		}
		else if( (Samplelist[index+3] < Samplelist[index+0]) && (Samplelist[index+3] < Samplelist[index+6])&& 
		(Samplelist[index+3] < Samplelist[index+1])&& (Samplelist[index+3] < Samplelist[index+5]) &&
		(Samplelist[index+3] < Samplelist[index+2])&& (Samplelist[index+3] < Samplelist[index+4]))
		{
			minvalue[k] = Samplelist[index+3];
			k++;
			index +=4;
		}
	}
	//����minvalue��maxvalue
	maxsum = sortandaverage(maxvalue,pp_num);
	minsum = sortandaverage(minvalue,pp_num);
	//������ֵ
	return (maxsum-minsum);
}

float sortandaverage(float * valuelist,const unsigned char longnum)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int count = 0;
	float temp = 0;
	
	for(i = 0;i<longnum;i++)
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
	//����ƽ��ֵ��ȥ�����ֵ����Сֵ��
	for(i = 1;i< count-1;i++)
	{
		temp += valuelist[i];
	}
	return temp/(count-2);
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


//-------------------------------------------------
//no more
//-------------------------------------------------

