#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H

/*-----------------------------------------
				 ͷ  ��  ��  ��  ��
------------------------------------------*/ 
#include "sys.h"
#include "delay.h"
#include "includes.h"
#include "GUI.h"



/*-----------------------------------------
				 ��   ��   ��
------------------------------------------*/ 


/*-----------------------------------------
				 ��  ��  ��  ��   
------------------------------------------*/ 
extern GUI_BITMAP bmmytest;

/*-----------------------------------------
				 ��  ��  ��  ��
------------------------------------------*/ 
char enwin_task_init(void* p_arg);
char touch_task_init(void* p_arg);



void emwin_task(void* p_arg);
void touch_task(void* p_arg);


#endif
