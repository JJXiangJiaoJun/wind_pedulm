#include "motor_control.h"
#include "motor_pid.h"
#include "motor_pwm.h"
#include "niming.h"
#include <math.h>

 
M1_MoTionTypeDef M1;
M2_MoTionTypeDef M2;
EulerAngleTypeDef EulerAngle;

u8     report   = 1   ;
u8     RoundDir = 0   ;
float  Radius = RADIUS;
float  Angle  = ANGLE;



/*------------------------------------------
 函数功能:模式1，画直线
 函数说明:		
------------------------------------------*/

void Mode_1(void)
{
  const float Period=PERIOD;               //单摆周期
 	
	static u32 MoveCnt=0;                     //每5ms计算一次
	float Omega ;
  float Set_x = 0;                          //x方向设定值
  float Set_y = 0;                          //y方向设定值	
  float A=0.0f;                             //振幅
  float Nomalization=0;                     //归一化变量
	M2.offset = 0.0f;
	
	MoveCnt+=5;                               //每5ms计算一次
	Nomalization = (float)MoveCnt/Period;     //周期归一化运算
	Omega = Nomalization*2*PI;                //换算成对应角度
	A = atan((Radius/Height))*57.2958f;       //计算振幅
	Set_x = A*sin(Omega);                     //计算当前摆角
	
	//电机1  PID运算
	PID_M1_SetPoint(Set_x);                   //x方向PID跟踪值
	PID_M1_SetKp(1200.0f);
	PID_M1_SetKi(1.35f);
	PID_M1_SetKd(45000.0f);

//	PID_M1_SetKp(0);
//	PID_M1_SetKi(0);
//	PID_M1_SetKd(0);

	
	M1.PWM = PID_M1_PosLocCalc(M1.CurPos);
	
//	//电机2  PID运算
//	PID_M2_SetPoint(0);                       //y方向PID跟踪值
//	PID_M2_SetKp(5.0f);
//	PID_M2_SetKi(0.33f);
//	PID_M2_SetKd(5000.0f);


	
	//电机2  PID运算
	PID_M2_SetPoint(0);                       //y方向PID跟踪值
	PID_M2_SetKp(0.3f);
	PID_M2_SetKi(0.11f);
	PID_M2_SetKd(3000.0f);
	
	
//	
//		//电机2  PID运算
//	PID_M2_SetPoint(Set_y);                   //y方向PID跟踪值
//	PID_M2_SetKp(RollSetPIDtemp.kp_temp);
//	PID_M2_SetKi(RollSetPIDtemp.ki_temp);
//	PID_M2_SetKd(RollSetPIDtemp.kd_temp);


	M2.PWM = PID_M2_PosLocCalc(M2.CurPos);
	
  //电机PWM输出限幅
  if(M1.PWM>PWM_MAX) M1.PWM=PWM_MAX;
	if(M1.PWM<-PWM_MAX) M1.PWM=-PWM_MAX;
	if(M2.PWM>PWM_MAX) M2.PWM=PWM_MAX;
	if(M2.PWM<-PWM_MAX) M2.PWM=-PWM_MAX;
	
	//输出PWM波
 SetMotorPWM(M1.PWM,M2.PWM);
	
	
	if(report)usart1_report_imu((short)Set_x,(short)M2.PWM,(short)0,(short)0,(short)0,(short)0,(int)(M2.CurPos*100),(int)(M1.CurPos*100),(int)(EulerAngle.YAW*10));
  

}



/*------------------------------------------
 函数功能:模式2，画直线,振幅可变
 函数说明:		
------------------------------------------*/
void Mode_2(void)
{

	static float Period=PERIOD;               //单摆周期 
	static u32 MoveCnt=0;                     //每5ms计算一次
	float Omega ;
  float Set_y = 0;                          //设定值	
  float A=0.0f;                             //振幅
  float Nomalization=0;                     //归一化变量
	
	MoveCnt+=5;                               //每5ms计算一次
	Nomalization = (float)MoveCnt/Period;     //周期归一化运算
	Omega = Nomalization*2*PI;                //换算成对应角度
	A = atan((Radius/Height))*57.2958f;       //计算振幅
	Set_y = A*sin(Omega);                     //计算当前摆角
	
	//电机1  PID运算 
	PID_M1_SetPoint(0);                       //x方向PID跟踪值
	PID_M1_SetKp(PitchSetPIDtemp.kp_temp);
	PID_M1_SetKi(PitchSetPIDtemp.ki_temp);
	PID_M1_SetKd(PitchSetPIDtemp.kd_temp);
	
		
	M1.PWM = PID_M1_PosLocCalc(M1.CurPos);
	
	//电机2  PID运算
	PID_M2_SetPoint(Set_y);                   //y方向PID跟踪值
	PID_M2_SetKp(RollSetPIDtemp.kp_temp);
	PID_M2_SetKi(RollSetPIDtemp.ki_temp);
	PID_M2_SetKd(RollSetPIDtemp.kd_temp);
	
	M2.PWM = PID_M2_PosLocCalc(M2.CurPos);
	
  //电机PWM输出限幅
  if(M1.PWM>PWM_MAX) M1.PWM=PWM_MAX;
	if(M1.PWM<-PWM_MAX) M1.PWM=-PWM_MAX;
	if(M2.PWM>PWM_MAX) M2.PWM=PWM_MAX;
	if(M2.PWM<-PWM_MAX) M2.PWM=-PWM_MAX;
	
	//输出PWM波
  SetMotorPWM(M1.PWM,M2.PWM);	

  if(report)usart1_report_imu((short)0,(short)Set_y,(short)0,(short)0,(short)0,(short)0,(int)(M2.CurPos*100),(int)(M1.CurPos*100),(int)(EulerAngle.YAW*10));


}


/*------------------------------------------
 函数功能:模式3，画直线,角度可变
 函数说明:		
------------------------------------------*/
void Mode_3(void)
{
	const float Period=PERIOD;               //单摆周期 
	static u32 MoveCnt=0;                     //每5ms计算一次
	float Omega ;
  float Set_x=  0;                          //x方向设定值 
	float Set_y = 0;                          //y方向设定值
  float A     =0.0f;                        //总振幅	
  float A_x=0.0f;                           //x方向振幅
	float A_y=0.0f;                           //y方向振幅
  float Nomalization=0;                     //归一化变量
	
	MoveCnt+=5;                               //每5ms计算一次
	Nomalization = (float)MoveCnt/Period;     //周期归一化运算
	Omega = Nomalization*2.0*PI;                //换算成对应角度
	//计算x方向和y方向的摆幅比
  
  A = atan((Radius/Height))*57.2958f;
  Set_x = A*sin(Angle)*sin(Omega);
	Set_y = A*cos(Angle)*sin(Omega);
  	

	//电机1  PID运算
	PID_M1_SetPoint(Set_x);                  	//x方向PID跟踪值
//	PID_M1_SetKp(800.0f);
//	PID_M1_SetKi(1.4f);
//	PID_M1_SetKd(50000.0f);

	PID_M1_SetKp(1800.0f);
	PID_M1_SetKi(1.35f);
	PID_M1_SetKd(47000.0f);
		
	M1.PWM = PID_M1_PosLocCalc(M1.CurPos);
	
	//电机2  PID运算
	PID_M2_SetPoint(Set_y);                   //y方向PID跟踪值
	PID_M2_SetKp(900.0f);
	PID_M2_SetKi(0.8f);
	PID_M2_SetKd(50000.0f);
	
	M2.PWM = PID_M2_PosLocCalc(M2.CurPos);
	
  //电机PWM输出限幅
  if(M1.PWM>PWM_MAX) M1.PWM=PWM_MAX;
	if(M1.PWM<-PWM_MAX) M1.PWM=-PWM_MAX;
	if(M2.PWM>PWM_MAX) M2.PWM=PWM_MAX;
	if(M2.PWM<-PWM_MAX) M2.PWM=-PWM_MAX;
	
	//输出PWM波
  SetMotorPWM(M1.PWM,M2.PWM);	
	
	if(report)usart1_report_imu((short)Set_x,(short)Set_y,(short)0,(short)0,(short)0,(short)0,(int)(M2.CurPos*100),(int)(M1.CurPos*100),(int)(EulerAngle.YAW*10));
	


}

/*------------------------------------------
 函数功能:模式4，5s内停止
 函数说明:		
------------------------------------------*/
void Mode_4(void)
{
  
	if(abs(M1.CurPos)<45.0&&abs(M2.CurPos)<45.0)
	{	//电机1  PID运算
		PID_M1_SetPoint(0);                         //x方向PID跟踪值
//		PID_M1_SetKp(1.25f);
//		PID_M1_SetKi(0.15f);
//		PID_M1_SetKd(7000.0f);
		 
		PID_M1_SetKp(0.5f);
		PID_M1_SetKi(0.15f);
		PID_M1_SetKd(5000.0f);
				
		M1.PWM = PID_M1_PosLocCalc(M1.CurPos);
		
		//电机2  PID运算
		PID_M2_SetPoint(0);                          //y方向PID跟踪值
//		PID_M2_SetKp(1.5f);
//		PID_M2_SetKi(0.25f);
//		PID_M2_SetKd(8000.0f);
		
		PID_M2_SetKp(0.7f);
		PID_M2_SetKi(0.25f);
		PID_M2_SetKd(5000.0f);
			
		M2.PWM = PID_M2_PosLocCalc(M2.CurPos);
		
		//电机PWM输出限幅
		if(M1.PWM>PWM_MAX) M1.PWM=PWM_MAX;
		if(M1.PWM<-PWM_MAX) M1.PWM=-PWM_MAX;
		if(M2.PWM>PWM_MAX) M2.PWM=PWM_MAX;
		if(M2.PWM<-PWM_MAX) M2.PWM=-PWM_MAX;
		
	}
	else
	{
	  
	  M1.PWM = 0;
		M2.PWM = 0;
	
	}

  		//输出PWM波
		SetMotorPWM(M1.PWM,M2.PWM);	
	
		if(report)usart1_report_imu((short)0,(short)0,(short)0,(short)0,(short)0,(short)0,(int)(M2.CurPos*100),(int)(M1.CurPos*100),(int)(EulerAngle.YAW*10));

}

/*------------------------------------------
 函数功能:模式5，画圆
 函数说明:		
------------------------------------------*/
void Mode_5(void)
{	
	static float Period=PERIOD;               //单摆周期 
	static u32 MoveCnt=0;                     //每5ms计算一次
	float Omega ;
  float Set_x = 0;                          //x方向设定值 
	float Set_y = 0;                          //y方向设定值
  float A  = 0.0f;                          //振幅(圆的半径)	
  float Phase =0;                           //相位差
  float Nomalization=0;                     //归一化变量
	
	MoveCnt+=5;                               //每5ms计算一次
	Nomalization = (float)MoveCnt/Period;     //周期归一化运算
	Omega = Nomalization*2*PI;                //换算成对应角度
	//计算x方向和y方向的摆幅比
	
	A = atan((Radius/Height))*57.2958f;     	//计算振幅
  
	if(RoundDir == 0)                         //0为正转，1为反转
	{
	     Phase = PI/2.0;
	}
	else
	{
	     Phase = 3.0*PI/2.0;
	}
	Set_x = A*sin(Omega);
	Set_y = A*sin(Omega+Phase);
	
	//电机1  PID运算
	PID_M1_SetPoint(Set_x);                   //x方向PID跟踪值
//	PID_M1_SetKp(PitchSetPIDtemp.kp_temp);
//	PI_M1_SetKi(PitchSetPIDtemp.ki_temp);
//	PID_M1_SetKd(PitchSetPIDtemp.kd_temp);
//	
	
	PID_M1_SetKp(20.0f);
	PID_M1_SetKi(1.4f);
	PID_M1_SetKd(45000.0f);
		
		
	M1.PWM = PID_M1_PosLocCalc(M1.CurPos);
	
	//电机2  PID运算
	PID_M2_SetPoint(Set_y);                   //y方向PID跟踪值
//	PID_M2_SetKp(RollSetPIDtemp.kp_temp);
//	PID_M2_SetKi(RollSetPIDtemp.ki_temp);
//	PID_M2_SetKd(RollSetPIDtemp.kd_temp);
	
	
	PID_M2_SetKp(30.0f);
	PID_M2_SetKi(1.2f);
	PID_M2_SetKd(30000.0f);
//	
//  PID_M2_SetKp(0);
//	PID_M2_SetKi(0);
//	PID_M2_SetKd(0);
	
	M2.PWM = PID_M2_PosLocCalc(M2.CurPos);
	
  //电机PWM输出限幅
  if(M1.PWM>PWM_MAX) M1.PWM=PWM_MAX;
	if(M1.PWM<-PWM_MAX) M1.PWM=-PWM_MAX;
	if(M2.PWM>PWM_MAX) M2.PWM=PWM_MAX;
	if(M2.PWM<-PWM_MAX) M2.PWM=-PWM_MAX;
	
	//输出PWM波
  SetMotorPWM(M1.PWM,M2.PWM);	

  
  if(report)usart1_report_imu((short)Set_x,(short)Set_y,(short)0,(short)0,(short)0,(short)0,(int)(M2.CurPos*100),(int)(M1.CurPos*100),(int)(EulerAngle.YAW*10));

}
/*------------------------------------------
 函数功能:模式6，
 函数说明:		
------------------------------------------*/
void Mode_6(void)
{
}