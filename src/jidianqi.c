#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "cmsis_os2.h"
#include "iot_errno.h"
#include "iot_gpio.h"
#include "iot_gpio_ex.h"
#include "iot_i2c.h"
#include "iot_i2c_ex.h"
#include "hi_io.h"
#include "jidianqi.h" 
#include "E53_IA1.h"

 void jidianqiIoInit(void)
{
    IoTGpioInit(E53_IA1_guo_GPIO);
    hi_io_set_func(HI_IO_NAME_GPIO_3, HI_IO_FUNC_GPIO_3_GPIO); //过滤
    IoTGpioSetDir(E53_IA1_guo_GPIO, IOT_GPIO_DIR_OUT); // 设置GPIO_3为输出模式

    IoTGpioInit(E53_IA1_chou_GPIO);
    IoTGpioSetFunc(HI_IO_NAME_GPIO_4, HI_IO_FUNC_GPIO_4_GPIO); //抽水
    IoTGpioSetDir(E53_IA1_chou_GPIO, IOT_GPIO_DIR_OUT); // 设置GPIO_4为输出模式

    IoTGpioInit(E53_IA1_zhu_GPIO);
    IoTGpioSetFunc(HI_IO_NAME_GPIO_5, HI_IO_FUNC_GPIO_5_GPIO); //注水
    IoTGpioSetDir(E53_IA1_zhu_GPIO, IOT_GPIO_DIR_OUT); // 设置GPIO_5为输出模式

    IoTGpioInit(E53_IA1_jia_GPIO);
    IoTGpioSetFunc(HI_IO_NAME_GPIO_6, HI_IO_FUNC_GPIO_6_GPIO); //加热
    IoTGpioSetDir(E53_IA1_jia_GPIO, IOT_GPIO_DIR_OUT); // 设置GPIO_7为输出模式

    IoTGpioInit(E53_IA1_kai_GPIO);
    IoTGpioSetFunc(HI_IO_NAME_GPIO_9, HI_IO_FUNC_GPIO_9_GPIO); //开灯
    IoTGpioSetDir(E53_IA1_kai_GPIO, IOT_GPIO_DIR_OUT); // 设置GPIO_8为输出模式   


}

void guoStatusSet(E53IA1Status status)
{
    if (status == ON) {
        IoTGpioSetOutputVal(E53_IA1_guo_GPIO, 1); // 设置GPIO_8输出高电平打开过滤
    }

    if (status == OFF) {
        IoTGpioSetOutputVal(E53_IA1_guo_GPIO, 0); // 设置GPIO_8输出低电平关闭过滤
    }
}

void chouStatusSet(E53IA1Status status)
{
    if (status == ON) {
        IoTGpioSetOutputVal(E53_IA1_chou_GPIO, 1); // 设置GPIO_8输出高电平打开抽水
    }

    if (status == OFF) {
        IoTGpioSetOutputVal(E53_IA1_chou_GPIO, 0); // 设置GPIO_8输出低电平关闭抽水
    }
}

void zhuStatusSet(E53IA1Status status)
{
    if (status == ON) {
        IoTGpioSetOutputVal(E53_IA1_zhu_GPIO, 1); // 设置GPIO_8输出高电平打开注水 
    }

    if (status == OFF) {
        IoTGpioSetOutputVal(E53_IA1_zhu_GPIO, 0); // 设置GPIO_8输出低电平关闭注水
    }
}

void jiaStatusSet(E53IA1Status status)
{
    if (status == ON) {
        IoTGpioSetOutputVal(E53_IA1_jia_GPIO, 1); // 设置GPIO_8输出高电平打开加热
    }

    if (status == OFF) {
        IoTGpioSetOutputVal(E53_IA1_jia_GPIO, 0); // 设置GPIO_8输出低电平关闭加热
    }
}

void kaiStatusSet(E53IA1Status status)
{
    if (status == ON) {
        IoTGpioSetOutputVal(E53_IA1_kai_GPIO, 1); // 设置GPIO_8输出高电平开灯
    }

    if (status == OFF) {
        IoTGpioSetOutputVal(E53_IA1_kai_GPIO, 0); // 设置GPIO_8输出低电平关灯
    }
}
