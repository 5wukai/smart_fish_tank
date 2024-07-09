
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
#include "ds18b20.h"


void DS18B20_GPIO_Config(void)
{		
	IoTGpioInit(DS18B20_PIN);
	hi_io_set_func(DS18B20_PIN, DS18B20_PIN_GPIO);
	IoTGpioSetDir(DS18B20_PIN, IOT_GPIO_DIR_OUT);  //推挽输出  
	
	IoTGpioSetOutputVal(DS18B20_PIN, IOT_GPIO_VALUE1);	 //DS18B20数据引脚初始化配置为高电平输出
}

void DS18B20_Mode_IPU(void)
{
 	  IoTGpioInit(DS18B20_PIN);
      hi_io_set_func(DS18B20_PIN, DS18B20_PIN_GPIO);
      IoTGpioSetDir(DS18B20_PIN, IOT_GPIO_DIR_IN);
	  hi_io_set_pull(DS18B20_PIN, HI_IO_PULL_UP);

}

void DS18B20_Mode_Out_PP(void)
{
	IoTGpioInit(DS18B20_PIN);
	hi_io_set_func(DS18B20_PIN, DS18B20_PIN_GPIO);
	IoTGpioSetDir(DS18B20_PIN, IOT_GPIO_DIR_OUT);  //推挽输出  
	
	IoTGpioSetOutputVal(DS18B20_PIN, IOT_GPIO_VALUE1);
}

 /**************************************************************************************
 * 描  述 : 主机给从机发送复位脉冲
 * 入  参 : 无
 * 返回值 : 无
 **************************************************************************************/
void DS18B20_Rst(void)
{
	DS18B20_Mode_Out_PP();     //主机设置为推挽输出 
	
	DS18B20_DATA_OUT(LOW);     //主机至少产生480us的低电平复位信号
	hi_udelay(750);
	DS18B20_DATA_OUT(HIGH);   //主机在产生复位信号后，需将总线拉高
	hi_udelay(15);   //从机接收到主机的复位信号后，会在15~60us后给主机发一个存在脉冲
}

 /**************************************************************************************
 * 描  述 : 检测从机给主机返回的存在脉冲
 * 入  参 : 无
 * 返回值 : 0：成功   1：失败  
 **************************************************************************************/
u8 DS18B20_Presence(void)
{
	u8 pulse_time = 0;
	IotGpioValue value;
	DS18B20_Mode_IPU();    //主机设置为上拉输入
	
	/* 等待存在脉冲的到来，存在脉冲为一个60~240us的低电平信号 
	 * 如果存在脉冲没有来则做超时处理，从机接收到主机的复位信号后，会在15~60us后给主机发一个存在脉冲
	 */
	IoTGpioGetInputVal(DS18B20_PIN, &value);
	while( DS18B20_DATA_IN() && pulse_time<100 )
	{
		pulse_time++;
		hi_udelay(1);
		IoTGpioGetInputVal(DS18B20_PIN, &value);
	}	

	if( pulse_time >=100 )  //经过100us后，存在脉冲都还没有到来
		return 1;             //读取失败
	else                 //经过100us后，存在脉冲到来
		pulse_time = 0;    //清零计时变量
	
	while( !DS18B20_DATA_IN() && pulse_time<240 )  // 存在脉冲到来，且存在的时间不能超过240us
	{
		pulse_time++;
		hi_udelay(1);
		IoTGpioGetInputVal(DS18B20_PIN, &value);
	}	
	if( pulse_time >=240 ) // 存在脉冲到来，且存在的时间超过了240us
		return 1;        //读取失败
	else
		return 0;
}
u8 DS18B20_Read_Bit(void)
{
	u8 dat;
	IotGpioValue value;
	
	/* 读0和读1的时间至少要大于60us */	
	DS18B20_Mode_Out_PP();
	/* 读时间的起始：必须由主机产生 >1us <15us 的低电平信号 */
	DS18B20_DATA_OUT(LOW);
	hi_udelay(10);
	
	/* 设置成输入，释放总线，由外部上拉电阻将总线拉高 */
	DS18B20_Mode_IPU();
	IoTGpioGetInputVal(DS18B20_PIN, &value);
	if( DS18B20_DATA_IN() == SET )
		dat = 1;
	else
		dat = 0;
	
	/* 这个延时参数请参考时序图 */
	hi_udelay(45);
	
	return dat;
}

u8 DS18B20_Read_Byte(void)
{
	u8 i, j, dat = 0;	
	
	for(i=0; i<8; i++) 
	{
		j = DS18B20_Read_Bit();		//从DS18B20读取一个bit
		dat = (dat) | (j<<i);
	}
	
	return dat;																																																																																
}

void DS18B20_Write_Byte(u8 dat)
{
	u8 i, testb;
	DS18B20_Mode_Out_PP();
	
	for( i=0; i<8; i++ )
	{
		testb = dat&0x01;
		dat = dat>>1;		
		/* 写0和写1的时间至少要大于60us */
		if (testb)
		{			
			DS18B20_DATA_OUT(LOW);
			hi_udelay(8);   //1us < 这个延时 < 15us
			
			DS18B20_DATA_OUT(HIGH);
			hi_udelay(58);    //58us+8us>60us
		}		
		else
		{			
			DS18B20_DATA_OUT(LOW);  
			/* 60us < Tx 0 < 120us */
			hi_udelay(70);
			
			DS18B20_DATA_OUT(HIGH);			
			/* 1us < Trec(恢复时间) < 无穷大*/
			hi_udelay(2);
		}
	}
}

void DS18B20_Start(void)
{
	DS18B20_Rst();	           //主机给从机发送复位脉冲
	DS18B20_Presence();	       //检测从机给主机返回的存在脉冲
	DS18B20_Write_Byte(0XCC);		 // 跳过 ROM 
	DS18B20_Write_Byte(0X44);		 // 开始转换 
}

u8 DS18B20_Init(void)
{
	DS18B20_GPIO_Config();   
	DS18B20_Rst();
	
	return DS18B20_Presence();
}

float DS18B20_Get_Temp(void)
{
	u8 tpmsb, tplsb;
	short s_tem;
	float f_tem;
	
	DS18B20_Rst();	   
	DS18B20_Presence();	 
	DS18B20_Write_Byte(0XCC);				/* 跳过 ROM */
	DS18B20_Write_Byte(0X44);				/* 开始转换 */
	
	DS18B20_Rst();
  DS18B20_Presence();
	DS18B20_Write_Byte(0XCC);				/* 跳过 ROM */
  DS18B20_Write_Byte(0XBE);				/* 读温度值 */
	
	tplsb = DS18B20_Read_Byte();		 
	tpmsb = DS18B20_Read_Byte(); 
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	if( s_tem < 0 )		/* 负温度 */
		f_tem = (~s_tem+1) * 0.0625;	
	else
		f_tem = (s_tem * 0.625);
	  
	return f_tem; 	
}



