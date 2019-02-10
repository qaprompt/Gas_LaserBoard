
#ifndef __MOD_MEASURE_H__
#define __MOD_MEASURE_H__

#define DEF_SAMPLE_DOT_MAX     200

typedef struct {
    FP32    af_Buff[DEF_SAMPLE_DOT_MAX];
    INT32U  ul_Len;
    INT32U  ul_Size;
}SampleDots_t;

typedef enum {
    e_MeasureIdle = 0x10,
    e_MeasureWait,
    e_MeasureDead,
    e_MeasureSample,
    e_MeasureCal,
    e_MeasureTimeOut,
}MeasureState_e;

typedef struct {
    MeasureState_e  e_State;        /* ����״̬ */
    BOOL	b_IsStaticMeasure;		/* �Ƿ�̬���� */
    INT32U  ul_DeadTime;            /* ����ʱ�� */
    INT32U  ul_MesureTime;          /* ����ʱ�� */
    INT16U	uin_InvalidDots;		/* ��Ч�� */
    INT16U	uin_ActiveDots;			/* ��Ч�� */
    SampleDots_t st_SampleCO;       /* CO������ */
    SampleDots_t st_SampleCO2;      /* CO2������ */
    FP32	f_CO;					/* ����ʱ�䴰���ڵ�ƽ��Ũ�� */
    FP32	f_CO2;					/* ����ʱ�䴰���ڵ�ƽ��Ũ�� */
}Measure_t ;

extern Measure_t st_Measure;

void Mod_MeasureInit(Measure_t* pst_Meas);
void Mod_MeasurePoll(Measure_t* pst_Meas);
void Mod_MeasureGasCO2Notification(FP32 f_Concentration);
void Mod_MeasureGasCONotification(FP32 f_Concentration);

void Mod_MeasureDoStaticMeasure(Measure_t* pst_Meas);
void Mod_MeasureDoDynamicMeasure(Measure_t* pst_Meas);


#endif /* __APP_MEASURE_H__ */
