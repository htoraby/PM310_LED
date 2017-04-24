#include <Main.h>


//-----------------------------------------------------------------------------
void CMyTableDMRUnit::ControlOut(WORD wControlOutCode,WORD wCommand)
{
	CMyTableDMR::ControlOut(wControlOutCode,wCommand);
	if(wControlOutCode==CONTROLOUT_KOC)
	{
		if(wCommand==0xaaaa && (g_deviceInfo.wDeviceStatus2&DS2_EnableRemote))
		{
			g_breaker.m_lockRemote.Unlock1();
			g_breaker.RemoteClose();
			g_breaker.m_lockRemote.Lock1();
		}
		return;
	}
	if(wControlOutCode==CONTROLOUT_KOT)
	{
		if(wCommand==0xaaaa && (g_deviceInfo.wDeviceStatus2&DS2_EnableRemote))
		{
			g_breaker.m_lockRemote.Unlock1();
			g_breaker.RemoteOpen();
			g_breaker.m_lockRemote.Lock1();
		}
		return;
	}
}
