#include "hmi_user_uart.h"
#include "SCI_Serial.h"

void UartInit()
{
	SCIC_Init();
}

void  SendChar(uchar t) 
{
   SCIC_xmit(t);     
} 
