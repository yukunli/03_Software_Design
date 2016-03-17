/*
 * ˵������AD7656�ɼ������źţ��õ���·�źŲ���ֵ������������Ŵ����󣬵õ���·�źŵķ�ֵ
 * 
 * 
 * 
 */



#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "DATA_Process.h"
#include "ConstData_Table.h"
#include "SCI_Serial.h"
#include "AD7656.h"
/*****************����ȫ�ֱ���*********************//*************************************************/
Uint16 ReceivedChar;
char *msg;

/**************************************************/
interrupt void ISRTimer0(void);
interrupt void scic_isr(void);

/*********************������***********************/
/**************************************************/
void main()
{
// Step 1. Initialize System Control:
   InitSysCtrl();

// Step 2. Initalize GPIO:
   InitXintf16Gpio();	//zq

// Step 3. Clear all interrupts and initialize PIE vector table:
   DINT;

// Initialize the PIE control registers to their default state.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
	InitPieVectTable();
	
	 
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.SCIRXINTC = &scic_isr;
	PieVectTable.TINT0 = & ISRTimer0;
	EDIS;    // This is needed to disable write to EALLOW protected registers 
   
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   
    PieCtrlRegs.PIEIER8.bit.INTx5 = 1;	//SCIRCINTC
    IER |= M_INT8;
    
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   //timer0
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;  //timer0
    IER |= M_INT1;
	EINT; 
	ERTM; 

// user code 
	SCIC_Init();        // Initalize SCI for echoback
	OUTAD_Init(); 
	START_SAMPLING();
    msg = "\r\n\n\nHello yukun!\0";
    SCIC_msg(msg);	
	
    DAL_Process(SampleValue1,BUF_SIZE1,sin_wave1,cos_wave1,Low_Filter2,DAL_OutPut1 );
	
	
	while(1)
	{
		if( SampleCount_Status_Flag )
		{
			SampleCount_Status_Flag = False;
			
		 	AD_Data_Shift();
		 	
		// 	START_SAMPLING();
		 	
		}
	}
}
/*
 * Interrupt _ timer
 */
interrupt void ISRTimer0(void)
{   
	float test;	   	
   	CLR_ADCOV;   //����ת���ź�
	DELAY_US(1); //�����ʵ��ĵ�ƽ��ʱ
	SET_ADCOV;
	//GpioDataRegs.GPADAT.bit.GPIO0 = ~GpioDataRegs.GPADAT.bit.GPIO0;
		while(AD_BUSY); //�ȴ�ת������
		   
		SampleTable1[SampleCount]=AD7656_BASIC & 0xFFFF; //��ȡ4·ADͨ������
		SampleTable2[SampleCount]=AD7656_BASIC & 0xFFFF; 
		SampleTable3[SampleCount]=AD7656_BASIC & 0xFFFF; 
		SampleTable4[SampleCount]=AD7656_BASIC & 0xFFFF; 
		//SampleTable_None[SampleCount]=AD7656_BASIC & 0xFFFF; 
		//SampleTable_None[SampleCount]=AD7656_BASIC & 0xFFFF;
		
		#if 0 //test
		if( SampleTable2[SampleCount]& 0x8000 ) //
		{
			test = (float)(65535-SampleTable2[SampleCount])/32767.0*AD_CVEF; 	
		}
		else 
		    test = SampleTable2[SampleCount]/32767.0*AD_PVEF;   
		#endif

		SampleCount++;
		if( SampleCount >= SAMPLE_COUNT ) 
		{
			CLR_ADCOV; 
			SampleCount = 0;
			SampleCount_Status_Flag = True;
			STOP_SAMPLING();
		}
	
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    CpuTimer0Regs.TCR.bit.TIF=1;   // ��ʱ����ָ��ʱ�䣬��־λ��λ�������־      
    CpuTimer0Regs.TCR.bit.TRB=1;  // ����Timer0�Ķ�ʱ����
} 

/************************************
 * SCI����C�жϷ������
 */
 interrupt void scic_isr(void)
 {
 	Uint16 j,rdataC;
 	rdataC=ScicRegs.SCIRXBUF.all;
 	switch (rdataC)
 	{
 		case '1': 
 			SCIC_msg("\r\n\nHello lyk!\0");
 			break;
 		case '0':
 			for(j=0;j<6;j++)
 			{
 				SCIC_xmit('D');
 				DELAY_US(10);
 			}
 			break;
 		default: 
 			msg = "\r\nEnter a character: \0";
       		SCIC_msg(msg);
 			break;
 	}
 	ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;
 	ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;
 	PieCtrlRegs.PIEACK.all |= 0x100;
 }	
//===========================================================================
// No more.
//===========================================================================


