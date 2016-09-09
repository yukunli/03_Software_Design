#ifndef _USER_UART__
#define _USER_UART__

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  "std_init.h"
#define uchar    unsigned char
#define uint8    unsigned char
#define uint16   unsigned short int
#define uint32   unsigned long
#define int16    short int
#define int32    long

/****************************************************************************
* ��    �ƣ� UartInit()
* ��    �ܣ� SCIC���ڳ�ʼ��
* ��ڲ����� ��
* ���ڲ����� ��
****************************************************************************/
void UartInit(uint32 Baudrate);

/*****************************************************************
* ��    �ƣ� SendChar()
* ��    �ܣ� ����1���ֽ�
* ��ڲ����� t  ���͵��ֽ�
* ���ڲ����� ��
 *****************************************************************/
void SendChar(uchar t);
void Send_msg(char *msg);
void SendValuetoLabview(LabView_Data* Test_LabviewData);

#endif
