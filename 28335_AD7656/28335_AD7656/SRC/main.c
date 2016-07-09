//�ڶ�ʱ���ڽ��в���,������1.5KHz
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define	  AD7656_BASIC    (*((volatile  Uint16 *)0x200000))
//#define	  AD7656_rst      (*((volatile  Uint16 *)0x200008))
#define   AD_BUSY         GpioDataRegs.GPBDAT.bit.GPIO60
#define   SET_ADRST       GpioDataRegs.GPBSET.bit.GPIO61=1
#define   CLEAR_ADRST     GpioDataRegs.GPBCLEAR.bit.GPIO61=1
#define   SET_ADCLK       GpioDataRegs.GPASET.bit.GPIO25=1
#define   CLR_ADCLK       GpioDataRegs.GPACLEAR.bit.GPIO25=1
Uint16 ad[6];
void InitXintf(void);
//int test[256];
long sampleCount=0;
Uint16 testSample1[200],testSample2[200],testSample3[200],//6��������AD����
       testSample4[200],testSample5[200],testSample6[200]; 
int i;
interrupt void ISRTimer0(void);

void ADInit(void)
{
	EALLOW;
	GpioCtrlRegs.GPAMUX2.bit.GPIO25=0;
	GpioCtrlRegs.GPADIR.bit.GPIO25=1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;  // XWE0
	GpioCtrlRegs.GPBDIR.bit.GPIO61=1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO60=0; //ADBUSY
	GpioCtrlRegs.GPBDIR.bit.GPIO60=0;//INPUT
	GpioCtrlRegs.GPBQSEL2.bit.GPIO60= 0;
	EDIS;
} 

void main(void)
{ 

	InitSysCtrl();
	InitXintf();
	InitXintf16Gpio();
	ADInit();
	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.TINT0 = &ISRTimer0;
   EDIS;    // This is needed to disable write to EALLOW protected registers
   InitCpuTimers();   // For this example, only initialize the Cpu Timers
   ConfigCpuTimer(&CpuTimer0, 150, 3); //�ڶ�ʱ���ڽ��в���,������50KHz
	
    IER |= M_INT1;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; 
	EINT; 
	ERTM;  
/*EALLOW;
GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; // GPIO0 = GPIO0
GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; 
EDIS;
GpioDataRegs.GPADAT.bit.GPIO0 = 0;*/
	SET_ADRST;  
	CLR_ADCLK;   //����ת���ź�
	DELAY_US(100000);
	CLEAR_ADRST; 
	SET_ADCLK;
	DELAY_US(100000);
	StartCpuTimer0();
	while(1);

}

interrupt void ISRTimer0(void)
{   	   	
   	CLR_ADCLK;   //����ת���ź�
	DELAY_US(0.3); //�����ʵ��ĵ�ƽ��ʱ
	SET_ADCLK;
	while(AD_BUSY); //�ȴ�ת������
	testSample1[sampleCount]=AD7656_BASIC;//ad[0];//�����������
	testSample2[sampleCount]=AD7656_BASIC;//ad[1];
	testSample3[sampleCount]=AD7656_BASIC;//ad[2];
	testSample4[sampleCount]=AD7656_BASIC;//ad[3];
	testSample5[sampleCount]=AD7656_BASIC;//ad[4];
	testSample6[sampleCount]=AD7656_BASIC;//ad[5]; 
	sampleCount++;
	if(sampleCount >= 200) 
	{
		sampleCount=0;
	}
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    CpuTimer0Regs.TCR.bit.TIF=1; // ��ʱ����ָ��ʱ�䣬��־λ��λ�������־      
    CpuTimer0Regs.TCR.bit.TRB=1;  // ����Timer0�Ķ�ʱ����
} 

