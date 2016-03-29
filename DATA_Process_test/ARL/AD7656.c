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

float  SampleValue1[SAMPLE_COUNT];
float  SampleValue2[SAMPLE_COUNT];
float  SampleValue3[SAMPLE_COUNT];
float  SampleValue4[SAMPLE_COUNT];

void AD7656_ConfigInit(void)
{
	EALLOW;
	GpioCtrlRegs.GPAMUX2.bit.GPIO25=0;
	GpioCtrlRegs.GPADIR.bit.GPIO25=1;		//OUTPUT
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;  // XWE0
	GpioCtrlRegs.GPBDIR.bit.GPIO61=1;		//OUTPUT
	GpioCtrlRegs.GPBMUX2.bit.GPIO60=0; //ADBUSY
	GpioCtrlRegs.GPBDIR.bit.GPIO60=0;//INPUT
	GpioCtrlRegs.GPBQSEL2.bit.GPIO60= 0;
	EDIS;
} 

void OUTAD_Timer_Init(void)
{
	InitCpuTimers();   //For this example, only initialize the Cpu Timers
	#if(CPU_FRQ_150MHZ)
		ConfigCpuTimer(&CpuTimer0, 100, 9); //在定时器内进行采样,100MHZ,987US,采样率1/(987us+prioed 0f AD read data)1KHz
	#endif
	#if(CPU_FRQ_100MHZ)
		ConfigCpuTimer(&CpuTimer0, 100, 987); //在定时器内进行采样,100MHZ,987US,采样率1/(987us+prioed 0f AD read data)1KHz
	#endif
}

/*
 * Function: 初始化与采样有关的变量
 */
void OUTAD_Variable_Init(void)
{
	int i=0;
	
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
}

/*
 * Function: 数字量转float， 由 SampleTable4 update SampleValue3
 */
void AD_Data_Shift(void)
{
	int i,j;
	float Setoff_ZoreVal = 0;

	
	for(i=0;i<= SAMPLE_COUNT;i++)
	{
		if(SampleTable4[i]&0x8000) //postive
		{
			SampleValue4[i] = (65535-SampleTable4[i])/32767.0*AD_CVEF;    // it should be 0 because connected to GND		
		}
		else 
		SampleValue4[i] = SampleTable4[i]/32767.0*AD_PVEF;
	}
		
	#if 1
	for(j=0;j<=SAMPLE_COUNT; j++ )
	{
		Setoff_ZoreVal += SampleValue4[i];
	}
	Setoff_ZoreVal = Setoff_ZoreVal / SAMPLE_COUNT;
	#endif
	
	for(i=0;i<= SAMPLE_COUNT;i++)
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
