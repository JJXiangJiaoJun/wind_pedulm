#ifndef __TOTAL_H
#define __TOTAL_H
/******************ͷ�ļ�����*************/
#include "includes.h"
#include "malloc.h"
/*****************������ͷ�ļ�************/
#include "lcdshow.h"
#include "ledtask.h"
#include "angletask.h"
#include "updatefont.h"
#include "textdisplay.h"
/****************�����************************/




/******************����鶨��*************/

//�������:1
//�����ܽ���:LED��ʱ��˸����ʾϵͳδ����
//�������ȼ�:60
//��������Ϣ:��
//���������Ϣ����
//��������(ʱ��������/��Ϣ������):ʱ������

//�������ȼ�
#define LED_TASK_PRIO		61
//�����ջ��С	
#define LED_STK_SIZE 		128
//������ƿ�
extern OS_TCB LEDTastTCB;
//�����ջ	
extern CPU_STK LED_TASK_STK[LED_STK_SIZE];

//�������:2
//�����ܽ���:LCD��ʾģ��
//�������ȼ�:59
//��������Ϣ:��
//���������Ϣ������LCD��ʾ��Ϣ
//��������(ʱ��������/��Ϣ������):��Ϣ�����������Դ���Ϣ���У�

//�������ȼ�
#define LCD_TASK_PRIO		59
//�����ջ��С	
#define LCD_STK_SIZE 		256
//������ƿ�
extern OS_TCB LCDTastTCB;
//�����ջ	
extern CPU_STK LCD_TASK_STK[LCD_STK_SIZE];






//�������:4
//�����ܽ���:ŷ���Ǽ���
//�������ȼ�:20
//��������Ϣ:��
//���������Ϣ������LCD��ʾ��Ϣ
//��������(ʱ��������/��Ϣ������):��Ϣ�����������Դ���Ϣ���У�

//�������ȼ�
#define ANGLE_TASK_PRIO		20
//�����ջ��С	
#define ANGLE_STK_SIZE 		2048
//������ƿ�
extern OS_TCB ANGLETastTCB;
//�����ջ	
extern CPU_STK ANGLE_TASK_STK[ANGLE_STK_SIZE];



//�������:5
//�����ܽ���:ŷ���Ǽ���
//�������ȼ�:20
//��������Ϣ:��
//���������Ϣ������LCD��ʾ��Ϣ
//��������(ʱ��������/��Ϣ������):��Ϣ�����������Դ���Ϣ���У�

//�������ȼ�
#define MPU6050_TASK_PRIO		30
//�����ջ��С	
#define MPU6050_STK_SIZE 		128
//������ƿ�
extern OS_TCB MPU6050TastTCB;
//�����ջ	
extern CPU_STK MPU6050_TASK_STK[MPU6050_STK_SIZE];


//�������:6
//�����ܽ���:EMWIN��������
//�������ȼ�:10
//��������Ϣ:��
//���������Ϣ������LCD��ʾ��Ϣ
//��������(ʱ��������/��Ϣ������):��Ϣ�����������Դ���Ϣ���У�

//�������ȼ�
#define EMWIN_TASK_PRIO		8
//�����ջ��С	
#define EMWIN_STK_SIZE 		2048
//������ƿ�
extern OS_TCB EMWINTastTCB;
//�����ջ	
extern CPU_STK EMWIN_TASK_STK[EMWIN_STK_SIZE];


//�������:7
//�����ܽ���:����������
//�������ȼ�:12
//��������Ϣ:��
//���������Ϣ������LCD��ʾ��Ϣ
//��������(ʱ��������/��Ϣ������):��Ϣ�����������Դ���Ϣ���У�

//�������ȼ�
#define TOUCH_TASK_PRIO		10
//�����ջ��С	
#define TOUCH_STK_SIZE 		128
//������ƿ�
extern OS_TCB TOUCHTastTCB;
//�����ջ	
extern CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];



//�ֿ��������
//�����������ȼ�
#define FONTUPDATA_TASK_PRIO		14
//�����ջ��С
#define FONTUPDATA_STK_SIZE			512
//������ƿ�
extern OS_TCB FontupdataTaskTCB;
//�����ջ
extern CPU_STK FONTUPDATA_TASK_STK[FONTUPDATA_STK_SIZE];




#endif

