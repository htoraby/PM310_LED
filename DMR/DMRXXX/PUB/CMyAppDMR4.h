#ifndef CMYAPPDMR4_H
#define CMYAPPDMR4_H

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
#define PROTECTACT_P		8			//��������ֵ:P;

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
#define EVENTCODE_ALARMPUa		(EVENTCODE_ALARMED+0x15)	//2PT��Ua����;
#define EVENTCODE_ALARMPUb		(EVENTCODE_ALARMED+0x16)	//2PT��Ub����;
#define EVENTCODE_ALARMPUc		(EVENTCODE_ALARMED+0x17)	//2PT��Uc����;

#ifndef KPUTIME
#define KPUTIME		20
#endif

struct DEVICEPARAM_DMR4
{
	WORD wModbusAddr1;				// ͨѶ��ַ1
	WORD wCANBaud1;					// CAN1������
	WORD wModbusAddr2;				// ͨѶ��ַ2
	WORD wCANBaud2;					// CAN2������
	WORD wSCIBaud;					// SCI������
	WORD wAddrIP1[2];				// IP��ַ1
	WORD wAddrMask1[2];				// ��������1
// 	WORD wGateway[2];				// ����1
	WORD wAddrIP2[2];				// IP��ַ2
	WORD wAddrMask2[2];				// ��������2
// 	WORD wGateway2[2];				// ����2
	WORD wToggleAlarmKM;			// ���Ƶ�Դʧ��
	WORD wToggleAlarmClose;			// ��բ��·����
	WORD wToggleAlarmOpen;			// ��բ��·����
	WORD wToggleAlarmCT;			// CT���߸澯
	WORD wToggleAlarmPT;			// PT���߸澯
	WORD wModeProtect;				// ����ģʽ:2P,3P
	WORD wModePT;					// PT���߷�ʽ:WYE,DEL,UAC
	WORD wScaleCT;					// CT���
	WORD wScalePT;					// PT���
	WORD wScale2IM;					// ������������
	WORD wScale2IP;					// ������������
	WORD wScale2Uln;				// ��ѹ����
	WORD wScale23I0;				// �����������
	WORD wScale23U0;				// �����ѹ����
	WORD wScale2Ix;					// ������������
	WORD wScale2Ux;					// ������ѹ����
#ifdef DCOUT_COUNT
	WORD wDCOUTLink[DCOUT_COUNT];
#endif/*DCOUT_COUNT*/
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
	WORD wDataUxa;
	WORD wDataUxb;
	WORD wDataUxc;
	WORD wDataUxab;
	WORD wDataUxbc;
	WORD wDataUxca;
	WORD wData3Ux0;
	WORD wData3Ux2;
	WORD wDataFx;
#ifdef DCIN_COUNT
	WORD wDataDC[DCIN_COUNT];
#endif/*DCIN_COUNT*/
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
#define CLASSNAME_APP CMyAppDMR4
class CMyAppDMR4:public CMyAppDMR
{
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
	void OnWhileLoop(void);
	void OnInitDevice(void);
	void OnResetDevice(void);
	void OnUpdateDevice(WORD* pData);
public:
	short GetDataDC(WORD wIndex);
	WORD GetBOStatus(void* pBreaker);
	void SetBOErrorCloseFlag(void* pBreaker,BOOL bError);
	void SetBOErrorOpenFlag(void* pBreaker,BOOL bError);
	void AddBOEvent(void* pBreaker,WORD wEventType,WORD wEventCode,WORD wEventData);
	BOOL IsCTMBreak(void);
	BOOL IsCTPBreak(void);
	BOOL IsPTBreak(void);
	void SetBreakerOperateMode(void);
	void HardEnableLocal(BOOL bEnable);
	void HardEnableRemote(BOOL bEnable);
	void LADEnableLocal(BOOL bEnable);
	void LADEnableRemote(BOOL bEnable);
protected:
// 	void CalculatePE(WORD wIndex);
protected:
	VIRTUAL void iiiOnSetDataMetrics(void);
	VIRTUAL void iiiOnCalculateData(void);
	VIRTUAL void iiiOnRefreshData(void);
	VIRTUAL void iiiOnAlarmDetect(void);
	VIRTUAL void iiiOnRelayOut(void);
	friend class CMyApp;
	friend class CMyAppDMR;
};

extern DEVICEPARAM_DMR4* g_pDeviceParam;
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
extern CMyData g_dataUxa;
extern CMyData g_dataUxb;
extern CMyData g_dataUxc;
extern CMyData g_dataUxab;
extern CMyData g_dataUxbc;
extern CMyData g_dataUxca;
extern CMyData g_data3Ux0;
extern CMyData g_data3Ux2;
extern CMyData g_dataFx;
extern CMyBreakerOperate g_breaker;
#ifdef DCIN_COUNT
extern CMyData g_dataDC[DCIN_COUNT];
#endif/*DCIN_COUNT*/
#ifdef _CMYDCPROCESS_H
extern CLASSNAME_DCPROCESS g_dcprocess;
#endif/*_CMYDCPROCESS_H*/

#endif/*CMYAPPDMR4_H*/

