#ifndef __PQPHQH_H
#define __PQPHQH_H

#ifdef __cplusplus
extern "C" {
#endif

extern short g_nPa;				//A���й�����;
extern short g_nPb;				//B���й�����;
extern short g_nPc;				//C���й�����;
extern short g_nQa;				//A���޹�����;
extern short g_nQb;				//B���޹�����;
extern short g_nQc;				//C���޹�����;
extern short g_nPFa;			//A�๦������;
extern short g_nPFb;			//A�๦������;
extern short g_nPFc;			//A�๦������;
extern short g_nPabc;			//�����й�����;
extern short g_nQabc;			//�����޹�����;
extern short g_nPFabc;			//���๦������;
extern DWORD g_dwPhImpW10ms;	//��10ms����������й����;
extern DWORD g_dwQhImpW10ms;	//��10ms����������޹����;
extern DWORD g_dwPhExpW10ms;	//��10ms����ڷ����й����;
extern DWORD g_dwQhExpW10ms;	//��10ms����ڷ����޹����;

//-----------------------------------------------------------------------------
extern void PQ_CalculatePQ(MyData* pDataI,MyData* pDataU,long* pP,long* pQ);
extern short PQ_GetPF(short nP,short nQ);
extern void PQ_Calculate1(MyData* pDataIa,MyData* pDataIb,MyData* pDataIc,
				   MyData* pDataUa,MyData* pDataUb,MyData* pDataUc,
				   WORD wScale2IM,WORD wScale2Uln,BOOL bSinglePhase);
	//˵��:�������๦��;bSinglePhase=TRUE��ʾҪ����㵥�๦��,����ֻ�������๦��;
extern void PQ_Calculate2(MyData* pDataIa,MyData* pDataIc,
				   MyData* pDataUab,MyData* pDataUbc,
				   WORD wScale2IM,WORD wScale2Uln);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__PQPHQH_H*/

/******************************************************************************
ģ�鹦��:
��Ҫ__Measure.*ģ�����;��g_app.OnTimer10ms()��ֱ�Ӵ���ʵ��pqphqh,������pqphqh.Calculate()����,
���ͨ��pqphqh���ڲ���Ա��������;
��������ڹ���(����),��λW,Se=(wScale2IM*0.01)*(wScale2Uln*0.01)*3;
ʵ�ʵ�A������й�����:Pa(W)=m_nPa/3000*Se;
ʵ�ʵ�B������й�����:Pb(W)=m_nPb/3000*Se;
ʵ�ʵ�C������й�����:Pc(W)=m_nPc/3000*Se;
ʵ�ʵ�A������޹�����:Qa(W)=m_nQa/3000*Se;
ʵ�ʵ�B������޹�����:Qb(W)=m_nQb/3000*Se;
ʵ�ʵ�C������޹�����:Qc(W)=m_nQc/3000*Se;
ʵ�ʵ���������й�����:P(W)=m_nPabc/3000*Se;
ʵ�ʵ���������޹�����:Q(W)=m_nQabc/3000*Se;
*/
//ThinkBoy,ShenBo,2006/04/30;
