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

    TRACE_DBG("\r\n=========================I/O��ʼ��=========================\r\n");
    TRACE_DBG("  >>LD_PROTECT=1,��������������\n");
    TRACE_DBG("  >>LD_SOFTON=1,���������𶯹��ܹر�\n");
    TRACE_DBG("  >>Tec1_EN=1,������TECģ�����\n");
    TRACE_DBG("  >>Tec2_EN=1,������TECģ�����\n");

    TRACE_DBG("\r\n=========================�ⲿSRAM�Լ�=========================\r\n");
    if(Bsp_SramSelfTest() == FALSE)
        TRACE_DBG("  >>�ⲿSRAM �Լ�ʧ��\n");
    else
        TRACE_DBG("  >>�ⲿSRAM �Լ�ɹ�\n");

    TRACE_DBG("\r\n=========================EEPROM�Լ�=========================\r\n");
        TRACE_DBG("  >>�ⲿEEPROM �Լ�ʧ��\n");
        TRACE_DBG("  >>�ⲿEEPROM �Լ�ɹ�\n");


    TRACE_DBG("\r\n=========================3.3V��ѹ�Լ�=========================\r\n");
    TRACE_DBG("  >>3.3V��ѹ�Լ�ɹ�\n");
    TRACE_DBG("\r\n=========================1.2V��ѹ�Լ�=========================\r\n");
    TRACE_DBG("  >>1.2V��ѹ�Լ�ɹ�\n");
    TRACE_DBG("\r\n========================REF2.5��ѹ�Լ�========================\r\n");
    TRACE_DBG("  >>REF2.5V��ѹ�Լ�ɹ�\n");
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
