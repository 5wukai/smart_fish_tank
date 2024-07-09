#ifndef __DS18B20_H
#define	__DS18B20_H

#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio.h"
#include "iot_errno.h"
#include "hi_pwm.h"
#include "hi_io.h"
#include "hi_time.h"


#define HIGH  1
#define LOW   0

#define SET 1

#define u8 unsigned char

#define DS18B20_PIN     HI_IO_NAME_GPIO_1
#define DS18B20_PIN_GPIO HI_IO_FUNC_GPIO_1_GPIO

//带参宏，可以像内联函数一样使用,输出高电平或低电平
#define DS18B20_DATA_OUT(HIGH) IoTGpioSetOutputVal(DS18B20_PIN, IOT_GPIO_VALUE1)
			
#define DS18B20_DATA_OUT(LOW) IoTGpioSetOutputVal(DS18B20_PIN, IOT_GPIO_VALUE0)
 //读取引脚的电平
#define  DS18B20_DATA_IN()	   /*IoTGpioGetInputVal(DS18B20_PIN, &value)*/value

typedef struct
{
	u8  humi_int;		//湿度的整数部分
	u8  humi_deci;	 	//湿度的小数部分
	u8  temp_int;	 	//温度的整数部分
	u8  temp_deci;	 	//温度的小数部分
	u8  check_sum;	 	//校验和
		                 
}DS18B20_Data_TypeDef;

u8 DS18B20_Init(void);
float DS18B20_Get_Temp(void);
#endif 