#ifndef __EDIT_H
#define __EDIT_H

#ifndef EDIT_COUNTMAX
#define EDIT_COUNTMAX		6		//ָ��ҳ�������Ŀɱ༭��,ȱʡΪ6;
#endif
#ifndef EDIT_ENUMSZMAX
#define EDIT_ENUMSZMAX		16		//ָ��ö�����Ϳɱ༭��Ŀ�ö����Ŀ,ȱʡΪ16;
#endif
#ifndef EDIT_BUFFERSIZE
#define EDIT_BUFFERSIZE		64
#endif

#define PASSWORD_NULL		0		//�����ȷ;
#define PASSWORD_LEVEL1		1		//����ͼ�(������)����Ȩ;
#define PASSWORD_LEVEL2		2		//�����м�(����)����Ȩ;
#define PASSWORD_LEVEL3		3		//����߼�(ϵͳ��)����Ȩ;

extern BOOL g_IsSetTime;

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
typedef struct _MyEdit
{
	WORD m_wMode;					//�༭��ģʽ;
	WORD m_wPosX;					//�༭��X����;
	WORD m_wPosY;					//�༭��Y����;
	WORD m_wColor;					//�༭����ɫ;
	BOOL m_bLargeFont;				//�༭������;
	WORD* m_pData;					//�༭������ָ��;
}MyEdit;

#define INHERIT_FROM_MyEdit			\
		WORD m_wMode;				\
		WORD m_wPosX;				\
		WORD m_wPosY;				\
		WORD m_wColor;				\
		BOOL m_bLargeFont;			\
		WORD* m_pData

//˵��:�����༭��;
extern BOOL Edit_OnCreate(MyEdit* pthis,WORD wMode,WORD* pData);
//˵��:��˸ָ�����ַ��µĹ��;
extern void Edit_RefreshShining(MyEdit* pthis,WORD wAsciiIndex);


//-----------------------------------------------------------------------------
typedef struct _MyEditEnum
{
	INHERIT_FROM_MyEdit;
	WORD m_wData;					//�༭���ݴ�����,�������;
	WORD m_wCountEnum;				//ö�����͵����ö����,�븳ֵ;
	WORD m_wCountChar;				//ö�����͵�����ַ���,�븳ֵ;
	char* m_pszEnum[EDIT_ENUMSZMAX];//ö�����͵�����ö�����ı�,�븳ֵ;
}MyEditEnum;

#define INHERIT_FROM_MyEditEnum		\
	INHERIT_FROM_MyEdit;			\
	WORD m_wData;					\
	WORD m_wCountEnum;				\
	WORD m_wCountChar;				\
	char* m_pszEnum[EDIT_ENUMSZMAX];

//˵��:����ö�����͵ı༭��;
extern BOOL EditEnum_OnCreate(MyEditEnum* pthis,WORD wMode,WORD* pData);
//˵��:��ʾö�����͵ı༭��,bCurSel:�Ƿ�ѡ��,��ѡ�����Զ������ƶ�һ����;
extern void EditEnum_Display(MyEditEnum* pthis,BOOL bCurSel);
//˵��:��˸�����༭���µĹ��;
extern void EditEnum_RefreshShining(MyEditEnum* pthis);
//˵��:����༭״̬�ĳ�ʼ��;
extern void EditEnum_EnterEditing(MyEditEnum* pthis);
//˵��:��������;
extern void EditEnum_OnKeyMsg(MyEditEnum* pthis,WORD wKeyCode,WORD* wEditStatus);
//˵��:�����ַ�����,������ʾ���;
extern WORD EditEnum_GetCountChar(MyEditEnum* pthis);

//-----------------------------------------------------------------------------
typedef struct _MyEditEnumHz
{
	INHERIT_FROM_MyEditEnum
}MyEditEnumHz;

extern void EditEnumHz_Display(MyEditEnumHz* pthis,BOOL bCurSel);
extern void EditEnumHz_RefreshShining1(MyEditEnumHz* pthis,WORD wIndex);
extern void EditEnumHz_RefreshShining(MyEditEnumHz* pthis);
extern void EditEnumHz_EnterEditing(MyEditEnumHz* pthis);
extern void EditEnumHz_OnKeyMsg(MyEditEnumHz* pthis,WORD wKeyCode,WORD* wEditStatus);

//-----------------------------------------------------------------------------
typedef struct _MyEditData
{
	INHERIT_FROM_MyEdit;
	DWORD m_dwData;					//�༭���ݴ�����,�������;
	DWORD m_dwDataMin;				//�༭��������,�븳ֵ;
	DWORD m_dwDataMax;				//�༭��������,�븳ֵ;
	WORD m_wFormat;					//�༭���ݵĸ�ʽ,�μ�__LCDXX.h��FormatReal()��˵��,�븳ֵ;
	BOOL m_bReserveZero;			//�ڷǱ༭״̬��ʾʱ,�Ƿ�ǰ������,�븳ֵ;
	WORD m_wEditDataBCD;			//��ǰ�༭λ��,�������;
}MyEditData;

//˵��:�����������͵ı༭��;
extern BOOL EditData_OnCreate(MyEditData* pthis,WORD wMode,WORD* pData);
//˵��:��ʾ�������͵ı༭��,bCurSel:�Ƿ�ѡ��,��ѡ�����Զ������ƶ�һ����;
extern void EditData_Display(MyEditData* pthis,BOOL bCurSel);
//˵��:��˸��ǰ�༭�����µĹ��;
extern void EditData_RefreshShining(MyEditData* pthis);
//˵��:����༭״̬�ĳ�ʼ��;
extern void EditData_EnterEditing(MyEditData* pthis);
//˵��:��������;
extern void EditData_OnKeyMsg(MyEditData* pthis,WORD wKeyCode,WORD* wEditStatus);
//˵��:�����ַ�����,������ʾ���;
extern WORD EditData_GetCountChar(MyEditData* pthis);
//˵��:����ʱ��ʽת��Ϊ�༭ʱ��ʽ;
extern void EditData_RuntimeDataToEditData(MyEditData* pthis);
//˵��:�༭ʱ��ʽת��Ϊ����ʱ��ʽ;
extern void EditData_EditDataToRuntimeData(MyEditData* pthis);


//-----------------------------------------------------------------------------
// typedef struct _MyEditBin
// {
// 	INHERIT_FROM_MyEditData;
// }MyEditBin;
// 
// //˵��:����༭״̬�ĳ�ʼ��
// extern void EditBin_EnterEditing(MyEditBin* pthis);
// //˵��:��ʾ�������͵ı༭��,bCurSel:�Ƿ�ѡ��,��ѡ�����Զ������ƶ�һ����;
// extern void EditBin_Display(MyEditBin* pthis,BOOL bCurSel);
// //˵��:��������;
// extern void EditBin_OnKeyMsg(MyEditBin* pthis,WORD wKeyCode,WORD& wEditStatus);

//----------------------------------------------------------------------------

// 	WORD m_wEditBuffer[EDIT_COUNTMAX][EDIT_BUFFERSIZE];
// 	WORD m_wEditCount;				//�༭�����;
// 	WORD m_wEditCurSel;				//��ǰѡ�еı༭��;
// 	WORD m_wEditStatus;				//��ǰ�༭״̬;

extern MyEditEnum* EditG_GetEditEnumCurSel(void);
extern MyEditEnumHz* EditG_GetEditEnumHzCurSel(void);
extern MyEditData* EditG_GetEditDataCurSel(void);
extern void EditG_AddEdit(WORD wMode,WORD* pData);
extern void EditG_EditCursorON(void);
//˵��:��ʼ������;
extern void EditG_OnInit(void);
//˵��:���Ӷ�ѡö�����ͱ༭��,pData:���༭���ݵ�ָ��;
extern void EditG_AddEditEnumMul(WORD* pData);
extern void EditG_AddEditEnumHzMul(WORD* pData);
//˵��:��������ֵ���ͱ༭��,pData:���༭���ݵ�ָ��;
extern void EditG_AddEditDataWord(WORD* pData);
//˵��:����˫����ֵ���ͱ༭��,pData:���༭���ݵ�ָ��;
extern void EditG_AddEditDataDWord(DWORD* pData);
//ִ���ⲿˢ�´���;
extern void EditG_OnRefreshPage(void);
//����༭ʹ��״̬;
extern void EditG_EnableEdit(WORD wRefreshMode);
//������Ӧ����;
extern WORD EditG_OnKeyMsg(WORD wKeyCode);
//˵��:ִ�б༭ʱ�����˸;
extern void EditG_OnTimer250ms(void);
//˵��:�趨Ͷ��ö�����ͱ༭��;
extern void EditG_SetEditEnumMetricsTog(void);
//˵��:�趨��ѡö�����ͱ༭��;
extern void EditG_SetEditEnumMetricsMul(WORD wCountEnum,WORD wCountChar,char* pszEnum);
extern void EditG_SetEditEnumHzMetricsMul(WORD wCountEnum,WORD wCountChar,char* pszEnum);
//˵��:�趨������ֵ���ͱ༭��;
extern void EditG_SetEditDataMetricsInteger(WORD wDataMin,WORD wDataMax,BOOL bReserveZero);
//˵��:�趨ʵ����ֵ���ͱ༭��;
extern void EditG_SetEditDataMetricsReal(DWORD dwDataMin,DWORD dwDataMax,WORD wFormat);
// ˵��:�趨������ֵ���ͱ༭��;
// extern void EditG_SetEditDataMetricsBin(WORD wDataMin,WORD wDataMax);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__EDIT_H*/

/******************************************************************************
ģ�鹦��:
��Ҫʵ�ֶԸ�����Ҫ�༭���ܵ�֧��,���豸�����޸�,����Ͷ��,��ֵ�޸�,��������ȵ�;
�û�����ͨ��AddEditXXXXXXX()�������༭����뵽ҳ��,��δִ��EnableEdit(),����Щ
����ı༭���֧����ʾ,����֧�ֱ༭�޸�;�û����������ҳ����ʾ�����жԼ���ı�
����ʵ�ֶ�Ӧ��GetEditMetrics(pData)������;
ʹ�ò���:
1.����Ӧ��Ҫ����EDIT_COUNTMAX��EDIT_ENUMSZMAX;
2.����CMyEditGroup��ʵ��,���������:g_edit;
3.��HMI������ʵ��GetEditMetrics()����,�Եõ��༭�����س���;
4.����ʾҳ�濪ʼ����OnInit(),ͨ��AddEditXXXXXXX()����������༭��;
5.�����Ƿ�֧���޸Ĺ��ܾ����Ƿ����EnableEdit();
6.��g_app.OnTimer250ms()�е���OnTimer250ms(),��֧�ֹ����˸;
7.ʵ��g_app.OnUpdateDevice()����,��֧�ֲ����޸�;
*/
//ThinkBoy,ShenBo,2006/04/30;
