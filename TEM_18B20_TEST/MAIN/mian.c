
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "DS18B20.h"

float tem_value;
main(void)
{
	char lev;
	InitSysCtrl();
	InitXintf16Gpio();

	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	
	TEM_Getinit();

	DELAY_US(50000);
	
//	EALLOW;
//	GpioCtrlRegs.GPBMUX1.bit.TEM_IO=0;
//  DQ_DIR=0;
//	EDIS;
	while(1)
	{
	
//		LED_Blue_Flash();
		DELAY_US(500000);
		//DQ = 0;
	//	tem_value = get_temp();
	//	DQ  = 1;
		DELAY_US(50000);
  //    	EALLOW;
//	    GpioCtrlRegs.GPBDIR.bit.GPIO40=0;
//	    GpioCtrlRegs.GPCDIR.bit.GPIO81=0;
//		GpioCtrlRegs.GPBPUD.bit.GPIO81 = 0;   // enalble pull up， 引脚在悬空时，的信号可能会时高时低，上拉后给它一个高电平，
//    DQ_DIR=0;
 //     EDIS;
//	DQ_HIGH();
//	DQ_LOW();
//	GpioDataRegs.GPBSET.bit.GPIO41 =1;
//	GpioDataRegs.GPBCLEAR.bit.GPIO41 =1;
    DELAY_US(5);
 //   DQ_HIGH();
    lev =DQ  ;
	   if(lev == 1)
	   {
	   		tem_value = 11.0;
	   }
		DELAY_US(500000);

		
	}
}
