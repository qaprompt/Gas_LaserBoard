//==================================================================================================
//| �ļ����� |Mod_Transmission.cpp
//|--------- |--------------------------------------------------------------------------------------
//| �ļ����� | ͸���ʲ��������
//|--------- |--------------------------------------------------------------------------------------
//| ���л��� | ����C/C++���Ա��뻷����������Ƭ��������
//|--------- |--------------------------------------------------------------------------------------
//| ��Ȩ���� | Copyright2007, �۹�Ƽ�(FPI)
//|----------|--------------------------------------------------------------------------------------
//|  �汾    |  ʱ��       |  ����     | ����
//|--------- |-------------|-----------|------------------------------------------------------------
//|  V1.0    | 2007.10.10  |  gao      | ����
//==================================================================================================

#include "App_Include.h"



Transmission_t st_Trans = {
    0,
    0,
    0,
    
    -0.16,
    0,
    1.0,
    0,
    0,
    0,
};

void Mod_TransInit(void)
{
    st_Trans.uin_SampleCount = 0;
    st_Trans.ul_TransSumAD1 = 0;
    st_Trans.ul_TransSumAD2 = 0;
    
    st_Trans.f_LightTrans = 0;
    st_Trans.f_Transmission = 0;
    st_Trans.f_VoltMax = 0;
    st_Trans.f_VoltMin = 0;
}

//==================================================================================================
//| �������� | s_SmapleAndAddTransmission1()
//|----------|--------------------------------------------------------------------------------------
//| �������� | ͸����1�������ۼ�(͸����������)
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//|----------|-------------------------------------------------------------------------------------- 
//| ������� | gao,07.10.24
//==================================================================================================  
void Mod_TransSmapleHigh(void)
{
    INT16U uin_Temp;
	uin_Temp = Bsp_Ltc1867SampleAvg(eSignalDC,50);
    st_Trans.ul_TransSumAD1 += uin_Temp; 
}


//==================================================================================================
//| �������� | s_SmapleAndAddTransmission2()
//|----------|--------------------------------------------------------------------------------------
//| �������� | ͸����2�������ۼ�(͸����������)
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//|----------|-------------------------------------------------------------------------------------- 
//| ������� | gao,07.10.24
//==================================================================================================  
void Mod_TransSmapleLow(void)
{
    INT16U uin_Temp;
	uin_Temp = Bsp_Ltc1867SampleAvg(eSignalDC,50);
    st_Trans.ul_TransSumAD2 += uin_Temp; 
    st_Trans.uin_SampleCount++;
}

//==================================================================================================
//| �������� | s_CalTransmission()
//|----------|--------------------------------------------------------------------------------------
//| �������� | ͸���ʼ���
//|----------|--------------------------------------------------------------------------------------
//| ������� | �� 
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ͸����״̬��׼λ
//|----------|-------------------------------------------------------------------------------------- 
//| ������� | gao,07.10.24
//==================================================================================================   
FP32 Mod_TransmissionPoll(void)
{
    FP32 f_Sub,f_Sub0;

    /* ���Ͳ��ε���ߵ����͵�֮��ĵ�ѹ */
	f_Sub0 = st_ModWave.puin_RiseBuff[0] - st_ModWave.puin_RiseBuff[st_ModWave.uin_SampleDot-1];
	f_Sub0 = -1.0f * Bsp_AD5546HexToVolt((INT16U)f_Sub0);

	if(st_Trans.ul_TransSumAD1 < st_Trans.ul_TransSumAD2)
    {
        INT32U temp = st_Trans.ul_TransSumAD1;
        st_Trans.ul_TransSumAD1 = st_Trans.ul_TransSumAD2;
        st_Trans.ul_TransSumAD2 = temp;
    }
    
    st_Trans.f_VoltMax = Bsp_Ltc1867HexToVolt(st_Trans.ul_TransSumAD1/(FP32)st_Trans.uin_SampleCount);
    st_Trans.f_VoltMin = Bsp_Ltc1867HexToVolt(st_Trans.ul_TransSumAD2/(FP32)st_Trans.uin_SampleCount);
        
    f_Sub = (st_Trans.ul_TransSumAD1 - st_Trans.ul_TransSumAD2)/(FP32)st_Trans.uin_SampleCount; 
	f_Sub  = Bsp_Ltc1867HexToVolt(f_Sub);       //ת����ʵ�ʵ�ѹ��

	st_Trans.f_LightTrans = f_Sub/f_Sub0;    //ʵ�ʵ�ѹ��ֵ/���۵�ѹ��ֵ
    

    st_Trans.f_Transmission = (st_Trans.f_LightTrans)*(1.6*st_Trans.f_TransK)*100.0;

    if (st_Trans.f_Transmission > 100)
   	{
   	   	st_Trans.f_Transmission=100;
	}				

    st_Trans.uin_SampleCount = 0;
    st_Trans.ul_TransSumAD1 = 0;
    st_Trans.ul_TransSumAD2 = 0;

	return st_Trans.f_Transmission;
}
