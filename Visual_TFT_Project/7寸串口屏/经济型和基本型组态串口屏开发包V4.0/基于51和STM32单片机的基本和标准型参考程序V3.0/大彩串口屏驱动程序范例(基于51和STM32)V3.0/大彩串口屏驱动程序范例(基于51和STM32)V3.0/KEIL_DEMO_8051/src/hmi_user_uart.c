#include "hmi_user_uart.h"

void UartInit()
{
	SCON=0x50;     //8λUART��BPS�ɱ�,�����н��տ���λ
	TMOD |=0x20;   //��ʱ��1������ʽ2(8λ�Զ���װ��ʽ)
	PCON |=0x80;   //�����ʼӱ�
	TH1=0xFA;  
	TL1=0xFA;      //9600������ ��11.0592M 
	IE |=0X90;     //Enable Serial Interrupt 
	TR1=1;  
	//ES = 0;   
}

void  SendChar(uchar t) 
{
	SBUF=t;
	while(TI==0);
	TI=0;           
} 