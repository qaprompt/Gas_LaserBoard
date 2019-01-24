//==================================================================================
//| �ļ����� | ˫�����л�
//|----------|----------------------------------------------------------------------
//| �ļ����� | 
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================

#include "App_Include.h"



void Mod_DoubleBuffInit(DoubleBuff_t* pst_DoubleBuff, void * vp_Buff0, void *vp_Buff1, INT16U uin_BuffLen)
{
    pst_DoubleBuff->b_SwitchFlag = FALSE;
    pst_DoubleBuff->uin_BuffLen = uin_BuffLen;
    pst_DoubleBuff->pv_UseBuff = vp_Buff0;
    pst_DoubleBuff->pv_IdleBuff = vp_Buff1;
}

/* �л������� */
void Mod_SwitchBuff(DoubleBuff_t* pst_DoubleBuff)
{
    void * temp = pst_DoubleBuff->pv_UseBuff;

    pst_DoubleBuff->pv_UseBuff =  pst_DoubleBuff->pv_IdleBuff;
    pst_DoubleBuff->pv_IdleBuff = (void*)temp;
    
    if(pst_DoubleBuff->b_SwitchFlag == FALSE)
        pst_DoubleBuff->b_SwitchFlag = TRUE;
    else
        pst_DoubleBuff->b_SwitchFlag = FALSE;
}
