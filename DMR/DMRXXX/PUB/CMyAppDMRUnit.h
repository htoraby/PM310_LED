#ifndef CMYAPPDMRUNIT_H
#define CMYAPPDMRUNIT_H

#define BOM_NULL			0x0000		//״̬��Ч;
#define BOM_DISABLE			0x3333		//������ֹ;
#define BOM_ENABLE			0x5555		//��������;

#define PROTECTACT_NULL		0			//��������ֵ:��;
#define PROTECTACT_IP		1			//��������ֵ:IP;
#define PROTECTACT_U		2			//��������ֵ:U;
#define PROTECTACT_3I0		3			//��������ֵ:3I0;
#define PROTECTACT_3U0		4			//��������ֵ:3U0;
#define PROTECTACT_Ix		5			//��������ֵ:Ix;
#define PROTECTACT_Ux		6			//��������ֵ:Ux;
#define PROTECTACT_F		7			//��������ֵ:F;

#define DS2_AlarmCTM		0x0001		//�澯�ź�:����CT����;
#define DS2_AlarmCTP		0x0002		//�澯�ź�:����CT����;
#define DS2_AlarmPT			0x0004		//�澯�ź�:PT����;
#define DS2_AlarmKM			0x0008		//�澯�ź�:���Ƶ�Դʧ��;
#define DS2_AlarmClose		0x0010		//�澯�ź�:��բ��·����;
#define DS2_AlarmOpen		0x0020		//�澯�ź�:��բ��·����;
#define DS2_ErrorClose		0x0040		//�澯�ź�:��բ�ܶ�;
#define DS2_ErrorOpen		0x0080		//�澯�ź�:��բ�ܶ�;
#define DS2_EnableLocal		0x0100		//���ز�������;
#define DS2_EnableRemote	0x0200		//ң�ز�������;
#define DS2_DirectP			0x0400		//�й����ʷ���;
#define DS2_DirectQ			0x0800		//�޹����ʷ���;
#define DS2_LockClose		0x1000		//��բ����;

#define EVENTCODE_LOCALBO		(EVENTCODE_OTHER+0x00)		//���ز�����·��;
#define EVENTCODE_REMOTEBO		(EVENTCODE_OTHER+0x01)		//ң�ز�����·��;
#define EVENTCODE_ALARMCTPA		(EVENTCODE_ALARMED+0x00)	//A�ౣ��CT����;
#define EVENTCODE_ALARMCTPB		(EVENTCODE_ALARMED+0x01)	//B�ౣ��CT����;
#define EVENTCODE_ALARMCTPC		(EVENTCODE_ALARMED+0x02)	//C�ౣ��CT����;
#define EVENTCODE_ALARMCTMA		(EVENTCODE_ALARMED+0x03)	//A�����CT����;
#define EVENTCODE_ALARMCTMB		(EVENTCODE_ALARMED+0x04)	//B�����CT����;
#define EVENTCODE_ALARMCTMC		(EVENTCODE_ALARMED+0x05)	//C�����CT����;
#define EVENTCODE_ALARMPT3		(EVENTCODE_ALARMED+0x06)	//����PT����;
#define EVENTCODE_ALARMPT2		(EVENTCODE_ALARMED+0x07)	//����PT����;
#define EVENTCODE_ALARMPT1		(EVENTCODE_ALARMED+0x08)	//����PT����;
#define EVENTCODE_ALARMKM		(EVENTCODE_ALARMED+0x10)	//���Ƶ�Դʧ��;
#define EVENTCODE_ALARMCLOSE	(EVENTCODE_ALARMED+0x11)	//��բ��·����;
#define EVENTCODE_ALARMOPEN		(EVENTCODE_ALARMED+0x12)	//��բ��·����;
#define EVENTCODE_ERRORCLOSE	(EVENTCODE_ALARMED+0x13)	//��բ�ܶ�;
#define EVENTCODE_ERROROPEN		(EVENTCODE_ALARMED+0x14)	//��բ�ܶ�;

#ifndef KPUTIME
#define KPUTIME		20
#endif


struct DEVICEPARAM_UNIT
{
	WORD wToggleAlarmKM;
	WORD wToggleAlarmClose;
	WORD wToggleAlarmOpen;
	WORD wToggleReserved;
	WORD wToggleAlarmCT;
	WORD wToggleAlarmPT;
	WORD wModeCTM;
	WORD wModeCTP;
	WORD wModePT;
	WORD wScaleCT;
	WORD wScalePT;
	WORD wScale2IM;
	WORD wScale2IP;
	WORD wScale2Uln;
	WORD wScale23I0;
	WORD wScale23U0;
	WORD wScale2Ix;
	WORD wScale2Ux;
	WORD wLinkInPE[4];
	WORD wPulsesPerkWh[4];
};

struct ANALOGDATA
{
	WORD wDataIa;
	WORD wDataIb;
	WORD wDataIc;
	WORD wDataIA;
	WORD wDataIB;
	WORD wDataIC;
	WORD wDataUa;
	WORD wDataUb;
	WORD wDataUc;
	WORD wDataUab;
	WORD wDataUbc;
	WORD wDataUca;
	WORD wData3I0;
	WORD wData3I2;
	WORD wData3U0;
	WORD wData3U2;
	WORD wDataF;
	short nDataP;
	short nDataQ;
	short nDataPF;
	WORD wDataIx;
	WORD wDataUxab;
	WORD wDataUxbc;
	WORD wDataUxca;
	WORD wData3Ux2;
	WORD wDataFx;
};

struct ANALOGDATAEXT
{
	BREAKEROPERATEINFO boinfo;
	DWORD dwDataPhImp;
	DWORD dwDataQhImp;
	DWORD dwDataPhExp;
	DWORD dwDataQhExp;
	DWORD dwDataPE[4];
	DWORD dwDataPhImpW10ms;
	DWORD dwDataQhImpW10ms;
	DWORD dwDataPhExpW10ms;
	DWORD dwDataQhExpW10ms;
	WORD wDataPE[4];
};


//-----------------------------------------------------------------------------
#undef CLASSNAME_APP
#define CLASSNAME_APP CMyAppDMRUnit
class CMyAppDMRUnit:public CMyAppDMR
{
public:
	BOOL m_bLockStatus;
protected:
	CMyAlarmGroupCTM m_alarmgroupCTM;
	CMyAlarmGroupCTP m_alarmgroupCTP;
	CMyAlarmGroupPT m_alarmgroupPT;
protected:
	WORD m_wHardEnableLocal;
	WORD m_wHardEnableRemote;
	WORD m_wLADEnableLocal;
	WORD m_wLADEnableRemote;
public:
	void OnInitParams(void);
	void OnInit(void);
	void OnTimer1ms(void);
	void OnTimer10ms(void);
	void OnTimer1000ms(void);
	void OnInitDevice(void);
	void OnResetDevice(void);
	void OnUpdateDevice(WORD* pData);
public:
	WORD GetBOStatus(void);
	void SetBOErrorCloseFlag(BOOL bError);
	void SetBOErrorOpenFlag(BOOL bError);
	BOOL IsCTMBreak(void);
	BOOL IsCTPBreak(void);
	BOOL IsPTBreak(void);
	void SetBreakerOperateMode(void);
	void HardEnableLocal(BOOL bEnable);
	void HardEnableRemote(BOOL bEnable);
	void LADEnableLocal(BOOL bEnable);
	void LADEnableRemote(BOOL bEnable);
protected:
	void CalculatePE(WORD wIndex);
protected:
	VIRTUAL void iiiOnSetDataMetrics(void);
	VIRTUAL void iiiOnCalculateData(void);
	VIRTUAL void iiiOnRefreshData(void);
	VIRTUAL void iiiOnAlarmDetect(void);
	VIRTUAL void iiiOnRelayOut(void);
	friend class CMyApp;
	friend class CMyAppDMR;
};

extern DEVICEPARAM_UNIT* g_pDeviceParam;
extern ANALOGDATA g_analogData;
extern ANALOGDATAEXT g_analogDataExt;
extern CMyData g_dataIa;
extern CMyData g_dataIb;
extern CMyData g_dataIc;
extern CMyData g_dataIA;
extern CMyData g_dataIB;
extern CMyData g_dataIC;
extern CMyData g_dataUa;
extern CMyData g_dataUb;
extern CMyData g_dataUc;
extern CMyData g_dataUab;
extern CMyData g_dataUbc;
extern CMyData g_dataUca;
extern CMyData g_data3I0;
extern CMyData g_data3U0;
extern CMyData g_data3I2;
extern CMyData g_data3U2;
extern CMyData g_dataF;
extern CMyData g_dataP;
extern CMyData g_dataQ;
extern CMyData g_dataPF;
extern CMyData g_dataIx;
extern CMyData g_dataUxab;
extern CMyData g_dataUxbc;
extern CMyData g_dataUxca;
extern CMyData g_data3Ux2;
extern CMyData g_dataFx;
extern CMyBreakerOperate g_breaker;

#endif/*CMYAPPDMRUNIT_H*/

