
#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "stdio.h"

#define SCI_INTERRUPT  1   

/*****************����ȫ�ֱ���*********************//*************************************************/
uint8 cmd_buffer[CMD_MAX_SIZE];
Water_Param gSystem_WaterParam = {12.0,1,1.66,22.3,0};  //�봮����������ϵͳˮ���ǲ���
Water_Value gSystem_WaterValue = {5.20, 5.21, 32.76};
/**************************************************/
interrupt void scic_isr(void);

/*********************������***********************/
/**************************************************/
void main(void)
{
	qsize  size = 0;
	
// Step 1. Initialize System Control:
   InitSysCtrl();
// Step 2. Initalize GPIO:
   InitXintf16Gpio();	//zq
// Step 3. Clear all interrupts and initialize PIE vector table:
   DINT;
// Initialize the PIE control registers to their default state.
   InitPieCtrl();
// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;
// Initialize the PIE vector table with pointers to the shell Interrupt
	InitPieVectTable();
	
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.SCIRXINTC = &scic_isr;
	EDIS;    // This is needed to disable write to EALLOW protected registers 
   
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   
    PieCtrlRegs.PIEIER8.bit.INTx5 = 1;	//SCIRCINTC
    IER |= M_INT8;
	EINT; 
	ERTM; 
 
	/*���ڳ�ʼ��,����������Ϊ115200*/
	UartInit(115200);
	/*��մ��ڽ��ջ�����*/
	queue_reset();
	/*��ʱ�ȴ���������ʼ�����,����ȴ�300ms*/
	DELAY_US(300000);
	InitUI(&gSystem_WaterParam);  //ʹ����������������ʾϵͳĬ�ϲ���
	while(1)
	{
	 	size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE); //�ӻ������л�ȡһ��ָ��        
		if(size > 0) //���յ�ָ��
		{
			ProcessMessage((PCTRL_MSG)cmd_buffer, size, &gSystem_WaterParam); //ָ���
		}
		DELAY_US(300000);		
		if(1)
		{		
			UpdateUI(&gSystem_WaterValue);
		}
		DELAY_US(300000);
		DELAY_US(300000);
	}
}


/************************************
 * SCI����C�жϷ������
 */
 interrupt void scic_isr(void)
 {
 	uint8 rdataC;
 	rdataC = ScicRegs.SCIRXBUF.all;
 	queue_push(rdataC);//ѹ�뵽ָ�����

 	ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;
 	ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;
 	PieCtrlRegs.PIEACK.all |= 0x100;
 }	
 
//===========================================================================
// No more.
//===========================================================================


