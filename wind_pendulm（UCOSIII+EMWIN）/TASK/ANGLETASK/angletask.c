#include "totaltask.h"
#include "angletask.h"
#include "motor_control.h"
#include "inv_mpu.h"
#include "led.h"

/*-----------------------------------------
			ȫ  ��  ��  ��
------------------------------------------*/ 

u8 Mode=1;           //ģʽ����



/*-----------------------------------------
				������ƿ鼰������
------------------------------------------*/ 
//�������:4
OS_TCB ANGLETastTCB;
CPU_STK ANGLE_TASK_STK[ANGLE_STK_SIZE];

char angle_task_init(void* p_arg)
{
	OS_ERR err;
	OSTaskCreate(  (OS_TCB 	* )&ANGLETastTCB,					//������ƿ�
								 (CPU_CHAR	* )"angle task", 				//��������
                 (OS_TASK_PTR )angle_task, 					//������
                 (void		* )0,											//���ݸ��������Ĳ���
                 (OS_PRIO	  )ANGLE_TASK_PRIO,     	//�������ȼ�
                 (CPU_STK   * )&ANGLE_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)ANGLE_STK_SIZE/10,		//�����ջ�����λ
                 (CPU_STK_SIZE)ANGLE_STK_SIZE,			//�����ջ��С
                 (OS_MSG_QTY  )0,										//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,											//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,											//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
                 (OS_ERR 	* )&err);									//��Ÿú�������ʱ�ķ���ֵ
	if(err != OS_ERR_NONE)
		return 0;																				//ʧ�ܷ���0
	return 1;																					//�ɹ�����1
}

/*-----------------------------------------
				 ��  ��  ��  ��
------------------------------------------*/ 

void angle_task(void *p_arg)
{
	OS_ERR err;
	
	u8 i=0;

	
	
	p_arg=p_arg;
	
	while(1)
	{
	   //�ȴ������ź��������5ms��ʱ����
		 OSTaskSemPend ( 	0,
											OS_OPT_PEND_BLOCKING,
											0,
											&err);
		/*-----------------------------------------
							��MPU6050�ж�ȡ��ŷ����
		------------------------------------------*/ 

		mpu_dmp_get_data(&EulerAngle.PITCH,&EulerAngle.ROLL,&EulerAngle.YAW);
		
			//�������ֱ��Ӧ��ͬ�Ľ� 
			/*-----------------------------------------
							M1------------>PITCH
							M2------------>ROLL           
			------------------------------------------*/ 
			
		M1.CurPos = EulerAngle.PITCH;
		M2.CurPos =	EulerAngle.ROLL ;
			/*-----------------------------------------
									ѡ��ͬ��ģʽ
			------------------------------------------*/ 
			
			switch(Mode)	//������Ŀѡ����
			{	
				case 1: Mode_1(); break;
				case 2: Mode_2(); break;
     		case 3: Mode_3(); break;
				case 4: Mode_4(); break;
				case 5: Mode_5(); break;
				case 6: Mode_6(); break;
				default:break;
			}

	
	
	}
	
}


char angle_task_deinit(void* p_arg)
{
	OS_ERR err;
	OSTaskDel((OS_TCB*)&ANGLETastTCB,&err);
	if(err != OS_ERR_NONE)
		return 0;//ʧ�ܷ���0
	return 1;//�ɹ�����1
}

/*-----------------------------------------
				��   ��   ��  ��
------------------------------------------*/ 

