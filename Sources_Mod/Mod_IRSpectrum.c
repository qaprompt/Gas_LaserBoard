#include "App_Include.h"

IrSpectrum_t st_IrSpectrum = {
    5,
    0,
    200,
    {0},
    {0},
    {0},
};


BOOL Mod_IRSpectrumPoll(IrSpectrum_t* pst_Spe)
{
    INT16U  i;

    if(++pst_Spe->uch_ScanCnt >= pst_Spe->uch_ScanAvg)
    {
        pst_Spe->uch_ScanCnt = 0;

        Mod_TransmissionPoll();                                                                      //����͸����

        for(i = 0; i < pst_Spe->uin_SpectrumLen; i++) 
        {
            pst_Spe->af_ProceSpectrum[i] = pst_Spe->af_SumSpectrum[i]/pst_Spe->uch_ScanAvg;             //����ƽ������
            /*����Ҫת���ɵ�ѹ��λ ����ȥ �˷ŵķŴ��� ����ʵ�ʵ����շ� */
            
            pst_Spe->af_SumSpectrum[i] = 0;                                                             //������͹���
        }

        for(i = 0; i < pst_Spe->uin_SpectrumLen; i++) 
        {
            //��б��ʽ ͨ���������������f1 �����ǲ���ֱ������
            FP32 f1 = (st_Trans.f_VoltMax - st_Trans.f_VoltMin) * i / pst_Spe->uin_SpectrumLen + st_Trans.f_VoltMin;
            FP32 f2 = 0; //����ͨ //..f2 = str_Trans.f_DcCancelV;
            FP32 f_K = st_Trans.f_LightTrans;			//������ѹ�Ĳ�ֵ / ԭʼ��ѹ�Ĳ�ֵ�����Ƿ�Ӧ͸���ʴ�С��ԭʼ����
            FP32 f_AverDc = 0;

            if(st_ModWave.f_TrgVpp >0 )													                //���ǲ���ֵ����0
            {
                //��ߵ�ֱ����ѹ(������ѹ) + ������ѹ��ԭʼ��ѹ�Ĳ�ֵ * ͸����ƫ��ֵ
                f_AverDc = f1 + f2 + f_K * st_Trans.f_OffestCompare;							        //͸��������ƫ��ֵ  ����ʵ�ʽ��յ�0.3v���ǲ� ������0.9v���ǲ�
            }
            else
            {
                f_AverDc = f2 +  f_K * st_Trans.f_OffestCompare;								        //͸��������ƫ��ֵ
            }
            
            pst_Spe->af_OriginalSpectrum[i] = pst_Spe->af_ProceSpectrum[i] / f_AverDc;                  //ac/dc ��������͸����
        }
    }
    else
    {
        for(i = 0; i < pst_Spe->uin_SpectrumLen; i++) 
            pst_Spe->af_SumSpectrum[i] += pst_Spe->af_RawSpectrum[i];        //�ۼ���͹���
    }
    return TRUE;
}
