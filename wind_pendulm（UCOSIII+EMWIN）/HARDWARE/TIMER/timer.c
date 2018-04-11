#include "timer.h"
#include "includes.h"
#include "totaltask.h"
#include "inv_mpu.h"

//引脚分配

/****************************

四路PWM输出

TIM3_CH1------->PC6
TIM3_CH2------->PC7
TIM3_CH3------->PC8
TIM3_CH4------->PC9


****************************/

/***********变量定义*****************/
TIM_HandleTypeDef TIM3_Handler;           //定时器句柄
TIM_HandleTypeDef TIM2_Handler;
TIM_OC_InitTypeDef TIM3_OCHandler;        //定时器3通道句柄（用于PWM输出）
TIM_ClockConfigTypeDef TIM2_Clock;
TIM_HandleTypeDef TIM5_Handler;           //定时器5句柄（定时5ms采样计算）
/***********变量定义*****************/




/***********************************外部函数****************************************/
//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{ 
    TIM3_Handler.Instance=TIM3;            //定时器3
    TIM3_Handler.Init.Prescaler=psc;       //定时器分频
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    TIM3_Handler.Init.Period=arr;          //自动重装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM3_Handler);       //初始化PWM
    
    TIM3_OCHandler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    TIM3_OCHandler.Pulse=arr;            //设置比较值,此值用来确定占空比，
                                            //默认比较值为自动重装载值的一半,即占空比为50%
    
	  TIM3_OCHandler.OCPolarity=TIM_OCPOLARITY_HIGH; //输出比较极性为高，数值越高占空比越大 
    
	  HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_OCHandler,TIM_CHANNEL_1);//配置TIM3通道1
    
	  TIM3_OCHandler.Pulse=0;            //设置比较值,此值用来确定占空比
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_OCHandler,TIM_CHANNEL_2);//配置TIM3通道2
	
		TIM3_OCHandler.Pulse=0;            //设置比较值,此值用来确定占空比
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_OCHandler,TIM_CHANNEL_3);//配置TIM3通道3
	
		TIM3_OCHandler.Pulse=0;            //设置比较值,此值用来确定占空比
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_OCHandler,TIM_CHANNEL_4);//配置TIM3通道4
	  
	  HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_1);//开启PWM通道4
		HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_2);//开启PWM通道4
		HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_3);//开启PWM通道4
		HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_4);//开启PWM通道4
}
/***********************************外部函数****************************************/

//定时器底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_PWM_Init()调用
//htim:定时器句柄
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_TIM3_CLK_ENABLE();			//使能定时器3
    __HAL_RCC_GPIOC_CLK_ENABLE();			//开启GPIOB时钟
	
    GPIO_Initure.Pin=GPIO_PIN_6;           	//PC6
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推完输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
		GPIO_Initure.Alternate=GPIO_AF2_TIM3;	//PB1复用为TIM3_CH4
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
	
	  GPIO_Initure.Pin=GPIO_PIN_7;           	//PC7
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	  
	  	
	  GPIO_Initure.Pin=GPIO_PIN_8;           	//PC8
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	  
		GPIO_Initure.Pin=GPIO_PIN_9;           	//PC9
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);
}


/***********************************外部函数****************************************/
//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!(定时器3挂在APB1上，时钟为HCLK/2)
void TIM3_Init(u16 arr,u16 psc)
{  
		TIM3_Handler.Instance=TIM3;                          //通用定时器3
    TIM3_Handler.Init.Prescaler=psc;                     //分频
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM3_Handler.Init.Period=arr;                        //自动装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE 
    
}



void TIM2_Init(u32 arr,u16 psc)
{  
	TIM2_Handler.Instance=TIM2;                          //通用定时器3
    TIM2_Handler.Init.Prescaler=psc;                     //分频
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM2_Handler.Init.Period=arr;                        //自动装载值
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM2_Handler);
	//配置TIM2时钟为外部触发时钟
	TIM2_Clock.ClockFilter=0x0;
	TIM2_Clock.ClockPolarity=TIM_CLOCKPOLARITY_RISING;
	TIM2_Clock.ClockPrescaler=TIM_CLOCKPRESCALER_DIV1;
	TIM2_Clock.ClockSource=TIM_CLOCKSOURCE_ETRMODE2;
	HAL_TIM_ConfigClockSource(&TIM2_Handler, &TIM2_Clock);
    
    HAL_TIM_Base_Start_IT(&TIM2_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE 
    	
}
/***********************************外部函数****************************************/

//定时器底册驱动，开启时钟，设置中断优先级
//此函数会被HAL_TIM_Base_Init()函数调用
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //使能TIM3时钟
		HAL_NVIC_SetPriority(TIM3_IRQn,2,3);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //开启ITM3中断   
	}
    else if(htim->Instance==TIM2)
	{
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE(); 
		GPIO_Initure.Pin=GPIO_PIN_15;            //PA15
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;      //复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLDOWN;        //下拉
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
		GPIO_Initure.Alternate=GPIO_AF1_TIM2;   //PA15复用为TIM2_ETR
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);		
	}
   else if(htim->Instance==TIM5)
   {
   		__HAL_RCC_TIM5_CLK_ENABLE();
			HAL_NVIC_SetPriority(TIM5_IRQn,3,3);    //设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(TIM5_IRQn);          //开启TIM5中断
   
   }	   
}



//通用定时器5中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器5!(定时器5挂在APB1上，时钟为HCLK/2)
void TIM5_Init(u32 arr,u16 psc)
{  
		TIM5_Handler.Instance=TIM5;                          //通用定时器5
    TIM5_Handler.Init.Prescaler=psc;                     //分频
    TIM5_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM5_Handler.Init.Period=arr;                        //自动装载值
    TIM5_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM5_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM5_Handler); //使能定时器5和定时器5更新中断：TIM_IT_UPDATE 
    
}



//定时器5中断服务函数
void TIM5_IRQHandler(void)
{

	OSIntEnter();

	HAL_TIM_IRQHandler(&TIM5_Handler);//定时器共用处理函数
	
	
	OSIntExit();
}
 



//定时器输入捕获中断处理回调函数，该函数在HAL_TIM_IRQHandler中会被调用
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//捕获中断发生时执行
{
	
}



//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}


void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM2_Handler);
}


/*-----------------------------------------
				溢  出  中  断  函 数
------------------------------------------*/ 
//定时器更新中断（计数溢出）中断处理回调函数， 该函数在HAL_TIM_IRQHandler中会被调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	OS_ERR err;

/*------------------------------------------------
   说明：TIM5溢出中断，采用信号量同步，转至ANGLETASK
	       中处理，采样并计算欧拉角
	 中断频率：200Hz
--------------------------------------------------*/ 
	if(htim->Instance==TIM5)
	{
		
		
			OSTaskSemPost ( &ANGLETastTCB,
										  OS_OPT_POST_NONE,
										  &err);
		 
		}
}
