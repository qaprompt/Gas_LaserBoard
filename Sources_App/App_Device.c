#include "App_Include.h"

Device_t st_Device = {
    e_DevInit,
    {e_NoAlarm,e_NoAlarm,e_NoAlarm,e_NoAlarm,e_NoAlarm},
};


BOOL App_DeviceInit(void)
{
    Bsp_Init();

    Mod_StdbusInit(&st_StdbusHost,0x20);
    Mod_StdbusSlaveInit();
    Mod_StdbusMasterInit();

    Mod_Usb4000Init();
    Mod_UsbHostInit();
    Mod_TemperInit(&st_LaserTemper);
    Mod_TemperInit(&st_PcbTemper);

    TRACE_DBG("==================================================================================\r\n");
    TRACE_DBG("| �������� | GAS_LASER                                                            \r\n");
    TRACE_DBG("|----------|----------------------------------------------------------------------\r\n");
    TRACE_DBG("| ����汾 | Ver 0.01                                                             \r\n");
    TRACE_DBG("==================================================================================\r\n");

    st_Device.e_State = e_DevSelfTest;

    return TRUE;
}


BOOL App_DeviceStart(void)
{
/*
    Bsp_AD5546Disable();
    Bsp_AD7622Disable();
    while(1)
    {

        Mod_UsbHostPoll();                  //USB�����ӿڴ���
        Mod_Usb4000Poll();                  //�����Ǵ���
        Mod_StdbusSlavePoll();              //ͨѶ����
        Mod_StdbusMasterPoll();             //ͨѶ����
        Mod_LaserPoll(&st_Laser);            //����������������
    }
*/
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
//                                  �ȴ�����������
//==================================================================================
   while(st_Laser.e_State != eLaserRise){}
   //��Ҫ�ڴ� ��USB4000��ʼ�ɼ�һ�Ź���


//==================================================================================
//                                  �ȴ�����ߵ�ƽ
//==================================================================================
    while(st_Laser.e_State != eLaserHigh){
        Mod_UsbHostPoll();                  //USB�����ӿڴ���
        Mod_Usb4000Poll();                  //�����Ǵ���
        Mod_StdbusSlavePoll();              //ͨѶ����
        Mod_StdbusMasterPoll();             //ͨѶ����
    }
    //�ɼ�͸���ʸߵ�



//==================================================================================
//                                  �ȴ������½���
//==================================================================================
    while(st_Laser.e_State != eLaserFall){}
//==================================================================================
//                                  �ȴ�����͵�ƽ
//==================================================================================
    while(st_Laser.e_State != eLaserLow){}
    //�ɼ�͸���ʸߵ�

    {
        INT16U  i;
        INT16U  uin_ResLen;
        FP32    pf_Res[200];



        Bsp_RunLed(eLedOn);

        for(i = 0; i < st_Laser.pst_Wave->uin_SampleDot;i++)
        {
            //st_Laser.pst_Wave->puin_RecvBuff[i] -= 32768UL;
            st_Laser.pst_Wave->puin_RecvBuff[i] = aui_TestSenseRecvBuff[i] - 32768UL;
        }

        Mod_DLiaCal(&st_DLia,
                     (INT16S*)st_Laser.pst_Wave->puin_RecvBuff,
                     st_Laser.pst_Wave->uin_SampleDot,
                     pf_Res,
                     &uin_ResLen);

        Bsp_RunLed(eLedOff);

        //��ӡ���շ�
        //for(i = 0; i < uin_ResLen; i++)
        //    TRACE_DBG("pf_Res[%04d] = %.6f\r\n",i,pf_Res[i]);

    }



    Mod_UsbHostPoll();                  //USB�����ӿڴ���
    Mod_Usb4000Poll();                  //�����Ǵ���
    Mod_StdbusSlavePoll();              //ͨѶ����
    Mod_StdbusMasterPoll();             //ͨѶ����
    Mod_LaserPoll(&st_Laser);            //����������������

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

