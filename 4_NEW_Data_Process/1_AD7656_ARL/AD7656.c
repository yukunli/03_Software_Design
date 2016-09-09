

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
	//����&CpuTimer0, 150, 4.7619 ����Ƶ�� = 4.76u/150M  4.275
	ConfigCpuTimer(&CpuTimer0, 150, 8.0);   //�ڶ�ʱ���ڽ��в���,������1/(1.76us+prioed 0f AD read dataԼ3us)=210KHz
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
	CLR_ADCOV;   
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
void GetAD_Value(STRSampleTable *FourSampleTable,STRSampleValue *FourSampleValue)
{
	int tem = 0;
	CLR_ADCOV;   	//����ת���ź�
	DELAY_US(0.2);
	SET_ADCOV;
	DELAY_US(3);
	while(AD_BUSY); 
	if(Head_pointNum >= 0)  //ȥ��ͷ3����
	{
		for(tem = 4; tem > 0; tem--)
			FourSampleTable->SamTable4[SampleCount] = AD7656_BASIC; //��ȡ4·ADͨ������
		Head_pointNum --;
		SampleCount = 0;
	}
	else if(SampleCount < SAMP_COUNT_MAX)
	{
		FourSampleTable->SamTable1[SampleCount] = AD7656_BASIC; 	//��ȡ4·ADͨ������
		FourSampleTable->SamTable2[SampleCount] = AD7656_BASIC; 
		FourSampleTable->SamTable3[SampleCount] = AD7656_BASIC; 
		FourSampleTable->SamTable4[SampleCount] = AD7656_BASIC; 
//		FourSampleValue->SamValue1[SampleCount]=  _IQmpy(FourSampleTable->SamTable1[SampleCount],_IQ(0.0003051758));  //��ΧΪ20V
//		FourSampleValue->SamValue2[SampleCount]=  _IQmpy(FourSampleTable->SamTable1[SampleCount],_IQ(0.0003051758));
//		FourSampleValue->SamValue3[SampleCount]=  _IQmpy(FourSampleTable->SamTable1[SampleCount],_IQ(0.0003051758));
//		FourSampleTable->SamTable4[SampleCount]=  _IQmpy(FourSampleTable->SamTable1[SampleCount],_IQ(0.0003051758));
		SampleCount  ++;
		return;
	}
	else 
	{
		CLR_ADCOV; 
		STOP_SAMPLING();
		SampleCount = 0;
		SampleCount_Status_Flag = True;
		Head_pointNum = 2;
	}
}
/**************************************
 * Function: ������תfloat�� �� SampleTable3 update SampleValue3
 *************************************/
void AD_Data_Shift(STRSampleTable *FourSampleTable, STRSampleValue *FourSampleValue)
{
	register unsigned int i  = 0;
//	float Setoff_ZoreVal = 0;
	
//	for(i=0;i< SAMP_COUNT_MAX;i++)
//	{
//		FourSampleValue->SamValue4[i] = FourSampleTable->SamTable4[i]*0.0003051757812;
//	}
//		
//	for(i=0;i< SAMP_COUNT_MAX; i++ )
//	{
//		Setoff_ZoreVal += FourSampleValue->SamValue4[i];
//	}
//	Setoff_ZoreVal = Setoff_ZoreVal / SAMP_COUNT_MAX;

	for(i=0;i< BUF_SIZE1;i++)
	{		
		FourSampleValue->SamValue1[i]= FourSampleTable->SamTable1[i]*0.0003051758;
		if(i< BUF_SIZE3)
		{
			FourSampleValue->SamValue2[i] = FourSampleTable->SamTable2[i]*0.0003051758;
			FourSampleValue->SamValue3[i] = FourSampleTable->SamTable3[i]*0.0003051758;
		}
		else if( i>= BUF_SIZE3 && i< BUF_SIZE2)
		{
			FourSampleValue->SamValue2[i]= FourSampleTable->SamTable2[i]*0.0003051758;
		}
	}
}

//--------------------------------------------------------------
// NO MORE
//---------------------------------------------------------------
