#include "ulitity.h"
#include "cmd_queue.h"

extern volatile  uint32 timer_tick_count;

#define TIME_TICK_10MS 10000

/**************************************************************************************************************
* 名    称： delay_ms
* 功    能： 延时n毫秒
* 入口参数： n-延时时间
* 出口参数： 无
***************************************************************************************************************/
void delay_ms(uint32 delay)
{
    uint32 tick = timer_tick_count;
    while(1)
    {
        if(timer_tick_count-tick>delay/10)
            break;
    }
}


//串口接收中断程序
void serial() interrupt 4
{
	if(RI)//接收到窗口数据
	{
		RI= 0;
		queue_push(SBUF);//压入到指令缓冲区
	}
}

//定时器初始化，10毫秒
void TimerInit (void)   
{           
	TMOD |= 0x01;   
	TH0 = (65536-TIME_TICK_10MS) /256; 
	TL0 = (65536-TIME_TICK_10MS) %256;

	ET0 = 1;
	TR0 = 1; 

	EA = 1;       
}


//定时器中断处理函数
void Time0_Int() interrupt 1
{
	TH0 = (65536-TIME_TICK_10MS) /256; 
	TL0 = (65536-TIME_TICK_10MS) %256;
	++timer_tick_count;
}
