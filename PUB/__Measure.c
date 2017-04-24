#include <Main.h>

// #ifndef _WIN32
// #pragma DATA_SECTION(g_analogWave,"DMABuff");
// #endif
ANALOGWAVE g_analogWave;			//实时波形数据;
REGULATESET g_regulateSet;
WORD g_wErrorAD;

static WORD s_wCountErrorAD;
static DFTDATASET s_dftDataSetOrg;
DFTDATASET g_dftDataSet;			//DFT处理结果数据;

static BOOL s_bAutoRegulate;
static short s_nRegCnt = 0;
static long s_lR[DFT_CHANNEL_HARD];
static long s_lX[DFT_CHANNEL_HARD];


/*======================================*/
/* U1:正序,U2:负序,U0:零序              */
/*                                      */
/* | U1 |         | 1  a  a2| | Ua |    */
/* | U2 | = 1/3 * | 1  a2 a | | Ub |    */
/* | U0 |         | 1  1  1 | | Uc |    */
/*                                      */
/* a  = e^j120°= -1/2 + j3^0.5/2       */
/* a2 = e^j240°= -1/2 - j3^0.5/2       */
/*                                      */
/* | U1 |         | 1  a2 0 | | Uab |   */
/* | U2 | = 1/3 * | 1  a  0 | | Ucb |   */
/* | U0 |         | 0  0  1 | | 3U0 |   */
/*                                      */
/* 1+a+a2=0                             */
/*======================================*/

//-----------------------------------------------------------------------------
WORD Measure_CalculateNegSeq(MyData* pDataA,MyData* pDataB,MyData* pDataC)
{
	short nRa,nRb,nRc,nR;
	short nXa,nXb,nXc,nX;
	nRa = pDataA->m_nR;
	nXa = pDataA->m_nX;
	nRc = pDataC->m_nR;
	nXc = pDataC->m_nX;
	if(pDataB==NULL)
	{
		nRb = -(nRa+nRc);
		nXb = -(nXa+nXc);
	}
	else
	{
		nRb = pDataB->m_nR;
		nXb = pDataB->m_nX;
	}
	nR = nRa-(nRb+nRc)/2+(short)(((long)(nXb-nXc)*433 + ((nXb-nXc>0)?250:-250))/500);
	nX = nXa-(nXc+nXb)/2+(short)(((long)(nRc-nRb)*433 + ((nRc-nRb>0)?250:-250))/500);
	return GetSqrtX(nR,nX);
}

WORD Measure_CalculateNegSeqEx(MyData* pDataAB,MyData* pDataBC)
{
	short nRab,nRbc,nR;
	short nXab,nXbc,nX;

	nRab = pDataAB->m_nR;
	nXab = pDataAB->m_nX;
	nRbc = pDataBC->m_nR;
	nXbc = pDataBC->m_nX;

	nR = nRab + nRbc/2 + (short)(((long)nXbc * 433 + ((nXbc>0)?250:-250)) / 500);
	nX = nXab + nXbc/2 - (short)(((long)nRbc * 433 + ((nRbc>0)?250:-250)) / 500);
	return GetSqrtX(nR,nX);
}


//-----------------------------------------------------------------------------
void Measure_OnInitParams(void)
{
	WORD i;
	for(i=0;i<DFT_CHANNEL_HARD;i++)
	{
		g_regulateSet.regulate[i].nRegulateR = 10000;
		g_regulateSet.regulate[i].nRegulateX = 0;
	}
}

void Measure_OnInit(void)
{
	WORD i;
	WORD j;
	for(i=0;i<DFT_CHANNEL_HARD;i++)
	{
		for(j=0;j<DFT_DOTNUM;j++) g_analogWave.wData[i][j] = 2000;
	}
	MemoryClear((WORD*)&s_dftDataSetOrg,SIZEOFWORD(s_dftDataSetOrg));
    MemoryClear((WORD*)&g_dftDataSet,SIZEOFWORD(g_dftDataSet));
	s_wCountErrorAD = 0;
	g_wErrorAD = 0;
}

void Measure_StartReg(void)
{
    short i;
    s_bAutoRegulate = TRUE;
    s_nRegCnt = 0;

    for(i=0;i<DFT_CHANNEL_HARD;i++)
    {
        s_lR[i] = 0;
        s_lX[i] = 0;
    }
}

BOOL Measure_GetRegStatus(void)
{
    return s_bAutoRegulate;
}

void Measure_OnRegulate(REGULATE* pRef)
{
    short i;
    REGULATE Ref;
    WORD wRefA;
    long lR, lX;
    BOOL bRegOk = FALSE;
    
    if(s_bAutoRegulate==FALSE) return;
    if(s_nRegCnt++<100)
    {
        for(i=0;i<DFT_CHANNEL_HARD;i++)
        {
            s_lR[i] += (long)s_dftDataSetOrg.dftdata[i].nR;
            s_lX[i] += (long)s_dftDataSetOrg.dftdata[i].nX;
        }
        return;
    }

    for(i=0;i<DFT_CHANNEL_HARD;i++)
    {
        s_lR[i] += (s_lR[i]>=0)?50L:-50L;
        s_lX[i] += (s_lX[i]>=0)?50L:-50L;
        s_lR[i] /= 100L;
        s_lX[i] /= 100L;
    }

    Ref.nRegulateR = (short)s_lR[DFT_Ua];
    Ref.nRegulateX = (short)s_lX[DFT_Ua];
    wRefA = GetSqrtX(Ref.nRegulateR, Ref.nRegulateX);
    lR = (long)Ref.nRegulateR*10000L/wRefA;
    lX = (long)Ref.nRegulateX*10000L/wRefA;
    Ref.nRegulateR = (short)lR;
    Ref.nRegulateX = (short)lX;

    for(i=0;i<DFT_CHANNEL_HARD;i++)
    {
        lR = (s_lR[i]*(long)Ref.nRegulateR + s_lX[i]*(long)Ref.nRegulateX);       // /10000L;
        lX = (s_lX[i]*(long)Ref.nRegulateR - s_lR[i]*(long)Ref.nRegulateX);       // /10000L;
        lR += (lR>=0)?5000L:-5000L;
        lX += (lX>=0)?5000L:-5000L;
        lR /= 10000L;
        lX /= 10000L;

        if(lR!=0 || lX!=0)
        {
            long lReR,lReX,lReA, lReA2;
            lReA = (lR*lR + lX*lX + 50L)/100L;
            lReR = ((long)pRef[i].nRegulateR*lR + (long)pRef[i].nRegulateX*lX)*100L;    // /lReA;
            lReX = ((long)pRef[i].nRegulateX*lR - (long)pRef[i].nRegulateR*lX)*100L;    // /lReA;
            lReA2 = (long)((DWORD)lReA>>1);
            lReR += (lReR>=0)?lReA2:-lReA2;
            lReX += (lReX>=0)?lReA2:-lReA2;
            lReR /= lReA;
            lReX /= lReA;

            if((lReR>=8500 && lReR<=25000)
                && (lReX>=-870 && lReX<=870))
            {
                g_regulateSet.regulate[i].nRegulateR = (short)lReR;
                g_regulateSet.regulate[i].nRegulateX = (short)lReX;
                bRegOk = TRUE;
            }
        }
    }

    if(bRegOk) MyApp_OnUpdateDevice((WORD*)&g_regulateSet, (g_deviceInfo.wSwitchStatus1&0x100)==0x100);
    MyHMI_TestLights();

    s_bAutoRegulate = FALSE;
}

void Measure_DoRegulate(void)
{
    short i;
    short nRegulateR, nRegulateX, nR, nX;
    WORD wA;
    long lR, lX;

    for(i=0;i<DFT_CHANNEL_HARD;i++)
    {
        nRegulateR = g_regulateSet.regulate[i].nRegulateR;
        nRegulateX = g_regulateSet.regulate[i].nRegulateX;
        nR = s_dftDataSetOrg.dftdata[i].nR;
        nX = s_dftDataSetOrg.dftdata[i].nX;
        lR = (long)nR*(long)nRegulateR-(long)nX*(long)nRegulateX;
        lX = (long)nX*(long)nRegulateR+(long)nR*(long)nRegulateX;
        lR += (lR>0)?5000L:-5000L;
        lX += (lX>0)?5000L:-5000L;
        nR = (short)(lR/10000L);
        nX = (short)(lX/10000L);
        wA = GetSqrtX(nR,nX);
        if(wA<= MEASURE_THRESHOLD)
        {
            nR = 0;
            nX = 0;
            wA = 0;
        }
        g_dftDataSet.dftdata[i].nR = nR;
        g_dftDataSet.dftdata[i].nX = nX;
        g_dftDataSet.dftdata[i].nData = (short)wA;
    }
}

void Measure_OnTimer10ms(void)
{
	WORD i;
// 	WORD wData;
	short nR;
	short nX;
	WORD wDataAvg;

	g_wErrorAD = 0;
	for(i=0;i<DFT_CHANNEL_HARD;i++)
	{
		nR = 0;
		nX = 0;
		Measure_CalculateDFT1(i,&nR,&nX);
        s_dftDataSetOrg.dftdata[i].nR = nR;
        s_dftDataSetOrg.dftdata[i].nX = nX;
#ifndef DISABLE_ADERROR
		wDataAvg = Measure_GetAnalogWaveAvg(i);
// #ifdef _WIN32
        if(wDataAvg<1600||wDataAvg>2500)
// #else
// 		if(wDataAvg<2300||wDataAvg>2700)
// #endif
			g_wErrorAD |= 1<<i;
#endif
	}
	if(g_wErrorAD)
	{
		if(s_wCountErrorAD<10) s_wCountErrorAD++;
		else g_deviceInfo.wDeviceStatus1 |= DS1_ErrorAD;
	}
	else
	{
		s_wCountErrorAD = 0;
		g_deviceInfo.wDeviceStatus1 &= 0xffff^DS1_ErrorAD;
	}
    Measure_OnRegulate((REGULATE*)g_Ref);
    Measure_DoRegulate();
}

void Measure_CalculateDFT1(WORD wIndexDFT,short* pDataR,short* pDataX)
{
	short nR,nX;
// 	short nRegulateR,nRegulateX;
// 	long lR,lX;

	if(wIndexDFT>=DFT_CHANNEL_HARD)
	{
		*pDataR = 0;
		*pDataX = 0;
		return;
	}
	nR = DFT_CalculateDFT1R((short*)&g_analogWave.wData[wIndexDFT][0]);
	nX = DFT_CalculateDFT1X((short*)&g_analogWave.wData[wIndexDFT][0]);
	*pDataR = nR;
	*pDataX = nX;
// 	nRegulateR = g_regulateSet.regulate[wIndexDFT].nRegulateR;
// 	nRegulateX = g_regulateSet.regulate[wIndexDFT].nRegulateX;
// 	lR = (long)nR*(long)nRegulateR-(long)nX*(long)nRegulateX;
// 	lX = (long)nX*(long)nRegulateR+(long)nR*(long)nRegulateX;
// 	lR += (lR>0)?5000L:-5000L;
// 	lX += (lX>0)?5000L:-5000L;
// 	nR = (short)(lR/10000L);
// 	nX = (short)(lX/10000L);
// 	*pDataR = (short)(lR/10000L);
// 	*pDataX = (short)(lX/10000L);
}

void Measure_SetData(WORD wIndexDFT,MyData* pdata)
{
	DFTDATA* pDFTData;
	if(wIndexDFT>=DFT_CHANNEL_HARD) return;
	pDFTData = &g_dftDataSet.dftdata[wIndexDFT];
	Data_SetData3(pdata,pDFTData->nR,pDFTData->nX,pDFTData->nData);
	pdata->m_wIndexDFT = wIndexDFT;
}

WORD Measure_GetAnalogWaveAvg(WORD wIndexDFT)
{
	WORD wDataSum;
	if(wIndexDFT>=DFT_CHANNEL_HARD) return 2000;
	wDataSum = 0;
	wDataSum += g_analogWave.wData[wIndexDFT][DFT_DOTNUM/4*0];
	wDataSum += g_analogWave.wData[wIndexDFT][DFT_DOTNUM/4*1];
	wDataSum += g_analogWave.wData[wIndexDFT][DFT_DOTNUM/4*2];
	wDataSum += g_analogWave.wData[wIndexDFT][DFT_DOTNUM/4*3];
	return (wDataSum>>2);
}
