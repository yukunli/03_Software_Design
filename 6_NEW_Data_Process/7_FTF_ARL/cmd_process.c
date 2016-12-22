
#include "cmd_process.h"
#include "stdio.h"

/* 
 *  \brief  消息处理流程，此处一般不需要更改
 *  \param msg 待处理消息
 *  \param size 消息长度
 */
void ProcessMessage( PCTRL_MSG msg, uint16 size, Water_Param *InterfaceParam)
{
	uint8 cmd_type = msg->cmd_type;		//指令类型
	//uint8 ctrl_msg = msg->ctrl_msg;   //消息的类型
	uint8 control_type = msg->control_type;			//控件类型
	uint16 screen_id = msg->screen_id1;	//画面ID
	uint16 control_id = msg->control_id1;	//控件ID
	//uint32 value = PTR2U32(msg->param);  //数值

	switch(cmd_type)
	{
	case NOTIFY_SCREEN:		//切换画面
		NotifyScreen(screen_id);
		break;
	case NOTIFY_TOUCH_PRESS:
	case NOTIFY_TOUCH_RELEASE:
		//NotifyTouchXY(cmd_buffer[1],PTR2U16(cmd_buffer+2),PTR2U16(cmd_buffer+4));
		break;	
	case NOTIFY_WRITE_FLASH_OK:
		NotifyWriteFlash(1);
		break;
	case NOTIFY_WRITE_FLASH_FAILD:
		NotifyWriteFlash(0);
		break;
	case NOTIFY_READ_FLASH_OK:
		//NotifyReadFlash(1,cmd_buffer+2,size-6);//去除帧头帧尾
		break;
	case NOTIFY_READ_FLASH_FAILD:
		NotifyReadFlash(0,0,0);
		break;
	case NOTIFY_CONTROL:
		{
			switch(control_type)
			{
			case kCtrlButton: //按钮控件0x10
				NotifyButton(screen_id, control_id, msg->param[1]);
				break;
			case kCtrlText://文本控件0x11
				NotifyText(screen_id, control_id, msg->param, InterfaceParam);
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

/*! 
 *  \brief  画面切换通知
 *  \details  当前画面改变时(或调用GetScreen)，执行此函数
 *  \param screen_id 当前画面ID
 */
void NotifyScreen(uint16 screen_id)
{
	
}

/*! 
 *  \brief  触摸坐标事件响应
 *  \param press 1按下触摸屏，3松开触摸屏
 *  \param x x坐标
 *  \param y y坐标
 */
void NotifyTouchXY(uint8 press,uint16 x,uint16 y)
{
	//TODO: 添加用户代码
}
//**************************
/*函数功能： 将浮点数转换为SCII码，用于在触摸屏显示
 * 输入： 浮点数
 * 约束： 针对格式为XX.XXX
 **/
void FloatToISCII(float floatnum, uint8 *iscii)
{
	uint16 float_int = 0;
	float_int = (unsigned int)(floatnum * 100);
	iscii[0]=(float_int/1000)%10+0x30;	
	if(iscii[0]!=0x30)
	{
		iscii[1]=(float_int/100)%10+0x30;	//整数部分的个位
		iscii[2]='.';
		iscii[3]=(float_int/10)%10+0x30;	//小数部分的十位
		iscii[4]=float_int%10+0x30;	//小数部分的个位
		iscii[5]='\0';	
		return;		
	}
	else
	{	
		iscii[0]=(float_int/100)%10 + 0x30;	//整数部分的个位
		iscii[0]=(float_int/100)%10 + 0x30;	//整数部分的个位
		iscii[1]='.';
		iscii[2]=(float_int/10)%10+0x30;	//小数部分的十位
		iscii[3]=float_int%10+0x30;	//小数部分的个位
		iscii[4]='\0';
		iscii[5]='\0';
	}
}
//**************************
/*函数功能： 将浮点数转换为SCII码，用于在触摸屏显示
 * 输入： 浮点数
 * 约束： 针对格式为XX.XXX
 **/
void Float2ISCII(float floatnum, uint8 *iscii)
{
	uint16 float_int = 0;
	float_int = (unsigned int)(floatnum * 1000);
	iscii[0]=(float_int/10000)%10+0x30;	   //得到浮点数的整数部分十位
	if(iscii[0]!=0x30)
	{
		iscii[1]=(float_int/1000)%10+0x30;	//整数部分的个位
		iscii[2]='.';
		iscii[3]=(float_int/100)%10+0x30;	//小数部分的十位
		iscii[4]=(float_int/10)%10+0x30;	      //小数部分的个位
		iscii[5]=float_int%10+0x30;	      //小数部分的个位
		iscii[6]='\0';	
		return;		
	}
	else
	{	
		iscii[0]=(float_int/1000)%10 + 0x30;	//整数部分的个位
		iscii[1]='.';
		iscii[2]=(float_int/100)%10 + 0x30;	//整数部分的个位
		iscii[3]=(float_int/10)%10+0x30;	//小数部分的十位
		iscii[4]=float_int%10+0x30;	        //小数部分的个位
		iscii[5]='\0';
	}
}
//初始化UI，
void InitUI(Water_Param *InterfaceParam)
{
	uint8 TEMdat[7] = {0};
	FloatToISCII(InterfaceParam->Water_b, TEMdat);
	SetTextValue( 1, 4,TEMdat);	//当前截距（画面1控件3）
	
	FloatToISCII(InterfaceParam->Water_k, TEMdat);
	SetTextValue( 1, 3,TEMdat);	//当前斜率（画面1控件4）
	
	FloatToISCII(InterfaceParam->PID_Kp, TEMdat);
	SetTextValue( 1, 6,TEMdat);	//当前kp（画面1控件7）
	
	FloatToISCII(InterfaceParam->PID_Ki, TEMdat);
	SetTextValue( 1, 7,TEMdat);	//当前ki（画面1控件7）
	
	FloatToISCII(InterfaceParam->PID_Kd, TEMdat);
	SetTextValue( 1, 8,TEMdat);	//当前kd（画面1控件7）
	
	//添加曲线控件数据通道
	GraphChannelAdd(2,2,0,0x07E0);
	
}
//更新界面控件显示
void UpdateUI(Water_Value * InterfaceValue, float debug_T)
{
	uint8 water_curve = 0;
	uint8 TEMdat[7] = {0};
	//更新曲线控件
	water_curve = (uint8)((InterfaceValue->WaterValue)*28.33-28.33);  //转换：把坐标范围转换到曲线控件的高度范围内（界面高度是1-10,255）
	GraphChannelDataAdd(2,2,0,&water_curve,1); //添加水分曲线的数据（依次为 屏幕ID，控件ID，通道号，数据，数据长度）
	
	FloatToISCII(InterfaceValue->WaterValue, TEMdat);
	//更新文本显示控件
    SetTextValue( 0, 3,TEMdat);	//当前物料水分（画面0控件3）
    //SetTextValue( 3, 6,TEMdat);	//当前物料水分（画面3控件6）
    
	FloatToISCII(InterfaceValue->SoonWaterValue, TEMdat);
	//更新文本显示控件
	SetTextValue( 0, 5,TEMdat);	//瞬时水分（画面0控件5）
	SetTextValue( 3, 5,TEMdat);	//瞬时水分（画面3控件5）
	
	FloatToISCII(InterfaceValue->temperature, TEMdat);
	TEMdat[4]= '\0'; //温度只显示1位小数
	TEMdat[5]= '\0';
   
   //更新文本显示控件
    SetTextValue( 0, 4,TEMdat);	//实时温度（画面0控件4）
	SetTextValue( 3, 4,TEMdat);	//实时温度（画面3控件4）

	//用于触摸屏调试模式
	if(debug_T == 0)
	{
		return;
	}
	else
	{
		Float2ISCII(debug_T, TEMdat);
		//更新文本显示控件
    	SetTextValue( 3, 6,TEMdat);	//当前物料水分（画面3控件6）
	}
	return;
}

/*! 
 *  \brief  按钮控件通知
 *  \details  当按钮状态改变(或调用GetControlValue)时，执行此函数
 *  \param screen_id 画面ID
 *  \param control_id 控件ID
 *  \param state 按钮状态：0弹起，1按下
 */
void NotifyButton(uint16 screen_id, uint16 control_id, uint8 state)
{
	//TODO: 添加用户代码
	if (screen_id == 1&& control_id == 1) //设置页面的保存按钮被按下
	{  
		if(0x01 == state)     //按钮被按下
		{
			//获取修正参数-斜率和截距
			GetControlValue(1,3);
			GetControlValue(1,4);
		} 

	}
	
	return;
}

//******************
/* 函数功能：将 string 转换为浮点数
 * 参数： 浮点数
 * 约束： 适用于XX.XX
 */
float StrToFloat(uint8 *str)
{
	uint8  i = 0;
	uint8 text_recevice[6] = {0};
	if(str[0] == 0x2d)   //表示有负数
	{  
		if (str[3] == 0x2e) 	//如果第三位是“.”
	{
		str[3] = 0x30;
		for(i = 1; i < 6; i++ )
		{
			text_recevice[i] = str[i] - 0x30;
			i++;
		}
		return (-1)*(text_recevice[1]*10 + text_recevice[2]+ text_recevice[4]*0.1 + text_recevice[5]*0.01);
	}
	else
	{
		str[2] = 0x30;
		for(i = 1; i <6;i++ )
		{
			text_recevice[i] = str[i] - 0x30;
			i++;
		}
		return (-1)*(text_recevice[1] + text_recevice[3]*0.1 + text_recevice[4]*0.01);
	}
	}
	else
	{
	if (str[2] == 0x2e) 	//如果第三位是“.”
	{
		str[2] = 0x30;
		for(i = 0; i < 5; i++ )
		{
			text_recevice[i] = str[i] - 0x30;
			i++;
		}
		return (text_recevice[0]*10 + text_recevice[1]+ text_recevice[3]*0.1 + text_recevice[4]*0.01);
	}
	else
	{
		str[1] = 0x30;
		for(i = 0; i <5;i++ )
		{
			text_recevice[i] = str[i] - 0x30;
			i++;
		}
		return (text_recevice[0] + text_recevice[2]*0.1 + text_recevice[3]*0.01);
	}
	}
}
/*! 
 *  \brief  文本控件通知
 *  \details  当文本通过键盘更新(或调用GetControlValue)时，执行此函数
 *  \param screen_id 画面ID
 *  \param control_id 控件ID
 *  \param str 文本控件内容 形式为： 【该位可能没有】 32  2E 31 34 00
 */
void NotifyText(uint16 screen_id, uint16 control_id, uint8 *str, Water_Param *InterfaceParam)
{
	//TODO: 添加用户代码
	if (screen_id == 1&& control_id == 3) //更新设置页面的斜率
	{       
		InterfaceParam->Water_k = StrToFloat(str);
		return;
	}
	else if (screen_id == 1&& control_id == 4) //更新设置页面的截距
	{
		InterfaceParam->Water_b = StrToFloat(str);
		return;
	}/*
	else if (screen_id == 1&& control_id == 5) //更新设置页面的量程
	{
		return;
	}*/
	else if (screen_id == 1&& control_id == 7) //更新设置页面的 KI
	{       
		InterfaceParam->PID_Ki = StrToFloat(str);
		return;
	}
	else if (screen_id == 1&& control_id == 6) //更新设置页面的 Kp
	{        
		InterfaceParam->PID_Kp = StrToFloat(str);
		return;
	}
	else if (screen_id == 1&& control_id == 8) //更新设置页面的 Kd
	{      
		InterfaceParam->PID_Kd = StrToFloat(str);
		return;
	}
	return;
}

/*! 
 *  \brief  读取用户FLASH状态返回
 *  \param status 0失败，1成功
 *  \param _data 返回数据
 *  \param length 数据长度
 */
void NotifyReadFlash(uint8 status,uint8 *_data,uint16 length)
{
	//TODO: 添加用户代码
}

/*! 
 *  \brief  写用户FLASH状态返回
 *  \param status 0失败，1成功
 */
void NotifyWriteFlash(uint8 status)
{
	//TODO: 添加用户代码
}

//no more

