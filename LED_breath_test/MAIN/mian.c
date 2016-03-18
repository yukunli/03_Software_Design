
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "LED.h"


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
	EPWM_LED_Init();
//	LED_IOinit();
	DELAY_US(50000);
	DELAY_US(50000);
	while(1)
	{
		for(i=0;i<=2000;i++);
	
//		LED_Blue_Flash();
		DELAY_US(500000);

		DELAY_US(500000);
//		LED_Red_Flash();
//		LED_Red_Flash_Slow();
//		LED_Error_Flash();
		DELAY_US(500000);
		DELAY_US(500000);
		DELAY_US(500000);
		DELAY_US(500000);
		LED_breathing();
		
	}
}
