#ifndef __ALARMCTPT_H
#define __ALARMCTPT_H

//-----------------------------------------------------------------------------
#ifndef ALARMCTM_0_1A
#define ALARMCTM_0_1A			50				//测量CT断线告警启动门槛0.1A;
#endif
#ifndef ALARMCTM_DELAY
#define ALARMCTM_DELAY			100				//测量CT断线告警延时1秒;
#endif

// extern void AlarmGCTM_ExeDetect(MyAlarmGroup3* pthis,MyData* dataIa,MyData* dataIb,MyData* dataIc,WORD wModeCTM,WORD wAlarmToggle,WORD wAlarmEventCode);


//-----------------------------------------------------------------------------
#ifndef ALARMCTP_0_5A
#define ALARMCTP_0_5A			15				//保护CT断线告警启动门槛0.5A;
#endif
#ifndef ALARMCTP_DELAY
#define ALARMCTP_DELAY			100				//保护CT断线告警延时1秒;
#endif

extern void AlarmGCTP_ExeDetect(MyAlarmGroup3* pthis,MyData* dataIA,MyData* dataIB,MyData* dataIC,WORD wModeCTP,WORD wAlarmToggle,WORD wAlarmEventCode);

//-----------------------------------------------------------------------------
#ifndef ALARMPT_10V
#define ALARMPT_10V				300				//相电压10V;
#endif
#ifndef ALARMPT_DELAY
#define ALARMPT_DELAY			100				//PT断线告警延时1秒;
#endif

extern void AlarmGPT_ExeDetect(MyAlarmGroup3* pthis,MyData* dataUa,MyData* dataUb,MyData* dataUc,
				   MyData* dataUab,MyData* dataUbc,MyData* dataUca,
				   WORD wModePT,WORD wDataIMax,WORD wAlarmToggle,WORD wAlarmEventCode);

#endif/*__ALARMCTPT_H*/

/******************************************************************************
模块功能:
实现通用的保护电流CTP,测量电流CTM,电压PT告警检测功能;
使用步骤:
1.在g_app.OnInit中调用OnInit()进行初始化;
2.在g_app.OnTimer10ms()中调用ExeDetect()进行告警检测;
3.在g_app.OnResetDevice()中调用OnReset()进行信号复归;
4.其它程序通过调用IsAlarmed()和IsAlarmStarted()得到告警是否产生和告警是否启动;
*/
//ThinkBoy,ShenBo,2006/04/30;

