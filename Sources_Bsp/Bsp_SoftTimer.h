#ifndef __BSP_SOFTTIMER_H__
#define __BSP_SOFTTIMER_H__

#ifdef __cplusplus
extern "C" {
#endif


#define     DEF_SOFT_TIMER_MAX      20

typedef struct {
    BOOL    b_IsOneShot;        //����ģʽ
    INT32U  ul_Dly;             //��һ�εĶ�ʱʱ��    
    INT32U  ul_Period;          //���ڶ�ʱʱ��
    void    (*cb_CallBack)(void* pv_Timer);         //�ص�����
    
    BOOL    b_Run;              //�Ƿ�����
    BOOL    b_First;            //��һ������
    INT32U  ul_Cnt;             //����ֵ
}SoftTimer_t;

void Bsp_DelayUs(INT32U us);
void Bsp_DelayMs(INT32U ms);

BOOL Bsp_SoftTimerReg(SoftTimer_t* pst_Timer);

BOOL Bsp_SoftTimerStart(SoftTimer_t* pst_Timer);

BOOL Bsp_SoftTimerStop(SoftTimer_t* pst_Timer);

void Bsp_SoftTimerPoll(void);

#ifdef __cplusplus
} /* extern "C" */
#endif  /* __cplusplus */


#endif
