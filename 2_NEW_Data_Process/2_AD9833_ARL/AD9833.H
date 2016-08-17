#ifndef AD9833_H_
#define AD9833_H_

#define  ad9833_sdata   GpioDataRegs.GPADAT.bit.GPIO30
#define  ad9833_sclk    GpioDataRegs.GPADAT.bit.GPIO31
#define  ad9833_fsync1  GpioDataRegs.GPCDAT.bit.GPIO82
#define  ad9833_fsync2  GpioDataRegs.GPCDAT.bit.GPIO83
#define  ad9833_fsync3  GpioDataRegs.GPBDAT.bit.GPIO39

#define CH1_OUT_FRE  1000.0
#define CH2_OUT_FRE  2000.0
#define CH3_OUT_FRE  3000.0

#define CSIN_Channel_1 0x01
#define CSIN_Channel_2 0x02
#define CSIN_Channel_3 0x03


extern void AD9833_configinit(void);
void delay(unsigned int m);
void write_ad9833_d16(unsigned int x);
extern void AD9833_Reset(unsigned char channel);
extern void AD9833_Outdata(unsigned char change,float frequence,unsigned char frequence_SFR,unsigned char WAVE_MODE,unsigned char Phase);

#endif /*AD9833_H_*/
