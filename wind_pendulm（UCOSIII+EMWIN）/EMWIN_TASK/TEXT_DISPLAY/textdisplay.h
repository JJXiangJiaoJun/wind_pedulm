#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H

/*-----------------------------------------
				 头  文  件  包  含
------------------------------------------*/ 
#include "sys.h"
#include "delay.h"
#include "includes.h"
#include "GUI.h"



/*-----------------------------------------
				 宏   定   义
------------------------------------------*/ 


/*-----------------------------------------
				 变  量  声  明   
------------------------------------------*/ 
extern GUI_BITMAP bmmytest;

/*-----------------------------------------
				 函  数  调  用
------------------------------------------*/ 
char enwin_task_init(void* p_arg);
char touch_task_init(void* p_arg);



void emwin_task(void* p_arg);
void touch_task(void* p_arg);


#endif
