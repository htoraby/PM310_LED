#define MODULE__SWITCH_H

#define SS_IN01			0x0001		//״̬������:IN01;
#define SS_IN02			0x0002		//״̬������:IN02;
#define SS_IN03			0x0004		//״̬������:IN03;
#define SS_IN04			0x0008		//״̬������:IN04;
#define SS_IN05			0x0010		//״̬������:IN05;
#define SS_IN06			0x0020		//״̬������:IN06;
#define SS_IN07			0x0040		//״̬������:IN07;
#define SS_IN08			0x0080		//״̬������:IN08;
#define SS_IN09			0x0100		//״̬������:IN09;
#define SS_IN10			0x0200		//״̬������:IN10;
#define SS_IN11			0x0400		//״̬������:IN11;
#define SS_IN12			0x0800		//״̬������:IN12;
#define SS_IN13			0x1000		//״̬������:IN13;
#define SS_IN14			0x2000		//״̬������:IN14;
#define SS_IN15			0x4000		//״̬������:IN15;
#define SS_IN16			0x8000		//״̬������:IN16;

#define SWITCHSetStatus(wIndex,wStatus)											\
	do																			\
	{																			\
		if(wStatus==STATUS_NULL||wStatus==STATUS_OFF||wStatus==STATUS_ON)		\
		{																		\
			g_wStatusNew[wIndex]     = wStatus;									\
			g_wStatusNewExt1[wIndex] = wStatus;									\
			g_wStatusNewExt2[wIndex] = wStatus;									\
		}																		\
	}																			\
	while(0)

//-----------------------------------------------------------------------------
// typedef struct _INPARAM
// {
// 	WORD wEventType;				//������״̬�����仯ʱ�������¼�����;
// 	WORD wAckDelayTime;				//������״̬�仯ȷ��ʱ��,�൱������˲�����;
// //  	WORD wszName[21];				//����������,���16���ַ���8������;
// //  	WORD wszStatus0[9];				//������״̬0ʱ����,���8���ַ���4������;
// //  	WORD wszStatus1[9];				//������״̬1ʱ����,���8���ַ���4������;
// 	WORD wName;
// 	WORD wStatus0;
// 	WORD wStatus1;
// }INPARAM;
// 
// typedef struct _INPARAMTABLE
// {
// 	INPARAM inparam[SWITCH_COUNT];
// }INPARAMTABLE;


#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//˵��:�趨ָ���������Ĳ���;
// extern void Switch_SetInParam(INPARAM* pInParam,WORD wEventType,WORD wName,WORD wStatus0,WORD wStatus1);
// ˵��:��ʼ������;
extern void Switch_OnInit(void);
// ˵��:��ʱ�������(�ϸ�)����,����ȷ��״̬;wIndex:������������(ֻ�����¼���¼�Ϳ���������);pInParam:����������;
extern void Switch_OnTimer1ms(void);
// extern void Switch_OnTimer1msDC(INPARAMTABLE* pInParamTable);
// extern void Switch_OnTimer1msAC(INPARAMTABLE* pInParamTable);

// extern INPARAMTABLE g_inparamTable;

extern WORD g_wStatusNew[SWITCH_COUNT];				// ȷ��ǰ״̬;
extern WORD g_wStatusNewExt1[SWITCH_COUNT];			// ȷ��ǰ״̬,��չ�Է�ֹ����;
extern WORD g_wStatusNewExt2[SWITCH_COUNT];			// ȷ��ǰ״̬,��չ�Է�ֹ����;
extern WORD g_wSwitchStatus1;
extern WORD g_wSwitchStatus2;
extern DWORD g_dwChangtoON1;						// �������ڱ�Ϊ�ߵ�ƽ�Ŀ�����;
// ��Ҫ���ڿ���������,��բ�����;
extern DWORD g_dwChangtoON2;						// ֵ��m_dwChangtoON1��ͬ������ȷ����������������
extern WORD g_wStatusOld[SWITCH_COUNT];				// ȷ�Ϻ�״̬;
extern WORD g_wCountAck[SWITCH_COUNT];				// ȷ�ϼ���;
extern WORD g_wCountStatus0[SWITCH_COUNT];				// 0״̬����
extern WORD g_wCountStatus1[SWITCH_COUNT];				// 1״̬����


#ifdef __cplusplus
}
#endif /* extern "C" */

/******************************************************************************
ģ�鹦��:
ʵ�ֿ������������,���Զ������趨�Ĳ���Ҫ����������¼�,��֧�ֿ��賤�ȵı�λȷ��ʱ��;
ʹ�ò���:
1.����Ӧ��Ҫ����SWITCH_COUNT;
2.����SWITCH_COUNT��CMySwitch��ʵ��,���������:g_switch[SWITCH_COUNT];
3.���û�������ʼ��������ͨ������SetInParam()Ԥ�迪��������;
4.��g_app.OnInit()�е���OnInit();
5.��g_app.OnTimer1ms()�е���OnTimer1ms();
6.��g_hdif.OnTimer1ms()�н��µ�ȷ��ǰ״̬��Ӳ��������ͨ��Setatus(wStatus)�����趨;
7.�����û�����ͨ������GetStatus()�õ���ȷ�Ϻ�Ŀ���������״̬;
8.�����ȵļ���ͨ��GetCountON()����;
*/
//ThinkBoy,ShenBo,2006/04/30;
