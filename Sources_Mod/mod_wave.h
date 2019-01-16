//==================================================================================
//| �ļ����� | ���Ʋ�����
//|----------|----------------------------------------------------------------------
//| �ļ����� | 
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#ifndef __MOD_WAVE_H__
#define __MOD_WAVE_H__

#include "mod_include.h"

#define     DEF_SINVPP_MIN      (0.0)
#define     DEF_SINVPP_MAX      (0.1)
#define     DEF_TRGVPP_MIN      (0.0)
#define     DEF_TRGVPP_MAX      (0.5)
#define     DEF_DCOFFSET_MIN    (0.0)    
#define     DEF_DCOFFSET_MAX    (1.0)    
#define     DEF_SINFREQ_MIN     (1.0)
#define     DEF_SINFREQ_MAX     (20.0)
#define     DEF_SAMPLEFREQ_MIN  (100.0)
#define     DEF_SAMPLEFREQ_MAX  (500.0)
#define     DEF_SAMPLEDOT_MIN   (1000)
#define     DEF_SAMPLEDOT_MAX   (30000)

#define		DEF_FALLDOT_MIN		(400)
#define		DEF_FALLDOT_MAX		(10000)

#define		DEF_WAVE_MAX		(2)

struct Wave_t {
    /* public */
    FP32    f_SinVpp;           /* ���Ҳ���ֵ V */ 
    FP32    f_TrgVpp;           /* ���ǲ�̧����ѹ V */ 
    FP32    f_DcOffset;         /* ֱ��ƫ�õ�ѹ V */ 
    
    FP32    f_SinFreq;          /* ���Ҳ�Ƶ�� KHZ */
    FP32    f_SampleFreq;       /* ����Ƶ�� KHZ */
    INT16U  uin_SampleDot;      /* �������� */
    
    FP32    f_RiseTime;         /* �����س���ʱ�� Ms*/    
    FP32    f_HigtTime;         /* �ߵ�ƽ����ʱ�� Ms*/    
    FP32    f_FallTime;         /* �½��س���ʱ�� Ms*/
    FP32    f_LowTime;          /* �͵�ƽ����ʱ�� Ms*/
    
    FP32    f_Interval;         /* ÿ����ļ��ʱ�� US*/
    INT16U  uin_RiseDot;        /* �������ε����ݻ��峤�� */
    INT16U  uin_HigtDot;        /* �ߵ�ƽʱ�����ݻ��峤�� */
    INT16U  uin_FallDot;        /* �½����ε����ݻ��峤�� */
    INT16U  uin_LowDot;         /* �͵�ƽʱ�����ݻ��峤�� */
    volatile INT16U* puin_RiseBuff;      /* �������ε����ݻ��� */
    volatile INT16U* puin_FallBuff;      /* �½����ε����ݻ��� */
    
    FP32    f_HwDcOffset;       /* Ӳ��ֱ��ƫ�õ�ѹ */    
};

extern struct Wave_t    st_Wave;

extern BOOL Mod_GenerateWave(void * pv_Wave);
extern BOOL Mod_SetSinVpp(void * pv_Wave,FP32 f_SinVpp,BOOL b_WriteEPROM);
extern BOOL Mod_SetTrgVpp(void * pv_Wave,FP32 f_TrgVpp,BOOL b_WriteEPROM);
extern BOOL Mod_SetDcOffset(void * pv_Wave,FP32 f_DcOffset,BOOL b_WriteEPROM);
extern BOOL Mod_SetSinFreq(void * pv_Wave,FP32 f_SinFreq,BOOL b_WriteEPROM);
extern BOOL Mod_SetSampleFreq(void * pv_Wave,FP32 f_SampleFreq,BOOL b_WriteEPROM);
extern BOOL Mod_SetSampleDot(void * pv_Wave,INT16U uin_SampleDot,BOOL b_WriteEPROM);


#endif