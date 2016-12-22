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

STRSampleTable gSampleTable;     //ȫ�� sample Table
STRSampleValue gSampleValue;     //ȫ�� Sample Value
uint8 cmd_buffer[CMD_MAX_SIZE];

Water_Param gSystem_WaterParam = {1,0,0.55,0.3,0};  //�봮����������ϵͳˮ���ǲ��� ��ʼ̬
Water_Value gSystem_WaterValue = {0.00, 0.00, 11.11};
Instant_Data gSystem_InstantData = {1.11,1.11,1.11,25.0,1.0};
Fit_Param   gSystem_Fit_Param1 = {-1590,2179,-1002,158.3,1};  //����Ԫ������·�źŵı�ֵ�����ڴ���������ģʽʹ��
//Fit_Param   gSystem_Fit_Param1 = {-2.125e+04,2.536e+04,-1.01e+04,1345,1};   //�ֶΣ�С��6%��
Fit_Param   gSystem_Fit_Param2 = {-4.872e+05,5.387e+05,-1.984e+05,2.436e+04,1};   //�ֶΣ�����6%��
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
   
    //PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   
    //PieCtrlRegs.PIEIER9.bit.INTx3 = 1;	//SCIRCINTB
    // IER |= M_INT9; 	//ʹ��SCI_B�ж�
    
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   //timer0
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;  //timer0
    IER |= M_INT1;	 //ʹ��AD������ʱ��
	EINT;   //ʹ���ж�
	ERTM; 	//ʹ�ܵ����¼�

	//LED��ʼ��
	LED_IOinit();
	BellIO_init();
	FanIO_init();
	
	// ������ʾ��
	BELL_Start();
	//��ʼ��AD9833���ҷ�����
	AD9833_configinit();
	AD9833_Reset(CSIN_Channel_1);
	AD9833_Reset(CSIN_Channel_2);
	AD9833_Reset(CSIN_Channel_3);
	delay(1000);  		//���뱣֤�㹻����ʱ
	//��ʼ��SCIC��UART_C��
	//UartBInit(115200);        // Initalize SCI for echoback, ��������115200
	UartCInit(115200);	
	//��ʼ��AD7656
	OUTAD_Init(&gSampleTable, &gSampleValue); 
	
	//FTF ��ָ��������
	queue_reset();
	
	//����AD9833���Ҽ����ź����
	AD9833_Outdata(CSIN_Channel_1,CH1_OUT_FRE,0,2,0 ); //��һƬ9833��,4KHz,Ƶ�ʼĴ���0�����Ҳ����
    delay(400);      
    AD9833_Outdata(CSIN_Channel_2,CH2_OUT_FRE,0,2,0 ); //�ڶ�Ƭ9833��,6KHz,Ƶ�ʼĴ���0�����Ҳ����
    delay(400);
    AD9833_Outdata(CSIN_Channel_3,CH3_OUT_FRE,0,2,0 ); //����Ƭ9833��,8KHz,Ƶ�ʼĴ���0�����Ҳ����
    delay(400);

	//�¶ȿ��Ʋ��ֳ�ʼ��
	TEM_Getinit();
    
    //��ʼ��FTF������DELAY_US(5);
    DELAY_US(20000);
    InitUI(&gSystem_WaterParam);  //ʹ����������������ʾϵͳĬ�ϲ���
    
    //��������
    FAN_Start();
    FAN_Start();
    //������ֹͣ
    BELL_Stop();BELL_Stop();
    LED_Core_On();LED_Core_On();
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
			//�˴��������ж�,M_INT9 is for scib, M_INT8 is for scic
			Timer_flag = 0;
			IER |= M_INT8; 	//ʹ��SCI_C�ж�
			
		 	AD_Data_Shift(&gSampleTable, &gSampleValue); 	//AD����ֵת��Ϊģ����
		 			 	
		 	//���㵥·ͨ�����źŷ�ֵ
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
		 		
		 		//����·ͨ�����źŷ�ֵ����Labview(��PC��)
		 		gSystem_InstantData.T_value = gSystem_InstantData.L19Value/(gSystem_InstantData.L17Value +gSystem_InstantData.L22Value);
		 		gSystem_Fit_Param1.T_value = gSystem_InstantData.T_value;
		 		
		 		//���¶Ȳ�����������ʾ��ֵ
		 		//gSystem_InstantData.temperature = 1/gSystem_InstantData.T_value;
		 		//SendValuetoLabview(&gSystem_InstantData);
		 		
		 		//������Ϲ�ʽ���㵱ǰ˲ʱˮ��ֵ
		
				gSystem_WaterValue.SoonWaterValue =  Moisture_FITcalcu(gSystem_InstantData.T_value, &gSystem_Fit_Param1, '1');
				SoWatVal[2] = SoWatVal[1];
				SoWatVal[1] = SoWatVal[0];
				SoWatVal[0] = gSystem_WaterValue.SoonWaterValue;
				//Blue LED ��˸
		 		LED_Blue_Flash();
		 		//�¶Ȳɼ�
		 	    gSystem_WaterValue.temperature = get_temp();
		
		 	}
		 	//�������ϵĲ���ˮ��ֵ������˲ʱˮ��ֵȡƽ��
			for(i = 0; i < 3; i++)
			{
				tempvalue += SoWatVal[i];
			}
			tempvalue= tempvalue/3;
			gSystem_WaterValue.WaterValue= Correct_Moisture(tempvalue,gSystem_WaterParam.Water_k,gSystem_WaterParam.Water_b);
		 	tempvalue = 0;
		 	
		 	//Red LED ��˸
		 	LED_Red_Flash();  

		 	//PID�¶ȵ��ڿ���
		 	
		 	//����FTF��������Ϣ
		 	size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE); //�ӻ������л�ȡһ��ָ��        
			if(size > 0)   //���յ�ָ��
			{
				ProcessMessage((PCTRL_MSG)cmd_buffer, size, &gSystem_WaterParam); //ָ���
			}				
			UpdateUI(&gSystem_WaterValue,gSystem_Fit_Param1.T_value);
		 	
		 	//�˴��ر������ж�
		 	IER &= ~M_INT8; 	             //��ֹSCI�ж�,M_INT9 is for scib, M_INT8 is for scic
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
    CpuTimer0Regs.TCR.bit.TIF = 1;   // ��ʱ����ָ��ʱ�䣬��־λ��λ�������־     
    CpuTimer0Regs.TCR.bit.TRB = 1;   // ����Timer0�Ķ�ʱ���� 
    SIN_On(); 
} 

/************************************
 * SCI����C�жϷ������
 ***********************************/
 interrupt void scic_isr(void)
 {
 	uint8 rdataC = 0;
 	rdataC = ScicRegs.SCIRXBUF.all;
 	queue_push(rdataC);                //ѹ�뵽ָ�����
 	ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;
 	ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;
 	PieCtrlRegs.PIEACK.all |= 0x100;
 }	

//===========================================================================
// No more.
//===========================================================================


