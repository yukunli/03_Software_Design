
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
 	//unsigned int yn = 0;
 	unsigned int i = 0,j = 0;
 	//yn = xn+hn-1;
 	for(i = 0; i< xn; i++)
 	{
 		temp = 0;
 		for(j = 0;j< hn; j++)
 		{
 			if(i >= j)
 			{
 				temp += h[j]*x[i-j];
 			}			
 		}
 		y[i] = temp;
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
	float maxvalue[15] = {0};
	float minvalue[15] = {0};
	static unsigned char lenth = 5;  // �Ƚϴ��ĳ���Ϊ5�� 
	unsigned int index = 0;
	unsigned int i = 0,k = 0;
	float maxsum = 0;
	float minsum = 0;
	unsigned char pp_num = 15;  //maxvalue����ĳ���
	//��ʼ������ maxvalue �� minvalue
	for(index = 0; index < pp_num; index++ )
	{
		maxvalue[index] = 0;
		minvalue[index] = 0;
	}
	//���������еķ��ֵ��ѹ��ȥ������ͷ����β������Ϊ Filer_size ������
	for(index = Filer_size; index < Buf_size-lenth; index++)
	{
		if((Samplelist[index+2] > Samplelist[index+0]) && (Samplelist[index+2] > Samplelist[index+4])&& 
		(Samplelist[index+2] > Samplelist[index+1])&& (Samplelist[index+2] > Samplelist[index+3])  )
		{
			maxvalue[i] = Samplelist[index+2];
			i++;
			index +=3;
			if(i>= pp_num)
				break;
		}
		else if( (Samplelist[index+2] < Samplelist[index+0]) && (Samplelist[index+2] < Samplelist[index+4])&& 
		(Samplelist[index+2] < Samplelist[index+1])&& (Samplelist[index+2] < Samplelist[index+3]) )
		{
			minvalue[k] = Samplelist[index+2];
			k++;
			index +=3;
			if(k>= pp_num)
				break;
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
 * ����ֵ��   �ս��ϵ�ˮ��˲ʱˮ�ְٷֺ���
 ****************************************************/
float Moisture_FITcalcu(float Tdata, Fit_Param* Param, const char FIT_Mode)
{
	float water_content = 0;

	switch(FIT_Mode)
	{
		case '1':  // �������
			water_content = (Param->Fit_a)*pow(Tdata,3) + (Param->Fit_b)*Tdata*Tdata +
							(Param->Fit_c)*Tdata + Param->Fit_d; 
			break;
		case '2':  // �ֶ��������
			//break;
		case '3':  // ָ�����
		    //water_content = 9040*pow(2.71828,-22.09*Tdata)+3.303;	
			break;
		default :
			break;
	}
	return water_content;
}

/*************************************************************
 * �������ܣ� ��������ϵ����ʵ�ʵ�ˮ��ֵ
 * ��ڲ����� ���ϲ���ˮ��ֵ
 * 			����ϵ����б�ʺͽؾ�
 * ����ֵ��   �ֳ���ˮ��ֵ
 ****************************************************/
float Correct_Moisture(float measuvalue, float corr_k, float corr_b)
{
	return corr_k*measuvalue + corr_b;
}

//-------------------------------------------------
//no more
//-------------------------------------------------

