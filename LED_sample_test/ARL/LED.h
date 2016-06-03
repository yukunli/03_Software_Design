
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
#include "std_int.h"
/*
#define LED_Yellow_On() P1OUT &= ~BIT3
#define LED_Yellow_Off() P1OUT |= BIT3
*/
#define Red_IO   GPIO3
#define Blue_IO  GPIO4

#define LED_Blue_On()   GpioDataRegs.GPADAT.bit.Blue_IO=0
#define LED_Blue_Off()  GpioDataRegs.GPADAT.bit.Blue_IO=1

#define LED_Red_On()   GpioDataRegs.GPADAT.bit.Red_IO=0
#define LED_Red_Off()  GpioDataRegs.GPADAT.bit.Red_IO=1

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


#endif /*LED_H_*/
