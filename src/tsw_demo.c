
#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio.h"
#include "iot_errno.h"
#include "hi_pwm.h"
#include "hi_io.h"
#include "hi_time.h"
#include "ds18b20.h"
#include "tsw_demo.h"
#include "hi_adc.h"


float GetTSW_30(void)
{
    unsigned int ret1;
    unsigned short data1;
    float TU=0.0;
    float TU_value=0.0;
    float TU_calibration=0.0;
    float temp_data=26;
    float K_Value=3047.19;

    //u8 DS18B20_Init(void);

    //temp_data = DS18B20_Get_Temp();

   
    ret1 = hi_adc_read(tsw_ADC, &data1, HI_ADC_EQU_MODEL_8, HI_ADC_CUR_BAIS_3P3V, 0xff);
    if (ret1 != HI_ERR_SUCCESS)
    {
        printf("ADC1 Read Fail\n");
    }
    TU =(float) data1/4096*3.3; // 读取转换的AD
  
	
		TU_calibration=-0.0192*(temp_data/10-25)+TU;  
	  TU_value=-865.68*TU_calibration + K_Value-1500;
	
		if(TU_value<=0){TU_value=0;}
		if(TU_value>=3000){TU_value=3000;}
    

    
    

    return TU_value;
    
    
}
