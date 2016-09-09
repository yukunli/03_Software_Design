/*
 * ˵������AD7656�ɼ������źţ��õ���·�źŲ���ֵ������������Ŵ����󣬵õ���·�źŵķ�ֵ
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
/*****************����ȫ�ֱ���*********************/
STRSampleTable gSampleTable;  //ȫ�� sample Table
STRSampleValue gSampleValue;  //ȫ�� Sample Value
uint8 cmd_buffer[CMD_MAX_SIZE];
Water_Param gSystem_WaterParam = {12.0,1,1.66,22.3,0};  //�봮����������ϵͳˮ���ǲ���
Water_Value gSystem_WaterValue = {5.20, 5.21, 32.76};
LabView_Data Test_gSystem_LabviewData = {1.11,1.11,1.11,25.0};
unsigned char Timer_flag = 0;
/**************************************************/
interrupt void ISRTimer0(void);
interrupt void scic_isr(void);
void InitXintf(void);
/*********************������***********************/
/**************************************************/
void main()
{    
	/*****************��ʱ��ȫ�ֱ���******************************/
	qsize  size = 0;
	unsigned int Count = 0;
	unsigned int i = 0;
	float L17Value[100] = {0};
	float L19Value[100] = {0};
	float L22Value[100] = {0};
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
// ���س���Flash
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart); 
	InitFlash();
	 
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.SCIRXINTC = &scic_isr;
	PieVectTable.TINT0 = & ISRTimer0;
	EDIS;    // This is needed to disable write to EALLOW protected registers 
   
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   
    PieCtrlRegs.PIEIER8.bit.INTx5 = 1;	//SCIRCINTC
   // IER |= M_INT8; 	//ʹ��SCI_C�ж�
    
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   //timer0
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;  //timer0
    IER |= M_INT1;	 //ʹ��AD������ʱ��
	EINT;   //ʹ���ж�
	ERTM; 	//ʹ�ܵ����¼�

	//LED��ʼ��
	LED_IOinit();
	
	//��ʼ��AD9833���ҷ�����
	AD9833_configinit();
	AD9833_Reset(CSIN_Channel_1);
	AD9833_Reset(CSIN_Channel_2);
	AD9833_Reset(CSIN_Channel_3);
	delay(1000);  		//���뱣֤�㹻����ʱ
	//��ʼ��SCIC��UART_C��
	UartInit(115200);        // Initalize SCI for echoback, ��������115200
		
	//��ʼ��AD7656
	OUTAD_Init(&gSampleTable, &gSampleValue); 
	
	//FTF��ָ��������
	//queue_reset();
	
	
	//����AD9833���Ҽ����ź����
	AD9833_Outdata(CSIN_Channel_1,CH1_OUT_FRE,0,2,0 ); //��һƬ9833��,5KHz,Ƶ�ʼĴ���0�����Ҳ����
    delay(200);      
    AD9833_Outdata(CSIN_Channel_2,CH2_OUT_FRE,0,2,0 ); //�ڶ�Ƭ9833��,6KHz,Ƶ�ʼĴ���0�����Ҳ����
    delay(200);
    AD9833_Outdata(CSIN_Channel_3,CH3_OUT_FRE,0,2,0 ); //����Ƭ9833��,7KHz,Ƶ�ʼĴ���0�����Ҳ����
    delay(100);
    /*
    // ������ʾ��
    Bell_Didadi();
    */
	//�¶ȿ��Ʋ��ֳ�ʼ��
	TEM_Getinit();
    /*
    //��ʼ��FTF������DELAY_US(5);
    DELAY_US(10000);
    InitUI(&gSystem_WaterParam);  //ʹ����������������ʾϵͳĬ�ϲ���
    
    //��������
    FAN_Start();
    */
	//����AD7656����
    START_SAMPLING();
	while(1)
	{	
		//LED_Core_On();
		if( Timer_flag == 1 && SampleCount_Status_Flag == False)  //ת��AD7656�Ĳ��� 
		{
			//���е����
			GetAD_Value(&gSampleTable);  
			Timer_flag = 0;
			SIN_Off(); 
		}
		else if(SampleCount_Status_Flag == True)   //��������������������һ���Ĵ���
		{
			//�˴��������ж�
			Timer_flag = 0;
			IER |= M_INT8; 	//ʹ��SCI_C�ж�
					
		 	AD_Data_Shift(&gSampleTable, &gSampleValue); 	//AD����ֵת��Ϊģ����
		 	//���㵥·ͨ�����źŷ�ֵ
		 	L17Value[Count] = Calcu_AMP(gSampleValue.SamValue1,BUF_SIZE1);
		 	L19Value[Count] = Calcu_AMP(gSampleValue.SamValue2,BUF_SIZE2);
		 	L22Value[Count] = Calcu_AMP(gSampleValue.SamValue3,BUF_SIZE3);
		 	Count++;
		 	if(Count == 100)
		 	{
		 		for(i = 0; i < 100; i++)
		 		{
		 			sum17Value  += L17Value[i];
		 			sum19Value  += L19Value[i];
		 			sum22Value  += L22Value[i];
		 		}
		 		Test_gSystem_LabviewData.L17Value = sum17Value/100;
		 		Test_gSystem_LabviewData.L19Value = sum19Value/100;
		 		Test_gSystem_LabviewData.L22Value = sum22Value/100;
		 		Count = 0;
		 		sum17Value = 0;
		 		sum19Value = 0;
		 		sum22Value = 0;
		 		//����·ͨ�����źŷ�ֵ����Labview(��PC��)
		 		SendValuetoLabview(&Test_gSystem_LabviewData);
		 	}
		 	 
		 	
		 	//������Ϲ�ʽ���㵱ǰ˲ʱˮ��ֵ
			gSystem_WaterValue.SoonWaterValue = 0.22;
			
		 	//Red LED ��˸
		 	LED_Red_Flash();
		 	
		 	//Blue LED ��˸
		 	LED_Blue_Flash();
		 	
		 	// �¶Ȳɼ�
		 	Test_gSystem_LabviewData.temperature = get_temp();
		 	
		 	// PID�¶ȵ��ڿ���
		 	
		 	
		 	/*
		 	//����FTF��������Ϣ
		 	size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE); //�ӻ������л�ȡһ��ָ��        
			if(size > 0) //���յ�ָ��
			{
				ProcessMessage((PCTRL_MSG)cmd_buffer, size, &gSystem_WaterParam); //ָ���
			}				
			UpdateUI(&gSystem_WaterValue);
			*/
		 	//while(1);
		 	
		 	//�˴��ر������ж�
		 	IER &= ~M_INT8; 	//��ֹSCI_C�ж�
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
	Timer_flag = 1; 
 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    CpuTimer0Regs.TCR.bit.TIF=1;   // ��ʱ����ָ��ʱ�䣬��־λ��λ�������־     
    CpuTimer0Regs.TCR.bit.TRB=1;   // ����Timer0�Ķ�ʱ����   
} 

/************************************
 * SCI����C�жϷ������
 ***********************************/
 interrupt void scic_isr(void)
 {
 	uint8 rdataC = 0;
 	rdataC = ScicRegs.SCIRXBUF.all;
 	queue_push(rdataC);//ѹ�뵽ָ�����
 	ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;
 	ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;
 	PieCtrlRegs.PIEACK.all |= 0x100;
 }	
 
//===========================================================================
// No more.
//===========================================================================


