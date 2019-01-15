//==================================================================================
//| �ļ����� | �¶ȿ���
//|----------|----------------------------------------------------------------------
//| �ļ����� | 
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#ifndef __MOD_TEMPERATURE_H__
#define __MOD_TEMPERATURE_H__

#include "mod_include.h"

typedef struct __Temperature {
    const FP32* pf_Volt;            /* ��ϵ�ѹ���� */
    const FP32* pf_Temperature;     /* ����¶���   */
    INT16U  uch_SampleDots;         /* ��ϲ������� */
    FP32    af_K[5];                /* ��ϲ���ϵ�� */
    INT8U   uch_Order;              /* ��Ͻ���     */
    FP32    f_Temperature;          /* �¶� �ɲ���  */
    AdcChannel_t e_Channel;		    /* ͨ�� 	  */
}Temper_t;

extern Temper_t st_LaserTemper;
extern Temper_t st_PcbTemper;

extern FP32 Mod_CalTemper(Temper_t* pst_Temper,FP32 f_Volt);
extern FP32 Mod_GetTemper(Temper_t* pst_Temper);
extern BOOL Mod_TemperInit(Temper_t* pst_Temper);

#endif
