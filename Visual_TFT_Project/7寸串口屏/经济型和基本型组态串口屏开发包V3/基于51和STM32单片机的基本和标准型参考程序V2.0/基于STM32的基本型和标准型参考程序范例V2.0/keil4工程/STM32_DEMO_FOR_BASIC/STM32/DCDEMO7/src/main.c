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
** 1) ����ע�ͣ�ȥ����������ľ���
** 2) ��ʹ�õ�Ӳ��ƽ̨ΪSTM32F103VCT6 ,ʹ���ڲ�RC����
------------------------------------------------------------------------------------*/

#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_process.h"
#include "stdio.h"
#include "main.h"
#include "hw_config.h"
#include "ulitity.h"

 /*
 ����������һ�����������ȣ���RAM���������£����������һЩ��
 ����ָ��س��������ָ���ֲᣨ��ϵ�еĴ�������������и�����������֧�ֵ�һ��������󳤶���2048�ֽ�
*/
#define CMD_MAX_BUFFER 128 
                          
uint8 cmd_buffer[CMD_MAX_BUFFER];  //����������ջ�����               
uint16 screen_id;                  //ҳ��ID��ű���
uint16 control_id;                 //�ؼ�ID��ű���
volatile uint16 current_screen_id; //��ǰ��Ļ���ڵĻ����ű���
volatile uint32  timer_tick_count; //��ʱ�����ı���

/**************************************************************************************************************
* ��    �ƣ� main
* ��    �ܣ� �������
***************************************************************************************************************/
int main(void)
{
    uint8 cmd_type = 0;
	  uint8 msg_type = 0;
    uint8 control_type = 0;
    qsize  size = 0;
	  uint8 update_en = 1;
    PCTRL_MSG msg = 0;
    /*����ʱ��*/
    Set_System();
    /*���ô����ж�*/
    Interrupts_Config();
    /*����ʱ�ӽ���*/
    systicket_init();
    /*���ڳ�ʼ��,����������Ϊ115200*/
    UartInit(115200);
    /*��մ��ڽ��ջ�����*/
    queue_reset();
  	/*��ʱ�ȴ���������ʼ�����,����ȴ�300ms*/
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
				cmd_type = msg->cmd_type;
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
void OnRecvButton(PCTRL_MSG msg,qsize size)
{
//		  uint8 tem_graph[8] = {0,10,20,30,40,0,50,100};   //�¶�����
//     uint8  button_type = msg->param[0];    //0�����л���1��ť��2���ⰴ��
//     uint8  value = msg->param[1];          //��ť��ֵ
    screen_id = PTR2U16(&msg->screen_id);  //����ID
    control_id = PTR2U16(&msg->control_id);//�ؼ�ID

    /**************************/
    /*-- SCREEM 0�Ļ��洦�� --*/
    /**************************/
    if(screen_id == 0 && control_id == 1)     //����0 IDΪ1�İ�����������
    {
        GetControlValue(1,2);                   //��ȡ��ߵ�ѹ�ı��ؼ���ֵ(����1���ؼ�2)
    }
    else if(screen_id == 0 && control_id == 3)//����0 IDΪ3�İ�����������
    {
        GraphChannelAdd(3,1,0,RED);            //��������¶�����ͨ�� ��ɫ	(����3���ؼ�1��ͨ��0)
    }
    /**************************/
    /*-- SCREEM 2�Ļ��洦�� --*/
    /**************************/
    else if(screen_id == 2 && control_id == 3)//����2 IDΪ3�İ�����������
    {
				ShowControl( 2, 2, VISABLE);            //����2 ID2�Ķ����ؼ���ʾ
        AnimationPlayFrame(2, 1, 1);            //����2 ID1��ͼ��ؼ����ŵ���һ֡
			  SetButtonValue(2,4,0);                  //��ֹͣ���е�ͼ���Ϊ������״̬(����2���ؼ�4)
        AnimationStart(2,2);	                  //��ʼ���Ŵ���Ķ���(����2���ؼ�2)
	
			  AnimationPlayFrame(2 ,1, 1);
    }
    else if(screen_id == 2 && control_id == 4)//����2 IDΪ4�İ�����������
    {
			  ShowControl( 2, 2, VISABLE);            //����2 ID2�Ķ����ؼ���ʾ
			  AnimationPlayFrame(2, 1, 0);            //����2 ID1��ͼ��ؼ����ŵ���0֡
        SetButtonValue(2,3,0);                  //���������е�ͼ���Ϊ������״̬(����2���ؼ�3)
        AnimationStop(2,2);                     //ֹͣ���Ŵ���Ķ���(����2���ؼ�2)

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
    uint8    buf[25];
    uint32 voltage=0;
    uint32 i=0;
    screen_id = PTR2U16(&msg->screen_id);  //����ID
    control_id = PTR2U16(&msg->control_id);//�ؼ�ID

    //TODO: �û�����
    //��ȡϵͳ�Դ���������
    if(screen_id == 1 &&  control_id == 2)
    {
        while(((uint8 *)(&msg->param))[i])
            voltage = voltage*10+ (((uint8 *)(&msg->param))[i++] - 0x30); //�ӽ��ջ�����ȡ��������������֣���ת����ʮ��������
        sprintf((char*)buf,"%d����",voltage/2);                              //��ȡ������������ݳ���2������ʾ����
        SetTextValue( 1, 5,buf);		                                  //��ʾ����ߵ�ѹ/2�ı��ؼ���(����1���ؼ�5)
    }
}

/**************************************************************************************************************
* ��    �ƣ� OnRecvProgress
* ��    �ܣ� ��������Ϣ��Ӧ����
* ��ڲ����� msg-ָ�������size-ָ���С
***************************************************************************************************************/
void OnRecvProgress(PCTRL_MSG msg,qsize size)
{
// 	uint32 value = PTR2U32(msg->param);     //��ֵ
// 	screen_id = PTR2U16(&msg->screen_id);   //����ID
// 	control_id = PTR2U16(&msg->control_id); //�ؼ�ID
    //TODO: �û�����
}

/**************************************************************************************************************
* ��    �ƣ� OnRecvSlider
* ��    �ܣ� ��������Ϣ��Ӧ����
* ��ڲ����� msg-ָ�������size-ָ���С
***************************************************************************************************************/
void OnRecvSlider(PCTRL_MSG msg,qsize size)
{
    uint32 value = PTR2U32(msg->param);     //��ֵ
    screen_id = PTR2U16(&msg->screen_id);   //����ID
    control_id = PTR2U16(&msg->control_id); //�ؼ�ID
    //TODO: �û�����
    if(screen_id ==5 && control_id == 2)   //����5 
    {
        SetBackLight((value*2)%255);       //���ڱ���
    }
}

/**************************************************************************************************************
* ��    �ƣ� OnRecvMeter
* ��    �ܣ� �Ǳ���Ϣ��Ӧ����
* ��ڲ����� msg-ָ�������size-ָ���С
***************************************************************************************************************/
void OnRecvMeter(PCTRL_MSG msg,qsize size)
{
//     uint16 screen_id = PTR2U16(&msg->screen_id);  //����ID
//     uint16 control_id = PTR2U16(&msg->control_id);//�ؼ�ID
//     uint32 value = PTR2U32(msg->param);           //��ֵ
    //TODO: �û�����
}

/**************************************************************************************************************
* ��    �ƣ� OnRecvMeter
* ��    �ܣ� ͼ��ؼ���Ӧ����
* ��ڲ����� msg-ָ�������size-ָ���С
***************************************************************************************************************/
void OnRecvAnimation(PCTRL_MSG msg,qsize size)
{
//     uint16 screen_id = PTR2U16(&msg->screen_id);  //����ID
//     uint16 control_id = PTR2U16(&msg->control_id);//�ؼ�ID
//     uint32 value = PTR2U32(msg->param);           
	
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
