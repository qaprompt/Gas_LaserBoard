//==================================================================================
//| �ļ����� | Mod_Gain.c    
//|----------|----------------------------------------------------------------------
//| �ļ����� | TEC����
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#include "App_Include.h"

Gain_t st_Gain = {
    1,
    1,
};

BOOL Mod_GainInit(Gain_t* pst_Gain)
{
    if (Mod_GainSetAcGain(pst_Gain,pst_Gain->in_AcGain,FALSE) == FALSE)
        Mod_GainSetAcGain(pst_Gain,1,TRUE);
    return TRUE;
}

//==================================================================================
//| �������� | Mod_GainSetAcGain
//|----------|----------------------------------------------------------------------
//| �������� | ����TEC�¿ص�ѹ 
//|----------|----------------------------------------------------------------------
//| ������� | pst_Gain:���   in_Gain:�����Ŵ���  b_WriteEPROM:�Ƿ�洢EPROM
//|----------|----------------------------------------------------------------------
//| ���ز��� | BOOL:�ɹ� TRUE ʧ�� FALSE
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Mod_GainSetAcGain(Gain_t* pst_Gain, INT16S in_Gain, BOOL b_WriteEPROM)
{
    switch(in_Gain)
    {
    case 1:
        Bsp_Pga2A0(0);
        Bsp_Pga2A1(0);
        pst_Gain->in_AcGain = 1;
        break;
    case 2:
        Bsp_Pga2A0(1);
        Bsp_Pga2A1(0); 
        pst_Gain->in_AcGain = 2;
        break;
    case 4:
        Bsp_Pga2A0(0);
        Bsp_Pga2A1(1); 
        pst_Gain->in_AcGain = 4;
        break;
    case 8:
        Bsp_Pga2A0(1);
        Bsp_Pga2A1(1); 
        pst_Gain->in_AcGain = 8;
        break;
    default:
        return FALSE;
    }
    
    if(b_WriteEPROM == TRUE)
        SaveToEeprom((INT32U)(&pst_Gain->in_AcGain));

    return TRUE;
}

BOOL Mod_GainSetDcGain(Gain_t* pst_Gain, INT16S in_Gain,BOOL b_WriteEPROM)
{
    
    return TRUE;
}

