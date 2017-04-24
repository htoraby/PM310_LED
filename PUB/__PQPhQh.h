#ifndef __PQPHQH_H
#define __PQPHQH_H

#ifdef __cplusplus
extern "C" {
#endif

extern short g_nPa;				//A相有功功率;
extern short g_nPb;				//B相有功功率;
extern short g_nPc;				//C相有功功率;
extern short g_nQa;				//A相无功功率;
extern short g_nQb;				//B相无功功率;
extern short g_nQc;				//C相无功功率;
extern short g_nPFa;			//A相功率因数;
extern short g_nPFb;			//A相功率因数;
extern short g_nPFc;			//A相功率因数;
extern short g_nPabc;			//三相有功功率;
extern short g_nQabc;			//三相无功功率;
extern short g_nPFabc;			//三相功率因数;
extern DWORD g_dwPhImpW10ms;	//本10ms间隔内正向有功电度;
extern DWORD g_dwQhImpW10ms;	//本10ms间隔内正向无功电度;
extern DWORD g_dwPhExpW10ms;	//本10ms间隔内反向有功电度;
extern DWORD g_dwQhExpW10ms;	//本10ms间隔内反向无功电度;

//-----------------------------------------------------------------------------
extern void PQ_CalculatePQ(MyData* pDataI,MyData* pDataU,long* pP,long* pQ);
extern short PQ_GetPF(short nP,short nQ);
extern void PQ_Calculate1(MyData* pDataIa,MyData* pDataIb,MyData* pDataIc,
				   MyData* pDataUa,MyData* pDataUb,MyData* pDataUc,
				   WORD wScale2IM,WORD wScale2Uln,BOOL bSinglePhase);
	//说明:计算三相功率;bSinglePhase=TRUE表示要求计算单相功率,否则只计算三相功率;
extern void PQ_Calculate2(MyData* pDataIa,MyData* pDataIc,
				   MyData* pDataUab,MyData* pDataUbc,
				   WORD wScale2IM,WORD wScale2Uln);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__PQPHQH_H*/

/******************************************************************************
模块功能:
需要__Measure.*模块配合;在g_app.OnTimer10ms()中直接创建实例pqphqh,并调用pqphqh.Calculate()函数,
结果通过pqphqh的内部成员变量访问;
额定三相视在功率(二次),单位W,Se=(wScale2IM*0.01)*(wScale2Uln*0.01)*3;
实际的A相二次有功功率:Pa(W)=m_nPa/3000*Se;
实际的B相二次有功功率:Pb(W)=m_nPb/3000*Se;
实际的C相二次有功功率:Pc(W)=m_nPc/3000*Se;
实际的A相二次无功功率:Qa(W)=m_nQa/3000*Se;
实际的B相二次无功功率:Qb(W)=m_nQb/3000*Se;
实际的C相二次无功功率:Qc(W)=m_nQc/3000*Se;
实际的三相二次有功功率:P(W)=m_nPabc/3000*Se;
实际的三相二次无功功率:Q(W)=m_nQabc/3000*Se;
*/
//ThinkBoy,ShenBo,2006/04/30;
