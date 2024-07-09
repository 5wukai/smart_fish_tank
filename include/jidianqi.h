#ifndef __JIDIANQI_H__
#define __JIDIANQI_H__

#define E53_IA1_guo_GPIO 3
#define E53_IA1_chou_GPIO 4
#define E53_IA1_zhu_GPIO 5
#define E53_IA1_jia_GPIO 6
#define E53_IA1_kai_GPIO 9

#include "E53_IA1.h"

void jidianqiIoInit();
void guoStatusSet(E53IA1Status status);
void chouStatusSet(E53IA1Status status);
void zhuStatusSet(E53IA1Status status);
void jiaStatusSet(E53IA1Status status);
void kaiStatusSet(E53IA1Status status);


#endif