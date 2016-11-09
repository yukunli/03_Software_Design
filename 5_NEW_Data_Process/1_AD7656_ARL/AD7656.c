

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
	DELAY_US(10000);
}

/**********************************
 * Function: ��ad7656���в��������ݶ�ȡ
 * ÿ��4��ͨ������ȡһ������
 * ��main()����
 *********************************/
void GetAD_Value(STRSampleTable *FourSampleTable)
{
	int tem = 0;
	CLR_ADCOV;   	//����ת���ź�
	DELAY_US(0.3);
	SET_ADCOV;
	DELAY_US(3.5);
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
		FourSampleTable->SamTable1[SampleCount] = AD7656_BASIC;  //��ȡ4·ADͨ������
		DELAY_US(0.1);
		FourSampleTable->SamTable2[SampleCount] = AD7656_BASIC;
		DELAY_US(0.1); 
		FourSampleTable->SamTable3[SampleCount] = AD7656_BASIC; 
		DELAY_US(0.1);
		FourSampleTable->SamTable4[SampleCount] = AD7656_BASIC; 
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
    unsigned int i  = 0;
	float Setoff_ZoreVal = 0;
	double const Trans_para = AD_PVEF/65536.0;
	
	for(i=0;i< BUF_SIZE4;i++)
	{
		FourSampleValue->SamValue4[i] = FourSampleTable->SamTable4[i]*Trans_para;
	}
		
	for(i=0;i< BUF_SIZE4; i++ )
	{
		Setoff_ZoreVal += FourSampleValue->SamValue4[i];
	}
	Setoff_ZoreVal = Setoff_ZoreVal / BUF_SIZE4 ;
	
	for(i=0;i< BUF_SIZE1;i++)
	{		
		FourSampleValue->SamValue1[i]= (FourSampleTable->SamTable1[i])*Trans_para- Setoff_ZoreVal;
	}
	for(i=0;i< BUF_SIZE2;i++)
	{
		FourSampleValue->SamValue2[i]= (FourSampleTable->SamTable2[i])*Trans_para - Setoff_ZoreVal;
	}
	for(i=0;i< BUF_SIZE3;i++)
	{
		FourSampleValue->SamValue3[i] = (FourSampleTable->SamTable3[i])*Trans_para - Setoff_ZoreVal;
	}
}

//--------------------------------------------------------------
// NO MORE
//---------------------------------------------------------------
