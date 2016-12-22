
#include "cmd_process.h"
#include "stdio.h"

/* 
 *  \brief  ��Ϣ�������̣��˴�һ�㲻��Ҫ����
 *  \param msg ��������Ϣ
 *  \param size ��Ϣ����
 */
void ProcessMessage( PCTRL_MSG msg, uint16 size, Water_Param *InterfaceParam)
{
	uint8 cmd_type = msg->cmd_type;		//ָ������
	//uint8 ctrl_msg = msg->ctrl_msg;   //��Ϣ������
	uint8 control_type = msg->control_type;			//�ؼ�����
	uint16 screen_id = msg->screen_id1;	//����ID
	uint16 control_id = msg->control_id1;	//�ؼ�ID
	//uint32 value = PTR2U32(msg->param);  //��ֵ

	switch(cmd_type)
	{
	case NOTIFY_SCREEN:		//�л�����
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
		//NotifyReadFlash(1,cmd_buffer+2,size-6);//ȥ��֡ͷ֡β
		break;
	case NOTIFY_READ_FLASH_FAILD:
		NotifyReadFlash(0,0,0);
		break;
	case NOTIFY_CONTROL:
		{
			switch(control_type)
			{
			case kCtrlButton: //��ť�ؼ�0x10
				NotifyButton(screen_id, control_id, msg->param[1]);
				break;
			case kCtrlText://�ı��ؼ�0x11
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
 *  \brief  �����л�֪ͨ
 *  \details  ��ǰ����ı�ʱ(�����GetScreen)��ִ�д˺���
 *  \param screen_id ��ǰ����ID
 */
void NotifyScreen(uint16 screen_id)
{
	
}

/*! 
 *  \brief  ���������¼���Ӧ
 *  \param press 1���´�������3�ɿ�������
 *  \param x x����
 *  \param y y����
 */
void NotifyTouchXY(uint8 press,uint16 x,uint16 y)
{
	//TODO: ����û�����
}
//**************************
/*�������ܣ� ��������ת��ΪSCII�룬�����ڴ�������ʾ
 * ���룺 ������
 * Լ���� ��Ը�ʽΪXX.XXX
 **/
void FloatToISCII(float floatnum, uint8 *iscii)
{
	uint16 float_int = 0;
	float_int = (unsigned int)(floatnum * 100);
	iscii[0]=(float_int/1000)%10+0x30;	
	if(iscii[0]!=0x30)
	{
		iscii[1]=(float_int/100)%10+0x30;	//�������ֵĸ�λ
		iscii[2]='.';
		iscii[3]=(float_int/10)%10+0x30;	//С�����ֵ�ʮλ
		iscii[4]=float_int%10+0x30;	//С�����ֵĸ�λ
		iscii[5]='\0';	
		return;		
	}
	else
	{	
		iscii[0]=(float_int/100)%10 + 0x30;	//�������ֵĸ�λ
		iscii[0]=(float_int/100)%10 + 0x30;	//�������ֵĸ�λ
		iscii[1]='.';
		iscii[2]=(float_int/10)%10+0x30;	//С�����ֵ�ʮλ
		iscii[3]=float_int%10+0x30;	//С�����ֵĸ�λ
		iscii[4]='\0';
		iscii[5]='\0';
	}
}
//**************************
/*�������ܣ� ��������ת��ΪSCII�룬�����ڴ�������ʾ
 * ���룺 ������
 * Լ���� ��Ը�ʽΪXX.XXX
 **/
void Float2ISCII(float floatnum, uint8 *iscii)
{
	uint16 float_int = 0;
	float_int = (unsigned int)(floatnum * 1000);
	iscii[0]=(float_int/10000)%10+0x30;	   //�õ�����������������ʮλ
	if(iscii[0]!=0x30)
	{
		iscii[1]=(float_int/1000)%10+0x30;	//�������ֵĸ�λ
		iscii[2]='.';
		iscii[3]=(float_int/100)%10+0x30;	//С�����ֵ�ʮλ
		iscii[4]=(float_int/10)%10+0x30;	      //С�����ֵĸ�λ
		iscii[5]=float_int%10+0x30;	      //С�����ֵĸ�λ
		iscii[6]='\0';	
		return;		
	}
	else
	{	
		iscii[0]=(float_int/1000)%10 + 0x30;	//�������ֵĸ�λ
		iscii[1]='.';
		iscii[2]=(float_int/100)%10 + 0x30;	//�������ֵĸ�λ
		iscii[3]=(float_int/10)%10+0x30;	//С�����ֵ�ʮλ
		iscii[4]=float_int%10+0x30;	        //С�����ֵĸ�λ
		iscii[5]='\0';
	}
}
//��ʼ��UI��
void InitUI(Water_Param *InterfaceParam)
{
	uint8 TEMdat[7] = {0};
	FloatToISCII(InterfaceParam->Water_b, TEMdat);
	SetTextValue( 1, 4,TEMdat);	//��ǰ�ؾࣨ����1�ؼ�3��
	
	FloatToISCII(InterfaceParam->Water_k, TEMdat);
	SetTextValue( 1, 3,TEMdat);	//��ǰб�ʣ�����1�ؼ�4��
	
	FloatToISCII(InterfaceParam->PID_Kp, TEMdat);
	SetTextValue( 1, 6,TEMdat);	//��ǰkp������1�ؼ�7��
	
	FloatToISCII(InterfaceParam->PID_Ki, TEMdat);
	SetTextValue( 1, 7,TEMdat);	//��ǰki������1�ؼ�7��
	
	FloatToISCII(InterfaceParam->PID_Kd, TEMdat);
	SetTextValue( 1, 8,TEMdat);	//��ǰkd������1�ؼ�7��
	
	//������߿ؼ�����ͨ��
	GraphChannelAdd(2,2,0,0x07E0);
	
}
//���½���ؼ���ʾ
void UpdateUI(Water_Value * InterfaceValue, float debug_T)
{
	uint8 water_curve = 0;
	uint8 TEMdat[7] = {0};
	//�������߿ؼ�
	water_curve = (uint8)((InterfaceValue->WaterValue)*28.33-28.33);  //ת���������귶Χת�������߿ؼ��ĸ߶ȷ�Χ�ڣ�����߶���1-10,255��
	GraphChannelDataAdd(2,2,0,&water_curve,1); //���ˮ�����ߵ����ݣ�����Ϊ ��ĻID���ؼ�ID��ͨ���ţ����ݣ����ݳ��ȣ�
	
	FloatToISCII(InterfaceValue->WaterValue, TEMdat);
	//�����ı���ʾ�ؼ�
    SetTextValue( 0, 3,TEMdat);	//��ǰ����ˮ�֣�����0�ؼ�3��
    //SetTextValue( 3, 6,TEMdat);	//��ǰ����ˮ�֣�����3�ؼ�6��
    
	FloatToISCII(InterfaceValue->SoonWaterValue, TEMdat);
	//�����ı���ʾ�ؼ�
	SetTextValue( 0, 5,TEMdat);	//˲ʱˮ�֣�����0�ؼ�5��
	SetTextValue( 3, 5,TEMdat);	//˲ʱˮ�֣�����3�ؼ�5��
	
	FloatToISCII(InterfaceValue->temperature, TEMdat);
	TEMdat[4]= '\0'; //�¶�ֻ��ʾ1λС��
	TEMdat[5]= '\0';
   
   //�����ı���ʾ�ؼ�
    SetTextValue( 0, 4,TEMdat);	//ʵʱ�¶ȣ�����0�ؼ�4��
	SetTextValue( 3, 4,TEMdat);	//ʵʱ�¶ȣ�����3�ؼ�4��

	//���ڴ���������ģʽ
	if(debug_T == 0)
	{
		return;
	}
	else
	{
		Float2ISCII(debug_T, TEMdat);
		//�����ı���ʾ�ؼ�
    	SetTextValue( 3, 6,TEMdat);	//��ǰ����ˮ�֣�����3�ؼ�6��
	}
	return;
}

/*! 
 *  \brief  ��ť�ؼ�֪ͨ
 *  \details  ����ť״̬�ı�(�����GetControlValue)ʱ��ִ�д˺���
 *  \param screen_id ����ID
 *  \param control_id �ؼ�ID
 *  \param state ��ť״̬��0����1����
 */
void NotifyButton(uint16 screen_id, uint16 control_id, uint8 state)
{
	//TODO: ����û�����
	if (screen_id == 1&& control_id == 1) //����ҳ��ı��水ť������
	{  
		if(0x01 == state)     //��ť������
		{
			//��ȡ��������-б�ʺͽؾ�
			GetControlValue(1,3);
			GetControlValue(1,4);
		} 

	}
	
	return;
}

//******************
/* �������ܣ��� string ת��Ϊ������
 * ������ ������
 * Լ���� ������XX.XX
 */
float StrToFloat(uint8 *str)
{
	uint8  i = 0;
	uint8 text_recevice[6] = {0};
	if(str[0] == 0x2d)   //��ʾ�и���
	{  
		if (str[3] == 0x2e) 	//�������λ�ǡ�.��
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
	if (str[2] == 0x2e) 	//�������λ�ǡ�.��
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
 *  \brief  �ı��ؼ�֪ͨ
 *  \details  ���ı�ͨ�����̸���(�����GetControlValue)ʱ��ִ�д˺���
 *  \param screen_id ����ID
 *  \param control_id �ؼ�ID
 *  \param str �ı��ؼ����� ��ʽΪ�� ����λ����û�С� 32  2E 31 34 00
 */
void NotifyText(uint16 screen_id, uint16 control_id, uint8 *str, Water_Param *InterfaceParam)
{
	//TODO: ����û�����
	if (screen_id == 1&& control_id == 3) //��������ҳ���б��
	{       
		InterfaceParam->Water_k = StrToFloat(str);
		return;
	}
	else if (screen_id == 1&& control_id == 4) //��������ҳ��Ľؾ�
	{
		InterfaceParam->Water_b = StrToFloat(str);
		return;
	}/*
	else if (screen_id == 1&& control_id == 5) //��������ҳ�������
	{
		return;
	}*/
	else if (screen_id == 1&& control_id == 7) //��������ҳ��� KI
	{       
		InterfaceParam->PID_Ki = StrToFloat(str);
		return;
	}
	else if (screen_id == 1&& control_id == 6) //��������ҳ��� Kp
	{        
		InterfaceParam->PID_Kp = StrToFloat(str);
		return;
	}
	else if (screen_id == 1&& control_id == 8) //��������ҳ��� Kd
	{      
		InterfaceParam->PID_Kd = StrToFloat(str);
		return;
	}
	return;
}

/*! 
 *  \brief  ��ȡ�û�FLASH״̬����
 *  \param status 0ʧ�ܣ�1�ɹ�
 *  \param _data ��������
 *  \param length ���ݳ���
 */
void NotifyReadFlash(uint8 status,uint8 *_data,uint16 length)
{
	//TODO: ����û�����
}

/*! 
 *  \brief  д�û�FLASH״̬����
 *  \param status 0ʧ�ܣ�1�ɹ�
 */
void NotifyWriteFlash(uint8 status)
{
	//TODO: ����û�����
}

//no more

