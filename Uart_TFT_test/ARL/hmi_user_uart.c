/************************************��Ȩ����********************************************
**                             ���ݴ�ʹ��Ƽ����޹�˾
**                             http://www.gz-dc.com
--------------------------------------------------------------------------------------
                                  ʹ�ñض�
   hmi_user_uart.c�еĴ��ڷ��ͽ��պ�����3�����������ڳ�ʼ��Uartinti()������1���ֽ�SendChar()��
   �����ַ���SendStrings().����ֲ������ƽ̨����Ҫ�޸ĵײ��
   ��������,����ֹ�޸ĺ������ƣ������޷���HMI������(hmi_driver.c)ƥ�䡣
--------------------------------------------------------------------------------------*/

#include "hmi_user_uart.h"
/****************************************************************************
* ��    �ƣ� UartInit()
* ��    �ܣ� ���ڳ�ʼ��
* ��ڲ����� ��
* ���ڲ����� ��
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
* ��    �ƣ� SendChar()
* ��    �ܣ� ����1���ֽ�
* ��ڲ����� t  ���͵��ֽ�
* ���ڲ����� ��
 *****************************************************************/
void  SendChar(uchar t)
{
    while (ScicRegs.SCICTL2.bit.TXRDY == 0) {}
    ScicRegs.SCITXBUF = t;
}
