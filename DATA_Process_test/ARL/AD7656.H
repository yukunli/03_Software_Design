#ifndef AD7656_H_
#define AD7656_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  "std_init.h"


#define SAMPLE_COUNT  450
#define START_SAMPLING() StartCpuTimer0()
#define STOP_SAMPLING()  StopCpuTimer0()

#define	  AD7656_BASIC    (*((volatile  Uint16 *)0x200000))
//#define	  AD7656_rst      (*((volatile  Uint16 *)0x200008))

#define   AD_BUSY         GpioDataRegs.GPBDAT.bit.GPIO60
#define   SET_ADRST       GpioDataRegs.GPBSET.bit.GPIO61=1
#define   CLEAR_ADRST     GpioDataRegs.GPBCLEAR.bit.GPIO61=1
#define   SET_ADCOV       GpioDataRegs.GPASET.bit.GPIO25=1
#define   CLR_ADCOV       GpioDataRegs.GPACLEAR.bit.GPIO25=1

#define AD_PVEF  10000		// AD reference volte value of positive (mv)
#define AD_CVEF	 (-10000)		// AD reference volte value of cathode (mv)

extern Uint16 SampleTable1[SAMPLE_COUNT];
extern Uint16 SampleTable2[SAMPLE_COUNT];
extern Uint16 SampleTable3[SAMPLE_COUNT];
extern Uint16 SampleTable4[SAMPLE_COUNT];
extern Uint16 SampleTable_None[SAMPLE_COUNT];

extern Uint16 SampleCount;
extern identi_bool volatile SampleCount_Status_Flag;   //it means the data array[SAMPLE_COUNT],window is full

extern float  SampleValue1[SAMPLE_COUNT];
extern float  SampleValue2[SAMPLE_COUNT];
extern float  SampleValue3[SAMPLE_COUNT];
extern float  SampleValue4[SAMPLE_COUNT];

extern void AD7656_ConfigInit(void);
extern void OUTAD_Timer_Init(void);
extern void OUTAD_Variable_Init(void);
extern void OUTAD_Init(void);
extern void AD_Data_Shift(void);
#endif /*AD7656_H_*/
