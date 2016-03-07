
/*
 created by li Danny
 Date:/ 2015/11/23
 
*/
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "AD9833.h"

/*******************************************
 * 函数描述： 模拟SPI的IO口初始化
 */
 void AD9833_configinit(void)
{
   EALLOW;
   GpioCtrlRegs.GPCMUX2.bit.GPIO81 = 0; // GPIO0 = GPIO0
   GpioCtrlRegs.GPCDIR.bit.GPIO81 = 1; 
   
   GpioCtrlRegs.GPBMUX1.bit.GPIO47 = 0; // GPIO1 = GPIO1
   GpioCtrlRegs.GPBDIR.bit.GPIO47 = 1;
   
   GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0; // GPIO2 = GPIO2
   GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;
   
   GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0; // GPIO2 = GPIO2
   GpioCtrlRegs.GPBDIR.bit.GPIO43 = 1;
   
   GpioCtrlRegs.GPBMUX1.bit.GPIO45 = 0; // GPIO2 = GPIO2
   GpioCtrlRegs.GPBDIR.bit.GPIO45 = 1;
   EDIS;
}


//延时程序
/**************************************************/
void delay(unsigned int m)
{
	unsigned int n;
	for (n=0;n<=m;n++)
	{
	}
}
/*****************************************************
*函数描述：数向AD9833写16位数据，严格按照这个时序，不能随意修改否则必出错！
*入口参数：x要发送的命令字，change为要控制的AD9833芯片号（对应为1,2,3）
*/
void write_ad9833_d16(unsigned int x,char change)
{
	int i,w;
	w=x;
	ad9833_sclk=1;
	ad9833_fsync1=1;
	ad9833_fsync2=1;
	ad9833_fsync3=1;
	DELAY_US(5);
	if(change==1)     //正弦信号通道1
	{
	ad9833_fsync1=0;
	}
	if(change==2)	 //正弦信号通道2
	{
	ad9833_fsync2=0;
	}
	if(change==3)	 //正弦信号通道3
	{
	ad9833_fsync3=0;
	}
	DELAY_US(5);
	//写16位数据
	
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
	ad9833_fsync1=1;
	ad9833_fsync2=1;
	ad9833_fsync3=1;
	DELAY_US(60);
}
/***************************************************
 * 函数描述： RESET AD9833
 */
 void AD9833_Reset(char channel)
 {
 	write_ad9833_d16(0x0100,channel);
 	write_ad9833_d16(0x2000,channel);
 	
 	write_ad9833_d16(0x4000,channel);
 	write_ad9833_d16(0x4000,channel);
 	write_ad9833_d16(0x2000,channel);
 	write_ad9833_d16(0x8000,channel);
 	write_ad9833_d16(0x8000,channel);
 	write_ad9833_d16(0xD000,channel);
 	write_ad9833_d16(0xF000,channel);
 	DELAY_US(5000);
 }
 
/*************计算AD9833的28位数据值***************/
/*****************************************************/
/**变量frequence就是频率值，单位Hz，比如输入100Hz，则 frequence为100，需要特别注意的是不能超过12MHz*/
/*****变量frequence_SFR是设置频率寄存器选择0为频率寄存器0，1为频率寄存器1；*******/
/*****变量WAVE_MODE是设置输出波形选择0为三角波，1为方波，2为正弦波；*******/
/*****变量Phase是设置波形相位值*******/
void AD9833_Outdata(char change,double frequence,unsigned int frequence_SFR,unsigned int WAVE_MODE,unsigned int Phase)
{
	int frequence_LSB,frequence_MSB,Phs_data;
	double frequence_mid,frequence_DATA;
	long int frequence_hex;
	char channel;
	/*********************************计算频率的16进制值***********************************/
	frequence_mid=268435456/1;//适合25M晶振
	//如果时钟频率不为25MHZ，修改该处的频率值，单位MHz ，AD9833最大支持25MHz
	frequence_DATA=frequence;
	frequence_DATA=frequence_DATA/1000000;
	frequence_DATA=frequence_DATA*frequence_mid;
	frequence_hex=frequence_DATA; //这个frequence_hex的值是32位的一个很大的数字，需要拆分成两个14位进行处理；
	frequence_LSB=frequence_hex; //frequence_hex低16位送给frequence_LSB
	frequence_LSB=frequence_LSB&0x3fff;//去除最高两位，16位数换去掉高位后变成了14位
	frequence_MSB=frequence_hex>>14; //frequence_hex高16位送给frequence_HSB
	frequence_MSB=frequence_MSB&0x3fff;//去除最高两位，16位数换去掉高位后变成了14位
	/****************************************************************************/
	channel=change;
	/******************************相位值*************************************/
	Phs_data=Phase|0xC000;
	
	if(frequence_SFR==0) //把数据设置到设置频率寄存器0
	{
		frequence_LSB=frequence_LSB|0x4000;
		frequence_MSB=frequence_MSB|0x4000;
		//使用频率寄存器0输出波形
		/*************************************************/
		write_ad9833_d16(0x0100,channel); //复位AD9833,即RESET位为1
		
		write_ad9833_d16(0x2100,channel); //选择数据一次写入，B28位和RESET位为1
		write_ad9833_d16(frequence_LSB,channel); //L14，选择频率寄存器0的低14位数据输入
		write_ad9833_d16(frequence_MSB,channel); //H14 频率寄存器的高14位数据输入
		write_ad9833_d16(Phs_data,channel); //设置相位
		//write_ad9833_d16(0x2000,channel); /**设置FSELECT位为0，芯片进入工作状态,频率寄存器0输出波形**/
	}
	/************************************************************************************/   
  if(frequence_SFR==1) //把数据设置到设置频率寄存器1
	{
	frequence_LSB=frequence_LSB|0x8000;
	frequence_MSB=frequence_MSB|0x8000;
	//使用频率寄存器1输出波形
	/*************************************************/
	write_ad9833_d16(0x0100,channel); //复位AD9833,即RESET位为1
	write_ad9833_d16(0x2100,channel); //选择数据一次写入，B28位和RESET位为1
	write_ad9833_d16(frequence_LSB,channel); //L14，选择频率寄存器1的低14位输入
	write_ad9833_d16(frequence_MSB,channel); //H14 频率寄存器1为
	write_ad9833_d16(Phs_data,channel); //设置相位
	//write_ad9833_d16(0x2800); /**设置FSELECT位为0，设置FSELECT位为1，即使用频率寄存器1的值，芯片进入工作状
	//态,频率寄存器1输出波形**/
	}
	/****************************************************************************************/
	if(WAVE_MODE==0)
	{
		//频率寄存器输出三角波波形
		/***************************************************/
		delay(1000);
		write_ad9833_d16(0x2002,channel); //设置MODE位为1，输出三角波模式
		}
	/***************************************************/
	if(WAVE_MODE==1)
	{
		//频率寄存器输出方波波形
		/***************************************************/
		delay(1000);
		write_ad9833_d16(0x2028,channel); //设置OPBITEN位为1，方波输出模式
	}
	/***************************************************/
	if(WAVE_MODE==2)
	{
		//频率寄存器输出正弦波波形
		/***************************************************/
		delay(1000);
		write_ad9833_d16(0x2000,channel); //设置MODE位为0，输出正弦波模式
	}
	/***************************************************/
}

//===========================================================================
// No more.
//===========================================================================

