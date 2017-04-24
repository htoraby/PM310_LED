#ifndef __ALARM_H
#define __ALARM_H

typedef struct _MyAlarm
{
	WORD m_wCount;					//�澯������;
	BOOL m_bAlarmed;				//�澯�Ƿ���;
	BOOL m_bAlarmStarted;			//�澯�Ƿ�����;
}MyAlarm;

//-----------------------------------------------------------------------------
//˵��:��ʼ������;
extern void Alarm_OnInit(MyAlarm* pthis);
//˵��:ִ�и澯���:
//wAlarmToggle:TOGGLE_OFF/TOGGLE_ON;
//wAlarmDelay:ʵ��ʱ�޵�10ms����;
//bAlarmValid:�澯��������;
//wAlarmEventCode:�澯�¼�����;
extern void Alarm_ExeDetect(MyAlarm* pthis,WORD wAlarmToggle,WORD wAlarmDelay,BOOL bAlarmValid,WORD wAlarmEventCode);
//˵��:��λ�澯���,�����澯����������;
extern void Alarm_OnReset(MyAlarm* pthis);
//˵��:�жϸ澯�Ƿ����;
// extern BOOL Alarm_IsAlarmed(MyAlarm* pthis);
//˵��:�жϸ澯�Ƿ�����;
// extern BOOL Alarm_IsAlarmStarted(MyAlarm* pthis);


//-----------------------------------------------------------------------------
typedef struct _MyAlarmGroup3
{
	MyAlarm m_alarmone[3];
}MyAlarmGroup3;

//˵��:��ʼ������;
extern void AlarmG_OnInit(MyAlarmGroup3* pthis);
//˵��:��λ�澯���,�����澯����������;
extern void AlarmG_OnReset(MyAlarmGroup3* pthis);
//˵��:�жϸ澯�Ƿ����;
extern BOOL AlarmG_IsAlarmed(MyAlarmGroup3* pthis);
//˵��:�жϸ澯�Ƿ�����;
extern BOOL AlarmG_IsAlarmStarted(MyAlarmGroup3* pthis);

#endif/*__ALARM_H*/
/******************************************************************************
ģ�鹦��:
ʵ�ָ澯���Ļ��๦��,���������澯�͸澯��;����ʹ��ʱ������������Ӧ����;
*/
//ThinkBoy,ShenBo,2006/04/30;


