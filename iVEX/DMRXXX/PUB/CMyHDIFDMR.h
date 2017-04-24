#ifndef CMyHDIFDMR_H
#define CMyHDIFDMR_H

#include "stdafx.h"

#include "PUB\CMyLCD.h"
#include "PUB\CMyLCDMem.h"
// #include "PUB\CMyArEEPROM.h"
#include "PUB\CMyArRTC.h"
#include "HDLIB\CMyArEEPROM_iVEX.h"
#include "HDLIB\CMyArEEPROM_iVEXMain.h"
#include "HDLIB\CMyArEEPROM_iVEXSub.h"
#include "HDLIB\CMyArRTC_iVEX.h"
#include "HDLIB\CMyComm_iVEX.h"

#define LCD_DEGREE_160x160			LCD_DEGREE_0
#define LCD_DEGREE_240x320			LCD_DEGREE_0

#ifndef CLASSNAME_AR_EEPROMMAIN
#define CLASSNAME_AR_EEPROMMAIN		CMyArEEPROM_iVEXMain
#endif

#ifndef CLASSNAME_AR_EEPROMSUB
#define CLASSNAME_AR_EEPROMSUB		CMyArEEPROM_iVEXSub
#endif

#define INTDisable()
#define INTEnable()

#define GPSTIMEOUT					1050

typedef struct
{
	short nTimeOut;				// 超时错误，每ms+1，收到P0清零，值大于1050认为出错
	DWORD dwCodeErrTotal;		// 收到8\5\2以外代码+1,不清零,溢出清零
	DWORD dwCodeErrCnt;			// 收到8\5\2以外代码+1
	DWORD dwCodeCnt;			// 收到代码总数，误码率=dwCodeErrCnt/dwCodeCnt;
}GPSERR;

//-----------------------------------------------------------------------------
#undef CLASSNAME_HDIF
#define CLASSNAME_HDIF CMyHDIFDMR
class CMyHDIFDMR:public CMyHDIF
{
public:
	WORD m_wFreqINT1;
	WORD m_wFreqINT2;
	WORD m_wPanelDiagCode;
	WORD m_wPWRUPS;
public:
	void OnInit1(void);
	void OnInit2(void);
	void OnPollingComm(void);
	void OnPollingCommET(void);
	void OnTimer10ms(void);
	WORD GetFreqINT1(void);
	WORD GetFreqINT2(void);
	WORD GetPanelDiagCode(void);
	void RestExProtocol(void);
	void InitCom(WORD wIndex);
public:
	VIRTUAL void iiiFlushLights(void){};
	VIRTUAL void iiiFlushRelays(void){};
};

extern CMyComm_iVEX g_comm1;
extern CMyComm_iVEX g_comm2;
extern WORD g_wRateF;

extern DEVICETIME g_GPSTime;
extern GPSERR g_GPSErr;

extern WORD g_wProtocolType;


#endif/*CMyHDIFDMR_H*/