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
                                       //上述IO口以被SD卡占用
 IIC_SCL  --------------->  PH4
 IIC_SDA  --------------->  PH5 
 
 
 
 
 
 注意！！！！！！！：实时控制系统中，使用EMWIN，请不要用外部输入图像的方法，速度回非常非常慢，导致整个系统瘫痪
 
 
  
-------------------------------------------------------------------------------------------*/   


#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "tftlcd.h"
#include "sdram.h"
#include "malloc.h"
#include "timer.h"
#include "touch.h"
#include "mpu.h"
#include "includes.h"

#include "sdmmc_sdcard.h"
#include "ff.h"
#include "ftl.h" 
#include "exfuns.h"


/*-----------------------------------------
				 外 设 头 文 件 包 含
------------------------------------------*/ 
#include "mpu6050.h"
#include "inv_mpu.h"
#include "GUI.h"
#include "WM.h"
#include "fontupd.h"


//各任务头文件包含

//************************************************
#include "totaltask.h"
//************************************************


/*-----------------------------------------
				 初  始  任  务
------------------------------------------*/ 


//任务优先级
#define START_TASK_PRIO 5
//任务堆栈大小
#define START_STK_SIZE 256
//任务控制块
OS_TCB  StartTaskTCB;
//任务堆栈
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);



/*-----------------------------------------
				主     函    数
------------------------------------------*/  

//注意！！！！MPU6050的读取速率要和采样速率保持一致，不然容易出现问题


int main(void)
{
      OS_ERR err;
	    u8 res;
	    CPU_SR_ALLOC();
	
      Write_Through();
      MPU_Memory_Protection();        //保护相关存储区域	
			Cache_Enable();                 //打开L1-Cache
			HAL_Init();				      			  //初始化HAL库
			Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 
			delay_init(216);                //延时初始化
			
	   /*---------------外设初始化----------------------*/
	    uart_init(500000);		       	//串口初始化
			LED_Init();                   //初始化LED
			KEY_Init();                   //初始化按键
			SDRAM_Init();                 //初始化SDRAM
			TFTLCD_Init();                   //初始化LCD
			TP_Init();
			my_mem_init(SRAMIN);		   	 	//初始化内部内存池
			my_mem_init(SRAMEX);		    	//初始化外部内存池
			my_mem_init(SRAMDTCM);		    //初始化DTCM内存池
	    LCD_ShowString(40,50,100,100,16,"System_Init...");
			
		  exfuns_init();			        //为fatfs相关变量申请内存				 
  	  f_mount(fs[0],"0:",1); 		    //挂载SD卡 
      f_mount(fs[1],"1:",1); 	        //挂载FLASH.	
      f_mount(fs[2],"2:",1); 		    //挂载NAND FLASH.

		while(SD_Init())	//检测SD卡
		{
			LCD_ShowString(30,90,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(30,90,200+30,70+16,WHITE);
			delay_ms(200);		    
		}
		font_init();
			/*-----------------------------------------
				初        始       化      MPU6050
			------------------------------------------*/  
			
//			while(MPU_Init())
//			{
//				 delay_ms(10);
//				 LCD_ShowString(40,150,100,100,16,"MPU_ERROR");
//			
//			}
			delay_ms(10);
			LCD_ShowString(40,50,100,100,16,"MPU_SUCCESS...");
			
			LCD_ShowString(40,200,100,100,16,"MPU_DMP_Init...");

//			while(mpu_dmp_init())
//			{
//					
//			   delay_ms(200);
//				 res=mpu_dmp_init();
//				 LCD_ShowString(20,250,100,100,16,"MPU_DMP_ERROR");
//			   LCD_ShowNum(20,150,res,16,16);
//				 delay_ms(200);
//			}
			LCD_ShowString(20,200,100,100,16,"MPU_DMP_SUCCESS");
			delay_ms(200);
			LCD_Clear(WHITE);
				
			//TIM3_PWM_Init(5400-1,1-1);    //TIM3实现4路PWM输出
			TIM5_Init(5000-1,108-1);      //5ms中断一次，进行同步采样
			
			
			/*----------------UCOSIII初始化------------------*/ 
			/*----------------创建开始任务------------------*/ 
      OSInit(&err);
	    OS_CRITICAL_ENTER();
	    
			OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
				
		OS_CRITICAL_EXIT();
    OSStart(&err); 								 
		/*----------------UCOSIII初始化------------------*/ 
		while(1)
		{		       
		}
}

void start_task(void *p_arg)
{
		OS_ERR err;
		CPU_SR_ALLOC();
		p_arg=p_arg;
	 
	  CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	  //使能时间片轮转调度功能,设置默认的时间片长度
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif	
	OS_CRITICAL_ENTER();
	/*-----------------------------------------
			各  任  务  初  始  化
	------------------------------------------*/ 
 	__HAL_RCC_CRC_CLK_ENABLE();		//使能CRC时钟
	GUI_Init();  			//STemWin初始化
	WM_MULTIBUF_Enable(1);  //开启STemWin多缓冲,RGB屏可能会用到
	
	led_task_init(&err);
	//lcd_task_init(&err);
	enwin_task_init(&err);
	touch_task_init(&err);
	angle_task_init(&err);
  //fontupdata_task_init(&err);
	OS_CRITICAL_EXIT();
  OSTaskDel((OS_TCB*)0,&err);								 

}



