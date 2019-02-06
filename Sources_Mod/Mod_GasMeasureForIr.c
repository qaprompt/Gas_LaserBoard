#include "App_Include.h"


#define DEF_GASMEASIR_DBG_EN           TRUE

#if (DEF_GASMEASIR_DBG_EN == TRUE)
    #define GASMEASIR_DBG(...)             do {                            \
                                            Bsp_Printf(__VA_ARGS__);    \
                                        }while(0)
#else
    #define GASMEASIR_DBG(...)
#endif

GasInfoForIr st_GasCO2 = {
    (INT8U*)"CO2",                          /* �������� */
    eGasCO2,                        /* ������ */
    0,                              /* ���׷�Χ */
    75,                             /* ���׷�Χ */

    0,                              /* �궨Ũ�� */

    0,                              /* ϵ��A */
    0,                              /* ϵ��B */
    0,                              /* ϵ��R */
    
    0,                              /* Ũ�� */
};

GasInfoForIr st_GasCO = {
    (INT8U*)"CO",                           /* �������� */
    eGasCO,                         /* ������ */
    75,                             /* ���׷�Χ */
    150,                            /* ���׷�Χ */

    0,                              /* �궨Ũ�� */

    0,                              /* ϵ��A */
    0,                              /* ϵ��B */
    0,                              /* ϵ��R */
    
    0,                              /* Ũ�� */
};

GasMeasForIr_t st_GasMeasForIr = {
    eGasDiffBackground,             /* ����״̬ */
    0,
    NULL,                           /* �������� */                         
    {0},                            /* ������� */
    {0},                            /* �������� */
    {0},                            /* ��ֹ��� */
    {0},                            /* У׼���� */
    
    0,
    0,
    0.5,                            /* ��������һ���˲�ϵ�� */
    TRUE,                           /* �Ƿ��ֲ��� */

    &st_GasCO2,                     /* ����1 */
    &st_GasCO,                      /* ����2 */
    
};

BOOL Mod_GasMeasInit(GasMeasForIr_t* pst_Meas)
{
    INT16U i = 0;
    if(pst_Meas->b_DiffMeasrue == TRUE)
        pst_Meas->e_State = eGasDiffBackground;
    else
        pst_Meas->e_State = eGasAbsMeasure;

    for(i = 0; i < pst_Meas->uin_SpectrumLen;i++)
    {
        pst_Meas->af_BkgSpectrum[i] = 0;
        pst_Meas->af_DiffSpectrum[i] = 0;
    }

    return TRUE;
}

BOOL Mod_GasMeasDoAdjZero(GasMeasForIr_t* pst_Meas,INT16U uin_Count)
{
    if(pst_Meas == NULL || pst_Meas->uin_ScanAvg != 0)
        return FALSE;
    pst_Meas->e_State = eGasAdjZero;
    pst_Meas->uin_ScanAvg = uin_Count;
    pst_Meas->uin_Cnt = 0;

    GASMEASIR_DBG(">>GASMEASIR_DB: �������ģʽ %d��ƽ��\r\n",pst_Meas->uin_ScanAvg);
    return TRUE;
}

BOOL Mod_GasMeasDoCalib(GasMeasForIr_t* pst_Meas,INT16U uin_Kind,INT16U uin_Count,FP32 f_CalibCon1,FP32 f_CalibCon2)
{
    if(pst_Meas == NULL || pst_Meas->uin_ScanAvg != 0)
        return FALSE;
    if(uin_Kind == 1)
    {
        pst_Meas->e_State = eGasCalibGas1;
        pst_Meas->uin_ScanAvg = uin_Count;
        pst_Meas->uin_Cnt = 0;
        pst_Meas->pst_Gas1->f_CalibCon = f_CalibCon1;
        GASMEASIR_DBG(">>GASMEASIR_DB: ����궨ģʽ �궨����1 %d��ƽ��\r\n",pst_Meas->uin_ScanAvg);
        return TRUE;
    }
    else if(uin_Kind == 2)
    {
        pst_Meas->e_State = eGasCalibGas2;
        pst_Meas->uin_ScanAvg = uin_Count;
        pst_Meas->uin_Cnt = 0;
        pst_Meas->pst_Gas2->f_CalibCon = f_CalibCon2;
        GASMEASIR_DBG(">>GASMEASIR_DB: ����궨ģʽ �궨����2 %d��ƽ��\r\n",pst_Meas->uin_ScanAvg);
        return TRUE;
    }
    else if(uin_Kind == 3)
    {
        pst_Meas->e_State = eGasCalibGasAll;
        pst_Meas->uin_ScanAvg = uin_Count;
        pst_Meas->uin_Cnt = 0;
        pst_Meas->pst_Gas1->f_CalibCon = f_CalibCon1;  
        pst_Meas->pst_Gas2->f_CalibCon = f_CalibCon2;  
        GASMEASIR_DBG(">>GASMEASIR_DB: ����궨ģʽ �궨�������� %d��ƽ��\r\n",pst_Meas->uin_ScanAvg);
        return TRUE;
    }
    return FALSE;
}

BOOL Mod_GasMeasDoAbsMeasure(GasMeasForIr_t* pst_Meas)
{
    if(pst_Meas->b_DiffMeasrue == FALSE)
    {
        pst_Meas->e_State = eGasAbsMeasure;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL Mod_GasMeasDoDiffMeasure(GasMeasForIr_t* pst_Meas)
{
    if(pst_Meas->b_DiffMeasrue == TRUE)
    {
        pst_Meas->e_State = eGasDiffMeasure;  
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL Mod_GasMeasDoDiffBackground(GasMeasForIr_t* pst_Meas)
{
    if(pst_Meas->b_DiffMeasrue == TRUE)
    {
        pst_Meas->e_State = eGasDiffBackground;  
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

///////////////////////////////////////////////////////////////////
//                          �Ǳ����
///////////////////////////////////////////////////////////////////
static void Mod_GasMeasAdjZero(GasMeasForIr_t* pst_Meas)
{
    INT16U  i;
    if(pst_Meas->uin_Cnt == 0 )
    {
        for( i = 0; i < pst_Meas->uin_SpectrumLen; i++)
        {
            pst_Meas->af_BkgSpectrum[i] = 0;
        }
    }

    for( i = 0; i < pst_Meas->uin_SpectrumLen; i++)
    {
        pst_Meas->af_BkgSpectrum[i] += pst_Meas->pf_ProcSpectrum[i];
    }
    
    if(++pst_Meas->uin_Cnt >= pst_Meas->uin_ScanAvg)
    {
        for( i = 0; i < pst_Meas->uin_SpectrumLen; i++)
        {
            pst_Meas->af_BkgSpectrum[i] /= pst_Meas->uin_ScanAvg;
            pst_Meas->af_ZeroSpectrum[i] = pst_Meas->af_BkgSpectrum[i];
        }
        pst_Meas->uin_ScanAvg = 0;
        
        SaveToEepromExt((INT32U)pst_Meas->af_ZeroSpectrum, 200);

        if(pst_Meas->b_DiffMeasrue == TRUE)
            pst_Meas->e_State = eGasDiffBackground;
        else
            pst_Meas->e_State = eGasAbsMeasure;


        GASMEASIR_DBG(">>GASMEASIR_DB: �������");
    }

}

///////////////////////////////////////////////////////////////////
//                          �Ǳ�궨
///////////////////////////////////////////////////////////////////

static void Mod_GasMeasCalib(GasMeasForIr_t* pst_Meas, GasInfoForIr* pst_Gas)
{
    INT16U  i;
    
    for( i = 0; i < pst_Meas->uin_SpectrumLen; i++)
    {
        pst_Meas->af_DiffSpectrum[i] = pst_Meas->pf_ProcSpectrum[i] - pst_Meas->af_ZeroSpectrum[i]; /* ���²�ֹ��� */
    }
    
    if(pst_Meas->uin_Cnt == 0 )
    {
        for( i = pst_Gas->uin_SpectrumRangeLeft; i < pst_Gas->uin_SpectrumRangeRight; i++)  /*��ն�Ӧ���εı�������*/
        {
            pst_Meas->af_BkgSpectrum[i] = 0;
        }
    }

    for( i = pst_Gas->uin_SpectrumRangeLeft; i < pst_Gas->uin_SpectrumRangeRight; i++)  /*�ۼƶ�Ӧ���εı�������*/
    {
        pst_Meas->af_BkgSpectrum[i] += pst_Meas->af_DiffSpectrum[i];
    }
    
    if(++pst_Meas->uin_Cnt >= pst_Meas->uin_ScanAvg )
    {
        for( i = pst_Gas->uin_SpectrumRangeLeft; i < pst_Gas->uin_SpectrumRangeRight; i++)  /*ƽ����Ӧ���εı�������*/
        {
            pst_Meas->af_BkgSpectrum[i] /= pst_Meas->uin_ScanAvg;
            pst_Meas->af_CalibSpectrum[i] = pst_Meas->af_BkgSpectrum[i];
        }

        SaveToEepromExt((INT32U)pst_Meas->af_CalibSpectrum, 200);

        pst_Meas->uin_ScanAvg = 0;
        if(pst_Meas->b_DiffMeasrue == TRUE)
            pst_Meas->e_State = eGasDiffBackground;
        else
            pst_Meas->e_State = eGasAbsMeasure;

        GASMEASIR_DBG(">>GASMEASIR_DB: �궨���");
    }
}

static void Mod_GasMeasCalibAll(GasMeasForIr_t* pst_Meas, GasInfoForIr* pst_Gas1,GasInfoForIr* pst_Gas2)
{
    INT16U  i;
    
    for( i = 0; i < pst_Meas->uin_SpectrumLen; i++)
    {
        pst_Meas->af_DiffSpectrum[i] = pst_Meas->pf_ProcSpectrum[i] - pst_Meas->af_ZeroSpectrum[i]; /* ���²�ֹ��� */
    }
    
    if(pst_Meas->uin_Cnt == 0 )
    {
        for( i = pst_Gas1->uin_SpectrumRangeLeft; i < pst_Gas1->uin_SpectrumRangeRight; i++)  /*��ն�Ӧ���εı�������*/
        {
            pst_Meas->af_BkgSpectrum[i] = 0;
        }
        for( i = pst_Gas2->uin_SpectrumRangeLeft; i < pst_Gas2->uin_SpectrumRangeRight; i++)  /*��ն�Ӧ���εı�������*/
        {
            pst_Meas->af_BkgSpectrum[i] = 0;
        } 
    }

    for( i = pst_Gas1->uin_SpectrumRangeLeft; i < pst_Gas1->uin_SpectrumRangeRight; i++)  /*�ۼƶ�Ӧ���εı�������*/
    {
        pst_Meas->af_BkgSpectrum[i] += pst_Meas->af_DiffSpectrum[i];
    }
    
    for( i = pst_Gas2->uin_SpectrumRangeLeft; i < pst_Gas2->uin_SpectrumRangeRight; i++)  /*�ۼƶ�Ӧ���εı�������*/
    {
        pst_Meas->af_BkgSpectrum[i] += pst_Meas->af_DiffSpectrum[i];
    }
    
    if(++pst_Meas->uin_Cnt >= pst_Meas->uin_ScanAvg )
    {
        for( i = pst_Gas1->uin_SpectrumRangeLeft; i < pst_Gas1->uin_SpectrumRangeRight; i++)  /*ƽ����Ӧ���εı�������*/
        {
            pst_Meas->af_BkgSpectrum[i] /= pst_Meas->uin_ScanAvg;
            pst_Meas->af_CalibSpectrum[i] = pst_Meas->af_BkgSpectrum[i];
        }
        
        for( i = pst_Gas2->uin_SpectrumRangeLeft; i < pst_Gas2->uin_SpectrumRangeRight; i++)  /*ƽ����Ӧ���εı�������*/
        {
            pst_Meas->af_BkgSpectrum[i] /= pst_Meas->uin_ScanAvg;
            pst_Meas->af_CalibSpectrum[i] = pst_Meas->af_BkgSpectrum[i];
        }
        
        SaveToEepromExt((INT32U)pst_Meas->af_CalibSpectrum, 200);

        pst_Meas->uin_ScanAvg = 0;
        if(pst_Meas->b_DiffMeasrue == TRUE)
            pst_Meas->e_State = eGasDiffBackground;
        else
            pst_Meas->e_State = eGasAbsMeasure;

        GASMEASIR_DBG(">>GASMEASIR_DB: �궨���");
    }
}


void LinearRegression(FP32* f_X, FP32* f_Y, INT16U uin_SampleNum,
                      FP32* f_K, FP32* f_B, FP32* f_R)
{
    FP32 f_Xavg, f_Yavg, f_Lxx, f_Lyy, f_Lxy;
    INT16U i;
    
///////////////////////////////////////////////////////////////////
//                          ����X��Y��ƽ��ֵ
///////////////////////////////////////////////////////////////////
    f_Xavg = 0;
    for (i = 0; i < uin_SampleNum; i++ )
    {
        f_Xavg += f_X[i];
    }
    f_Xavg /= uin_SampleNum;
    
    f_Yavg = 0;
    for (i = 0; i < uin_SampleNum; i++ )
    {
        f_Yavg += f_Y[i];
    }
    f_Yavg /= uin_SampleNum;
///////////////////////////////////////////////////////////////////
//                          ����Lxx Lyy Lxy
///////////////////////////////////////////////////////////////////
    f_Lxx = 0;
    for (i = 0; i < uin_SampleNum; i++ )
    {
        f_Lxx += f_X[i]*f_X[i];
    }
    f_Lxx -= uin_SampleNum*f_Xavg*f_Xavg;
    
    f_Lyy = 0;
    for (i = 0; i < uin_SampleNum; i++ )
    {
        f_Lyy += f_Y[i]*f_Y[i];
    }
    f_Lxx -= uin_SampleNum*f_Xavg*f_Xavg;
      
    f_Lxy = 0;
    for (i = 0; i < uin_SampleNum; i++ )
    {
        f_Lxy += f_X[i]*f_Y[i];
    }
    f_Lxx -= uin_SampleNum*f_Xavg*f_Yavg;

///////////////////////////////////////////////////////////////////
//                          ����K B R
///////////////////////////////////////////////////////////////////
    if(f_K != NULL)
        *f_K = f_Lxy/f_Lxx;

    if(f_K != NULL && f_B != NULL)
        *f_B = f_Yavg - *f_K*f_Xavg;

    if(f_R != NULL)
        *f_R = f_Lxy/sqrt(f_Lxx*f_Lyy);
}

void Mod_GasMeasMeasure(GasMeasForIr_t* pst_Meas,GasInfoForIr* pst_Gas)
{
    LinearRegression(&pst_Meas->af_CalibSpectrum[pst_Gas->uin_SpectrumRangeLeft],
                     &pst_Meas->af_DiffSpectrum[pst_Gas->uin_SpectrumRangeLeft],
                     pst_Gas->uin_SpectrumRangeRight - pst_Gas->uin_SpectrumRangeLeft + 1,
                     &pst_Gas->f_K,&pst_Gas->f_B,&pst_Gas->f_R);
    pst_Gas->f_Con = pst_Gas->f_CalibCon * pst_Gas->f_K;
}

///////////////////////////////////////////////////////////////////
//                        �Ǳ���Բ���
///////////////////////////////////////////////////////////////////
static void Mod_GasMeasAbsMeasure(GasMeasForIr_t* pst_Meas)
{
    INT16U i;
    for( i = 0; i < pst_Meas->uin_SpectrumLen; i++)
    {
        pst_Meas->af_DiffSpectrum[i] = pst_Meas->pf_ProcSpectrum[i] - pst_Meas->af_ZeroSpectrum[i] ;
    }
    Mod_GasMeasMeasure(pst_Meas,pst_Meas->pst_Gas1);
    Mod_GasMeasMeasure(pst_Meas,pst_Meas->pst_Gas2);
}

///////////////////////////////////////////////////////////////////
//                        �Ǳ��ֲ���
///////////////////////////////////////////////////////////////////
static void Mod_GasMeasDiffMeasure(GasMeasForIr_t* pst_Meas)
{
    INT16U i;
    for( i = 0; i < pst_Meas->uin_SpectrumLen; i++)
    {
        pst_Meas->af_DiffSpectrum[i] = pst_Meas->pf_ProcSpectrum[i] - pst_Meas->af_BkgSpectrum[i] ;
    }
    Mod_GasMeasMeasure(pst_Meas,pst_Meas->pst_Gas1);
    Mod_GasMeasMeasure(pst_Meas,pst_Meas->pst_Gas2);
}

static void Mod_GasMeasBackground(GasMeasForIr_t* pst_Meas)
{
    INT16U i;
    for( i = 0; i < pst_Meas->uin_SpectrumLen; i++)
    {
        pst_Meas->af_BkgSpectrum[i] = pst_Meas->pf_ProcSpectrum[i] * pst_Meas->f_FilterCoeff + 
                                      pst_Meas->af_BkgSpectrum[i] *(1-pst_Meas->f_FilterCoeff);
                                      
        pst_Meas->af_DiffSpectrum[i] = pst_Meas->pf_ProcSpectrum[i] - pst_Meas->af_BkgSpectrum[i] ;
    }
}
       
BOOL Mod_GasMeasForIr(GasMeasForIr_t* pst_Meas,FP32* pf_Spectrum, INT16U uin_SpectrumLen)
{
    pst_Meas->pf_ProcSpectrum = pf_Spectrum;
    pst_Meas->uin_SpectrumLen = uin_SpectrumLen;
    GASMEASIR_DBG(">>GASMEASIR_DB: ��������Ũ�ȷ���\r\n");
    switch(pst_Meas->e_State)
    {
    case eGasIdle:
    
        break;
    case eGasAdjZero:
        Mod_GasMeasAdjZero(pst_Meas);
        break;
    case eGasCalibGas1:
        Mod_GasMeasCalib(pst_Meas,pst_Meas->pst_Gas1);
        break;  
    case eGasCalibGas2:
        Mod_GasMeasCalib(pst_Meas,pst_Meas->pst_Gas2);
        break; 
    case eGasCalibGasAll:
        Mod_GasMeasCalibAll(pst_Meas,pst_Meas->pst_Gas1,pst_Meas->pst_Gas2);
        break;
    case eGasAbsMeasure:
        Mod_GasMeasAbsMeasure(pst_Meas);
        break;  
    case eGasDiffBackground:
        Mod_GasMeasBackground(pst_Meas);
        break;
    case eGasDiffMeasure:
        Mod_GasMeasDiffMeasure(pst_Meas);
        break;
    default:
        break;
    }

    return TRUE;
}
