/************************************版权申明********************************************
**                             广州大彩光电科技有限公司                                
**                             http://www.gz-dc.com
**-----------------------------------文件信息--------------------------------------------
** 文件名称:   hmi_user_uart.c 
** 修改时间:   2011-05-18
** 文件说明:   用户MCU串口驱动函数库
** 技术支持：  Tel: 020-22077476  Email: hmi@gz-dc.com  
**--------------------------------------------------------------------------------------*/
        
/**--------------------------------------------------------------------------------------    
                                  使用必读                      
   hmi_user_uart.c中的串口发送接收函数共3个函数：串口初始化Uartinti()、发送1个字节SendChar()、
   发送字符串SendStrings().目前暂时只提供8051驱动平台，如果用户MCU非8051平台，需要修改底层寄
   存器设置,但禁止修改函数名称，否则无法与HMI驱动库(hmi_driver.c)匹配。 
**--------------------------------------------------------------------------------------*/

#include "hmi_user_uart.h"

/*----------------------------------------------------------------------------------------
**                          1. 基于8051平台串口驱动
*----------------------------------------------------------------------------------------

/****************************************************************************
* 名    称： UartInit()
* 功    能： 串口初始化
* 入口参数： 无      
* 出口参数： 无
****************************************************************************/
void UartInit(uint16_t BaudRate)
{ 
	GPIO_InitTypeDef        GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//  /* Configure USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	USART_DeInit(USART1);//复位USART1	  
	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode =   USART_Mode_Tx|USART_Mode_Rx;

	/* USART configuration */
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //接收中断使能

	/* Enable USART */
	USART_Cmd(USART1, ENABLE);   
  }
/*****************************************************************
* 名    称： SendChar()
* 功    能： 发送1个字节
* 入口参数： t  发送的字节       
* 出口参数： 无                  
 *****************************************************************/
void  SendChar(uchar t) 
 {
		USART_SendData(USART1,t);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);         
 } 
/*****************************************************************
* 名    称： SendStrings()
* 功    能： 发送字符串
* 入口参数： str  发送的字符串     
* 出口参数： 无               
 *****************************************************************/

 void SendStrings(uchar *str)
 {
     while(*str)
	 {
	  SendChar(*str);
	  str++;
	 }
 } 


