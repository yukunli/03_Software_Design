#ifndef AD9833_H_
#define AD9833_H_

#define  ad9833_sdata   GpioDataRegs.GPCDAT.bit.GPIO81
#define  ad9833_sclk    GpioDataRegs.GPBDAT.bit.GPIO47
#define  ad9833_fsync1  GpioDataRegs.GPBDAT.bit.GPIO41
#define  ad9833_fsync2  GpioDataRegs.GPBDAT.bit.GPIO43
#define  ad9833_fsync3  GpioDataRegs.GPBDAT.bit.GPIO45

#define CH1_OUT_FRE  5000
#define CH2_OUT_FRE  5000
#define CH3_OUT_FRE  5000

#define CSIN_Channel_1 0x01
#define CSIN_Channel_2 0x02
#define CSIN_Channel_3 0x03


extern void AD9833_configinit(void);
extern void delay(unsigned int m);
extern void write_ad9833_d16(unsigned int x,char change);
extern void AD9833_Reset(char channel);
extern void AD9833_Outdata(char change,double frequence,unsigned int frequence_SFR,unsigned int WAVE_MODE,unsigned int Phase);

#endif /*AD9833_H_*/
