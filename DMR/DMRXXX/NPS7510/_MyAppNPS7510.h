#ifndef __IBCU2140L_H
#define __IBCU2140L_H

#define LINKOUT_ALARMED
#define LINKOUT_TRIPPED
#define LINKOUT_ERRORED

#define BOM_NULL			0x0000		//状态无效;
#define BOM_DISABLE			0x3333		//操作禁止;
#define BOM_ENABLE			0x5555		//操作允许;

#define PROTECTACT_NULL		0			//保护动作值:空;
#define PROTECTACT_IP		1			//保护动作值:IP;
#define PROTECTACT_U		2			//保护动作值:U;
#define PROTECTACT_3I0		3			//保护动作值:3I0;

#define DS2_AlarmPT			0x0001		//告警信号:PT断线;
#define DS2_AlarmKM			0x0002		//告警信号:控制电源失电;

#define EVENTCODE_ALARMPT3		(EVENTCODE_ALARMED+0x00)	//三相PT断线;
#define EVENTCODE_ALARMPT2		(EVENTCODE_ALARMED+0x01)	//两相PT断线;
#define EVENTCODE_ALARMPT1		(EVENTCODE_ALARMED+0x02)	//单相PT断线;
#define EVENTCODE_ALARMKM		(EVENTCODE_ALARMED+0x03)    //控制回路断线;

typedef struct _DEVICEPARAM_IBCU2
{
    WORD wToggleAlarmPT;			// PT断线告警
    WORD wModePT;
    WORD wScaleCT;
    WORD wScalePT;
    WORD wSLType;
}DEVICEPARAM_IBCU2;

typedef struct _ANALOGDATA
{
    WORD wDataIa;
    WORD wDataIb;
    WORD wDataIc;
    WORD wDataUa;
    WORD wDataUb;
    WORD wDataUc;
    WORD wDataUab;
    WORD wDataUbc;
    WORD wDataUca;
//    WORD wData3I0;
    WORD wDataF;
    short nDataP;
    short nDataQ;
    short nDataS;
    short nDataPF;
    short nAngIa;
    short nAngIb;
    short nAngIc;
    short nAngUa;
    short nAngUb;
    short nAngUc;
    short nAngUab;
    short nAngUbc;
    short nAngUca;
}ANALOGDATA;

typedef struct
{
    DWORD dwDataPhImp;
    DWORD dwDataQhImp;
    DWORD dwDataPhExp;
    DWORD dwDataQhExp;
    DWORD dwDataPhImpW10ms;
    DWORD dwDataQhImpW10ms;
    DWORD dwDataPhExpW10ms;
    DWORD dwDataQhExpW10ms;
}ANALOGDATAEXT;

#define MyApp_OnUpdateDeviceSub(pwData)

#ifdef __cplusplus
extern "C" {
#endif

extern void MyApp_OnInitSubParam(void);
extern void MyApp_OnInitsub(void);
extern void MyApp_OnSetDataMetrics(void);
extern void MyApp_OnResetSubDevice(void);
extern void MyApp_OnCalculateData(void);
extern void MyApp_OnAlarmDetect(void);
extern void MyApp_OnRefreshData(void);
extern BOOL MyApp_IsPTBreak(void);
extern BOOL MyApp_IsOpenBreak(void);
extern void MyApp_OnWaveRecord(WORD wCountAD);
extern void MyApp_SetWaveRecordK(WAVERECORD* pWaveRecord);
extern short MyApp_GetDataSecondary(MyData* pData,  short nData, BOOL bSignedType);

extern DEVICEPARAM_IBCU2* g_pDeviceParam;
extern ANALOGDATA g_analogData;
extern ANALOGDATAEXT g_analogDataExt;
extern MyData g_dataIa;
extern MyData g_dataIb;
extern MyData g_dataIc;
// extern MyData g_dataIA;
// extern MyData g_dataIB;
// extern MyData g_dataIC;
// extern MyData g_data3I0;
// extern MyData g_data3I2;
extern MyData g_dataUa;
extern MyData g_dataUb;
extern MyData g_dataUc;
extern MyData g_dataUab;
extern MyData g_dataUbc;
extern MyData g_dataUca;
// extern MyData g_data3U0;
// extern MyData g_data3U2;
extern MyData g_dataF;

extern MyData g_dataP;
extern MyData g_dataQ;
extern MyData g_dataS;
extern MyData g_dataPF;
// extern WORD g_wCountAfterClosed;

extern const REGULATE g_Ref[DFT_CHANNEL_HARD];


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__IBCU2140L_H*/
