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
}eLaserState;

/* ǰ������  typedef����ṹ�����͵�ǰ������ */
struct __Wave;
//typedef struct __Wave Wave_t;

struct __DoubleBuff;
//typedef struct __DoubleBuff DoubleBuff_t;

typedef struct __TEC Tec_t;

typedef struct __Laser {
    /* public */
    eLaserState e_State;                    /* ״̬ */
    
    struct Wave_t* pst_Wave;                /* ���Ͳ��νṹ�� ��� */

    
    //Tec_t * pst_Tec;					    /* TEC��� */
}Laser_t;

extern Laser_t    st_Laser;

extern void Mod_LaserEnable(void* pv_Laser);
extern void Mod_LaserDisable(void* pv_Laser);

#endif
