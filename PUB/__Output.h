#ifndef __OUTPUT_H
#define __OUTPUT_H

#define OUTPUT_TM_00		0			//����ģʽ:ȫ��
#define OUTPUT_TM_01		1			//����ģʽ:�ȷֺ��
#define OUTPUT_TM_10		2			//����ģʽ:�ȺϺ��
#define OUTPUT_TM_11		3			//����ģʽ:ȫ��

typedef struct _MyOutput
{
	WORD m_wStatus1;					//�����״̬1;
	WORD m_wStatus2;					//�����״̬2;
	WORD m_wStatus3;					//�����״̬3;
	WORD m_wCountPulse;					//����ʽ����ʱ����;
	WORD m_wCountTestMode;				//���Զ���ʱ����;
	WORD m_wTestMode;					//����ģʽ;
}MyOutput;

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//˵��:��ʼ������,��״̬��ʼ��Ϊ��;
extern void Output_OnInit(MyOutput* pthis);
//˵��:��ʱ�������(�ϸ�)����,���ڶ�״̬����ˢ��;
extern void Output_OnTimer10ms(MyOutput* pthis);
//˵��:��ƽʽ����;wStatus:STATUS_OFF��;STATUS_ON:��;
extern void Output_SetLevel(MyOutput* pthis,WORD wStatus);
//˵��:����ʽ����,�Ⱥ�,��wDelay10ms���Զ���;
extern void Output_SetPulse(MyOutput* pthis,WORD wDelay10ms);
//˵��:�������ģʽ,����ģʽ�ۼ���ʱ2����Զ�����;
extern void Output_EnterTest(MyOutput* pthis,WORD wTestMode,WORD wCountTestMode);
//˵��:���ص�ǰ״̬,TRUE:��ʾ����;FALSE:δ����;
extern BOOL Output_IsOutputValid(MyOutput* pthis);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__OUTPUT_H*/

/******************************************************************************
ģ�鹦��:
ʵ�������(ָʾ�ƻ�̵���)����;
ʹ�ò���:
1.����CMyOutputʵ��,���������:g_lightXXX��g_relayXXX;
2.��g_app.OnInit()�е���OnInit();
3.��g_app.OnTimer10ms()�е���OnTimer10ms();
4.ͨ��SetLevel()��SetPulse()�趨�����״̬;
5.ͨ��IsOutputValid()�õ��̵���״̬�����;
6.ͨ��EnterTest()����������в���,����֧������ģʽ;
*/
