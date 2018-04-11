#include "test.h"
#include "led.h"
#include "totaltask.h"
#include "inv_mpu.h"

/****************������ƿ��������ջ����**************/
//�������:1
/*----------------MPU6050��������----------------*/

OS_TCB MPU6050TastTCB;
CPU_STK MPU6050_TASK_STK[MPU6050_STK_SIZE];

char mpu_task_init(void* p_arg)
{
	OS_ERR err;
	OSTaskCreate(  (OS_TCB 	* )&MPU6050TastTCB,		//������ƿ�
								 (CPU_CHAR	* )"mpu task", 		//��������
                 (OS_TASK_PTR )mpu_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )MPU6050_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&MPU6050_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)MPU6050_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)MPU6050_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	if(err != OS_ERR_NONE)
		return 0;//ʧ�ܷ���0
	return 1;//�ɹ�����1
}

void mpu_task(void* p_arg)
{
	OS_ERR err;
	float pitch,roll,yaw;
	p_arg  = p_arg;
	while(1)
	{
		LED0_Toggle;
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0)
			printlcd("mpu6050 dmp get data error!");
		else
		//mpu_dmp_get_data(&pitch,&roll,&yaw);
			printlcd("pitch:%.2f  roll:%.2f  yaw:%.2f",pitch,roll,yaw);
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

char mpu_task_deinit(void* p_arg)
{
	OS_ERR err;
	OSTaskDel((OS_TCB*)&MPU6050TastTCB,&err);
	if(err != OS_ERR_NONE)
		return 0;//ʧ�ܷ���0
	return 1;//�ɹ�����1
}