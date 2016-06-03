#ifndef _CMD_PROCESS_H
#define _CMD_PROCESS_H
#include "hmi_driver.h"

#define NOTIFY_TOUCH_PRESS      0X01   //����������֪ͨ
#define NOTIFY_TOUCH_RELEASE  0X03  //�������ɿ�֪ͨ
#define NOTIFY_WRITE_FLASH_OK  0X0C  //дFLASH�ɹ�
#define NOTIFY_WRITE_FLASH_FAILD  0X0D  //дFLASHʧ��
#define NOTIFY_READ_FLASH_OK  0X0B  //��FLASH�ɹ�
#define NOTIFY_READ_FLASH_FAILD  0X0F  //��FLASHʧ��
#define NOTIFY_MENU                        0X14  //�˵��¼�֪ͨ
#define NOTIFY_TIMER                       0X43  //��ʱ����ʱ֪ͨ
#define NOTIFY_CONTROL                0XB1  //�ؼ�����֪ͨ
#define NOTIFY_SCREEN                   0XB2  //�����л�֪ͨ

#define PTR2U16(PTR) ((((uint8 *)(PTR))[0]<<8)|((uint8 *)(PTR))[1])  //�ӻ�����ȡ16λ����
#define PTR2U32(PTR) ((((uint8 *)(PTR))[0]<<24)|(((uint8 *)(PTR))[1]<<16)|(((uint8 *)(PTR))[2]<<8)|((uint8 *)(PTR))[3])  //�ӻ�����ȡ32λ����
enum CtrlType
{
	kCtrlUnknown=0x0,
	kCtrlButton=0x10,  //��ť
	kCtrlText,  //�ı�
	kCtrlProgress,  //������
	kCtrlSlider,    //������
	kCtrlMeter,  //�Ǳ�
	kCtrlDropList, //�����б�
	kCtrlAnimation, //����
	kCtrlRTC, //ʱ����ʾ
	kCtrlGraph, //����ͼ�ؼ�
	kCtrlTable, //���ؼ�
	kCtrlMenu,//�˵��ؼ�
	kCtrlSelector,//ѡ��ؼ�
	kCtrlQRCode//��ά��
};

typedef struct
{
	float Water_b;  //�ؾ����
	float Water_k;	//б�ʲ���
	float PID_Kp;	//pid��kp����
	float PID_Ki;	//pid��ki����
	float PID_Kd;	//pid��kd����
}Water_Param;
typedef struct
{
	float WaterValue;	//����ˮ��ֵ
	float SoonWaterValue;	//˲ʱˮ��ֵ
	float temperature;	//�¶�
}Water_Value;

typedef struct
{
	uint8    cmd_head;  //֡ͷ
	uint8    cmd_type;  //��������(UPDATE_CONTROL)	
	uint8    ctrl_msg;   //CtrlMsgType-ָʾ��Ϣ������
	uint8    screen_id0;  //������Ϣ�Ļ���ID0
	uint8 	 screen_id1;  //������Ϣ�Ļ���ID1
	uint8    control_id0;  //������Ϣ�Ŀؼ�ID0
	uint8    control_id1;  //������Ϣ�Ŀؼ�ID1
	uint8    control_type; //�ؼ�����
	uint8    param[6];	//�ɱ䳤�Ȳ��������256���ֽ�
	uint8  cmd_tail[4];   //֡β
}CTRL_MSG,*PCTRL_MSG;


void ProcessMessage( PCTRL_MSG msg, uint16 size, Water_Param *InterfaceParam );

void InitUI(Water_Param *InterfaceParam);

void UpdateUI(Water_Value * InterfaceValue);

void NotifyScreen(uint16 screen_id);

void NotifyTouchXY(uint8 press,uint16 x,uint16 y);

void NotifyButton(uint16 screen_id, uint16 control_id, uint8  state);

void NotifyText(uint16 screen_id, uint16 control_id, uint8 *str, Water_Param *InterfaceParam);

void NotifyReadFlash(uint8 status,uint8 *_data,uint16 length);

void NotifyWriteFlash(uint8 status);

#endif
