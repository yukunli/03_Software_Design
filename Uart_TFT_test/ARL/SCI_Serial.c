/*
 * code in 2015/12/19,in freescale
 */
 #include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
 #include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
 #include "SCI_Serial.h"
 
/*
 * SCI for Uart
 */
void SCIC_IO_Init(void)
{
	InitScicGpio();
}
void SCIC_Init(void)
{
    // Note: Clocks were turned on to the SCIC peripheral
    // in the InitSysCtrl() function
	SCIC_IO_Init();
 	ScicRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
	ScicRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
	ScicRegs.SCICTL2.all =0x0003;
	ScicRegs.SCICTL2.bit.TXINTENA = 1;
	ScicRegs.SCICTL2.bit.RXBKINTENA =1;
	
	#if (CPU_FRQ_150MHZ && SCI_BAUD_9600)
	      ScicRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 37.5MHz.
	      ScicRegs.SCILBAUD    =0x00E7;		
	#endif
	#if (CPU_FRQ_150MHZ && SCI_BAUD_19200) //@LSPCLK = 37.5MHz
	      ScicRegs.SCIHBAUD    =0x0000;  // 19200 baud,actual baud=19211,Error=0.06% @LSPCLK = 37.5MHz.
	      ScicRegs.SCILBAUD    =0x00F3;		
	#endif
	#if (CPU_FRQ_150MHZ && SCI_BAUD_115200) //@LSPCLK = 37.5MHz
	      ScicRegs.SCIHBAUD    =0x0000;  // 115200 baud,actual baud=19211,Error=0.75% @LSPCLK = 37.5MHz.
	      ScicRegs.SCILBAUD    =0x0028;		
	#endif
	#if (CPU_FRQ_100MHZ && SCI_BAUD_9600)  //@LSPCLK = 20MHz.
      ScicRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 20MHz.
      ScicRegs.SCILBAUD    =0x0044;
	#endif
	
	ScicRegs.SCICTL1.all =0x23;  // Relinquish SCI from Reset
}
/*
 * Transmit a character from the SCI
 */ 
void SCIC_xmit(char a)
{
    while (ScicRegs.SCICTL2.bit.TXRDY == 0) {}
    ScicRegs.SCITXBUF=a;

}

void SCIC_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        SCIC_xmit(msg[i]);
        i++;
    }
}

// Initalize the SCI FIFO
void SCIC_fifo_init(void)
{
    ScicRegs.SCIFFTX.all=0x8000;
//    ScicRegs.SCIFFRX.all=0x204f;
//    ScicRegs.SCIFFCT.all=0x0;
}
//===========================================================================
// No more.
//===========================================================================
