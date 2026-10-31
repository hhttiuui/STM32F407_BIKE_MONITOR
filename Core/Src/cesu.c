#include "stm32f4xx.h"
#include "key.h"
#include "gpio.h"
#include "stm32f4xx_it.h"
#include "adc.h"
#include "oled.h"

extern uint16_t co,sptim;
extern uint16_t time;
extern uint16_t wendutim;
extern uint16_t ridetime_s;
uint16_t ridetime_min = 0;
uint16_t sp = 0;
uint16_t du = 0;
uint8_t a = 0;
uint16_t du_C;

void speedshow()
{
	
	if(sptim > 20)
	{
		sp = 3.14*0.3*2*co/18;
		co = 0;
		sptim = 0;
	}
	OLED_ShowNum(3,3,sp,2);


	
}

void wendushow()
{
	
	if(wendutim == 5 )
	{
		HAL_ADC_Start(&hadc3);
		if(HAL_ADC_PollForConversion(&hadc3,50) == HAL_OK)
		{
			du = HAL_ADC_GetValue(&hadc3);
		}
	}
	du_C = -0.04 * du + 105;
	OLED_ShowNum(3,13,du_C,2);
	//OLED_ShowNum(4,13,du,4);
	
}

void ridetimeshow()
{
	OLED_ShowNum(1,6,ridetime_min,3);
	OLED_ShowNum(1,10,ridetime_s,2);
	
	if(ridetime_s == 0 && a == 0)
	{
		ridetime_min++;
		a = 1;
	}
	if(ridetime_s == 1 && a == 1)
	{
		a = 0;
	}
	
	
}





