
#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "stdio.h"

#define SCI_INTERRUPT  1   

/*****************定义全局变量*********************//*************************************************/
uint8 cmd_buffer[CMD_MAX_SIZE];
Water_Param gSystem_WaterParam = {12.0,1,1.66,22.3,0};  //与串口屏交互的系统水分仪参数
Water_Value gSystem_WaterValue = {5.20, 5.21, 32.76};
/**************************************************/
interrupt void scic_isr(void);

/*********************主程序***********************/
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
 
	/*串口初始化,波特率设置为115200*/
	UartInit(115200);
	/*清空串口接收缓冲区*/
	queue_reset();
	/*延时等待串口屏初始化完毕,必须等待300ms*/
	DELAY_US(300000);
	InitUI(&gSystem_WaterParam);  //使串口屏参数界面显示系统默认参数
	while(1)
	{
	 	size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE); //从缓冲区中获取一条指令        
		if(size > 0) //接收到指令
		{
			ProcessMessage((PCTRL_MSG)cmd_buffer, size, &gSystem_WaterParam); //指令处理
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
 * SCI——C中断服务程序
 */
 interrupt void scic_isr(void)
 {
 	uint8 rdataC;
 	rdataC = ScicRegs.SCIRXBUF.all;
 	queue_push(rdataC);//压入到指令缓冲区

 	ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;
 	ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;
 	PieCtrlRegs.PIEACK.all |= 0x100;
 }	
 
//===========================================================================
// No more.
//===========================================================================


