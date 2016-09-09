
/*
 * LED.C
 *
 *  Created on: dec 15, 2015
 *      Author: Danny
 */

#ifndef LED_H_
#define LED_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "std_init.h"
/*
#define LED_Yellow_On() P1OUT &= ~BIT3
#define LED_Yellow_Off() P1OUT |= BIT3
*/
#define Red_IO   GPIO42   //位于DSP控制板上
#define Blue_IO  GPIO44	  //位于DSP控制板上
#define Core_LED GPIO1    //位于dsp核心板上

#define Fan_IO   GPIO5    //位于DSP控制板上
#define Bell_IO  GPIO4    //位于DSP控制板上
#define SIN_IO   GPIO29   //位于信号激励板上

#define LED_Blue_On()   GpioDataRegs.GPBDAT.bit.Blue_IO=1
#define LED_Blue_Off()  GpioDataRegs.GPBDAT.bit.Blue_IO=0

#define LED_Red_On()   GpioDataRegs.GPBDAT.bit.Red_IO=1
#define LED_Red_Off()  GpioDataRegs.GPBDAT.bit.Red_IO=0

#define LED_Core_On()   GpioDataRegs.GPADAT.bit.Core_LED=1
#define LED_Core_Off()   GpioDataRegs.GPADAT.bit.Core_LED=0

#define FAN_Start()   GpioDataRegs.GPADAT.bit.Fan_IO=1
#define FAN_Stop()   GpioDataRegs.GPADAT.bit.Fan_IO=0

#define BELL_Start()   GpioDataRegs.GPADAT.bit.Bell_IO=1
#define BELL_Stop()   GpioDataRegs.GPADAT.bit.Bell_IO=0

#define SIN_On()   GpioDataRegs.GPADAT.bit.SIN_IO=1
#define SIN_Off()   GpioDataRegs.GPADAT.bit.SIN_IO=0


extern UINT8 red_light_state1 ;
extern UINT8 i1;

extern UINT8 red_light_state2 ;
extern UINT8 i2;

extern UINT8 light_state3 ;
extern UINT8 i3;

extern UINT8 blue_light_state4;
extern UINT8 i4;

extern UINT8 blue_light_state5 ;
extern UINT8 i5;
//void LED_Yellow_Flash(void);
extern void LED_IOinit(void);
extern void LED_Blue_Flash(void);
extern void LED_Blue_Flash_Slow(void);
extern void LED_Red_Flash(void);
//extern void LED_Red_Flash_Slow(void);
extern void LED_Error_Flash(void);

extern void Bell_Didadi(void);

#endif /*LED_H_*/
