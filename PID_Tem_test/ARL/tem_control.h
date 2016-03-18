#ifndef TEM_CONTROL_H_
#define TEM_CONTROL_H_

#include "PWM_tem.h"
/****************************
 * creaded in the nxp on 2016.1.9 
 * describption:
 * to get the enverinment tempreture and control the tempreture of the sensor 
 */
#define TEM_SETVALUE  25   // the temperature set to the value 25 du 
#define OCCUPY_SETVALUE  TEM_SP/2  //the inint occupy rate is TEM_SP/2
 
extern char  Get_new_occupyrate(float temvalue);
extern float Get_Temvalue(void);




#endif /*TEM_CONTROL_H_*/

