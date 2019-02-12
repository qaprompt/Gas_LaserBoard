#include "App_Include.h"

Device_t st_Device = {
    e_DevInit,
    {e_NoAlarm,e_NoAlarm,e_NoAlarm,e_NoAlarm,e_NoAlarm},
};


void SpectrumReady(FP32* pf_Spectrum,INT16U uin_SpectrumLen)
{
    Mod_GasMeasForIr(&st_GasMeasForIr, pf_Spectrum, uin_SpectrumLen);
}

BOOL App_DeviceInit(void)
{
    Bsp_Init();

    Mod_StdbusInit(&st_StdbusHost,0x20);
    Mod_StdbusSlaveInit();
    Mod_StdbusMasterInit();

    Mod_TemperInit(&st_LaserTemper);
    Mod_TemperInit(&st_PcbTemper);


    st_IrSpectrum.cb_SpectrumReady = SpectrumReady;

    TRACE_DBG("==================================================================================\r\n");
    TRACE_DBG("| �������� | GAS_LASER                                                            \r\n");
    TRACE_DBG("|----------|----------------------------------------------------------------------\r\n");
    TRACE_DBG("| ����汾 | Ver 0.01                                                             \r\n");
    TRACE_DBG("==================================================================================\r\n");

    st_Device.e_State = e_DevSelfTest;

    Mod_Usb4000Init();
    Mod_UsbHostInit();

    while(1)
    {
       Mod_UsbHostPoll();                  //USB�����ӿڴ���
       Mod_Usb4000Poll();                  //�����Ǵ���
    }

    return TRUE;
}


BOOL App_DeviceStart(void)
{
    Mod_MeasureInit(&st_Measure);
    Mod_GasMeasInit(&st_GasMeasForIr);
    Mod_GenerateModWave(&st_ModWave);               //���ɵ��Ʋ�����

    st_DLia.f_PsdFreq = st_ModWave.f_SinFreq * 2;      // �Ŵ����Ҳ��Ķ���г��
    st_DLia.f_SampleFreq = st_ModWave.f_SampleFreq;    // ����Ƶ��

    Mod_LaserEnable(&st_Laser);
    st_Device.e_State = e_DevRun;
    return TRUE;
}

BOOL App_DevicrRun(void)
{
//==================================================================================
//                                  �ȴ�����ߵ�ƽ
//==================================================================================
    while(st_Laser.e_State != eLaserHigh){}
    //�ɼ�͸���ʸߵ�
    Bsp_DelayUs(1);
    Mod_TransSmapleHigh();                  //3MS���ҵ�����

//==================================================================================
//                                  �ȴ�����͵�ƽ
//==================================================================================
    while(st_Laser.e_State != eLaserLow){}
    //�ɼ�͸���ʸߵ�
    Bsp_DelayUs(1);
    Mod_TransSmapleLow();                   //3MS���ҵ�����


    Mod_MeasurePoll(&st_Measure);
    Bsp_RunLed(eLedOn);
    Mod_SpectrumProcForIr(&st_IrSpectrum);     //���շ������ɺ� ���ܻ��������Ѿ����ͷ���
    Bsp_RunLed(eLedOff);

    Mod_StdbusSlavePoll();                  //ͨѶ����
    Mod_StdbusMasterPoll();                 //ͨѶ����

    Mod_LaserPoll(&st_Laser);




    //Mod_UsbHostPoll();                  //USB�����ӿڴ���
    //Mod_Usb4000Poll();                  //�����Ǵ���


    return TRUE;
}

BOOL App_DevicePoll(void)
{
    switch (st_Device.e_State)
    {
    case e_DevSelfTest:

        App_DeviceSelfTest();

        break;

    case e_DevStart:

        App_DeviceStart();

        break;

    case e_DevRun:

        App_DevicrRun();
        break;

    case e_DevError:

        break;

    default:
        break;

    }
    return TRUE;

}

void App_AddOneAlarm(DevAlarmCode_t uch_AlarmCode)
{
    INT8U i;

    /* ������������� �Ƿ���� */
    for(i = 0; i < 5; i++)
    {
        if (st_Device.ae_Alarm[i] == uch_AlarmCode)
            return; //���������
    }

    /* ������������ */
    for(i = 0; i < 5; i++)
    {
        if (st_Device.ae_Alarm[i] == e_NoAlarm)
        {
            st_Device.ae_Alarm[i] = (DevAlarmCode_t)uch_AlarmCode;
            return;
        }
    }

    /* ����ǹ��ϴ������ɾ��һ������ */
    if(uch_AlarmCode > e_FaultFlag)
    {
        for(i = 0; i < 5; i++)
        {
            if (st_Device.ae_Alarm[i] <= e_WarningFlag)
            {
                st_Device.ae_Alarm[i] = (DevAlarmCode_t)uch_AlarmCode;
                return;
            }
        }
    }
}


void App_ClrOneAlarm(DevAlarmCode_t uch_AlarmCode)
{
    INT8U i;
    /* ������������� �Ƿ���� */
     for(i = 0; i < 5; i++)
     {
         st_Device.ae_Alarm[i] = e_NoAlarm;
     }
}

