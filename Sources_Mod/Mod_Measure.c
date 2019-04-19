#include "App_Include.h"

#define     DEF_MEASURE_DBG_EN           TRUE

#if (DEF_MEASURE_DBG_EN == TRUE)
    #define MEASURE_DBG(...)            do {                            \
                                            Bsp_Printf(__VA_ARGS__);    \
                                        }while(0)
#else
    #define MEASURE_DBG(...)
#endif

void Mod_MeasureGasCO2Notification(FP32 f_Concentration);
void Mod_MeasureGasCONotification(FP32 f_Concentration);
void TimeOut(void* timer);

Measure_t st_Measure = {
    e_MeasureIdle,                  /* ����״̬ */
	FALSE,							/* �Ƿ�̬���� */
    10,                             /* ����ʱ�� */
    1000,                           /* ����ʱ�� */
    2,								/* ��Ч�� */
    5,								/* ��Ч�� */
    {{0},0,DEF_SAMPLE_DOT_MAX},     /* CO������ */
    {{0},0,DEF_SAMPLE_DOT_MAX},     /* CO2������ */
	0.0,							/* ����ʱ�䴰���ڵ�ƽ��Ũ�� */
	0.0,							/* ����ʱ�䴰���ڵ�ƽ��Ũ�� */
};


SoftTimer_t st_TimeOut = {
    TRUE,                   //����ģʽ
    5000,                   //��һ�εĶ�ʱʱ��
    0,                      //���ڶ�ʱʱ��
    &TimeOut     //�ص�����
};

static void* s_Msg;

static void PostMsg(void* pv_Msg)
{
	s_Msg = pv_Msg;
}

static void* PendMeg(void)
{
    void * pv_Msg;
	DINT;
	pv_Msg = s_Msg;
    if(pv_Msg != NULL)
    	s_Msg = NULL;
	EINT;
    return pv_Msg;
}


void TimeOut(void* timer)
{
    switch (st_Measure.e_State)
    {
    case e_MeasureWait:
        PostMsg((void*)e_MeasureTimeOut);	//�ȴ���ʱ
        Mod_MeasurePoll(&st_Measure);       //��������
        break;
    case e_MeasureDead:
        PostMsg((void*)e_MeasureSample);	//����������ʼ����
        Mod_MeasurePoll(&st_Measure);       //��������
        break;
    case e_MeasureSample:
        PostMsg((void*)e_MeasureCal);		//����������ʼ����  �ȴ�����������
        break;
    }
}

static void StartTimeOutCheck(INT32U TimeOutMs)
{
    st_TimeOut.ul_Dly = TimeOutMs;
    Bsp_SoftTimerStart(&st_TimeOut);
}

static void StopTimeOutCheck(void)
{
    Bsp_SoftTimerStop(&st_TimeOut);
}


static void InitTimeOutCheck(void)
{
    Bsp_SoftTimerReg(&st_TimeOut);
}

static void SortBuff(FP32* pf_Buff,INT16U uin_Len)
{
	INT16U i,j;
	FP32 t;
	for(i = 0; i < uin_Len-1; i++)
	{
		for(j = i+1; j < uin_Len; j++)
		{
			if(pf_Buff[j] > pf_Buff[i])
			{
				t = pf_Buff[j];				//����������
				pf_Buff[j] = pf_Buff[i];
				pf_Buff[i] = t;
			}
		}
	}
}

static FP32 WindowFilter(FP32* pf_Buff,INT16U uin_Use,INT16U uin_InvalidDots, INT16U uin_ActiveDots)
{
    INT16U  i;
    FP32 f = 0;
    FP32 af_Buff[DEF_SAMPLE_DOT_MAX] = {0};

    //memcpy(af_Buff,pf_Buff,sizeof(af_Buff[DEF_SAMPLE_DOT_MAX]));

    for(i = 0; i < DEF_SAMPLE_DOT_MAX; i++)
    {
        af_Buff[i] = pf_Buff[i];
    }


    SortBuff(af_Buff,uin_Use);

    /* �����ȥn1�����ֵ֮�� ʣ��ֵ��n2����Чֵ��ƽ��ֵ */
    if (uin_Use > uin_InvalidDots)
    {
        /* �ܵ��� ������Ч���� */
        INT16U num = uin_Use - uin_InvalidDots;		//����ȥ��N1����Ч���ʣ�����Ʒ����

        if (num  > uin_ActiveDots)					//�ж�ʣ������Ƿ����N2����Ч����
            num  = uin_ActiveDots;

        for( i = 0; i <	num; i++)
            f += af_Buff[uin_InvalidDots + i];	    //���
        f /= num;								    //��ƽ��
    }
    return f;
}

void Mod_MeasureDoStaticMeasure(Measure_t* pst_Meas)
{
	pst_Meas->b_IsStaticMeasure = TRUE;
    Mod_GasMeasDoDiffMeasure(&st_GasMeasForIr);                 //��ʼ��ֲ���
	PostMsg((void*)e_MeasureSample);	//ֱ�ӿ�ʼ����
}

void Mod_MeasureDoDynamicMeasure(Measure_t* pst_Meas)
{
	pst_Meas->b_IsStaticMeasure = FALSE;
    Mod_GasMeasDoDiffBackground(&st_GasMeasForIr);          //��ʼ��ֱ���
	PostMsg((void*)e_MeasureIdle);		//�л�������ģʽ
}


void Mod_MeasureInit(Measure_t* pst_Meas)
{
	InitTimeOutCheck();
    st_GasCO2.cb_Notification = Mod_MeasureGasCO2Notification;
    st_GasCO.cb_Notification  = Mod_MeasureGasCONotification;
}

void Mod_MeasurePoll(Measure_t* pst_Meas)
{
	INT32U i;
    INT32U  e_Msg = (INT32U)PendMeg();
    //FP32 f;
    switch(e_Msg)
    {
    case e_MeasureWait:
        pst_Meas->e_State = e_MeasureWait;
        StartTimeOutCheck(5000);                                        //��ʼ��ʱ��� 10Km/h ��������ʱ��200ms 180Km/h��������ʱ��10ms/h
        Mod_GasMeasDoDiffMeasure(&st_GasMeasForIr);                  //��ʼ��ֲ���

        MEASURE_DBG(">>MEASURE DBG:   �������� ׼����ʼ����\r\n");
        break;
    case e_MeasureDead:
		pst_Meas->e_State = e_MeasureDead;
        StopTimeOutCheck();                                     	    //ֹͣ��ʱ���
        if ( pst_Meas->ul_DeadTime > 0 )
        {
			StartTimeOutCheck(pst_Meas->ul_DeadTime);                   //��ʼ������ʱ
	        MEASURE_DBG(">>MEASURE DBG:   ������ȥ ������ʱ\r\n");
        }
        else
        {
			PostMsg((void*)e_MeasureSample);	                        //����������ʼ����
			Mod_MeasurePoll(pst_Meas);                                  //�ݹ�ע��
        }
        break;

    case e_MeasureSample:
        pst_Meas->e_State = e_MeasureSample;
        pst_Meas->st_SampleCO.ul_Len = 0;
        pst_Meas->st_SampleCO2.ul_Len = 0;

        StopTimeOutCheck();                                     	//ֹͣ��ʱ���
        if ( pst_Meas->ul_MesureTime > 0 )
        {
			StartTimeOutCheck(pst_Meas->ul_MesureTime);            	//��ʼ������ʱ
        }
        else
        {
            PostMsg((void*)e_MeasureCal);							//����������ʼ����
        }
        MEASURE_DBG(">>MEASURE DBG:   ��ʼ����\r\n");
        break;
    case e_MeasureCal:
        MEASURE_DBG(">>MEASURE DBG:   ��������\r\n");
        if(st_Measure.b_IsStaticMeasure == TRUE)
        {
			PostMsg((void*)e_MeasureSample);						//����������ʼ����
        }
        else
        {
			Mod_GasMeasDoDiffBackground(&st_GasMeasForIr);          //��ʼ��ֱ���
			pst_Meas->e_State = e_MeasureIdle;
        }

        pst_Meas->f_CO2 = WindowFilter (pst_Meas->st_SampleCO2.af_Buff,
                                        pst_Meas->st_SampleCO2.ul_Len,
                                        pst_Meas->uin_InvalidDots,
                                        pst_Meas->uin_ActiveDots);

        pst_Meas->f_CO  = WindowFilter (pst_Meas->st_SampleCO.af_Buff,
                                        pst_Meas->st_SampleCO.ul_Len,
                                        pst_Meas->uin_InvalidDots,
                                        pst_Meas->uin_ActiveDots);

#if 1
        {
            MEASURE_DBG(">>MEASURE DBG:================================================\r\n");

            MEASURE_DBG(">>MEASURE DBG: һ�β������\r\n");

            MEASURE_DBG(">> CO2 %d��������\r\n",(INT16U)pst_Meas->st_SampleCO2.ul_Len);
            for(i = 0; i < pst_Meas->st_SampleCO2.ul_Len; i++)
            {
            	MEASURE_DBG(">> CO2[%02d]: %f\r\n", (INT16U)i, pst_Meas->st_SampleCO2.af_Buff[i]);
            }

            MEASURE_DBG(">> CO->%d��������\r\n",(INT16U)pst_Meas->st_SampleCO.ul_Len);
            for(i = 0; i < pst_Meas->st_SampleCO.ul_Len; i++)
            {
            	MEASURE_DBG(">> CO[%02d]: %f\r\n", (INT16U)i, pst_Meas->st_SampleCO.af_Buff[i]);
            }
            MEASURE_DBG(">> CO2ƽ��ֵ: %f\r\n",pst_Meas->f_CO2 );
            MEASURE_DBG(">> COƽ��ֵ: %f\r\n",pst_Meas->f_CO);

            MEASURE_DBG(">>MEASURE DBG:   �����������\r\n");
            MEASURE_DBG(">>MEASURE DBG:================================================\r\n");

        }
#endif

        break;
    case e_MeasureTimeOut:
        /* �ָ�����ģʽ  */
        MEASURE_DBG(">>MEASURE DBG:   ��������ʱ\r\n");

        StopTimeOutCheck();                                     //ֹͣ��ʱ���

        Mod_GasMeasDoDiffBackground(&st_GasMeasForIr);          //��ʼ��ֱ���

        pst_Meas->e_State = e_MeasureIdle;
        break;

    default:
        break;
    }
}
void Mod_MeasureGasCO2Notification(FP32 f_Concentration)
{
    if(st_Measure.e_State == e_MeasureSample)
    {
        if(st_Measure.st_SampleCO2.ul_Len < st_Measure.st_SampleCO2.ul_Size)
        {
            st_Measure.st_SampleCO2.af_Buff[st_Measure.st_SampleCO2.ul_Len++] = f_Concentration;
        }
    }
}

void Mod_MeasureGasCONotification(FP32 f_Concentration)
{
    if(st_Measure.e_State == e_MeasureSample)
    {
        if(st_Measure.st_SampleCO.ul_Len < st_Measure.st_SampleCO.ul_Size)
        {
            st_Measure.st_SampleCO.af_Buff[st_Measure.st_SampleCO.ul_Len++] = f_Concentration;
        }
    }
}

void Bsp_GpioEvent(INT32U ul_Pin, BOOL b_IsRising)
{
#if 1
    if(ul_Pin == 55 && b_IsRising == TRUE )         //��ͷ��ס��һ��������
    {
        if(st_Measure.e_State == e_MeasureIdle)
        {
            //Mod_LaserDoStop(&st_Laser);           //ֹͣ������ɨ��
            PostMsg((void*)e_MeasureWait);
            Mod_MeasurePoll(&st_Measure);           //��������
        }
    }
    else if(ul_Pin == 56  && b_IsRising == FALSE )   //��λ�뿪�ڶ���������
    {
        if(st_Measure.e_State == e_MeasureWait)
        {
            //Mod_LaserExitIdle(&st_Laser);         //�˳�����ģʽ ����������ɨ��
            //Mod_TransmissionClear();             //͸�������
            PostMsg((void*)e_MeasureDead);
            Mod_MeasurePoll(&st_Measure);           //��������
        }
    }
#else
    //MEASURE_DBG("����:0x%x,����:%x\r\n", ul_Pin, b_IsRising);

	char buff[100];
    sprintf(buff,"����:0x%x,����:%x\r\n", ul_Pin, b_IsRising);
    s_SendStr(buff);
#endif
}





