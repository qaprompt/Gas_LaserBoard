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


typedef struct __SoftLia {
    FP32    f_PsdFreq;               /* ������Ƶ�� KHZ       */
    FP32    f_PsdPhase;              /* ��������λ �Ƕ�      */
    FP32    f_SampleFreq;            /* ����Ƶ�� KHZ         */
    INT16U  uin_SampleMaxDots;       /* ������ */
    
    FP32*   pf_Buff;                 /* ���㻺���� */
}DLia_t;

extern DLia_t st_DLia;
extern const INT16U aui_TestSenseRecvBuff[10000];

BOOL Mod_DLiaInit(DLia_t* pst_DLia);

BOOL Mod_DLiaCal(DLia_t* pst_DLia,INT16S* puin_InData, INT16U uin_InDataLen,FP32* pf_OutData,INT16U* puin_OutDataLen);

BOOL Mod_DLiaSetPhase(DLia_t* pst_DLia,FP32 f_Phase);

#endif
