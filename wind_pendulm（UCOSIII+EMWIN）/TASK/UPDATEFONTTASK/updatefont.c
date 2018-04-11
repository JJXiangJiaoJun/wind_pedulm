#include "totaltask.h"
#include "updatefont.h"
#include "Hzfontupdata.h"
#include "led.h"


/****************������ƿ��������ջ����**************/
//�������:3
 OS_TCB FontupdataTaskTCB;
//�����ջ	
 CPU_STK FONTUPDATA_TASK_STK[FONTUPDATA_STK_SIZE];
/*******************�ֲ���������***********************/

/********************�ڲ�����**************************/

/********************���⺯��**************************/


/********************��������**************************/
char fontupdata_task_init(void* p_arg)
{
	OS_ERR err;	
	OSTaskCreate((OS_TCB 	* )&FontupdataTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"updatefont task", 		//��������
                 (OS_TASK_PTR )fontupdata_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )FONTUPDATA_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&FONTUPDATA_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)FONTUPDATA_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)FONTUPDATA_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )10,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	if(err != OS_ERR_NONE)
		return 0;//ʧ�ܷ���0
	return 1;//�ɹ�����1
}


void fontupdata_task(void *pdata)
{
	OS_ERR err;

  HzFontupdataCreate();   //�����ֿ�
//	while(1)
//	{
//	  LED0_Toggle;
		OSTimeDlyHMSM(0,0,5,0,OS_OPT_TIME_PERIODIC,&err);//��ʱ10ms
	//}
}

char updatefont_task_deinit(void* p_arg)
{
	OS_ERR err;

	OSTaskDel((OS_TCB*)&FontupdataTaskTCB,&err);
	if(err != OS_ERR_NONE)
		return 0;//ʧ�ܷ���0
	return 1;//�ɹ�����1
}