

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "AD7656.h"
#include "std_init.h"
#include "LED.h"
Uint16 SampleCount = 0;
identi_bool volatile SampleCount_Status_Flag; 
char  Head_pointNum = 3;
inline void AD7656_ConfigInit(void)
{
	EALLOW;
	GpioCtrlRegs.GPAMUX2.bit.GPIO24=0;
	GpioCtrlRegs.GPADIR.bit.GPIO24=1;		//OUTPUT
	
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;    // XWE0
	GpioCtrlRegs.GPADIR.bit.GPIO25=1;		//OUTPUT
	
	GpioCtrlRegs.GPAMUX2.bit.GPIO27=0;      //ADBUSY
	GpioCtrlRegs.GPADIR.bit.GPIO27=0;       //INPUT
	GpioCtrlRegs.GPAQSEL2.bit.GPIO27= 0;
	EDIS;
} 

inline void OUTAD_Timer_Init(void)
{
	InitCpuTimers();   //For this example, only initialize the Cpu Timers
	//理想&CpuTimer0, 150, 4.7619 采样频率 = 4.76u/150M  4.275 8.0
	ConfigCpuTimer(&CpuTimer0, 150, 6);   //在定时器内进行采样,
}

/*
 * Function: 初始化与采样有关的变量
 */
void OUTAD_Variable_Init(STRSampleTable *FourSampleTable, STRSampleValue *FourSampleValue)
{
	unsigned int i =0;
	for(i=0; i<SAMP_COUNT_MAX; i++)
	{
		FourSampleTable->SamTable1[i] = 0;
		FourSampleTable->SamTable2[i] = 0;
		FourSampleTable->SamTable3[i] = 0;
		FourSampleTable->SamTable4[i] = 0;
	}
	for(i = 0; i < BUF_SIZE1; i++)
	{
		FourSampleValue->SamValue1[i] = 0;
	}
	for(i = 0; i < BUF_SIZE2; i++)
	{
		FourSampleValue->SamValue2[i] = 0;
	}
	for(i = 0; i < BUF_SIZE3; i++)
	{
		FourSampleValue->SamValue3[i] = 0;
	}
	for(i = 0; i < BUF_SIZE4; i++)
	{
		FourSampleValue->SamValue4[i] = 0;
	}
	SampleCount = 0;
	SampleCount_Status_Flag = False;
}

/**************************
 * Function: AD7656 初始化
 *************************/
void OUTAD_Init(STRSampleTable *FourSampleTable, STRSampleValue *FourSampleValue)
{
	OUTAD_Timer_Init();
	OUTAD_Variable_Init(FourSampleTable,FourSampleValue);
	AD7656_ConfigInit();
	SET_ADRST;  
	CLR_ADCOV;   
	DELAY_US(100000);
	CLEAR_ADRST; 
	SET_ADCOV;
	DELAY_US(1000);
}

/**********************************
 * Function: 对ad7656进行采样和数据读取
 * 每次4个通道各读取一个数据
 * 由main()调用
 *********************************/
void GetAD_Value(STRSampleTable *FourSampleTable)
{
	int tem = 0;
	CLR_ADCOV;   	//启动转换信号
	DELAY_US(0.1);
	SET_ADCOV;
	DELAY_US(2);
	while(AD_BUSY); 
	if(Head_pointNum >= 0)  //去掉头3个点
	{
		for(tem = 4; tem > 0; tem--)
		{
			FourSampleTable->SamTable4[SampleCount] = AD7656_BASIC; //读取4路AD通道数据  
		}
		Head_pointNum --;
		SampleCount = 0;
	}
	else if((SampleCount < SAMP_COUNT_MAX) || (SampleCount > SAMP_COUNT_MAX))
	{
		//SIN_Off();
		FourSampleTable->SamTable1[SampleCount] = AD7656_BASIC; //读取4路AD通道数据
		tem++;
		FourSampleTable->SamTable2[SampleCount] = AD7656_BASIC; 
		tem++;
		FourSampleTable->SamTable3[SampleCount] = AD7656_BASIC;
		tem++;
		FourSampleTable->SamTable4[SampleCount] = AD7656_BASIC; 
		SampleCount ++;
		return;
	}
	else 
	{
		CLR_ADCOV; 
		STOP_SAMPLING();
		SampleCount = 0;
		SampleCount_Status_Flag = True;
		Head_pointNum = 3;
	}
}
/**************************************
 * Function: 数字量转float， 由 SampleTable3 update SampleValue3
 *************************************/
void AD_Data_Shift(STRSampleTable *FourSampleTable, STRSampleValue *FourSampleValue)
{
	unsigned int i  = 0;
	float Setoff_ZoreVal = 0;
	
	for(i=0;i< BUF_SIZE4;i++)
	{
		FourSampleValue->SamValue4[i] = FourSampleTable->SamTable4[i]/65536.0*AD_PVEF;
	}
		
	for(i=0;i< BUF_SIZE4; i++ )
	{
		Setoff_ZoreVal += FourSampleValue->SamValue4[i];
	}
	Setoff_ZoreVal = Setoff_ZoreVal / (BUF_SIZE4);

	for(i=0;i< BUF_SIZE1;i++)
	{		
		FourSampleValue->SamValue1[i]= (float)(FourSampleTable->SamTable1[i])/65536.0*AD_PVEF - Setoff_ZoreVal;
		if(i< BUF_SIZE3)
		{
			FourSampleValue->SamValue2[i]= (float)(FourSampleTable->SamTable2[i])/65536.0*AD_PVEF - Setoff_ZoreVal;
			FourSampleValue->SamValue3[i] = (float)(FourSampleTable->SamTable3[i])/65536.0*AD_PVEF - Setoff_ZoreVal;
		}
		else if( i>= BUF_SIZE3 && i< BUF_SIZE2)
		{
			FourSampleValue->SamValue2[i]= (float)(FourSampleTable->SamTable2[i])/65536.0*AD_PVEF - Setoff_ZoreVal;
		}
	}
}

//--------------------------------------------------------------
// NO MORE
//---------------------------------------------------------------
