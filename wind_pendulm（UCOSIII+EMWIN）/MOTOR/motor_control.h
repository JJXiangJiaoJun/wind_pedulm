#ifndef __MOTOR_CONTROL_H
#define __MOTOR_CONTROL_H

/*-----------------------------------------
				 ͷ  ��  ��  ��  ��
------------------------------------------*/ 
#include "sys.h"
#include "delay.h"


/*-----------------------------------------
				 ��   ��   ��
------------------------------------------*/ 
#define  Height   80.0f          //����ھ������ĸ߶�
#define  PERIOD   1626.3f        //��������
#define  PI       3.141592f      //��
#define  RADIUS   15.0f          //�뾶
#define  PWM_MAX  5400           //PWM������ֵ
#define  ANGLE    240.0f/57.2958f //��ʼ�Ƕ�ֵ
/*-----------------------------------------
				 ��  ��  ��  ��   
------------------------------------------*/ 
typedef struct{
  
 volatile  float CurPos ;      //��ǰλ��
 volatile  float PrePos ;      //��һ��λ��
	 
	float Pitch  ;               //Pitch��
	float Roll   ;               //Roll�� 
	
	float offset ;
	
	int32_t   PWM;


}M1_MoTionTypeDef,M2_MoTionTypeDef;


typedef struct{

		float PITCH;
		float ROLL;
		float YAW;

}EulerAngleTypeDef;



extern M1_MoTionTypeDef M1;
extern M2_MoTionTypeDef M2;
extern EulerAngleTypeDef EulerAngle;
extern float Angle;
extern float Radius;
extern u8     RoundDir;


/*-----------------------------------------
				 ��  ��  ��  ��
------------------------------------------*/ 

void Mode_1(void);
void Mode_2(void);
void Mode_3(void);
void Mode_4(void);
void Mode_5(void);
void Mode_6(void);


#endif

