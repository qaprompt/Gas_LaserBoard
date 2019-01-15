#ifndef __BSP_TIMER_H__
#define	 __BSP_TIMER_H__

#include "Bsp.h"

#ifdef __cplusplus
extern "C" {
#endif

//��ʱ��0��ʼ��
void Bsp_Time0Init(float timeUs);
//��ʱ��0��ʼ
void Bsp_Time0Start(void);
//��ʱ��0����
void Bsp_Time0Stop(void);
//��ʱ��0�����ж�
void Bsp_Time0IntEnable(void);
//��ʱ��0�ر��ж�
void Bsp_Time0IntDisable(void);
//��ʱ��0�ص�����ע��
void Bsp_Time0HookRegister(void (*hook)(void));

//��ʱ��1��ʼ��
void Bsp_Time1Init(float timeUs);
//��ʱ��1��ʼ
void Bsp_Time1Start(void);
//��ʱ��1����
void Bsp_Time1Stop(void);
//��ʱ��1�����ж�
void Bsp_Time1IntEnable(void);
//��ʱ��1�ر��ж�
void Bsp_Time1IntDisable(void);
//��ʱ��1�ص�����ע��
void Bsp_Time1HookRegister(void (*hook)(void));


#ifdef __cplusplus
} /* extern "C" */
#endif  /* __cplusplus */

#endif
