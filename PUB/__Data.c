#include <Main.h>

//-----------------------------------------------------------------------------
void Filter_OnInit(MyFilter* pthis)
{
	MemoryClear((WORD*)&pthis->m_nData,FILTER_DEPTH);
	pthis->m_wCurPos = 0;
	pthis->m_bStarted = FALSE;
}

void Filter_AddData(MyFilter* pthis,short nData)
{
	WORD i;
	if(pthis->m_bStarted)
	{
		pthis->m_wCurPos++;
		pthis->m_wCurPos %= FILTER_DEPTH;
		pthis->m_nData[pthis->m_wCurPos] = nData;
	}
	else
	{
		for(i=0;i<FILTER_DEPTH;i++) pthis->m_nData[i] = nData;
	}
	pthis->m_bStarted = TRUE;
}

short Filter_GetData(MyFilter* pthis,BOOL bThresholdProcess)
{
	WORD i;
	short nData;
	long lAddSum;

	lAddSum = 0;
	for(i=0;i<FILTER_DEPTH;i++) lAddSum += pthis->m_nData[i];
	if(lAddSum>=0) lAddSum += FILTER_DEPTH/2;
	else lAddSum -= FILTER_DEPTH/2;
	nData = (short)(lAddSum/FILTER_DEPTH);
	if(bThresholdProcess)
	{
		if(nData<=MEASURE_THRESHOLD && nData>=-MEASURE_THRESHOLD) nData = 0;
	}
	return nData;
}

BOOL g_bAddFilter;
static char s_szUnitageText[32];

//-----------------------------------------------------------------------------
void Data_OnInit(MyData* pthis)
{
	g_bAddFilter = FALSE;
	pthis->m_nR = 0;
	pthis->m_nX = 0;
	pthis->m_nData = 0;
	pthis->m_nDataAvg = 0;
	pthis->m_wIndexDFT = 0xffff;
	pthis->m_dwScaleSecondaryFix = 10000;
	pthis->m_dwScaleSecondary = 10000;
	pthis->m_dwScalePrimary = 10000;
	pthis->m_wFormatSecondary = 0x52;
	pthis->m_wFormatPrimary = 0x52;
	pthis->m_dwDataSecondary = 0L;
	pthis->m_dwDataPrimary = 0L;
	pthis->m_pszName = NULL;
	pthis->m_pszUnitage = NULL;
	Filter_OnInit(&pthis->m_filter);
}

void Data_SetMetrics(MyData* pthis,DWORD dwScaleSecondary,DWORD dwScale,char* pszName,char* pszUnitage)
{
	WORD wFormatPrimary;
	DWORD dwScalePrimary;
	DWORD dwTemp;

	pthis->m_pszName = pszName;
	pthis->m_pszUnitage = pszUnitage;
	pthis->m_dwScaleSecondaryFix = dwScaleSecondary;
	if(dwScaleSecondary<=2000L)
	{
		pthis->m_wFormatSecondary = 0x0053;
		pthis->m_dwScaleSecondary = dwScaleSecondary*10L;
	}
	else if(dwScaleSecondary<=20000L)
	{
		pthis->m_wFormatSecondary = 0x0052;
		pthis->m_dwScaleSecondary = dwScaleSecondary;
	}
	else if(dwScaleSecondary<=200000L)
	{
		pthis->m_wFormatSecondary = 0x0051;
		pthis->m_dwScaleSecondary = dwScaleSecondary/10L;
	}
	else
	{
		pthis->m_wFormatSecondary = 0x0060;
		pthis->m_dwScaleSecondary = dwScaleSecondary/100L;
	}
	wFormatPrimary = 0x0000;
	dwScalePrimary = dwScaleSecondary*dwScale;
	if(dwScaleSecondary>=dwScale) dwScaleSecondary /= 10L;
	else dwScale /= 10L;
	if(dwScaleSecondary>=dwScale) dwScaleSecondary /= 10L;
	else dwScale /= 10L;
	if(dwScaleSecondary>=dwScale) dwScaleSecondary /= 10L;
	else dwScale /= 10L;
	dwTemp = dwScaleSecondary*dwScale;
	if(dwTemp>=4000000L)
	{
		wFormatPrimary = 0x4000;
		dwScalePrimary = dwTemp;
	}
	if(dwScalePrimary>200000L)
	{
		wFormatPrimary += 0x4000;
		dwScalePrimary /= 1000L;
	}
	if(dwScalePrimary<=2000L)
	{
		pthis->m_wFormatPrimary = wFormatPrimary+0x0053;
		pthis->m_dwScalePrimary = dwScalePrimary*10L;
	}
	else if(dwScalePrimary<=20000L)
	{
		pthis->m_wFormatPrimary = wFormatPrimary+0x0052;
		pthis->m_dwScalePrimary = dwScalePrimary;
	}
	else if(dwScalePrimary<=200000L)
	{
		pthis->m_wFormatPrimary = wFormatPrimary+0x0051;
		pthis->m_dwScalePrimary = dwScalePrimary/10L;
	}
	else
	{
		pthis->m_wFormatPrimary = wFormatPrimary+0x0060;
		pthis->m_dwScalePrimary = dwScalePrimary/100L;
	}
}

void Data_SetData1(MyData* pthis,short nData)
{
	pthis->m_nData = nData;
	if(g_bAddFilter) Filter_AddData(&pthis->m_filter,nData);
}

void Data_SetData2(MyData* pthis,short nR,short nX)
{
	pthis->m_nR = nR;
	pthis->m_nX = nX;
	Data_SetData1(pthis,(short)GetSqrtX(nR,nX));
}

void Data_SetData3(MyData* pthis,short nR,short nX,short nData)
{
	pthis->m_nR = nR;
	pthis->m_nX = nX;
	Data_SetData1(pthis,nData);
}

DWORD Data_GetDataSecondary(MyData* pthis,short nData,BOOL bSignedType)
{
	WORD wData;
	DWORD dwDataSecondary;

	wData = (WORD)((nData>=0)?nData:(-nData));
	dwDataSecondary = ((DWORD)wData*pthis->m_dwScaleSecondary+2048)/4096;
	if(bSignedType) dwDataSecondary += (nData<0)?0xc0000000:0x80000000;
	return dwDataSecondary;
}

DWORD Data_GetDataPrimary(MyData* pthis,short nData,BOOL bSignedType)
{
	WORD wData;
	DWORD dwDataPrimary;

	wData = (WORD)((nData>=0)?nData:(-nData));
	dwDataPrimary = ((DWORD)wData*pthis->m_dwScalePrimary+2048)/4096;
	if(bSignedType) dwDataPrimary += (nData<0)?0xc0000000:0x80000000;
	return dwDataPrimary;
}

short Data_RefreshData(MyData* pthis,BOOL bSignedType)
{
	pthis->m_nDataAvg = Filter_GetData(&pthis->m_filter,!bSignedType);
	pthis->m_dwDataSecondary = Data_GetDataSecondary(pthis,pthis->m_nDataAvg,bSignedType);
	pthis->m_dwDataPrimary = Data_GetDataPrimary(pthis,pthis->m_nDataAvg,bSignedType);
	return pthis->m_nDataAvg;
}

WORD Data_GetValueSecondaryFix1(MyData* pthis)
{
	WORD wData = (WORD)((pthis->m_nData>=0)?pthis->m_nData:(-pthis->m_nData));
	return (WORD)(((DWORD)wData*pthis->m_dwScaleSecondaryFix+2048)/4096);
}

WORD Data_GetValueSecondaryFix2(MyData* pthis,WORD wData)
{
	return (WORD)(((DWORD)wData*pthis->m_dwScaleSecondaryFix+2048)/4096);
}

char* Data_GetUnitageText(MyData* pthis,char* pszText)
{
	char* pszTemp;
	pszTemp = &s_szUnitageText[0];
	*pszTemp = 0;
	if(pthis->m_pszUnitage==NULL) return s_szUnitageText;
	while(*pszText)
	{
		if(pszTemp>=&s_szUnitageText[24]) break;
		if(*pszText=='%')
		{
			if(*(pszText+1)=='S')
			{
				StringCopy(pszTemp,pthis->m_pszUnitage);
				pszTemp += GetStringLength(pthis->m_pszUnitage);
				pszText += 2;
				continue;
			}
			if(*(pszText+1)=='P')
			{
				if((pthis->m_wFormatPrimary&0xc000)==0x4000) *pszTemp++ = 'k';
				if((pthis->m_wFormatPrimary&0xc000)==0x8000) *pszTemp++ = 'M';
				StringCopy(pszTemp,pthis->m_pszUnitage);
				pszTemp += GetStringLength(pthis->m_pszUnitage);
				pszText += 2;
				continue;
			}
		}
		*pszTemp++ = *pszText++;
	}
	*pszTemp++ = 0;
	return s_szUnitageText;
}

