#include "hmi_user_uart.h"

void UartInit()
{
	SCON=0x50;     //8位UART，BPS可变,允许串行接收控制位
	TMOD |=0x20;   //定时器1工作方式2(8位自动重装方式)
	PCON |=0x80;   //波特率加倍
	TH1=0xFA;  
	TL1=0xFA;      //9600波特率 ，11.0592M 
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