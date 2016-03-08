/************************************��Ȩ����********************************************
**                             ���ݴ�ʹ��Ƽ����޹�˾
**                             http://www.gz-dc.com
**-----------------------------------�ļ���Ϣ--------------------------------------------
** �ļ�����:   main.c
** ����ʱ��:   2012-06-1
** �ļ�˵��:   ������ģ���������Ļ����������̣�������Ҫ�����Ϣ����Ӧ����
** ����֧�֣�  Tel: 020-82186683  Email: hmi@gz-dc.com Web:www.gz-dc.com

** �޸ļ�¼
** ����: 2012-10-08
** 1) ָ�����queue_find_cmd���֡ͷ�ж�
** 2) �ṹ��CTRL_MSGָ�����ֽڶ��룬������ܻ���ֶ�������
** 3) ���uint32�������Ͷ��壬���޸����ָ�����
** ����: 2013-12-12
** 1) ����ע��
** 2) Ӳ��ƽ̨ STC51��Ƭ�� STC89C52RC �ⲿ���������22.1184M �����ʲ��ܴﵽ115200�������11.0592M�ľ���
      ���뽫�����ʸ�Ϊ57600
------------------------------------------------------------------------------------  */

#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_process.h"
#include "stdio.h"
#include "DefineID.c"
#include "main.h"
#include "ulitity.h"

 /*
 ����������һ�����������ȣ���RAM���������£����������һЩ��
 ����ָ��س��������ָ���ֲᣨ��ϵ�еĴ�������������и�����������֧�ֵ�һ��������󳤶���2048�ֽ�
*/

#define CMD_MAX_BUFFER 40  
uint8  idata cmd_buffer[CMD_MAX_BUFFER];

uint16 idata  screen_id;
uint16 idata  control_id;
uint16 idata  timer_tick_count;
uint16 idata current_screen_id; //��ǰ��Ļ���ڵĻ����ű���

/**************************************************************************************************************
* ��    �ƣ� main
* ��    �ܣ� �������
***************************************************************************************************************/
int main(void)
{

    uint8 idata cmd_type = 0;
	uint8 idata msg_type = 0;
    uint8 idata control_type = 0;
	uint8 update_en = 1;
    qsize  size = 0;
    PCTRL_MSG idata msg = 0;
	  /*����ʱ�ӽ���*/
    systicket_init();
	 /*���ڳ�ʼ��,����������Ϊ115200,����22.1184M �ⲿ����֧�֣������11.0592M���������޸Ĳ�����Ϊ57600*/
    UartInit();
	 /*��մ��ڽ��ջ�����*/
    queue_reset();
	delay_ms(300);
	/*��ʼ���û��ؼ�*/
    iniuserctr();
    while(1)
    {
        /*****************************************************************************
         100ms����һ������
        ����Ƶ�����´����������ݣ���Ȼ�ᵼ�´�����æ����ָ�ʧ(��׼�ʹ�������8K����������������4.7K������)
        �������ȷ���Ƿ���̫Ƶ�������жϴ�������BUSY���ţ�Ϊ��ʱ���ܷ���ָ���������
        ********************************************************************************/
	   
	    if(timer_tick_count%10 == 0 && update_en)
		{		  
			update_en = 0;
			UpDate();//�������ݣ���ѹ���������¶ȣ�ʪ�ȣ�
		}
		else if(timer_tick_count%10 == 1)
		{
		   update_en = 1;
		}
        size = queue_find_cmd(cmd_buffer,CMD_MAX_BUFFER); //�ӻ������л�ȡһ��ָ��
        if(size<=0)//û�н��յ�ָ��
            continue;
        msg = (PCTRL_MSG)cmd_buffer;			

        cmd_type = msg->cmd_type;//ָ������
		 /*���ݽ��յ��Ĵ���������أ�ת����Ӧ�ķ�֧ȥ�����¼�*/
        switch(cmd_type)//ָ������
        {
        case CMD_TOUCH_PRESS_RETURN://���´����������ϴ�
        case CMD_TOUCH_RELEASE_RETURN://�ɿ������������ϴ�
            OnRecvTouchXY(cmd_buffer[1],PTR2U16(cmd_buffer+2),PTR2U16(cmd_buffer+4));
            break;

        case CMD_TYPE_UPDATE_CONTROL://�ؼ�������Ϣ
			 msg_type = msg->ctrl_msg;
        switch(msg_type)//��Ϣ����
        {   
			case kCtrlMsgGetCurrentScreen:					
				OnRecCurrentScreen(msg,size);// ��ȡ��ǰ����ֵ
				break;
			case kCtrlMsgGetData:
				control_type = msg->control_type;//�ؼ�����
				switch(control_type)
				{
				case 	kCtrlMsgGetCurrentScreen:
					OnRecCurrentScreen(msg,size);// ���µ�ǰ����ֵ
				case kCtrlButton:
						OnRecvButton(msg,size);
						break; //��ť�ؼ�����
				case kCtrlText:
						OnRecvText(msg,size);
						break; //�ı��ؼ�����
				case kCtrlProgress:
						OnRecvProgress(msg,size);
						break; //�������ؼ�����
				case kCtrlSlider:
						OnRecvSlider(msg,size);
						break; //�������ؼ� ����
				case kCtrlMeter:
						OnRecvMeter(msg,size);
						break; //�Ǳ�ؼ�����
				case kCtrlAnimation:
						OnRecvAnimation(msg,size);
						break; //ͼ����߶����ؼ�����
				default:
						break;
				}
			 break;
          }
       }
    }
}

/**************************************************************************************************************
* ��    �ƣ� OnRecvChangeScreen
* ��    �ܣ� �����л���Ϣ��Ӧ����
* ��ڲ����� screen_id-�л���Ļ���ID
***************************************************************************************************************/
void OnRecvChangeScreen(uint16 screen_id)
{
    //TODO: �û�����
}

/**************************************************************************************************************
* ��    �ƣ� OnRecvTouchXY
* ��    �ܣ� �������������Ӧ
* ��ڲ����� press-1���´�������3�ɿ�������
* ��ڲ����� x-����X����
* ��ڲ����� y-����y����
***************************************************************************************************************/
void OnRecvTouchXY(uint8 press,uint16 x,uint16 y)
{
    //TODO: �û�����
}

/**************************************************************************************************************
* ��    �ƣ� OnRecvButton
* ��    �ܣ� ��ť��Ϣ��Ӧ����
* ��ڲ����� msg-ָ�������size-ָ���С
***************************************************************************************************************/
uint8  ICON_run_status = 0;
uint8  ICON_fans_status = 0;
uint8  ICON_wind_status =0;
void OnRecvButton(PCTRL_MSG msg,qsize size)
{
    uint8  button_type = msg->param[0];   //0�����л���1��ť��2���ⰴ��
    uint8  value = msg->param[1];         //��ť��ֵ
    screen_id = PTR2U16(&msg->screen_id); //����ID
    control_id = PTR2U16(&msg->control_id);//�ؼ�ID
	  /**************************/
	  /*-- SCREEM 0�Ļ��洦�� --*/
	  /**************************/
    if(screen_id == 0 && control_id == 1)    //����0 IDΪ1�İ�����������
    {
		GetControlValue(1,2);                //��ȡ��ߵ�ѹ�ı��ؼ���ֵ	(����1���ؼ�2)
    }
	else if(screen_id== 0 && control_id == 3)//����0 IDΪ3�İ�����������
	{
		GraphChannelAdd(3,1,0,RED);           //��������¶�����ͨ�� ��ɫ	(����3���ؼ�1��ͨ��0)
	
    }
	 /**************************/
	  /*-- SCREEM 2�Ļ��洦�� --*/
	  /**************************/
    else if(screen_id == 2 && control_id == 3)//����2 IDΪ3�İ�����������
    {
		ShowControl( 2, 2, VISABLE);            //����2 ID2�Ķ����ؼ���ʾ
        AnimationPlayFrame(2, 1, 1);            //����2 ID1��ͼ��ؼ����ŵ���һ֡
	    SetButtonValue(2,4,0);                  //��ֹͣ���е�ͼ���Ϊ������״̬
        AnimationStart(2,2);	 				 //��ʼ���Ŵ���Ķ���(����2���ؼ�2)
    }
   else if(screen_id == 2 && control_id == 4 )//����2 IDΪ4�İ�����������
	{
	     ShowControl( 2, 2, VISABLE);         //����2 ID2�Ķ����ؼ���ʾ
	      AnimationPlayFrame(2, 1, 0);        //����2 ID1��ͼ��ؼ����ŵ���0֡
		  SetButtonValue( 2, 3, 0);           //���������е�ͼ���Ϊ������״̬
		  AnimationStop(2,2);		          //ֹͣ���Ŵ���Ķ���	(����2���ؼ�2)
    }
 	 else if(screen_id == 2 && control_id == 6)//����2 IDΪ6�İ�����������
    {
		SetButtonValue(2,4,0);                  //��ֹͣ���е�ͼ���Ϊ������״̬(����2���ؼ�4)
		SetButtonValue(2,3,0);                  //�������������е�ͼ���Ϊ������״̬(����2���ؼ�4)
		ShowControl( 2, 2,UNVISABLE);           //�����ؼ�����
        AnimationPlayFrame(2, 1, 2);            //ͼ���ļ����ŵ�����֡��͸��֡�������أ�
    }

} 

/**************************************************************************************************************
* ��    �ƣ� OnRecvText
* ��    �ܣ� �ı��ؼ���Ϣ��Ӧ����
* ��ڲ����� msg-ָ�������size-ָ���С
***************************************************************************************************************/
void OnRecvText(PCTRL_MSG msg,qsize size)
{
	uint8 buf[25];
	uint16 voltage=0;
	uint16 i=0;
    screen_id = PTR2U16(&msg->screen_id);  //����ID
    control_id = PTR2U16(&msg->control_id);//�ؼ�ID

    //TODO: �û�����

	//��ȡϵͳ�Դ���������
	if(screen_id == 1 &&  control_id == 2)
	{	
		while(((uint8 *)(&msg->param))[i])
        voltage = voltage*10+ (((uint8 *)(&msg->param))[i++] - 0x30);//�ӽ��ջ�����ȡ��һ���ֽ����ݣ���ת����ʮ��������
		//��ʾ����ߵ�ѹ/2
		voltage  = 		voltage/2;
		//ֻ����֧��3λ��
		buf[0] = voltage/100 +0x30;			     	  //��λ
		buf[1] = (voltage- voltage/100*100)/10 +0x30; //ʮλ
		buf[2] = (voltage)%10+0X30;					  //��λ
        buf[3] = 0;
		if(buf[0] == 0x30 && buf[1] == 0x30)         //��λ��ʮλ��Ϊ0
	   {
		 buf[0] = buf[2];
		 buf[1] = 0;
		 buf[2] = 0;
	   }
	   else if(buf[0] == 0x30)						//��λΪ0
	  {
		buf[0] = buf[1];
		buf[1] = buf[2];
		buf[2] = 0;
	  }
		SetTextValue( 1, 5,buf); //��ʾ����ߵ�ѹ/2�ı��ؼ�(����1���ؼ�5)
  }
}

/**************************************************************************************************************
* ��    �ƣ� OnRecvProgress
* ��    �ܣ� ��������Ϣ��Ӧ����
* ��ڲ����� msg-ָ�������size-ָ���С
***************************************************************************************************************/
void OnRecvProgress(PCTRL_MSG msg,qsize size)
{
    uint16 value = PTR2U32(msg->param);    //��ֵ
    screen_id = PTR2U16(&msg->screen_id);  //����ID
    control_id = PTR2U16(&msg->control_id);//�ؼ�ID
    //TODO: �û�����
}

/**************************************************************************************************************
* ��    �ƣ� OnRecvSlider
* ��    �ܣ� ��������Ϣ��Ӧ����
* ��ڲ����� msg-ָ�������size-ָ���С
***************************************************************************************************************/
void OnRecvSlider(PCTRL_MSG msg,qsize size)
{
    uint16 value = PTR2U32(msg->param);  //��ֵ
    screen_id = PTR2U16(&msg->screen_id);//����ID
    control_id = PTR2U16(&msg->control_id);//�ؼ�ID
    //TODO: �û�����
	if(screen_id ==5 &&  control_id == 2)
   {
     SetBackLight((value*2)%255);//���ڱ���
   }
}

/**************************************************************************************************************
* ��    �ƣ� OnRecvMeter
* ��    �ܣ� �Ǳ���Ϣ��Ӧ����
* ��ڲ����� msg-ָ�������size-ָ���С
***************************************************************************************************************/
void OnRecvMeter(PCTRL_MSG msg,qsize size)
{
    uint16 screen_id = PTR2U16(&msg->screen_id); //����ID
    uint16 control_id = PTR2U16(&msg->control_id);//�ؼ�ID
    uint16 value = PTR2U32(msg->param);           //��ֵ

    //TODO: �û�����
}
 /**************************************************************************************************************
* ��    �ƣ� OnRecvMeter
* ��    �ܣ� ͼ��ؼ���Ӧ����
* ��ڲ����� msg-ָ�������size-ָ���С
***************************************************************************************************************/
void OnRecvAnimation(PCTRL_MSG msg,qsize size)
{
    uint16 screen_id = PTR2U16(&msg->screen_id);  //����ID
    uint16 control_id = PTR2U16(&msg->control_id);//�ؼ�ID
    uint16 value = PTR2U32(msg->param);           
	
    //TODO: �û�����
}
/**************************************************************************************************************
* ��    �ƣ� OnRecCurrentScreen
* ��    �ܣ� ����״̬��Ӧ����
* ��ڲ����� msg-ָ�������size-ָ���С
***************************************************************************************************************/

void	OnRecCurrentScreen(PCTRL_MSG msg,qsize size)
{
	 current_screen_id = PTR2U16(&msg->screen_id);
}