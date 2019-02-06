#ifndef     __MOD_GASMEASFORIR_H__
#define     __MOD_GASMEASFORIR_H__


typedef enum {
    eGasN2 = 0,
    eGasCO2,
    eGasCO,
    eGasNO,
    eGasHC,
}GasType_e;

typedef struct {
    INT8U*      puch_Name;                      /* �������� */
    GasType_e   e_GasType;                      /* ������ */

    INT16U      uin_SpectrumRangeLeft;          /* ���׷�Χ */
    INT16U      uin_SpectrumRangeRight;         /* ���׷�Χ */

    FP32        f_CalibCon;                     /* �궨Ũ�� */
    
    FP32        f_K;                            /* ϵ��K */
    FP32        f_B;                            /* ϵ��B */
    FP32        f_R;                            /* ϵ��R */
    
    FP32        f_Con;                          /* Ũ�� f_Concentration */
}GasInfoForIr;

typedef enum {
    eGasIdle = 0,                               /* ����ɶ������ */
    eGasAdjZero,                                /* ���� */
    eGasCalibGas1,                              /* �궨 ����1 */
    eGasCalibGas2,                              /* �궨 ����2 */
    eGasCalibGasAll,                            /* �궨 �������� */
    eGasAbsMeasure,                             /* ����Ũ�Ȳ��� */
    eGasDiffBackground,                         /* ��ֲ����ɼ����� */
    eGasDiffMeasure,                            /* ���Ũ�Ȳ��� */
}GasMeasureState_e;

typedef struct {
    GasMeasureState_e   e_State;                /* ״̬ */
    INT16U  uin_SpectrumLen;
    FP32*   pf_ProcSpectrum;                    /* �������� */
    FP32    af_ZeroSpectrum[200];               /* ������� */
    FP32    af_BkgSpectrum[200];                /* �������� */
    FP32    af_DiffSpectrum[200];               /* ��ֹ��� */
    FP32    af_CalibSpectrum[200];              /* У׼���� */
    
    INT16U  uin_Cnt;
    INT16U  uin_ScanAvg; 
    FP32    f_FilterCoeff;                      /* ��������һ���˲�ϵ�� */
    BOOL    b_DiffMeasrue;                      /* �Ƿ��ֲ��� */
    
    GasInfoForIr* pst_Gas1;
    GasInfoForIr* pst_Gas2;
}GasMeasForIr_t;

extern GasInfoForIr st_GasCO2;
extern GasInfoForIr st_GasCO;
extern GasMeasForIr_t st_GasMeasForIr;

BOOL Mod_GasMeasInit(GasMeasForIr_t* pst_Meas);

BOOL Mod_GasMeasForIr(GasMeasForIr_t* pst_Meas,FP32* pf_Spectrum, INT16U uin_SpectrumLen);

BOOL Mod_GasMeasDoAdjZero(GasMeasForIr_t* pst_Meas,INT16U uin_Count);

BOOL Mod_GasMeasDoCalib(GasMeasForIr_t* pst_Meas,INT16U uin_Kind,INT16U uin_Count,FP32 f_CalibCon1,FP32 f_CalibCon2);

BOOL Mod_GasMeasDoAbsMeasure(GasMeasForIr_t* pst_Meas);

BOOL Mod_GasMeasDoDiffMeasure(GasMeasForIr_t* pst_Meas);

BOOL Mod_GasMeasDoDiffBackground(GasMeasForIr_t* pst_Meas);


#endif
