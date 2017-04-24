#include <Main.h>


//-----------------------------------------------------------------------------
void CMyLADDMRX01P::iiiSetStatusLAD(WORD wBitID,WORD wStatus)
{
	CMyLADDMRUnit::iiiSetStatusLAD(wBitID,wStatus);
	switch(wBitID+1)
	{
	case 26: if(wStatus==LAD_1111) g_protect.m_piCHZ.Discharge(); break;
	case 27: if(wStatus==LAD_1111) g_protect.m_piCHZ.SetAllowFlag(); break;
	case 28: if(wStatus==LAD_1111) g_protect.m_piBZT.Discharge(); break;
	case 29: g_protect.m_piBZT.ForceLine1LostPower(wStatus==LAD_1111); break;
	case 30: g_protect.m_piBZT.ForceLine2HavePower(wStatus==LAD_1111); break;
	case 31: if(wStatus==LAD_1111) g_protect.m_piGR.OnInit(); break;
	}
}

