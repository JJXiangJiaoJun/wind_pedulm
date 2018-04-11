#include "totaltask.h"
#include "updatefont.h"
#include "Hzfontupdata.h"
#include "led.h"


/****************任务控制块与任务堆栈定义**************/
//任务序号:3
 OS_TCB FontupdataTaskTCB;
//任务堆栈	
 CPU_STK FONTUPDATA_TASK_STK[FONTUPDATA_STK_SIZE];
/*******************局部变量定义***********************/

/********************内部函数**************************/

/********************对外函数**************************/


/********************函数部分**************************/
char fontupdata_task_init(void* p_arg)
{
	OS_ERR err;	
	OSTaskCreate((OS_TCB 	* )&FontupdataTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"updatefont task", 		//任务名字
                 (OS_TASK_PTR )fontupdata_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )FONTUPDATA_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&FONTUPDATA_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)FONTUPDATA_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)FONTUPDATA_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )10,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	if(err != OS_ERR_NONE)
		return 0;//失败返回0
	return 1;//成功返回1
}


void fontupdata_task(void *pdata)
{
	OS_ERR err;

  HzFontupdataCreate();   //升级字库
//	while(1)
//	{
//	  LED0_Toggle;
		OSTimeDlyHMSM(0,0,5,0,OS_OPT_TIME_PERIODIC,&err);//延时10ms
	//}
}

char updatefont_task_deinit(void* p_arg)
{
	OS_ERR err;

	OSTaskDel((OS_TCB*)&FontupdataTaskTCB,&err);
	if(err != OS_ERR_NONE)
		return 0;//失败返回0
	return 1;//成功返回1
}