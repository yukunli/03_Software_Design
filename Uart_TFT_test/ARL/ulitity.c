#include "ulitity.h"
#include "cmd_queue.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

/**************************************************************************************************************
* 名    称： delay_ms
* 功    能： 延时n毫秒
* 入口参数： n-延时时间
* 出口参数： 无
***************************************************************************************************************/
void delay_ms(uint32 delay)
{
    int i;
    for(i=0;i< delay;i++)
    {
    	DELAY_US(1000);
    }

}

#if( SCI_INTERRUPT )
/************************************
 * SCI——C中断服务程序
 */
interrupt void scic_isr(void)
{
	if(RI)//接收到窗口数据
	{
		RI= 0;
		queue_push(SBUF);//压入到指令缓冲区
	}
}	
#endif


