#include "App_Include.h"

#define DEF_MASTERDEAL_DBG_EN           TRUE

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

    //�����������
    CMD_RW_IR_SINVPP = 0x20,
    CMD_RW_IR_SINFREQ,
    CMD_RW_IR_TRGVPP,
    CMD_RW_IR_SAMPLEFREQ,
    CMD_RW_IR_DCVOLT,
    CMD_RW_IR_SINPHASE,
    CMD_RW_IR_TECVOLAT = 0x26,

    CMD_RW_SYS_LASER_TEMP = 0x2a,
    CMD_RW_SYS_PCB_TEMP = 0x2c,

    //�����������
    CMD_R_SPE_STATE = 0x40,
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

    //��ȡ�������
    CMD_R_IR_ACWAVE = 0xC0,
    CMD_R_IR_DCWAVE,
    CMD_R_IR_RAW_SPECTRUM,      //ԭʼ���շ�
    CMD_R_IR_PROC_SPECTRUM,     //AC/DC���շ�
    CMD_R_IR_ZERO_SPECTRUM,     //���� ���շ�
    CMD_R_IR_GALIBGAS1_SPECTRUM,//�궨����1 ���շ�
    CMD_R_IR_GALIBGAS2_SPECTRUM,//�궨����2 ���շ�
    CMD_R_IR_BKG_SPECTRUM,      //���� ���շ�
    CMD_R_IR_DIFF_SPECTRUM,     //��� ���շ�
}eLasterBoardCmd;


typedef union {

    INT16U auin_Buff[10000];
    FP32   af_Buff[5000];
}ComTemp_t;


#ifdef __cplusplus
#pragma DATA_SECTION("Exsram")
#else
//#pragma DATA_SECTION(un_Temp,"Exsram");
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
            pst_Fram->uin_PayLoadLenth = 0;
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

#if TRUE //�������
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

                if (Mod_DLiaSetPhase(&st_DLia,f_Temp) == TRUE)
                {
                    res = TRUE;    //Ӧ��
                }
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 4;
            //Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],st_DLia.f_PsdPhase,FALSE);
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
                if(Mod_TecSetVolt(&st_LaserTEC, f_Temp) == TRUE)
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
#if 0
//==================================================================================
//                                  ���ò���ƽ������
//==================================================================================
    case 0x27:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 2)
            {
                INT16U uin_DataTemp;
                uin_DataTemp = ((INT32U)pst_Fram->puc_PayLoad[1]<<8) + ((INT32U)pst_Fram->puc_PayLoad[0]);

                if ((uin_DataTemp>=1)&&(uin_DataTemp<=9999))
                {
                    uin_SampleWaveTotalNum = uin_DataTemp;
                    str_Sample.uin_WaveNum = 0;
                    s_WriteOneIntToEeprom(uin_DataTemp,0xc8);
                    uch_ThrowWaveEn = 1;//���ڶ����εĹ��ܿ���  by guxiaohua
                    uin_100usCount = 0;
                    uin_1sCount = 0;
                    s_ClrGlobalArray();  //s_DoubleGas_ClrGasConcenStruct();
                    sprintf(buf,"Ũ�ȼ���ƽ�������ѱ�����Ϊ: %u\r\n",uin_SampleWaveTotalNum);
                    TRACE_DBG(buf);
                }

                res = TRUE;    //Ӧ��
            }

        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //�������Ƿ����Ƿ��ڵ���
            pst_Fram->uin_PayLoadLenth = 2;

            INT16U j = uin_SampleWaveTotalNum;

            pst_Fram->puc_PayLoad[1] = (INT8U)(j>>8);
            pst_Fram->puc_PayLoad[0] = (INT8U)(j&0xff);

            res = TRUE;    //Ӧ��
        }
        break;
#endif
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
                    un_Temp.auin_Buff[i] = i;//st_ModWave.puin_RecvBuff[i];
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
#endif

    default:
        break;
    }

#if 0
    switch(pst_Fram->uch_Cmd)
    {
//==================================================================================
//                                ��ȡ������״̬ ����orδ����
//==================================================================================
    case 0x10:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //������
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = USB4000.b_IsConnect;
            res = TRUE;    //Ӧ��
        }
        break;

//==================================================================================
//                                ���ù����ǻ���ʱ��
//==================================================================================
    case 0x11:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 4)
            {
                INT32U  i;

                TRACE_DBG(">>DBG>>      ���ù����ǻ���ʱ��\n\r");

                i = Bsp_CnvArrToINT32U(&pst_Fram->puc_PayLoad[0],FALSE);

                if( i > 65000000)
                    i = 65000000;

                USB4000.b_SetFlag = TRUE;
                USB4000.ul_SetIntegralTime = i;
                SaveToEeprom((INT32U)&USB4000.ul_SetIntegralTime);
                res = TRUE;    //Ӧ��
            }

        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //�������Ƿ����Ƿ��ڵ���
            pst_Fram->uin_PayLoadLenth = 4;

            Bsp_CnvINT32UToArr(&pst_Fram->puc_PayLoad[0],USB4000.ul_SetIntegralTime,FALSE);
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                              ���ù��������ƽ������
//==================================================================================
    case 0x12:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                USB4000.uch_ScansToAverage = pst_Fram->puc_PayLoad[0];
                SaveToEeprom((INT32U)&USB4000.uch_ScansToAverage);
                res = TRUE;    //Ӧ��
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //�������Ƿ����Ƿ��ڵ���
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = USB4000.uch_ScansToAverage;
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                              ���ù����ǻ����˲�����
//==================================================================================
    case 0x13:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                USB4000.uch_Boxcar = pst_Fram->puc_PayLoad[0];
                SaveToEeprom((INT32U)&USB4000.uch_Boxcar);
                res = TRUE;    //Ӧ��
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //�������Ƿ����Ƿ��ڵ���
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = USB4000.uch_Boxcar;
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                              ���ù������Ƿ���EDC(����������)
//==================================================================================
    case 0x14:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                USB4000.b_EdcEnable = pst_Fram->puc_PayLoad[0];
                SaveToEeprom((INT32U)&USB4000.b_EdcEnable);
                res = TRUE;    //Ӧ��
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //�������Ƿ����Ƿ��ڵ���
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = USB4000.b_EdcEnable;
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                              ���ù������Ƿ���NLC(�����Բ���)
//==================================================================================
    case 0x15:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                USB4000.b_NlcEnable = pst_Fram->puc_PayLoad[0];
                SaveToEeprom((INT32U)&USB4000.b_NlcEnable);
                res = TRUE;    //Ӧ��
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //�������Ƿ����Ƿ��ڵ���
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = USB4000.b_NlcEnable;
            res = TRUE;    //Ӧ��
        }
        break;

//==================================================================================
//                            �л���̬��̬����ģʽ
//==================================================================================
	case 0x18:
		if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
		{

		}
		else if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
				if(pst_Fram->puc_PayLoad[0] == 0)
				{
					Mod_MeasureDoStaticMeasure(&st_Measure);
				}
				else
				{
					Mod_MeasureDoDynamicMeasure(&st_Measure);
				}
				res = TRUE;    //Ӧ��
            }
        }

		break;

//==================================================================================
//                          �޸�һ���궨��/��ȡһ���궨��
//==================================================================================
    case 0x22:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            //д�������޸�һ���궨��   byte0 byte0 ������ byte1�������� byte2-byte9 double ����
            if(pst_Fram->uin_PayLoadLenth == 11)
            {
                CalibPoint_t point;
                point.b_Use = pst_Fram->puc_PayLoad[2];
                point.f_X = Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[3],FALSE);
                point.f_Y = Bsp_CnvArrToFP32(&pst_Fram->puc_PayLoad[7],FALSE);
                if( pst_Fram->puc_PayLoad[0] == 0 )
                    Mod_CalibPointListEditOnePoint(&st_CPList_GasNO,pst_Fram->puc_PayLoad[1],&point);
                res = TRUE;    //Ӧ��
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //�������Ƕ�ȡһ���궨��
            //������        ���ر궨������
            //����һ������  ����ָ�������ı궨�������
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                //��ȡ��һҳ�������鳤��
                if( pst_Fram->puc_PayLoad[0] == 0 )
                {
                    pst_Fram->puc_PayLoad[1] = DEF_CALIBPOINT_MAX;
                    pst_Fram->uin_PayLoadLenth = 2;
                    res = TRUE;    //Ӧ��
                }
 
            }
            else if(pst_Fram->uin_PayLoadLenth == 2)
            {
                CalibPoint_t point;
                if( pst_Fram->puc_PayLoad[0] == 0 )
                {   
                    Mod_CalibPointListReadOnePoint(&st_CPList_GasNO,pst_Fram->puc_PayLoad[1],&point);
                    pst_Fram->puc_PayLoad[2] = point.b_Use;
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[3],point.f_X,FALSE);
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[7],point.f_Y,FALSE);                
                    pst_Fram->uin_PayLoadLenth = 11;        
                    res = TRUE;    //Ӧ��
                }
            }

        }
        break;

//==================================================================================
//                                ���ý���/��ȡ����
//==================================================================================
    case 0x23:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 2)
            {
                if ( pst_Fram->puc_PayLoad[1] > 3)
                   res = FALSE;

                if( pst_Fram->puc_PayLoad[0] == 0 )
                {
                    st_GasMeasure.pst_Gas1->uch_NiheOrder = pst_Fram->puc_PayLoad[1];
                    SaveToEeprom((INT32U)(&st_GasMeasure.pst_Gas1->uch_NiheOrder));
                    pst_Fram->uin_PayLoadLenth = 2;
                    res = TRUE;    //Ӧ��
                }
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                if( pst_Fram->puc_PayLoad[0] == 0 )
                {
                    pst_Fram->puc_PayLoad[1] = st_GasMeasure.pst_Gas1->uch_NiheOrder;
                    pst_Fram->uin_PayLoadLenth = 2;
                    res = TRUE;    //Ӧ��
                }
            }
        }

        break;

//==================================================================================
//                                  ������������
//==================================================================================
    case 0x24:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            //д�����ǽ�����������
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                Mod_GasMarkWorkLine(&st_GasMeasure,pst_Fram->puc_PayLoad[0]);
                res = TRUE;            //Ӧ�� ���޸�����ԭʼ���ݷ���
            }
        }
        break;
//==================================================================================
//                          ���ù�������ϵ��/��ȡ��������ϵ��
//==================================================================================
    case 0x25:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            //д�����ǽ�����������
            if(pst_Fram->uin_PayLoadLenth == 0)
            {

            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //�������Ƕ�ȡ���ϵ��
            //������������ ��һ������ѡ���������ϵ�� �ڶ���������ѡ��An
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                if(pst_Fram->puc_PayLoad[0] == 0)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[1],st_GasMeasure.pst_Gas1->af_NiheCoeff[0],FALSE);                
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[5],st_GasMeasure.pst_Gas1->af_NiheCoeff[1],FALSE);   
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[9],st_GasMeasure.pst_Gas1->af_NiheCoeff[2],FALSE);   
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[13],st_GasMeasure.pst_Gas1->af_NiheCoeff[3],FALSE);                
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[17],st_GasMeasure.pst_Gas1->af_NiheCoeff[4],FALSE);   
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[21],st_GasMeasure.pst_Gas1->af_NiheCoeff[5],FALSE);   
                    pst_Fram->uin_PayLoadLenth = 25;
                    res = TRUE;    //Ӧ��
                }
            }
        }
        break;

//==================================================================================
//                                   ��ȡ10·�̹��ѹ
//==================================================================================
    case 0x30:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                uint16_t i = 0;
                pst_Fram->uin_PayLoadLenth = 40;

                for(i = 0; i < 10; i++)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[i*4],st_Grey.pst_Channel[i].f_Volt,FALSE);
                }
            }
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                   ��ȡ10·�̹��ֵ�궨��ѹ
//==================================================================================
    case 0x31:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                uint16_t i = 0;
                pst_Fram->uin_PayLoadLenth = 40;

                for(i = 0; i < 10; i++)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[i*4],st_Grey.pst_Channel[i].f_AbsTransVolt,FALSE);
                }
            }
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                   ��ȡ10·�̹ⱳ����ѹ
//==================================================================================
    case 0x32:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                uint16_t i = 0;
                pst_Fram->uin_PayLoadLenth = 40;

                for(i = 0; i < 10; i++)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[i*4],st_Grey.pst_Channel[i].f_BkVolt,FALSE);
                }
            }
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                   ��ȡ10·�̹�͸����
//==================================================================================
    case 0x33:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                uint16_t i = 0;
                pst_Fram->uin_PayLoadLenth = 40;

                for(i = 0; i < 10; i++)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[i*4],st_Grey.pst_Channel[i].f_Trans,FALSE);
                }
            }
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                   ��ȡ10·�̹�Ҷ�
//==================================================================================
    case 0x34:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                uint16_t i = 0;
                pst_Fram->uin_PayLoadLenth = 40;

                for(i = 0; i < 10; i++)
                {
                    Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[i*4],st_Grey.pst_Channel[i].f_Grey,FALSE);
                }
            }
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                                   �����̹⹤��״̬
//==================================================================================
    case 0x3a:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = st_Grey.e_Status;
            res = TRUE;
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                switch(pst_Fram->puc_PayLoad[0])
                {
                case 0:
                    Mod_GreyGotoIdle(&st_Grey);
                    break;
                case 1:
                    Mod_GreyGotoMeas(&st_Grey);
                    break;
                case 2:
                    Mod_GreyGotoCalib(&st_Grey);
                    break;
                default:
                    return FALSE;
                }
            }
            res = TRUE;    //Ӧ��
        }
        break;
//==================================================================================
//                         ��ȡ�̹⹤��״̬/��͸����/�ܻҶ�
//==================================================================================
    case 0x3b:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 9;
            pst_Fram->puc_PayLoad[0] = st_Grey.e_Status;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[1],st_Grey.f_Trans,FALSE);
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[5],st_Grey.f_Grey,FALSE);
            res = TRUE;
        }
        break;
//==================================================================================
//                                   ��ȡ����
//==================================================================================
    case 0x40:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                INT16U i = 0;
                INT16U len = 0;
                OS_ERR os_err;

                /* ���ع��׵� ������ ȷ�������ٴ���һ���� ���¹��� */
                OSSchedLock(&os_err);
                for(i = st_GasMeasure.ul_UseLeftDot; i < st_GasMeasure.ul_UseRightDot; i++)
                    lf_Buff[len++] = st_GasMeasure.plf_Spectrum[i];
                OSSchedUnlock(&os_err);

                //��ȡ��һҳ�������鳤��
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0], len, FALSE);
                pst_Fram->uin_PayLoadLenth = 2;
                res = TRUE;    //Ӧ��
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                //��һ�����ֽ���ReadAddress �ڶ������ֽ���ReadLenth
                INT16U i = 0;
                INT16U uin_Offset = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0], FALSE);
                INT16U uin_Lenth = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[2], FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 8;
                for(i = 0; i<uin_Lenth;i++)
                {
                    Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[i*8+4],lf_Buff[uin_Offset+i],FALSE);
                }
                res = TRUE;    //Ӧ��
            }
        }
        break;

//==================================================================================
//                                  ��ȡ�궨����
//==================================================================================
    case 0x41:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                INT16U i = 0;
                INT16U len = 0;
                OS_ERR os_err;

                /* ���ع��׵� ������ ȷ�������ٴ���һ���� ���¹��� */
                OSSchedLock(&os_err);
                for(i = st_GasMeasure.ul_UseLeftDot; i < st_GasMeasure.ul_UseRightDot; i++)
                    lf_Buff[len++] = st_GasMeasure.plf_AbsSpectrum[i];
                OSSchedUnlock(&os_err);

                //��ȡ��һҳ�������鳤��
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0], len, FALSE);
                pst_Fram->uin_PayLoadLenth = 2;
                res = TRUE;    //Ӧ��
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                //��һ�����ֽ���ReadAddress �ڶ������ֽ���ReadLenth
                INT16U i = 0;
                INT16U uin_Offset = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0], FALSE);
                INT16U uin_Lenth = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[2], FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 8;
                for(i = 0; i<uin_Lenth;i++)
                {
                    Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[i*8+4],lf_Buff[uin_Offset+i],FALSE);
                }
                res = TRUE;    //Ӧ��
            }
        }
        break;

//==================================================================================
//                                  ��ȡ��������
//==================================================================================
    case 0x42:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                INT16U i = 0;
                INT16U len = 0;
                OS_ERR os_err;

                /* ���ع��׵� ������ ȷ�������ٴ���һ���� ���¹��� */
                OSSchedLock(&os_err);
                for(i = st_GasMeasure.ul_UseLeftDot; i < st_GasMeasure.ul_UseRightDot; i++)
                    lf_Buff[len++] = st_GasMeasure.plf_BkgSpectrum[i];
                OSSchedUnlock(&os_err);

                //��ȡ��һҳ�������鳤��
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0], len, FALSE);
                pst_Fram->uin_PayLoadLenth = 2;
                res = TRUE;    //Ӧ��
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                //��һ�����ֽ���ReadAddress �ڶ������ֽ���ReadLenth
                INT16U i = 0;
                INT16U uin_Offset = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0], FALSE);
                INT16U uin_Lenth = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[2], FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 8;
                for(i = 0; i<uin_Lenth;i++)
                {
                    Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[i*8+4],lf_Buff[uin_Offset+i],FALSE);
                }
                res = TRUE;    //Ӧ��
            }
        }
        break;
//==================================================================================
//                                  ��ȡ��ֹ���
//==================================================================================
    case 0x43:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 0)
            {
                INT16U i = 0;
                INT16U len = 0;
                OS_ERR os_err;

                /* ���ع��׵� ������ ȷ�������ٴ���һ���� ���¹��� */
                OSSchedLock(&os_err);
                for(i = st_GasMeasure.ul_UseLeftDot; i < st_GasMeasure.ul_UseRightDot; i++)
                    lf_Buff[len++] = st_GasMeasure.plf_DiffSpectrum[i];
                OSSchedUnlock(&os_err);

                //��ȡ��һҳ�������鳤��
                Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0], len, FALSE);
                pst_Fram->uin_PayLoadLenth = 2;
                res = TRUE;    //Ӧ��
            }
            else if(pst_Fram->uin_PayLoadLenth == 4)
            {
                //��һ�����ֽ���ReadAddress �ڶ������ֽ���ReadLenth
                INT16U i = 0;
                INT16U uin_Offset = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[0], FALSE);
                INT16U uin_Lenth = Bsp_CnvArrToINT16U(&pst_Fram->puc_PayLoad[2], FALSE);

                pst_Fram->uin_PayLoadLenth = 4 + uin_Lenth * 8;
                for(i = 0; i<uin_Lenth;i++)
                {
                    Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[i*8+4],lf_Buff[uin_Offset+i],FALSE);
                }
                res = TRUE;    //Ӧ��
            }
        }
        break;
//==================================================================================
//                                  �л�����ģʽ
//==================================================================================
    case 0x4a:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            //byte0: 0:�л�������״̬
            //       1:�л����궨״̬
            //       2:�л�������״̬
            //       3:�л�����ֲ���״̬
            //byte1-5 float :�л����궨״̬��ʱ�·��ı궨Ũ��
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                switch(pst_Fram->puc_PayLoad[0])
                {
                case eGasAdjZero:
                    Mod_GasMeasureGotoAdjZero(&st_GasMeasure);           //�л�����0״̬
                    res = TRUE;    //Ӧ��
                    break;
                case eGasAbsMeasure:
                    Mod_GasMeasureGotoAbsMeasure(&st_GasMeasure);        //�л�������״̬
                    res = TRUE;    //Ӧ��
                    break;
                case eGasDiffMeasure:
                    Mod_GasMeasureGotoDiffMeasure(&st_GasMeasure);        //�л�������״̬
                    res = TRUE;    //Ӧ��
                    break;
                case eGasWait:
                    Mod_GasMeasureGotoWait(&st_GasMeasure);               //�л����ȴ�״̬
                    res = TRUE;    //Ӧ��
                    break;
                case eGasCalibTrans:
                    Mod_GasMeasureGotoCalibTrans(&st_GasMeasure);         //�л���͸���ʱ궨�������궨��        
                    res = TRUE;    //Ӧ��
                    break;
                default:
                    break;
                }
            }
            else if(pst_Fram->uin_PayLoadLenth == 17)
            {
                FP64 f1,f2;

                TRACE_DBG(">>DBG>>      ���յ��궨����\n\r");

                f1 = Bsp_CnvArrToFP64(&pst_Fram->puc_PayLoad[1],FALSE);
                f2 = Bsp_CnvArrToFP64(&pst_Fram->puc_PayLoad[9],FALSE);
                
                if(pst_Fram->puc_PayLoad[0] == eGasCalibGas1 || pst_Fram->puc_PayLoad[0] == eGasCalibGas2 ||
                   pst_Fram->puc_PayLoad[0] == eGasCalibAll)
                {
                     Mod_GasMeasureGotoCalib(&st_GasMeasure,
                                            ((GasMeasureState_e)pst_Fram->puc_PayLoad[0]),
                                            f1,f2);
                     res = TRUE;    //Ӧ��
                }

                if(pst_Fram->puc_PayLoad[0] == eGasCalibCorrectionGas1 || pst_Fram->puc_PayLoad[0] == eGasCalibCorrectionGas2 ||
                   pst_Fram->puc_PayLoad[0] == eGasCalibCorrectionGasAll)
                {
                     Mod_GasMeasureGotoCalibCorrection(&st_GasMeasure,
                                            ((GasMeasureState_e)pst_Fram->puc_PayLoad[0]),
                                            f1,f2);
                     res = TRUE;    //Ӧ��
                }

            }

        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            //�������Ƿ����Ƿ��ڵ���
            pst_Fram->uin_PayLoadLenth = 1;
            pst_Fram->puc_PayLoad[0] = st_GasMeasure.e_State;
            res = TRUE;    //Ӧ��
        }
        break;  
//==================================================================================
//                                  ��ȡ����״̬
//==================================================================================
    case 0x4b:
        if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            pst_Fram->uin_PayLoadLenth = 37;
            pst_Fram->puc_PayLoad[0] = st_GasMeasure.e_State;
            Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[1],st_GasMeasure.f_Trans,FALSE);
            if(st_GasMeasure.pst_Gas1 != NULL)
            {
                Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[5],st_GasMeasure.pst_Gas1->lf_PeakHight,FALSE);
                Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[13],st_GasMeasure.pst_Gas1->lf_Concentration,FALSE);
            }
            else
            {
                Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[5],0.0,FALSE);
                Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[13],0.0,FALSE);
            }
            if(st_GasMeasure.pst_Gas2 != NULL)
            {
                Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[21],st_GasMeasure.pst_Gas2->lf_PeakHight,FALSE);
                Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[29],st_GasMeasure.pst_Gas2->lf_Concentration,FALSE);
            }
            else
            {
                Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[21],0.0,FALSE);
                Bsp_CnvFP64ToArr(&pst_Fram->puc_PayLoad[29],0.0,FALSE);
            }
            res = TRUE;
        }
        break;      
//==================================================================================
//                                   �̵���IO����
//==================================================================================
    case 0x80:
        if(pst_Fram->uch_SubCmd == e_StdbusWriteCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 2)
            {
                BOOL b_State = (pst_Fram->puc_PayLoad[1] == FALSE) ? FALSE : TRUE ;
                Bsp_GpioWirte((GpioId_e)(e_IO_Relay0 + pst_Fram->puc_PayLoad[0]),b_State);
                res = TRUE;     //Ӧ��
            }
        }
        else if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
        {
            if(pst_Fram->uin_PayLoadLenth == 1)
            {
                pst_Fram->puc_PayLoad[1] = Bsp_GpioReadOut((GpioId_e)(e_IO_Relay0 + pst_Fram->puc_PayLoad[0]));
                pst_Fram->uin_PayLoadLenth = 2;
                res = TRUE;     //Ӧ��
            }
        }
        break;
//==================================================================================
//                                   ��������ʱ��
//==================================================================================
    case 0xA0:
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
    case 0xA1:
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
//                                  ��ȡNO������
//==================================================================================
	case 0xA2:
		if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
		{
			if(pst_Fram->uin_PayLoadLenth == 0)
			{
				//��ȡ��һҳ�������鳤��
				int i = 0;

				Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_Measure.st_SampleNO.ul_Len,FALSE);

				for(i = 0; i < st_Measure.st_SampleNO.ul_Len; i++)
				{
					Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[2+i*4],st_Measure.st_SampleNO.af_Buff[i],FALSE);
				}

				pst_Fram->uin_PayLoadLenth = 2 + i * 4;

				res = TRUE;    //Ӧ��
			}
		}
		break;
//==================================================================================
//                                  ��ȡHC������
//==================================================================================
	case 0xA3:
		if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
		{
			if(pst_Fram->uin_PayLoadLenth == 0)
			{
				//��ȡ��һҳ�������鳤��
				int i = 0;

				Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_Measure.st_SampleHC.ul_Len,FALSE);

				for(i = 0; i < st_Measure.st_SampleHC.ul_Len; i++)
				{
					Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[2+i*4],st_Measure.st_SampleHC.af_Buff[i],FALSE);
				}

				pst_Fram->uin_PayLoadLenth = 2 + i * 4;

				res = TRUE;    //Ӧ��
			}
		}
		break;

//==================================================================================
//                                   ������Ч����N1
//==================================================================================
	case 0xA4:
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
	case 0xA5:
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
//                                  ��ȡƽ����Ũ��
//==================================================================================
	case 0xA6:
		if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
		{
			if(pst_Fram->uin_PayLoadLenth ==0)
			{
				pst_Fram->uin_PayLoadLenth = 8;
				Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[0],(FP32)st_Measure.lf_NO,FALSE);
				Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[4],(FP32)st_Measure.lf_HC,FALSE);
				res = TRUE;    //Ӧ��
			}
		}
		break;
//==================================================================================
//                                  ��ȡ�̶Ȳ�����
//==================================================================================
	case 0xAA:
		if(pst_Fram->uch_SubCmd == e_StdbusReadCmd)
		{
			if(pst_Fram->uin_PayLoadLenth == 1)
			{
				//��ȡ��һҳ�������鳤��
				int i = 0;
                int index = pst_Fram->puc_PayLoad[0];
				Bsp_CnvINT16UToArr(&pst_Fram->puc_PayLoad[0],st_Measure.st_SampleGrey[index].ul_Len,FALSE);

				for(i = 0; i < st_Measure.st_SampleGrey[index].ul_Len; i++)
				{
					Bsp_CnvFP32ToArr(&pst_Fram->puc_PayLoad[2+i*4],st_Measure.st_SampleGrey[index].af_Buff[i],FALSE);
				}

				pst_Fram->uin_PayLoadLenth = 2 + i * 4;

				res = TRUE;    //Ӧ��
			}
		}
		break;     
        
    default:
        break;

    }
    
#endif
	return res;
}
