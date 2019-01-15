//==================================================================================
//| �ļ����� | �������Ŵ���
//|----------|----------------------------------------------------------------------
//| �ļ����� | 
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#ifndef __MOD_DLIA_H__
#define __MOD_DLIA_H__

#include "mod_include.h"

typedef struct __SoftLia {
    FP32    f_PsdFreq;               /* ������Ƶ�� KHZ       */
    FP32    f_PsdPhase;              /* ��������λ �Ƕ�      */
    FP32    f_SampleFreq;            /* ����Ƶ�� KHZ         */
    INT16U  uin_SampleMaxDots;       /* ������ */
    
    INT16U  uin_SampleLen;           /* ���������� */
    FP64*   plf_SampleBuff;          /* �����㻺���� */
    INT16U  uin_ResultLen;           /* ������� */
    FP64*   plf_ResultBuff;          /* ��������� */
    
    FP64*   plf_CalBuff;             /* ���㻺���� */
    FP64* 	plf_PsdBuff;             /* ���������� */
}DLia_t;

extern DLia_t st_DLia;

BOOL Mod_DLiaInit(DLia_t* pst_DLia);

BOOL  Mod_DLiaCal(DLia_t* pst_DLia,FP64* lf_ResBuff, INT16U* uin_ResLen);

BOOL Mod_DLiaSetPhase(DLia_t* pst_DLia,FP32 f_Phase,BOOL b_Init);

#endif
