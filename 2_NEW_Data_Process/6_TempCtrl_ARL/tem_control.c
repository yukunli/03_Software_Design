


#include "PWM_tem.h"
#include "std_init.h"
#include "tem_control.h"

/**********************************
 * define
 */
//PID变量
float PID_KI = 1;
float PID_KP = 0.2;
unsigned long PID_y1 = 0;
unsigned long PID_y0 = 0;
long PID_eut = 0;
float Fresh_occupyvalue = OCCUPY_SETVALUE ; // the init occupyrate is   0% : TEM_SP:0% ;TEM_SP_SP/2:50% 0: 100%
long PID_e1 = 0;
long PID_e0 = 0;
long PID_de = 0;




/***********************************
* CODE
*/
/**********************************
 * fuction: 
 * parameter : get back the tem value 
 */
float Get_Temvalue(void)
{
	
	return 28.5;
}

/**********************************
 * funciton: get the new occupy rate to control the temperature
 * parameter: return the  new occupy rate
 */
char  Get_new_occupyrate(float temvalue)
{
	char tem_Upda_statu;
	PID_y0 = PID_y1;
	PID_y1 = temvalue;
	PID_e0 = PID_y0 - TEM_SETVALUE;//上次偏差
	PID_e1 = PID_y1 - TEM_SETVALUE;//本次偏差
	PID_de = PID_e1 - PID_e0;
	PID_eut = PID_KP * PID_de + PID_KI * PID_e1;
	Fresh_occupyvalue = Fresh_occupyvalue - PID_eut;
	//if  the Fresh_occupyvalue is bigger than TEM_SP = 100 or the -0
	if( 0 < Fresh_occupyvalue < TEM_SP )
		tem_Upda_statu = EPWM_tem_UpdataCMPA(Fresh_occupyvalue);
	else if (Fresh_occupyvalue > TEM_SP)
		tem_Upda_statu = EPWM_tem_UpdataCMPA(TEM_SP);
	else
		tem_Upda_statu = EPWM_tem_UpdataCMPA(0);
	
	return tem_Upda_statu;
}




//********************************
// no more 
//********************************

