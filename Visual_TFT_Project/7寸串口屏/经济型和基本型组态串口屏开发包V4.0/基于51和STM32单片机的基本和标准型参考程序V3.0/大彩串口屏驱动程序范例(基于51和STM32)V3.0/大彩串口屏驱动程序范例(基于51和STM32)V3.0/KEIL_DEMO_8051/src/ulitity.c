#include "ulitity.h"
#include "cmd_queue.h"

extern volatile  uint32 timer_tick_count;

#define TIME_TICK_10MS 10000

/**************************************************************************************************************
* ��    �ƣ� delay_ms
* ��    �ܣ� ��ʱn����
* ��ڲ����� n-��ʱʱ��
* ���ڲ����� ��
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


//���ڽ����жϳ���
void serial() interrupt 4
{
	if(RI)//���յ���������
	{
		RI= 0;
		queue_push(SBUF);//ѹ�뵽ָ�����
	}
}

//��ʱ����ʼ����10����
void TimerInit (void)   
{           
	TMOD |= 0x01;   
	TH0 = (65536-TIME_TICK_10MS) /256; 
	TL0 = (65536-TIME_TICK_10MS) %256;

	ET0 = 1;
	TR0 = 1; 

	EA = 1;       
}


//��ʱ���жϴ�����
void Time0_Int() interrupt 1
{
	TH0 = (65536-TIME_TICK_10MS) /256; 
	TL0 = (65536-TIME_TICK_10MS) %256;
	++timer_tick_count;
}
