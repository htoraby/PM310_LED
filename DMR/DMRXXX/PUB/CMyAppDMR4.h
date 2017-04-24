#ifndef CMYAPPDMR4_H
#define CMYAPPDMR4_H

#define BOM_NULL			0x0000		//状态无效;
#define BOM_DISABLE			0x3333		//操作禁止;
#define BOM_ENABLE			0x5555		//操作允许;

#define PROTECTACT_NULL		0			//保护动作值:空;
#define PROTECTACT_IP		1			//保护动作值:IP;
#define PROTECTACT_U		2			//保护动作值:U;
#define PROTECTACT_3I0		3			//保护动作值:3I0;
#define PROTECTACT_3U0		4			//保护动作值:3U0;
#define PROTECTACT_Ix		5			//保护动作值:Ix;
#define PROTECTACT_Ux		6			//保护动作值:Ux;
#define PROTECTACT_F		7			//保护动作值:F;
#define PROTECTACT_P		8			//保护动作值:P;

#define DS2_AlarmCTM		0x0001		//告警信号:测量CT断线;
#define DS2_AlarmCTP		0x0002		//告警信号:保护CT断线;
#define DS2_AlarmPT			0x0004		//告警信号:PT断线;
#define DS2_AlarmKM			0x0008		//告警信号:控制电源失电;
#define DS2_AlarmClose		0x0010		//告警信号:合闸回路断线;
#define DS2_AlarmOpen		0x0020		//告警信号:跳闸回路断线;
#define DS2_ErrorClose		0x0040		//告警信号:合闸拒动;
#define DS2_ErrorOpen		0x0080		//告警信号:跳闸拒动;
#define DS2_EnableLocal		0x0100		//本地操作允许;
#define DS2_EnableRemote	0x0200		//遥控操作允许;
#define DS2_DirectP			0x0400		//有功功率方向;
#define DS2_DirectQ			0x0800		//无功功率方向;
#define DS2_LockClose		0x1000		//合闸闭锁;

#define EVENTCODE_LOCALBO		(EVENTCODE_OTHER+0x00)		//本地操作断路器;
#define EVENTCODE_REMOTEBO		(EVENTCODE_OTHER+0x01)		//遥控操作断路器;
#define EVENTCODE_ALARMCTPA		(EVENTCODE_ALARMED+0x00)	//A相保护CT断线;
#define EVENTCODE_ALARMCTPB		(EVENTCODE_ALARMED+0x01)	//B相保护CT断线;
#define EVENTCODE_ALARMCTPC		(EVENTCODE_ALARMED+0x02)	//C相保护CT断线;
#define EVENTCODE_ALARMCTMA		(EVENTCODE_ALARMED+0x03)	//A相测量CT断线;
#define EVENTCODE_ALARMCTMB		(EVENTCODE_ALARMED+0x04)	//B相测量CT断线;
#define EVENTCODE_ALARMCTMC		(EVENTCODE_ALARMED+0x05)	//C相测量CT断线;
#define EVENTCODE_ALARMPT3		(EVENTCODE_ALARMED+0x06)	//三相PT断线;
#define EVENTCODE_ALARMPT2		(EVENTCODE_ALARMED+0x07)	//两相PT断线;
#define EVENTCODE_ALARMPT1		(EVENTCODE_ALARMED+0x08)	//单相PT断线;
#define EVENTCODE_ALARMKM		(EVENTCODE_ALARMED+0x10)	//控制电源失电;
#define EVENTCODE_ALARMCLOSE	(EVENTCODE_ALARMED+0x11)	//合闸回路断线;
#define EVENTCODE_ALARMOPEN		(EVENTCODE_ALARMED+0x12)	//跳闸回路断线;
#define EVENTCODE_ERRORCLOSE	(EVENTCODE_ALARMED+0x13)	//合闸拒动;
#define EVENTCODE_ERROROPEN		(EVENTCODE_ALARMED+0x14)	//跳闸拒动;
#define EVENTCODE_ALARMPUa		(EVENTCODE_ALARMED+0x15)	//2PT中Ua断线;
#define EVENTCODE_ALARMPUb		(EVENTCODE_ALARMED+0x16)	//2PT中Ub断线;
#define EVENTCODE_ALARMPUc		(EVENTCODE_ALARMED+0x17)	//2PT中Uc断线;

#ifndef KPUTIME
#define KPUTIME		20
#endif

struct DEVICEPARAM_DMR4
{
	WORD wModbusAddr1;				// 通讯地址1
	WORD wCANBaud1;					// CAN1波特率
	WORD wModbusAddr2;				// 通讯地址2
	WORD wCANBaud2;					// CAN2波特率
	WORD wSCIBaud;					// SCI波特率
	WORD wAddrIP1[2];				// IP地址1
	WORD wAddrMask1[2];				// 子网掩码1
// 	WORD wGateway[2];				// 网关1
	WORD wAddrIP2[2];				// IP地址2
	WORD wAddrMask2[2];				// 子网掩码2
// 	WORD wGateway2[2];				// 网关2
	WORD wToggleAlarmKM;			// 控制电源失电
	WORD wToggleAlarmClose;			// 合闸回路断线
	WORD wToggleAlarmOpen;			// 跳闸回路断线
	WORD wToggleAlarmCT;			// CT断线告警
	WORD wToggleAlarmPT;			// PT断线告警
	WORD wModeProtect;				// 保护模式:2P,3P
	WORD wModePT;					// PT接线方式:WYE,DEL,UAC
	WORD wScaleCT;					// CT变比
	WORD wScalePT;					// PT变比
	WORD wScale2IM;					// 测量电流量程
	WORD wScale2IP;					// 保护电流量程
	WORD wScale2Uln;				// 电压量程
	WORD wScale23I0;				// 零序电流量程
	WORD wScale23U0;				// 零序电压量程
	WORD wScale2Ix;					// 辅助电流量程
	WORD wScale2Ux;					// 辅助电压量程
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

