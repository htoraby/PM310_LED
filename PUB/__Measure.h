#ifndef __MEASURE_H
#define __MEASURE_H

#ifndef DFT_CHANNEL_HARD
#define DFT_CHANNEL_HARD	8		//A/DӲ��ͨ����;
#endif

//-----------------------------------------------------------------------------
typedef struct _DFTDATA
{
	short nR;						//ʵ��;
	short nX;						//�鲿;
	short nData;					//��Чֵ;
}DFTDATA;

//-----------------------------------------------------------------------------
typedef struct _DFTDATASET
{
	DFTDATA dftdata[DFT_CHANNEL_HARD];
}DFTDATASET;

//-----------------------------------------------------------------------------
typedef struct _ANALOGWAVE
{
//     short nHead;
//     short nEnd;
	WORD wData[DFT_CHANNEL_HARD][DFT_DOTNUM*2];
}ANALOGWAVE;

//-----------------------------------------------------------------------------
typedef struct _REGULATE
{
	short nRegulateR;				//У��ϵ��ʵ��;
	short nRegulateX;				//У��ϵ���鲿;
}REGULATE;

//-----------------------------------------------------------------------------
typedef struct _REGULATESET
{
	REGULATE regulate[DFT_CHANNEL_HARD];
}REGULATESET;

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//˵��:���㸺��ֵ,����������ֵ,ֻ�轫A��C��λ�û�������;
//WORD CalculateNegSeq(MyData* pDataA,MyData* pDataB,MyData* pDataC);
//WORD CalculateNegSeqEx(MyData* pDataAB,MyData* pDataBC);
extern WORD Measure_CalculateNegSeq(MyData* pDataA,MyData* pDataB,MyData* pDataC);
extern WORD Measure_CalculateNegSeqEx(MyData* pDataAB,MyData* pDataBC);

extern REGULATESET g_regulateSet;			//У��ϵ��,������ֵУ������λУ��;
extern ANALOGWAVE g_analogWave;				//ʵʱ��������;
extern WORD g_wErrorAD;
extern DFTDATASET g_dftDataSet;

extern void Measure_StartReg(void);
extern BOOL Measure_GetRegStatus(void);
//˵��:��ʼ����������;
extern void Measure_OnInitParams(void);
//˵��:��ʼ������;
extern void Measure_OnInit(void);
//˵��:��ʱ�������(�ϸ�)����,���ڼ���DFT;
extern void Measure_OnTimer10ms(void);
//˵��:���������ֵ,���������ͨ��pData����;
// extern void Measure_CalculateRMS(WORD wIndexDFT,WORD* pData);
//˵��:�������,���������ʵ�����鲿ͨ��pDataR��pDataX����;
extern void Measure_CalculateDFT1(WORD wIndexDFT,short* pDataR,short* pDataX);
//˵��:����wTHD��г��,���������ʵ�����鲿ͨ��pDataR��pDataX����;
//extern void Measure_CalculateDFTn(WORD wIndexDFT,WORD wTHD,short* pDataR,short* pDataX);
//˵��:��ָ��ͨ����DFT�����趨����Ӧ��������;
extern void Measure_SetData(WORD wIndexDFT,MyData* pdata);
//˵��:����ָ��ͨ���������ݵ�ƽ��ֵ;
extern WORD Measure_GetAnalogWaveAvg(WORD wIndexDFT);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__MEASURE_H*/

/******************************************************************************
ģ�鹦��:
ʵ�ֲ�������,���Զ�����DFT����;
ʹ�ò���:
1.ָ��Ӳ��ͨ����;
2.����CMyMeasure��ʵ��,���������:g_measure;
3.��g_app.OnInitParams()�е���OnInitParams();
4.��g_app.OnInit()�е���OnInit();
5.��g_app.OnTimer10ms()�е���OnTimer10ms(),���ڼ���DFT���ݺ�ͨ���Լ�;
6.Ӧ�ó����ͨ��SetData()������õ���DFT�����趨����Ӧ��������;
*/
//ThinkBoy,ShenBo,2006/04/30;
