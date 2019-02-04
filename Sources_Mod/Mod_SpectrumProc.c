#include "App_Include.h"

IrSpectrum_t st_IrSpectrum = {
    5,          //uch_ScanAvg
    0,          //uch_ScanCnt
    150,        //uin_SpectrumLen
    {0},        //af_RawSpectrum
    {0},        //af_SumSpectrum
    {0},        //af_ProceSpectrum
    {0},        //af_OriginalSpectrum
    NULL,       //cb_SpectrumReady
};


BOOL Mod_SpectrumProcForIr(IrSpectrum_t* pst_Spe)
{
    INT16U  i;

    for(i = 0; i < st_Laser.pst_Wave->uin_SampleDot;i++)
    {
        st_Laser.pst_Wave->puin_RecvBuff[i] -= 32768UL;
        //st_Laser.pst_Wave->puin_RecvBuff[i] = aui_TestSenseRecvBuff[i] - 32768UL;       //ʹ�õ����������
    }

    /* ��������Ŵ��� ��������շ� ���շ������ɺ� ���ܻ��������Ѿ����ͷ��� */
    Mod_DLiaCal(&st_DLia,
                 (INT16S*)st_Laser.pst_Wave->puin_RecvBuff,
                 st_Laser.pst_Wave->uin_SampleDot,
                 pst_Spe->af_RawSpectrum,
                 &pst_Spe->uin_SpectrumLen);


    for(i = 0; i < pst_Spe->uin_SpectrumLen; i++)
        pst_Spe->af_SumSpectrum[i] += pst_Spe->af_RawSpectrum[i];        //�ۼ���͹���

    if(++pst_Spe->uch_ScanCnt >= pst_Spe->uch_ScanAvg)
    {
        pst_Spe->uch_ScanCnt = 0;

        Mod_TransmissionPoll();                                                                         //����͸����

        for(i = 0; i < pst_Spe->uin_SpectrumLen; i++) 
        {
            pst_Spe->af_ProceSpectrum[i] = pst_Spe->af_SumSpectrum[i]/pst_Spe->uch_ScanAvg;             //����ƽ������
            /*����Ҫת���ɵ�ѹ��λ ����ȥ �����ķŴ��� ����ʵ�ʵ����շ� */
            
            pst_Spe->af_SumSpectrum[i] = 0;                                                             //������͹���
        }

        for(i = 0; i < pst_Spe->uin_SpectrumLen; i++) 
        {
            //��б��ʽ ͨ���������������f1 �����ǲ���ֱ������
            FP32 f1 = (st_Trans.f_VoltMax - st_Trans.f_VoltMin) * i / pst_Spe->uin_SpectrumLen + st_Trans.f_VoltMin;
            FP32 f2 = 0; //����ͨ //..f2 = str_Trans.f_DcCancelV;
            FP32 f_K = st_Trans.f_LightTrans;			//������ѹ�Ĳ�ֵ / ԭʼ��ѹ�Ĳ�ֵ�����Ƿ�Ӧ͸���ʴ�С��ԭʼ����
            FP32 f_AverDc = 0;
/*
            f_AverDc = st_Trans.f_OffestCompare * f_K;
*/
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

    return TRUE;
}
