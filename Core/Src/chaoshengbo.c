#include "stm32f4xx.h"
#include "key.h"
#include "gpio.h"
#include "stm32f4xx_it.h"
#include "tim.h"
#include "delay.h"
#include "oled.h"

extern uint16_t time,ridetime_s;

float juli = 0,wide = 0;
uint32_t cc1flag = 0,cc2flag = 0;
uint16_t ccr1 = 0, ccr2 = 0;



void julishow()
{
	if(ridetime_s % 5 == 0 && time == 3)
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET );  
		for(uint32_t i = 0;i<10000;i++);//延时10us
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET ); 

		HAL_TIM_Base_Start(&htim2); 
		
		uint32_t overtime1 = HAL_GetTick()+50;
		
		while( HAL_GPIO_ReadPin (GPIOC ,GPIO_PIN_5) != GPIO_PIN_SET)
		{
			if(HAL_GetTick()>overtime1)	
				break;		
		}
		
		__HAL_TIM_SetCounter(&htim2,0);
		
		uint32_t overtime2 = HAL_GetTick()+50;

		while(HAL_GPIO_ReadPin (GPIOC ,GPIO_PIN_5) == GPIO_PIN_SET)
		{
			if(HAL_GetTick()>overtime2)
				break;
			
		}
		
		wide = __HAL_TIM_GetCounter(&htim2);
		HAL_TIM_Base_Stop(&htim2);
		juli = (uint16_t )wide*1.7;
			
			
			
//			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET );  
//			for(uint32_t i = 0;i<10000;i++);//延时10us
//			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET ); 

//			HAL_TIM_Base_Start(&htim2); 
//			while( HAL_GPIO_ReadPin (GPIOC ,GPIO_PIN_5) != GPIO_PIN_SET);
//			__HAL_TIM_SetCounter(&htim2,0);

//			while(HAL_GPIO_ReadPin (GPIOC ,GPIO_PIN_5) == GPIO_PIN_SET)
//			
//				wide = __HAL_TIM_GetCounter(&htim2);
//			HAL_TIM_Base_Stop(&htim2);

//			 juli = (uint16_t )wide*1.7;	
			
			
			
			
//			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET );  
//			for(uint32_t i = 0;i<10000;i++);//延时10us
//			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET ); 

//			HAL_TIM_Base_Start(&htim2); 
//			while( HAL_GPIO_ReadPin (GPIOC ,GPIO_PIN_5) != GPIO_PIN_SET);
//			__HAL_TIM_SetCounter(&htim2,0);

//			while(HAL_GPIO_ReadPin (GPIOC ,GPIO_PIN_5) == GPIO_PIN_SET)
//			
//				wide = __HAL_TIM_GetCounter(&htim2);
//			HAL_TIM_Base_Stop(&htim2);

//			 juli = (uint16_t )wide*1.7;
		}
		
		if(juli<100 && juli >10)OLED_ShowString(2,11,"BEHIND"); 
		if(juli <= 10)OLED_ShowString(2,11,"   N/M"); 
		if(juli > 100)
			OLED_ShowString(2,10,"       ");
		OLED_ShowNum(3,6,juli,3);
	
		

                       

	
//	if(a == 0)
//	{
//		__HAL_TIM_SET_COUNTER(&htim2,0);//计数器CNT归零
//	
//		__HAL_TIM_CLEAR_FLAG(&htim2,TIM_FLAG_CC1);//清除CC1/CC2标志位
//		__HAL_TIM_CLEAR_FLAG(&htim2,TIM_FLAG_CC2);
//		
//		HAL_TIM_IC_Start(&htim2,TIM_CHANNEL_1);//启动输入捕获
//		HAL_TIM_IC_Start(&htim2,TIM_CHANNEL_2);
//		
//		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);//发送10us的脉冲
//		for(uint32_t i = 0;i<100;i++);//延时10us
//		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
//		
//		cc1flag = __HAL_TIM_GET_FLAG(&htim2,TIM_FLAG_CC1);
//		a = 1;
//	}
//	
//	
//	cc2flag = __HAL_TIM_GET_FLAG(&htim2,TIM_FLAG_CC2);
//	
//	if(cc1flag && cc2flag)
//	{
//		a = 0;
//		HAL_TIM_IC_Stop(&htim2,TIM_CHANNEL_1);//关闭定时器
//		HAL_TIM_IC_Stop(&htim2,TIM_CHANNEL_2);
//		
//		ccr1 = __HAL_TIM_GET_COMPARE(&htim2,TIM_CHANNEL_1);//获取CCR1/CCR2的值
//		ccr2 = __HAL_TIM_GET_COMPARE(&htim2,TIM_CHANNEL_2);
//		
//		wide = (ccr2-ccr1)*1e-6;
//		
//		juli = 340* wide/2;
//	}
		
	
	
	
}

uint16_t showccr()
{
	return ccr1;
}
