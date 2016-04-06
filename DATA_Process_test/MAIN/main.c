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

#define test_LED	GpioDataRegs.GPADAT.bit.GPIO0
/*****************����ȫ�ֱ���*********************//*************************************************/
Uint16 ReceivedChar;
char *mesg;
char Timer_flag = 0;
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
//test
   EALLOW;
   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; // GPIO0 = GPIO0
   GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; 
   EDIS;
 //end test
	SCIC_Init();        // Initalize SCI for echoback
	OUTAD_Init(); 
    mesg = "welcome!\n\0";
    SCIC_msg(mesg);	
    START_SAMPLING();
	while(1)
	{	//test_LED = 0;
		if( SampleCount_Status_Flag == False && Timer_flag == 1 )  //ת��AD7656�Ĳ��� 
		{
			test_LED = 1;
			GetAD_Value();
			Timer_flag = 0;
			test_LED = 0;
		}
		else if(SampleCount_Status_Flag == True)   //��������������������һ���Ĵ���
		{
		 	AD_Data_Shift();
		 	DAL_Process(SampleValue2,BUF_SIZE1,Low_Filter2,DAL_OutPut1);
		 	while(1);
			//SampleCount_Status_Flag = False;
		 	//START_SAMPLING();
		 	
		}
	}
}
/*
 * Interrupt _ timer
 */
interrupt void ISRTimer0(void)
{   
  // 	if(Timer_flag ==1)
   	test_LED = 1;

   	Timer_flag = 1;
    CpuTimer0Regs.TCR.bit.TIF=1;   // ��ʱ����ָ��ʱ�䣬��־λ��λ�������־      
//    CpuTimer0Regs.TCR.bit.TRB=1;   // ����Timer0�Ķ�ʱ����
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
   	test_LED = 0;
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
 		case 1: 
 			SCIC_msg("\r\nHello lyk!\0");
 			break;
 		case 0:
 			for(j=0;j<6;j++)
 			{
 				SCIC_xmit('D');
 				DELAY_US(10);
 			}
 			break;
 		default: 
 			break;
 	}
 	ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;
 	ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;
 	PieCtrlRegs.PIEACK.all |= 0x100;
 }	
//===========================================================================
// No more.
//===========================================================================


