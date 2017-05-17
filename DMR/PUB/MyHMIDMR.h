#ifndef CMYHMIDMR_H
#define CMYHMIDMR_H

// #include "PUB\__Key.h"
// #include "PUB\__Edit.h"

#ifndef MULTI_LANGUAGE
#define MULTITEXT(szCH,szEN)	((char*)szCH)
#else
#define MULTITEXT(szCH,szEN)	((g_deviceParam.wMultiLanguage==0)?(char*)szCH:(char*)szEN)
#endif

#define ISENGLISH				(g_deviceParam.wMultiLanguage!=0)

enum DISPLAY_INDEX
{
    INDEX_ANALOG = 0x0000,          // 显示索引号基址:模拟量;
    INDEX_ANALOGEX = 0x2000,        // 显示索引号基址:扩展模拟量;
    INDEX_ALARMED = 0x40000,        // 显示索引号基址:告警信号;
    INDEX_ERRORED = 0x60000,        // 显示索引号基址:自检信号;
    INDEX_PARAM = 0x80000,          // 显示索引号基址:设备参数;
};


#ifndef LIGHTBAKCNT
#define LIGHTBAKCNT			8
#endif

enum IndexErrored
{
	_INDEX_ERRORED = INDEX_ERRORED
	,INDEX_DEVICETYPE
	,INDEX_VERSION
	,INDEX_DATE
	,INDEX_TIME
	,INDEX_NUMPWRUPS
	,INDEX_WRMSTR
	,INDEX_EXTANDID
	,INDEX_ERRORED_PARAM
	,INDEX_ERRORED_INPARAM
	,INDEX_ERRORED_DCPARAM
	,INDEX_ERRORED_REGULATE
	,INDEX_ERRORED_SETPOINT
	,INDEX_ERRORED_DRW
	,INDEX_ERRORED_LAD
	,INDEX_ERRORED_AD
	,INDEX_ERRORED_DC
	,INDEX_ERRORED_TIME
	,INDEX_ERRORED_FLASH
	,INDEX_ERRORED_PANEL
    ,INDEX_CRCINFO
};

enum IndexParam
{
	_INDEX_PARAM = INDEX_PARAM
	,INDEX_PARAM_DEVICETYPE
	,INDEX_PARAM_PASSWORD1
	,INDEX_PARAM_PASSWORD2
	,INDEX_PARAM_LCDCONTRAST
	,INDEX_PARAM_LIGHTMODE
	,INDEX_PARAM_COMMADDR
	,INDEX_PARAM_COMMBUADRATE
	,INDEX_PARAM_LINKOUTALARMED
	,INDEX_PARAM_LINKOUTTRIPPED
	,INDEX_PARAM_LINKOUTERRORED
	,INDEX_PARAM_TOGINDC
	,INDEX_PARAM_INPOWERTYPE
	,INDEX_PARAM_PROTECTKHMODE
	,INDEX_PARAM_PROTECTKHSET
	,INDEX_PARAM_MULTILANGUAGE
	,INDEX_PARAM_RATEFREQUENCY
	,INDEX_PARAM_RESERVED
};

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
extern void MyHMI_OnInit(void);
extern void MyHMI_OnTimer10ms(void);
extern void MyHMI_OnTimer250ms(void);
extern void MyHMI_OnTimer1000ms(void);
extern void MyHMI_OnWhileLoop(void);
extern void MyHMI_OnUpdateDevice(void);
extern void MyHMI_OnResetDevice(void);
extern void MyHMI_AddEventText(char* pszText);
extern void MyHMI_AddEventTextW(WORD* pszwText);
extern WORD MyHMI_GetPasswordMode(WORD wInputPassword);
// extern char* MyHMI_GetEventText(EVENT* pEvent);
extern void MyHMI_AutoLCDDataOut(WORD wIndex);
extern void MyHMI_GetEditMetrics(WORD* pData);
extern void MyHMI_TestLights(void);
extern void MyHMI_iiiOnWhileLoopExt(WORD wKeyCode);

extern void MyHMI_OnRefresh(WORD wRefreshMode);

// extern const char c_szSCIBaudRate[3][6];
// extern const char c_szCANBaudRate[8][5];
// // extern const char c_szLinkIn[][5];
// // extern const char c_szLinkOut[][5];
// // extern const char c_szEventType[3][8];
// // extern const char c_szProtectCFG[4][4];
// extern const char c_szProtectTOG[][4];

// extern MyKey g_key;
// extern MyEditGroup g_edit;
// extern MyOutput g_lightRun;
// // extern MyOutput g_lightComm;
// extern MyOutput g_lightErrored;
// extern MyOutput g_lightAlarmed;
// extern MyOutput g_lightTripped;
// extern MyOutput g_lightBakGRN[LIGHTBAKCNT];
// extern MyOutput g_lightBakRED[LIGHTBAKCNT];

// extern char g_szEventText[41];
// extern WORD g_wCountEventText;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*CMYHMIDMR_H*/



