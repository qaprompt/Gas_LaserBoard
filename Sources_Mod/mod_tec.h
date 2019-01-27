//==================================================================================
//| �ļ����� | mod_tec.h
//|----------|----------------------------------------------------------------------
//| �ļ����� | 
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#ifndef __MOD_TEC_H__
#define __MOD_TEC_H__


#define   DEF_TECVOLT_MAX   (2.0)
#define   DEF_TECVOLT_MIN   (0.5)


typedef struct {
    FP32        f_SetTemper;    /* �����¶� */
    FP32        f_SetCtrlVolt;  /* �¿ص�ѹ */
    FP32        f_FbTemper;     /* ������ʵ���¶� */
    Temper_t*   pst_Temper;     /* �¶Ⱦ�� */
    BOOL        b_Enable;       /* ����״̬ */   
    void (*cb_TecOps)(TecStatus_t); /* TEC�������� */
}Tec_t;

extern Tec_t st_LaserTEC;

BOOL Mod_TecSetVolt(Tec_t* pst_Tec, FP32 f_CtrlVolt,BOOL b_WriteEPROM);
BOOL Mod_TecEnable(Tec_t* pst_Tec, INT16S uin_TimeOut);

#endif
