#include "motor_pwm.h"


void SetMotorPWM(int32_t SetM1PWM,int32_t SetM2PWM)
{
    if(SetM1PWM>=0)                    //若角度大于0
    {
		  PWM_Motor1_Action(SetM1PWM) ;
			PWM_Motor2_Action(0)        ;
		}			
    else if(SetM1PWM<0)
    {
			PWM_Motor1_Action(0) 				;
			PWM_Motor2_Action(SetM1PWM) ;
		
		}
		if(SetM2PWM>=0)
		{
			PWM_Motor3_Action(SetM2PWM) ;
			PWM_Motor4_Action(0) 				;
		
		}
		else if(SetM2PWM<0)
		{
			PWM_Motor3_Action(0) 				;
			PWM_Motor4_Action(SetM2PWM) ;
		}
}

/*------------------------------------------
 函数功能:电机1正方向运动
 函数参数:CCR1_VAL占空比计数值
 函数说明:CCR1_VAL越大转速越快 				
------------------------------------------*/

static void PWM_Motor1_Action(u16 val)
{
		TIM3->CCR1=val;               //设置占空比，val越大占空比越大     
}

/*------------------------------------------
 函数功能:电机2正方向运动
 函数参数:CCR2_VAL占空比计数值
 函数说明:CCR2_VAL越大转速越快 				
------------------------------------------*/
static void PWM_Motor2_Action(u16 val)
{

		TIM3->CCR2=val;         
}
/*------------------------------------------
 函数功能:电机3正方向运动
 函数参数:CCR3_VAL占空比计数值
 函数说明:CCR3_VAL越大转速越快 				
------------------------------------------*/

static void PWM_Motor3_Action(u16 val)
{
		TIM3->CCR3=val;     
}
/*------------------------------------------
 函数功能:电机4正方向运动
 函数参数:CCR4_VAL占空比计数值
 函数说明:CCR4_VAL越大转速越快 				
------------------------------------------*/
static void PWM_Motor4_Action(u16 val)
{
    TIM3->CCR4=val;     
}