/*
 * code in 2015/12/19,in freescale
 * use the SCIC to transtale data by uart
 * don't need configration the IO
 * 1 stop bit,  No loopback no parity,8 char bits,9600/19200
 */
#ifndef SCI_SERIAL_H_
#define SCI_SERIAL_H_


#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define SCI_BAUD_9600   0 
#define SCI_BAUD_19200  1
#define SCI_BAUD_115200  0

extern void SCIC_Init(void);
extern void SCIC_xmit(int a);
extern void SCIC_msg(char * msg);
extern void SCIC_fifo_init(void);


#endif /*SCI_SERIAL_H_*/
