#include "textdisplay.h"
#include "GUI.h"
#include "delay.h"
#include "WM.h"
#include "DIALOG.h"
#include "myframe.h"
#include "totaltask.h"
#include "xbffontcreate.h"


/*----------------变量定义------------------*/ 
OS_TCB EMWINTastTCB;
CPU_STK EMWIN_TASK_STK[EMWIN_STK_SIZE];

OS_TCB TOUCHTastTCB;
CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];

/*-----------------------------------------
				任务控制块及任务定义
------------------------------------------*/ 
char enwin_task_init(void* p_arg)
{
	OS_ERR err;
	OSTaskCreate(  (OS_TCB 	* )&EMWINTastTCB,					//任务控制块
								 (CPU_CHAR	* )"emwin task", 				//任务名字
                 (OS_TASK_PTR )emwin_task, 					//任务函数
                 (void		* )0,											//传递给任务函数的参数
                 (OS_PRIO	  )EMWIN_TASK_PRIO,     	//任务优先级
                 (CPU_STK   * )&EMWIN_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)EMWIN_STK_SIZE/10,		//任务堆栈深度限位
                 (CPU_STK_SIZE)EMWIN_STK_SIZE,			//任务堆栈大小
                 (OS_MSG_QTY  )0,										//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,											//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,											//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                 (OS_ERR 	* )&err);									//存放该函数错误时的返回值
	if(err != OS_ERR_NONE)
		return 0;																				//失败返回0
	return 1;																					//成功返回1
}



char touch_task_init(void* p_arg)
{
	OS_ERR err;
	OSTaskCreate(  (OS_TCB 	* )&TOUCHTastTCB,					//任务控制块
								 (CPU_CHAR	* )"touch task", 				//任务名字
                 (OS_TASK_PTR )touch_task, 					//任务函数
                 (void		* )0,											//传递给任务函数的参数
                 (OS_PRIO	  )TOUCH_TASK_PRIO,     	//任务优先级
                 (CPU_STK   * )&TOUCH_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)TOUCH_STK_SIZE/10,		//任务堆栈深度限位
                 (CPU_STK_SIZE)TOUCH_STK_SIZE,			//任务堆栈大小
                 (OS_MSG_QTY  )0,										//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,											//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,											//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                 (OS_ERR 	* )&err);									//存放该函数错误时的返回值
	if(err != OS_ERR_NONE)
		return 0;																				//失败返回0
	return 1;																					//成功返回1
}



/*----------------内部函数调用------------------*/ 


/*----------------任务函数------------------*/ 

void emwin_task(void* p_arg)
{
    
	OS_ERR err;
	WM_CALLBACK  *_cbOldBk;
	WM_HWIN myhWin;
	p_arg=p_arg;
	
			//更换皮肤
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX); 
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX);
	GUI_CURSOR_Show(); //显示鼠标
	
	
	Create_XBF12("0:/SYSTEM/EMWINFONT/XBF12.xbf");
	Create_XBF16("0:/SYSTEM/EMWINFONT/XBF16.xbf");
	Create_XBF24("0:/SYSTEM/EMWINFONT/XBF24.xbf");
	Create_XBF36("0:/SYSTEM/EMWINFONT/XBF36.xbf");
	GUI_UC_SetEncodeUTF8();
	
	
	myhWin=CreateFramewin();

	

	
	while(1)
	{

		GUI_Delay(500);
    
	
	}
	
}


void touch_task(void*  p_arg)
{
	OS_ERR err;
	p_arg=p_arg;
	while(1)
	{
		GUI_TOUCH_Exec();	
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//延时5ms
	}

}