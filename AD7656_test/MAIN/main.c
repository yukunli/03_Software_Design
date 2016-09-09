
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "AD7656.h"
//#include "Interrupt_Init.h"

/*****************定义全局变量*********************//*************************************************/

/**************************************************/
interrupt void ISRTimer0(void);

/*********************主程序***********************/
/**************************************************/
void main(void)
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
	PieVectTable.TINT0 = & ISRTimer0;
	EDIS;    //This is needed to disable write to EALLOW protected registers
   
   
    IER |= M_INT1;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   //timer0
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;  //timer0
	EINT; 
	ERTM; 
	
	OUTAD_Init(); 
	START_SAMPLING();
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
   	CLR_ADCOV;   //启动转换信号
	DELAY_US(0.3); //给予适当的电平延时
	SET_ADCOV;
	DELAY_US(1);
	//GpioDataRegs.GPADAT.bit.GPIO0 = ~GpioDataRegs.GPADAT.bit.GPIO0;
		while(AD_BUSY); //等待转换结束
		   
		SampleTable1[SampleCount]=AD7656_BASIC & 0xFFFF; //读取6路AD通道数据
		SampleTable2[SampleCount]=AD7656_BASIC & 0xFFFF; 
		SampleTable3[SampleCount]=AD7656_BASIC & 0xFFFF; 
		SampleTable4[SampleCount]=AD7656_BASIC & 0xFFFF; 
		SampleTable_None[SampleCount]=AD7656_BASIC & 0xFFFF; 
		SampleTable_None[SampleCount]=AD7656_BASIC & 0xFFFF;
		
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
    CpuTimer0Regs.TCR.bit.TIF=1;   // 定时到了指定时间，标志位置位，清除标志      
    CpuTimer0Regs.TCR.bit.TRB=1;  // 重载Timer0的定时数据
} 

//===========================================================================
// No more.
//===========================================================================


