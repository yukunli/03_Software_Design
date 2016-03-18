#ifndef LPWM_LED_H_
#define LPWM_LED_H_

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
#define TB_HSPCLKDIV 0x07 // 010:1/4  100:1/8  101: 1/10 110:1/12 111: 1/14
#define TB_CLKDIV  0x07  		// 010:1/4, 011:1/8  110: 1/64 111: 1/128
#define PWM_FRE   3000               // If diff freq. desired, change freq here.TPWM=1/PWM_FRE
#define TBCLK 	  (CPU_CLK/(14*128))
#define SP        TBCLK/(2*PWM_FRE)  //TBPRD=SP

#define TBCTLVAL  0x200E                // Up-down cnt, timebaseTBCLK = SYSCLKOUT/(HSPCLKDIV*CLKDIV)

/***************************************
 * 
 */
extern void EPWM_LED_Init(void);
extern void EPWM_LED_deInit(void);
extern char EPWM_LED_UpdataCMPA(unsigned int x);
 
#endif /*LPWM_LED_H_*/
