#include "Bsp.h"

I2cHandle_t Bsp_At24c512;

static void Bsp_E2pomSDAH(void) 
{
    GPIO_WritePin(2,1);
}

static void Bsp_E2pomSDAL(void) 
{
    GPIO_WritePin(2,0);
}

static void Bsp_E2pomSCLH(void)
{
    GPIO_WritePin(3,1);
}

static void Bsp_E2pomSCLL(void)
{
    GPIO_WritePin(3,0);
}

static INT8U Bsp_E2pomSDAValue(void)
{
    return (INT8U)(GPIO_ReadPin(2));
}


void  Bsp_I2cInit(I2cHandle_t* pst_Dev)
{
  
    if( pst_Dev == 0)
        return;
    
    if( pst_Dev == &Bsp_At24c512 )
    {
        /* IO��ʼ�� */
    	//scl
    	GPIO_SetupPinMux(3, GPIO_MUX_CPU1, 0);
    	GPIO_SetupPinOptions(3, GPIO_OUTPUT, GPIO_PULLUP);
    	//sda
    	GPIO_SetupPinMux(2, GPIO_MUX_CPU1, 0);
    	GPIO_SetupPinOptions(2, GPIO_OUTPUT, GPIO_PULLUP);
        
        /* ע��IO�������� */
        pst_Dev->SDA_H = Bsp_E2pomSDAH;
        pst_Dev->SDA_L = Bsp_E2pomSDAL;
        pst_Dev->SCL_H = Bsp_E2pomSCLH;
        pst_Dev->SCL_L = Bsp_E2pomSCLL;
        pst_Dev->SDA_Read = Bsp_E2pomSDAValue; 
        
        Bsp_I2cStop(pst_Dev);
    }

}

//==================================================================================================
//| �������� | Bsp_I2cDelay
//|----------|--------------------------------------------------------------------------------------
//| �������� | I2C��ʱ
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//==================================================================================================
void Bsp_I2cDelay(void) 
{ 
	Bsp_DelayUs(5);
}

//==================================================================================================
//| �������� | Bsp_I2cStart
//|----------|--------------------------------------------------------------------------------------
//| �������� | I2C����
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//==================================================================================================
INT8U Bsp_I2cStart(I2cHandle_t* pst_Dev)
{ 
    (pst_Dev->SDA_H)(); 
    (pst_Dev->SCL_H)();
    
    Bsp_I2cDelay();
    if ( (pst_Dev->SDA_Read)() == 0 )
        return 0; //SDA��Ϊ�͵�ƽ������æ,�˳� 
    
    
    (pst_Dev->SDA_L)(); 
    Bsp_I2cDelay(); 
    if ( (pst_Dev->SDA_Read)() != 0 )
        return 0; //SDA��Ϊ�ߵ�ƽ�����߳���,�˳� 
    
    (pst_Dev->SCL_L)();
    Bsp_I2cDelay(); 
    return 1; 
} 

//==================================================================================================
//| �������� | Bsp_I2cStop
//|----------|--------------------------------------------------------------------------------------
//| �������� | I2C1ֹͣλ
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//==================================================================================================
void Bsp_I2cStop(I2cHandle_t* pst_Dev) 
{ 
    (pst_Dev->SCL_L)();
    Bsp_I2cDelay(); 
    (pst_Dev->SDA_L)(); 
    Bsp_I2cDelay(); 
    (pst_Dev->SCL_H)();
    Bsp_I2cDelay(); 
    (pst_Dev->SDA_H)();
    Bsp_I2cDelay(); 
} 

//==================================================================================================
//| �������� | Bsp_I2cAck
//|----------|--------------------------------------------------------------------------------------
//| �������� | I2C1Ӧ��
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//==================================================================================================
void Bsp_I2cAck(I2cHandle_t* pst_Dev) 
{ 
    (pst_Dev->SCL_L)();
    Bsp_I2cDelay(); 
    (pst_Dev->SDA_L)();
    Bsp_I2cDelay(); 
    (pst_Dev->SCL_H)();
    Bsp_I2cDelay(); 
    (pst_Dev->SCL_L)();
    Bsp_I2cDelay(); 
} 

//==================================================================================================
//| �������� | Bsp_I2cNoAck
//|----------|--------------------------------------------------------------------------------------
//| �������� | I2C1��Ӧ��
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//==================================================================================================
void Bsp_I2cNoAck(I2cHandle_t* pst_Dev) 
{ 
    (pst_Dev->SCL_L)();
    Bsp_I2cDelay(); 
    (pst_Dev->SDA_H)();
    Bsp_I2cDelay(); 
    (pst_Dev->SCL_H)();
    Bsp_I2cDelay(); 
    (pst_Dev->SCL_L)();
    Bsp_I2cDelay(); 
}

//==================================================================================================
//| �������� | Bsp_I2cWaitAck
//|----------|--------------------------------------------------------------------------------------
//| �������� | I2C1�ȴ�Ӧ��
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//==================================================================================================
INT8U Bsp_I2cWaitAck(I2cHandle_t* pst_Dev)
{ 
    (pst_Dev->SCL_L)();
    Bsp_I2cDelay(); 
    (pst_Dev->SDA_H)();
    Bsp_I2cDelay(); 
    (pst_Dev->SCL_H)();
    Bsp_I2cDelay(); 
    if ((pst_Dev->SDA_Read)())
    {
        (pst_Dev->SCL_L)();
        return 0; 
    }
    else
    {
        (pst_Dev->SCL_L)();
        return 1;     
    }
} 

//==================================================================================================
//| �������� | Bsp_I2cSendByte
//|----------|--------------------------------------------------------------------------------------
//| �������� | I2C��������
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//==================================================================================================
void Bsp_I2cSendByte(I2cHandle_t* pst_Dev,INT8U SendByte)
{ 
    INT8U i = 8;
    while (i--)
    {
        (pst_Dev->SCL_L)();
        Bsp_I2cDelay(); 
        
        if ( SendByte & 0x80 )
            (pst_Dev->SDA_H)();
        else
            (pst_Dev->SDA_L)(); 
        
        SendByte<<=1;
        
        Bsp_I2cDelay(); 
        (pst_Dev->SCL_H)();
        Bsp_I2cDelay(); 
    } 
    (pst_Dev->SCL_L)();
} 

//==================================================================================================
//| �������� | Bsp_I2cReceiveByte
//|----------|--------------------------------------------------------------------------------------
//| �������� | I2C1��������
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//==================================================================================================
INT8U Bsp_I2cReceiveByte(I2cHandle_t* pst_Dev)
{  
    INT8U i=8;
    INT8U ReceiveByte=0;

    (pst_Dev->SDA_H)();
    while (i--)
    {
        ReceiveByte<<=1;       
        (pst_Dev->SCL_L)();
        Bsp_I2cDelay(); 
        (pst_Dev->SCL_H)();
        Bsp_I2cDelay(); 
        if ((pst_Dev->SDA_Read)())
        {
            ReceiveByte|=0x01; 
        }
    } 
    (pst_Dev->SCL_L)();
    return ReceiveByte; 
} 
#if 0
//==================================================================================================
//| �������� | I2C1_WriteByte
//|----------|--------------------------------------------------------------------------------------
//| �������� | д��1�ֽ�����
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//==================================================================================================
INT8U I2C1_BufferWrite(I2cHandle_t* pst_Dev, INT8U* pBuffer, uint16_t length,uint16_t WriteAddress, INT8U DeviceAddress)
{
    //���ж�
	__disable_irq();
	
	if(!Bsp_I2cStart(pst_Dev))
	{
	    //���ж�
	    __enable_irq();
		return 0;
	}
    Bsp_I2cSendByte(pst_Dev,DeviceAddress);           //����������ַ
    if(!Bsp_I2cWaitAck(pst_Dev))
	{
		Bsp_I2cStop(pst_Dev); 
		//���ж�
	    __enable_irq();
		return 0;
	}

	Bsp_I2cSendByte(pst_Dev,(INT8U)(WriteAddress>>8));       //������ʼ��ַ(��)
    Bsp_I2cWaitAck(pst_Dev);
	
	Bsp_I2cSendByte(pst_Dev,(INT8U)(WriteAddress));         //������ʼ��ַ(��)
    Bsp_I2cWaitAck(pst_Dev);
	
    while(length--)
    {
      Bsp_I2cSendByte(pst_Dev,*pBuffer);
      Bsp_I2cWaitAck(pst_Dev);
      pBuffer++;
    }
    Bsp_I2cStop(pst_Dev);

	AT24C512_WRITE_PAGE_DLY();
	
	//���ж�
	__enable_irq();

    return 1;
} 

//==================================================================================================
//| �������� | I2C1_ReadByte
//|----------|--------------------------------------------------------------------------------------
//| �������� | ����1������ 
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//==================================================================================================	
void I2C1_PageWrite(I2cHandle_t* pst_Dev,INT8U* pBuffer,uint16_t length,uint16_t WriteAddress,INT8U DeviceAddress)
{
	/*
    INT8U NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;
    Addr  = WriteAddress % AT24C512_PGE_SZE;  //д���ַ�ǿ�ʼҳ�ĵڼ�λ
    count = AT24C512_PGE_SZE - Addr;          //�ڿ�ʼҳҪд��ĸ���
    NumOfPage   =  length / AT24C512_PGE_SZE; //Ҫд���ҳ��
    NumOfSingle =  length % AT24C512_PGE_SZE; //����һҳ�ĸ���

    if(Addr == 0)         //д���ַ��ҳ�Ŀ�ʼ
    {
      if(NumOfPage == 0)  //����С��һҳ
      {
        I2C1_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);   //д����һҳ������
      }
      else                //���ݴ��ڵ���һҳ
      {
        while(NumOfPage)//Ҫд���ҳ��
        {
          I2C1_BufferWrite(pBuffer,AT24C512_PGE_SZE,WriteAddress,DeviceAddress);//дһҳ������
          WriteAddress +=  AT24C512_PGE_SZE;
          pBuffer      +=  AT24C512_PGE_SZE;
          NumOfPage--;
          AT24C512_WRITE_PAGE_DLY();
         }
        if(NumOfSingle!=0)//ʣ������С��һҳ
        {
          I2C1_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress); //д����һҳ������
          AT24C512_WRITE_PAGE_DLY();
        }
       }
    }
    else                  //д���ַ����ҳ�Ŀ�ʼ
    {
      if(NumOfPage== 0)   //����С��һҳ
      {
        I2C1_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);   //д����һҳ������
      }
      else                //���ݴ��ڵ���һҳ
      {
        length       -= count;
        NumOfPage     = length / AT24C512_PGE_SZE;  //���¼���Ҫд���ҳ��
        NumOfSingle   = length % AT24C512_PGE_SZE;  //���¼��㲻��һҳ�ĸ���

        if(count != 0)
        {
          I2C1_BufferWrite(pBuffer,count,WriteAddress,DeviceAddress);      //����ʼ�Ŀռ�д��һҳ
          WriteAddress += count;
          pBuffer      += count;
         }

        while(NumOfPage--)  //Ҫд���ҳ��
        {
          I2C1_BufferWrite(pBuffer,AT24C512_PGE_SZE,WriteAddress,DeviceAddress);//дһҳ������
          WriteAddress +=  AT24C512_PGE_SZE;
          pBuffer      +=  AT24C512_PGE_SZE;
        }
        if(NumOfSingle != 0)//ʣ������С��һҳ
        {
          I2C1_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress); //д����һҳ������
        }
      }
    }
	*/
	I2C1_BufferWrite(pst_Dev, pBuffer,length,WriteAddress,DeviceAddress);
} 

//==================================================================================================
//| �������� | I2C1_ReadByte
//|----------|--------------------------------------------------------------------------------------
//| �������� | ����1������ 
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//==================================================================================================	
INT8U I2C1_ReadByte(I2cHandle_t* pst_Dev,INT8U* pBuffer,uint16_t length,uint16_t ReadAddress,INT8U DeviceAddress)
{       
    
	if (!Bsp_I2cStart(pst_Dev))
	    return 0;

    Bsp_I2cSendByte(pst_Dev,DeviceAddress);
	if (!Bsp_I2cWaitAck(pst_Dev))
    {
        Bsp_I2cStop(pst_Dev); 
		return 0;
    }
	Bsp_I2cSendByte(pst_Dev,(INT8U)(ReadAddress>>8));   //�������ݵ�ַ(��)
    Bsp_I2cWaitAck(pst_Dev);
	
	Bsp_I2cSendByte(pst_Dev,(INT8U)(ReadAddress));   //�������ݵ�ַ(��)
    Bsp_I2cWaitAck(pst_Dev);

	Bsp_I2cDelay();
	
    if (!Bsp_I2cStart(pst_Dev))
	    return 0;

	Bsp_I2cSendByte(pst_Dev,DeviceAddress|0x01);   //���ö���ַ      
    Bsp_I2cWaitAck(pst_Dev);

    while (length)
    {
        *pBuffer = Bsp_I2cReceiveByte(pst_Dev);
        if (length == 1)
		    Bsp_I2cNoAck(pst_Dev);
        else 
		    Bsp_I2cAck(pst_Dev); 
        pBuffer++;
        length--;
    }
    Bsp_I2cStop(pst_Dev);

    return 1;
}

#endif
