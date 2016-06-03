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

//�ⲿ����30M
# define TEM_IO    GPIO60    //GPIO is the 18b20 data io XA1--A01--XA01
# define DQ        GpioDataRegs.GPBDAT.bit.TEM_IO           //����18B20���ݶ˿� 0utput
# define DQ_DIR    GpioCtrlRegs.GPBDIR.bit.TEM_IO    //����18B20D�ڷ���Ĵ��� 
# define DQ_HIGH() EALLOW;DQ_DIR=0; EDIS        //�������ݿ�Ϊ����
# define DQ_LOW()  EALLOW;DQ_DIR=1; EDIS   //�������ݿ�Ϊ���

extern void TEM_Getinit(void);
extern float  get_temp();

#endif /*DS18B20_H_*/
