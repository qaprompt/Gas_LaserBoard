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
    INT16U  uin
    INT16U  uin_UseLeft;
    INT16U  uin_UseRigth;
    INT16U  uin_Max;
    INT16U  uin_LeftMin;
    INT16U  uin_RightMin;

}GasInfoForIr;

typedef struct {
    INT8U*      puch_Name;                      /* �������� */
    GasType_e   e_GasType;                      /* ������ */

    INT16U      uin_SpectrumRangeLeft;          /* ���׷�Χ */
    INT16U      uin_SpectrumRangeRigth;         /* ���׷�Χ */

    FP32        f_A;                            /* ϵ��A */
    FP32        f_B;                            /* ϵ��B */
    FP32        f_R;                            /* ϵ��R */
    
    FP32        f_PeakHight;                    /* ���շ�߶� */
    FP32        f_Concentration;                /* Ũ�� */
}GasInfo_t;



typedef struct {
    FP32    af_ZeroSpectrum[200];
    FP32    af_BkgSpectrum[200];
    FP32    af_DiffSpectrum[200];
    FP32    af_CalibSpectrum[200];
    
    GasInfoForIr* pst_Gas1;
    GasInfoForIr* pst_Gas2;
}GasMeasForIr_t;

extern GasMeasForIr_t st_GasMeasForIr;

BOOL Mod_GasMeasForIr(GasMeasForIr_t* pst_Spe);

#endif
