//==================================================================================
//| �ļ����� | bsp_usart.c
//|----------|----------------------------------------------------------------------
//| �ļ����� | ���ϲ��ṩͳһ�Ľӿ� ����ݲ�ͬ��ƽ̨���ĵײ�
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#include   "Bsp.h"

#define     DEF_UART_CONFIG         115200,UART_WORDLENGTH_8B,UART_STOPBITS_1,UART_PARITY_NONE,UART_HWCONTROL_NONE,UART_MODE_TX_RX
#define     DEF_UART_HOOK           0,0,0,0
#define     DEF_UART_BUFF_SIZE      100

static INT8U    auch_RxBuff[4][DEF_UART_BUFF_SIZE] = {0};
static INT8U 	auch_PrintfBuff[100] = {0};
/**/
Dev_SerialPort COM1 = {(const INT8S*)"COM1",                              //�˿���
                        DEF_UART_CONFIG,                    //Ĭ������
                        
                        NULL,                               //���ͻ���������
                        0,
                        0,
                        
                        &auch_RxBuff[0][0],                 //���ջ���������
                        DEF_UART_BUFF_SIZE,
                        0,                     
                        
                        DEF_UART_HOOK,                      //�ص�����
						(void*)&SciaRegs};                 //�ײ���

Dev_SerialPort COM2 = {(const INT8S*)"COM2",                              //�˿���
                        DEF_UART_CONFIG,                    //Ĭ������
                        
                        NULL,                               //���ͻ���������
                        0,
                        0,
                        
                        &auch_RxBuff[1][0],                 //���ջ���������
                        DEF_UART_BUFF_SIZE,
                        0,                     
                        
                        DEF_UART_HOOK,                      //�ص�����
						(void*)&ScibRegs};                 //�ײ���

Dev_SerialPort COM3 = {(const INT8S*)"COM3",                              //�˿���
                        DEF_UART_CONFIG,                    //Ĭ������
                        
                        NULL,                               //���ͻ���������
                        0,
                        0,
                        
                        &auch_RxBuff[2][0],                 //���ջ���������
                        DEF_UART_BUFF_SIZE,
                        0,                     
                        
                        DEF_UART_HOOK,                      //�ص�����
                        (void*)&ScicRegs};                 //�ײ���

Dev_SerialPort COM4 = {(const INT8S*)"COM4",                              //�˿���
                        DEF_UART_CONFIG,                    //Ĭ������
                        
                        NULL,                               //���ͻ���������
                        0,
                        0,
                        
                        &auch_RxBuff[3][0],                 //���ջ���������
                        DEF_UART_BUFF_SIZE,
                        0,                     
                        
                        DEF_UART_HOOK,                      //�ص�����
                        (void*)&ScidRegs};                 //�ײ���

void HAL_UART_MspInit(struct SCI_REGS *huart);
void HAL_UART_MspDeInit(struct SCI_REGS *huart);

                        
void Bsp_UsartRxEnable(Dev_SerialPort* pst_Dev)
{
	struct SCI_REGS * UartHandle = pst_Dev->pv_UartHandle;
    /* ������������ж� */  
	if(UartHandle == &SciaRegs)
	{
		PieCtrlRegs.PIEIER9.bit.INTx1 = 1;          // Enable PIE Group 9 INT1
	}
	else if(UartHandle == &ScibRegs)
	{
		PieCtrlRegs.PIEIER9.bit.INTx3 = 1;          // Enable PIE Group 9 INT3
	}
	else if(UartHandle == &ScicRegs)
	{
		PieCtrlRegs.PIEIER8.bit.INTx5 = 1;          // Enable PIE Group 8 INT5
	}
	else if(UartHandle == &ScidRegs)
	{
		PieCtrlRegs.PIEIER8.bit.INTx7 = 1;          // Enable PIE Group 8 INT7
	}
}

void Bsp_UsartRxDisable(Dev_SerialPort* pst_Dev)
{
	struct SCI_REGS * UartHandle = pst_Dev->pv_UartHandle;
    /* ������������ж� */
	if(UartHandle == &SciaRegs)
	{
		PieCtrlRegs.PIEIER9.bit.INTx1 = 0;          // Enable PIE Group 9 INT1
	}
	else if(UartHandle == &ScibRegs)
	{
		PieCtrlRegs.PIEIER9.bit.INTx3 = 0;          // Enable PIE Group 9 INT3
	}
	else if(UartHandle == &ScicRegs)
	{
		PieCtrlRegs.PIEIER8.bit.INTx5 = 0;          // Enable PIE Group 8 INT5
	}
	else if(UartHandle == &ScidRegs)
	{
		PieCtrlRegs.PIEIER8.bit.INTx7 = 0;          // Enable PIE Group 8 INT7
	}
}

void Bsp_UsartTxEnable(Dev_SerialPort* pst_Dev)
{
	struct SCI_REGS * UartHandle = pst_Dev->pv_UartHandle;
    /* ������������ж� */
	if(UartHandle == &SciaRegs)
	{
		PieCtrlRegs.PIEIER9.bit.INTx2 = 1;          // Enable PIE Group 9 INT1
	}
	else if(UartHandle == &ScibRegs)
	{
		PieCtrlRegs.PIEIER9.bit.INTx4 = 1;          // Enable PIE Group 9 INT3
	}
	else if(UartHandle == &ScicRegs)
	{
		PieCtrlRegs.PIEIER8.bit.INTx6 = 1;          // Enable PIE Group 8 INT5
	}
	else if(UartHandle == &ScidRegs)
	{
		PieCtrlRegs.PIEIER8.bit.INTx8 = 1;          // Enable PIE Group 8 INT7
	}
}

void Bsp_UsartTxDisable(Dev_SerialPort* pst_Dev)
{
	struct SCI_REGS * UartHandle = pst_Dev->pv_UartHandle;
    /* �رշ�������ж� */
	if(UartHandle == &SciaRegs)
	{
		PieCtrlRegs.PIEIER9.bit.INTx2 = 0;          // Enable PIE Group 9 INT1
	}
	else if(UartHandle == &ScibRegs)
	{
		PieCtrlRegs.PIEIER9.bit.INTx4 = 0;          // Enable PIE Group 9 INT3
	}
	else if(UartHandle == &ScicRegs)
	{
		PieCtrlRegs.PIEIER8.bit.INTx6 = 0;          // Enable PIE Group 8 INT5
	}
	else if(UartHandle == &ScidRegs)
	{
		PieCtrlRegs.PIEIER8.bit.INTx8 = 0;          // Enable PIE Group 8 INT7
	}
}

__STATIC_INLINE void Bsp_SendOneByte(Dev_SerialPort* pst_Dev, INT8U byte)
{
    struct SCI_REGS* UartHandle = pst_Dev->pv_UartHandle;
    while (UartHandle->SCIFFTX.bit.TXFFST != 0) {}
    UartHandle->SCITXBUF.all = byte;
}

__STATIC_INLINE INT8U Bsp_RecvOneByte(Dev_SerialPort* pst_Dev)
{
   struct SCI_REGS* UartHandle = pst_Dev->pv_UartHandle;
   //while(UartHandle.SCIFFRX.bit.RXFFST == 0) {} // wait for empty state
   return ((INT8U)UartHandle->SCIRXBUF.all);
}

__STATIC_INLINE void USARTxRecv_IRQHandler(Dev_SerialPort* pst_Dev)
{
    if(pst_Dev->cb_RecvReady != NULL)
    {
        INT8U tmp = Bsp_RecvOneByte(pst_Dev);
        pst_Dev->cb_RecvReady(pst_Dev, &tmp, 1);
    }
}
 __STATIC_INLINE void USARTxSend_IRQHandler(Dev_SerialPort* pst_Dev)
{
    if( pst_Dev->uin_TxCount < pst_Dev->uin_TxLen)
    {
        Bsp_SendOneByte(pst_Dev, pst_Dev->puch_TxBuff[pst_Dev->uin_TxCount++]);
    }
    else
    {
        pst_Dev->uin_TxCount = 0;
        pst_Dev->uin_TxLen = 0;
        if(pst_Dev->cb_SendComplete != NULL)
        {
            pst_Dev->cb_SendComplete(pst_Dev);
        }
    }
}

//==================================================================================
//| �������� | USART1_IRQHandler
//|----------|----------------------------------------------------------------------
//| �������� | USART1�����жϴ�����
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
interrupt void Bsp_SciaRecvIsr(void)
{
	struct SCI_REGS * UartHandle = COM1.pv_UartHandle;

    USARTxRecv_IRQHandler(&COM1);

    UartHandle->SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    UartHandle->SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

interrupt void Bsp_SciaSendIsr(void)
{
	struct SCI_REGS * UartHandle = COM1.pv_UartHandle;

    USARTxSend_IRQHandler(&COM1);

    UartHandle->SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}
//==================================================================================
//| �������� | USART2_IRQHandler
//|----------|----------------------------------------------------------------------
//| �������� | USART2�����жϴ�����
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
interrupt void Bsp_ScibRecvIsr(void)
{
	struct SCI_REGS * UartHandle = COM2.pv_UartHandle;

    USARTxRecv_IRQHandler(&COM2);

    UartHandle->SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    UartHandle->SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

interrupt void Bsp_ScibSendIsr(void)
{
	struct SCI_REGS * UartHandle = COM2.pv_UartHandle;

    USARTxSend_IRQHandler(&COM2);

    UartHandle->SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}
//==================================================================================
//| �������� | USART3_IRQHandler
//|----------|----------------------------------------------------------------------
//| �������� | USART3�����жϴ�����
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
interrupt void Bsp_ScicRecvIsr(void)
{
	struct SCI_REGS * UartHandle = COM3.pv_UartHandle;

    USARTxRecv_IRQHandler(&COM3);

    UartHandle->SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    UartHandle->SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}

interrupt void Bsp_ScicSendIsr(void)
{
	struct SCI_REGS * UartHandle = COM3.pv_UartHandle;

    USARTxSend_IRQHandler(&COM3);

    UartHandle->SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}
//==================================================================================
//| �������� | UART4_IRQHandler
//|----------|----------------------------------------------------------------------
//| �������� | UART4�����жϴ�����
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
interrupt void Bsp_ScidRecvIsr(void)
{
	struct SCI_REGS * UartHandle = COM4.pv_UartHandle;

    USARTxRecv_IRQHandler(&COM4);

    UartHandle->SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    UartHandle->SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

interrupt void Bsp_ScidSendIsr(void)
{
	struct SCI_REGS * UartHandle = COM4.pv_UartHandle;

    USARTxSend_IRQHandler(&COM4);

    UartHandle->SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}
//==================================================================================
//| �������� | Bsp_UartOpen
//|----------|----------------------------------------------------------------------
//| �������� | ���ò��򿪴���
//|----------|----------------------------------------------------------------------
//| ������� | pst_Dev:�����豸�ṹ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | FALSE ��ʧ��, TRUE �򿪳ɹ�
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Bsp_UartOpen(Dev_SerialPort* pst_Dev)
{
    struct SCI_REGS* UartHandle = pst_Dev->pv_UartHandle;
    
    HAL_UART_MspInit(pst_Dev->pv_UartHandle);

    UartHandle->SCICCR.all = 0x0007; // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol
    UartHandle->SCICTL1.all = 0x0003; // enable TX, RX, internal SCICLK,
                                     // Disable RX ERR, SLEEP, TXWAKE
    UartHandle->SCICTL2.all = 0x0003;
    UartHandle->SCICTL2.bit.TXINTENA = 1;
    UartHandle->SCICTL2.bit.RXBKINTENA = 1;

    //
    // SCIA at 9600 baud
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x02 and LBAUD = 0x8B.
    // @LSPCLK = 30 MHz (120 MHz SYSCLK) HBAUD = 0x01 and LBAUD = 0x86.
    //
	INT16U uin_Temp = (INT16U)(200e6 / 4 / pst_Dev->ul_BaudRate / 8 - 1); //Baud = LSPCLK / ((BRR + 1) *8)

    UartHandle->SCIHBAUD.all = uin_Temp >> 8;
    UartHandle->SCILBAUD.all = uin_Temp & 0xff;

    UartHandle->SCICTL1.all = 0x0023;  // Relinquish SCI from Reset

    UartHandle->SCIFFTX.all = 0xA040;
    UartHandle->SCIFFRX.all = 0x2044;
    UartHandle->SCIFFCT.all = 0x0;
    
	if(UartHandle == &SciaRegs)
	{
        EALLOW;	// This is needed to write to EALLOW protected registers
        PieVectTable.SCIA_RX_INT = &Bsp_SciaRecvIsr;
        PieVectTable.SCIA_TX_INT = &Bsp_SciaSendIsr;
        EDIS;   // This is needed to disable write to EALLOW protected registers

        PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
        IER |= M_INT9;                              // Enable CPU INT9
	}
	else if(UartHandle == &ScibRegs)
	{
        EALLOW;	// This is needed to write to EALLOW protected registers
        PieVectTable.SCIB_RX_INT = &Bsp_ScibRecvIsr;
        PieVectTable.SCIB_TX_INT = &Bsp_ScibSendIsr;
        EDIS;   // This is needed to disable write to EALLOW protected registers

        PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
        IER |= M_INT9;                              // Enable CPU INT9
	}
	else if(UartHandle == &ScicRegs)
	{
        EALLOW;	// This is needed to write to EALLOW protected registers
        PieVectTable.SCIC_RX_INT = &Bsp_ScicRecvIsr;
        PieVectTable.SCIC_TX_INT = &Bsp_ScicSendIsr;
        EDIS;   // This is needed to disable write to EALLOW protected registers

        PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
        IER |= M_INT8;                              // Enable CPU INT8
	}
	else if(UartHandle == &ScidRegs)
	{
        EALLOW;	// This is needed to write to EALLOW protected registers
        PieVectTable.SCID_RX_INT = &Bsp_ScidRecvIsr;
        PieVectTable.SCID_TX_INT = &Bsp_ScidSendIsr;
        EDIS;   // This is needed to disable write to EALLOW protected registers

        PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
        IER |= M_INT8;                              // Enable CPU INT8
	}
	Bsp_UsartTxEnable(pst_Dev);
	Bsp_UsartRxEnable(pst_Dev);

    return TRUE;
}

//==================================================================================
//| �������� | Bsp_UartClose
//|----------|----------------------------------------------------------------------
//| �������� | �رմ���
//|----------|----------------------------------------------------------------------
//| ������� | pst_Dev:�������ýṹ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | FALSE �ر�ʧ��, TRUE �رճɹ�
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Bsp_UartClose(Dev_SerialPort* pst_Dev)
{
	HAL_UART_MspDeInit(pst_Dev->pv_UartHandle);
    return TRUE;
}

//==================================================================================
//| �������� | Bsp_UartSendBlock
//|----------|----------------------------------------------------------------------
//| �������� | ���ڷ���(������)
//|----------|----------------------------------------------------------------------
//| ������� | pst_Dev:���ڽṹ�� puch_Buff:���ͻ����� uin_Len:���ͻ���������
//|----------|----------------------------------------------------------------------
//| ���ز��� | FALSE:��������, TRUE:���ͳɹ�
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Bsp_UartSendBlock(Dev_SerialPort *pst_Dev, INT8U* puch_Buff, INT16U uin_Len)
{
    //INT16U i = 0;
#if 0
    if( pst_Dev == NULL || puch_Buff == NULL || uin_Len == 0 )
        return FALSE;
    
    /* ������������� ����ʹ�������ķ��� */
    if( pst_Dev->uin_TxCount != 0 || pst_Dev->uin_TxLen != 0)
        return FALSE;

    
    /* ��Ҫ�رմ��ڷ�������ж� */
    while(uin_Len--)
    {
        Bsp_SendOneByte(pst_Dev,puch_Buff[i++]);
    }
#endif
    if( pst_Dev == NULL || puch_Buff == NULL || uin_Len == 0 )
        return FALSE;

    if( pst_Dev->uin_TxCount < pst_Dev->uin_TxLen)
        return FALSE;

    pst_Dev->puch_TxBuff    = puch_Buff;
    pst_Dev->uin_TxLen      = uin_Len;
    pst_Dev->uin_TxCount    = 0;

    Bsp_SendOneByte(pst_Dev, puch_Buff[pst_Dev->uin_TxCount++]);

    while(pst_Dev->uin_TxLen != 0){}

    return TRUE;
}

//==================================================================================
//| �������� | Bsp_UartSend
//|----------|----------------------------------------------------------------------
//| �������� | ���ڷ���(������)
//|----------|----------------------------------------------------------------------
//| ������� | pst_Dev:���ڽṹ�� puch_Buff:���ͻ����� uin_Len:���ͻ���������
//|----------|----------------------------------------------------------------------
//| ���ز��� | FALSE:��������, TRUE:���ͳɹ�
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Bsp_UartSend(Dev_SerialPort *pst_Dev, INT8U* puch_Buff, INT16U uin_Len)
{
    if( pst_Dev == NULL || puch_Buff == NULL || uin_Len == 0 )
        return FALSE;
    
    if( pst_Dev->uin_TxCount < pst_Dev->uin_TxLen)
        return FALSE;

    pst_Dev->puch_TxBuff    = puch_Buff;
    pst_Dev->uin_TxLen      = uin_Len;
    pst_Dev->uin_TxCount    = 0;
    
    Bsp_SendOneByte(pst_Dev, puch_Buff[pst_Dev->uin_TxCount++]);

    return TRUE;
}

/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - Peripheral's GPIO Configuration  
  *           - NVIC configuration for UART interrupt request enable
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(struct SCI_REGS *huart)
{
    if(huart == &SciaRegs)
    {
        // SCIA GPIO ��ʼ��
#if 0
        GPIO_SetupPinMux(9, GPIO_MUX_CPU1, 6);
        GPIO_SetupPinOptions(9, GPIO_INPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(8, GPIO_MUX_CPU1, 6);
        GPIO_SetupPinOptions(8, GPIO_OUTPUT, GPIO_ASYNC);
#else
        GPIO_SetupPinMux(64, GPIO_MUX_CPU1, 6);
        GPIO_SetupPinOptions(64, GPIO_INPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(65, GPIO_MUX_CPU1, 6);
        GPIO_SetupPinOptions(65, GPIO_OUTPUT, GPIO_ASYNC);
#endif

    }
    else if(huart == &ScibRegs)
    {
        // SCIB GPIO ��ʼ��
        GPIO_SetupPinMux(11, GPIO_MUX_CPU1, 6);
        GPIO_SetupPinOptions(11, GPIO_INPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(10, GPIO_MUX_CPU1, 6);
        GPIO_SetupPinOptions(10, GPIO_OUTPUT, GPIO_ASYNC);
    }
    else if(huart == &ScicRegs)
    {

    }
    else if(huart == &ScidRegs)
    {

    }
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(struct SCI_REGS *huart)
{
    if(huart == &SciaRegs)
    {

    }
    else if(huart == &ScibRegs)
    {

    }
    else if(huart == &ScicRegs)
    {

    }
    else if(huart == &ScidRegs)
    {

    }
}

void Bsp_UartPrintf(const char * Format,...)
{
	Dev_SerialPort* p = &COM1;
	while(p->uin_TxLen != 0){}
	va_list pArgs;
	va_start(pArgs,Format);
	vsprintf((char *)auch_PrintfBuff,Format,pArgs);
	va_end(pArgs);

	/* scia �� 485�ӿ�*/
	if(p == &COM1)
	{
        //Bsp_Rs485de(eRs485Trans);
	}

	Bsp_UartSendBlock(p,auch_PrintfBuff,strlen((const char*)auch_PrintfBuff));
}


int fputc(int ch, FILE *f)
{
    //while (!LL_USART_IsActiveFlag_TXE(USART1)){}
    //LL_USART_TransmitData8(USART1, ch); 
    
    //while (!LL_USART_IsActiveFlag_TC(USART2)){}
    //LL_USART_ClearFlag_TC(USART2);
    return ch;
}

