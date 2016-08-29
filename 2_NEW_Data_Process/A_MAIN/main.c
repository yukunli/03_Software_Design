/*
 * 说明：由AD7656采集正弦信号，得到三路信号采样值，经数字锁相放大器后，得到三路信号的幅值
 * 
 */
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "DATA_Process.h"
#include "AD7656.h"
#include "hmi_user_uart.h"
#include "AD9833.h"
#include "LED.h"
#include "DS18B20.h"
#include "cmd_process.h"
#include "cmd_queue.h"
/*****************定义全局变量*********************/
STRSampleTable gSampleTable;  //全局 sample Table
STRSampleValue gSampleValue;  //全局 Sample Value
STRDalOutPut   gDalOutPut;    //全局 DalOutPut
uint8 cmd_buffer[CMD_MAX_SIZE];
Water_Param gSystem_WaterParam = {12.0,1,1.66,22.3,0};  //与串口屏交互的系统水分仪参数
Water_Value gSystem_WaterValue = {5.20, 5.21, 32.76};
LabView_Data Test_gSystem_LabviewData = {1.11,1.11,1.11,25.0};
unsigned char Timer_flag = 0;
float Cross_OutPut[2*BUF_SIZE1-1] = {0};
/**************************************************/
interrupt void ISRTimer0(void);
interrupt void scic_isr(void);
void InitXintf(void);
/*********************主程序***********************/
/**************************************************/
void main()
{    
	/*****************临时的全局变量******************************/
	qsize  size = 0;
// Step 1. Initialize System Control:
	InitSysCtrl();
	InitXintf();
// Step 2. Initalize GPIO:
	//InitXintf16Gpio();	//zq

// Step 3. Clear all interrupts and initialize PIE vector table:
	DINT;

// Initialize the PIE control registers to their default state.
	InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
	InitPieVectTable();
// 下载程序到Flash
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart); 
	InitFlash();
	 
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.SCIRXINTC = &scic_isr;
	PieVectTable.TINT0 = & ISRTimer0;
	EDIS;    // This is needed to disable write to EALLOW protected registers 
   
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   
    PieCtrlRegs.PIEIER8.bit.INTx5 = 1;	//SCIRCINTC
   // IER |= M_INT8; 	//使能SCI_C中断
    
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   //timer0
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;  //timer0
    IER |= M_INT1;	 //使能AD采样定时器
	EINT;   //使能中断
	ERTM; 	//使能调试事件

	//LED初始化
	LED_IOinit();
	
	//初始化AD9833正弦发生器
	AD9833_configinit();
	AD9833_Reset(CSIN_Channel_1);
	AD9833_Reset(CSIN_Channel_2);
	AD9833_Reset(CSIN_Channel_3);
	delay(1000);  		//必须保证足够的延时
	//初始化SCIC（UART_C）
	UartInit(115200);        // Initalize SCI for echoback, 波特率是115200
		
	//初始化AD7656
	OUTAD_Init(&gSampleTable, &gSampleValue); 
	
	//FTF屏指令缓存区清空
	//queue_reset();
	
	
	//启动AD9833正弦激励信号输出
	AD9833_Outdata(CSIN_Channel_1,CH1_OUT_FRE,0,2,0 ); //第一片9833，,5KHz,频率寄存器0，正弦波输出
    delay(200);      
    AD9833_Outdata(CSIN_Channel_2,CH2_OUT_FRE,0,2,0 ); //第二片9833，,6KHz,频率寄存器0，正弦波输出
    delay(200);
    AD9833_Outdata(CSIN_Channel_3,CH3_OUT_FRE,0,2,0 ); //第三片9833，,7KHz,频率寄存器0，正弦波输出
    delay(100);
    /*
    // 蜂鸣器示响
    Bell_Didadi();
    */
	//温度控制部分初始化
	TEM_Getinit();
    /*
    //初始化FTF屏界面
    DELAY_US(10000);
    InitUI(&gSystem_WaterParam);  //使串口屏参数界面显示系统默认参数
    
    //启动风扇
    FAN_Start();
    */
	//启动AD7656采样
    START_SAMPLING();
	while(1)
	{	
		//LED_Core_On();
		
		if( Timer_flag == 1 && SampleCount_Status_Flag == False)  //转换AD7656的采样 
		{
			//进行点采样
			GetAD_Value(&gSampleTable);  
			Timer_flag = 0;
			SIN_Off(); 
		}
		else if(SampleCount_Status_Flag == True)   //采样序列已满，进行下一步的处理
		{
			//此处打开其他中断
			Timer_flag = 0;
			IER |= M_INT8; 	//使能SCI_C中断
					
		 	AD_Data_Shift(&gSampleTable, &gSampleValue); 	//AD采样值转换为模拟量
		 	
		 	DAL_Process((gSampleValue.SamValue1),BUF_SIZE1,Cross_OutPut);	//数字相关运算
		 	LinearConvolution(BUF_SIZE1,LOWFILT_SIZE,Cross_OutPut,Low_Filter1,gDalOutPut.DAL_OutPut1);  //线性卷积
		 	
		 	DAL_Process((gSampleValue.SamValue2),BUF_SIZE2,Cross_OutPut);	//数字相关运算
		 	LinearConvolution(BUF_SIZE2,LOWFILT_SIZE,Cross_OutPut,Low_Filter1,gDalOutPut.DAL_OutPut2);  //线性卷积
		 	
		 	DAL_Process((gSampleValue.SamValue3),BUF_SIZE3,Cross_OutPut);	//数字相关运算
		 	LinearConvolution(BUF_SIZE3,LOWFILT_SIZE,Cross_OutPut,Low_Filter1,gDalOutPut.DAL_OutPut3);  //线性卷积
		 	
		 	//计算单路通道的信号幅值
		 	Test_gSystem_LabviewData.L17Value = Single_AmpValue(gDalOutPut.DAL_OutPut1,BUF_SIZE1 );
		 	Test_gSystem_LabviewData.L19Value = Single_AmpValue(gDalOutPut.DAL_OutPut2,BUF_SIZE2 );
		 	Test_gSystem_LabviewData.L22Value = Single_AmpValue(gDalOutPut.DAL_OutPut3,BUF_SIZE3 );
		 	
		 	//利用拟合公式计算当前瞬时水分值
			gSystem_WaterValue.SoonWaterValue = 0.22;
			
		 	//Red LED 闪烁
		 	LED_Red_Flash();
		 	
		 	//Blue LED 闪烁
		 	LED_Blue_Flash();
		 	
		 	// 温度采集
		 	Test_gSystem_LabviewData.temperature = get_temp();
		 	
		 	// PID温度调节控制
		 	
		 	//将单路通道的信号幅值发到Labview(或PC端)
		 	SendValuetoLabview(&Test_gSystem_LabviewData);
		 	/*
		 	//处理FTF串口屏消息
		 	size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE); //从缓冲区中获取一条指令        
			if(size > 0) //接收到指令
			{
				ProcessMessage((PCTRL_MSG)cmd_buffer, size, &gSystem_WaterParam); //指令处理
			}				
			UpdateUI(&gSystem_WaterValue);
			*/
		 	while(1);
		 	
		 	
		 	//此处关闭其他中断
		 	IER &= ~M_INT8; 	//禁止SCI_C中断
			SampleCount_Status_Flag = False;
		 	START_SAMPLING();
		}  
	}
}
/**********************************
 * Interrupt _ timer
 *********************************/
interrupt void ISRTimer0(void)
{   SIN_On();
 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    CpuTimer0Regs.TCR.bit.TIF=1;   // 定时到了指定时间，标志位置位，清除标志 
    Timer_flag = 1;     
    CpuTimer0Regs.TCR.bit.TRB=1;   // 重载Timer0的定时数据   
    
} 

/************************************
 * SCI——C中断服务程序
 ***********************************/
 interrupt void scic_isr(void)
 {
 	uint8 rdataC = 0;
 	rdataC = ScicRegs.SCIRXBUF.all;
 	queue_push(rdataC);//压入到指令缓冲区
 	ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;
 	ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;
 	PieCtrlRegs.PIEACK.all |= 0x100;
 }	
 
//===========================================================================
// No more.
//===========================================================================


