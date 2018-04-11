#include "test.h"
#include "led.h"
#include "totaltask.h"
#include "inv_mpu.h"

/****************任务控制块与任务堆栈定义**************/
//任务序号:1
/*----------------MPU6050测试任务----------------*/

OS_TCB MPU6050TastTCB;
CPU_STK MPU6050_TASK_STK[MPU6050_STK_SIZE];

char mpu_task_init(void* p_arg)
{
	OS_ERR err;
	OSTaskCreate(  (OS_TCB 	* )&MPU6050TastTCB,		//任务控制块
								 (CPU_CHAR	* )"mpu task", 		//任务名字
                 (OS_TASK_PTR )mpu_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )MPU6050_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&MPU6050_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)MPU6050_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)MPU6050_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	if(err != OS_ERR_NONE)
		return 0;//失败返回0
	return 1;//成功返回1
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
		return 0;//失败返回0
	return 1;//成功返回1
}