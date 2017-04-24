#include <Main.h>

short g_nPa;			//A相有功功率;
short g_nPb;			//B相有功功率;
short g_nPc;			//C相有功功率;
short g_nQa;			//A相无功功率;
short g_nQb;			//B相无功功率;
short g_nQc;			//C相无功功率;
short g_nPFa;			//A相功率因数;
short g_nPFb;			//A相功率因数;
short g_nPFc;			//A相功率因数;
short g_nPabc;			//三相有功功率;
short g_nQabc;			//三相无功功率;
short g_nPFabc;			//三相功率因数;
DWORD g_dwPhImpW10ms;	//本10ms间隔内正向有功电度;
DWORD g_dwQhImpW10ms;	//本10ms间隔内正向无功电度;
DWORD g_dwPhExpW10ms;	//本10ms间隔内反向有功电度;
DWORD g_dwQhExpW10ms;	//本10ms间隔内反向无功电度;

//-----------------------------------------------------------------------------
short PQ_FormatToShort(long lPQ)
{
    lPQ += (lPQ>0)?6144L:-6144L;
    return (short)(lPQ/12288L);
}

//-----------------------------------------------------------------------------
void PQ_CalculatePQ(MyData* pDataI,MyData* pDataU,long* pP,long* pQ)
{
	if(pDataI==NULL||pDataU==NULL)
	{
		*pP = 0;
		*pQ = 0;
		return;
	}
	if(pDataI->m_nData==0||pDataU->m_nData==0)
	{
		*pP = 0;
		*pQ = 0;
		return;
	}
	*pP = (long)(pDataU->m_nR)*(long)(pDataI->m_nR)+(long)(pDataU->m_nX)*(long)(pDataI->m_nX);
	*pQ = (long)(pDataU->m_nX)*(long)(pDataI->m_nR)-(long)(pDataU->m_nR)*(long)(pDataI->m_nX);
}

short PQ_GetPF(short nP,short nQ)
{
	if(nP==0) return 0;
	if(nQ==0)
	{
		if(nP>=0) return 10000;
		return -10000;
	}
	return (short)(80000L*(long)nP/GetSqrtX((short)(nP<<3),(short)(nQ<<3)));
}

void PQ_Calculate1(MyData* pDataIa,MyData* pDataIb,MyData* pDataIc,
						  MyData* pDataUa,MyData* pDataUb,MyData* pDataUc,
						  WORD wScale2IM,WORD wScale2Uln,BOOL bSinglePhase)
{
	long lPa,lPb,lPc,lPabc;
	long lQa,lQb,lQc,lQabc;
	DWORD dwScale2PQ;
	DWORD dwTempP;
	DWORD dwTempQ;

	PQ_CalculatePQ(pDataIa,pDataUa,&lPa,&lQa);
	PQ_CalculatePQ(pDataIb,pDataUb,&lPb,&lQb);
	PQ_CalculatePQ(pDataIc,pDataUc,&lPc,&lQc);
	lPabc = lPa+lPb+lPc;
	lQabc = lQa+lQb+lQc;
	if(bSinglePhase)
	{
		g_nPa = PQ_FormatToShort(lPa);
		g_nPb = PQ_FormatToShort(lPb);
		g_nPc = PQ_FormatToShort(lPc);
		g_nQa = PQ_FormatToShort(lQa);
		g_nQb = PQ_FormatToShort(lQb);
		g_nQc = PQ_FormatToShort(lQc);
		g_nPFa = PQ_GetPF(g_nPa,g_nQa);
		g_nPFb = PQ_GetPF(g_nPa,g_nQa);
		g_nPFc = PQ_GetPF(g_nPa,g_nQa);
	}
	else
	{
		g_nPa = 0;
		g_nPb = 0;
		g_nPc = 0;
		g_nQa = 0;
		g_nQb = 0;
		g_nQc = 0;
		g_nPFa = 0;
		g_nPFb = 0;
		g_nPFc = 0;
	}
	g_nPabc = PQ_FormatToShort(lPabc);
	g_nQabc = PQ_FormatToShort(lQabc);
	g_nPFabc = PQ_GetPF(g_nPabc,g_nQabc);
	dwScale2PQ = (DWORD)wScale2IM*(DWORD)wScale2Uln*3L/100L;
	dwTempP = (g_nPabc<0)?(DWORD)(-g_nPabc):(DWORD)g_nPabc;
	dwTempQ = (g_nQabc<0)?(DWORD)(-g_nQabc):(DWORD)g_nQabc;
	dwTempP = (dwTempP*dwScale2PQ+2048L)/4096L;
	dwTempQ = (dwTempQ*dwScale2PQ+2048L)/4096L;
	if(g_nPabc<0)
	{
		g_dwPhImpW10ms = 0;
		g_dwPhExpW10ms = dwTempP;
	}
	else
	{
		g_dwPhImpW10ms = dwTempP;
		g_dwPhExpW10ms = 0;
	}
	if(g_nQabc<0)
	{
		g_dwQhImpW10ms = 0;
		g_dwQhExpW10ms = dwTempQ;
	}
	else
	{
		g_dwQhImpW10ms = dwTempQ;
		g_dwQhExpW10ms = 0;
	}
}

void PQ_Calculate2(MyData* pDataIa,MyData* pDataIc,
						  MyData* pDataUab,MyData* pDataUbc,
						  WORD wScale2IM,WORD wScale2Uln)
{
	long lP1,lP2,lPabc;
	long lQ1,lQ2,lQabc;
	MyData DataUcb;
	DWORD dwScale2PQ;
	DWORD dwTempP;
	DWORD dwTempQ;

	Data_SetData3(&DataUcb,-pDataUbc->m_nR,-pDataUbc->m_nX,pDataUbc->m_nData);
	PQ_CalculatePQ(pDataIa,pDataUab,&lP1,&lQ1);
	PQ_CalculatePQ(pDataIc,&DataUcb,&lP2,&lQ2);
	lPabc = lP1+lP2;
	lQabc = lQ1+lQ2;
	g_nPabc = PQ_FormatToShort(lPabc);
	g_nQabc = PQ_FormatToShort(lQabc);
	g_nPFabc = PQ_GetPF(g_nPabc,g_nQabc);
	dwScale2PQ = (DWORD)wScale2IM*(DWORD)wScale2Uln*3L/100L;
	dwTempP = (g_nPabc<0)?(DWORD)(-g_nPabc):(DWORD)g_nPabc;
	dwTempQ = (g_nQabc<0)?(DWORD)(-g_nQabc):(DWORD)g_nQabc;
	dwTempP = (dwTempP*dwScale2PQ+2048L)/4096L;
	dwTempQ = (dwTempQ*dwScale2PQ+2048L)/4096L;
	if(g_nPabc<0)
	{
		g_dwPhImpW10ms = 0;
		g_dwPhExpW10ms = dwTempP;
	}
	else
	{
		g_dwPhImpW10ms = dwTempP;
		g_dwPhExpW10ms = 0;
	}
	if(g_nQabc<0)
	{
		g_dwQhImpW10ms = 0;
		g_dwQhExpW10ms = dwTempQ;
	}
	else
	{
		g_dwQhImpW10ms = dwTempQ;
		g_dwQhExpW10ms = 0;
	}
}

