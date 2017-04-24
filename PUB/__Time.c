#include <Main.h>

const DEVICETIME c_timeInit = 
{
	0,1,1,0,0,0,0
};

static WORD s_wCountReadBackupTime;		//保存和重读控制;
DEVICETIME g_deviceTime;

//-----------------------------------------------------------------------------
WORD Time_GetDayOfMonth(WORD wYear,WORD wMonth)
{
	switch(wMonth)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2: return (wYear%4==0)?29:28;
	default: return 31;
	}
}

BOOL Time_IsTimeOK(DEVICETIME* pDeviceTime)
{
	if(pDeviceTime==NULL) return FALSE;
	if(pDeviceTime->wYear>50) return FALSE;
	if(pDeviceTime->wMonth-1>11) return FALSE;
	if(pDeviceTime->wDay-1>Time_GetDayOfMonth(pDeviceTime->wYear,pDeviceTime->wMonth)-1) return FALSE;
	if(pDeviceTime->wHour>23) return FALSE;
	if(pDeviceTime->wMinute>59) return FALSE;
	if(pDeviceTime->wSecond>59) return FALSE;
	if(pDeviceTime->wMilliSecond>999) return FALSE;
	return TRUE;
}


//-----------------------------------------------------------------------------
void Time_OnInit(void)
{
	g_deviceTime = c_timeInit;
	RTC_OnInit(&c_timeInit);
	RTC_ReadTime(&g_deviceTime);
	if(!Time_IsTimeOK(&g_deviceTime)) g_deviceTime = c_timeInit;
	s_wCountReadBackupTime = 0;
}

void Time_OnTimer1ms(void)
{
	g_deviceTime.wMilliSecond++;
	if(g_deviceTime.wMilliSecond>999)
	{
		g_deviceTime.wMilliSecond = 0;
		g_deviceTime.wSecond++;
		if(g_deviceTime.wSecond>59)
		{
			g_deviceTime.wSecond = 0;
			g_deviceTime.wMinute++;
			if(g_deviceTime.wMinute>59)
			{
				g_deviceTime.wMinute = 0;
				g_deviceTime.wHour++;
				if(g_deviceTime.wHour>23)
				{
					g_deviceTime.wHour = 0;
					g_deviceTime.wDay++;
					if(g_deviceTime.wDay>Time_GetDayOfMonth(g_deviceTime.wYear,g_deviceTime.wMonth))
					{
						g_deviceTime.wDay = 1;
						g_deviceTime.wMonth++;
						if(g_deviceTime.wMonth>12)
						{
							g_deviceTime.wMonth = 1;
							g_deviceTime.wYear++;
						}
					}
				}
			}
		}
	}
}

void Time_OnTimer1000ms(void)
{
	if(s_wCountReadBackupTime==0xffff)
	{
		if(Time_IsTimeOK(&g_deviceTime)) RTC_WriteTime(&g_deviceTime);
	}
	s_wCountReadBackupTime++;
	if(s_wCountReadBackupTime>=1800)
	{
		s_wCountReadBackupTime = 0;
		RTC_ReadTime(&g_deviceTime);
	}
}

void Time_OnUpdateDevice(WORD* pData)
{
	if(pData>=(WORD*)&g_deviceTime && (pData<(WORD*)&g_deviceTime+SIZEOFWORD(DEVICETIME)))
	{
		s_wCountReadBackupTime = 0xffff;
	}
}

BOOL Time_IsFlashing(void)
{
	return (g_deviceTime.wMilliSecond<450)?TRUE:FALSE;
}
