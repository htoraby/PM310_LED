/*
;*****************************************************************************************************
;*						Copyright (c) 2009 by ThinkBoy. 
;*						All rights reserved.
;*
;* Header:
;* File Name: 
;* Author: jimmy
;* Date:
;*****************************************************************************************************
;*/

#ifndef _CMYPROTECT_H
#define _CMYPROTECT_H

/******************************************************************************
支持文件:
__Event.*;
g_deviceInfo.wSwitchStatus;
g_app.SetAlarmedFlag();
g_app.SetTrippedFlag();
g_protect.Run();
g_protect.OnProtectActAlarmed();
g_protect.OnProtectActTripped();
*/

#ifndef INSETPOINTNUM
#define INSETPOINTNUM			4			// 开关量保护个数
#endif

#ifndef USERSETPOINTNUM
#define USERSETPOINTNUM			8			// 自定义保护个数
#endif

// #define PROTECTCFG_NULL			0x0000		//关闭;
// #define PROTECTCFG_LAD			0x0001		//梯形图;
// #define PROTECTCFG_ALM			0x0002		//发告警信号;
// #define PROTECTCFG_TRE			0x0003		//发故障信号不动作;
// #define PROTECTCFG_TRP			0x0004		//发故障信号并动作;
// #define PROTECTCFG_TAP			0x0005		//发故障信号并动作,KPU出口;

// enum PROTECTCFG
// {
// 	 PROTECTCFG_NULL = 0		//关闭;
// //	,PROTECTCFG_LAD				//梯形图;
// 	,PROTECTCFG_ALM				//发告警信号;
// 	,PROTECTCFG_TRE				//发故障信号不动作;
// 	,PROTECTCFG_TRP				//发故障信号并动作;
// //	,PROTECTCFG_TAP				//发故障信号并动作,KPU出口;
// };

enum PROTECTTOG
{
	 PROTECTTOG_OFF = 0x0000				//保护退出=TOGGLE_OFF;
	,PROTECTTOG_ON							//保护投入=TOGGLE_ON;
};


#define SETPOINTCFG(a)				(g_deviceSetpoint.wConfig[a])
#define SETPOINTTOG(a)				(g_deviceSetpoint.wToggle[a])
// #define SETPOINTMTX(a)				(g_deviceSetpoint.wTripMatrix[a])
#define SETPOINT(a)					(g_pDeviceSetpoint->a)

//-----------------------------------------------------------------------------
typedef struct _INSETPOINT
{
	WORD wConfig;					// 保护配置;
	WORD wLinkIN;					// 关联开关量;
	WORD wToggle;					// 开关量保护投退;
}INSETPOINT;

//-----------------------------------------------------------------------------
typedef struct _DEVICESETPOINT
{
	WORD wConfig[6];								// 保护配置;
	WORD wToggle[6];								// 保护投退;
// 	WORD wReserved;									// (保留);
// 	WORD wSetpointConfig[3];
//	WORD wProtectSetpointArea;						// 设定的保护定值区;
	WORD wSetpointArea1[24];						// 保护定值区1;
	INSETPOINT INSetpoint[INSETPOINTNUM];			// 开关量保护;
}DEVICESETPOINT;

//-----------------------------------------------------------------------------
typedef struct _SETPOINTCFGINFO
{
	char* pszName;					// 配置中文名称;
	char* pszNameEnglish;			// 配置英文名称;
}SETPOINTCFGINFO;


//-----------------------------------------------------------------------------
typedef struct _PROTECTACTINFO
{
	char* pszName;					// 保护中文名称;
	char* pszNameEnglish;			// 保护英文名称;
	WORD wProtectAct;				// 保护动作值类型;
}PROTECTACTINFO;


//-----------------------------------------------------------------------------
typedef struct _PROTECTACTDATAINFO
{
	char* pszDataName;				// 保护动作值名称;
	char* pszUnitage;				// 保护动作值单位;
	DWORD dwActData;				// 保护动作值;
	WORD wFormat;					// 保护动作值显示格式;
}PROTECTACTDATAINFO;


//-----------------------------------------------------------------------------
extern WORD g_wProtectAct[6];					// 保护动作标志;
extern WORD g_wProtectActIN[INSETPOINTNUM];		// 开关量保护动作标志;
extern DWORD g_dwProtectActed;					// 保护动作标志(自保持),须复归后清除;
extern WORD g_wProtectActedIN;					// 开关量保护动作标志(自保持),须复归后清除;
extern WORD g_wProtectCloseFlag;				// 保护动作引起合闸标志;
extern WORD g_wProtectOpenFlag;					// 保护动作引起跳闸标志;

extern BOOL g_bProtectAct;                      // 总的保护动作标志;

//说明:初始化程序;
extern void Protect_OnInit1(void);
// 开关量保护处理;
extern void Protect_OnTimer1ms(void);
//说明:定时服务程序,自动调用Run();
extern void Protect_OnTimer10ms(void);
extern void Protect_SetProtectAct(WORD wProtectIndexExt,WORD wActData,WORD wActMode);
//说明:执行过量保护;bLock:是否闭锁,若闭锁,则保护计时递减;
extern WORD Protect_ProtectXGE(WORD wProtectIndexExt,WORD wData,WORD wTime,WORD wDataSet,WORD wTimeSet,BOOL bLock);
//说明:执行欠量保护;bLock:是否闭锁,若闭锁,则保护计时递减;
extern WORD Protect_ProtectXLE(WORD wProtectIndexExt,WORD wData,WORD wTime,WORD wDataSet,WORD wTimeSet,BOOL bLock);

extern BOOL Protect_GetAct(void);               // 获取保护动作信号

extern DEVICESETPOINT g_deviceSetpoint;
//说明:全局保护定值;

#endif/*_CMYPROTECT_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/

