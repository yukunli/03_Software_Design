
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "SCI_Serial.h"

#define SCI_INTERRUPT  1   //
/*****************定义全局变量*********************//*************************************************/
Uint16 LoopCount;
Uint16 ErrorCount;
Uint16 ReceivedChar;
char *msg;
/**************************************************/
interrupt void scic_isr(void);
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
	
	#if( SCI_INTERRUPT )  
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.SCIRXINTC = &scic_isr;
	EDIS;    // This is needed to disable write to EALLOW protected registers 
   
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   
    PieCtrlRegs.PIEIER8.bit.INTx5 = 1;	//SCIRCINTC
    IER |= M_INT8;
	EINT; 
	ERTM; 
	#endif  
   
	LoopCount = 0;
    ErrorCount = 0;
 //   SCIC_fifo_init();	 // Initialize the SCI FIFO
    SCIC_Init();        // Initalize SCI for echoback

    msg = "\r\n\n\nHello yukun!\0";
    SCIC_msg(msg);

    msg = "\r\nYou will enter a character, and the DSP will echo it back! \n\0";
    SCIC_msg(msg);
    msg = "\r\nEnter a character: \0";
    SCIC_msg(msg);
	while(1)
	{
	   
	   
       #if( !SCI_INTERRUPT )
       // Wait for int character
       while(ScicRegs.SCIRXST.bit.RXRDY !=1) { } // wait for XRDY =1 for empty state

       // Get character
       ReceivedChar = ScicRegs.SCIRXBUF.all;

       // Echo character back
       msg = "  You sent: \0";
       SCIC_msg(msg);
       SCIC_xmit(ReceivedChar);
       LoopCount++;
      #endif 
	}
}

/*
 * Interrupt _ timer
 */
#if( SCI_INTERRUPT )
/************************************
 * SCI——C中断服务程序
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
#endif

//===========================================================================
// No more.
//===========================================================================


