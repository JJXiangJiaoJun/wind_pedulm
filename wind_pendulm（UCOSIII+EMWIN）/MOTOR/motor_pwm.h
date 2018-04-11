#ifndef __MOTOR_PWM_H
#define __MOTOR_PWM_H

/*-----------------------------------------
				 头  文  件  包  含
------------------------------------------*/ 
#include "sys.h"
#include "delay.h"


/*-----------------------------------------
				 宏   定   义
------------------------------------------*/ 


/*-----------------------------------------
				 变  量  声  明   
------------------------------------------*/ 


/*-----------------------------------------
				 函  数  调  用
------------------------------------------*/ 


/*----------------外部调用---------------*/ 
void SetMotorPWM(int32_t SetM1PWM,int32_t SetM2PWM);

/*----------------内部调用---------------*/
static void PWM_Motor1_Action(u16 val);
static void PWM_Motor2_Action(u16 val);
static void PWM_Motor3_Action(u16 val);
static void PWM_Motor4_Action(u16 val);




#endif