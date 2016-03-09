/*! 
 *  \file hmi_user_uart.h
 *  \brief ���ڳ�ʼ�������ݷ���
 *  \version 1.0
 *  \date 2012-2015
 */

#ifndef _USER_UART__
#define _USER_UART__

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define uchar    unsigned char
#define uint8    unsigned char
#define uint16   unsigned short int
#define uint32   unsigned long
#define int16    short int
#define int32    long

/*! 
 *  \brief  ��ʼ������
 */
void UartInit();

/*! 
 *  \brief  ���ڷ��͵����ֽ�
 *  \param  c ����
 */
void  SendChar(uchar c);


#endif
