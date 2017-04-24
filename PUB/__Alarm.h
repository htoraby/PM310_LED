#ifndef __ALARM_H
#define __ALARM_H

typedef struct _MyAlarm
{
	WORD m_wCount;					//告警检测计数;
	BOOL m_bAlarmed;				//告警是否检测;
	BOOL m_bAlarmStarted;			//告警是否启动;
}MyAlarm;

//-----------------------------------------------------------------------------
//说明:初始化程序;
extern void Alarm_OnInit(MyAlarm* pthis);
//说明:执行告警检测:
//wAlarmToggle:TOGGLE_OFF/TOGGLE_ON;
//wAlarmDelay:实际时限的10ms倍数;
//bAlarmValid:告警成立条件;
//wAlarmEventCode:告警事件代码;
extern void Alarm_ExeDetect(MyAlarm* pthis,WORD wAlarmToggle,WORD wAlarmDelay,BOOL bAlarmValid,WORD wAlarmEventCode);
//说明:复位告警检测,即将告警检测计数清零;
extern void Alarm_OnReset(MyAlarm* pthis);
//说明:判断告警是否出现;
// extern BOOL Alarm_IsAlarmed(MyAlarm* pthis);
//说明:判断告警是否启动;
// extern BOOL Alarm_IsAlarmStarted(MyAlarm* pthis);


//-----------------------------------------------------------------------------
typedef struct _MyAlarmGroup3
{
	MyAlarm m_alarmone[3];
}MyAlarmGroup3;

//说明:初始化程序;
extern void AlarmG_OnInit(MyAlarmGroup3* pthis);
//说明:复位告警检测,即将告警检测计数清零;
extern void AlarmG_OnReset(MyAlarmGroup3* pthis);
//说明:判断告警是否出现;
extern BOOL AlarmG_IsAlarmed(MyAlarmGroup3* pthis);
//说明:判断告警是否启动;
extern BOOL AlarmG_IsAlarmStarted(MyAlarmGroup3* pthis);

#endif/*__ALARM_H*/
/******************************************************************************
模块功能:
实现告警检测的基类功能,包括单个告警和告警组;具体使用时必须派生具体应用类;
*/
//ThinkBoy,ShenBo,2006/04/30;


