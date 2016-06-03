
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "DS18B20.h"

float tem_value;
main(void)
{
	InitSysCtrl();
	InitSysCtrl();
	InitXintf16Gpio();

	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	
	TEM_Getinit();

	DELAY_US(5000);
	
	tem_value = get_temp();
	while(1)
	{
	
	}
}
