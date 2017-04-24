#ifndef __MEASURE_H
#define __MEASURE_H

#ifndef DFT_CHANNEL_HARD
#define DFT_CHANNEL_HARD	8		//A/D硬件通道数;
#endif

//-----------------------------------------------------------------------------
typedef struct _DFTDATA
{
	short nR;						//实部;
	short nX;						//虚部;
	short nData;					//有效值;
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
	short nRegulateR;				//校正系数实部;
	short nRegulateX;				//校正系数虚部;
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
//说明:计算负序值,若计算正序值,只需将A和C的位置互换即可;
//WORD CalculateNegSeq(MyData* pDataA,MyData* pDataB,MyData* pDataC);
//WORD CalculateNegSeqEx(MyData* pDataAB,MyData* pDataBC);
extern WORD Measure_CalculateNegSeq(MyData* pDataA,MyData* pDataB,MyData* pDataC);
extern WORD Measure_CalculateNegSeqEx(MyData* pDataAB,MyData* pDataBC);

extern REGULATESET g_regulateSet;			//校正系数,包括幅值校正和相位校正;
extern ANALOGWAVE g_analogWave;				//实时波形数据;
extern WORD g_wErrorAD;
extern DFTDATASET g_dftDataSet;

extern void Measure_StartReg(void);
extern BOOL Measure_GetRegStatus(void);
//说明:初始化参数程序;
extern void Measure_OnInitParams(void);
//说明:初始化程序;
extern void Measure_OnInit(void);
//说明:定时服务程序(严格)调用,用于计算DFT;
extern void Measure_OnTimer10ms(void);
//说明:计算均方根值,其计算结果的通过pData返回;
// extern void Measure_CalculateRMS(WORD wIndexDFT,WORD* pData);
//说明:计算基波,其计算结果的实部和虚部通过pDataR和pDataX返回;
extern void Measure_CalculateDFT1(WORD wIndexDFT,short* pDataR,short* pDataX);
//说明:计算wTHD次谐波,其计算结果的实部和虚部通过pDataR和pDataX返回;
//extern void Measure_CalculateDFTn(WORD wIndexDFT,WORD wTHD,short* pDataR,short* pDataX);
//说明:将指定通道的DFT数据设定到对应的数据中;
extern void Measure_SetData(WORD wIndexDFT,MyData* pdata);
//说明:计算指定通道波形数据的平均值;
extern WORD Measure_GetAnalogWaveAvg(WORD wIndexDFT);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__MEASURE_H*/

/******************************************************************************
模块功能:
实现测量管理,能自动计算DFT数据;
使用步骤:
1.指定硬件通道数;
2.创建CMyMeasure的实例,建议变量名:g_measure;
3.在g_app.OnInitParams()中调用OnInitParams();
4.在g_app.OnInit()中调用OnInit();
5.在g_app.OnTimer10ms()中调用OnTimer10ms(),用于计算DFT数据和通道自检;
6.应用程序可通过SetData()将计算得到的DFT数据设定到对应的数据中;
*/
//ThinkBoy,ShenBo,2006/04/30;
