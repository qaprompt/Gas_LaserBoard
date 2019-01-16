//==================================================================================
//| �ļ����� | mod_tec.c    
//|----------|----------------------------------------------------------------------
//| �ļ����� | TEC����
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#include "mod_tec.h"

Tec_t st_LaserTEC = {
    25.0,               /* �����¶� */
    1.25,               /* �¿ص�ѹ */
    25.0,               /* ������ʵ���¶� */
    &st_LaserTemper,    /* �¶Ⱦ�� */
    FALSE,              /* ����״̬ */
    Bsp_Tec1Enable,     /* TEC�������� */
};

//==================================================================================
//| �������� | Mod_TecSetVolt
//|----------|----------------------------------------------------------------------
//| �������� | ����TEC�¿ص�ѹ 
//|----------|----------------------------------------------------------------------
//| ������� | pst_Tec:���   f_CtrlVolt:�¶ȿ��Ƶ�ѹ
//|----------|----------------------------------------------------------------------
//| ���ز��� | BOOL:�ɹ� TRUE ʧ�� FALSE
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Mod_TecSetVolt(Tec_t* pst_Tec, FP32 f_CtrlVolt)
{
    if(pst_Tec == NULL || pst_Tec->pst_Temper == NULL)
        return FALSE;
    
    if(f_CtrlVolt >= DEF_TECVOLT_MIN && f_CtrlVolt <= DEF_TECVOLT_MAX)
    {
        pst_Tec->f_SetCtrlVolt = f_CtrlVolt;
        pst_Tec->f_SetTemper = Mod_CalTemper(pst_Tec->pst_Temper,pst_Tec->f_SetCtrlVolt);

        if(SaveToEeprom((INT32U)&pst_Tec->f_SetCtrlVolt) != TRUE)
            return FALSE;

        Bsp_Printf("    >>TEC�¿ص�ѹ����Ϊ:%.4fV(%.4f��)\r\n",pst_Tec->f_SetCtrlVolt,pst_Tec->f_SetTemper);
        Bsp_AD5663Set(eAD5563_CHB, Bsp_AD5663CHBVoltToHex(pst_Tec->f_SetCtrlVolt));
        return TRUE;
    }
    else
        return FALSE;
}

//==================================================================================
//| �������� | Mod_TecEnable
//|----------|----------------------------------------------------------------------
//| �������� | ����TEC 
//|----------|----------------------------------------------------------------------
//| ������� | pst_Tec:���   uin_TimeOut:��ʱʱ�䵥λS 0:���ȴ� -1:һֱ�ȴ�
//|----------|----------------------------------------------------------------------
//| ���ز��� | BOOL:ָ��ʱ�䵽���趨�¶ȷ���TRUE û�е��ﷵ��FALSE
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Mod_TecEnable(Tec_t* pst_Tec, INT16S uin_TimeOut)
{
    INT16U  i = 0;
    Bsp_Printf("\r\n===========================TEC����==========================\r\n");
    Bsp_Printf("    >>����TEC�¿ص�ѹ\r\n");
    Mod_TecSetVolt(pst_Tec,pst_Tec->f_SetCtrlVolt);
    Bsp_Printf("    >>����TEC\r\n");
    pst_Tec->cb_TecOps(eTecEnable);
    
    if(uin_TimeOut == -1)
    {
        Bsp_Printf("    >>TEC�ȴ������趨�¶�\r\n");
        while(1)
        {
            Bsp_DelayMs(1000);
            pst_Tec->f_FbTemper = Mod_GetTemper(pst_Tec->pst_Temper);
            Bsp_Printf("    >>��%u��TEC�¶�:%.4f\r\n",i,pst_Tec->f_FbTemper);
            if(abs(pst_Tec->f_FbTemper - pst_Tec->f_SetTemper) <= 1.0)
            {
                Bsp_Printf("    >>TEC�����趨�¶�\r\n");
                return TRUE;
            }
        }
    }
    else
    {
        Bsp_Printf("    >>TEC�ȴ������趨�¶�\r\n");
        for(i =0; i < uin_TimeOut; i++)
        {
            Bsp_DelayMs(1000);
            pst_Tec->f_FbTemper = Mod_GetTemper(pst_Tec->pst_Temper);
            Bsp_Printf("    >>��%u��TEC�¶�:%.4f\r\n",i,pst_Tec->f_FbTemper);
            /* �����趨�¶� */
            if(abs(pst_Tec->f_FbTemper - pst_Tec->f_SetTemper) <= 1.0)
            {
                Bsp_Printf("    >>TEC�����趨�¶�\r\n");
                return TRUE;
            }
        }
        Bsp_Printf("    >>TEC�ȴ��¶ȳ�ʱ\r\n");        
    }

    return FALSE;
}