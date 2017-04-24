#ifndef __EVENT_H
#define __EVENT_H

#ifndef EVENT_COUNT
#define EVENT_COUNT			8
#endif

#define EVENTTYPE_NULL		0x0000		//���¼�
#define EVENTTYPE_SWITCH	0x0001		//���ر�λ�¼�
#define EVENTTYPE_RUNINFO	0x0002		//������Ϣ�¼�
#define EVENTTYPE_ALARMED	0x0003		//�豸�澯�¼�
#define EVENTTYPE_TRIPPED	0x0004		//�豸�����¼�
#define EVENTTYPE_OPERATE	0x0005		//������¼�¼�
#define EVENTTYPE_ERRORED	0x0006		//�Լ��쳣�¼�
#define EVENTTYPE_NOTUSED	0x0007		//��Ч�¼�

#define EVENTCODE_NULL					//���¼�����
#define EVENTCODE_OTHER		0x0100		//�豸����¼�
#define EVENTCODE_SWITCH	0x0200		//��������λ�¼�
#define EVENTCODE_ALARMED	0x0300		//�澯����¼�
#define EVENTCODE_PROTECT	0x0400		//���������¼�
#define EVENTCODE_ERRORED	0x0500		//�Լ��쳣�¼�
#define EVENTCODE_LAD		0x0600		//����ͼ�¼�
#define EVENTCODE_REMOTE	0x0700		//ң�ز����¼�

#define EVENT_SIZE			10			//��һһ���¼��ĳ���


//-----------------------------------------------------------------------------
typedef struct _EVENT
{
	DEVICETIME time;				//�¼�������ʱ���;
	WORD wType;						//�¼�����;
	WORD wCode;						//�¼�����;
	WORD wData;						//�������,�京��ȡ�����¼�����;
}EVENT;


//-----------------------------------------------------------------------------
typedef struct EVENTTABLE
{
	EVENT event[EVENT_COUNT];		// �¼���¼��;
    WORD wEventReadCnt;             // ��ȡ����
}EVENTTABLE;

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//˵��:��ʼ������;
extern void Event_OnInit(void);
//˵��:��ʱ�������,���ڼ�������¼���¼���Զ�����;
extern void Event_OnTimer1000ms(void);
//˵��:��ʼ���豸,�Զ�����¼���¼;
extern void Event_OnInitDevice(void);
//˵��:�����¼���¼,wEventType:�¼�����,��Χ1-6,wEventCode:�¼�����,wEventData:�������;
extern void Event_AddEvent(WORD wEventType,WORD wEventCode,WORD wEventData);
//˵��:����ָ��λ�õ��¼���¼;
extern EVENT* Event_GetEvent(WORD wIndexEvent);
//˵��:���¼���¼��;
extern void Event_ReadEventTable(void);
//˵��:д�¼���¼��;
extern void Event_WriteEventTable(void);

extern WORD g_wEventTableCountNew;
extern EVENTTABLE g_eventTable;			//�¼���¼��;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__EVENT_H*/
/******************************************************************************
ģ�鹦��:
��Ҫʵ�ֶԸ����¼���¼�Ĺ���,��ѭ�����еķ�ʽ�����¼���¼,����ֵm_wCountNew��ʼֵ
Ϊ0(װ�õ�һ������),ÿ����һ���¼�,�����Զ���һ;�¼���¼��m_wCountNew%EVENT_COUNT
�ķ�ʽ����;��ʾ�¼���¼ʱ���鶪�������1-2���¼���¼,�Է�ֹ�ٽ��ͻ;
ʹ�ò���:
1.����Ӧ��Ҫ����EVENT_COUNT;
2.��g_app.OnInit()�е���OnInit(),����ɼ���ֵ��ʼ��,���Զ�װ���¼���¼��;
3.�����û�����ֱ�ӵ���AddEvent(wEventType,wEventCode,wEventData)���������¼���¼;
4.��g_app.OnTimer1000ms()�е���OnTimer1000ms(),�Լ���������¼����Զ�����;
5.���س���ʱ��m_wCountNew���浽g_deviceInfo.wCountEventTable��;
6.��ҳ����ʾ������ʾ�¼���¼��;
*/

