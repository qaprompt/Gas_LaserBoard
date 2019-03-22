//==================================================================================
//| �ļ����� | ���FIR�˲���
//|----------|----------------------------------------------------------------------
//| �ļ����� | 
//|----------|----------------------------------------------------------------------
//| ������� | ��
//|----------|----------------------------------------------------------------------
//| ���ز��� | ��
//==================================================================================
#ifndef __MOD_FIRFILTE_H__
#define __MOD_FIRFILTE_H__

//�����IR
void Mod_FIRFilter(FP32 * pf_Input, INT16U uin_Lenth, const FP32* pf_Factor,INT16U uin_Order,INT16U uin_Avg,INT16U uin_Spand);
//ʹ��DSP���Ż���FIR
void Mod_FIRFilterDsp(FP32 * pf_Input, INT16U uin_Lenth, const FP32* pf_Factor,INT16U uin_Order,INT16U uin_Avg,INT16U uin_Spand);
//ʹ��˫���Ż���FIR
void Mod_FIRFilterTwoCpu(FP32 * pf_Input, INT16U uin_Lenth, const FP32* pf_Factor,INT16U uin_Order,INT16U uin_Avg,INT16U uin_Spand);

#endif
