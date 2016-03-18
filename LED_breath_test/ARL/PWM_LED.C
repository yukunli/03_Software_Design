
/**************
 * creaded in nxp 2016.1.8
 */
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "PWM_LED.h"
#include "std_int.h"
/**********************
 * CODE
 */
 void EPWM_LED_Init()
{
    //InitEPwm1Gpio();
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    //gpio inner shang la 
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   //set the gpio0 to  EPWM1A function
    EDIS;
    
    EALLOW;
	EPwm1Regs.TBSTS.all=0;
	EPwm1Regs.TBPHS.half.TBPHS=0;  // THE count counts from the TBPHS value
	EPwm1Regs.TBCTR=0;

	EPwm1Regs.CMPCTL.all=0x50;        // Immediate mode for CMPA and CMPB
	EPwm1Regs.CMPA.half.CMPA =(unsigned int)(SP);    // set zhankongbi
	EPwm1Regs.CMPB=0x0;

	EPwm1Regs.AQCTLA.all=0x60;        // EPWMxA = 1 when CTR=CMPA and counter inc
	                                  // EPWMxA = 0 when CTR=CMPA and counter dec
	EPwm1Regs.AQCTLB.all=0;
	EPwm1Regs.AQSFRC.all=0;
	EPwm1Regs.AQCSFRC.all=0;

	EPwm1Regs.DBCTL.all=0xb;          // EPWMxB is inverted
	EPwm1Regs.DBRED=0;
	EPwm1Regs.DBFED=0;

	EPwm1Regs.TZSEL.all=0;
	EPwm1Regs.TZCTL.all=0;
	EPwm1Regs.TZEINT.all=0;
	EPwm1Regs.TZFLG.all=0;
	EPwm1Regs.TZCLR.all=0;
	EPwm1Regs.TZFRC.all=0;

	EPwm1Regs.ETSEL.all=0;            // Interrupt when TBCTR = 0x0000
	EPwm1Regs.ETFLG.all=0;
	EPwm1Regs.ETCLR.all=0;
	EPwm1Regs.ETFRC.all=0;

	EPwm1Regs.PCCTL.all=0;
	// DUI TB de time jinxing fenping
	EPwm1Regs.TBCTL.bit.PHSDIR = 1; // when the time-base is up-down-count .count u after the synchronization event
	EPwm1Regs.TBCTL.bit.CLKDIV = TB_CLKDIV;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_HSPCLKDIV;
	EPwm1Regs.TBCTL.bit.PHSEN = 1;     //count register load form phase register   enable
	EPwm1Regs.TBCTL.bit.PRDLD = 0;     //Active period register load from shadow register select
	EPwm1Regs.TBCTL.bit.CTRMODE = 0x2; //up_down-count mode
	EPwm1Regs.TBCTL.bit.SYNCOSEL = 0x1;
	
	//EPwm1Regs.TBCTL.all |=0x0010+TBCTLVAL; // Enable Timer,set the up_down-count mode.CLKDIV bits determine part of the time-base clock p
	// 0X0010 means SYNCOSEL=01(TBCTR=zero0X0000)
	EPwm1Regs.TBPRD=(unsigned int)(SP);      //the time-base counter starts from zero orX and  increments nntil the period 
											// TBPRD value is reached
	EDIS;
}
/**********************************************
 *  function: set the 
 * canshu : x (0~SP)
 */
char EPWM_LED_UpdataCMPA(unsigned int x)
{
	int cycle = x;
	if(cycle < SP)
	{
		EALLOW;
		EPwm1Regs.CMPA.half.CMPA = (unsigned int)(cycle);	
		EDIS;
		return 1;	
	}
	else
		return 0;
}
/***********************************************
 * 
 */
 void EPWM_LED_deInit()
 {
 	EALLOW;
 //	EPwm1Regs.TBCTL.bit.PHSEN = 0x0; //  TB disenable it don't work
 	EDIS;
 }
 
