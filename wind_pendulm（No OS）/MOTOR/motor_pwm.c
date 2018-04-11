#include "motor_pwm.h"


void SetMotorPWM(int32_t SetM1PWM,int32_t SetM2PWM)
{
    if(SetM1PWM>=0)                    //���Ƕȴ���0
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
 ��������:���1�������˶�
 ��������:CCR1_VALռ�ձȼ���ֵ
 ����˵��:CCR1_VALԽ��ת��Խ�� 				
------------------------------------------*/

static void PWM_Motor1_Action(u16 val)
{
		TIM3->CCR1=val;               //����ռ�ձȣ�valԽ��ռ�ձ�Խ��     
}

/*------------------------------------------
 ��������:���2�������˶�
 ��������:CCR2_VALռ�ձȼ���ֵ
 ����˵��:CCR2_VALԽ��ת��Խ�� 				
------------------------------------------*/
static void PWM_Motor2_Action(u16 val)
{

		TIM3->CCR2=val;         
}
/*------------------------------------------
 ��������:���3�������˶�
 ��������:CCR3_VALռ�ձȼ���ֵ
 ����˵��:CCR3_VALԽ��ת��Խ�� 				
------------------------------------------*/

static void PWM_Motor3_Action(u16 val)
{
		TIM3->CCR3=val;     
}
/*------------------------------------------
 ��������:���4�������˶�
 ��������:CCR4_VALռ�ձȼ���ֵ
 ����˵��:CCR4_VALԽ��ת��Խ�� 				
------------------------------------------*/
static void PWM_Motor4_Action(u16 val)
{
    TIM3->CCR4=val;     
}