//==================================================================================================
//| �ļ����� | Bsp.c
//|----------|--------------------------------------------------------------------------------------
//| �ļ����� | Bsp.c �弶�������ܵ�ʵ��
//|----------|--------------------------------------------------------------------------------------
//| ��Ȩ���� | 
//|----------|--------------------------------------------------------------------------------------
//|  �汾    |  ʱ��       |  ����     | ����
//|----------|-------------|-----------|------------------------------------------------------------
//|  V1.0    | 2018.10.31  |  wjb      | ����
//==================================================================================================
#include  "Bsp.h"


float af_Tmp[5] = {10.1,20.2,30.3,40.4,50.5};
float pf_InData[5] = {0};

void  Bsp_Init (void)
{

    Bsp_DelayMs(100);

    Bsp_GpioInit();
    Bsp_SramInit();
    Bsp_SpibInit();       // init SPI
    Bsp_AdcInit();


    Bsp_AD5546Init();   //����DAC
    Bsp_AD5663Init();   //SPI DAC
    Bsp_AD7622Init();   //����ADC
    Bsp_Ltc1867Init();  //SPI ADC

    /* ��ʱ��1 �����ʱ�� ϵͳʱ�Ӷ�ʱ�� */
    Bsp_Time1Init(1000);
    Bsp_Time1IntEnable();
    Bsp_Time1Start();
    Bsp_Time1HookRegister(Bsp_SoftTimerPoll);


    /* ���Կ�  RS485 */
    COM1.ul_BaudRate   = 1000000;
    COM1.ul_WordLength = UART_WORDLENGTH_8B;
    COM1.ul_StopBits   = UART_STOPBITS_1;
    COM1.ul_Parity     = UART_PARITY_NONE;
    COM1.ul_HwFlowCtl  = UART_HWCONTROL_NONE;
    COM1.ul_Mode       = UART_MODE_TX_RX;
    Bsp_UartOpen(&COM1);

    /* STDBUS �������� */
    COM2.ul_BaudRate   = 230400;
    COM2.ul_WordLength = UART_WORDLENGTH_8B;
    COM2.ul_StopBits   = UART_STOPBITS_1;
    COM2.ul_Parity     = UART_PARITY_NONE;
    COM2.ul_HwFlowCtl  = UART_HWCONTROL_NONE;
    COM2.ul_Mode       = UART_MODE_TX_RX;
    Bsp_UartOpen(&COM2);

    /* STDBUS ������λ�� */
    COM3.ul_BaudRate   = 230400;
    COM3.ul_WordLength = UART_WORDLENGTH_8B;
    COM3.ul_StopBits   = UART_STOPBITS_1;
    COM3.ul_Parity     = UART_PARITY_NONE;
    COM3.ul_HwFlowCtl  = UART_HWCONTROL_NONE;
    COM3.ul_Mode       = UART_MODE_TX_RX;
    Bsp_UartOpen(&COM3);

    Bsp_At24c512Init();

    while(0)
    {
#include "App_Include.h"

        float a[10] = {0,2,3,4,5,6,7,8,9,10};
        float b[3] = {1,2,3};
        a[0] += 1;
        Mod_FIRFilter(a,10,b,2,2,2);
        b[0] += 1;

    }


    while(0)
    {
        #include "App_Include.h"



        //����DMA���п�����������
        DMACH3AddrConfig((volatile Uint16 *)&pf_InData[0],(volatile Uint16 *)&af_Tmp[0]);
        DMACH3BurstConfig(0,0,0);           // Burst size, src step, dest step  Burst size 0 = 1�δ���
        //DMACH3WrapConfig(0, 0, 0, 0);
        DMACH3TransferConfig((10)-1,1,1);       // transfer size, src step, dest step   transfer size 0 = 1�δ���
        DMACH3ModeConfig(0,
                           PERINT_ENABLE,
                           ONESHOT_ENABLE,
                           CONT_DISABLE,
                           SYNC_DISABLE,
                           SYNC_SRC,
                           OVRFLOW_DISABLE,
                           SIXTEEN_BIT,
                           CHINT_END,
                           CHINT_DISABLE);

        StartDMACH3();


        while(1){
            int i = 0;
            for( i = 0; i < 5; i++)
            {
                TRACE_DBG("af_Tmp[%d] = %f\r\n",i ,af_Tmp[i]);
            }

            for( i = 0; i < 5; i++)
            {
                TRACE_DBG("pf_InData[%d]= %f\r\n" ,i ,pf_InData[i]);
            }

        }

    }
}

