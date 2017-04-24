#define LINKOUT_ALARMED
#define LINKOUT_TRIPPED
#define LINKOUT_ERRORED

#define BOM_NULL			0x0000		//״̬��Ч;
#define BOM_DISABLE			0x3333		//������ֹ;
#define BOM_ENABLE			0x5555		//��������;

#define PROTECTACT_NULL		0			//��������ֵ:��;
#define PROTECTACT_U		1			//��������ֵ:U;
#define PROTECTACT_3U0		2			//��������ֵ:3U0;

#define DS2_Alarm1XPT		0x0001		//�澯�ź�:1#PT����;
#define DS2_Alarm2XPT		0x0002		//�澯�ź�:2#PT����;
#define DS2_EnableLocal		0x0100		//���ز�������;
#define DS2_EnableRemote	0x0200		//ң�ز�������;
#define DS2_EnableLink		0x1000		//��������;
#define DS2_AutoMode		0x2000		//�Զ�ģʽ;
#define DS2_Status1XPT		0x4000		//1#PT����״̬;
#define DS2_Status2XPT		0x8000		//2#PT����״̬;

#define EVENTCODE_LOCALBO		(EVENTCODE_OTHER+0x00)		//���ز������м̵���;
#define EVENTCODE_REMOTEBO		(EVENTCODE_OTHER+0x01)		//ң�ز������м̵���;
#define EVENTCODE_AUTOLINK		(EVENTCODE_OTHER+0x02)		//�Զ��������м̵���;
#define EVENTCODE_STATUS1XPT	(EVENTCODE_OTHER+0x03)		//1#PT����״̬;
#define EVENTCODE_STATUS2XPT	(EVENTCODE_OTHER+0x04)		//2#PT����״̬;
#define EVENTCODE_ALARM1XPT3	(EVENTCODE_ALARMED+0x00)	//1#PT�������;
#define EVENTCODE_ALARM1XPT2	(EVENTCODE_ALARMED+0x01)	//1#PT�������;
#define EVENTCODE_ALARM1XPT1	(EVENTCODE_ALARMED+0x02)	//1#PT�������;
#define EVENTCODE_ALARM2XPT3	(EVENTCODE_ALARMED+0x03)	//2#PT�������;
#define EVENTCODE_ALARM2XPT2	(EVENTCODE_ALARMED+0x04)	//2#PT�������;
#define EVENTCODE_ALARM2XPT1	(EVENTCODE_ALARMED+0x05)	//2#PT�������;

//-----------------------------------------------------------------------------
// Not Used In DMRX81P, Only Support for Breaker10 Module;
#define EVENTCODE_ALARMKM		(EVENTCODE_ALARMED+0x10)	//���Ƶ�Դʧ��;
#define EVENTCODE_ALARMCLOSE	(EVENTCODE_ALARMED+0x11)	//��բ��·����;
#define EVENTCODE_ALARMOPEN		(EVENTCODE_ALARMED+0x12)	//��բ��·����;
#define EVENTCODE_ERRORCLOSE	(EVENTCODE_ALARMED+0x13)	//��բ�ܶ�;
#define EVENTCODE_ERROROPEN		(EVENTCODE_ALARMED+0x14)	//��բ�ܶ�;

//-----------------------------------------------------------------------------
struct THDINFO
{
	WORD wTHD;
	WORD wTHD2;
	WORD wTHD3;
	WORD wTHD4;
	WORD wTHD5;
	WORD wTHD6;
	WORD wTHD7;
	WORD wTHD8;
	WORD wTHD9;
	WORD wTHD10;
	WORD wTHD11;
};

struct DEVICEPARAM_DMRX81P
{
	WORD wToggleAlarm1XPT;
	WORD wToggleAlarm2XPT;
	WORD wToggleProtect1XPT;
	WORD wToggleProtect2XPT;
	WORD wModePT;
	WORD wScalePT;
	WORD wScale2Uln;
	WORD wScale23U0;
	WORD wModeTHD;
};

struct ANALOGDATA
{
	WORD wData1XUa;
	WORD wData1XUb;
	WORD wData1XUc;
	WORD wData1XUab;
	WORD wData1XUbc;
	WORD wData1XUca;
	WORD wData1X3U0;
	WORD wData1X3U2;
	WORD wData1XF;
	WORD wData2XUa;
	WORD wData2XUb;
	WORD wData2XUc;
	WORD wData2XUab;
	WORD wData2XUbc;
	WORD wData2XUca;
	WORD wData2X3U0;
	WORD wData2X3U2;
	WORD wData2XF;
};

struct ANALOGDATAEXT
{
	THDINFO ti1XUa;
	THDINFO ti1XUb;
	THDINFO ti1XUc;
	THDINFO ti2XUa;
	THDINFO ti2XUb;
	THDINFO ti2XUc;
};


//-----------------------------------------------------------------------------
#undef CLASSNAME_APP
#define CLASSNAME_APP CMyAppDMRX81P
class CMyAppDMRX81P:public CMyAppDMR
{
public:
	CMyAlarmGroupPT m_alarmgroup1XPT;
	CMyAlarmGroupPT m_alarmgroup2XPT;
protected:
	WORD m_wHardEnableAuto;
	WORD m_wHardEnableLocal;
	WORD m_wHardEnableRemote;
	WORD m_wLADEnableAuto;
	WORD m_wLADEnableLocal;
	WORD m_wLADEnableRemote;
	WORD m_wLADHandClose;
	WORD m_wLADHandOpen;
protected:
	WORD m_wTimerTHD;
	CMyFilter m_filter1XUa[10];
	CMyFilter m_filter1XUb[10];
	CMyFilter m_filter1XUc[10];
	CMyFilter m_filter2XUa[10];
	CMyFilter m_filter2XUb[10];
	CMyFilter m_filter2XUc[10];
public:
	void OnInitParams(void);
	void OnInit(void);
	void OnTimer1ms(void);
	void OnTimer10ms(void);
	void OnTimer1000ms(void);
	void OnInitDevice(void);
	void OnResetDevice(void);
	void OnUpdateDevice(WORD* pData);
	void OnWaveRecord(WORD wCountAD);
public:
	WORD GetBOStatus(void);
	void SetBOErrorCloseFlag(BOOL bError){};
	void SetBOErrorOpenFlag(BOOL bError){};
	BOOL Is1XPTBreak(void);
	BOOL Is2XPTBreak(void);
	void SetBreakerOperateMode(void);
	void HardEnableAuto(BOOL bEnable);
	void HardEnableLocal(BOOL bEnable);
	void HardEnableRemote(BOOL bEnable);
	void LADEnableAuto(BOOL bEnable);
	void LADEnableLocal(BOOL bEnable);
	void LADEnableRemote(BOOL bEnable);
	void LADHandClose(void);
	void LADHandOpen(void);
protected:
	VIRTUAL void iiiOnSetDataMetrics(void);
	VIRTUAL void iiiOnCalculateData(void);
	VIRTUAL void iiiOnRefreshData(void);
	VIRTUAL void iiiOnAlarmDetect(void);
	VIRTUAL void iiiOnRelayOut(void);
	friend class CMyApp;
	friend class CMyAppDMR;
};

extern DEVICEPARAM_DMRX81P* g_pDeviceParam;
extern ANALOGDATA g_analogData;
extern ANALOGDATAEXT g_analogDataExt;
extern CMyData g_data1XUa;
extern CMyData g_data1XUb;
extern CMyData g_data1XUc;
extern CMyData g_data1XUab;
extern CMyData g_data1XUbc;
extern CMyData g_data1XUca;
extern CMyData g_data1X3U0;
extern CMyData g_data1X3U2;
extern CMyData g_data1XF;
extern CMyData g_data2XUa;
extern CMyData g_data2XUb;
extern CMyData g_data2XUc;
extern CMyData g_data2XUab;
extern CMyData g_data2XUbc;
extern CMyData g_data2XUca;
extern CMyData g_data2X3U0;
extern CMyData g_data2X3U2;
extern CMyData g_data2XF;
extern CMyBreakerOperate g_breaker;

