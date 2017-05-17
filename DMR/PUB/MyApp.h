#ifndef __MYAPP_H
#define __MYAPP_H

#ifndef EVENT_COUNT
#define EVENT_COUNT			8
#endif/*EVENT_COUNT*/

#define SetAlarmedFlag												\
	do																\
	{																\
		g_deviceInfo.wDeviceStatus1 |= DS1_Alarmed;					\
		g_bDInfoChanged = TRUE;										\
	}while(0)


#define SetTrippedFlag												\
	do																\
	{																\
		g_deviceInfo.wDeviceStatus1 |= DS1_Tripped;					\
		g_bDInfoChanged = TRUE;										\
	}while(0)

#define DS1_Alarmed			0x0001		//总告警信号;
#define DS1_Tripped			0x0002		//总故障信号;
#define DS1_Errored			0xfffc		//总自检信号;
#define DS1_ErrorParam		0x0004		//自检:设备参数;
#define DS1_ErrorRegulate	0x0008		//自检:精度校正系数;
#define DS1_ErrorSetpoint	0x0010		//自检:保护定值;
#define DS1_ErrorAD			0x0020		//自检:A/D通道;
#define DS1_ErrorTime		0x0040		//自检:Time芯片;

#define DS3_DeviceReset		0x0800		//复归信号;

enum Relay
{
    Relay_J1 = 0,                   // 跳闸
    Relay_J2                       // 合闸
};


// #define EEPROMADDR_DeviceStatus				8
// #define EEPROMADDR_DeviceParam				(EEPROMADDR_DeviceStatus+12+SIZEOFBYTE(g_deviceInfo))
// #define EEPROMADDR_DeviceInParam			(EEPROMADDR_DeviceParam+12+SIZEOFBYTE(g_deviceParam))
// #define EEPROMADDR_DeviceRegulate			(EEPROMADDR_DeviceParam+12+SIZEOFBYTE(g_deviceParam))
// #define EEPROMADDR_DeviceSetpoint			(EEPROMADDR_DeviceRegulate+12+SIZEOFBYTE(g_regulateSet))
// #define EEPROMADDR_EventTable				(EEPROMADDR_DeviceSetpoint+12+SIZEOFBYTE(g_deviceSetpoint))

#define BLOCKSIZE							4096L		// Flash扇区大小:4kByte
#define BLOCKCOUNT(b)						((((DWORD)b)+8L+(BLOCKSIZE-1))/BLOCKSIZE)
#define BLOCKADDRMAIN(a,b)					((((DWORD)a)+((DWORD)b)+8L+BLOCKSIZE-1) & ~(BLOCKSIZE-1))

#define EEPROMADDR_DeviceStatus				8
#define EEPROMADDR_DeviceParam				BLOCKADDRMAIN(EEPROMADDR_DeviceStatus,SIZEOFBYTE(DEVICEPARAM))
// #define EEPROMADDR_DeviceInParam			(EEPROMADDR_DeviceParam+12+SIZEOFBYTE(g_deviceParam))
#define EEPROMADDR_DeviceRegulate			BLOCKADDRMAIN(EEPROMADDR_DeviceParam, SIZEOFBYTE(g_deviceParam))
#define EEPROMADDR_DeviceSetpoint			BLOCKADDRMAIN(EEPROMADDR_DeviceRegulate, SIZEOFBYTE(g_regulateSet))
#define EEPROMADDR_EventTable				BLOCKADDRMAIN(EEPROMADDR_DeviceSetpoint, SIZEOFBYTE(g_deviceSetpoint))

//#ifdef __WAVERECORD_H
//#define EEPROMADDR_WaveRecordX(i)			(EEPROMADDR_EventTable+(DWORD)i*BLOCKSIZE*BLOCKCOUNT(SIZEOFBYTE(WAVERECORD)))
//#endif

#ifdef __WAVERECORD_H
#define EEPROMADDR_WaveRecord				BLOCKADDRMAIN(EEPROMADDR_EventTable, SIZEOFBYTE(EVENTTABLE))
#define EEPROMADDR_WaveRecordX(i)			(EEPROMADDR_WaveRecord+(DWORD)i*BLOCKSIZE*BLOCKCOUNT(SIZEOFBYTE(WAVERECORD)))
#endif

#define BLOCKADDRSUB(a,b)					(a+b+20)
#define EEPROMADDR_ANALOGEXT1               0

#define EEPROMADDR_Max                      BLOCKADDRSUB(EEPROMADDR_ANALOGEXT1,SIZEOFBYTE(EVENTTABLE))

typedef struct _DEVICEINFO
{
	WORD wDeviceType;					// 设备类型代码
	WORD wSwitchStatus1;				// 开关量状态 0~15
	WORD wSwitchStatus2;				// 开关量状态16~31
	// --------------------需要保存---------------------------------
	WORD wNumPwrup;						// 启动次数 Number of Power ups
	WORD wWrmStr;						// 热启次数 Number of Warm Starts
	WORD wDeviceStatus1;				// 自检信息
	WORD wDeviceStatus2;
	// ------------------------------------------------------------
	WORD wDeviceStatus3;
	WORD wDeviceStatus4;
	WORD wExtID;
	WORD wSelfTestMain;					// 主存储器自检信息
	WORD wSelfTestSub;					// 从存储器自检信息
	WORD wCountAll;
	WORD wCountEventTable;
	WORD wCountWaveRecord;
	WORD wCountDeviceParam;
	WORD wCountDeviceRegulate;
	WORD wCountDeviceSetpoint;
	WORD wMainVersion;
	WORD wSubVersion;
	WORD wLCDHeigh;
	WORD wLCDWidth;
    WORD wCRC;
// 	WORD wReserved;
}DEVICEINFO;

typedef struct _DEVICEPARAM
{
	WORD wLCDContrast;					// LCD对比度
	WORD wszDeviceType[17];				// 设备名称
	WORD wMultiLanguage;				// 界面语言
	WORD wModbusAddr1;					//通信地址
	WORD wBaudrate1;					//通信速率
	WORD wReserved[11];					// 保留:具体型号特有参数
}DEVICEPARAM;

#ifdef __cplusplus
extern "C" {
#endif

extern void MyApp_OnInit(void);
extern void MyApp_OnInitParams(void);
extern void MyApp_OnInitDevice(void);
extern void MyApp_OnTimer1ms(void);
extern void MyApp_OnTimer10ms(void);
extern void MyApp_OnTimer1000ms(void);
extern void MyApp_OnWhileLoop(void);
extern void MyApp_OnResetDevice(void);
extern void MyApp_OnUpdateDevice(WORD* pwData, BOOL bRemote);
extern void MyApp_OnRelayOut(void);
extern void MyApp_TestRelay(WORD wIndex);

extern void MyApp_OnTimerSample(WORD wIndex);

// extern void MyApp_OnWaveRecordEx(WORD wSwitchStatus,WORD wData1,WORD wData2,WORD wData3,WORD wData4,WORD wData5,WORD wData6,WORD wData7,WORD wData8);


extern DEVICEINFO g_deviceInfo;
extern DEVICEPARAM g_deviceParam;
extern DEVICETIME g_deviceTime;
extern MyOutput g_relayKH[RELAYKH_COUNT];
#ifdef RELAYKOT_COUNT
extern MyOutput g_relayKOT[RELAYKOT_COUNT];
#endif/*RELAYKOT_COUNT*/

extern WORD g_wFreq;
extern WORD g_wCountAllOld;
extern BOOL g_bDInfoChanged;
extern DWORD g_dwSystick;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__MYAPP_H*/
