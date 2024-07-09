
#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio.h"
#include "iot_gpio_ex.h"
#include "iot_errno.h"
#include "hi_pwm.h"
#include "hi_io.h"
#include "hi_time.h"
#include "hi_adc.h"
#include "hi_uart.h"
#include "iot_uart.h"
#include "USART.h"



void Uart1GpioInit(void)
{
IoTGpioInit(HI_IO_NAME_GPIO_0);
// 设置GPIO0的管脚复用关系为UART1_TX Set the pin reuse relationship of GPIO0 UART1_ TX

hi_io_set_func(HI_IO_NAME_GPIO_0, HI_IO_FUNC_GPIO_0_UART1_TXD);
IoTGpioInit(HI_IO_NAME_GPIO_1);
// 设置GPIO1的管脚复用关系为UART1_RX Set the pin reuse relationship of GPIO1 UART1_ RX
hi_io_set_func(HI_IO_NAME_GPIO_1, HI_IO_FUNC_GPIO_1_UART1_RXD);
}

void Uart1Config(void)
{
uint32_t ret;
/* 初始化UART配置，波特率 9600，数据bit为8,停止位1，奇偶校验为NONE */
/* Initialize UART configuration, baud rate is 9600, data bit is 8, stop bit is 1, parity is NONE */

IotUartAttribute uart_attr = {
.baudRate = 9600,
.dataBits = 8,
.stopBits = 1,
.parity = 0,
};
ret = IoTUartInit(HI_UART_IDX_1, &uart_attr);
if (ret != IOT_SUCCESS) {
printf("Init Uart1 Falied Error No : %d\n", ret);
return;
}
}

void UartTask(const char* data)
{
uint32_t count = 0;

// 对UART1的一些初始化 Some initialization of UART1
Uart1GpioInit();
// 对UART1参数的一些配置 Some configurations of UART1 parameters
Uart1Config();

// 通过UART1 发送数据 Send data through UART1
IoTUartWrite(HI_UART_IDX_1, (unsigned char*)data, strlen(data));
}






