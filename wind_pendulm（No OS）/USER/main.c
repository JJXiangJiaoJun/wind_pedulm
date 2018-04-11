/*-------------------------------------------------------------------------------------------
        		   			风力摆控制系统(2017-8-19)

 硬件平台:
 			主控器: STM32F767 
			驱动器: L298N
		    电源: DC +12V

 软件平台:
 			开发环境: RealView MDK-ARM uVision5.20
			C编译器 : ARMCC
			ASM编译器:ARMASM
			连接器:   STLINK
			底层驱动: 各个外设驱动程序       
 
 时间: 2017年8月19日       
 
 作者: 香蕉君
-------------------------------------------------------------------------------------------*/   

/*-------------------------------------------------------------------------------------------
 引脚配置：
 
 电机1PWM --------------->  PC6
 电机2PWM --------------->  PC7
 电机3PWM --------------->  PC8
 电机4PWM --------------->  PC9
 
 IIC_SCL  --------------->  PH4
 IIC_SDA  --------------->  PH5 
 
 
  
-------------------------------------------------------------------------------------------*/   


#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "malloc.h"
#include "timer.h"
#include "motor_pid.h"
#include "motor_control.h" 

/*-----------------------------------------
				 外 设 头 文 件 包 含
------------------------------------------*/ 
#include "mpu6050.h"
#include "inv_mpu.h"
#include "niming.h"


//各任务头文件包含

//************************************************
//************************************************


/*-----------------------------------------
				 初  始  任  务
------------------------------------------*/ 



/*-----------------------------------------
				主     函    数
------------------------------------------*/  

//注意！！！！MPU6050的读取速率要和采样速率保持一致，不然容易出现问题


int main(void)
{
	    u8 res;
	    u8 buf[30];
	
      Write_Through(); 
			Cache_Enable();                 //打开L1-Cache
			HAL_Init();				      			  //初始化HAL库
			Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 
			delay_init(216);                //延时初始化
			
	   /*---------------外设初始化----------------------*/
	    uart_init(500000);		       	//串口初始化
			LED_Init();                   //初始化LED
			KEY_Init();                   //初始化按键
			SDRAM_Init();                 //初始化SDRAM
			LCD_Init();                   //初始化LCDq
			my_mem_init(SRAMIN);		   	 	//初始化内部内存池
			my_mem_init(SRAMEX);		    	//初始化外部内存池
			my_mem_init(SRAMDTCM);		    //初始化DTCM内存池
	    LCD_ShowString(40,50,100,100,16,"MPU_Init...");
	    
			while(MPU_Init())
			{
				 delay_ms(10);
				 LCD_ShowString(40,150,100,100,16,"MPU_ERROR");
			
			}
			delay_ms(10);
			LCD_ShowString(40,50,100,100,16,"MPU_SUCCESS...");
			
			LCD_ShowString(40,200,100,100,16,"MPU_DMP_Init...");

			while(mpu_dmp_init())
			{
					
			   delay_ms(200);
				 res=mpu_dmp_init();
				 LCD_ShowString(20,250,100,100,16,"MPU_DMP_ERROR");
			   LCD_ShowNum(20,150,res,16,16);
				 delay_ms(200);
			}
			LCD_ShowString(20,200,100,100,16,"MPU_DMP_SUCCESS");
			
			delay_ms(200);
			LCD_Clear(WHITE);
			
			POINT_COLOR=BLUE;//设置字体为蓝色 
			LCD_ShowString(10,30,300,300,24,"HUN Wind pendulum");
			POINT_COLOR=RED;//设置字体为蓝色 
			LCD_ShowString(90,80,300,300,16,"-----By xiang jiao jun");

      POINT_COLOR=YELLOW;//设置字体为蓝色
      
			LCD_ShowString(30,170,200,24,24,"System Runing......");	 
			
			POINT_COLOR=MAGENTA;//设置字体为蓝色
			
			LCD_ShowString(30,260,200,24,24,"Mode  : 1 ");	
			
			LCD_ShowString(30,290,200,24,24,"Radius: 25.0cm");	
			
			LCD_ShowString(30,320,200,24,24,"Angle : 90");	 
			
			LCD_ShowString(30,350,200,24,24,"RoundDir : 0");
			
			PitchSetPID_Init();
			RollSetPID_Init();
				
			TIM3_PWM_Init(5400-1,1-1);    //TIM3实现4路PWM输出
			TIM5_Init(5000-1,108-1);      //5ms中断一次，进行同步采样
			

							 
		while(1)
		{   
      //上位机修改PID参数
			if(USART_RX_STA == 1)
			{
			   USART_RX_STA = 0;
				
				 LED0_Toggle;
				
				//上位机发送的PID读入缓冲区
				RollSetPIDtemp.kp_temp = (USART_RX_BUF[4]<<8)|USART_RX_BUF[5];
				//RollSetPIDtemp.ki_temp = (USART_RX_BUF[6]<<8)|USART_RX_BUF[7];
				RollSetPIDtemp.kd_temp = (USART_RX_BUF[8]<<8)|USART_RX_BUF[9];
				
				PitchSetPIDtemp.kp_temp = (USART_RX_BUF[10]<<8)|USART_RX_BUF[11];
				PitchSetPIDtemp.ki_temp = (USART_RX_BUF[12]<<8)|USART_RX_BUF[13];
				PitchSetPIDtemp.kd_temp = (USART_RX_BUF[14]<<8)|USART_RX_BUF[15];
				 
			  Mode       =   (u8) RollSetPIDtemp.kd_temp;                     //改变模式
				Radius     =   (float)PitchSetPIDtemp.kp_temp;                  //改变半径
				Angle      =   (float)PitchSetPIDtemp.ki_temp/57.2958f;         //改变角度
				RoundDir   =  (u8)PitchSetPIDtemp.kd_temp;                      //改变旋转方向
				
				
				sprintf((char *)buf,"Mode  : %d ",Mode);
				
				LCD_ShowString(30,260,200,24,24,buf);
				
				sprintf((char *)buf,"Radius: %.1fcm  ",Radius);
				
				LCD_ShowString(30,290,200,24,24,buf);
				
				sprintf((char *)buf,"Angle : %.0f    ",PitchSetPIDtemp.ki_temp);
				
				LCD_ShowString(30,320,200,24,24,buf);
				
				sprintf((char *)buf,"RoundDir : %d  ",RoundDir);
				
				LCD_ShowString(30,350,200,24,24,buf);
		
			}
          
			
		}
}