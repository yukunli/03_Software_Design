/*

*/

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "AD7656.h"
#include "std_init.h"

Uint16 SampleTable1[SAMPLE_COUNT];
Uint16 SampleTable2[SAMPLE_COUNT];
Uint16 SampleTable3[SAMPLE_COUNT];
Uint16 SampleTable4[SAMPLE_COUNT];
Uint16 SampleTable_None[SAMPLE_COUNT];

Uint16 SampleCount;
identi_bool volatile SampleCount_Status_Flag; 
char first_flag = 1;
float  SampleValue1[SAMPLE_COUNT];
float  SampleValue2[SAMPLE_COUNT];
float  SampleValue3[SAMPLE_COUNT];
float  SampleValue4[SAMPLE_COUNT];

void AD7656_ConfigInit(void)
{
	EALLOW;
	GpioCtrlRegs.GPAMUX2.bit.GPIO25=0;
	GpioCtrlRegs.GPADIR.bit.GPIO25=1;		//OUTPUT
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;    // XWE0
	GpioCtrlRegs.GPBDIR.bit.GPIO61=1;		//OUTPUT
	GpioCtrlRegs.GPBMUX2.bit.GPIO60=0;      //ADBUSY
	GpioCtrlRegs.GPBDIR.bit.GPIO60=0;       //INPUT
	GpioCtrlRegs.GPBQSEL2.bit.GPIO60= 0;
	EDIS;
} 

void OUTAD_Timer_Init(void)
{
	InitCpuTimers();   //For this example, only initialize the Cpu Timers

	ConfigCpuTimer(&CpuTimer0, 150, 4.762);   //在定时器内进行采样,采样率1/(1.76us+prioed 0f AD read data约3us)=210KHz

}

/*
 * Function: 初始化与采样有关的变量
 */
void OUTAD_Variable_Init(void)
{
	unsigned int i=0;
	
	for(i=0;i<=SAMPLE_COUNT;i++)
	{
		SampleTable1[i]=0; 
		SampleTable2[i]=0;
		SampleTable3[i]=0;
		SampleTable4[i]=0;
		SampleTable_None[i]=0;
	}
	
	SampleCount = 0;
	SampleCount_Status_Flag = False;
}

/*
 * Function: AD7656 初始化
 */
void OUTAD_Init(void)
{

	OUTAD_Timer_Init();
	OUTAD_Variable_Init();
	AD7656_ConfigInit();
	SET_ADRST;  
	DELAY_US(100000);
	CLEAR_ADRST; 
	DELAY_US(1000);
	/*
	START_SAMPLING();
	CLR_ADCOV;   //启动转换信号
	while(i--);
	SET_ADCOV;
	while(AD_BUSY); 
	for(i =6;i>0;i--)
		firstvalue = AD7656_BASIC & 0xFFFF; //读取4路AD通道数据
	CLR_ADCOV;
	STOP_SAMPLING();
	*/
}
/*
 * Function: 对ad7656进行采样和数据读取
 */
void GetAD_Value(void)
{
	char nop = 5;
	CLR_ADCOV;   //启动转换信号
	while(nop--);
	SET_ADCOV;
//	DELAY_US(2); //等待转换结束
	while(AD_BUSY); 
	if(first_flag == 1)
	{
		for(nop =6;nop>0;nop--)
			SampleTable4[SampleCount] = AD7656_BASIC & 0xFFFF; //读取4路AD通道数据
		first_flag =0;
	}
	else if(SampleCount < SAMPLE_COUNT)
	{
		SampleTable1[SampleCount]=AD7656_BASIC & 0xFFFF; //读取4路AD通道数据
		SampleTable2[SampleCount]=AD7656_BASIC & 0xFFFF; 
		SampleTable3[SampleCount]=AD7656_BASIC & 0xFFFF; 
		SampleTable4[SampleCount]=AD7656_BASIC & 0xFFFF; 
		SampleTable4[SampleCount]=AD7656_BASIC;
		SampleTable4[SampleCount]=AD7656_BASIC;
		SampleCount  ++;
	}
	else 
	{
		CLR_ADCOV; 
		SampleCount = 0;
		SampleCount_Status_Flag = True;
		first_flag = 1;
		STOP_SAMPLING();
	}
}
/*
 * Function: 数字量转float， 由 SampleTable4 update SampleValue3
 */
void AD_Data_Shift(void)
{
	unsigned int i;
	float Setoff_ZoreVal = 0;
	
	for(i=0;i< SAMPLE_COUNT;i++)
	{
		if(SampleTable4[i]&0x8000) //postive
		{
			SampleValue4[i] = (65535-SampleTable4[i])/32767.0*AD_CVEF;    // it should be 0 because connected to GND		
		}
		else 
		SampleValue4[i] = SampleTable4[i]/32767.0*AD_PVEF;
	}
		
	for(i=0;i< SAMPLE_COUNT; i++ )
	{
		Setoff_ZoreVal += SampleValue4[i];
	}
	Setoff_ZoreVal = Setoff_ZoreVal / SAMPLE_COUNT;

	
	for(i=0;i< SAMPLE_COUNT;i++)
	{	
		if(SampleTable3[i]& 0x8000 )
		{
			SampleValue3[i] = (65535-SampleTable3[i])/32767.0*AD_CVEF - Setoff_ZoreVal;
		}
		else
			SampleValue3[i]= SampleTable3[i]/32767.0*AD_PVEF - Setoff_ZoreVal;
		
		if(SampleTable2[i]& 0x8000 )
		{
			SampleValue2[i] =(float)(65535-SampleTable2[i])/32767.0*AD_CVEF - Setoff_ZoreVal;
		}
		else
		{
			SampleValue2[i]= (float)SampleTable2[i]/32767.0*AD_PVEF - Setoff_ZoreVal;
		}
		if(SampleTable1[i]& 0x8000 )
		{
			SampleValue1[i] = (float)(65535-SampleTable1[i])/32767.0*AD_CVEF - Setoff_ZoreVal;
		
		}
		else
			SampleValue1[i]= (float)SampleTable1[i]/32767.0*AD_PVEF - Setoff_ZoreVal;
	}
}
//--------------------------------------------------------------
// NO MORE
//---------------------------------------------------------------
