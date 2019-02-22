//==================================================================================
//| �ļ����� | ���ⷢ����մ���
//|----------|----------------------------------------------------------------------
//| �ļ����� | 
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#include "App_Include.h"

#if 0
#ifdef __cplusplus
#pragma DATA_SECTION("exsram")
#else
#pragma DATA_SECTION(auin_DoubleRecvBuff,"Exsram");
#endif
volatile INT16U auin_DoubleRecvBuff[2][DEF_SAMPLEDOT_MAX] = {0};    //

static DoubleBuff_t st_RecvDoubleBuff = {
    FALSE,                                  /* ���ܻ������л���־  */
    DEF_SAMPLEDOT_MAX,                      /* ���ܻ���������      */
    (void*)auin_DoubleRecvBuff[0],         /* 1���ܻ����� ƹ���л� */
    (void*)auin_DoubleRecvBuff[1],         /* �������� ƹ���л� */
};
#endif


Laser_t    st_Laser = {
    eLaserOff,              /* ״̬ */
    &st_ModWave,            /* ���Ͳ��νṹ�� ��� */
    &st_LaserTEC,           /* TEC��� */
};

static void Mod_RiseLevelInit(void* pv_Laser);
static void Mod_HigtLevelInit(void* pv_Laser);
static void Mod_FallLevelInit(void* pv_Laser);
static void Mod_LowLevelInit(void* pv_Laser);

//==================================================================================
//| �������� | DMA_Handle
//|----------|----------------------------------------------------------------------
//| �������� | DMA2 DAC���DMA�ж� �л��ĸ�״̬
//|----------|----------------------------------------------------------------------
//| ������� | pv_Laser:���
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
void DMA_Handle(void)
{
    Bsp_Time0Stop();
    //TimeA���� TimeB��ʱ TimeC�½� TimeD��ʱ
    switch(st_Laser.e_State)
    {
    /* �����ؽ��� ��ʼ���ߵ�ƽ */
    case eLaserRise:
        Mod_HigtLevelInit(&st_Laser);
        break;
    /* �ߵ�ƽ���� ��ʼ���½��� */
    case eLaserHigh:
        Mod_FallLevelInit(&st_Laser);
        break;
    /* �½��ؽ��� ��ʼ���͵�ƽ */
    case eLaserFall:
        Mod_LowLevelInit(&st_Laser);
        break;
    /* �͵�ƽ���� ��ʼ�������� ��������*/
    case eLaserLow:
        Mod_RiseLevelInit(&st_Laser);
        break;
    /* �½�״̬���� ��ʼ�������� ��������*/
    case eLaserStop:
        Mod_RiseLevelInit(&st_Laser);
        st_Laser.e_State = eLaserIdle;
        return; //�͵�ƽ�����󲻿�����ʱ��
    default:
        Mod_RiseLevelInit(&st_Laser);
        break;
    }
    Bsp_Time0Start();
}

//==================================================================================
//| �������� | DMA_Handle1
//|----------|----------------------------------------------------------------------
//| �������� | DMA1 ADC����DMA�ж� ������
//|----------|----------------------------------------------------------------------
//| ������� | pv_Laser:���
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
void DMA_Handle1(void)
{
    static int j = 0;
    if(j ==0 )
    {
        j = 1;
        Bsp_AlarmLed(eLedOff);
    }
    else
    {
        j = 0;
        Bsp_AlarmLed(eLedOn);
    }
}


//==================================================================================
//| �������� | Mod_SetDcVolt
//|----------|----------------------------------------------------------------------
//| �������� | ����ֱ����ѹ 
//|----------|----------------------------------------------------------------------
//| ������� | f_DcVolt:ֱ����ѹ(V)
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
void Mod_SetDcVolt(FP32 f_DcVolt,FP32 f_AcVolt)
{
    static FP32 f_NowDcVolt = 0.0;
    static FP32 f_NowAcVolt = 0.0;
    INT16U    i,uin_Hex;
    FP32 f_Add;
    for(i = 1;i <= 100;i++)
    {
        f_Add = (f_DcVolt - f_NowDcVolt) / 100.0 * i;
        uin_Hex  = Bsp_AD5663CHAVoltToHex(f_NowDcVolt + f_Add);
        Bsp_AD5663Set(eAD5663_CHA,uin_Hex);

        f_Add = (f_AcVolt - f_NowAcVolt) / 100.0 * i;
        uin_Hex  = Bsp_AD5546VoltToHex(f_NowAcVolt + f_Add);
        Bsp_AD5546Set(uin_Hex);

        Bsp_DelayMs(2);
    }
    f_NowDcVolt = f_DcVolt;
    f_NowAcVolt = f_AcVolt;
}

FP32 Mod_LaserGetCurr(void* pv_Laser)
{
    Laser_t* p = pv_Laser;
    INT16U uin_Temp;
    FP32   f_Temp;
    uin_Temp = Bsp_Ltc1867SampleAvg(eLaserCurr,20);
    f_Temp = Bsp_Ltc1867HexToVolt(uin_Temp);
    p->f_Curr = f_Temp*1000 /1.5 /10;            //1.5�ǵ�ѹ�Ŵ��� 10�ǲ�������
    return p->f_Curr;
}
//==================================================================================
//| �������� | Mod_LaserEnable
//|----------|----------------------------------------------------------------------
//| �������� | ���������� 
//|----------|----------------------------------------------------------------------
//| ������� | pv_Laser:���
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
void Mod_LaserEnable(void* pv_Laser)
{
    INT16U i;

    Laser_t* p = pv_Laser;

    Bsp_Time0Stop();

    Mod_TecEnable(p->pst_Tec,20);

    Bsp_Printf("\r\n=========================����������=========================\r\n");

    Bsp_Printf("    >>�ر�Mos��ǯλ\r\n");
    Bsp_LaserPR(eLaserPrOff);
  
    Bsp_Printf("    >>��������������Դ\r\n");
    Bsp_SoftStart(eSofrtStartOn);
    
    Bsp_Printf("    >>����ֱ��ƫ�õ�ѹ(100�ηֶ�)\r\n");
    Mod_SetDcVolt(p->pst_Wave->f_HwDcOffset,p->pst_Wave->f_HwAcOffset);

    Bsp_Printf("    >>��ӡ10s����������\r\n");
    for(i = 1; i <= 10 ; i++)
    {
        FP32 f_Curr = Mod_LaserGetCurr(p);
        Bsp_Printf("    >>��%02u�뼤��������:%.4f(mA)\r\n",i,f_Curr);
        Bsp_DelayMs(1000);
    }

    Bsp_Printf("    >>������ʱ������DMA���\r\n");
    Mod_RiseLevelInit(p);
    Bsp_Time0Start();
}

//==================================================================================
//| �������� | Mod_LaserDisable
//|----------|----------------------------------------------------------------------
//| �������� | �رռ����� 
//|----------|----------------------------------------------------------------------
//| ������� | pv_Laser:���
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
void Mod_LaserDisable(void* pv_Laser)
{
    Bsp_Printf("\r\n=========================�������ر�=========================\r\n");
    Bsp_Time0Stop();
    
    Bsp_Printf("    >>����ֱ��ƫ�õ�ѹΪ (100�ηֶ�):0.0V \r\n");
    Mod_SetDcVolt(0.0,0.0);

    Bsp_Printf("    >>�رռ���������Դ...\r\n");
    Bsp_SoftStart(eSofrtStartOff);

    Bsp_Printf("    >>�Ͽ������������̵���...\r\n");
    Bsp_LaserPR(eLaserPrOn);
}

void Mod_LaserDoStop(void* pv_Laser)
{
    Bsp_Time0Stop();
    Laser_t* p = pv_Laser;


    switch (p->e_State)
    {
    /* ������ ���ݵ�ǰ��ѹ�ص�0λ*/
    case eLaserRise:
        {
            TRACE_DBG("    >>������ ���ݵ�ǰ��ѹ�ص�0λ\r\n");

            INT16U i = Bsp_Dma1GetTranCont();
            INT16U hex = p->pst_Wave->puin_RiseBuff[i];
            for(i = 0; i < p->pst_Wave->uin_FallDot;i++)
            {
                if (hex < p->pst_Wave->puin_FallBuff[i])
                {
                    break;
                }
            }

            //TRACE_DBG("    >>i = %d, hex = %04x\r\n", i, hex);

            Bsp_Dma1Stop();
            Bsp_Dma2Stop();

            Bsp_Dma1Init((void*)&p->pst_Wave->puin_FallBuff[i],
                 (void*)DEF_AD5546ADDR,
                 1,
                 0,
                 p->pst_Wave->uin_FallDot - i);                   //��DA

            Bsp_Dma1HookRegister(&DMA_Handle);                  //ע��DMA1�ص�����
            Bsp_Dma1IntEnable();                                //����DMA1

            Bsp_Dma1Start();                                    //����DA
            Bsp_Dma2Stop();                                     //�ر�AD����
            p->e_State = eLaserStop;

            //TRACE_DBG("    >>p->pst_Wave->uin_FallDot - i = %d, hex = %04x\r\n", p->pst_Wave->uin_FallDot - i, p->pst_Wave->puin_FallBuff[i]);
        }
        break;
    /* �ߵ�ƽ ֱ�ӵ����½��س���ص�0λ*/
    case eLaserHigh:
        TRACE_DBG("    >>�ߵ�ƽ ֱ�ӵ����½��س���ص�0λ\r\n");
        Bsp_Dma1Stop();
        Bsp_Dma2Stop();
        Mod_FallLevelInit(&st_Laser);
        p->e_State = eLaserStop;
        break;
    /* �½��� ���ı� �����½���0λ*/
    case eLaserFall:
        TRACE_DBG("    >>�½��� ���ı� �����½���0λ\r\n");
        p->e_State = eLaserStop;
        break;
    /* �͵�ƽ ���������ط�ʽ���� ����������ʱ��ֱ���˳� */
    case eLaserLow:
        TRACE_DBG("    >>�͵�ƽ ���������ط�ʽ���� ����������ʱ��ֱ���˳�\r\n");
        Bsp_Dma1Stop();
        Bsp_Dma2Stop();
        Mod_RiseLevelInit(&st_Laser);
        p->e_State = eLaserIdle;
        return;
    }

    Bsp_Time0Start();
}

void Mod_LaserExitIdle(void* pv_Laser)
{
    Laser_t* p = pv_Laser;
    Bsp_Time0Start();
    p->e_State = eLaserRise;
}

void Mod_LaserPoll(void* pv_Laser)
{
    Laser_t* p = pv_Laser;
    if(p->pst_Wave->b_GenerateWave == TRUE)
    {
        Mod_LaserDisable(&st_Laser);                        /* �رռ�����                 */
        Mod_GenerateModWave(&st_ModWave);                 /* �������Ҳ� �������        */
        Mod_LaserEnable(&st_Laser);                         /* ����������                 */
    }
    else
    {
        if(p->e_State == eLaserLow)
        {
            while(st_Laser.e_State == eLaserLow){}
            //Bsp_Time0Start();
            //  <<�ڴ˴�����USB��ȡһ�Ź���
        }
        else if(p->e_State == eLaserRise)
        {
            //Bsp_Time0Start();
            //  <<�ڴ˴�����USB��ȡһ�Ź���
            TRACE_DBG("    >>�͵�ƽʱ�䴦��ʱ\r\n");
        }
    }
}



//==================================================================================
//| �������� | Mod_RiseLevelInit
//|----------|----------------------------------------------------------------------
//| �������� | ��ʼ���½������� 
//|----------|----------------------------------------------------------------------
//| ������� | pv_Laser:���
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
void Mod_RiseLevelInit(void* pv_Laser)
{
    Laser_t* p = pv_Laser;
    //��Ӧ�ϳ���TimeA
    p->e_State = eLaserRise;

    Bsp_Dma1Init((void*)p->pst_Wave->puin_RiseBuff,
        (void*)DEF_AD5546ADDR,
         1,
         0,
         p->pst_Wave->uin_RiseDot);                 //��DA

    Bsp_Dma2Init((void*)DEF_AD7622ADDR,
         (void*)p->pst_Wave->puin_RecvBuff,         //���ܵ�ʹ�û�����
         0,
         1,
         p->pst_Wave->uin_RiseDot);                 //��AD


    Bsp_Dma1HookRegister(&DMA_Handle);
    Bsp_Dma1IntEnable();

    Bsp_Dma2HookRegister(&DMA_Handle1);
    Bsp_Dma2IntEnable();
    Bsp_Dma1Start();
    Bsp_Dma2Start();

}

//==================================================================================
//| �������� | Mod_HigtLevelInit
//|----------|----------------------------------------------------------------------
//| �������� | ��ʼ���ߵ�ƽ���� 
//|----------|----------------------------------------------------------------------
//| ������� | pv_Laser:���
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
void Mod_HigtLevelInit(void* pv_Laser)
{
    Bsp_Dma2Stop();                                 //�ر�AD����

    Laser_t* p = pv_Laser;
    //��Ӧ�ϳ���TimeB
    p->e_State = eLaserHigh;
    Bsp_Dma1Init((void*)&p->pst_Wave->puin_RiseBuff[p->pst_Wave->uin_RiseDot-1],      //���һ���� ά�ֵ͵�ƽ
         (void*)DEF_AD5546ADDR,
         0,
         0,
         p->pst_Wave->uin_HigtDot);        //��DA

    Bsp_Dma1HookRegister(&DMA_Handle);             //ע��DMA1�ص�����
    Bsp_Dma1IntEnable();                            //����DMA1

    Bsp_Dma1Start();                                //����DA
    
    /* �л������� */
    //Mod_SwitchBuff(p->pst_DoubleRecvBuff);
    /*  ���͵����ݴ�������� */

}
//==================================================================================
//| �������� | Mod_FallLevelInit
//|----------|----------------------------------------------------------------------
//| �������� | ��ʼ���½������� 
//|----------|----------------------------------------------------------------------
//| ������� | pv_Laser:���
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
void Mod_FallLevelInit(void* pv_Laser)
{
    Laser_t* p = pv_Laser;
    //��Ӧ�ϳ���TimeC
    p->e_State = eLaserFall;
    Bsp_Dma1Init((void*)p->pst_Wave->puin_FallBuff,
         (void*)DEF_AD5546ADDR,
         1,
         0,
         p->pst_Wave->uin_FallDot);        //��DA

    Bsp_Dma1HookRegister(&DMA_Handle);            //ע��DMA2�ص�����
    Bsp_Dma1IntEnable();                           //����DMA2

    Bsp_Dma1Start();                                //����DA
    Bsp_Dma2Stop();                                 //�ر�AD����
}

//==================================================================================
//| �������� | Mod_LowLevelInit
//|----------|----------------------------------------------------------------------
//| �������� | ��ʼ���͵�ƽ���� 
//|----------|----------------------------------------------------------------------
//| ������� | pv_Laser:���
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
void Mod_LowLevelInit(void* pv_Laser)
{
    Laser_t* p = pv_Laser;
    //��Ӧ�ϳ���TimeD
    p->e_State = eLaserLow;
    Bsp_Dma1Init((void*)&p->pst_Wave->puin_RiseBuff[0],   //��һ���� ά�ֵ͵�ƽ
         (void*)DEF_AD5546ADDR,
         0,
         0,
         p->pst_Wave->uin_LowDot);        //��DA

    Bsp_Dma1HookRegister(&DMA_Handle);              //ע��DMA2�ص�����
    Bsp_Dma1IntEnable();                            //����DMA2

    Bsp_Dma1Start();                                //����DA
    Bsp_Dma2Stop();                                 //�ر�AD����
}



