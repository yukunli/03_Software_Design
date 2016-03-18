
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "tem_control.h"
#include "PWM_tem.h"

main(void)
{
	int i;
	
	InitSysCtrl();
	InitXintf16Gpio();

	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	
	
	
	
	EPWM_tem_Init();
	
	DELAY_US(50000);

	while(1)
	{
		for(i=0;i<=2000;i++);
	
		DELAY_US(500000);
		DELAY_US(500000);
		Get_new_occupyrate(Get_Temvalue());
		
	}
}
