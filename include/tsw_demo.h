#ifndef __TSW_DEMO_H
#define	__TSW_DEMO_H


// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC输入通道（引脚）配置**************************/
#define    tsw_ADC                       HI_ADC_CHANNEL_6



float GetTSW_30(void);


#endif /* __TSW_DEMO_H */
