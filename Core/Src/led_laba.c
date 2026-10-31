#include "stm32f4xx.h"
#include "key.h"
#include "gpio.h"
#include "oled.h"
#include "waring.h"

uint16_t shijian = 5;//用于设定灯闪烁时间

void led_laba_init()
{
	MX_GPIO_Init();
}

void ledleft(uint8_t b)
{
	uint16_t a;
	if(b == 0)//关闭左转向灯
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET);
		OLED_ShowString(4,1,"    ");
	}
	else if(b == 1)//让左转向灯以一定频率闪烁
	{
		a = showtime();
		if(a<=shijian)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_SET);
			OLED_ShowString(4,1,"LEFT");
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET);
			OLED_ShowString(4,1,"    ");
		}
			
	}
	else if(b == 3)//让左转向灯常亮
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_SET);
		OLED_ShowString(4,1,"LEFT");
	}
	
}

void ledright(uint8_t b)
{
	uint16_t a;//设定闪烁时间
	if(b == 0)//关闭右转向灯
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET);
		OLED_ShowString(4,12,"     ");
	}
	else if(b == 1)//让右转向灯以一定频率闪烁
	{
		a = showtime();//设定闪烁时间
		if(a<=shijian)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_SET);
			OLED_ShowString(4,12,"RIGHT");
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET);
			OLED_ShowString(4,12,"     ");
		}
			
	}
	else if(b == 3)//让右转向灯常亮
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_SET);
		OLED_ShowString(4,12,"RIGHT");
	}
	
}

void ledfront(uint8_t b)//前大灯
{
	uint16_t a;
	if(b == 0)//关闭前大灯
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_RESET);
		OLED_ShowString(4,7,"OFF");
	}
	else if(b == 1)//让前大灯以一定频率闪烁
	{
		a = showtime();
		if(a<=shijian)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_SET);
			OLED_ShowString(4,7,"ON ");
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_RESET);
			OLED_ShowString(4,7,"OFF");
		}
	}
	else if(b == 3)//让前大灯常亮
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_SET);
		OLED_ShowString(4,7,"ON ");
	}
	
}

void led_under(uint8_t b)//下方的灯
{
	uint16_t a;
	if(b == 0)//关闭
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,GPIO_PIN_RESET);

	}
	else if(b == 1)//让下方的灯以一定频率启动
	{
		a = showtime();
		if(a<=shijian)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,GPIO_PIN_RESET);

		}
		else
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,GPIO_PIN_SET);

		}
	}
	else if(b == 3)//让下方的灯常开
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,GPIO_PIN_SET);

	}
	
}

void laba(uint8_t b)//喇叭
{
	uint16_t a;
	if(b == 0)//关闭喇叭
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);

	}
	else if(b == 1)//让喇叭以一定频率启动
	{
		a = showtime();
		if(a<=shijian)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);

		}
		else
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);

		}
	}
	else if(b == 3)//让喇叭常开
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);

	}
	
}


void zhuanxiangdeng()
{
	if(Key_GetNum(1) == 1)						//Key_GetNum(1)1±íÊ¾×ªÏòµÆµÄ°´Å¥
		{
			ledleft(1);
			ledright(0);
		}
		else if(Key_GetNum(1) == 2)
		{
			ledright(1);
			ledleft(0);
		}
		else if(Key_GetNum(1) == 0)
		{
			ledright(0);
			ledleft(0);
			
		}
}

void laba_dadeng()
{
	if(Key_GetNum(2) == 1 && ifshuaiche() == 0)//Key_GetNum(2)2±íÊ¾´óµÆµÄ
	{
		ledfront(3);
	}
	else if(Key_GetNum(2) == 0 && ifshuaiche() == 0)
	{
		ledfront(0);
	}
		
	if(Key_GetNum(3) == 1 && ifshuaiche() == 0)//Key_GetNum(3)3±íÊ¾À®°ÈµÄ
	{
		laba(3);
	}
	else if(Key_GetNum(3) == 0 && ifshuaiche() == 0)
	{
		laba(0);
	}
}
  
void moshi()
{
	if(Key_GetNum(4) == 0)//4表示获取模式的按钮
	{
		OLED_ShowString(1,15,"D");
		led_under(0);
		
	}
	if(Key_GetNum(4) == 1)
	{
		led_under(1);
		OLED_ShowString(1,15,"N");
	}
}

//uint16_t time = 0;

//uint16_t showtime()
//{
//	return time;
//}




