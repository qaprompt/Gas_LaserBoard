//==================================================================================
//| �ļ����� | ���Ʋ�����
//|----------|----------------------------------------------------------------------
//| �ļ����� | 
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#include "App_Include.h"

/*********************************
 * ���ͽ��ܻ����� �����鶨��
 *********************************/

#ifdef __cplusplus
#pragma DATA_SECTION("Exsram")
#else
//#pragma DATA_SECTION(auin_RiseBuff,"Exsram");
#endif
volatile INT16U auin_RiseBuff[DEF_SAMPLEDOT_MAX] = {0};	//

#ifdef __cplusplus
#pragma DATA_SECTION("Exsram")
#else
//#pragma DATA_SECTION(auin_FallBuff,"Exsram");
#endif
volatile INT16U auin_FallBuff[DEF_FALLDOT_MAX]={0};

#ifdef __cplusplus
#pragma DATA_SECTION("Exsram")
#else
//#pragma DATA_SECTION(auin_RecvBuff,"Exsram");
#endif
volatile INT16U auin_RecvBuff[DEF_SAMPLEDOT_MAX] = {0};



Wave_t    st_ModWave = {
    0.025,          /* ���Ҳ���ֵ V */ 
    0.45,           /* ���ǲ�̧����ѹ V */
    0.512,          /* ֱ��ƫ�õ�ѹ V */ 
    
    10.0,           /* ���Ҳ�Ƶ�� KHZ */
    500.0,          /* ����Ƶ�� KHZ */
    10000.0,        /* �������� */
    
    0.0,            /* �����س���ʱ�� Ms*/    
    4.0,            /* �ߵ�ƽ����ʱ�� Ms*/
    1.0,            /* �½��س���ʱ�� Ms*/
    10.0,           /* �͵�ƽ����ʱ�� Ms*/
    
    0.0,            /* ÿ����ļ��ʱ�� US*/
    0,              /* �������ε����ݻ��峤�� */
    2000,           /* �ߵ�ƽʱ�����ݻ��峤�� */
    1000,           /* �½����ε����ݻ��峤�� */
    7000,           /* �͵�ƽʱ�����ݻ��峤�� */
    auin_RiseBuff,  /* �������ε����ݻ��� */
    auin_FallBuff,  /* �½����ε����ݻ��� */
    
    0,              /* Ӳ��ֱ��ƫ�õ�ѹ */

    auin_RecvBuff,  /* ���ܲ��λ��� */
};

//==================================================================================
//| �������� | Mod_GenerateModWave
//|----------|----------------------------------------------------------------------
//| �������� | �������ݲ������� 
//|----------|----------------------------------------------------------------------
//| ������� | pv_Wave:���
//|----------|----------------------------------------------------------------------
//| ���ز��� | TRUE:�ɹ� FALSE:ʧ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Mod_GenerateModWave(void * pv_Wave)
{
    FP64 fmax = 0.0;
    FP64 mPI = 3.1415926535897932384626433832795;
    FP64 f1 = 0.0,f2 = 0.0,f3 = 0.0, f = 0.0;
    FP64 fdt = 0.0,fpt = 0.0,fw = 0.0;    
    INT16U i;
    Wave_t* p = pv_Wave;
    
    /* ����������� ��λS 1/KHZ*1000 = 1/HZ = S */
    fdt = 1.0 / (p->f_SampleFreq*1000.0);
    /* ����������� ��λus ���ڸ���ʱ����ʼ�� */
    fpt = fdt * 1e6;
    Bsp_Time0Init(fpt);
    /* ���Ҳ���Ƶ�� ��λHZ */   
    fw = p->f_SinFreq * 1000;
   

    /* �����������ʱ��͵��� 
    p->f_Interval = fpt;
    p->uin_RiseDot = p->uin_SampleDot;
    p->uin_HigtDot = p->f_HigtTime * 1000 /  fpt;
    p->uin_FallDot = p->f_FallTime * 1000 /  fpt;
    p->uin_LowDot  = p->f_LowTime * 1000 / fpt;
    p->f_RiseTime = p->uin_SampleDot * p->f_Interval / 1000;*/
    
    /* �����������ʱ��͵��� ͨ��������ʱ�� ���е��������� */
    p->uin_RiseDot = p->uin_SampleDot;
    p->f_RiseTime = p->uin_RiseDot * p->f_Interval / 1000;
    p->f_HigtTime = p->uin_HigtDot * p->f_Interval / 1000;
    p->f_FallTime = p->uin_FallDot * p->f_Interval / 1000;
    p->f_LowTime = p->uin_LowDot * p->f_Interval / 1000;

    /* ��¼һ�����ֵ */
	for(i = 0; i < p->uin_RiseDot; i++)		        //Ĭ��10000�� Э��ɸ���
	{
	    f1 = p->f_DcOffset;					                    //ֱ������
        f2 = p->f_TrgVpp * ( i / (FP64)(p->uin_RiseDot - 1));	//���ǲ�	��ֵ * ��ǰ����/�ܵ���
		f3 = p->f_SinVpp * sin(2 * mPI * (fw * i * fdt));       //���Ҳ�    i / (����Ƶ�� / ���Ҳ���Ƶ��) = i * 1 / ����Ƶ�� * ���Ҳ���Ƶ��
		f  = f1 + f2 + f3;
		if ( f > fmax )
			fmax = f;
        //ι��
	}
    
	/* ����DAC�����ֱ������ */
    p->f_HwDcOffset = fmax;


    /* ����ʵ�ʵĲ��ڵ�ѹ����  */
	for(i = 0; i < p->uin_RiseDot; i++)		                //Ĭ��10000�� Э��ɸ���
	{
		/* sinvpp �Ƿ�ֵ ���� sinvpp*2 + trgvpp <= 0.5V*/
	    f1 = p->f_DcOffset;					                    //ֱ������
        f2 = p->f_TrgVpp * ( i / (FP64)(p->uin_RiseDot - 1));	//���ǲ�	��ֵ * ��ǰ����/�ܵ���
		f3 = p->f_SinVpp * sin(2 * mPI * (fw * i * fdt));       //���Ҳ�
		f  = f1 + f2 + f3 - fmax;

		p->puin_RiseBuff[i] = Bsp_AD5546VoltToHex(f);					//���ڵ�ѹ���� ת�� ΪHex
        //ι��
	}
    
    /* �½�����400���� �����Ƿ�ɵ�? */
	f1 = p->puin_RiseBuff[p->uin_RiseDot-1];               //���һ����
	f2 = p->puin_RiseBuff[0];                              //�ʼ�ĵ�
	for(i = 0; i < p->uin_FallDot; i++)					//�����½�
	{
        f = (f2 - f1) * i / (p->uin_FallDot - 1.0);
        p->puin_FallBuff[i] = f + f1; 
	}

	p->b_GenerateWave = FALSE;
	return TRUE;
}

//==================================================================================
//| �������� | Mod_SetSinVpp
//|----------|----------------------------------------------------------------------
//| �������� | �������Ҳ���ֵ ����������
//|----------|----------------------------------------------------------------------
//| ������� | pv_Wave:��� 
//|          | f_SinVpp:���Ҳ���ֵ
//|          | b_WriteEPROM:TRUE д��EPROM FALSE FALSE:ֻ�������ڴ���
//|----------|----------------------------------------------------------------------
//| ���ز��� | TRUE:�ɹ� FALSE:ʧ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Mod_SetSinVpp(void * pv_Wave,FP32 f_SinVpp,BOOL b_WriteEPROM)
{
	Wave_t* p = pv_Wave;
    if( p != NULL)
    {
        if(f_SinVpp >= DEF_SINVPP_MIN && f_SinVpp <= DEF_SINVPP_MAX && 
           f_SinVpp + p->f_TrgVpp + p->f_DcOffset <= DEF_WAVE_MAX)
        {
            p->f_SinVpp = f_SinVpp;
            
            if(b_WriteEPROM == TRUE)
            {
                if(SaveToEeprom((INT32U)&p->f_SinVpp) != TRUE)
                    return FALSE;
            }
            p->b_GenerateWave = TRUE;
            return TRUE;
        }          
    }
    return FALSE;
}

//==================================================================================
//| �������� | Mod_SetTrgVpp
//|----------|----------------------------------------------------------------------
//| �������� | �������ǲ���ֵ ����������
//|----------|----------------------------------------------------------------------
//| ������� | pv_Wave:��� 
//|          | f_TrgVpp:���ǲ���ֵ
//|          | b_WriteEPROM:TRUE д��EPROM FALSE FALSE:ֻ�������ڴ���
//|----------|----------------------------------------------------------------------
//| ���ز��� | TRUE:�ɹ� FALSE:ʧ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Mod_SetTrgVpp(void * pv_Wave,FP32 f_TrgVpp,BOOL b_WriteEPROM)
{
	Wave_t* p = pv_Wave;
    if( p != NULL)
    {
        if(f_TrgVpp >= DEF_TRGVPP_MIN && f_TrgVpp <= DEF_TRGVPP_MAX &&
            p->f_SinVpp +f_TrgVpp + p->f_DcOffset <= DEF_WAVE_MAX)
        {
            p->f_TrgVpp = f_TrgVpp;
            
            if(b_WriteEPROM == TRUE)
            {
                if(SaveToEeprom((INT32U)&p->f_TrgVpp) != TRUE)
                    return FALSE;
            }
            p->b_GenerateWave = TRUE;
            return TRUE;
        }          
    }
    return FALSE;
}

//==================================================================================
//| �������� | Mod_SetDcOffset
//|----------|----------------------------------------------------------------------
//| �������� | ����ֱ��ƫ�õ�ѹ 
//|----------|----------------------------------------------------------------------
//| ������� | pv_Wave:��� 
//|          | f_DcOffset:ֱ��ƫ�õ�ѹ 
//|          | b_WriteEPROM:TRUE д��EPROM FALSE FALSE:ֻ�������ڴ���
//|----------|----------------------------------------------------------------------
//| ���ز��� | TRUE:�ɹ� FALSE:ʧ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Mod_SetDcOffset(void * pv_Wave,FP32 f_DcOffset,BOOL b_WriteEPROM)
{
	Wave_t* p = pv_Wave;
    if( p != NULL)
    {
        if(f_DcOffset >= DEF_DCOFFSET_MIN && f_DcOffset <= DEF_DCOFFSET_MAX && 
           p->f_SinVpp + p->f_TrgVpp + f_DcOffset <= DEF_WAVE_MAX)
        {
            p->f_DcOffset = f_DcOffset;
            
            if(b_WriteEPROM == TRUE)
            {
                if(SaveToEeprom((INT32U)&p->f_DcOffset) != TRUE)
                    return FALSE;
            }
            p->b_GenerateWave = TRUE;
            return TRUE;
        }          
    }
    return FALSE;
}

//==================================================================================
//| �������� | Mod_SetSinFreq
//|----------|----------------------------------------------------------------------
//| �������� | �������Ҳ�Ƶ��
//|----------|----------------------------------------------------------------------
//| ������� | pv_Wave:��� 
//|          | f_SinFreq:���Ҳ�Ƶ�� 
//|          | b_WriteEPROM:TRUE д��EPROM FALSE FALSE:ֻ�������ڴ���
//|----------|----------------------------------------------------------------------
//| ���ز��� | TRUE:�ɹ� FALSE:ʧ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Mod_SetSinFreq(void * pv_Wave,FP32 f_SinFreq,BOOL b_WriteEPROM)
{
	Wave_t* p = pv_Wave;
    if( p != NULL)
    {
        if(f_SinFreq >= DEF_SINFREQ_MIN && f_SinFreq <= DEF_SINFREQ_MAX)
        {
            p->f_SinFreq = f_SinFreq;
            
            if(b_WriteEPROM == TRUE)
            {
                if(SaveToEeprom((INT32U)&p->f_SinFreq) != TRUE)
                    return FALSE;
            }
            p->b_GenerateWave = TRUE;
            return TRUE;
        }          
    }
    return FALSE;
}

//==================================================================================
//| �������� | Mod_SetSampleFreq
//|----------|----------------------------------------------------------------------
//| �������� | ���ò���Ƶ��
//|----------|----------------------------------------------------------------------
//| ������� | pv_Wave:��� 
//|          | f_SampleFreq:����Ƶ��
//|          | b_WriteEPROM:TRUE д��EPROM FALSE FALSE:ֻ�������ڴ���
//|----------|----------------------------------------------------------------------
//| ���ز��� | TRUE:�ɹ� FALSE:ʧ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Mod_SetSampleFreq(void * pv_Wave,FP32 f_SampleFreq,BOOL b_WriteEPROM)
{
	Wave_t* p = pv_Wave;
    if( p != NULL)
    {
        if(f_SampleFreq >= DEF_SAMPLEFREQ_MIN && f_SampleFreq <= DEF_SAMPLEFREQ_MAX)
        {
            p->f_SampleFreq = f_SampleFreq;
            
            if(b_WriteEPROM == TRUE)
            {
                if(SaveToEeprom((INT32U)&p->f_SampleFreq) != TRUE)
                    return FALSE;
            }
            p->b_GenerateWave = TRUE;
            return TRUE;
        }          
    }
    return FALSE;
}

//==================================================================================
//| �������� | Mod_SetSampleDot
//|----------|----------------------------------------------------------------------
//| �������� | ���ò���Ƶ��
//|----------|----------------------------------------------------------------------
//| ������� | pv_Wave:��� 
//|          | uin_SampleDot:��������
//|          | b_WriteEPROM:TRUE д��EPROM FALSE FALSE:ֻ�������ڴ���
//|----------|----------------------------------------------------------------------
//| ���ز��� | TRUE:�ɹ� FALSE:ʧ��
//|----------|----------------------------------------------------------------------
//| ������� | wjb
//==================================================================================
BOOL Mod_SetSampleDot(void * pv_Wave,INT16U uin_SampleDot,BOOL b_WriteEPROM)
{
	Wave_t* p = pv_Wave;
    if( p != NULL)
    {
        if(uin_SampleDot >= DEF_SAMPLEDOT_MIN && uin_SampleDot <= DEF_SAMPLEDOT_MAX)
        {
            p->uin_SampleDot = uin_SampleDot;
            
            if(b_WriteEPROM == TRUE)
            {
                if(SaveToEeprom((INT32U)&p->uin_SampleDot) != TRUE)
                    return FALSE;
            }
            p->b_GenerateWave = TRUE;
            return TRUE;
        }          
    }
    return FALSE;
}

