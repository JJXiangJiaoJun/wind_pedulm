#ifndef __MOTOR_PID_H
#define __MOTOR_PID_H

/*-----------------------------------------
				 头  文  件  包  含
------------------------------------------*/ 
#include "sys.h"
#include "delay.h"


/*-----------------------------------------
				 宏   定   义
-----------------------------------------*/ 
#define IntergralMax   3500    //积分上限
#define IntergralMin  -3500     //积分下限

/*-----------------------------------------
				 变  量  声  明   
------------------------------------------*/ 
typedef struct
{
	
	float  SetPoint;              //设定值
	double SumError;              //累计误差
   
  float   Kp;                   //比例系数Kp
  float   Ki;                   //积分系数Ki
  float   Kd;	                  //微分系数Kd
	
	
	float  LastError;             //E[-1]
	float  PreError;              //E[-2]
	
}PIDTypeDef;


typedef struct
{
   
   float kp_temp;
	 float ki_temp;
	 float kd_temp;
 

}PitchSetPIDByUpTypeDef,RollSetPIDByUpTypeDef;


extern PitchSetPIDByUpTypeDef PitchSetPIDtemp;
extern RollSetPIDByUpTypeDef 	 RollSetPIDtemp;

/*-----------------------------------------
				 函  数  调  用
------------------------------------------*/ 

int32_t   PID_M1_PosLocCalc(float NextPoint);         


void 	PID_M1_Init(void);
void  PID_M1_SetPoint(float setpoint);
void 	PID_M1_SetKp(float kp);
void  PID_M1_SetKi(float ki);
void 	PID_M1_SetKd(float kd);


int32_t   PID_M2_PosLocCalc(float NextPoint);         

void 	PID_M2_Init(void);
void  PID_M2_SetPoint(float setpoint);
void 	PID_M2_SetKp(float kp);
void  PID_M2_SetKi(float ki);
void 	PID_M2_SetKd(float kd);

void PitchSetPID_Init(void);
void RollSetPID_Init(void);

#endif


