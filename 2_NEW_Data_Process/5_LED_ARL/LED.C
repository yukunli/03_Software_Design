/*
 * LED.C
 *
 *  Created on: dec 15, 2015
 *      Author: Danny
 */

#include "LED.h"
#include "std_init.h"

UINT8 red_light_state1 = 0;
UINT8 i1=0;

UINT8 red_light_state2 = 0;
UINT8 i2=0;

UINT8 light_state3 = 0;
UINT8 i3=0;

UINT8 blue_light_state4 = 0;
UINT8 i4=0;

UINT8 blue_light_state5 = 0;
UINT8 i5=0;
void LED_IOinit(void)
{
	EALLOW; 
	GpioCtrlRegs.GPBMUX1.bit.Blue_IO=0;
	GpioCtrlRegs.GPBDIR.bit.Blue_IO=1;
	GpioCtrlRegs.GPBMUX1.bit.Red_IO=0;
	GpioCtrlRegs.GPBDIR.bit.Red_IO=1;  
	GpioCtrlRegs.GPAMUX1.bit.Core_LED=0;
	GpioCtrlRegs.GPADIR.bit.Core_LED=1;
	
	GpioCtrlRegs.GPAMUX1.bit.Fan_IO=0;
	GpioCtrlRegs.GPADIR.bit.Fan_IO=1;
	GpioCtrlRegs.GPAMUX1.bit.Bell_IO=0;
	GpioCtrlRegs.GPADIR.bit.Bell_IO=1;
	EDIS;
	
	LED_Red_Off();
	LED_Blue_Off();
	LED_Core_Off();
	FAN_Stop();
	BELL_Stop();
}
void LED_Red_Flash(void)
{

	if(red_light_state1 == 0)
	{
		LED_Red_Off();
		i1++;
		if(i1>=2)
		{
			red_light_state1 = 1;
			i1 = 0;
		}
	}
	else
	{
		LED_Red_On();
		i1++;
		if(i1>=2)
		{
			red_light_state1 = 0;
			i1 = 0;
		}
	}
}

void LED_Red_Flash_Slow(void)
{

	if(red_light_state2 == 0)
	{
		LED_Red_Off();
		i2++;
		if(i2>=1)
		{
			red_light_state2 = 1;
			i2 = 0;
		}
	}
	else
	{
		LED_Red_On();
		i2++;
		if(i2>=1)
		{
			red_light_state2 = 0;
			i2 = 0;
		}
	}
}

void LED_Error_Flash(void)
{

	if(light_state3 == 0)
	{
		LED_Red_Off();
		LED_Blue_On();
		i3++;
		if(i3>=10)
		{
			light_state3 = 1;
			i3 = 0;
		}
	}
	else
	{
		LED_Blue_Off();
		LED_Red_On();
		i3++;
		if(i3>=10)
		{
			light_state3 = 0;
			i3 = 0;
		}
	}
}

void LED_Blue_Flash(void)//5hz
{

	if(blue_light_state4 == 0)
	{
		LED_Blue_Off();
		i4++;
		if(i4>=2)
		{
			blue_light_state4 = 1;
			i4 = 0;
		}
	}
	else
	{
		LED_Blue_On();
		i4++;
		if(i4>=2)
		{
			blue_light_state4 = 0;
			i4 = 0;
		}
	}
}

void LED_Blue_Flash_Slow(void)//1hz
{

	if(blue_light_state5 == 0)
	{
		LED_Blue_Off();
		i5++;
		if(i5>=10)
		{
			blue_light_state5 = 1;
			i5 = 0;
		}
	}
	else
	{
		LED_Blue_On();
		i5++;
		if(i5>=10)
		{
			blue_light_state5 = 0;
			i5 = 0;
		}
	}
}

void Bell_Didadi(void)
{
	BELL_Start();
	DELAY_US(700000);
	BELL_Stop();
	DELAY_US(700000);
	BELL_Start();
	DELAY_US(700000);
	BELL_Stop();
}
//End of LED Flash


