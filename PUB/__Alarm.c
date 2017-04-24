#include <Main.h>

//-----------------------------------------------------------------------------
void Alarm_OnInit(MyAlarm* pthis)
{
	pthis->m_wCount = 0;
	pthis->m_bAlarmed = FALSE;
	pthis->m_bAlarmStarted = FALSE;
}

void Alarm_ExeDetect(MyAlarm* pthis,WORD wAlarmToggle,WORD wAlarmDelay,BOOL bAlarmValid,WORD wAlarmEventCode)
{
	pthis->m_bAlarmStarted = (bAlarmValid)?TRUE:FALSE;
	if(wAlarmToggle==TOGGLE_ON)
	{
		if(bAlarmValid)
		{
			if(pthis->m_wCount<wAlarmDelay)
			{
				pthis->m_wCount++;
				if(pthis->m_wCount>=wAlarmDelay)
				{
					if(pthis->m_bAlarmed==FALSE) Event_AddEvent(EVENTTYPE_ALARMED,wAlarmEventCode,1);
					pthis->m_bAlarmed = TRUE;
				}
			}
			else pthis->m_wCount = wAlarmDelay;
		}
		else
		{
			if(pthis->m_wCount)
			{
				if(pthis->m_wCount>100) pthis->m_wCount = 100;
				pthis->m_wCount--;
				if(pthis->m_wCount==0)
				{
					if(pthis->m_bAlarmed==TRUE) Event_AddEvent(EVENTTYPE_ALARMED,wAlarmEventCode,0);
					pthis->m_bAlarmed = FALSE;
				}
			}
		}
	}
	else
	{
		pthis->m_wCount = 0;
		pthis->m_bAlarmed = FALSE;
	}
}

void Alarm_OnReset(MyAlarm* pthis)
{
	pthis->m_wCount = 0;
	pthis->m_bAlarmed = FALSE;
	pthis->m_bAlarmStarted = FALSE;
}

// BOOL Alarm_IsAlarmed(MyAlarm* pthis)
// {
// 	return pthis->m_bAlarmed;
// }
// 
// BOOL Alarm_IsAlarmStarted(MyAlarm* pthis)
// {
// 	return pthis->m_bAlarmStarted;
// }


//-----------------------------------------------------------------------------
void AlarmG_OnInit(MyAlarmGroup3* pthis)
{
	Alarm_OnInit(&pthis->m_alarmone[0]);
	Alarm_OnInit(&pthis->m_alarmone[1]);
	Alarm_OnInit(&pthis->m_alarmone[2]);
}

void AlarmG_OnReset(MyAlarmGroup3* pthis)
{
	Alarm_OnReset(&pthis->m_alarmone[0]);
	Alarm_OnReset(&pthis->m_alarmone[1]);
	Alarm_OnReset(&pthis->m_alarmone[2]);
}

BOOL AlarmG_IsAlarmed(MyAlarmGroup3* pthis)
{
	if(pthis->m_alarmone[0].m_bAlarmed) return TRUE;
	if(pthis->m_alarmone[1].m_bAlarmed) return TRUE;
	if(pthis->m_alarmone[2].m_bAlarmed) return TRUE;
	return FALSE;
}

BOOL AlarmG_IsAlarmStarted(MyAlarmGroup3* pthis)
{
	if(pthis->m_alarmone[0].m_bAlarmStarted) return TRUE;
	if(pthis->m_alarmone[0].m_bAlarmStarted) return TRUE;
	if(pthis->m_alarmone[0].m_bAlarmStarted) return TRUE;
	return FALSE;
}

