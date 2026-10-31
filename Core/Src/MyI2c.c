#include "stm32f4xx.h"                  // Device header
#include "gpio.h"
#include "delay.h"

void MyI2C_W_SCL(uint8_t BitValue)//主机写
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,(GPIO_PinState)BitValue);//置高低电平，1为高
	//Delay_us(5);//防止mpu6050跟不上
}

void MyI2C_W_SDA(uint8_t BitValue)//主机写
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,(GPIO_PinState)BitValue);//置高低电平，1为高
	//Delay_us(5);//防止mpu6050跟不上
}

uint8_t MyI2C_R_SDA(void)//读
{
	uint8_t BitValue;
	BitValue = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11);
	//Delay_us(5);
	return BitValue;
}

void MyI2C_Init(void)
{
	MX_GPIO_Init();
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//开漏输出
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	
//	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
	
}

void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);//先拉高SCL再SDA后拉低SDA,SCL可兼容起始和重复起始
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
	
}

void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i=0;i<8;i++)
	{
		MyI2C_W_SDA(Byte & (0x80>>i));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}

uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t i,Byte = 0x00;
	MyI2C_W_SDA(1);//主机释放
	for (i=0;i<8;i++)
	{
		MyI2C_W_SCL(1);
		if(MyI2C_R_SDA()){Byte |= (0x80>>i);}
		MyI2C_W_SCL(0);
	}
	return Byte;
}

void MyI2C_SendAck(uint8_t AckBit)
{
		MyI2C_W_SDA(AckBit);
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	
}

uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);//主机释放
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}
