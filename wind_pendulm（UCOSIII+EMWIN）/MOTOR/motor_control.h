#ifndef __MOTOR_CONTROL_H
#define __MOTOR_CONTROL_H

/*-----------------------------------------
				 头  文  件  包  含
------------------------------------------*/ 
#include "sys.h"
#include "delay.h"


/*-----------------------------------------
				 宏   定   义
------------------------------------------*/ 
#define  Height   80.0f          //万向节距离地面的高度
#define  PERIOD   1626.3f        //单摆周期
#define  PI       3.141592f      //π
#define  RADIUS   15.0f          //半径
#define  PWM_MAX  5400           //PWM输出最大值
#define  ANGLE    240.0f/57.2958f //初始角度值
/*-----------------------------------------
				 变  量  声  明   
------------------------------------------*/ 
typedef struct{
  
 volatile  float CurPos ;      //当前位置
 volatile  float PrePos ;      //上一次位置
	 
	float Pitch  ;               //Pitch角
	float Roll   ;               //Roll角 
	
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
				 函  数  调  用
------------------------------------------*/ 

void Mode_1(void);
void Mode_2(void);
void Mode_3(void);
void Mode_4(void);
void Mode_5(void);
void Mode_6(void);


#endif

