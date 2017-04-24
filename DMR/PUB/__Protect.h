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
֧���ļ�:
__Event.*;
g_deviceInfo.wSwitchStatus;
g_app.SetAlarmedFlag();
g_app.SetTrippedFlag();
g_protect.Run();
g_protect.OnProtectActAlarmed();
g_protect.OnProtectActTripped();
*/

#ifndef INSETPOINTNUM
#define INSETPOINTNUM			4			// ��������������
#endif

#ifndef USERSETPOINTNUM
#define USERSETPOINTNUM			8			// �Զ��屣������
#endif

// #define PROTECTCFG_NULL			0x0000		//�ر�;
// #define PROTECTCFG_LAD			0x0001		//����ͼ;
// #define PROTECTCFG_ALM			0x0002		//���澯�ź�;
// #define PROTECTCFG_TRE			0x0003		//�������źŲ�����;
// #define PROTECTCFG_TRP			0x0004		//�������źŲ�����;
// #define PROTECTCFG_TAP			0x0005		//�������źŲ�����,KPU����;

// enum PROTECTCFG
// {
// 	 PROTECTCFG_NULL = 0		//�ر�;
// //	,PROTECTCFG_LAD				//����ͼ;
// 	,PROTECTCFG_ALM				//���澯�ź�;
// 	,PROTECTCFG_TRE				//�������źŲ�����;
// 	,PROTECTCFG_TRP				//�������źŲ�����;
// //	,PROTECTCFG_TAP				//�������źŲ�����,KPU����;
// };

enum PROTECTTOG
{
	 PROTECTTOG_OFF = 0x0000				//�����˳�=TOGGLE_OFF;
	,PROTECTTOG_ON							//����Ͷ��=TOGGLE_ON;
};


#define SETPOINTCFG(a)				(g_deviceSetpoint.wConfig[a])
#define SETPOINTTOG(a)				(g_deviceSetpoint.wToggle[a])
// #define SETPOINTMTX(a)				(g_deviceSetpoint.wTripMatrix[a])
#define SETPOINT(a)					(g_pDeviceSetpoint->a)

//-----------------------------------------------------------------------------
typedef struct _INSETPOINT
{
	WORD wConfig;					// ��������;
	WORD wLinkIN;					// ����������;
	WORD wToggle;					// ����������Ͷ��;
}INSETPOINT;

//-----------------------------------------------------------------------------
typedef struct _DEVICESETPOINT
{
	WORD wConfig[6];								// ��������;
	WORD wToggle[6];								// ����Ͷ��;
// 	WORD wReserved;									// (����);
// 	WORD wSetpointConfig[3];
//	WORD wProtectSetpointArea;						// �趨�ı�����ֵ��;
	WORD wSetpointArea1[24];						// ������ֵ��1;
	INSETPOINT INSetpoint[INSETPOINTNUM];			// ����������;
}DEVICESETPOINT;

//-----------------------------------------------------------------------------
typedef struct _SETPOINTCFGINFO
{
	char* pszName;					// ������������;
	char* pszNameEnglish;			// ����Ӣ������;
}SETPOINTCFGINFO;


//-----------------------------------------------------------------------------
typedef struct _PROTECTACTINFO
{
	char* pszName;					// ������������;
	char* pszNameEnglish;			// ����Ӣ������;
	WORD wProtectAct;				// ��������ֵ����;
}PROTECTACTINFO;


//-----------------------------------------------------------------------------
typedef struct _PROTECTACTDATAINFO
{
	char* pszDataName;				// ��������ֵ����;
	char* pszUnitage;				// ��������ֵ��λ;
	DWORD dwActData;				// ��������ֵ;
	WORD wFormat;					// ��������ֵ��ʾ��ʽ;
}PROTECTACTDATAINFO;


//-----------------------------------------------------------------------------
extern WORD g_wProtectAct[6];					// ����������־;
extern WORD g_wProtectActIN[INSETPOINTNUM];		// ����������������־;
extern DWORD g_dwProtectActed;					// ����������־(�Ա���),�븴������;
extern WORD g_wProtectActedIN;					// ����������������־(�Ա���),�븴������;
extern WORD g_wProtectCloseFlag;				// �������������բ��־;
extern WORD g_wProtectOpenFlag;					// ��������������բ��־;

extern BOOL g_bProtectAct;                      // �ܵı���������־;

//˵��:��ʼ������;
extern void Protect_OnInit1(void);
// ��������������;
extern void Protect_OnTimer1ms(void);
//˵��:��ʱ�������,�Զ�����Run();
extern void Protect_OnTimer10ms(void);
extern void Protect_SetProtectAct(WORD wProtectIndexExt,WORD wActData,WORD wActMode);
//˵��:ִ�й�������;bLock:�Ƿ����,������,�򱣻���ʱ�ݼ�;
extern WORD Protect_ProtectXGE(WORD wProtectIndexExt,WORD wData,WORD wTime,WORD wDataSet,WORD wTimeSet,BOOL bLock);
//˵��:ִ��Ƿ������;bLock:�Ƿ����,������,�򱣻���ʱ�ݼ�;
extern WORD Protect_ProtectXLE(WORD wProtectIndexExt,WORD wData,WORD wTime,WORD wDataSet,WORD wTimeSet,BOOL bLock);

extern BOOL Protect_GetAct(void);               // ��ȡ���������ź�

extern DEVICESETPOINT g_deviceSetpoint;
//˵��:ȫ�ֱ�����ֵ;

#endif/*_CMYPROTECT_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/

