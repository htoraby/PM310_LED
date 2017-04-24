#include <Main.h>

CMyComm_iVEX g_comm1;
CMyComm_iVEX g_comm2;
WORD g_wRateF = 0;

WORD g_wProtocolType = 0;

DEVICETIME g_GPSTime;
GPSERR g_GPSErr;

//-----------------------------------------------------------------------------
void CMyHDIFDMR::OnInit1(void)
{
	m_wFreqINT1 = 5000;
	m_wFreqINT2 = 5000;
// 	m_wPanelDiagCode = 0x0055;
	m_wPWRUPS = POWERUPS;
	memset(&g_GPSTime,0,sizeof(DEVICETIME));
	g_GPSErr.dwCodeErrCnt = 0;
	g_GPSErr.dwCodeErrTotal = 0;
	g_GPSErr.dwCodeCnt = 0;
	g_GPSErr.nTimeOut = GPSTIMEOUT;
}

void CMyHDIFDMR::OnInit2(void)
{
	g_comm1.SetComm(&g_pComm1);
	g_comm2.SetComm(&g_pComm2);
	g_comm1.OnInit();
	g_comm2.OnInit();
}

void CMyHDIFDMR::OnPollingComm(void)
{
	g_comm1.OnPolling();
	g_comm2.OnPolling();
}

void CMyHDIFDMR::OnPollingCommET(void)
{

}

void CMyHDIFDMR::OnTimer10ms(void)
{
	g_comm1.OnTimer10ms();
	g_comm2.OnTimer10ms();
}

WORD CMyHDIFDMR::GetFreqINT1(void)
{
	return m_wFreqINT1;
}

WORD CMyHDIFDMR::GetFreqINT2(void)
{
	return m_wFreqINT2;
}

WORD CMyHDIFDMR::GetPanelDiagCode(void)
{
	return m_wPanelDiagCode;
}

void CMyHDIFDMR::RestExProtocol(void)
{
	return;
}

void CMyHDIFDMR::InitCom(WORD wIndex)
{
	return;
}