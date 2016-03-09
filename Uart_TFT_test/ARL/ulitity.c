#include "ulitity.h"
#include "cmd_queue.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

/**************************************************************************************************************
* ��    �ƣ� delay_ms
* ��    �ܣ� ��ʱn����
* ��ڲ����� n-��ʱʱ��
* ���ڲ����� ��
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
 * SCI����C�жϷ������
 */
interrupt void scic_isr(void)
{
	if(RI)//���յ���������
	{
		RI= 0;
		queue_push(SBUF);//ѹ�뵽ָ�����
	}
}	
#endif


