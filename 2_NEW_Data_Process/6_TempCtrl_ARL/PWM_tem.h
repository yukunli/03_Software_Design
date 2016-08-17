

#ifndef LPWM_LED_H_
#define LPWM_LED_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
/**************
 * creaded in nxp 2016.1.8
 */
/**********************
 * 
 * describption:
 * the file is use to difine the epwm funciton for the LED breath
 */
#if (CPU_FRQ_150MHZ)
  #define CPU_CLK   150e6
#endif
#if (CPU_FRQ_100MHZ)
  #define CPU_CLK   100e6
#endif

#define TEM_TB_HSPCLKDIV 0x02    // 010:1/4  100:1/8  101: 1/10 110:1/12 111: 1/14
#define TEM_TB_CLKDIV  0x06 		// 010:1/4, 011:1/8  110: 1/64 111: 1/128
#define TEM_PWM_FRE   2929               // If diff freq. desired, change freq here.TPWM=1/PWM_FRE
#define TEM_TBCLK 	  (CPU_CLK/(4*64))
#define TEM_SP        TEM_TBCLK/(2*TEM_PWM_FRE)  //TBPRD=SP  lilun TEM_SP=100  

#define TEM_TBCTLVAL  0x200E                // Up-down cnt, timebaseTBCLK = SYSCLKOUT/(HSPCLKDIV*CLKDIV)

/***************************************
 * 
 */
extern void EPWM_tem_Init(void);
extern void EPWM_tem_deInit(void);
extern char EPWM_tem_UpdataCMPA(unsigned int x);
 
#endif /*LPWM_LED_H_*/
