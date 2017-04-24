/*
;*****************************************************************************************************
;*						Copyright (c) 2009 by ThinkBoy. 
;*						All rights reserved.
;*
;* Header:
;* File Name: 
;* Author: jimmy
;* Date:
;*****************************************************************************************************
;*/

#include <main.h>

const char g_szDCLinkData[][5] = 
{
	"----","  Ia","  Ib","  Ic"," 3I0","  Ua","  Ub","  Uc"," Uab"," Ubc"," Uca"," 3U0","   P","   Q","  PF","Freq"
};

//====================================================================================================
void CMyDCProcessDMR450F::GetLinkData(WORD wDataIndex,WORD &wData,WORD &wScale)
{
	WORD wDataT = 0;
// ==========for debug=========
// 	wDataT = 1500;
// ==========for debug=========

	WORD wScaleT = 3000;
	switch(wDataIndex)
	{
	case DCLINK_Ia: wDataT = g_dataIa.m_nDataAvg; break;
	case DCLINK_Ib: wDataT = g_dataIb.m_nDataAvg; break;
	case DCLINK_Ic: wDataT = g_dataIc.m_nDataAvg; break;
	case DCLINK_3I0: wDataT = g_data3I0.m_nDataAvg;
		if(wDataT>3000) wDataT = 3000;
		break;
	case DCLINK_Ua: wDataT = g_dataUa.m_nDataAvg; break;
	case DCLINK_Ub: wDataT = g_dataUb.m_nDataAvg; break;
	case DCLINK_Uc: wDataT = g_dataUc.m_nDataAvg; break;
	case DCLINK_Uab: wDataT = g_dataUab.m_nDataAvg;
		if(wDataT>5196) wDataT = 5196;
		wScaleT = 5196;
		break;
	case DCLINK_Ubc: wDataT = g_dataUbc.m_nDataAvg;
		if(wDataT>5196) wDataT = 5196;
		wScaleT = 5196;
		break;
	case DCLINK_Uca: wDataT = g_dataUca.m_nDataAvg;
		if(wDataT>5196) wDataT = 5196;
		wScaleT = 5196;
		break;
	case DCLINK_3U0: wDataT = g_data3U0.m_nDataAvg;
		if(wDataT>3000) wDataT = 3000;
		wScaleT = 3000;
		break;
	case DCLINK_P: wDataT = g_dataP.m_nDataAvg; break;
	case DCLINK_Q: wDataT = g_dataQ.m_nDataAvg; break;
	case DCLINK_PF: wDataT = g_dataPF.m_nDataAvg; wScaleT = 10000; break;
	case DCLINK_Freq:wDataT = g_dataF.m_nDataAvg;
		if(wDataT>6500) wData = 6500;
		wScaleT = 6500;
		break;
	}

	wData = wDataT;
	wScale = wScaleT;
}


/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/

