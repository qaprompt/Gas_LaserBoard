//==================================================================================
//| �ļ����� | ���ⷢ����մ���
//|----------|----------------------------------------------------------------------
//| �ļ����� | 
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#ifndef __MOD_LASER_H__
#define __MOD_LASER_H__


typedef enum {
    eLaserOff,
    eLaserRise,
    eLaserHigh,
    eLaserFall,
    eLaserLow,
    eLaserStop,//ֹͣ״̬   ͬ���źŽ��ܵ������źź� ���Ʋ��½���0�Ĺ���
    eLaserIdle,//����״̬   ���Ʋ��½���0�� �ȴ� ���ܵ�������ȥ�źź� ��ʼ����
}eLaserState;


typedef struct __Laser {
    /* public */
    volatile eLaserState e_State;                    /* ״̬ */
    
    Wave_t* pst_Wave;                       /* ���Ͳ��νṹ�� ��� */

    Tec_t * pst_Tec;					    /* TEC��� */

    FP32    f_Curr;                         /* ���������� */

}Laser_t;

extern Laser_t    st_Laser;

extern void Mod_LaserEnable(void* pv_Laser);
extern void Mod_LaserDisable(void* pv_Laser);
extern void Mod_LaserPoll(void* pv_Laser);
extern void Mod_LaserDoStop(void* pv_Laser);
extern void Mod_LaserExitIdle(void* pv_Laser);
#endif
