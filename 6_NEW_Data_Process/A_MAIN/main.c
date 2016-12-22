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

STRSampleTable gSampleTable;     //全局 sample Table
STRSampleValue gSampleValue;     //全局 Sample Value
uint8 cmd_buffer[CMD_MAX_SIZE];

Water_Param gSystem_WaterParam = {1,0,0.55,0.3,0};  //与串口屏交互的系统水分仪参数 初始态
Water_Value gSystem_WaterValue = {0.00, 0.00, 11.11};
Instant_Data gSystem_InstantData = {1.11,1.11,1.11,25.0,1.0};
Fit_Param   gSystem_Fit_Param1 = {-1590,2179,-1002,158.3,1};  //最后个元素是三路信号的比值，用于触摸屏调试模式使用
//Fit_Param   gSystem_Fit_Param1 = {-2.125e+04,2.536e+04,-1.01e+04,1345,1};   //分段（小余6%）
Fit_Param   gSystem_Fit_Param2 = {-4.872e+05,5.387e+05,-1.984e+05,2.436e+04,1};   //分段（大余6%）
unsigned char Timer_flag = 0;
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
	unsigned int Count = 0;
	unsigned int i = 0;
	float CrossData[550] = {0};
	
	float L17Value[30] = {0};
	float L19Value[30] = {0};
	float L22Value[30] = {0};
	float SoWatVal[5] = {0};
	float tempvalue = 0;
	float sum17Value = 0;
	float sum19Value = 0;
	float sum22Value = 0;
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
   
    //PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   
    //PieCtrlRegs.PIEIER9.bit.INTx3 = 1;	//SCIRCINTB
    // IER |= M_INT9; 	//使能SCI_B中断
    
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   //timer0
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;  //timer0
    IER |= M_INT1;	 //使能AD采样定时器
	EINT;   //使能中断
	ERTM; 	//使能调试事件

	//LED初始化
	LED_IOinit();
	BellIO_init();
	FanIO_init();
	
	// 蜂鸣器示响
	BELL_Start();
	//初始化AD9833正弦发生器
	AD9833_configinit();
	AD9833_Reset(CSIN_Channel_1);
	AD9833_Reset(CSIN_Channel_2);
	AD9833_Reset(CSIN_Channel_3);
	delay(1000);  		//必须保证足够的延时
	//初始化SCIC（UART_C）
	//UartBInit(115200);        // Initalize SCI for echoback, 波特率是115200
	UartCInit(115200);	
	//初始化AD7656
	OUTAD_Init(&gSampleTable, &gSampleValue); 
	
	//FTF 屏指令缓存区清空
	queue_reset();
	
	//启动AD9833正弦激励信号输出
	AD9833_Outdata(CSIN_Channel_1,CH1_OUT_FRE,0,2,0 ); //第一片9833，,4KHz,频率寄存器0，正弦波输出
    delay(400);      
    AD9833_Outdata(CSIN_Channel_2,CH2_OUT_FRE,0,2,0 ); //第二片9833，,6KHz,频率寄存器0，正弦波输出
    delay(400);
    AD9833_Outdata(CSIN_Channel_3,CH3_OUT_FRE,0,2,0 ); //第三片9833，,8KHz,频率寄存器0，正弦波输出
    delay(400);

	//温度控制部分初始化
	TEM_Getinit();
    
    //初始化FTF屏界面DELAY_US(5);
    DELAY_US(20000);
    InitUI(&gSystem_WaterParam);  //使串口屏参数界面显示系统默认参数
    
    //启动风扇
    FAN_Start();
    FAN_Start();
    //蜂鸣器停止
    BELL_Stop();BELL_Stop();
    LED_Core_On();LED_Core_On();
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
			//此处打开其他中断,M_INT9 is for scib, M_INT8 is for scic
			Timer_flag = 0;
			IER |= M_INT8; 	//使能SCI_C中断
			
		 	AD_Data_Shift(&gSampleTable, &gSampleValue); 	//AD采样值转换为模拟量
		 			 	
		 	//计算单路通道的信号幅值
		 	LinearConvolution(BUF_SIZE1,PBFILT_SIZE1,gSampleValue.SamValue1, PassB_Filter1,CrossData);
		 	//FIR_Filter(BUF_SIZE1,gSampleValue.SamValue1,PBFILT_SIZE1, PassB_Filter1, CrossData);
		 	L17Value[Count] = Calcu_AMP(CrossData,BUF_SIZE1,PBFILT_SIZE1);
		 	
	 	    LinearConvolution(BUF_SIZE2,PBFILT_SIZE2,gSampleValue.SamValue2, PassB_Filter2,CrossData);
		 	//FIR_Filter(BUF_SIZE2,gSampleValue.SamValue2,PBFILT_SIZE2, PassB_Filter2, CrossData);
		 	L19Value[Count] = Calcu_AMP(CrossData,BUF_SIZE2,PBFILT_SIZE2);
		 	
		 	LinearConvolution(BUF_SIZE3,PBFILT_SIZE3,gSampleValue.SamValue3, PassB_Filter3,CrossData);
		 	//FIR_Filter(BUF_SIZE3,gSampleValue.SamValue3,PBFILT_SIZE3, PassB_Filter3, CrossData);
		 	L22Value[Count] = Calcu_AMP(CrossData,BUF_SIZE3,PBFILT_SIZE3);
		 	
		 	Count++;
		 	if(Count == 30)
		 	{
		 		for(i = 0; i < 30; i++)
		 		{
		 			sum17Value  += L17Value[i];
		 			sum19Value  += L19Value[i];
		 			sum22Value  += L22Value[i];
		 		}
		 		gSystem_InstantData.L17Value = sum17Value/30;
		 		gSystem_InstantData.L19Value = sum19Value/30;
		 		gSystem_InstantData.L22Value = sum22Value/30;
		 		Count = 0;
		 		sum17Value = 0;
		 		sum19Value = 0;
		 		sum22Value = 0;
		 		
		 		//将单路通道的信号幅值发到Labview(或PC端)
		 		gSystem_InstantData.T_value = gSystem_InstantData.L19Value/(gSystem_InstantData.L17Value +gSystem_InstantData.L22Value);
		 		gSystem_Fit_Param1.T_value = gSystem_InstantData.T_value;
		 		
		 		//将温度参数先用来显示比值
		 		//gSystem_InstantData.temperature = 1/gSystem_InstantData.T_value;
		 		//SendValuetoLabview(&gSystem_InstantData);
		 		
		 		//利用拟合公式计算当前瞬时水分值
		
				gSystem_WaterValue.SoonWaterValue =  Moisture_FITcalcu(gSystem_InstantData.T_value, &gSystem_Fit_Param1, '1');
				SoWatVal[2] = SoWatVal[1];
				SoWatVal[1] = SoWatVal[0];
				SoWatVal[0] = gSystem_WaterValue.SoonWaterValue;
				//Blue LED 闪烁
		 		LED_Blue_Flash();
		 		//温度采集
		 	    gSystem_WaterValue.temperature = get_temp();
		
		 	}
		 	//计算物料的测量水分值，即对瞬时水分值取平均
			for(i = 0; i < 3; i++)
			{
				tempvalue += SoWatVal[i];
			}
			tempvalue= tempvalue/3;
			gSystem_WaterValue.WaterValue= Correct_Moisture(tempvalue,gSystem_WaterParam.Water_k,gSystem_WaterParam.Water_b);
		 	tempvalue = 0;
		 	
		 	//Red LED 闪烁
		 	LED_Red_Flash();  

		 	//PID温度调节控制
		 	
		 	//处理FTF串口屏消息
		 	size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE); //从缓冲区中获取一条指令        
			if(size > 0)   //接收到指令
			{
				ProcessMessage((PCTRL_MSG)cmd_buffer, size, &gSystem_WaterParam); //指令处理
			}				
			UpdateUI(&gSystem_WaterValue,gSystem_Fit_Param1.T_value);
		 	
		 	//此处关闭其他中断
		 	IER &= ~M_INT8; 	             //禁止SCI中断,M_INT9 is for scib, M_INT8 is for scic
			SampleCount_Status_Flag = False;
		 	START_SAMPLING();
		} 
		
	}
}
/**********************************
 * Interrupt _ timer
 *********************************/
interrupt void ISRTimer0(void)
{   
	Timer_flag = 1; 
 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    CpuTimer0Regs.TCR.bit.TIF = 1;   // 定时到了指定时间，标志位置位，清除标志     
    CpuTimer0Regs.TCR.bit.TRB = 1;   // 重载Timer0的定时数据 
    SIN_On(); 
} 

/************************************
 * SCI——C中断服务程序
 ***********************************/
 interrupt void scic_isr(void)
 {
 	uint8 rdataC = 0;
 	rdataC = ScicRegs.SCIRXBUF.all;
 	queue_push(rdataC);                //压入到指令缓冲区
 	ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;
 	ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;
 	PieCtrlRegs.PIEACK.all |= 0x100;
 }	

//===========================================================================
// No more.
//===========================================================================


