/*
 * LED.C
 *
 *  Created on: dec 15, 2015
 *      Author: Danny
 */

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "LED.h"
#include "std_int.h"
#include "stdio.h"
#include "PWM_LED.h"

void LED_IOinit(void)
{
	EALLOW; 
	GpioCtrlRegs.GPCMUX2.bit.Blue_IO=0;
	GpioCtrlRegs.GPCDIR.bit.Blue_IO=1;
	GpioCtrlRegs.GPCMUX2.bit.Red_IO=0;
	GpioCtrlRegs.GPCDIR.bit.Red_IO=1;
	LED_Red_Off();
	LED_Blue_Off();
	LED_Red_Off();
	LED_Blue_Off();
	
	EDIS;
}
void LED_Red_Flash(void)
{
	static unsigned char red_light_state = 0;
	static unsigned char i;
	if(red_light_state == 0)
	{
		LED_Red_Off();
		i++;
		if(i>=2)
		{
			red_light_state = 1;
			i = 0;
		}
	}
	else
	{
		LED_Red_On();
		i++;
		if(i>=2)
		{
			red_light_state = 0;
			i = 0;
		}
	}
}

void LED_Red_Flash_Slow(void)
{
	static unsigned char red_light_state = 0;
	static unsigned char i;
	if(red_light_state == 0)
	{
		LED_Red_Off();
		i++;
		if(i>=10)
		{
			red_light_state = 1;
			i = 0;
		}
	}
	else
	{
		LED_Red_On();
		i++;
		if(i>=10)
		{
			red_light_state = 0;
			i = 0;
		}
	}
}
/*
 * function: 
 */
void LED_Error_Flash(void)
{
	static unsigned char light_state = 0;
	static unsigned char i;
	if(light_state == 0)
	{
		LED_Red_Off();
		LED_Red_Off();
		LED_Blue_On();
		LED_Blue_On();
		i++;
		if(i>=10)
		{
			light_state = 1;
			i = 0;
		}
	}
	else
	{
		LED_Blue_Off();
		LED_Blue_Off();
		LED_Red_On();
		LED_Red_On();
		i++;
		if(i>=10)
		{
			light_state = 0;
			i = 0;
		}
	}
}

void LED_Blue_Flash(void)//5hz
{
	static unsigned char blue_light_state = 0;
	static unsigned char i;
	if(blue_light_state == 0)
	{
		LED_Blue_Off();
		i++;
		if(i>=2)
		{
			blue_light_state = 1;
			i = 0;
		}
	}
	else
	{
		LED_Blue_On();
		i++;
		if(i>=2)
		{
			blue_light_state = 0;
			i = 0;
		}
	}
}

void LED_Blue_Flash_Slow(void)//1hz
{
	static unsigned char blue_light_state = 0;
	static unsigned char i;
	if(blue_light_state == 0)
	{
		LED_Blue_Off();
		i++;
		if(i>=10)
		{
			blue_light_state = 1;
			i = 0;
		}
	}
	else
	{
		LED_Blue_On();
		i++;
		if(i>=10)
		{
			blue_light_state = 0;
			i = 0;
		}
	}
}
/***********************************
 * need: the LED IO should be config the PWM
 */
 void LED_breathing(void)
{
	int priod;
	unsigned int cmpavalue = SP/2;
	
	//EPWM_LED_Init();
	for(priod = SP ;priod >= cmpavalue;priod--)  //light down
	{
		EPWM_LED_UpdataCMPA(priod);
		DELAY_US(50000000-priod*3000);
		DELAY_US(50000);
	}
	for (priod= cmpavalue;priod <= SP ;priod++)
	{
		EPWM_LED_UpdataCMPA(priod);   // light up  the value is more big , the output value is more small
		DELAY_US(5000000-priod*3000);
		DELAY_US(50000);
	}
	
}
//End of LED Flash


