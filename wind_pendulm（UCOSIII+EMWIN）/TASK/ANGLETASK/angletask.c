#include "totaltask.h"
#include "angletask.h"
#include "motor_control.h"
#include "inv_mpu.h"
#include "led.h"

/*-----------------------------------------
			全  局  变  量
------------------------------------------*/ 

u8 Mode=1;           //模式控制



/*-----------------------------------------
				任务控制块及任务定义
------------------------------------------*/ 
//任务序号:4
OS_TCB ANGLETastTCB;
CPU_STK ANGLE_TASK_STK[ANGLE_STK_SIZE];

char angle_task_init(void* p_arg)
{
	OS_ERR err;
	OSTaskCreate(  (OS_TCB 	* )&ANGLETastTCB,					//任务控制块
								 (CPU_CHAR	* )"angle task", 				//任务名字
                 (OS_TASK_PTR )angle_task, 					//任务函数
                 (void		* )0,											//传递给任务函数的参数
                 (OS_PRIO	  )ANGLE_TASK_PRIO,     	//任务优先级
                 (CPU_STK   * )&ANGLE_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)ANGLE_STK_SIZE/10,		//任务堆栈深度限位
                 (CPU_STK_SIZE)ANGLE_STK_SIZE,			//任务堆栈大小
                 (OS_MSG_QTY  )0,										//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,											//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,											//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                 (OS_ERR 	* )&err);									//存放该函数错误时的返回值
	if(err != OS_ERR_NONE)
		return 0;																				//失败返回0
	return 1;																					//成功返回1
}

/*-----------------------------------------
				 对  内  函  数
------------------------------------------*/ 

void angle_task(void *p_arg)
{
	OS_ERR err;
	
	u8 i=0;

	
	
	p_arg=p_arg;
	
	while(1)
	{
	   //等待接收信号量，完成5ms定时采样
		 OSTaskSemPend ( 	0,
											OS_OPT_PEND_BLOCKING,
											0,
											&err);
		/*-----------------------------------------
							从MPU6050中读取处欧拉角
		------------------------------------------*/ 

		mpu_dmp_get_data(&EulerAngle.PITCH,&EulerAngle.ROLL,&EulerAngle.YAW);
		
			//两组电机分别对应不同的角 
			/*-----------------------------------------
							M1------------>PITCH
							M2------------>ROLL           
			------------------------------------------*/ 
			
		M1.CurPos = EulerAngle.PITCH;
		M2.CurPos =	EulerAngle.ROLL ;
			/*-----------------------------------------
									选择不同的模式
			------------------------------------------*/ 
			
			switch(Mode)	//根据题目选择函数
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
		return 0;//失败返回0
	return 1;//成功返回1
}

/*-----------------------------------------
				对   外   函  数
------------------------------------------*/ 

