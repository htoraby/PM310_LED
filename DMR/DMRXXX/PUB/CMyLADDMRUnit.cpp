#include <Main.h>


//-----------------------------------------------------------------------------
void CMyLADDMRUnit::iiiSetStatusLAD(WORD wBitID,WORD wStatus)
{
	CMyLADDMR::iiiSetStatusLAD(wBitID,wStatus);
	switch(wBitID+1)
	{
	case 21: if(wStatus==LAD_1111) g_protect.m_wProtectCloseFlag = 0xaaaa; break;
	case 22: if(wStatus==LAD_1111) g_protect.m_wProtectOpenFlag = 0xaaaa; break;
	case 23: g_app.LADEnableLocal((wStatus==LAD_1111)?TRUE:FALSE); break;
	case 24: g_app.LADEnableRemote((wStatus==LAD_1111)?TRUE:FALSE); break;
	case 25: g_breaker.m_wLockClose = (wStatus==LAD_1111)?0xaaaa:0x0000; break;
	}
}

CMyData* CMyLADDMRUnit::iiiGetAnalogData(WORD wIndex)
{
	switch(wIndex)
	{
	case  0: return &g_dataIa;
	case  1: return &g_dataIb;
	case  2: return &g_dataIc;
	case  3: return &g_dataIA;
	case  4: return &g_dataIB;
	case  5: return &g_dataIC;
	case  6: return &g_dataUa;
	case  7: return &g_dataUb;
	case  8: return &g_dataUc;
	case  9: return &g_dataUab;
	case 10: return &g_dataUbc;
	case 11: return &g_dataUca;
	case 12: return &g_data3I0;
	case 13: return &g_data3I2;
	case 14: return &g_data3U0;
	case 15: return &g_data3U2;
	case 16: return &g_dataF;
	case 17: return &g_dataP;
	case 18: return &g_dataQ;
	case 19: return &g_dataPF;
	case 20: return &g_dataIx;
	case 21: return &g_dataUxab;
	case 22: return &g_dataUxbc;
	case 23: return &g_dataUxca;
	case 24: return &g_data3Ux2;
	case 25: return &g_dataFx;
	}
	return NULL;
}
