
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "AD7656.h"
#include "std_init.h"

Uint16 SampleCount = 0;
identi_bool volatile SampleCount_Status_Flag; 
char  Head_pointNum = 3;

inline void AD7656_ConfigInit(void)
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

inline void OUTAD_Timer_Init(void)
{
	InitCpuTimers();   //For this example, only initialize the Cpu Timers
	//����&CpuTimer0, 150, 4.762
	ConfigCpuTimer(&CpuTimer0, 150, 4.7619);   //�ڶ�ʱ���ڽ��в���,������1/(1.76us+prioed 0f AD read dataԼ3us)=210KHz
}

/*
 * Function: ��ʼ��������йصı���
 */
void OUTAD_Variable_Init(STRSampleTable *FourSampleTable, STRSampleValue *FourSampleValue)
{
	unsigned int i =0;
	for(i = 0; i < SAMP_COUNT_MAX; i++)
	{
		FourSampleTable->SamTable1[i] = 0;
		FourSampleTable->SamTable2[i] = 0;
		FourSampleTable->SamTable3[i] = 0;
		FourSampleTable->SamTable4[i] = 0;
		FourSampleValue->SamValue1[i] = 0;
		FourSampleValue->SamValue2[i] = 0;
		FourSampleValue->SamValue3[i] = 0;
		FourSampleValue->SamValue4[i] = 0;
	}
	SampleCount = 0;
	SampleCount_Status_Flag = False;
}

/**************************
 * Function: AD7656 ��ʼ��
 *************************/
void OUTAD_Init(STRSampleTable *FourSampleTable, STRSampleValue *FourSampleValue)
{
	OUTAD_Timer_Init();
	OUTAD_Variable_Init(FourSampleTable,FourSampleValue);
	AD7656_ConfigInit();
	SET_ADRST;  
	CLR_ADCOV;   //����ת���ź�CLR_ADCOV
	DELAY_US(100000);
	CLEAR_ADRST; 
	SET_ADCOV;
	DELAY_US(1000);
}

/**********************************
 * Function: ��ad7656���в��������ݶ�ȡ
 * ÿ��4��ͨ������ȡһ������
 * ��main()����
 *********************************/
void GetAD_Value(STRSampleTable *FourSampleTable)
{
	unsigned int tem = 0;
	CLR_ADCOV;   	//����ת���ź�
	DELAY_US(0.3);
	SET_ADCOV;
	while(AD_BUSY); 
	if(Head_pointNum >= 0)  //ȥ��ͷ3����
	{
		for(tem = 6; tem > 0; tem--)
			FourSampleTable->SamTable4[SampleCount] = AD7656_BASIC; //��ȡ4·ADͨ������
		Head_pointNum --;
		SampleCount = 0;
	}
	else if(SampleCount < SAMP_COUNT_MAX)
	{
		FourSampleTable->SamTable1[SampleCount] = AD7656_BASIC; //��ȡ4·ADͨ������
		FourSampleTable->SamTable2[SampleCount] = AD7656_BASIC; 
		FourSampleTable->SamTable3[SampleCount] = AD7656_BASIC; 
		FourSampleTable->SamTable4[SampleCount] = AD7656_BASIC; 
		tem = AD7656_BASIC;
		tem = AD7656_BASIC;
		SampleCount  ++;
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
 * Function: ������תfloat�� �� SampleTable3 update SampleValue3
 *************************************/
void AD_Data_Shift(STRSampleTable *FourSampleTable, STRSampleValue *FourSampleValue)
{
	register unsigned int i  = 0;
	float Setoff_ZoreVal = 0;
	
	for(i=0;i< SAMP_COUNT_MAX;i++)
	{
		if(FourSampleTable->SamTable4[i]&0x8000) //postive
		{
			FourSampleValue->SamValue4[i] = (65535-FourSampleTable->SamTable4[i])/32767.0*AD_CVEF;    // it should be 0 because connected to GND		
		}
		else 
		FourSampleValue->SamValue4[i] = FourSampleTable->SamTable4[i]/32767.0*AD_PVEF;
	}
		
	for(i=0;i< SAMP_COUNT_MAX; i++ )
	{
		Setoff_ZoreVal += FourSampleValue->SamValue4[i];
	}
	Setoff_ZoreVal = Setoff_ZoreVal / SAMP_COUNT_MAX;

	
	for(i=0;i< SAMP_COUNT_MAX;i++)
	{	
		if(FourSampleTable->SamTable3[i]& 0x8000 )
		{
			FourSampleValue->SamValue3[i] = (65535-FourSampleTable->SamTable3[i])/32767.0*AD_CVEF - Setoff_ZoreVal;
		}
		else
			FourSampleValue->SamValue3[i]= FourSampleTable->SamTable3[i]/32767.0*AD_PVEF - Setoff_ZoreVal;
		
		if(FourSampleTable->SamTable2[i]& 0x8000 )
		{
			FourSampleValue->SamValue2[i] =(float)(65535-FourSampleTable->SamTable2[i])/32767.0*AD_CVEF - Setoff_ZoreVal;
		}
		else
		{
			FourSampleValue->SamValue2[i]= (float)FourSampleTable->SamTable2[i]/32767.0*AD_PVEF - Setoff_ZoreVal;
		}
		if(FourSampleTable->SamTable1[i]& 0x8000 )
		{
			FourSampleValue->SamValue1[i] = (float)(65535-FourSampleTable->SamTable1[i])/32767.0*AD_CVEF - Setoff_ZoreVal;
		
		}
		else
			FourSampleValue->SamValue1[i]= (float)FourSampleTable->SamTable1[i]/32767.0*AD_PVEF - Setoff_ZoreVal;
	}
}

//--------------------------------------------------------------
// NO MORE
//---------------------------------------------------------------
