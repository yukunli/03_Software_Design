

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

void Send_msg(char *msg)
{
    unsigned int i=0;

    while(msg[i] != '\0')
    {
        SendChar(msg[i]);
        i++;
    }
}
/*******************************************************************
 * 函数名称:SendValuetoLabview()
 * 功能：将计算得到的模拟量值发送给Labview
 * 入口参数： float 模拟量数值
 * 如发送的值为：1.223，则一次发送1 2 2 3
 *            1.23， 则依次发送 1 2 3 0
 *            12.33，则依次发送12 3 3  0 
 * ***************************************************************/
void SendValuetoLabview(LabView_Data* Test_LabviewData)
{
	unsigned long int_value = 0;
	int k = 0;
	uchar aa[20] = {0};	
	int_value = Test_LabviewData->L19Value*1000; //数值的最小分辨率为1mv
	aa[1] = int_value/1000;
	aa[2] = (int_value/100)%10;
	aa[3] = (int_value/10)%10;
	aa[4] = int_value%10;
	aa[0] = 0xff;
	int_value = Test_LabviewData->L17Value*1000; //数值的最小分辨率为1mv
	aa[6] = int_value/1000;
	aa[7] = (int_value/100)%10;
	aa[8] = (int_value/10)%10;
	aa[9] = int_value%10;
	aa[5] = 0xff;
	int_value = Test_LabviewData->L22Value*1000; //数值的最小分辨率为1mv
	aa[11] = int_value/1000;
	aa[12] = (int_value/100)%10;
	aa[13] = (int_value/10)%10;
	aa[14] = int_value%10;
	aa[10] = 0xff;
	int_value = Test_LabviewData->temperature*1000; //数值的最小分辨率为1度
	aa[16] = int_value/1000;
	aa[17] = (int_value/100)%10;
	aa[18] = (int_value/10)%10;
	aa[19] = int_value%10;
	aa[15] = 0xff;
	for(k=0;k<20;k++)
	{
		SendChar(aa[k]);
	}
}

//no more
