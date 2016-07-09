/************************************版权申明********************************************
**                             广州大彩光电科技有限公司
**                             http://www.gz-dc.com
--------------------------------------------------------------------------------------
                                  使用必读
   hmi_user_uart.c中的串口发送接收函数共3个函数：串口初始化Uartinti()、发送1个字节SendChar()、
   发送字符串SendStrings().若移植到其他平台，需要修改底层寄
   存器设置,但禁止修改函数名称，否则无法与HMI驱动库(hmi_driver.c)匹配。
--------------------------------------------------------------------------------------*/

#include "hmi_user_uart.h"
/****************************************************************************
* 名    称： UartInit()
* 功    能： 串口初始化
* 入口参数： 无
* 出口参数： 无
****************************************************************************/

void UartInit(uint32 BaudRate)
{
    InitScicGpio();
    ScicRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
	ScicRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
	ScicRegs.SCICTL2.all =0x0003;
	ScicRegs.SCICTL2.bit.TXINTENA = 1;
	ScicRegs.SCICTL2.bit.RXBKINTENA =1;
	switch(BaudRate)
	{
		case 9600 :  
			ScicRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 37.5MHz.
	      	ScicRegs.SCILBAUD    =0x00E7;
	      	break;
		case 19200 :
			ScicRegs.SCIHBAUD    =0x0000;  // 19200 baud,actual baud=19211,Error=0.06% @LSPCLK = 37.5MHz.
	      	ScicRegs.SCILBAUD    =0x00F3;
	      	break;
	    case 115200 :
	    	ScicRegs.SCIHBAUD    =0x0000;  // 115200 baud,actual baud=19211,Error=0.75% @LSPCLK = 37.5MHz.
	      	ScicRegs.SCILBAUD    =0x0028;
	      	break;
	    default : break;
	}
	ScicRegs.SCICTL1.all =0x23;  // Relinquish SCI from Reset
}

/*****************************************************************
* 名    称： SendChar()
* 功    能： 发送1个字节
* 入口参数： t  发送的字节
* 出口参数： 无
 *****************************************************************/
void  SendChar(uchar t)
{
    while (ScicRegs.SCICTL2.bit.TXRDY == 0) {}
    ScicRegs.SCITXBUF = t;
}
