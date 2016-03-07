
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "LED.h"


main(void)
{
	int i;
	
	InitSysCtrl();
	InitXintf();
	InitXintf16Gpio();

	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	
	LED_IOinit();
	
	while(1)
	{
		for(i=0;i<=2000;i++);
	
		LED_Blue_Flash();
		DELAY_US(50000);
		DELAY_US(50000);
		DELAY_US(5000);
//		LED_Red_Flash();
		DELAY_US(50000);
		DELAY_US(50000);
	}
}
