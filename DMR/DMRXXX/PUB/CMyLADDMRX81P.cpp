#include <Main.h>


//-----------------------------------------------------------------------------
void CMyLADDMRX81P::iiiSetStatusLAD(WORD wBitID,WORD wStatus)
{
	CMyLADDMR::iiiSetStatusLAD(wBitID,wStatus);
	switch(wBitID+1)
	{
	case 21: if(wStatus==LAD_1111) g_app.LADHandClose(); break;
	case 22: if(wStatus==LAD_1111) g_app.LADHandOpen(); break;
	case 23: g_app.LADEnableLocal((wStatus==LAD_1111)?TRUE:FALSE); break;
	case 24: g_app.LADEnableRemote((wStatus==LAD_1111)?TRUE:FALSE); break;
	case 25: if(wStatus==LAD_1111) g_breaker.m_wLockClose = 0xaaaa; break;
	case 26: g_app.LADEnableAuto((wStatus==LAD_1111)?TRUE:FALSE); break;
	}
}

CMyData* CMyLADDMRX81P::iiiGetAnalogData(WORD wIndex)
{
	switch(wIndex)
	{
	case  0: return &g_data1XUa;
	case  1: return &g_data1XUb;
	case  2: return &g_data1XUc;
	case  3: return &g_data1XUab;
	case  4: return &g_data1XUbc;
	case  5: return &g_data1XUca;
	case  6: return &g_data1X3U0;
	case  7: return &g_data1X3U2;
	case  8: return &g_data1XF;
	case  9: return &g_data2XUa;
	case 10: return &g_data2XUb;
	case 11: return &g_data2XUc;
	case 12: return &g_data2XUab;
	case 13: return &g_data2XUbc;
	case 14: return &g_data2XUca;
	case 15: return &g_data2X3U0;
	case 16: return &g_data2X3U2;
	case 17: return &g_data2XF;
	}
	return NULL;
}
