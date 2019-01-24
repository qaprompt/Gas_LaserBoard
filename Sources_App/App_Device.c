#include "App_Include.h"

Device_t st_Device = {
    .e_State = e_DevInit,

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

BOOL App_DeviceSelfTest(void)
{
    INT16U i = 0;
    INT16U uin_Temp = 0;
    FP32 f_Temp = 0;
    FP32 f_Aver = 0;


    TRACE_DBG("\r\n=========================I/O��ʼ��=========================\r\n");
    TRACE_DBG("  >>LD_PROTECT=1,��������������\n");
    TRACE_DBG("  >>LD_SOFTON=1,���������𶯹��ܹر�\n");
    TRACE_DBG("  >>Tec1_EN=1,������TECģ�����\n");
    TRACE_DBG("  >>Tec2_EN=1,������TECģ�����\n");

    TRACE_DBG("\r\n=========================�ⲿSRAM�Լ�=========================\r\n");
    //if(Bsp_SramSelfTest() == FALSE)
        TRACE_DBG("  >>�ⲿSRAM �Լ�ʧ��\n");
    //else
        TRACE_DBG("  >>�ⲿSRAM �Լ�ɹ�\n");

    TRACE_DBG("\r\n=========================EEPROM�Լ�=========================\r\n");
        TRACE_DBG("  >>�ⲿEEPROM �Լ�ʧ��\n");
        TRACE_DBG("  >>�ⲿEEPROM �Լ�ɹ�\n");


    TRACE_DBG("\r\n======================3.3V��Դ��ѹ���======================\r\n");

    f_Aver = 0;
    for(i = 1; i <= 10; i++)
    {
        uin_Temp = Bsp_AdcSampleOne(BSP_HF_3_3V_M,BSP_HF_3_3V_CH);
        f_Temp = Bsp_AdcHexToVolt(uin_Temp);
        f_Aver += f_Temp;
        TRACE_DBG("  >>��%02d�β���ֵ:%.4f(0x%04X)\n",i,f_Temp,uin_Temp);
        Bsp_DelayMs(100);
    }
    f_Aver = f_Aver/10;
    TRACE_DBG("  >>ƽ������ֵ:%.4f\n",f_Aver);
    f_Temp = 3.3/2;
    if(f_Aver>f_Temp*0.95 && f_Aver<f_Temp*1.05)
    {
        TRACE_DBG("  >>3.3V��Դ��ѹ�������\n\n");
    }
    else
    {
        TRACE_DBG("  >>3.3V��Դ��ѹ����쳣\n\n");
        while(1);
    }

    TRACE_DBG("\r\n======================1.2V��Դ��ѹ���======================\r\n");
    f_Aver = 0;
    for(i = 1; i <= 10; i++)
    {
        uin_Temp = Bsp_AdcSampleOne(BSP_1_2V_M,BSP_1_2V_CH);
        f_Temp = Bsp_AdcHexToVolt(uin_Temp);
        f_Aver += f_Temp;
        TRACE_DBG("  >>��%02d�β���ֵ:%.4f(0x%04X)\n",i,f_Temp,uin_Temp);
        Bsp_DelayMs(100);
    }
    f_Aver = f_Aver/10;
    TRACE_DBG("  >>ƽ������ֵ:%.4f\n",f_Aver);
    f_Temp = 1.2;
    if(f_Aver>f_Temp*0.95 && f_Aver<f_Temp*1.05)
    {
        TRACE_DBG("  >>1.2V��Դ��ѹ�������\n\n");
    }
    else
    {
        TRACE_DBG("  >>1.2V��Դ��ѹ����쳣\n\n");
        while(1);
    }

    TRACE_DBG("\r\n======================REF2.5V�ο���ѹ���=====================\r\n");

    f_Aver = 0;
    for(i=1; i<=10 ;i++)
    {
        uin_Temp = Bsp_AdcSampleOne(BSP_HF_REF2_5V_M,BSP_HF_REF2_5V_CH);
        f_Temp = Bsp_AdcHexToVolt(uin_Temp);
        f_Aver += f_Temp;
        TRACE_DBG("  >>��%02d�β���ֵ:%.4f(0x%04X)\n",i,f_Temp,uin_Temp);
        Bsp_DelayMs(100);
    }
    f_Aver = f_Aver/10;
    TRACE_DBG("  >>ƽ������ֵ:%.4f\n",f_Aver);
    f_Temp = 2.5/2;
    if(f_Aver>f_Temp*0.95 && f_Aver<f_Temp*1.05 )
    {
        TRACE_DBG("  >>REF2.5V�ο���ѹ�������\n\n");
    }
    else
    {
        TRACE_DBG("  >>REF2.5V�ο���ѹ����쳣\n\n");
        while(1);
    }
    TRACE_DBG("\r\n=========================PCB�¶��Լ�==========================\r\n");
    TRACE_DBG("\r\n========================�������¶��Լ�========================\r\n");
    TRACE_DBG("\r\n========================�������¶��Լ�========================\r\n");

    st_Device.e_State = e_DevStart;

    return TRUE;
}

BOOL App_DeviceStart(void)
{
    Mod_GenerateModWave(&st_ModWave);      //���ɵ��Ʋ�����

    Mod_LaserEnable(&st_Laser);
    st_Device.e_State = e_DevWork;
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

    case e_DevWork:

        Mod_UsbHostPoll();
        Mod_Usb4000Poll();
        Mod_StdbusSlavePoll();
        Mod_StdbusMasterPoll();

        break;

    case e_DevError:

        break;

    default:
        break;

    }
    return TRUE;

}
