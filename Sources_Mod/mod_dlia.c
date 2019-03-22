//==================================================================================
//| �ļ����� | �������Ŵ���
//|----------|----------------------------------------------------------------------
//| �ļ����� | 
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#include "App_Include.h"
#include "fpu_filter.h"
#include "Mod_TestSense.h"
#include "Mod_FirCoeff1.h"      //1200K-1500-4900-1-100     1091
#include "Mod_FirCoeff2.h"      //120K-1200-2400-1-80       253

//���Բ���
//400k_200_9000_1_100
//40k_10_500_1_100

#define     DEF_DLA_DBG_EN           FALSE

#if (DEF_DLA_DBG_EN == TRUE)
    #define DLA_DBG(...)            do {                            \
                                            Bsp_Printf(__VA_ARGS__);    \
                                        }while(0)
#else
    #define DLA_DBG(...)
#endif

/**/
#ifdef __cplusplus
#pragma DATA_SECTION("PrivateRam")
#else
#pragma DATA_SECTION(B1,"PrivateRam");
#endif
//��ͨ 1200k_5000_18000_1_100

#ifdef __cplusplus
#pragma DATA_SECTION("PrivateRam")
#else
#pragma DATA_SECTION(B2,"PrivateRam");
#endif

#ifdef __cplusplus
#pragma DATA_SECTION("PublicRam")
#else
#pragma DATA_SECTION(af_Buff,"PublicRam");
#endif
static FP32 af_Buff[DEF_SAMPLEDOT_MAX] = {0};

DLia_t st_DLia = {
    10.0,                       /* ������Ƶ�� KHZ       */
    0.0,                        /* ��������λ �Ƕ�      */
    200,                        /* ����Ƶ�� KHZ         */
    DEF_SAMPLEDOT_MAX,          /* ������ */
    
    af_Buff,                   /* ���㻺���� */
};


//==================================================================================================
//| �������� | Mod_DLiaGeneratePsdWave
//|----------|--------------------------------------------------------------------------------------
//| �������� | �ڻ������� ���ɼ���������
//|----------|--------------------------------------------------------------------------------------
//| ������� | pst_DLia: ����Ŵ������
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//|----------|-------------------------------------------------------------------------------------- 
//| ������� | 
//==================================================================================================
#pragma CODE_SECTION(Mod_DLiaGeneratePsdWave, ".TI.ramfunc");       //���ص�Ram����ȥ���� �����ʹ��
BOOL Mod_DLiaGeneratePsdWave(DLia_t* pst_DLia, INT16U* puin_InData, INT16U uin_InDataLen)
{
    INT16U i;
	FP64 f1;
	FP64 fdp,fdt,fw;
	FP64 mPI= 3.1415926535897932384626433832795;
/*
    //ʹ������������Ҳ�
	fdt = 1.0 / (pst_DLia->f_SampleFreq * 1000);        // ����������� S
	fdp = pst_DLia->f_PsdPhase / 180 * mPI;             // ת���Ƕ�Ϊ����
	fw = pst_DLia->f_PsdFreq * 1000;                    // �������Ҳ�Ƶ�� HZ

	for(i = 0; i < pst_DLia->uin_SampleMaxDots; i++)
	{
		//f1 = __sin((fw * i * fdt + __mpy2pif32(pst_DLia->f_PsdPhase/360)));
        f1 = sin( 2 * mPI * (fw * i * fdt) + fdp);

		pst_DLia->pf_Buff[i] = (FP32)f1;
        //ι��
	}
*/
	//ʹ��Ӳ��TMU�������Ҳ�
    fdt = 1.0 / (pst_DLia->f_SampleFreq * 1000);        // ����������� S
    fdp = pst_DLia->f_PsdPhase / 360;                   // ת���Ƕ�Ϊ����
    fw = pst_DLia->f_PsdFreq * 1000;                    // �������Ҳ�Ƶ�� HZ
    for(i = 0; i < pst_DLia->uin_SampleMaxDots; i++)
    {
        f1 = __sinpuf32((fw * i * fdt + fdp));
        //pst_DLia->pf_Buff[i] = (aui_TestSenseRecvBuff[i]) * f1;       //ʹ�õ����������
        pst_DLia->pf_Buff[i] = (puin_InData[i]) * f1;   //ʹ�ý��ܵ����ݼ���
        //ι��
    }

	return TRUE;
}

#pragma CODE_SECTION(Mod_DLiaGeneratePsdWave, ".TI.ramfunc");       //���ص�Ram����ȥ���� �����ʹ��
BOOL Mod_DLiaGeneratePsdWaveTwoCpu(DLia_t* pst_DLia)
{
/*
    while(IPCLtoRFlagBusy(IPC_FLAG11) != 0){}           //�����Ƿ����
    DLia_t* p = (void*)CPU01_TO_CPU02_PASSMSG;
    p->f_PsdFreq = pst_DLia->f_PsdFreq;
    p->f_PsdPhase = pst_DLia->f_PsdPhase;
    p->f_SampleFreq = pst_DLia->f_SampleFreq;
    p->pf_Buff = pst_DLia->pf_Buff;
    p->uin_SampleMaxDots = pst_DLia->uin_SampleMaxDots;
    IPCLtoRFlagSet(IPC_FLAG11);                          //����CPU2���� ����FIR��벿��
*/
    return TRUE;
}

//==================================================================================================
//| �������� | Mod_DLiaSetPhase
//|----------|--------------------------------------------------------------------------------------
//| �������� | ��������Ŵ�����λ
//|----------|--------------------------------------------------------------------------------------
//| ������� | pst_DLia: ����Ŵ������	f_Phase:�Ƕ� 0~360 b_Init:�Ƿ���������������
//|----------|--------------------------------------------------------------------------------------
//| ���ز��� | ��
//|----------|--------------------------------------------------------------------------------------
//| ������� |
//==================================================================================================
BOOL Mod_DLiaSetPhase(DLia_t* pst_DLia,FP32 f_Phase,BOOL b_WriteEPROM)
{
	if(f_Phase >= 0.0 && f_Phase < 360)
	{
		pst_DLia->f_PsdPhase = f_Phase;
        if(b_WriteEPROM == TRUE)
            if(SaveToEeprom((INT32U)&pst_DLia->f_PsdPhase) != TRUE)
                return FALSE;

        return TRUE;
	}
	return FALSE;
}

//==================================================================================================
//| �������� | Mod_DLiaCal
//|----------|--------------------------------------------------------------------------------------
//| �������� | ��������Ŵ�������
//|----------|--------------------------------------------------------------------------------------
//| ������� | pst_DLia: ����Ŵ������
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//|----------|-------------------------------------------------------------------------------------- 
//| ������� | 
//==================================================================================================
#pragma CODE_SECTION(Mod_DLiaCal, ".TI.ramfunc");       //���ص�Ram����ȥ���� �����ʹ��
BOOL Mod_DLiaCal(DLia_t* pst_DLia,INT16U* puin_InData, INT16U uin_InDataLen,FP32* pf_OutData,INT16U* puin_OutDataLen)
{
    INT16U i;
    INT16U FirOrder1 = sizeof(B1)/sizeof(FP32);
    INT16U FirOrder2 = sizeof(B2)/sizeof(FP32);

    
    /*  ������ �Ѳ����źźͼ�������ǰ���ɵ��ź���� 
        ��Ϊ SinA*SinB= [Cos(A+B)+Cos(A-B)]/2
        ���� VPP*Sin(A)*Sin(A+Phase) = VPP*<[Cos(A+A+Phase)+Cos(A-A-+Phase)]/2>
                                     = VPP*<[Cos(2*A+Phase)+Cos(+-Phase)]/2>
    */
    //Mod_DLiaGenerateTwoCpu(pst_DLia);
    Bsp_AlarmLed(eLedOn);
    DLA_DBG("������\r\n");
    Mod_DLiaGeneratePsdWave(pst_DLia, puin_InData, uin_InDataLen);


    /* ��ͨ�˲��� �˳���Ƶ�ɷ� ��ȡ������ 
       �� VPP*<[Cos(2*A+Phase)+Cos(+-Phase)]/2> ͨ����ͨ�˲�����
       �õ� VPP*[Cos(+-Phase)]/2 �������ź���λ��ͬʱ��ӽ��� Phase ~= 0
       +-Phase��ӦΪ�ڵ�һ��������޶�����ֵ �ڵڶ���������޶��Ǹ�ֵ
       �õ� VPP*[Cos(0)]/2 = VPP/2
    */
    Bsp_AlarmLed(eLedOff);
    DLA_DBG("һ��FIR�˲�\r\n");
    Mod_FIRFilter(pst_DLia->pf_Buff, uin_InDataLen, B1, FirOrder1, 1, 10);			//5.1ms
    Bsp_AlarmLed(eLedOn);
    DLA_DBG("����FIR�˲�\r\n");
    Mod_FIRFilter(pst_DLia->pf_Buff, (uin_InDataLen-FirOrder1)/10, B2, FirOrder2, 1, 4);			//0.9ms
    Bsp_AlarmLed(eLedOff);

    /* �������ݵ�������� */
    if(pf_OutData != NULL)
    {
        DLA_DBG("��������\r\n");
        for(i = 0; i < 200; i++)
        {
            pf_OutData[i] = pst_DLia->pf_Buff[i];
        }
    }

    if(puin_OutDataLen != NULL)
    {
        DLA_DBG("�������\r\n");
        *puin_OutDataLen = 200;
    }

	return TRUE;
}
