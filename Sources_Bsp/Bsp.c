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


void  Bsp_Init (void)
{

    Bsp_DelayMs(100);

    Bsp_GpioInit();
    Bsp_SramInit();
    Bsp_SpibInit();       // init SPI

    Bsp_AD5546Init();   //����DAC
    Bsp_AD5663Init();   //SPI DAC
    Bsp_AD7622Init();   //����ADC

    /* ��ʱ��1 �����ʱ�� ϵͳʱ�Ӷ�ʱ�� */
    Bsp_Time1Init(1000);
    Bsp_Time1IntEnable();
    Bsp_Time1Start();
    Bsp_Time1HookRegister(Bsp_SoftTimerPoll);


    /* ���Կ�  RS485 */
    COM1.ul_BaudRate   = 230400;
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


    Bsp_Pga2A0(1);
    Bsp_Pga2A1(1);
}

