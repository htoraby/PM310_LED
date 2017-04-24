#ifndef __Data_H
#define __Data_H

#ifndef MEASURE_THRESHOLD
#define MEASURE_THRESHOLD	9		//模拟量计算阈值;
#endif
#ifndef FILTER_DEPTH
#define FILTER_DEPTH		20		//滤波器深度;
#endif

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
typedef struct _MYFILTER
{
	short m_nData[FILTER_DEPTH];	//滤波器数据队列;
	WORD m_wCurPos;					//滤波器新数据的当前当前位置;
	BOOL m_bStarted;				//滤波器是否启动;
}MyFilter;


//说明:初始化程序;
extern void Filter_OnInit(MyFilter* pthis);
//说明:加入新的数据;
extern void Filter_AddData(MyFilter* pthis,short nData);
//说明:得到软件滤波器的平均值,bThresholdProcess:是否需要阈值处理;
extern short Filter_GetData(MyFilter* pthis,BOOL bThresholdProcess);


//-----------------------------------------------------------------------------
typedef struct _MYDATA
{
	short m_nR;					//实部;
	short m_nX;					//虚部;
	short m_nData;				//当前值;
	short m_nDataAvg;			//经数据滤波器处理后的平均值;
	WORD m_wIndexDFT;			//硬件AD通道;
	DWORD m_dwScaleSecondaryFix;//二次测量量程(按0x52固定显示格式,对应3000);
	DWORD m_dwScaleSecondary;	//二次测量量程(按二次侧值显示格式,对应3000);
	DWORD m_dwScalePrimary;		//一次测量量程(按一次侧值显示格式,对应3000);
	WORD m_wFormatSecondary;	//二次侧值显示格式;
	WORD m_wFormatPrimary;		//一次侧值显示格式;
	DWORD m_dwDataSecondary;	//二次侧值(按二次侧值显示格式);
	DWORD m_dwDataPrimary;		//一次侧值(按一次侧值显示格式);
	char* m_pszName;			//数据名称;
	char* m_pszUnitage;			//数据单位(二次侧);
	MyFilter m_filter;			//数据滤波器;
}MyData;

//说明:初始化程序;
extern void Data_OnInit(MyData* pthis);
//说明:设定二次测量量程(格式为小数点后两位),变比,名称和单位;
extern void Data_SetMetrics(MyData* pthis,DWORD dwScaleSecondary,DWORD dwScale,char* pszName,char* pszUnitage);
//说明:直接设定数据,通过数值计算的数据类型,如PF,F等;
extern void Data_SetData1(MyData* pthis,short nData);
//说明:通过实部和虚部来设定数据,用于通过矢量计算的数据类型,如P,Q,Uab等;
extern void Data_SetData2(MyData* pthis,short nR,short nX);
//说明:通过实部,虚部和幅值来设定数据,用于硬件通道的数据类型,如IA,Ua等;
extern void Data_SetData3(MyData* pthis,short nR,short nX,short nData);
//说明:按本数据的显示格式,得到指定数据值的二次侧显示值;
extern DWORD Data_GetDataSecondary(MyData* pthis,short nData,BOOL bSignedType);
//说明:按本数据的显示格式,得到指定数据值的一次侧显示值;
extern DWORD Data_GetDataPrimary(MyData* pthis,short nData,BOOL bSignedType);
//说明:从数据滤波器中得到平均值,并刷新其它相关数据,bSignedType:是否有+/-符号;
extern short Data_RefreshData(MyData* pthis,BOOL bSignedType);
//说明:得到当前数据的二次值,格式为小数点后两位;
extern WORD Data_GetValueSecondaryFix1(MyData* pthis);
//说明:得到指定数据的二次值,格式为小数点后两位;
extern WORD Data_GetValueSecondaryFix2(MyData* pthis,WORD wData);
//说明:得到数据单位,自动将%S转换为二次侧数据单位,将%P转换为一次侧数据单位;
extern char* Data_GetUnitageText(MyData* pthis,char* pszText);

extern BOOL g_bAddFilter;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__Data_H*/
/******************************************************************************
模块功能:
实现数据管理,能自动采用数据滤波器,并产生数据的显示格式;
使用步骤:
1.指定数据计算阈值(缺省为9,即9/3000=0.3%)和滤波器深度(缺省为20=400ms);
2.创建CMyData的实例,建议变量名:g_dataXXX;
3.在g_app.OnInit()中调用各数据的OnInit();
4.在g_app.OnTimer10ms()中重复调用SetMetrics(),以防内部参数被异常修改;
5.在g_app.OnTimer10ms()中根据针对不同数据调用SetData()的三个版本;
6.在g_app.OnTimer1000ms()中将调用RefreshData()进行数据更新,生成显示格式;
7.在数据显示程序中可直接使用指定格式的显示一次侧或二次侧数据;
8.其它用户程序可使用GetValueSecondaryFix()取得二次值;
*/
//ThinkBoy,ShenBo,2006/04/30;
