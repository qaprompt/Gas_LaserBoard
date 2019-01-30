
#ifndef  __APP_TRANSMISSION_H__
#define  __APP_TRANSMISSION_H__  

typedef struct {
    INT16U  uin_SampleCount;
    INT32U  ul_TransSumAD1;
    INT32U  ul_TransSumAD2;

    FP32    f_OffestCompare;  //͸��������ƫ��ֵ
    FP32    f_LightTrans;     //ͨ����         ������ѹ��ֵ/���͵�ѹ��ֵ�����Ƿ�Ӧ͸���ʴ�С��ԭʼ����
    FP32    f_TransK;         //͸��������ϵ��
    FP32    f_Transmission;   //͸����
    FP32    f_VoltMax;        //ʵ�ʵ�ѹ���ֵ
    FP32    f_VoltMin;        //ʵ�ʵ�ѹ��Сֵ
}Transmission_t;

extern Transmission_t st_Trans;

extern void Mod_TransInit(void);
extern void Mod_TransSmapleHigh(void);
extern void Mod_TransSmapleLow(void);
extern FP32 Mod_TransmissionPoll(void);


#endif







