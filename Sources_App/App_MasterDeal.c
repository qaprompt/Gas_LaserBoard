#include "App_Include.h"

#define DEF_MASTERDEAL_DBG_EN           FALSE

#if (DEF_MASTERDEAL_DBG_EN == TRUE)
    #define MASTERDEAL_DBG(...)        do {                            \
                                            TRACE_DBG(__VA_ARGS__);    \
                                        }while(0)
#else
    #define MASTERDEAL_DBG(...)
#endif



typedef enum
{
    CMD_R_CONNECT = 0x00,


    CMD_RW_IR_SET_MODE = 0x10,                  //���ú��⹤��ģʽ
    CMD_RW_IR_SET_MEASURE_MODE = 0x12,          //���ú������ģʽ

    //�����������
    CMD_RW_IR_SINVPP = 0x20,
    CMD_RW_IR_SINFREQ,
    CMD_RW_IR_TRGVPP,
    CMD_RW_IR_SAMPLEFREQ,
    CMD_RW_IR_DCVOLT,
    CMD_RW_IR_SINPHASE,
    CMD_RW_IR_TECVOLAT,
    CMD_RW_IR_SCANAVG,
    CMD_RW_IR_TRANSCOEFF,

    CMD_RW_SYS_LASER_TEMP = 0x2a,
    CMD_RW_SYS_PCB_TEMP = 0x2c,
    CMD_RW_IR_ACGAIN,
    CMD_RW_IR_DCGAIN,



    //��ȡ�������
    CMD_R_IR_PROC_SPECTRUM = 0x3B,      //AC/DC���շ�
    CMD_R_IR_ZERO_SPECTRUM,             //���� ���շ�
    CMD_R_IR_GALIBGAS_SPECTRUM,         //�궨�������շ�
    CMD_R_IR_DCWAVE,
    CMD_R_IR_ACWAVE = 0x40,
    CMD_R_IR_RAW_SPECTRUM,              //ԭʼ���շ�
    CMD_R_IR_BKG_SPECTRUM,              //���� ���շ�
    CMD_R_IR_DIFF_SPECTRUM,             //��� ���շ�

    CMD_R_IR_STATE = 0x80,              //��ȡ����״̬

    //�ۺϲ������
    CMD_RW_MEAS_DEAD_TIME   = 0xA0,     //��������ʱ��
    CMD_RW_MEAS_MEAS_TIME,              //���ò���ʱ��
    CMD_RW_MEAS_INVALID_DOTS,           //������Ч����
    CMD_RW_MEAS_ACTIVE_DOTS,            //������Ч����
    CMD_R_MEAS_SAMPLEDOT_CO2,           //��ȡCO2������
    CMD_R_MEAS_SAMPLEDOT_CO,            //��ȡCO������

    //�����������
    CMD_R_SPE_STATE = 0xD0,
    CMD_R_SPE_SERIALNUM,
    CMD_R_SPE_WLCCOEFF,
    CMD_R_SPE_NLCCOEFF,
    CMD_R_SPE_NLCORDER,
    CMD_R_SPE_PIXELS,
    CMD_RW_SPE_INTERGRALTIME,
    CMD_RW_SPE_EDC,
    CMD_RW_SPE_NLC,
    CMD_RW_SPE_SCANAVG,
    CMD_RW_SPE_BOXCAR,
    CMD_R_SPE_SPECTRUM,

    //����ӵ�����
    CMD_RW_IR_RISEDOTS = 0xF0,
    CMD_RW_IR_HIGHDOTS,
    CMD_RW_IR_FALLDOTS,
    CMD_RW_IR_LOWDOTS,


}eLasterBoardCmd;


typedef union {

    INT16U auin_Buff[10000];
    FP32   af_Buff[5000];
}ComTemp_t;


#ifdef __cplusplus
#pragma DATA_SECTION("Exsram")
#else
#pragma DATA_SECTION(un_Temp,"Exsram");
#endif
ComTemp_t un_Temp;

BOOL App_StdbusMasterDealFram(StdbusFram_t* pst_Fram)
{
    INT16U i;
    BOOL res = FALSE;
    switch(pst_Fram->uch_Cmd)
    {
#if TRUE //ϵͳ�������
//==================================================================================
//                            ������ û���κ�����ȷ���Ƿ�����
//==================================================================================
    case CMD_R_CONNECT:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            if(pst_Fram->uin_PayLoadLenth ==0)
                res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���յ�������\r\n");
        }
        break;
//==================================================================================
//                                  ��ȡ�������¶�
//==================================================================================
    case CMD_RW_SYS_LASER_TEMP:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],st_LaserTEC.f_FbTemper,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                  ��ȡpcb�¶�
//==================================================================================
    case CMD_RW_SYS_PCB_TEMP:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            FP32 f_temp = Mod_GetTemper(&st_PcbTemper);

            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],f_temp,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;
#endif

#if FALSE //�������
//==================================================================================
//                            ��ȡ������״̬
//==================================================================================
    case CMD_R_SPE_STATE:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = (INT8U)st_Usb4000.e_State;
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��ȡ����������״̬\r\n");
        }
        break;
//==================================================================================
//                            ��ȡ���������к�
//==================================================================================
    case CMD_R_SPE_SERIALNUM:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = strlen((const char*)st_Usb4000.auc_SerialNumber);
            memcpy(&pst_Fram->puc_PayLoad[0],st_Usb4000.auc_SerialNumber,pst_Fram->uin_PayLoadLenth);
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��ȡ���������к� = %s\r\n", st_Usb4000.auc_SerialNumber);
        }
        break;
//==================================================================================
//                            ��ȡ�����ǲ����������
//==================================================================================
    case CMD_R_SPE_WLCCOEFF:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = 4*4;

            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0], st_Usb4000.af_WlcCoeff[0], FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[4], st_Usb4000.af_WlcCoeff[1], FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[8], st_Usb4000.af_WlcCoeff[2], FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[12], st_Usb4000.af_WlcCoeff[3], FALSE);
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��ȡ�����ǲ����������\r\n");
            for( i = 0; i < 4 ;i++)
                MASTERDEAL_DBG(">>MASTERDEAL_DBG: �������%d = %e\r\n", i, st_Usb4000.af_WlcCoeff[i]);
        }
        break;
//==================================================================================
//                            ��ȡ�����Ƿ����Խ�������
//==================================================================================
    case CMD_R_SPE_NLCCOEFF:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = 8*4;

            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0], st_Usb4000.af_NlcCoeff[0], FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[4], st_Usb4000.af_NlcCoeff[1], FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[8], st_Usb4000.af_NlcCoeff[2], FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[12], st_Usb4000.af_NlcCoeff[3], FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[16], st_Usb4000.af_NlcCoeff[4], FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[20], st_Usb4000.af_NlcCoeff[5], FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[24], st_Usb4000.af_NlcCoeff[6], FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[28], st_Usb4000.af_NlcCoeff[7], FALSE);

            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��ȡ�����Ƿ����Խ�������\r\n");
            for( i = 0; i < 8 ;i++)
                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��������%d = %e\r\n", i, st_Usb4000.af_NlcCoeff[i]);
        }
        break;
//==================================================================================
//                            ��ȡ�����Ƿ����Խ�������
//==================================================================================
    case CMD_R_SPE_NLCORDER:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = st_Usb4000.uch_NlcOrder;
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��ȡ��������Ͻ��� = %d\r\n",st_Usb4000.uch_NlcOrder);
        }
        break;
//==================================================================================
//                            ��ȡ����������
//==================================================================================
    case CMD_R_SPE_PIXELS:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = 2;
            Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_Usb4000.uin_Pixels,FALSE);
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��ȡ���������� = %d\\r\n",st_Usb4000.uin_Pixels);
        }
//==================================================================================
//                            ����/��ȡ�����ǻ���ʱ��
//==================================================================================
    case CMD_RW_SPE_INTERGRALTIME:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvINT32UToArr(&pst_Fram->puc_PayLoad[0],st_Usb4000.ul_IntegralTime,FALSE);
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��ȡ�����ǻ���ʱ�� = %d\r\n",st_Usb4000.ul_IntegralTime);
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            //д����
            if(pst_Fram->uin_PayLoadLenth == 4)
                st_Usb4000.ul_IntegralTime = Bsp_CnvArrToINT32U(&pst_Fram->puc_PayLoad[0],FALSE);
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ù����ǻ���ʱ��  = %d\r\n",st_Usb4000.ul_IntegralTime);
        }
        break;
//==================================================================================
//                            ����/��ȡ�����ǰ���������
//==================================================================================
    case CMD_RW_SPE_EDC:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = st_Usb4000.b_EdcEnable;
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��ȡ�����ǰ��������� = %d\r\n",st_Usb4000.b_EdcEnable);
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            //д����
            if(pst_Fram->uin_PayLoadLenth == 1)
                st_Usb4000.b_EdcEnable = pst_Fram->puc_PayLoad[0];
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ù����ǰ���������  = %d\r\n",st_Usb4000.b_EdcEnable);
        }
        break;
//==================================================================================
//                            ����/��ȡ�����Ƿ���������
//==================================================================================
    case CMD_RW_SPE_NLC:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = st_Usb4000.b_EdcEnable;
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��ȡ�����Ƿ��������� = %d\r\n",st_Usb4000.b_NlcEnable);
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            //д����
            if(pst_Fram->uin_PayLoadLenth == 1)
                st_Usb4000.b_EdcEnable = pst_Fram->puc_PayLoad[0];
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ù����Ƿ���������  = %d\r\n",st_Usb4000.b_NlcEnable);
        }
        break;
//==================================================================================
//                            ����/��ȡ������ɨ��ƽ������
//==================================================================================
    case CMD_RW_SPE_SCANAVG:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = st_Usb4000.uch_ScansToAverage;
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��ȡ������ɨ��ƽ������ = %d\r\n",st_Usb4000.uch_ScansToAverage);
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            //д����
            if(pst_Fram->uin_PayLoadLenth == 1)
                st_Usb4000.uch_ScansToAverage = pst_Fram->puc_PayLoad[0];
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ù�����ɨ��ƽ������  = %d\r\n",st_Usb4000.uch_ScansToAverage);
        }
        break;
//==================================================================================
//                            ����/��ȡ�����ǻ����˲�
//==================================================================================
    case CMD_RW_SPE_BOXCAR:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = st_Usb4000.uch_Boxcar;
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ��ȡ�����ǻ����˲� = %d\r\n",st_Usb4000.uch_Boxcar);
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            //д����
            if(pst_Fram->uin_PayLoadLenth == 1)
                st_Usb4000.uch_Boxcar = pst_Fram->puc_PayLoad[0];
            res = TRUE;    //Ӧ��

            MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ù�����ɨ�����˲�  = %d\r\n",st_Usb4000.uch_Boxcar);
        }
        break;
//==================================================================================
//                            ��ȡ�����ǹ���(ԭʼ����)
//==================================================================================
    case CMD_R_SPE_SPECTRUM:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                //���ع��׵��ڴ�
                for(i = 0; i < st_Usb4000.uin_Pixels; i++)
                    un_Temp.auin_Buff[i] = (INT16U)st_Usb4000.af_ProcessSpectrum[i];

                //��ȡ��һҳ�������鳤��
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0], st_Usb4000.uin_Pixels, FALSE);
                pst_Fram->uin_PayLoadLenth = 2;
                res = TRUE;    //Ӧ��

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ع��׵��ڴ�\r\n");
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                //��һ�����ֽ���ReadAddress �ڶ������ֽ���ReadLenth
                INT16U uin_Offset = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0], FALSE);
                INT16U uin_Lenth = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[2], FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 2;
                for(i = 0; i<uin_Lenth;i++)
                {
                    Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[i*2+4],un_Temp.auin_Buff[uin_Offset+i],FALSE);
                }
                res = TRUE;    //Ӧ��
            }
        }
        break;
#endif

#if TRUE //�������
//==================================================================================
//                                  ��ȡ��ǰ״̬
//==================================================================================
    case CMD_R_IR_STATE:
        //��ȡ��һҳ�������鳤��
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->puc_PayLoad[0] = st_GasMeasForIr.e_State;
            Bsp_CnvINT32UToArr(&pst_Fram->puc_PayLoad[1],rand(),FALSE);                                //������� ��ʱ��һ�������
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[5],st_Trans.f_Transmission,FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[9],st_GasMeasForIr.pst_Gas1->f_R,FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[13],st_GasMeasForIr.pst_Gas1->f_Con,FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[17],st_GasMeasForIr.pst_Gas2->f_R,FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[21],st_GasMeasForIr.pst_Gas2->f_Con,FALSE);

            pst_Fram->uin_PayLoadLenth = 25;
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                  ���ù���ģʽ
//==================================================================================
    case CMD_RW_IR_SET_MODE:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            switch(pst_Fram->puc_PayLoad[0])
            {
            case eGasAdjZero:
                if(pst_Fram->uin_PayLoadLenth == 3)
                {
                    Mod_GasMeasDoAdjZero(&st_GasMeasForIr,Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[1],FALSE));
                    res = TRUE;    //Ӧ��
                }
                break;
            case eGasCalibGas1:
            case eGasCalibGas2:
            case eGasCalibGasAll:
                if(pst_Fram->uin_PayLoadLenth == 11)
                {
                    Mod_GasMeasDoCalib(&st_GasMeasForIr,
                                       pst_Fram->puc_PayLoad[0],
                                       Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[1],FALSE),
                                       Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[3],FALSE),
                                       Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[7],FALSE));
                    res = TRUE;    //Ӧ��
                }
                break;
            case eGasAbsMeasure:
                if(pst_Fram->uin_PayLoadLenth == 1)
                {
                    if(st_GasMeasForIr.b_DiffMeasrue != FALSE)
                    {
                        st_GasMeasForIr.b_DiffMeasrue = FALSE;
                        res = (BOOL)SaveToEeprom((INT32U)&st_GasMeasForIr.b_DiffMeasrue);
                    }
                    else
                        res = TRUE;

                    Mod_GasMeasDoAbsMeasure(&st_GasMeasForIr);
                }
                break;
            case eGasDiffBackground:
                if(pst_Fram->uin_PayLoadLenth == 1)
                {
                    if(st_GasMeasForIr.b_DiffMeasrue != TRUE)
                    {
                        st_GasMeasForIr.b_DiffMeasrue = TRUE;
                        res = (BOOL)SaveToEeprom((INT32U)&st_GasMeasForIr.b_DiffMeasrue);
                    }
                    else
                        res = TRUE;

                    Mod_GasMeasDoDiffBackground(&st_GasMeasForIr);
                }
                break;
            case eGasDiffMeasure:
                if(pst_Fram->uin_PayLoadLenth == 1)
                {
                    if(st_GasMeasForIr.b_DiffMeasrue != TRUE)
                    {
                        st_GasMeasForIr.b_DiffMeasrue = TRUE;
                        res = (BOOL)SaveToEeprom((INT32U)&st_GasMeasForIr.b_DiffMeasrue);
                    }
                    else
                        res = TRUE;

                    Mod_GasMeasDoDiffMeasure(&st_GasMeasForIr);
                }
                break;
            default:
                break;

            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],st_ModWave.f_SinVpp,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                  ���ò�������ģʽ
//==================================================================================
    case CMD_RW_IR_SET_MEASURE_MODE:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                if(pst_Fram->puc_PayLoad[0] != FALSE)
                    Mod_MeasureDoStaticMeasure(&st_Measure);
                else
                    Mod_MeasureDoDynamicMeasure(&st_Measure);
                res = TRUE;
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = st_Measure.b_IsStaticMeasure;
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                  �������Ҳ���ֵ
//==================================================================================
    case CMD_RW_IR_SINVPP:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 4)
            {
                FP32 f_Temp = Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[0],FALSE);

                if (Mod_SetSinVpp(&st_ModWave,f_Temp,TRUE) == TRUE)
                {
                    res = TRUE;    //Ӧ��
                }
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],st_ModWave.f_SinVpp,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                  �������Ҳ�Ƶ��
//==================================================================================
    case CMD_RW_IR_SINFREQ:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 4)
            {
                FP32 f_Temp = Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[0],FALSE);

                if (Mod_SetSinFreq(&st_ModWave,f_Temp,TRUE) == TRUE)
                {
                    st_DLia.f_PsdFreq = st_ModWave.f_SinFreq * 2;       /* �Ŵ����Ҳ��Ķ���г��   */
                    res = TRUE;    //Ӧ��
                }
            }

        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],st_ModWave.f_SinFreq,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                  �������ǲ���ֵ
//==================================================================================
    case CMD_RW_IR_TRGVPP:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 4)
            {
                FP32 f_Temp = Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[0],FALSE);

                if (Mod_SetTrgVpp(&st_ModWave,f_Temp,TRUE) == TRUE)
                {
                    res = TRUE;    //Ӧ��
                }
            }

        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],st_ModWave.f_TrgVpp,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                  ���ò���Ƶ��
//==================================================================================
    case CMD_RW_IR_SAMPLEFREQ:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 4)
            {
                FP32 f_Temp = Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[0],FALSE);

                if (Mod_SetSampleFreq(&st_ModWave,f_Temp,TRUE) == TRUE)
                {
                    st_DLia.f_SampleFreq = st_ModWave.f_SampleFreq;    /* ����Ƶ��    */
                    res = TRUE;    //Ӧ��
                }
            }

        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],st_ModWave.f_SampleFreq,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                  ����ֱ��ƫ��
//==================================================================================
    case CMD_RW_IR_DCVOLT:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 4)
            {
                FP32 f_Temp = Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[0],FALSE);

                if (Mod_SetDcOffset(&st_ModWave,f_Temp,TRUE) == TRUE)
                {
                    res = TRUE;    //Ӧ��
                }
            }

        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],st_ModWave.f_DcOffset,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;

//==================================================================================
//                                  �������Ҳ���λ
//==================================================================================
    case CMD_RW_IR_SINPHASE:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 4)
            {
                FP32 f_Temp = Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[0],FALSE);

                if (Mod_DLiaSetPhase(&st_DLia,f_Temp,TRUE) == TRUE)
                {
                    res = TRUE;    //Ӧ��
                }
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],st_DLia.f_PsdPhase,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;

//==================================================================================
//                                  ����TEC��ѹ
//==================================================================================
    case CMD_RW_IR_TECVOLAT:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 4)
            {
                FP32 f_Temp = Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[0],FALSE);
                if(Mod_TecSetVolt(&st_LaserTEC, f_Temp,TRUE) == TRUE)
                {
                    res = TRUE;    //Ӧ��
                }
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],st_LaserTEC.f_SetCtrlVolt,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;

//==================================================================================
//                                  ����ɨ��ƽ������
//==================================================================================
    case CMD_RW_IR_SCANAVG:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 2)
            {
                st_IrSpectrum.uch_ScanAvg = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0],FALSE);

                res = SaveToEeprom((INT32U)&st_IrSpectrum.uch_ScanAvg);
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 2;
            Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_IrSpectrum.uch_ScanAvg,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;

//==================================================================================
//                              ����͸���ʼ���ϵ��
//==================================================================================
    case CMD_RW_IR_TRANSCOEFF:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 4)
            {
                st_Trans.f_TransK = Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[0],FALSE);

                res = SaveToEeprom((INT32U)&st_Trans.f_TransK);
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 4;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],st_Trans.f_TransK ,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;

//==================================================================================
//                              ���õ��Ʋ������ص���
//==================================================================================
    case CMD_RW_IR_RISEDOTS:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 2)
            {
                INT16U uin_Temp = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0],FALSE);
                if(Mod_SetRiseDots(&st_ModWave, uin_Temp,TRUE) == TRUE)
                {
                    res = TRUE;    //Ӧ��
                }
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 2;
            Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_ModWave.uin_RiseDot,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;

//==================================================================================
//                              ���õ��Ʋ��ߵ�ƽ����
//==================================================================================
    case CMD_RW_IR_HIGHDOTS:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 2)
            {
                INT16U uin_Temp = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0],FALSE);
                if(Mod_SetHighDots(&st_ModWave, uin_Temp,TRUE) == TRUE)
                {
                    res = TRUE;    //Ӧ��
                }
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 2;
            Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_ModWave.uin_HigtDot,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;

//==================================================================================
//                              ���õ��Ʋ��½��ص���
//==================================================================================
    case CMD_RW_IR_FALLDOTS:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 2)
            {
                INT16U uin_Temp = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0],FALSE);
                if(Mod_SetFallDots(&st_ModWave, uin_Temp,TRUE) == TRUE)
                {
                    res = TRUE;    //Ӧ��
                }
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 2;
            Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_ModWave.uin_FallDot,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                              ���õ��Ʋ��½��ص���
//==================================================================================
    case CMD_RW_IR_LOWDOTS:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 2)
            {
                INT16U uin_Temp = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0],FALSE);
                if(Mod_SetLowDots(&st_ModWave, uin_Temp,TRUE) == TRUE)
                {
                    res = TRUE;    //Ӧ��
                }
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 2;
            Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_ModWave.uin_LowDot,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;

//==================================================================================
//                              ���ý����Ŵ���
//==================================================================================
    case CMD_RW_IR_ACGAIN:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                res = Mod_GainSetAcGain(&st_Gain,pst_Fram->puc_PayLoad[0],TRUE);
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = st_Gain.in_AcGain & 0x00ff;
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                              ����ֱ���Ŵ���
//==================================================================================
    case CMD_RW_IR_DCGAIN:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                res = Mod_GainSetDcGain(&st_Gain,pst_Fram->puc_PayLoad[0],TRUE);
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = st_Gain.in_DcGain & 0x00ff;
            res = TRUE;    //Ӧ��
        }
        break;
#endif







#if TRUE //��ȡ�������
//==================================================================================
//                                   ��ȡ��������������
//==================================================================================
    case CMD_R_IR_ACWAVE:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
             //��һ���ֽ���PageIndex  �ڶ������ֽ���ReadAddress ��������ֽ���ReadLenth
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                //��ȡ��һҳ�������鳤��
                pst_Fram->uin_PayLoadLenth = 2;
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_ModWave.uin_SampleDot,FALSE);
                /* ���ع��׵� ������ ȷ�������ٴ���һ���� ���¹���*/
                Bsp_IntDis();
                for(i = 0; i < st_ModWave.uin_SampleDot; i++)
                {
                    un_Temp.auin_Buff[i] = st_ModWave.puin_RecvBuff[i];//aui_TestSenseRecvBuff[i];//
                }
                Bsp_IntEn();

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ش������������ε������� %d����\r\n",i);
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                uint16_t i = 0;
                uint16_t uin_Offset = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad,FALSE);
                uint16_t uin_Lenth = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad + 2,FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 2;
                for(i = 0; i<uin_Lenth;i++)
                {
                    INT16U j = un_Temp.auin_Buff[uin_Offset + i];

                    Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[i * 2 + 4],j,FALSE);
                }

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ͻ��������� Offset = %d ���� = %d \r\n",uin_Offset,i);
            }
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                   ��ȡԭʼ���շ岨��
//==================================================================================
    case CMD_R_IR_RAW_SPECTRUM:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
             //��һ���ֽ���PageIndex  �ڶ������ֽ���ReadAddress ��������ֽ���ReadLenth
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                //��ȡ��һҳ�������鳤��
                pst_Fram->uin_PayLoadLenth = 2;
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_IrSpectrum.uin_SpectrumLen,FALSE);
                /* ���ع��׵� ������ ȷ�������ٴ���һ���� ���¹���*/
                Bsp_IntDis();
                for(i = 0; i < st_IrSpectrum.uin_SpectrumLen; i++)
                {
                    un_Temp.af_Buff[i] = st_IrSpectrum.af_ProceSpectrum[i];//st_ModWave.puin_RecvBuff[i];
                }
                Bsp_IntEn();

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ����ԭʼ���շ岨�ε������� %d����\r\n",i);
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                uint16_t i = 0;
                uint16_t uin_Offset = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad,FALSE);
                uint16_t uin_Lenth = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad + 2,FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 4;
                for(i = 0; i<uin_Lenth;i++)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[i * 4 + 4],un_Temp.af_Buff[uin_Offset + i],FALSE);
                }

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ͻ��������� Offset = %d ���� = %d \r\n",uin_Offset,i);
            }
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                   ��ȡ��������շ岨��
//==================================================================================
    case CMD_R_IR_PROC_SPECTRUM:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
             //��һ���ֽ���PageIndex  �ڶ������ֽ���ReadAddress ��������ֽ���ReadLenth
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                //��ȡ��һҳ�������鳤��
                pst_Fram->uin_PayLoadLenth = 2;
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_IrSpectrum.uin_SpectrumLen,FALSE);
                /* ���ع��׵� ������ ȷ�������ٴ���һ���� ���¹���*/
                Bsp_IntDis();
                for(i = 0; i < st_IrSpectrum.uin_SpectrumLen; i++)
                {
                    un_Temp.af_Buff[i] = st_IrSpectrum.af_OriginalSpectrum[i];//st_ModWave.puin_RecvBuff[i];
                }
                Bsp_IntEn();

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ش�������շ岨�ε������� %d����\r\n",i);
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                uint16_t i = 0;
                uint16_t uin_Offset = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad,FALSE);
                uint16_t uin_Lenth = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad + 2,FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 4;
                for(i = 0; i<uin_Lenth;i++)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[i * 4 + 4],un_Temp.af_Buff[uin_Offset + i],FALSE);
                }

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ͻ��������� Offset = %d ���� = %d \r\n",uin_Offset,i);
            }
            res = TRUE;    //Ӧ��
        }
        break;

//==================================================================================
//                                   ��ȡ�������շ岨��
//==================================================================================
    case CMD_R_IR_ZERO_SPECTRUM:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
             //��һ���ֽ���PageIndex  �ڶ������ֽ���ReadAddress ��������ֽ���ReadLenth
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                //��ȡ��һҳ�������鳤��
                pst_Fram->uin_PayLoadLenth = 2;
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_GasMeasForIr.uin_SpectrumLen,FALSE);
                /* ���ع��׵� ������ ȷ�������ٴ���һ���� ���¹���*/
                Bsp_IntDis();
                for(i = 0; i < st_GasMeasForIr.uin_SpectrumLen; i++)
                {
                    un_Temp.af_Buff[i] = st_GasMeasForIr.af_ZeroSpectrum[i];//st_ModWave.puin_RecvBuff[i];
                }
                Bsp_IntEn();

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ص������շ岨�ε������� %d����\r\n",i);
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                uint16_t i = 0;
                uint16_t uin_Offset = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad,FALSE);
                uint16_t uin_Lenth = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad + 2,FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 4;
                for(i = 0; i<uin_Lenth;i++)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[i * 4 + 4],un_Temp.af_Buff[uin_Offset + i],FALSE);
                }

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ͻ��������� Offset = %d ���� = %d \r\n",uin_Offset,i);
            }
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                   ��ȡ�궨���շ岨��
//==================================================================================
    case CMD_R_IR_GALIBGAS_SPECTRUM:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
             //��һ���ֽ���PageIndex  �ڶ������ֽ���ReadAddress ��������ֽ���ReadLenth
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                //��ȡ��һҳ�������鳤��
                pst_Fram->uin_PayLoadLenth = 2;
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_GasMeasForIr.uin_SpectrumLen,FALSE);
                /* ���ع��׵� ������ ȷ�������ٴ���һ���� ���¹���*/
                Bsp_IntDis();
                for(i = 0; i < st_GasMeasForIr.uin_SpectrumLen; i++)
                {
                    un_Temp.af_Buff[i] = st_GasMeasForIr.af_CalibSpectrum[i];//st_ModWave.puin_RecvBuff[i];
                }
                Bsp_IntEn();

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ر궨���շ岨�ε������� %d����\r\n",i);
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                uint16_t i = 0;
                uint16_t uin_Offset = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad,FALSE);
                uint16_t uin_Lenth = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad + 2,FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 4;
                for(i = 0; i<uin_Lenth;i++)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[i * 4 + 4],un_Temp.af_Buff[uin_Offset + i],FALSE);
                }

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ͻ��������� Offset = %d ���� = %d \r\n",uin_Offset,i);
            }
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                   ��ȡ�������շ岨��
//==================================================================================
    case CMD_R_IR_BKG_SPECTRUM:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
             //��һ���ֽ���PageIndex  �ڶ������ֽ���ReadAddress ��������ֽ���ReadLenth
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                //��ȡ��һҳ�������鳤��
                pst_Fram->uin_PayLoadLenth = 2;
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_GasMeasForIr.uin_SpectrumLen,FALSE);
                /* ���ع��׵� ������ ȷ�������ٴ���һ���� ���¹���*/
                Bsp_IntDis();
                for(i = 0; i < st_GasMeasForIr.uin_SpectrumLen; i++)
                {
                    un_Temp.af_Buff[i] = st_GasMeasForIr.af_BkgSpectrum[i];//st_ModWave.puin_RecvBuff[i];
                }
                Bsp_IntEn();

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ر������շ岨�ε������� %d����\r\n",i);
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                uint16_t i = 0;
                uint16_t uin_Offset = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad,FALSE);
                uint16_t uin_Lenth = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad + 2,FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 4;
                for(i = 0; i<uin_Lenth;i++)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[i * 4 + 4],un_Temp.af_Buff[uin_Offset + i],FALSE);
                }

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ͻ��������� Offset = %d ���� = %d \r\n",uin_Offset,i);
            }
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                   ��ȡ������շ岨��
//==================================================================================
    case CMD_R_IR_DIFF_SPECTRUM:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
             //��һ���ֽ���PageIndex  �ڶ������ֽ���ReadAddress ��������ֽ���ReadLenth
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                //��ȡ��һҳ�������鳤��
                pst_Fram->uin_PayLoadLenth = 2;
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_GasMeasForIr.uin_SpectrumLen,FALSE);
                /* ���ع��׵� ������ ȷ�������ٴ���һ���� ���¹���*/
                Bsp_IntDis();
                for(i = 0; i < st_GasMeasForIr.uin_SpectrumLen; i++)
                {
                    un_Temp.af_Buff[i] = st_GasMeasForIr.af_DiffSpectrum[i];//st_ModWave.puin_RecvBuff[i];
                }
                Bsp_IntEn();

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ز�����շ岨�ε������� %d����\r\n",i);
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                uint16_t i = 0;
                uint16_t uin_Offset = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad,FALSE);
                uint16_t uin_Lenth = Bsp_CnvArrToINT16U(pst_Fram->puc_PayLoad + 2,FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 4;
                for(i = 0; i<uin_Lenth;i++)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[i * 4 + 4],un_Temp.af_Buff[uin_Offset + i],FALSE);
                }

                MASTERDEAL_DBG(">>MASTERDEAL_DBG: ���ͻ��������� Offset = %d ���� = %d \r\n",uin_Offset,i);
            }
            res = TRUE;    //Ӧ��
        }
        break;
#endif
//==================================================================================
//                                   ��������ʱ��
//==================================================================================
    case CMD_RW_MEAS_DEAD_TIME:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 4)
            {
                st_Measure.ul_DeadTime = Bsp_CnvArrToINT32U(&pst_Fram->puc_PayLoad[0],FALSE);
                SaveToEeprom((INT32U)(&st_Measure.ul_DeadTime));
                res = TRUE;     //Ӧ��
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                Bsp_CnvINT32UToArr(&pst_Fram->puc_PayLoad[0],st_Measure.ul_DeadTime,FALSE);
                pst_Fram->uin_PayLoadLenth = 4;
                res = TRUE;     //Ӧ��
            }
        }
        break; 
//==================================================================================
//                                   ���ò���ʱ��
//==================================================================================  
    case CMD_RW_MEAS_MEAS_TIME:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 4)
            {
                st_Measure.ul_MesureTime = Bsp_CnvArrToINT32U(&pst_Fram->puc_PayLoad[0],FALSE);
                SaveToEeprom((INT32U)(&st_Measure.ul_MesureTime));
                res = TRUE;     //Ӧ��
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                Bsp_CnvINT32UToArr(&pst_Fram->puc_PayLoad[0],st_Measure.ul_MesureTime,FALSE);
                pst_Fram->uin_PayLoadLenth = 4;
                res = TRUE;     //Ӧ��
            }
        }
        break;  
//==================================================================================
//                                   ������Ч����N1
//==================================================================================
	case CMD_RW_MEAS_INVALID_DOTS:
		if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
		{
			if(pst_Fram->uin_PayLoadLenth == 2)
			{
				st_Measure.uin_InvalidDots = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0],FALSE);
                SaveToEeprom((INT32U)(&st_Measure.uin_InvalidDots));
				res = TRUE;     //Ӧ��
			}
		}
		else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
		{
			if(pst_Fram->uin_PayLoadLenth == 0)
			{
				Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_Measure.uin_InvalidDots,FALSE);
				pst_Fram->uin_PayLoadLenth = 2;
				res = TRUE;     //Ӧ��
			}
		}
		break;
//==================================================================================
//                                   ������Ч����N2
//==================================================================================
	case CMD_RW_MEAS_ACTIVE_DOTS:
		if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
		{
			if(pst_Fram->uin_PayLoadLenth == 2)
			{
				st_Measure.uin_ActiveDots = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0],FALSE);
                SaveToEeprom((INT32U)(&st_Measure.uin_ActiveDots));
				res = TRUE;     //Ӧ��
			}
		}
		else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
		{
			if(pst_Fram->uin_PayLoadLenth == 0)
			{
				Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_Measure.uin_ActiveDots,FALSE);
				pst_Fram->uin_PayLoadLenth = 2;
				res = TRUE;     //Ӧ��
			}
		}
		break;
        
//==================================================================================
//                                  ��ȡCO2������
//==================================================================================
	case CMD_R_MEAS_SAMPLEDOT_CO2:
		if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
		{
			if(pst_Fram->uin_PayLoadLenth == 0)
			{
				//��ȡ��һҳ�������鳤��
				int i = 0;

				Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_Measure.st_SampleCO2.ul_Len,FALSE);

				for(i = 0; i < st_Measure.st_SampleCO2.ul_Len; i++)
				{
					Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[2+i*4],st_Measure.st_SampleCO2.af_Buff[i],FALSE);
				}

				pst_Fram->uin_PayLoadLenth = 2 + i * 4;

				res = 1;    //Ӧ��
			}
		}
		break;
//==================================================================================
//                                  ��ȡCO������
//==================================================================================
	case CMD_R_MEAS_SAMPLEDOT_CO:
		if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
		{
			if(pst_Fram->uin_PayLoadLenth == 0)
			{
				//��ȡ��һҳ�������鳤��
				int i = 0;

				Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_Measure.st_SampleCO.ul_Len,FALSE);

				for(i = 0; i < st_Measure.st_SampleCO.ul_Len; i++)
				{
					Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[2+i*4],st_Measure.st_SampleCO.af_Buff[i],FALSE);
				}

				pst_Fram->uin_PayLoadLenth = 2 + i * 4;

				res = 1;    //Ӧ��
			}
		}
		break;


    default:
        break;
    }
	return res;
}
