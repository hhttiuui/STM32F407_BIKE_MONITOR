#include "stm32f4xx.h"
#include "led_laba.h"
#include "mpu6050.h"
#include "oled.h"


extern uint16_t time,ridetime_s,time;

int16_t AX,AY,AZ,GX,GY,GZ;

uint8_t ifshuaiche()
{
	
	MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);
//	if(ridetime_s % 5 == 0 && time == 6 &&AX == 0)			//用于确保MPU6050在短暂的掉电后仍能正常工作
//		MPU6050_Init();
	if(AY>1800||AY<-1800)
		return 1;
	else
		return 0;
}

void dosth()
{
	if(ifshuaiche() == 1)
	{
		ledleft(1);
		ledright(1);
		ledfront(1);
		laba(1);
		OLED_ShowString(2,1,"WARING");
	}
	if(ifshuaiche() == 0)
	{
		OLED_ShowString(2,1,"SAVE  ");
	}

}



