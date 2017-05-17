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

#define DS1_Alarmed			0x0001		//�ܸ澯�ź�;
#define DS1_Tripped			0x0002		//�ܹ����ź�;
#define DS1_Errored			0xfffc		//���Լ��ź�;
#define DS1_ErrorParam		0x0004		//�Լ�:�豸����;
#define DS1_ErrorRegulate	0x0008		//�Լ�:����У��ϵ��;
#define DS1_ErrorSetpoint	0x0010		//�Լ�:������ֵ;
#define DS1_ErrorAD			0x0020		//�Լ�:A/Dͨ��;
#define DS1_ErrorTime		0x0040		//�Լ�:TimeоƬ;

#define DS3_DeviceReset		0x0800		//�����ź�;

enum Relay
{
    Relay_J1 = 0,                   // ��բ
    Relay_J2                       // ��բ
};


// #define EEPROMADDR_DeviceStatus				8
// #define EEPROMADDR_DeviceParam				(EEPROMADDR_DeviceStatus+12+SIZEOFBYTE(g_deviceInfo))
// #define EEPROMADDR_DeviceInParam			(EEPROMADDR_DeviceParam+12+SIZEOFBYTE(g_deviceParam))
// #define EEPROMADDR_DeviceRegulate			(EEPROMADDR_DeviceParam+12+SIZEOFBYTE(g_deviceParam))
// #define EEPROMADDR_DeviceSetpoint			(EEPROMADDR_DeviceRegulate+12+SIZEOFBYTE(g_regulateSet))
// #define EEPROMADDR_EventTable				(EEPROMADDR_DeviceSetpoint+12+SIZEOFBYTE(g_deviceSetpoint))

#define BLOCKSIZE							4096L		// Flash������С:4kByte
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
	WORD wDeviceType;					// �豸���ʹ���
	WORD wSwitchStatus1;				// ������״̬ 0~15
	WORD wSwitchStatus2;				// ������״̬16~31
	// --------------------��Ҫ����---------------------------------
	WORD wNumPwrup;						// �������� Number of Power ups
	WORD wWrmStr;						// �������� Number of Warm Starts
	WORD wDeviceStatus1;				// �Լ���Ϣ
	WORD wDeviceStatus2;
	// ------------------------------------------------------------
	WORD wDeviceStatus3;
	WORD wDeviceStatus4;
	WORD wExtID;
	WORD wSelfTestMain;					// ���洢���Լ���Ϣ
	WORD wSelfTestSub;					// �Ӵ洢���Լ���Ϣ
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
	WORD wLCDContrast;					// LCD�Աȶ�
	WORD wszDeviceType[17];				// �豸����
	WORD wMultiLanguage;				// ��������
	WORD wModbusAddr1;					//ͨ�ŵ�ַ
	WORD wBaudrate1;					//ͨ������
	WORD wReserved[11];					// ����:�����ͺ����в���
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
