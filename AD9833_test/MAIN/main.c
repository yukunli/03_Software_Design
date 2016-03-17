
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "AD9833.h"


/*****************定义全局变量*********************//*************************************************/
// Uint16 RamfuncsLoadStart;
// Uint16 RamfuncsLoadEnd;
// Uint16 RamfuncsRunStart;
/**************************************************/
/*********************主程序***********************/
/**************************************************/
void main()
{
	// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example
   InitXintf16Gpio();	//zq

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
   InitPieVectTable();
   MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart); 
   InitFlash();
   
   
   AD9833_configinit();
   AD9833_Reset(CSIN_Channel_1);
   delay(9000);

   AD9833_Outdata(CSIN_Channel_1,CH1_OUT_FRE,0,2,0 ); //第一片9833，,6KHz,频率寄存器0，正弦波输出
   delay(9000);
  // AD9833_Reset(CSIN_Channel_1);

	while(1)
	{
	
	}
}

//===========================================================================
// No more.
//===========================================================================


