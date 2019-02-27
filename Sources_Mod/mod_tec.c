//==================================================================================
//| �ļ����� | mod_tec.c    
//|----------|----------------------------------------------------------------------
//| �ļ����� | TEC����
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#include "App_Include.h"

Tec_t st_LaserTEC = {
    34.5,               /* �����¶� */
    0.986,              /* �¿ص�ѹ */
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
BOOL Mod_TecSetVolt(Tec_t* pst_Tec, FP32 f_CtrlVolt,BOOL b_WriteEPROM)
{
    if(pst_Tec == NULL || pst_Tec->pst_Temper == NULL)
        return FALSE;
    
    if(f_CtrlVolt >= DEF_TECVOLT_MIN && f_CtrlVolt <= DEF_TECVOLT_MAX)
    {
        pst_Tec->f_SetCtrlVolt = f_CtrlVolt;
        pst_Tec->f_SetTemper = Mod_CalTemper(pst_Tec->pst_Temper,pst_Tec->f_SetCtrlVolt);

        if(b_WriteEPROM == TRUE)
            if(SaveToEeprom((INT32U)&pst_Tec->f_SetCtrlVolt) != TRUE)
                return FALSE;

        TRACE_DBG("    >>TEC�¿ص�ѹ����Ϊ:%.4fV(%.4f��)\r\n",pst_Tec->f_SetCtrlVolt,pst_Tec->f_SetTemper);
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
    INT16U  uin_SuccessCnt = 0;
    INT16U  i = 0;
    TRACE_DBG("\r\n===========================TEC����==========================\r\n");
    TRACE_DBG("    >>����TEC�¿ص�ѹ\r\n");
    Mod_TecSetVolt(pst_Tec,pst_Tec->f_SetCtrlVolt,FALSE);
    TRACE_DBG("    >>����TEC\r\n");
    pst_Tec->cb_TecOps(eTecEnable);
    
    if(uin_TimeOut == -1)
    {
        TRACE_DBG("    >>TEC�ȴ������趨�¶�\r\n");
        while(1)
        {
            Bsp_DelayMs(1000);
            pst_Tec->f_FbTemper = Mod_GetTemper(pst_Tec->pst_Temper);
            TRACE_DBG("    >>��%02u��TEC�¶�:%.4f\r\n",i,pst_Tec->f_FbTemper);
            if(fabs(pst_Tec->f_FbTemper - pst_Tec->f_SetTemper) <= 1.0)
            {
                if(++uin_SuccessCnt >= 5 )
                {
                    TRACE_DBG("    >>TEC�����趨�¶�\r\n");
                    return TRUE;
                }
                return TRUE;
            }
            else
            {

                uin_SuccessCnt = 0;
            }
        }
    }
    else
    {
        TRACE_DBG("    >>TEC�ȴ������趨�¶�\r\n");
        for(i = 1; i <= uin_TimeOut; i++)
        {
            Bsp_DelayMs(1000);
            pst_Tec->f_FbTemper = Mod_GetTemper(pst_Tec->pst_Temper);
            TRACE_DBG("    >>��%02u��TEC�¶�:%.4f\r\n",i,pst_Tec->f_FbTemper);
            /* �����趨�¶� */
            if(fabs(pst_Tec->f_FbTemper - pst_Tec->f_SetTemper) <= 1.0)
            {
                if(++uin_SuccessCnt >= 5 )
                {
                    TRACE_DBG("    >>TEC�����趨�¶�\r\n");
                    return TRUE;
                }
            }
            else
            {

                uin_SuccessCnt = 0;
            }
        }
        TRACE_DBG("    >>TEC�ȴ��¶ȳ�ʱ\r\n");
    }

    return FALSE;
}
