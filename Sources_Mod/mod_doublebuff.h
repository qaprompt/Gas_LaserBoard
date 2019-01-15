//==================================================================================
//| �ļ����� | ���ⷢ����մ���
//|----------|----------------------------------------------------------------------
//| �ļ����� | 
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#ifndef __MOD_DOUBLEBUFF_H__
#define __MOD_DOUBLEBUFF_H__

#include "mod_include.h"

typedef struct __DoubleBuff {
    BOOL    b_SwitchFlag;   /* ���ܻ������л���־  */
    INT16U  uin_BuffLen;        /* ���ܻ���������      */
    void* 	pv_UseBuff;      /* ���ܻ����� ƹ���л� */
    void* 	pv_IdleBuff;      /* �������� ƹ���л� */

}DoubleBuff_t;

extern void Mod_DoubleBuffInit(DoubleBuff_t* pst_DoubleBuff, void * vp_Buff0, void *vp_Buff1, INT16U uin_BuffLen);
extern void Mod_SwitchBuff(DoubleBuff_t* pst_DoubleBuff);

#endif
