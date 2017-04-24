#include <Main.h>


//-----------------------------------------------------------------------------
WORD CMyHDIFDMRX01P::GetFreqINT1(void)
{
#ifdef DFT_Ua
	if(g_dataUa.m_nData>60||g_dataUc.m_nData>60) return m_wFreqINT1;
#endif
	return 0;
}

WORD CMyHDIFDMRX01P::GetFreqINT2(void)
{
#ifdef DFT_Ux
	if(g_dataUx.m_nData>60) return m_wFreqINT2;
#endif
#ifdef DFT_Uxa
	if(g_dataUxa.m_nData>60||g_dataUxc.m_nData>60) return m_wFreqINT2;
#endif
	return 0;
}

