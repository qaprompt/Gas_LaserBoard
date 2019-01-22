#ifndef __MOD_USB4000_H__
#define __MOD_USB4000_H__

typedef enum
{
    USB4000_DISCONNECT = 0,
    USB4000_INIT,
    USB4000_CONFIG,
    USB4000_SAMPLE,
    USB4000_ERROR,
}USB4000_StateTypeDef;

typedef struct _USB4000_Process
{
    uint32_t             rx_count;

    uint8_t              b_SetFlag;
    uint32_t             ul_SetIntegralTime;



    int16_t              ain_Spectrum[3840];
    int32_t              al_SumSpectrum[38];

    float               af_ProcessSpectrum[38];
    float               af_WaveLenth[38];


    uint8_t              uch_ScansToAverage;
    uint8_t              uch_ScansConut;
    uint8_t              uch_Boxcar;



    uint8_t              b_EdcEnable;
    uint8_t              b_NlcEnable;
    uint8_t              b_IsConnect;
    uint8_t              b_Open;





    uint8_t              auc_SerialNumber[20];      /* ���к� */
    uint16_t             auin_EdcIndexs[11];        /* 5-15����  */
    float               af_WlcCoeff[4];            /* ����������� */
    float               af_NlcCoeff[8];            /* ������������� */
    uint8_t              uch_NlcOrder;             /* �����Խ���ϵ�� */

    uint16_t             uin_Pixels;               /* ���� */
    uint32_t             ul_IntegralTime;          /* ����ʱ�� */
    uint8_t              uc_PackNum;               /* ������ */
    uint8_t              b_HighSpeed;              /* Usb�ӿ�����  */

    USB4000_StateTypeDef e_State;
}USB4000_HandleTypeDef;

extern USB4000_HandleTypeDef   st_Usb4000;

BOOL Mod_Usb4000Init(void);

BOOL Mod_Usb4000Poll(void);

#endif
