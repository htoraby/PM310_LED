#ifndef __TIME_H
#define __TIME_H


//-----------------------------------------------------------------------------
typedef struct _DEVICETIME
{
	WORD wYear;						//��(ʵ����-2000,0-100);
	WORD wMonth;					//��(1-12);
	WORD wDay;						//��(1-31);
	WORD wHour;						//ʱ(0-23);
	WORD wMinute;					//��(0-59);
	WORD wSecond;					//��(0-59);
	WORD wMilliSecond;				//����(0-999);
}DEVICETIME;


#ifdef __cplusplus
extern "C" {
#endif

//˵��:����ָ�����µ�������;
extern WORD Time_GetDayOfMonth(WORD wYear,WORD wMonth);
//˵��:���ʱ���Ƿ���ȷ;
extern BOOL Time_IsTimeOK(DEVICETIME* pDeviceTime);
//˵��:��ʼ������,��ϵͳʱ���ʼ��Ϊ2000-01-01 00:00:00.000;
extern void Time_OnInit(void);
//˵��:��ʱ�������(�ϸ�)����,����ʱ��ˢ��;
extern void Time_OnTimer1ms(void);
//˵��:��ʱ����������,���ڱ���ʱ����ض�ʱ��;
extern void Time_OnTimer1000ms(void);
//˵��:��g_app��OnUpdateDevice()���е���,�����ñ�����±�־;
extern void Time_OnUpdateDevice(WORD* pData);
//˵��:�жϺ�������Ƿ�С��450(��������˸Ч��),����ÿ��һ����˸����;
extern BOOL Time_IsFlashing(void);

extern DEVICETIME g_deviceTime;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__TIME_H*/

/******************************************************************************
ģ�鹦��:
ʵ��ʱ�����;
ʹ�ò���:
1.����CMyTimeʵ��,���������:g_time;
2.��g_app.OnInit()�е���g_time.OnInit();
3.��g_app.OnTimer1ms()�е���g_time.OnTimer1ms();
4.��g_app.OnTimer1000ms()�е���g_time.OnTimer1000ms();
5.�����û�����ͨ����������g_time.m_deviceTime�����豸ʱ��;
6.Уʱ�����ʱ������Ҫ��ı�ʱ���,ֱ���޸�g_time.m_deviceTime,������
  g_time.OnUpdateDevice((WORD*)&g_time.m_deviceTime),���ñ�����±�־;
  ����ÿ��Сʱ��ʱ��оƬ�ض�һ������ʱ��,��������±�־���ú��Զ�����
  �µ�ʱ�䱣�浽ʱ��оƬ��;
*/
//ThinkBoy,ShenBo,2006/04/30;
