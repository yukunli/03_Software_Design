#ifndef DS18B20_H_
#define DS18B20_H_

/*******************************
 * created in the suzhou home in 1/9
 *  description:
 * the file is to get the temperatuer by the 18B20
 * current parameratr": the data line is the  GPIO41  b41
 */
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//外部晶振30M
# define TEM_IO    GPIO60    //GPIO is the 18b20 data io XA1--A01--XA01
# define DQ        GpioDataRegs.GPBDAT.bit.TEM_IO           //定义18B20数据端口 0utput
# define DQ_DIR    GpioCtrlRegs.GPBDIR.bit.TEM_IO    //定义18B20D口方向寄存器 
# define DQ_HIGH() EALLOW;DQ_DIR=0; EDIS        //设置数据口为输入
# define DQ_LOW()  EALLOW;DQ_DIR=1; EDIS   //设置数据口为输出

extern void TEM_Getinit(void);
extern float  get_temp();

#endif /*DS18B20_H_*/
