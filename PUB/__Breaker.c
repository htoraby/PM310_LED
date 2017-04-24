//-----------------------------------------------------------------------------------------------------
//									Copyright (c) 2009 by ThinkBoy.
//										All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#include <Main.h>

//WORD g_wStatusKM;				//控制电源信号状态,0:表示无信号,非0:表示有信号;
// WORD g_wStatusPosOpened;		//分位信号状态,0:表示无信号,非0:表示有信号;
WORD g_wStatusPosClosed;		//合位信号状态,0:表示无信号,非0:表示有信号;

MyAlarmGroup3 g_breaker;

//-----------------------------------------------------------------------------
void BreakerStatus_OnInit(void)
{
	AlarmG_OnInit(&g_breaker);

//	g_wStatusKM = 20;
// 	g_wStatusPosOpened = 20;
	g_wStatusPosClosed = 20;
}

void BreakerStatus_OnTimer1ms(void)
{
//	if(g_wStatusKM) g_wStatusKM--;
// 	if(g_wStatusPosOpened) g_wStatusPosOpened--;
// 	if(g_wStatusPosClosed) g_wStatusPosClosed--;
// 
// 	if(g_deviceInfo.wSwitchStatus1&0x01)
// 	{
// 		g_wCountAfterClosed++;
// 		if(g_wCountAfterClosed>60000) g_wCountAfterClosed = 60000;
// 	}
// 	else g_wCountAfterClosed = 0;
}

void BreakerStatus_ExeDetect(WORD wAlarmToggleKM,WORD wAlarmToggleClose,WORD wAlarmToggleOpen)
{
// 	Alarm_ExeDetect(&g_breaker.m_alarmone[0],wAlarmToggleKM,BOALARM_DELAYKM,(g_wStatusKM==0),EVENTCODE_ALARMKM);
// 	if(BreakerStatus_IsAlarmedKM())
// 	{
// // 		Alarm_OnReset(&g_breaker.m_alarmone[1]);
// 		Alarm_OnReset(&g_breaker.m_alarmone[2]);
// 	}
// 	else
// 	{
//		if(s_wStatus==BOSTATUS_OPENED) Alarm_ExeDetect(pthis->m_alarmone[1],wAlarmToggleClose,BOALARM_DELAYCLOSE,g_wStatusPosOpened,EVENTCODE_ALARMCLOSE);
//		else Alarm_OnReset(pthis->m_alarmone[1]);
		if(g_deviceInfo.wSwitchStatus1&SS_IN01) Alarm_ExeDetect(&g_breaker.m_alarmone[2],wAlarmToggleOpen,BOALARM_DELAYOPEN,(g_wStatusPosClosed==0),EVENTCODE_ALARMOPEN);
		else Alarm_OnReset(&g_breaker.m_alarmone[2]);
//	}
}

// BOOL BreakerStatus_IsAlarmedKM(void)
// {
// 	return g_breaker.m_alarmone[0].m_bAlarmed ? TRUE : FALSE;
// }
// 
// BOOL BreakerStatus_IsAlarmedClose(void)
// {
// 	return g_breaker.m_alarmone[1].m_bAlarmed ? TRUE : FALSE;
// }

BOOL BreakerStatus_IsAlarmedOpen(void)
{
	return g_breaker.m_alarmone[2].m_bAlarmed ? TRUE : FALSE;
}

void BreakerStatus_Rest(void)
{
	AlarmG_OnReset(&g_breaker);
}

//-----------------------------------------------------------------------------------------------------
//											End Of File
//-----------------------------------------------------------------------------------------------------
