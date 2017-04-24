#ifndef __EDIT_H
#define __EDIT_H

#ifndef EDIT_COUNTMAX
#define EDIT_COUNTMAX		6		//指定页面中最大的可编辑项,缺省为6;
#endif
#ifndef EDIT_ENUMSZMAX
#define EDIT_ENUMSZMAX		16		//指定枚举类型可编辑项的可枚举数目,缺省为16;
#endif
#ifndef EDIT_BUFFERSIZE
#define EDIT_BUFFERSIZE		64
#endif

#define PASSWORD_NULL		0		//口令不正确;
#define PASSWORD_LEVEL1		1		//允许低级(操作级)的授权;
#define PASSWORD_LEVEL2		2		//允许中级(管理级)的授权;
#define PASSWORD_LEVEL3		3		//允许高级(系统级)的授权;

extern BOOL g_IsSetTime;

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
typedef struct _MyEdit
{
	WORD m_wMode;					//编辑项模式;
	WORD m_wPosX;					//编辑项X坐标;
	WORD m_wPosY;					//编辑项Y坐标;
	WORD m_wColor;					//编辑项颜色;
	BOOL m_bLargeFont;				//编辑项字体;
	WORD* m_pData;					//编辑项数据指针;
}MyEdit;

#define INHERIT_FROM_MyEdit			\
		WORD m_wMode;				\
		WORD m_wPosX;				\
		WORD m_wPosY;				\
		WORD m_wColor;				\
		BOOL m_bLargeFont;			\
		WORD* m_pData

//说明:创建编辑项;
extern BOOL Edit_OnCreate(MyEdit* pthis,WORD wMode,WORD* pData);
//说明:闪烁指定的字符下的光标;
extern void Edit_RefreshShining(MyEdit* pthis,WORD wAsciiIndex);


//-----------------------------------------------------------------------------
typedef struct _MyEditEnum
{
	INHERIT_FROM_MyEdit;
	WORD m_wData;					//编辑项暂存数据,无须关心;
	WORD m_wCountEnum;				//枚举类型的最大枚举项,须赋值;
	WORD m_wCountChar;				//枚举类型的最大字符数,须赋值;
	char* m_pszEnum[EDIT_ENUMSZMAX];//枚举类型的所有枚举项文本,须赋值;
}MyEditEnum;

#define INHERIT_FROM_MyEditEnum		\
	INHERIT_FROM_MyEdit;			\
	WORD m_wData;					\
	WORD m_wCountEnum;				\
	WORD m_wCountChar;				\
	char* m_pszEnum[EDIT_ENUMSZMAX];

//说明:创建枚举类型的编辑项;
extern BOOL EditEnum_OnCreate(MyEditEnum* pthis,WORD wMode,WORD* pData);
//说明:显示枚举类型的编辑项,bCurSel:是否选中,若选中则自动向上移动一个点;
extern void EditEnum_Display(MyEditEnum* pthis,BOOL bCurSel);
//说明:闪烁整个编辑项下的光标;
extern void EditEnum_RefreshShining(MyEditEnum* pthis);
//说明:进入编辑状态的初始化;
extern void EditEnum_EnterEditing(MyEditEnum* pthis);
//说明:按键处理;
extern void EditEnum_OnKeyMsg(MyEditEnum* pthis,WORD wKeyCode,WORD* wEditStatus);
//说明:返回字符个数,用于显示光标;
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
	DWORD m_dwData;					//编辑项暂存数据,无须关心;
	DWORD m_dwDataMin;				//编辑数据下限,须赋值;
	DWORD m_dwDataMax;				//编辑数据上限,须赋值;
	WORD m_wFormat;					//编辑数据的格式,参见__LCDXX.h的FormatReal()的说明,须赋值;
	BOOL m_bReserveZero;			//在非编辑状态显示时,是否前边填零,须赋值;
	WORD m_wEditDataBCD;			//当前编辑位置,无须关心;
}MyEditData;

//说明:创建数据类型的编辑项;
extern BOOL EditData_OnCreate(MyEditData* pthis,WORD wMode,WORD* pData);
//说明:显示数据类型的编辑项,bCurSel:是否选中,若选中则自动向上移动一个点;
extern void EditData_Display(MyEditData* pthis,BOOL bCurSel);
//说明:闪烁当前编辑数字下的光标;
extern void EditData_RefreshShining(MyEditData* pthis);
//说明:进入编辑状态的初始化;
extern void EditData_EnterEditing(MyEditData* pthis);
//说明:按键处理;
extern void EditData_OnKeyMsg(MyEditData* pthis,WORD wKeyCode,WORD* wEditStatus);
//说明:返回字符个数,用于显示光标;
extern WORD EditData_GetCountChar(MyEditData* pthis);
//说明:运行时格式转化为编辑时格式;
extern void EditData_RuntimeDataToEditData(MyEditData* pthis);
//说明:编辑时格式转化为运行时格式;
extern void EditData_EditDataToRuntimeData(MyEditData* pthis);


//-----------------------------------------------------------------------------
// typedef struct _MyEditBin
// {
// 	INHERIT_FROM_MyEditData;
// }MyEditBin;
// 
// //说明:进入编辑状态的初始化
// extern void EditBin_EnterEditing(MyEditBin* pthis);
// //说明:显示数据类型的编辑项,bCurSel:是否选中,若选中则自动向上移动一个点;
// extern void EditBin_Display(MyEditBin* pthis,BOOL bCurSel);
// //说明:按键处理;
// extern void EditBin_OnKeyMsg(MyEditBin* pthis,WORD wKeyCode,WORD& wEditStatus);

//----------------------------------------------------------------------------

// 	WORD m_wEditBuffer[EDIT_COUNTMAX][EDIT_BUFFERSIZE];
// 	WORD m_wEditCount;				//编辑项个数;
// 	WORD m_wEditCurSel;				//当前选中的编辑项;
// 	WORD m_wEditStatus;				//当前编辑状态;

extern MyEditEnum* EditG_GetEditEnumCurSel(void);
extern MyEditEnumHz* EditG_GetEditEnumHzCurSel(void);
extern MyEditData* EditG_GetEditDataCurSel(void);
extern void EditG_AddEdit(WORD wMode,WORD* pData);
extern void EditG_EditCursorON(void);
//说明:初始化程序;
extern void EditG_OnInit(void);
//说明:增加多选枚举类型编辑项,pData:被编辑数据的指针;
extern void EditG_AddEditEnumMul(WORD* pData);
extern void EditG_AddEditEnumHzMul(WORD* pData);
//说明:增加字数值类型编辑项,pData:被编辑数据的指针;
extern void EditG_AddEditDataWord(WORD* pData);
//说明:增加双字数值类型编辑项,pData:被编辑数据的指针;
extern void EditG_AddEditDataDWord(DWORD* pData);
//执行外部刷新处理;
extern void EditG_OnRefreshPage(void);
//进入编辑使能状态;
extern void EditG_EnableEdit(WORD wRefreshMode);
//按键响应处理;
extern WORD EditG_OnKeyMsg(WORD wKeyCode);
//说明:执行编辑时光标闪烁;
extern void EditG_OnTimer250ms(void);
//说明:设定投退枚举类型编辑项;
extern void EditG_SetEditEnumMetricsTog(void);
//说明:设定多选枚举类型编辑项;
extern void EditG_SetEditEnumMetricsMul(WORD wCountEnum,WORD wCountChar,char* pszEnum);
extern void EditG_SetEditEnumHzMetricsMul(WORD wCountEnum,WORD wCountChar,char* pszEnum);
//说明:设定整数数值类型编辑项;
extern void EditG_SetEditDataMetricsInteger(WORD wDataMin,WORD wDataMax,BOOL bReserveZero);
//说明:设定实数数值类型编辑项;
extern void EditG_SetEditDataMetricsReal(DWORD dwDataMin,DWORD dwDataMax,WORD wFormat);
// 说明:设定整数数值类型编辑项;
// extern void EditG_SetEditDataMetricsBin(WORD wDataMin,WORD wDataMax);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__EDIT_H*/

/******************************************************************************
模块功能:
主要实现对各种需要编辑功能的支持,如设备参数修改,保护投退,定值修改,口令输入等等;
用户程序通过AddEditXXXXXXX()函数将编辑项加入到页中,若未执行EnableEdit(),则这些
加入的编辑项仅支持显示,否则支持编辑修改;用户程序必须在页面显示程序中对加入的编
辑项实现对应的GetEditMetrics(pData)的设置;
使用步骤:
1.根据应用要求定义EDIT_COUNTMAX和EDIT_ENUMSZMAX;
2.创建CMyEditGroup的实例,建议变量名:g_edit;
3.在HMI程序中实现GetEditMetrics()函数,以得到编辑项的相关场境;
4.在显示页面开始调用OnInit(),通过AddEditXXXXXXX()函数加入各编辑项;
5.根据是否支持修改功能决定是否调用EnableEdit();
6.在g_app.OnTimer250ms()中调用OnTimer250ms(),以支持光标闪烁;
7.实现g_app.OnUpdateDevice()函数,以支持参数修改;
*/
//ThinkBoy,ShenBo,2006/04/30;
