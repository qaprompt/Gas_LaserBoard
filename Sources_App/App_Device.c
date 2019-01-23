#include "App_Include.h"

Device_t st_Device = {
    .e_State = e_DevInit,

};
/*
#ifdef __cplusplus
#pragma DATA_SECTION("Exsram")
#else
#pragma DATA_SECTION(auin_ExsramSelfTest,"Exsram");
#endif
volatile INT16U auin_ExsramSelfTest[0x080000] = {0};    //10k
*/

volatile INT16U* auin_ExsramSelfTest = (volatile INT16U*)0x100000;

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
    static BOOL flag = FALSE;
    INT32U i = 0;
    if( flag == FALSE )
    {
        TRACE_DBG("================================I/O��ʼ��================================\r\n");
        TRACE_DBG("  >>LD_PROTECT=1,��������������\n");
        TRACE_DBG("  >>LD_SOFTON=1,���������𶯹��ܹر�\n");
        TRACE_DBG("  >>Tec1_EN=1,������TECģ�����\n");
        TRACE_DBG("  >>Tec2_EN=1,������TECģ�����\n");

        TRACE_DBG("==============================�ⲿSRAM�Լ�===============================\r\n");
/*

        {
            INT16U datbit = 0;
            INT16U rdat = 0;
            INT16U wdat = 0;

            rdat

        }
*/
/**/
        Bsp_IntDis();
        Bsp_AD5546Disable();
        Bsp_AD7622Disable();
        for(i = 0; i < 0x080000; i++)
        {
            auin_ExsramSelfTest[i] = 0;
        }
        for(i = 0; i < 0x080000; i++)
        {
            INT16U dat = (i%65000);
            INT16U rdat;
            auin_ExsramSelfTest[i] = dat;
            rdat = 0;
            rdat = auin_ExsramSelfTest[i];

            if(rdat != dat)
            {

                TRACE_DBG("  >>ExsramSelfTest[%02X%04X]",(INT16U)(i/0x10000ul),(INT16U)(i%0x10000ul));
                TRACE_DBG("  WDAT = %04X, RDAT = %04X, DAT^RDAT = %04X\r\n",dat,rdat,rdat^dat);
            }
        }
        Bsp_AD5546Enable();
        Bsp_AD7622Enable();
        Bsp_IntEn();
/*
        if(Bsp_SramSelfTest() == FALSE)
            TRACE_DBG("  >>�ⲿSRAM �Լ�ʧ��\n");
        else
            TRACE_DBG("  >>�ⲿSRAM �Լ�ɹ�\n");
*/
        TRACE_DBG("===============================EEPROM�Լ�================================\r\n");
            TRACE_DBG("  >>�ⲿEEPROM �Լ�ʧ��\n");
            TRACE_DBG("  >>�ⲿEEPROM �Լ�ɹ�\n");


        TRACE_DBG("==============================3.3V��ѹ�Լ�===============================\r\n");
        TRACE_DBG("==============================1.2V��ѹ�Լ�===============================\r\n");
        TRACE_DBG("=============================REF2.5��ѹ�Լ�==============================\r\n");
        TRACE_DBG("==============================PCB�¶��Լ�================================\r\n");
        TRACE_DBG("=============================�������¶��Լ�==============================\r\n");
        TRACE_DBG("=============================�������¶��Լ�==============================\r\n");
    }


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
