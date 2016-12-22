/*! 
 *  \file hmi_driver.h
 *  \brief �����������ļ�
 *  \version 1.0
 *  \date 2012-2015
 *  \copyright ���ݴ�ʹ��Ƽ����޹�˾
 */

#ifndef _HMI_DRIVER_
#define _HMI_DRIVER_

#define CRC16_ENABLE 0         /*!< �����ҪCRC16У�鹦�ܣ��޸Ĵ˺�Ϊ1(��ʱ��Ҫ��VisualTFT��������CRCУ��)*/
#define CMD_MAX_SIZE 18        /*!<����ָ���С��������Ҫ�������������ô�һЩ*/
#define QUEUE_MAX_SIZE 30      /*!< ָ����ջ�������С��������Ҫ�������������ô�һЩ*/

#include "hmi_user_uart.h"

/*! 
 *  \brief  �����豸���ã�����֮����Ҫ�����������޸Ĳ����ʡ���������������������ʽ
 */
void LockDeviceConfig(void);

/*! 
 *  \brief  �����豸����
 */
void UnlockDeviceConfig(void);


/*! 
 *  \brief  ������������
 */
void SetHandShake(void);

/*! 
 *  \brief  ����ǰ��ɫ
 *  \param  color ǰ��ɫ
 */
void SetFcolor(uint16 color);


/*! 
 *  \brief  �������
 */
void GUI_CleanScreen(void);

/*! 
 *  \brief  �������ּ��
 *  \param  x_w ������
  *  \param  y_w ������
 */
void SetTextSpace(uint8 x_w, uint8 y_w);

/*! 
 *  \brief  ����������ʾ����
 *  \param  enable �Ƿ���������
 *  \param  width ���
 *  \param  height �߶�
 */
void SetFont_Region(uint8 enable,uint16 width,uint16 height );


/*! 
 *  \brief      ��ʾȫ��ͼƬ
 *  \param  image_id ͼƬ����
 *  \param  masken �Ƿ�����͸������
 */
void DisFull_Image(uint16 image_id,uint8 masken);

/*! 
 *  \brief      ��ʾGIF����
 *  \param  x λ��X����
 *  \param  y λ��Y����
 *  \param  flashimage_id ͼƬ����
 *  \param  enable �Ƿ���ʾ
 *  \param  playnum ���Ŵ���
 */
void DisFlashImage(uint16 x,uint16 y,uint16 flashimage_id,uint8 enable,uint8 playnum);

/*! 
 *  \brief      ����
 *  \param  x λ��X����
 *  \param  y λ��Y����
 */
void GUI_Dot(uint16 x,uint16 y);

/*! 
 *  \brief      ����
 *  \param  x0 ��ʼλ��X����
 *  \param  y0 ��ʼλ��Y����
 *  \param  x1 ����λ��X����
 *  \param  y1 ����λ��Y����
 */
void GUI_Line(uint16 x0, uint16 y0, uint16 x1, uint16 y1);

/*! 
 *  \brief      ������
 *  \param  mode ģʽ
 *  \param  dot ���ݵ�
 *  \param  dot_cnt ����
 */
void GUI_ConDots(uint8 mode,uint16 *dot,uint16 dot_cnt);

/*! 
 *  \brief      ����
 *  \param  x0 ��ʼλ��X����
 *  \param  y0 ��ʼλ��Y����
 *  \param  x1 ����λ��X����
 *  \param  y1 ����λ��Y����
 */
void SetBackLight(uint8 light_level);

/*! 
 *  \brief   ����������
 *  \time  time ����ʱ��(���뵥λ)
 */
void SetBuzzer(uint8 time);

/*! 
 *  \brief   ����������
 *  \param enable ����ʹ��
 *  \param beep_on ����������
 *  \param work_mode ��������ģʽ��0���¾��ϴ���1�ɿ����ϴ���2�����ϴ�����ֵ��3���º��ɿ����ϴ�����
 *  \param press_calibration �������������20��У׼��������0���ã�1����
 */
void SetTouchPaneOption(uint8 enbale,uint8 beep_on,uint8 work_mode,uint8 press_calibration);

/*! 
 *  \brief   У׼������
 */
void	CalibrateTouchPane(void);

/*! 
 *  \brief  ����������
 */
void TestTouchPane(void);


/*! 
 *  \brief      ���õ�ǰ��ʾͼ��
 *  \param  layer ͼ����
 */
void DisplyLayer(uint8 layer);

/*! 
 *  \brief      ���ͼ�㣬ʹͼ����͸��
 *  \param  layer ͼ����
 */
void ClearLayer(uint8 layer);

/*! 
 *  \brief  д���ݵ��������û��洢��
 *  \param  startAddress ��ʼ��ַ
 *  \param  length �ֽ���
 *  \param  _data ��д�������
 */
void WriteUserFlash(uint32 startAddress,uint16 length,uint8 *_data);

/*! 
 *  \brief  �Ӵ������û��洢����ȡ����
 *  \param  startAddress ��ʼ��ַ
 *  \param  length �ֽ���
 */
void ReadUserFlash(uint32 startAddress,uint16 length);

/*! 
 *  \brief      ����ͼ��
 *  \param  src_layer ԭʼͼ��
 *  \param  dest_layer Ŀ��ͼ��
 */
void CopyLayer(uint8 src_layer,uint8 dest_layer);

/*! 
 *  \brief      ���õ�ǰ����
 *  \param  screen_id ����ID
 */
void SetScreen(uint16 screen_id);

/*! 
 *  \brief      ��ȡ��ǰ����
 */
void GetScreen(void);

/*! 
 *  \brief     ����\���û������
 *  \details ����\����һ��ɶ�ʹ�ã����ڱ�����˸�����ˢ���ٶ�
 *  \details �÷���
 *	\details SetScreenUpdateEnable(0);//��ֹ����
 *	\details һϵ�и��»����ָ��
 *	\details SetScreenUpdateEnable(1);//��������
 *  \param  enable 0���ã�1����
 */
void SetScreenUpdateEnable(uint8 enable);

/*! 
 *  \brief     ���ÿؼ����뽹��
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  focus �Ƿ�������뽹��
 */
void SetControlFocus(uint16 screen_id,uint16 control_id,uint8 focus);

/*! 
 *  \brief     ���ô����ؼ�ʹ��
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  enable �ؼ��Ƿ�ʹ��
 */
void SetControlEnable(uint16 screen_id,uint16 control_id,uint8 enable);

/*! 
 *  \brief     ��ȡ�ؼ�ֵ
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void GetControlValue(uint16 screen_id,uint16 control_id);

/*! 
 *  \brief     ���ð�ť״̬
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  value ��ť״̬
 */
void SetButtonValue(uint16 screen_id,uint16 control_id,uchar value);

/*! 
 *  \brief     �����ı�ֵ
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  str �ı�ֵ
 */
void SetTextValue(uint16 screen_id,uint16 control_id,uchar *str);
 
/*! 
 *  \brief      ��ʼ���Ŷ���
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void AnimationStart(uint16 screen_id,uint16 control_id);

/*! 
 *  \brief      ֹͣ���Ŷ���
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void AnimationStop(uint16 screen_id,uint16 control_id);

/*! 
 *  \brief      ��ͣ���Ŷ���
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void AnimationPause(uint16 screen_id,uint16 control_id);

/*! 
 *  \brief     ������һ֡
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void AnimationPlayPrev(uint16 screen_id,uint16 control_id);

/*! 
 *  \brief     ������һ֡
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void AnimationPlayNext(uint16 screen_id,uint16 control_id);

/*! 
 *  \brief     ���߿ؼ�-���ͨ��
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  channel ͨ����
 *  \param  color ��ɫ
 */
void GraphChannelAdd(uint16 screen_id,uint16 control_id,uint8 channel,uint16 color);

/*! 
 *  \brief     ���߿ؼ�-ɾ��ͨ��
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  channel ͨ����
 */
void GraphChannelDel(uint16 screen_id,uint16 control_id,uint8 channel);

/*! 
 *  \brief     ���߿ؼ�-�������
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  channel ͨ����
 *  \param  pData ��������
 *  \param  nDataLen ���ݸ���
 */
void GraphChannelDataAdd(uint16 screen_id,uint16 control_id,uint8 channel,uint8* pData,uint16 nDataLen);

/*! 
 *  \brief     ���߿ؼ�-�������
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  channel ͨ����
 */
void GraphChannelDataClear(uint16 screen_id,uint16 control_id,uint8 channel);

/*! 
 *  \brief     ���߿ؼ�-������ͼ����
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  x_offset ˮƽƫ��
 *  \param  x_mul ˮƽ����ϵ��
 *  \param  y_offset ��ֱƫ��
 *  \param  y_mul ��ֱ����ϵ��
 */
void GraphSetViewport(uint16 screen_id,uint16 control_id,int16 x_offset,uint16 x_mul,int16 y_offset,uint16 y_mul);

/*! 
 *  \brief     ��ʼ��������
 *  \param  screen_id ����ID
 */
void BatchBegin(uint16 screen_id);

/*! 
 *  \brief     �������½������ؼ�
 *  \param  control_id �ؼ�ID
 *  \param  value ��ֵ
 */
void BatchSetProgressValue(uint16 control_id,uint32 value);

/*! 
 *  \brief     �������»������ؼ�
 *  \param  control_id �ؼ�ID
 *  \param  value ��ֵ
 */
void BatchSetSliderValue(uint16 control_id,uint32 value);

/*! 
 *  \brief     ���������ı��ؼ�
 *  \param  control_id �ؼ�ID
 *  \param  strings �ַ���
 */
void BatchSetText(uint16 control_id,uchar *strings);

/*! 
 *  \brief    ������������
 */
void BatchEnd(void);

/*! 
 *  \brief     ��ʾ\����ϵͳ����
 *  \param  show 0���أ�1��ʾ
 *  \param  x ������ʾλ��X����
 *  \param  y ������ʾλ��Y����
 *  \param  type 0С���̣�1ȫ����
 *  \param  option 0�����ַ���1���룬2ʱ������
 *  \param  max_len ����¼���ַ���������
 */
void ShowKeyboard(uint8 show,uint16 x,uint16 y,uint8 type,uint8 option,uint8 max_len);

#endif
