#include "totaltask.h"
#include "ledtask.h"
#include "led.h"

/****************������ƿ��������ջ����**************/
//�������:1
OS_TCB LEDTastTCB;
CPU_STK LED_TASK_STK[LED_STK_SIZE];

char led_task_init(void* p_arg)
{
	OS_ERR err;
	OSTaskCreate((OS_TCB 	* )&LEDTastTCB,		//������ƿ�
				 (CPU_CHAR	* )"led task", 		//��������
                 (OS_TASK_PTR )led_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )LED_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&LED_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)LED_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)LED_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	if(err != OS_ERR_NONE)
		return 0;//ʧ�ܷ���0
	return 1;//�ɹ�����1
}

void led_task(void* p_arg)
{
	OS_ERR err;
	while(1)
	{
		LED1_Toggle;
		
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

char led_task_deinit(void* p_arg)
{
	OS_ERR err;
	OSTaskDel((OS_TCB*)&LEDTastTCB,&err);
	if(err != OS_ERR_NONE)
		return 0;//ʧ�ܷ���0
	return 1;//�ɹ�����1
}

