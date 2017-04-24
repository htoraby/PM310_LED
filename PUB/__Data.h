#ifndef __Data_H
#define __Data_H

#ifndef MEASURE_THRESHOLD
#define MEASURE_THRESHOLD	9		//ģ����������ֵ;
#endif
#ifndef FILTER_DEPTH
#define FILTER_DEPTH		20		//�˲������;
#endif

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
typedef struct _MYFILTER
{
	short m_nData[FILTER_DEPTH];	//�˲������ݶ���;
	WORD m_wCurPos;					//�˲��������ݵĵ�ǰ��ǰλ��;
	BOOL m_bStarted;				//�˲����Ƿ�����;
}MyFilter;


//˵��:��ʼ������;
extern void Filter_OnInit(MyFilter* pthis);
//˵��:�����µ�����;
extern void Filter_AddData(MyFilter* pthis,short nData);
//˵��:�õ�����˲�����ƽ��ֵ,bThresholdProcess:�Ƿ���Ҫ��ֵ����;
extern short Filter_GetData(MyFilter* pthis,BOOL bThresholdProcess);


//-----------------------------------------------------------------------------
typedef struct _MYDATA
{
	short m_nR;					//ʵ��;
	short m_nX;					//�鲿;
	short m_nData;				//��ǰֵ;
	short m_nDataAvg;			//�������˲���������ƽ��ֵ;
	WORD m_wIndexDFT;			//Ӳ��ADͨ��;
	DWORD m_dwScaleSecondaryFix;//���β�������(��0x52�̶���ʾ��ʽ,��Ӧ3000);
	DWORD m_dwScaleSecondary;	//���β�������(�����β�ֵ��ʾ��ʽ,��Ӧ3000);
	DWORD m_dwScalePrimary;		//һ�β�������(��һ�β�ֵ��ʾ��ʽ,��Ӧ3000);
	WORD m_wFormatSecondary;	//���β�ֵ��ʾ��ʽ;
	WORD m_wFormatPrimary;		//һ�β�ֵ��ʾ��ʽ;
	DWORD m_dwDataSecondary;	//���β�ֵ(�����β�ֵ��ʾ��ʽ);
	DWORD m_dwDataPrimary;		//һ�β�ֵ(��һ�β�ֵ��ʾ��ʽ);
	char* m_pszName;			//��������;
	char* m_pszUnitage;			//���ݵ�λ(���β�);
	MyFilter m_filter;			//�����˲���;
}MyData;

//˵��:��ʼ������;
extern void Data_OnInit(MyData* pthis);
//˵��:�趨���β�������(��ʽΪС�������λ),���,���ƺ͵�λ;
extern void Data_SetMetrics(MyData* pthis,DWORD dwScaleSecondary,DWORD dwScale,char* pszName,char* pszUnitage);
//˵��:ֱ���趨����,ͨ����ֵ�������������,��PF,F��;
extern void Data_SetData1(MyData* pthis,short nData);
//˵��:ͨ��ʵ�����鲿���趨����,����ͨ��ʸ���������������,��P,Q,Uab��;
extern void Data_SetData2(MyData* pthis,short nR,short nX);
//˵��:ͨ��ʵ��,�鲿�ͷ�ֵ���趨����,����Ӳ��ͨ������������,��IA,Ua��;
extern void Data_SetData3(MyData* pthis,short nR,short nX,short nData);
//˵��:�������ݵ���ʾ��ʽ,�õ�ָ������ֵ�Ķ��β���ʾֵ;
extern DWORD Data_GetDataSecondary(MyData* pthis,short nData,BOOL bSignedType);
//˵��:�������ݵ���ʾ��ʽ,�õ�ָ������ֵ��һ�β���ʾֵ;
extern DWORD Data_GetDataPrimary(MyData* pthis,short nData,BOOL bSignedType);
//˵��:�������˲����еõ�ƽ��ֵ,��ˢ�������������,bSignedType:�Ƿ���+/-����;
extern short Data_RefreshData(MyData* pthis,BOOL bSignedType);
//˵��:�õ���ǰ���ݵĶ���ֵ,��ʽΪС�������λ;
extern WORD Data_GetValueSecondaryFix1(MyData* pthis);
//˵��:�õ�ָ�����ݵĶ���ֵ,��ʽΪС�������λ;
extern WORD Data_GetValueSecondaryFix2(MyData* pthis,WORD wData);
//˵��:�õ����ݵ�λ,�Զ���%Sת��Ϊ���β����ݵ�λ,��%Pת��Ϊһ�β����ݵ�λ;
extern char* Data_GetUnitageText(MyData* pthis,char* pszText);

extern BOOL g_bAddFilter;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__Data_H*/
/******************************************************************************
ģ�鹦��:
ʵ�����ݹ���,���Զ����������˲���,���������ݵ���ʾ��ʽ;
ʹ�ò���:
1.ָ�����ݼ�����ֵ(ȱʡΪ9,��9/3000=0.3%)���˲������(ȱʡΪ20=400ms);
2.����CMyData��ʵ��,���������:g_dataXXX;
3.��g_app.OnInit()�е��ø����ݵ�OnInit();
4.��g_app.OnTimer10ms()���ظ�����SetMetrics(),�Է��ڲ��������쳣�޸�;
5.��g_app.OnTimer10ms()�и�����Բ�ͬ���ݵ���SetData()�������汾;
6.��g_app.OnTimer1000ms()�н�����RefreshData()�������ݸ���,������ʾ��ʽ;
7.��������ʾ�����п�ֱ��ʹ��ָ����ʽ����ʾһ�β����β�����;
8.�����û������ʹ��GetValueSecondaryFix()ȡ�ö���ֵ;
*/
//ThinkBoy,ShenBo,2006/04/30;
