//-----------------------------------------------------------------------------------------------------
//									Copyright (c) 2009 by ThinkBoy.
//										All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __BREAKER_H
#define __BREAKER_H

#define MODULE__BREAKER_H

#define BOMODE_LOCAL			1			//��·������ģʽ:����;
#define BOMODE_REMOTE			2			//��·������ģʽ:ң��;
#define BOMODE_PROTECT			3			//��·������ģʽ:����;

#define BOSTATUS_NULL			0x0000		//��·��״̬:��Ч,һ��Ϊ�����Դ�쳣����;
#define BOSTATUS_OPENED			0x3333		//��·��״̬:��λ;
#define BOSTATUS_CLOSED			0x5555		//��·��״̬:��λ;
#define BOSTATUS_TOCLOSED		0x3355		//��·��״̬:��->��;
#define BOSTATUS_TOOPENED		0x5533		//��·��״̬:��->��;

#ifndef BOALARM_DELAYKM
#define BOALARM_DELAYKM			50			//���Ƶ�Դ���߸澯��ʱ0.5��;
#endif
#ifndef BOALARM_DELAYCLOSE
#define BOALARM_DELAYCLOSE		3000		//��բ��·���߸澯��ʱ30��;
#endif
#ifndef BOALARM_DELAYOPEN
#define BOALARM_DELAYOPEN		100			//��բ��·���߸澯��ʱ1��;
#endif

#ifndef EVENTCODE_LOCALBO
#define EVENTCODE_LOCALBO		(EVENTCODE_OTHER+0x00)		//���ز�����·��;
#endif
#ifndef EVENTCODE_REMOTEBO
#define EVENTCODE_REMOTEBO		(EVENTCODE_OTHER+0x01)		//ң�ز�����·��;
#endif
#ifndef EVENTCODE_ALARMKM
#define EVENTCODE_ALARMKM		(EVENTCODE_ALARMED+0x10)	//���Ƶ�Դʧ��;
#endif
#ifndef EVENTCODE_ALARMCLOSE
#define EVENTCODE_ALARMCLOSE	(EVENTCODE_ALARMED+0x11)	//��բ��·����;
#endif
#ifndef EVENTCODE_ALARMOPEN
#define EVENTCODE_ALARMOPEN		(EVENTCODE_ALARMED+0x12)	//��բ��·����;
#endif
#ifndef EVENTCODE_ERRORCLOSE
#define EVENTCODE_ERRORCLOSE	(EVENTCODE_ALARMED+0x13)	//��բ�ܶ�;
#endif
#ifndef EVENTCODE_ERROROPEN
#define EVENTCODE_ERROROPEN		(EVENTCODE_ALARMED+0x14)	//��բ�ܶ�;
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void BreakerStatus_OnInit(void);
//˵��:ִ�и澯���;
extern void BreakerStatus_ExeDetect(WORD wAlarmToggleKM,WORD wAlarmToggleClose,WORD wAlarmToggleOpen);
//˵��:�ж���բ��·�����Ƿ�澯;
extern BOOL BreakerStatus_IsAlarmedOpen(void);
// ˵��:�жϿ��Ƶ�Դʧ���Ƿ�澯;
extern BOOL BreakerStatus_IsAlarmedKM(void);
// ˵��:�жϺ�բ��·�����Ƿ�澯;
extern BOOL BreakerStatus_IsAlarmedClose(void);
extern void BreakerStatus_OnTimer1ms(void);
extern void BreakerStatus_Rest(void);

extern WORD g_wStatusKM;				//���Ƶ�Դ�ź�״̬,0:��ʾ���ź�,��0:��ʾ���ź�;
// extern WORD g_wStatusPosOpened;		//��λ�ź�״̬,0:��ʾ���ź�,��0:��ʾ���ź�;
extern WORD g_wStatusPosClosed;		//��λ�ź�״̬,0:��ʾ���ź�,��0:��ʾ���ź�;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__BREAKER_H*/

/******************************************************************************
ģ�鹦��:
ʵ�ֶ�·�������ӿڵ���ع���,������·���澯,������Ϣͳ��,��·���ܶ��澯,��·����/��բ����,
���ز�������,���ṩ���״̬�������������ʾ��;
ʹ�ò���:
1.����CMyBreakerOperateʵ��,���������:g_breaker;
2.��g_app.OnInit()�е���OnInit();
3.�ֱ���g_app.OnTimer1ms()��g_app.OnTimer10ms()�е���OnTimer1ms()��OnTimer10ms();
4.���û��������ṩg_app.GetBOStatus(),���ܵķ���ֵΪ:BOSTATUS_NULL/BOSTATUS_OPENED/BOSTATUS_CLOSED;
5.���û��������ṩg_app.SetBOErrorCloseFlag(),g_app.SetBOErrorOpenFlag(),�����趨��բ�ܶ�����բ�ܶ���־;
6.��g_hdif.OnTimer1ms()�и���Ӳ�������Ϣִ��HitStatusKM(),HitStatusPosOpened(),HitStatusPosClosed();
7.��g_app.OnTimer10ms()�е���OnTimer10ms(),�ٵ���ExeDetect()���и澯���;
8.�����û�����ͨ��IsAlarmedKM(),IsAlarmedClose(),IsAlarmedOpen()�õ��澯�����Ϣ;
9.�ڰ�����������е���LocalClose(),LocalOpen(),ע����ִ��g_breaker.m_lockLocal.Unlock1();
10.�Ա�����ң�ز�����·����ֱ�ӵ���ExecuteClose(),ExecuteOpen(),ע�����ģʽ����wBOMode�Ͷ�Ӧ���������;
11.�ж�·��������ϢҪ���,��������²���:
	1.����FLASH�б���Ķ�·��������Ϣ���ݸ��Ƶ�m_boinfo;
	2.�����ݼ���ģ������ͨ��SetDataIMax()��m_wDataIMax,m_wDataIMax100mA��ֵ,ע���䵥λ;
	3.���ڱ���m_boinfo��FLASH��,�Է����綪ʧ;
12.�ڱ��������п�ʹ��m_wCountAfterClosed,m_wCountAfterOpened,m_wCountAfterTripped�ṩ����Ϣ;

��Բ�ͬ�Ķ�·������ģʽ:����/ң��/����,�ṩ�����������;
���ز���:
1.m_lockLocal.Unlock1();
2.��բִ��LocalClose(),��բִ��LocalOpen();
3.m_lockLocal.Lock1();
ң�ز���:
1.m_lockRemote.Unlock1();
2.��բִ��RemoteClose(),��բִ��RemoteOpen();
3.m_lockRemote.Lock1();
��������:
1.m_lockProtect.Unlock1();
2.m_lockProtect.Unlock2();
3.m_lockProtect.Unlock3();
4.��բִ��ExecuteClose(BOMODE_PROTECT),��բִ��ExecuteOpen(BOMODE_PROTECT);
5.m_lockProtect.Lock3();
6.m_lockProtect.Lock2();
7.m_lockProtect.Lock1();
˵��:�ڲ�ͬ�ķ�֧�в���1,2,3��,��ֹ�����쳣ʱ��·������;
*/

//ThinkBoy,ShenBo,2006/04/30;
//-----------------------------------------------------------------------------------------------------
//											End Of File
//-----------------------------------------------------------------------------------------------------
