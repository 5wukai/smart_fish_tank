#include <stdio.h>
#include <unistd.h>

#include "cmsis_os2.h"
#include "ohos_init.h"
#include <stdlib.h>
#include <hi_adc.h>

#define d 2.7

#define p 90.9

float WaterSensorTask(void)
{
	float height;
	unsigned int ret;
	unsigned short data;
		ret = hi_adc_read(HI_ADC_CHANNEL_0, &data, HI_ADC_EQU_MODEL_8,HI_ADC_CUR_BAIS_3P3V,0xff);
		if (ret != HI_ERR_SUCCESS)
		{
			printf("ADC1 Read Fail\n");
		}
		height = ((float)data*3300000/4096/1000-90)/200+10;

		
	return height;
}
