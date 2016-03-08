#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "stdio.h"
#include "ulitity.h"

#define TIME_100MS 10

volatile uint32  timer_tick_count = 0; //定时器节拍

uint8 cmd_buffer[CMD_MAX_SIZE];//指令缓存

static int32 test_value = 0;//测试值
static uint8 update_en = 0;//更新标记

void UpdateUI();

//程序入口
void main()
{
	qsize  size = 0;
	uint32 timer_tick_last_update = 0;
	
	UartInit();//串口初始化
	
	TimerInit();//定时器初始化

	queue_reset();//清空指令接收缓冲区

	/*延时等待串口屏初始化完毕,必须等待300ms*/
	delay_ms(300);

	while(1)
	{
		size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE); //从缓冲区中获取一条指令        
		if(size>0)//接收到指令
		{
			ProcessMessage((PCTRL_MSG)cmd_buffer, size);
		}

		/****************************************************************************************************************
		特别注意
		MCU不要频繁向串口屏发送数据，否则串口屏的内部缓存区会满，从而导致数据丢失(缓冲区大小：标准型8K，基本型4.7K)
		1) 一般情况下，控制MCU向串口屏发送数据的周期大于100ms，就可以避免数据丢失的问题；
		2) 如果仍然有数据丢失的问题，请判断串口屏的BUSY引脚，为高时不能发送数据给串口屏。
		******************************************************************************************************************/

		//TODO: 添加用户代码
		//数据有更新时，每100毫秒刷新一次
		if(update_en&&timer_tick_count-timer_tick_last_update>=TIME_100MS)
		{
			update_en = 0;
			timer_tick_last_update = timer_tick_count;			

			UpdateUI();	
		}
	}
}

/*! 
 *  \brief  消息处理流程
 *  \param msg 待处理消息
 *  \param size 消息长度
 */
void ProcessMessage( PCTRL_MSG msg, uint16 size )
{
	uint8 cmd_type = msg->cmd_type;//指令类型
	uint8 ctrl_msg = msg->ctrl_msg;   //消息的类型
	uint8 control_type = msg->control_type;//控件类型
	uint16 screen_id = PTR2U16(&msg->screen_id);//画面ID
	uint16 control_id = PTR2U16(&msg->control_id);//控件ID
	uint32 value = PTR2U32(msg->param);//数值

	switch(cmd_type)
	{
	case NOTIFY_SCREEN://切换画面
		NotifyScreen(screen_id);
		break;
	case NOTIFY_TOUCH_PRESS:
	case NOTIFY_TOUCH_RELEASE:
		NotifyTouchXY(cmd_buffer[1],PTR2U16(cmd_buffer+2),PTR2U16(cmd_buffer+4));
		break;	
	case NOTIFY_WRITE_FLASH_OK:
		NotifyWriteFlash(1);
		break;
	case NOTIFY_WRITE_FLASH_FAILD:
		NotifyWriteFlash(0);
		break;
	case NOTIFY_READ_FLASH_OK:
		NotifyReadFlash(1,cmd_buffer+2,size-6);//去除帧头帧尾
		break;
	case NOTIFY_READ_FLASH_FAILD:
		NotifyReadFlash(0,0,0);
		break;
	case NOTIFY_CONTROL:
		{
			switch(control_type)
			{
			case kCtrlButton: //按钮控件
				NotifyButton(screen_id,control_id,msg->param[1]);
				break;
			case kCtrlText://文本控件
				NotifyText(screen_id,control_id,msg->param);
				break;
			case kCtrlProgress: //进度条控件
				NotifyProgress(screen_id,control_id,value);
				break;
			case kCtrlSlider: //滑动条控件
				NotifySlider(screen_id,control_id,value);
				break;
			case kCtrlMeter: //仪表控件
				NotifyMeter(screen_id,control_id,value);
				break;
			case kCtrlMenu://菜单控件
				NotifyMenu(screen_id,control_id,msg->param[0],msg->param[1]);
				break;
			case kCtrlSelector://选择控件
				NotifySelector(screen_id,control_id,msg->param[0]);
				break;
			case kCtrlRTC://倒计时控件
				NotifyTimer(screen_id,control_id);
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
	//TODO: 添加用户代码
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

void SetTextValueInt32(uint16 screen_id, uint16 control_id,int32 value)
{
	uchar buffer[12] = {0};
	sprintf(buffer,"%ld",value);
	SetTextValue(screen_id,control_id,buffer);
}

void UpdateUI()
{
	SetTextValueInt32(0,2,test_value);
	SetProgressValue(0,3,test_value);
	SetSliderValue(0,4,test_value);	
	SetMeterValue(0,7,test_value);
}

/*! 
 *  \brief  按钮控件通知
 *  \details  当按钮状态改变(或调用GetControlValue)时，执行此函数
 *  \param screen_id 画面ID
 *  \param control_id 控件ID
 *  \param state 按钮状态：0弹起，1按下
 */
void NotifyButton(uint16 screen_id, uint16 control_id, uint8  state)
{
	//TODO: 添加用户代码
	if(screen_id==0&&control_id==5)//递增按钮
	{
		if(test_value<100)
			++test_value;
	}
	else if(screen_id==0&&control_id==6)//递减按钮
	{
		if(test_value>0)
			--test_value;
	}

	//UpdateUI();
	update_en = 1;
}

/*! 
 *  \brief  文本控件通知
 *  \details  当文本通过键盘更新(或调用GetControlValue)时，执行此函数
 *  \param screen_id 画面ID
 *  \param control_id 控件ID
 *  \param str 文本控件内容
 */
void NotifyText(uint16 screen_id, uint16 control_id, uint8 *str)
{
	//TODO: 添加用户代码
	sscanf(str,"%ld",&test_value);
	if(test_value>100)
		test_value = 100;
	else if(test_value<0)
		test_value = 0;

	//UpdateUI();
	update_en = 1;
}

/*! 
 *  \brief  进度条控件通知
 *  \details  调用GetControlValue时，执行此函数
 *  \param screen_id 画面ID
 *  \param control_id 控件ID
 *  \param value 值
 */
void NotifyProgress(uint16 screen_id, uint16 control_id, uint32 value)
{
	//TODO: 添加用户代码
}

/*! 
 *  \brief  滑动条控件通知
 *  \details  当滑动条改变(或调用GetControlValue)时，执行此函数
 *  \param screen_id 画面ID
 *  \param control_id 控件ID
 *  \param value 值
 */
void NotifySlider(uint16 screen_id, uint16 control_id, uint32 value)
{
	//TODO: 添加用户代码
	test_value = value;

	//UpdateUI();
	update_en = 1;
}

/*! 
 *  \brief  仪表控件通知
 *  \details  调用GetControlValue时，执行此函数
 *  \param screen_id 画面ID
 *  \param control_id 控件ID
 *  \param value 值
 */
void NotifyMeter(uint16 screen_id, uint16 control_id, uint32 value)
{
	//TODO: 添加用户代码
}

/*! 
 *  \brief  菜单控件通知
 *  \details  当菜单项按下或松开时，执行此函数
 *  \param screen_id 画面ID
 *  \param control_id 控件ID
 *  \param item 菜单项索引
 *  \param state 按钮状态：0松开，1按下
 */
void NotifyMenu(uint16 screen_id, uint16 control_id, uint8  item, uint8  state)
{
	//TODO: 添加用户代码
}

/*! 
 *  \brief  选择控件通知
 *  \details  当选择控件变化时，执行此函数
 *  \param screen_id 画面ID
 *  \param control_id 控件ID
 *  \param item 当前选项
 */
void NotifySelector(uint16 screen_id, uint16 control_id, uint8  item)
{
	//TODO: 添加用户代码
}

/*! 
 *  \brief  定时器超时通知处理
 *  \param screen_id 画面ID
 *  \param control_id 控件ID
 */
void NotifyTimer(uint16 screen_id, uint16 control_id)
{
	//TODO: 添加用户代码
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