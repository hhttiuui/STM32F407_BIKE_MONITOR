#include "stm32f4xx.h"                  // Device header
#include "gpio.h"
#include "usart.h"
#include "cesu.h"
#include "key.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

extern uint8_t du_C,sp,ridetime_s,ridetime_min,time;
char* a1;						//16进制转换成10进制，再以字符串的形式存储
char* a2;
char* b1;
char* c1;


// 参数：hex - 要转换的十六进制数
//        buffer - 外部提供的缓冲区（至少12字节）
// 返回值：指向结果的指针
char* hex_to_dec_str_static(unsigned int hex, char* buffer) {
    // 处理0值
    if (hex == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return buffer;
    }
    
    // 从缓冲区末尾开始填充
    char* p = buffer + 11; // 32位整数最大10位数字 + 结束符
    *p = '\0';  // 设置结束符
    
    unsigned int temp = hex;
    while (temp) {
        *--p = '0' + (temp % 10);  // 提取最后一位数字
        temp /= 10;  // 移除最后一位
    }
    
    return p;
}

void lanya()
{
	char buffer1[12],buffer2[12],buffer3[12],buffer4[12];
	char *T = "  t:";
	char *T2 = ":";
	char *TEMP = "  temp:";
	char *V = "  v:";
	a1 = hex_to_dec_str_static(ridetime_s,buffer1);
	a2 = hex_to_dec_str_static(ridetime_min,buffer4);
	b1 = hex_to_dec_str_static(du_C,buffer2);
	c1 = hex_to_dec_str_static(sp,buffer3);
	
	if(ridetime_s % 10 == 0 && time == 3)
	{
		HAL_UART_Transmit(&huart1,(uint8_t*)T,strlen(T),10);//时间，当前速度，每10s传输一次
		HAL_UART_Transmit(&huart1,(uint8_t*)a2,2,10);
		HAL_UART_Transmit(&huart1,(uint8_t*)T2,strlen(T2),10);
		HAL_UART_Transmit(&huart1,(uint8_t*)a1,2,10);
		
		HAL_UART_Transmit(&huart1,(uint8_t*)TEMP,strlen(TEMP),10);//温度，当前速度，每10s传输一次
		HAL_UART_Transmit(&huart1,(uint8_t*)b1,2,10);
		
		HAL_UART_Transmit(&huart1,(uint8_t*)V,strlen(V),10);//温度，当前速度，每10s传输一次
		HAL_UART_Transmit(&huart1,(uint8_t*)c1,2,10);
		
	}
	
}


