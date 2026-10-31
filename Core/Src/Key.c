#include "stm32f4xx.h"                  // Device header
//#include "delay.h"
#include "gpio.h"

void Key_Init(void)
{
	MX_GPIO_Init();
}

uint8_t KeyNumzhuan = 0,KeyNumlaba = 0,KeyNumdeng = 0,KeyNummoshi = 0;
uint16_t time = 0;
uint16_t sptim = 0;
uint16_t wendutim = 0;
uint16_t ridetime_s = 0;

uint8_t Key_GetNum(uint8_t num)//获得按键位置
{
	if(num == 1)
		return KeyNumzhuan;
	else if(num == 2)
		return KeyNumlaba;
	else if(num == 3)
		return KeyNumdeng;
	else if(num == 4)
		return KeyNummoshi;
	else 
		return 0;
}

uint16_t showtime()
{
	return time;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//定时器定时扫描按键
{
	if(htim->Instance==TIM1)
	{
		
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_7) == SET)//左转向灯
			KeyNumzhuan = 1;
		else if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_8) == SET)//右转向灯		
			KeyNumzhuan = 2;
		else
			KeyNumzhuan = 0;
	
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_9) == SET)//喇叭		
			KeyNumlaba = 1;
		else
			KeyNumlaba = 0;
		
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_10) == SET)//大灯
			KeyNumdeng = 1;
		else
			KeyNumdeng = 0;
		
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2) == SET)//模式
			KeyNummoshi = 1;
		else
			KeyNummoshi = 0;
		
		time++;
		if(time>10)time = 0;
		
		sptim++;
		
		wendutim++;
		if(wendutim >40)wendutim = 0;
	}
	
	if(htim->Instance==TIM3)
	{
		ridetime_s++;
		if(ridetime_s>=60)
		{
			ridetime_s = 0;
		}
	}
}
