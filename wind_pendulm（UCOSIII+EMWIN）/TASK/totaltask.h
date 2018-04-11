#ifndef __TOTAL_H
#define __TOTAL_H
/******************头文件包含*************/
#include "includes.h"
#include "malloc.h"
/*****************各任务头文件************/
#include "lcdshow.h"
#include "ledtask.h"
#include "angletask.h"
#include "updatefont.h"
#include "textdisplay.h"
/****************曾庆宏************************/




/******************任务块定义*************/

//任务序号:1
//任务功能介绍:LED定时闪烁，显示系统未死机
//任务优先级:60
//任务发送消息:无
//任务接受消息：无
//任务类型(时间阻塞型/消息阻塞型):时间阻塞

//任务优先级
#define LED_TASK_PRIO		61
//任务堆栈大小	
#define LED_STK_SIZE 		128
//任务控制块
extern OS_TCB LEDTastTCB;
//任务堆栈	
extern CPU_STK LED_TASK_STK[LED_STK_SIZE];

//任务序号:2
//任务功能介绍:LCD显示模块
//任务优先级:59
//任务发送消息:无
//任务接受消息：接受LCD显示消息
//任务类型(时间阻塞型/消息阻塞型):消息阻塞（任务自带消息队列）

//任务优先级
#define LCD_TASK_PRIO		59
//任务堆栈大小	
#define LCD_STK_SIZE 		256
//任务控制块
extern OS_TCB LCDTastTCB;
//任务堆栈	
extern CPU_STK LCD_TASK_STK[LCD_STK_SIZE];






//任务序号:4
//任务功能介绍:欧拉角计算
//任务优先级:20
//任务发送消息:无
//任务接受消息：接受LCD显示消息
//任务类型(时间阻塞型/消息阻塞型):消息阻塞（任务自带消息队列）

//任务优先级
#define ANGLE_TASK_PRIO		20
//任务堆栈大小	
#define ANGLE_STK_SIZE 		2048
//任务控制块
extern OS_TCB ANGLETastTCB;
//任务堆栈	
extern CPU_STK ANGLE_TASK_STK[ANGLE_STK_SIZE];



//任务序号:5
//任务功能介绍:欧拉角计算
//任务优先级:20
//任务发送消息:无
//任务接受消息：接受LCD显示消息
//任务类型(时间阻塞型/消息阻塞型):消息阻塞（任务自带消息队列）

//任务优先级
#define MPU6050_TASK_PRIO		30
//任务堆栈大小	
#define MPU6050_STK_SIZE 		128
//任务控制块
extern OS_TCB MPU6050TastTCB;
//任务堆栈	
extern CPU_STK MPU6050_TASK_STK[MPU6050_STK_SIZE];


//任务序号:6
//任务功能介绍:EMWIN界面任务
//任务优先级:10
//任务发送消息:无
//任务接受消息：接受LCD显示消息
//任务类型(时间阻塞型/消息阻塞型):消息阻塞（任务自带消息队列）

//任务优先级
#define EMWIN_TASK_PRIO		8
//任务堆栈大小	
#define EMWIN_STK_SIZE 		2048
//任务控制块
extern OS_TCB EMWINTastTCB;
//任务堆栈	
extern CPU_STK EMWIN_TASK_STK[EMWIN_STK_SIZE];


//任务序号:7
//任务功能介绍:触摸屏任务
//任务优先级:12
//任务发送消息:无
//任务接受消息：接受LCD显示消息
//任务类型(时间阻塞型/消息阻塞型):消息阻塞（任务自带消息队列）

//任务优先级
#define TOUCH_TASK_PRIO		10
//任务堆栈大小	
#define TOUCH_STK_SIZE 		128
//任务控制块
extern OS_TCB TOUCHTastTCB;
//任务堆栈	
extern CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];



//字库更新任务
//设置任务优先级
#define FONTUPDATA_TASK_PRIO		14
//任务堆栈大小
#define FONTUPDATA_STK_SIZE			512
//任务控制块
extern OS_TCB FontupdataTaskTCB;
//任务堆栈
extern CPU_STK FONTUPDATA_TASK_STK[FONTUPDATA_STK_SIZE];




#endif

