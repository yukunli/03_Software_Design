
/*
 created by li Danny
 Date:/ 2015/11/23
 
*/
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "AD9833.h"

/*******************************************
 * ���������� ģ��SPI��IO�ڳ�ʼ��
 */
 void AD9833_configinit(void)
{
   EALLOW;
   GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0; // GPIO0 = GPIO0
   GpioCtrlRegs.GPADIR.bit.GPIO30 = 1; 
   
   GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0; // GPIO1 = GPIO1
   GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
   
   GpioCtrlRegs.GPCMUX2.bit.GPIO82 = 0; // GPIO2 = GPIO2
   GpioCtrlRegs.GPCDIR.bit.GPIO82 = 1;
   
   GpioCtrlRegs.GPCMUX2.bit.GPIO83 = 0; // GPIO2 = GPIO2
   GpioCtrlRegs.GPCDIR.bit.GPIO83 = 1;
   
   GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0; // GPIO2 = GPIO2
   GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;
   EDIS;
}


//��ʱ����
/**************************************************/
void delay(unsigned int m)
{
	unsigned int n;
	for (n=0;n<=m;n++);
}
/*****************************************************
*��������������AD9833д16λ���ݣ��ϸ������ʱ�򣬲��������޸ķ���س���
*��ڲ�����xҪ���͵������֣�changeΪҪ���Ƶ�AD9833оƬ�ţ���ӦΪ1,2,3��
*/
void write_ad9833_d16(unsigned int x)
{
	unsigned char i = 0;
	unsigned int w = x;  
	ad9833_sclk = 1;
//	ad9833_fsync1=1;
//	ad9833_fsync2=1;
//	ad9833_fsync3=1;
	DELAY_US(5);
	//д16λ����
	
	for(i=0;i<16;i++)
	{
		if(w&0x8000)
		{
			ad9833_sdata=1;
		}
		else 
		{
			ad9833_sdata=0;
		}
		DELAY_US(2);
		ad9833_sclk=0;
		DELAY_US(2);
		ad9833_sdata=0;
		DELAY_US(2);
		ad9833_sclk=1;
		DELAY_US(5);
		w=w<<1;
	}	
//	ad9833_fsync1=1;
//	ad9833_fsync2=1;
//	ad9833_fsync3=1;
	DELAY_US(60);
}
void JudgeCS(unsigned char change)
{
	if(change == 0x01)     //�����ź�ͨ��1
	{
		ad9833_fsync1=0;
		ad9833_fsync1=0;
		ad9833_fsync2=1;
		ad9833_fsync3=1;
		return;
	}
	else if(change == 0x02)	 //�����ź�ͨ��2
	{
		ad9833_fsync2=0;
		ad9833_fsync2=0;
		ad9833_fsync1=1;
		ad9833_fsync3=1;
		return;
	}
	else 	 				//�����ź�ͨ��3
	{
		ad9833_fsync3=0;
		ad9833_fsync3=0;
		ad9833_fsync1=1;
		ad9833_fsync2=1;
	}
	return;
}
/***************************************************
 * ���������� RESET AD9833
 */
 void AD9833_Reset(unsigned char channel)
 {
 	JudgeCS(channel);
 	write_ad9833_d16(0x0100);
 	write_ad9833_d16(0x2000);
 	
 	write_ad9833_d16(0x4000);
 	write_ad9833_d16(0x4000);
 	write_ad9833_d16(0x2000);
 	write_ad9833_d16(0x8000);
 	write_ad9833_d16(0x8000);
 	write_ad9833_d16(0xD000);
 	write_ad9833_d16(0xF000);
 	DELAY_US(5000);
	ad9833_fsync1=1;
	ad9833_fsync2=1;
	ad9833_fsync3=1;
 }
 
/*************����AD9833��28λ����ֵ***************/
/*****************************************************/
/**����frequence����Ƶ��ֵ����λHz����������100Hz���� frequenceΪ100����Ҫ�ر�ע����ǲ��ܳ���12MHz*/
/*****����frequence_SFR������Ƶ�ʼĴ���ѡ��0ΪƵ�ʼĴ���0��1ΪƵ�ʼĴ���1��*******/
/*****����WAVE_MODE�������������ѡ��0Ϊ���ǲ���1Ϊ������2Ϊ���Ҳ���*******/
/*****����Phase�����ò�����λֵ*******/
void AD9833_Outdata(unsigned char change,float frequence,unsigned char frequence_SFR,unsigned char WAVE_MODE,unsigned char Phase)
{
	unsigned int frequence_LSB,frequence_MSB,Phs_data;
	double frequence_DATA;
	unsigned long int frequence_hex;
	JudgeCS(change);
	/*********************************����Ƶ�ʵ�16����ֵ***********************************/
	frequence_DATA = frequence;
	frequence_DATA = frequence_DATA/1000000;
	frequence_DATA = frequence_DATA*(268435456/1);  //���ʱ��Ƶ�ʲ�Ϊ25MHZ���޸ĸô���Ƶ��ֵ����λMHz ��AD9833���֧��25MHz
	frequence_hex=frequence_DATA; //���frequence_hex��ֵ��32λ��һ���ܴ�����֣���Ҫ��ֳ�����14λ���д���
	frequence_LSB=frequence_hex; //frequence_hex��16λ�͸�frequence_LSB
	frequence_LSB=frequence_LSB&0x3fff;//ȥ�������λ��16λ����ȥ����λ������14λ
	frequence_MSB=frequence_hex>>14; //frequence_hex��16λ�͸�frequence_HSB
	frequence_MSB=frequence_MSB&0x3fff;//ȥ�������λ��16λ����ȥ����λ������14λ
	/****************************************************************************/
	/******************************��λֵ*************************************/
	Phs_data=Phase|0xC000;
	
	if(frequence_SFR==0) //���������õ�����Ƶ�ʼĴ���0
	{
		frequence_LSB=frequence_LSB|0x4000;
		frequence_MSB=frequence_MSB|0x4000;
		//ʹ��Ƶ�ʼĴ���0�������
		/*************************************************/
		write_ad9833_d16(0x0100); //��λAD9833,��RESETλΪ1
		
		write_ad9833_d16(0x2100); //ѡ������һ��д�룬B28λ��RESETλΪ1
		write_ad9833_d16(frequence_LSB); //L14��ѡ��Ƶ�ʼĴ���0�ĵ�14λ��������
		write_ad9833_d16(frequence_MSB); //H14 Ƶ�ʼĴ����ĸ�14λ��������
		write_ad9833_d16(Phs_data); //������λ
		//write_ad9833_d16(0x2000,channel); /**����FSELECTλΪ0��оƬ���빤��״̬,Ƶ�ʼĴ���0�������**/
	}
	/************************************************************************************/   
  if(frequence_SFR==1) //���������õ�����Ƶ�ʼĴ���1
	{
	frequence_LSB=frequence_LSB|0x8000;
	frequence_MSB=frequence_MSB|0x8000;
	//ʹ��Ƶ�ʼĴ���1�������
	/*************************************************/
	write_ad9833_d16(0x0100); //��λAD9833,��RESETλΪ1
	write_ad9833_d16(0x2100); //ѡ������һ��д�룬B28λ��RESETλΪ1
	write_ad9833_d16(frequence_LSB); //L14��ѡ��Ƶ�ʼĴ���1�ĵ�14λ����
	write_ad9833_d16(frequence_MSB); //H14 Ƶ�ʼĴ���1Ϊ
	write_ad9833_d16(Phs_data); //������λ
	//write_ad9833_d16(0x2800); /**����FSELECTλΪ0������FSELECTλΪ1����ʹ��Ƶ�ʼĴ���1��ֵ��оƬ���빤��״
	//̬,Ƶ�ʼĴ���1�������**/
	}
	/****************************************************************************************/
	if(WAVE_MODE== 0)
	{
		//Ƶ�ʼĴ���������ǲ�����
		/***************************************************/
		delay(1000);
		write_ad9833_d16(0x2002); //����MODEλΪ1��������ǲ�ģʽ
	}
	/***************************************************/
	else if(WAVE_MODE==1)
	{
		//Ƶ�ʼĴ��������������
		/***************************************************/
		delay(1000);
		write_ad9833_d16(0x2028); //����OPBITENλΪ1���������ģʽ
	}
	/***************************************************/
	else if(WAVE_MODE==2)
	{
		//Ƶ�ʼĴ���������Ҳ�����
		/***************************************************/
		delay(1000);
		write_ad9833_d16(0x2000); //����MODEλΪ0��������Ҳ�ģʽ
	}
	/***************************************************/
	ad9833_fsync1=1;
	ad9833_fsync2=1;
	ad9833_fsync3=1;
}

//===========================================================================
// No more.
//===========================================================================

