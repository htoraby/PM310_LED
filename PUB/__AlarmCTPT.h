#ifndef __ALARMCTPT_H
#define __ALARMCTPT_H

//-----------------------------------------------------------------------------
#ifndef ALARMCTM_0_1A
#define ALARMCTM_0_1A			50				//����CT���߸澯�����ż�0.1A;
#endif
#ifndef ALARMCTM_DELAY
#define ALARMCTM_DELAY			100				//����CT���߸澯��ʱ1��;
#endif

// extern void AlarmGCTM_ExeDetect(MyAlarmGroup3* pthis,MyData* dataIa,MyData* dataIb,MyData* dataIc,WORD wModeCTM,WORD wAlarmToggle,WORD wAlarmEventCode);


//-----------------------------------------------------------------------------
#ifndef ALARMCTP_0_5A
#define ALARMCTP_0_5A			15				//����CT���߸澯�����ż�0.5A;
#endif
#ifndef ALARMCTP_DELAY
#define ALARMCTP_DELAY			100				//����CT���߸澯��ʱ1��;
#endif

extern void AlarmGCTP_ExeDetect(MyAlarmGroup3* pthis,MyData* dataIA,MyData* dataIB,MyData* dataIC,WORD wModeCTP,WORD wAlarmToggle,WORD wAlarmEventCode);

//-----------------------------------------------------------------------------
#ifndef ALARMPT_10V
#define ALARMPT_10V				300				//���ѹ10V;
#endif
#ifndef ALARMPT_DELAY
#define ALARMPT_DELAY			100				//PT���߸澯��ʱ1��;
#endif

extern void AlarmGPT_ExeDetect(MyAlarmGroup3* pthis,MyData* dataUa,MyData* dataUb,MyData* dataUc,
				   MyData* dataUab,MyData* dataUbc,MyData* dataUca,
				   WORD wModePT,WORD wDataIMax,WORD wAlarmToggle,WORD wAlarmEventCode);

#endif/*__ALARMCTPT_H*/

/******************************************************************************
ģ�鹦��:
ʵ��ͨ�õı�������CTP,��������CTM,��ѹPT�澯��⹦��;
ʹ�ò���:
1.��g_app.OnInit�е���OnInit()���г�ʼ��;
2.��g_app.OnTimer10ms()�е���ExeDetect()���и澯���;
3.��g_app.OnResetDevice()�е���OnReset()�����źŸ���;
4.��������ͨ������IsAlarmed()��IsAlarmStarted()�õ��澯�Ƿ�����͸澯�Ƿ�����;
*/
//ThinkBoy,ShenBo,2006/04/30;

