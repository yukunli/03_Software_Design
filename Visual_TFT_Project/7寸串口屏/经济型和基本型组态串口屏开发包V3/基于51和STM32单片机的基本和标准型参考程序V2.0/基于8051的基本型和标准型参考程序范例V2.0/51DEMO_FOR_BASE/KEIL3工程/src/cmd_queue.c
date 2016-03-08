/************************************��Ȩ����********************************************
**                             ���ݴ�ʹ��Ƽ����޹�˾
**                             http://www.gz-dc.com
**-----------------------------------�ļ���Ϣ--------------------------------------------
** �ļ�����:   cmd_queue.c
** �޸�ʱ��:   2011-05-18
** �ļ�˵��:   �û�MCU��������������
** ����֧�֣�  Tel: 020-82186683  Email: hmi@gz-dc.com Web:www.gz-dc.com
**--------------------------------------------------------------------------------------*/


#include "cmd_queue.h"

typedef struct _QUEUE
{
    qsize _head;
    qsize _tail;
    qdata _data[QUEUE_MAX_SIZE];
} QUEUE;//�������ݽ��ն��нṹ��

static QUEUE que = {0,0,0};
static qdata cmd_state = 0;
static qsize cmd_pos = 0;

/********************************
*��    �ƣ� queue_reset
*��    ��    ���ڽ��ն��и�λ
*��ڲ����� ��
*���ڲ����� ��
*********************************/
void queue_reset()
{
    que._head = que._tail = 0;
    cmd_pos = cmd_state = 0;
}

/**********************************************
*��    �ƣ� queue_push
*��    ��   ����һ�����ݵ����ڽ��ն��У�FIFO����
*��ڲ����� ��
*���ڲ����� ��
**********************************************/
void queue_push(qdata _data)
{
    qsize pos = (que._head+1)%QUEUE_MAX_SIZE;
    if(pos!=que._tail)//����״̬
    {
        que._data[que._head] = _data;
        que._head = pos;
    }
}
/**********************************************
*��    �ƣ� queue_pop
*��    ��   �Ӵ��ڽ��ն���(FIFO)��ȡ��һ���ֽ�����
*��ڲ����� ��
*���ڲ����� ��
**********************************************/
static void queue_pop(qdata* _data)
{
    if(que._tail!=que._head)//�ǿ�״̬
    {
        *_data = que._data[que._tail];
        que._tail = (que._tail+1)%QUEUE_MAX_SIZE;
    }
}
/**********************************************
*��    �ƣ� queue_size
*��    ��   ��ȡ���ڽ��ն���(FIFO)�ĳ���
*��ڲ����� ��
*���ڲ����� ��
**********************************************/
static qsize queue_size()
{
    return ((que._head+QUEUE_MAX_SIZE-que._tail)%QUEUE_MAX_SIZE);
}

/******************************************************************
*��    �ƣ� queue_find_cmd
*��    ��   ��ȡ���ڽ��ն���(FIFO)��һ��������֡
            һ��������֡����EE��ͷ��FF FC FF FF ��β��һ������֡
*��ڲ����� ��
*���ڲ����� ��
********************************************************************/
qsize queue_find_cmd(qdata *buffer,qsize buf_len)
{
    qsize cmd_size = 0;
    qdata _data = 0;
    while(queue_size()>0)
    {
        //ȡһ������
        queue_pop(&_data);

        if(cmd_pos==0&&_data!=0xEE)//֡ͷ��������
            continue;

        if(cmd_pos<buf_len)//��ֹ���������
            buffer[cmd_pos++] = _data;

        //�ж�֡β
        if(_data==0xFF)
        {
            switch (cmd_state)
            {
            case 2:
                cmd_state = 3;
                break; //FF FC FF ?? (���һ���ֽڲ���)
            case 3:
                cmd_state = 4;
                break; //FF FC FF FF ��ȷ��֡β
            default:
                cmd_state = 1;
                break; //FF ?? ?? ??(��������ֽڲ���)
            }
        }
        else if(_data==0xFC)
        {
            switch (cmd_state)
            {
            case 1:
                cmd_state = 2;
                break; //FF FC ?? ??(�������ֽڲ���)
            case 3:
                cmd_state = 2;
                break; //FF FC FF FC ��ȷ��֡β
            default:
                cmd_state = 0;
                break; //?? ?? ?? ??(ȫ���ֽڲ���)
            }
        }
        else
            cmd_state = 0;

        //�õ�������֡β
        if(cmd_state==4)
        {
            cmd_size = cmd_pos;
            cmd_state = 0;
            cmd_pos = 0;
            return cmd_size;
        }
    }

    return 0;//û���γ�������һ֡
}
