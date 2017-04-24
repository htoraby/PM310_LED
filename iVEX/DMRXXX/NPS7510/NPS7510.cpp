/*
;*****************************************************************************************************
;*						Copyright (c) 2000-2012 ThinkBon. 
;*						All rights reserved.
;*
;* Header:
;* File Name: NPS7510.cpp
;* Author: iVexMaker
;* Date: 2015-08-12 13:26:09 32 - Wednesday
;*****************************************************************************************************
;*/
// NPS7510.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "NPS7510.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE NPS7510DLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("NPS7510.DLL Initializing!\n");

		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(NPS7510DLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(NPS7510DLL);
		CMyIED::s_pRuntimeClassRegister = RUNTIME_CLASS(CMyIEDNPS7510);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("NPS7510.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(NPS7510DLL);
	}
	return 1;   // ok
}


// ----------------------------------- CMyIEDNPS7510 -------------------------------
IMPLEMENT_SERIAL(CMyIEDNPS7510,CMyIED,0)

CMyIEDNPS7510::CMyIEDNPS7510():CMyIED()
{
//     m_bCBButtonUsed = FALSE;
    m_wSampleMax = 4096;
}

CMyIEDNPS7510::~CMyIEDNPS7510()
{
}

void CMyIEDNPS7510::OnCreate()
{
    CMyIED::OnCreate();

    m_pLCD = GetObjLCD("LCD");

    m_pKeyUp = GetObjKey("KeyUp");
    m_pKeyDown = GetObjKey("KeyDown");
    m_pKeyOK = GetObjKey("KeyOK");
    m_pKeyCancel = GetObjKey("KeyCancel");
//     m_pKeyReset = GetObjKey("KeyReset");
//     m_pKeyLeft = GetObjKey("KeyLeft");
//     m_pKeyRight = GetObjKey("KeyRight");
//     m_pKeyAdd = GetObjKey("KeyAdd");
//     m_pKeySub = GetObjKey("KeySub");

//     m_pLightRun = GetObjLight("LightRun");
//     m_pLightTripped = GetObjLight("LightTripped");
//     m_pLightAlarmed = GetObjLight("LightAlarmed");
//     m_pLightOpened = GetObjLight("LightOpened");
//     m_pLightClosed = GetObjLight("LightClosed");
}

void CMyIEDNPS7510::OnMainInit()
{
	short i;
	strcpy(g_szFlashDeviceType,(const char*)m_strType);
    strcpy(g_szEEPROMDeviceType,(const char*)m_strType);
	if(m_pLCD)
	{
// 		WORD wLCDCX = (WORD)(m_pLCD->m_rect.right - m_pLCD->m_rect.left);
// 		WORD wLCDCY = (WORD)(m_pLCD->m_rect.bottom - m_pLCD->m_rect.top);
		m_pLCD->SetLCDMetrics(160,160,(BYTE*)LCD_GetLCDBuffer(),FALSE);
	}

	::OnMainInit();

    AddACChannel("Ia","(A)",5.0f,-30,1.5f);
    AddACChannel("Ib","(A)",5.0f,-150,1.5f);
    AddACChannel("Ic","(A)",5.0f,-270,1.5f);
//     AddACChannel("IA","(A)",5.0f,-30,1.5f);
//     AddACChannel("IB","(A)",5.0f,-150,1.5f);
//     AddACChannel("IC","(A)",5.0f,-270,1.5f);
//     AddACChannel("3I0","(A)",0.0f,0,1.5f);
    AddACChannel("Ua","(V)",220.0f,0,1.5f);
    AddACChannel("Ub","(V)",220.0f,-120,1.5f);
    AddACChannel("Uc","(V)",220.0f,-240,1.5f);

    for(i=0;i<SWITCH_COUNT;i++)
    {
        CString strName;
        strName.Format("%s/IN%d", g_pszInName[i], i+1);
        AddINChannel(strName, "分位", "合位", 0);
    }

//     AddOutChannel("YT");
//     AddOutChannel("TZ");
//     AddOutChannel("YH");
//     AddOutChannel("HZ");
//     AddOutChannel("GZ");
//     AddOutChannel("GJ");

    AddOutChannel("J1");
    AddOutChannel("J2");

    CreateDemoPanelDlg();
}

void CMyIEDNPS7510::OnMainTimer1ms()
{
    CMyIED::OnMainTimer1ms();

    ::OnMainTimer1ms();
    ::OnMainPollingComm();

    if(Output_IsOutputValid(&g_relayKH[Relay_J1])) SetCBCoilT();
    else if(Output_IsOutputValid(&g_relayKH[Relay_J2])) SetCBCoilC();

    if(GetCBStatus()==0x3333)
    {
        SetINStatus(9,0);
        SetINStatus(10,1);
    }
    else
    {
        SetINStatus(9,1);
        SetINStatus(10,0);
    }
}

static WORD s_wADBuff[DFT_CHANNEL_HARD][DFT_DOTNUM];

const float PI = 3.1415926535897932384626433832795f;

// void GetADData(WORD* pData, float fSampRate, float fRate, short nSampDot)
// {
//     float fDelAng = fRate/fSampRate*2*PI/nSampDot;
//     static float fAng = 0;
//     for(short i=0;i<nSampDot;i++, fAng += fDelAng)
//     {
//         pData[i] = 2000*sin(fAng)+2000;
//     }
// }

static float fAng[16] = {0};

void CMyIEDNPS7510::GetACWaveDataEx(int nIndex, WORD* pData, float fSampRate,/* float fRate,*/ float f2Scale, short nSampDot, BOOL bBreakPos)
{
    ASSERT(nIndex<16);
    ASSERT(nSampDot>0);
    ASSERT(fSampRate>0);

    float fRate = (float)GetFreqData()*0.01f;
    float fDelAng = fRate/fSampRate*2*PI/nSampDot;
    float fData, fA;
    float fScale = f2Scale*0.01f;
    GetACData(nIndex, fData, fA);
    if(bBreakPos==FALSE)
    {
        fData = 0;
    }
    fA = PI/180*fA;
    fData = (float)m_wSampleMax/2*fData/fScale;
    for(short i=0; i<nSampDot; i++, fAng[nIndex] += fDelAng)
    {
        pData[i] = (WORD)(fData*sin(fAng[nIndex]+fA)+m_wSampleMax/2+0.5);
    }
    while(fAng[nIndex]>=2*PI)
    {
        fAng[nIndex] -= 2*PI;
    }
}

void CMyIEDNPS7510::OnMainTimer10ms()
{
	short i;
	CMyIED::OnMainTimer10ms();
	
	WORD wKeyHardStatus = 0;
	if(m_pKeyUp&&m_pKeyUp->m_bButtonDown) wKeyHardStatus |= KEY_UP;
	if(m_pKeyDown&&m_pKeyDown->m_bButtonDown) wKeyHardStatus |= KEY_DOWN;
// 	if(m_pKeyLeft&&m_pKeyLeft->m_bButtonDown) wKeyHardStatus |= KEY_LEFT;
// 	if(m_pKeyRight&&m_pKeyRight->m_bButtonDown) wKeyHardStatus |= KEY_RIGHT;
	if(m_pKeyOK&&m_pKeyOK->m_bButtonDown) wKeyHardStatus |= KEY_OK;
	if(m_pKeyCancel&&m_pKeyCancel->m_bButtonDown) wKeyHardStatus |= KEY_CANCEL;
// 	if(m_pKeyReset&&m_pKeyReset->m_bButtonDown) wKeyHardStatus |= KEY_RESET;
//     if(m_pKeyAdd&&m_pKeyAdd->m_bButtonDown) wKeyHardStatus |= KEY_ADD;
//     if(m_pKeySub&&m_pKeySub->m_bButtonDown) wKeyHardStatus |= KEY_SUB;
//	if(m_pKeyLED&&m_pKeyLED->m_bButtonDown) wKeyHardStatus |= KEY_LED;
	Key_SetKeyHardCode(wKeyHardStatus);
// 
// 	g_wHDIFFreqINT1 = GetFreqData();
// // 	g_hdif.m_wFreqINT2 = GetFreqData();
//     float fFsam = 10000000.0f/((float)g_wFsam*DFT_DOTNUM)/*g_wFsam*0.01*/;
//     if(fFsam>=75 || fFsam<=45)
//     {
//         fFsam = 50;
//         g_wFsam = 8333;
//     }
    float fFsam = 7200000.0f/((float)g_dwFsam*DFT_DOTNUM)/*g_wFsam*0.01*/;
    if(GetCBStatus()==0x3333)
    {
        GetACWaveDataEx(DFT_Ia,s_wADBuff[DFT_Ia],fFsam,SCALE2IM,DFT_DOTNUM, FALSE);
        GetACWaveDataEx(DFT_Ib,s_wADBuff[DFT_Ib],fFsam,SCALE2IM,DFT_DOTNUM, FALSE);
        GetACWaveDataEx(DFT_Ic,s_wADBuff[DFT_Ic],fFsam,SCALE2IM,DFT_DOTNUM, FALSE);
//         GetACWaveDataEx(DFT_IA,s_wADBuff[DFT_IA],fFsam,10000,DFT_DOTNUM, FALSE);
//         GetACWaveDataEx(DFT_IB,s_wADBuff[DFT_IB],fFsam,10000,DFT_DOTNUM, FALSE);
//         GetACWaveDataEx(DFT_IC,s_wADBuff[DFT_IC],fFsam,10000,DFT_DOTNUM, FALSE);
//         GetACWaveDataEx(DFT_3I0,s_wADBuff[DFT_3I0],fFsam,10000,DFT_DOTNUM, FALSE);
    }
    else
    {
//         GetACWaveData(DFT_Ia,s_wADBuff[DFT_Ia],600,DFT_DOTNUM);
//         GetACWaveData(DFT_Ib,s_wADBuff[DFT_Ib],600,DFT_DOTNUM);
//         GetACWaveData(DFT_Ic,s_wADBuff[DFT_Ic],600,DFT_DOTNUM);
//         GetACWaveData(DFT_IA,s_wADBuff[DFT_IA],10000,DFT_DOTNUM);
//         GetACWaveData(DFT_IB,s_wADBuff[DFT_IB],10000,DFT_DOTNUM);
//         GetACWaveData(DFT_IC,s_wADBuff[DFT_IC],10000,DFT_DOTNUM);
//         GetACWaveData(DFT_3I0,s_wADBuff[DFT_3I0],10000,DFT_DOTNUM);

        GetACWaveDataEx(DFT_Ia,s_wADBuff[DFT_Ia],fFsam,SCALE2IM,DFT_DOTNUM);
        GetACWaveDataEx(DFT_Ib,s_wADBuff[DFT_Ib],fFsam,SCALE2IM,DFT_DOTNUM);
        GetACWaveDataEx(DFT_Ic,s_wADBuff[DFT_Ic],fFsam,SCALE2IM,DFT_DOTNUM);
//         GetACWaveDataEx(DFT_IA,s_wADBuff[DFT_IA],fFsam,10000,DFT_DOTNUM);
//         GetACWaveDataEx(DFT_IB,s_wADBuff[DFT_IB],fFsam,10000,DFT_DOTNUM);
//         GetACWaveDataEx(DFT_IC,s_wADBuff[DFT_IC],fFsam,10000,DFT_DOTNUM);
//         GetACWaveDataEx(DFT_3I0,s_wADBuff[DFT_3I0],fFsam,10000,DFT_DOTNUM);
    }
//     GetACWaveData(DFT_Ua,s_wADBuff[DFT_Ua],12000,DFT_DOTNUM);
//     GetACWaveData(DFT_Ub,s_wADBuff[DFT_Ub],12000,DFT_DOTNUM);
//     GetACWaveData(DFT_Uc,s_wADBuff[DFT_Uc],12000,DFT_DOTNUM);

    GetACWaveDataEx(DFT_Ua,s_wADBuff[DFT_Ua],fFsam,SCALE2ULN,DFT_DOTNUM);
    GetACWaveDataEx(DFT_Ub,s_wADBuff[DFT_Ub],fFsam,SCALE2ULN,DFT_DOTNUM);
    GetACWaveDataEx(DFT_Uc,s_wADBuff[DFT_Uc],fFsam,SCALE2ULN,DFT_DOTNUM);

//     DWORD dwFsaminv = 10000000/fFsam/DFT_DOTNUM+0.5;        // 0.1us
    DWORD dwFsaminv = 7200000/fFsam/DFT_DOTNUM+0.5;        // 0.1us
    for(i=0;i<DFT_DOTNUM;i++)
    {
        for(short j=0;j<DFT_CHANNEL_HARD;j++)
        {
            g_analogWave.wData[j][i] = s_wADBuff[j][i];
            g_analogWave.wData[j][i+24] = s_wADBuff[j][i];
        }
        MyApp_OnTimerSample(i);
        g_dwSysTimerUs -= dwFsaminv;
    }
    for(i=0;i<SWITCH_COUNT;i++)
    {
        WORD wData = GetINStatus(i)?STATUS_ON:STATUS_OFF;
        SWITCHSetStatus(i,wData);
    }

//     if(GetINStatus(0))
//     {
//         Measure_StartReg();
//         SetINStatus(0,0);
//     }

    ::OnMainTimer10ms();
    
    if(m_pLCD)
    {
        m_pLCD->SetLCDOpened(g_bLCDOpened);
        if(g_bLCDRefresh) m_pLCD->SetLCDRefresh();
        g_bLCDRefresh = FALSE;
    }
//     COLORREF clrDark = RGB(192,192,192);
//     COLORREF clrRed = RGB(255,64,64);
//     COLORREF clrGreen = RGB(64,255,64);
//     COLORREF clrYellow = RGB(255,255,64);
//     
//     if(m_pLightRun) m_pLightRun->SetStatus(Output_IsOutputValid(&g_lightRun)?clrGreen:clrDark);
//     if(m_pLightAlarmed) m_pLightAlarmed->SetStatus(Output_IsOutputValid(&g_lightAlarmed)?clrYellow:clrDark);
//     if(m_pLightTripped) m_pLightTripped->SetStatus(Output_IsOutputValid(&g_lightTripped)?clrRed:clrDark);
//     if(m_pLightOpened) m_pLightOpened->SetStatus(Output_IsOutputValid(&g_lightOpened)?clrGreen:clrDark);
//     if(m_pLightClosed) m_pLightClosed->SetStatus(Output_IsOutputValid(&g_lightClosed)?clrRed:clrDark);
    
    for(i=0;i<RELAYKH_COUNT;i++) SetOutStatus(i,Output_IsOutputValid(&g_relayKH[i]));

//     m_bAlarmed = (g_deviceInfo.wDeviceStatus1&DS1_Alarmed)?TRUE:FALSE;
// 	m_bTripped = (g_deviceInfo.wDeviceStatus1&DS1_Tripped)?TRUE:FALSE;

}

void CMyIEDNPS7510::OnMainTimer250ms()
{
	CMyIED::OnMainTimer250ms();
	::OnMainTimer250ms();
}

void CMyIEDNPS7510::OnMainTimer1000ms()
{
	CMyIED::OnMainTimer1000ms();
	::OnMainTimer1000ms();
}

void CMyIEDNPS7510::OnMainWhileLoop()
{
	CMyIED::OnMainWhileLoop();
	::OnMainWhileLoop();
}

void CMyIEDNPS7510::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
// 	示例代码
// 	以下分别为电脑键盘的上,下,左,右,ESC,Enter键弹起
    switch(nChar)
    {
    case VK_UP: if(m_pKeyUp) m_pKeyUp->m_bButtonDown = FALSE; break;
    case VK_DOWN: if(m_pKeyDown) m_pKeyDown->m_bButtonDown = FALSE; break;
//     case VK_LEFT: if(m_pKeyLeft) m_pKeyLeft->m_bButtonDown = FALSE; break;
//     case VK_RIGHT: if(m_pKeyRight) m_pKeyRight->m_bButtonDown = FALSE; break;
    case VK_ESCAPE: if(m_pKeyCancel) m_pKeyCancel->m_bButtonDown = FALSE; break;
    case VK_RETURN: if(m_pKeyOK) m_pKeyOK->m_bButtonDown = FALSE; break;
    }
}

void CMyIEDNPS7510::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
// 	示例代码
// 	以下分别为电脑键盘的上,下,左,右,ESC,Enter键按下
    switch(nChar)
    {
    case VK_UP: if(m_pKeyUp) m_pKeyUp->m_bButtonDown = TRUE; break;
    case VK_DOWN: if(m_pKeyDown) m_pKeyDown->m_bButtonDown = TRUE; break;
//     case VK_LEFT: if(m_pKeyLeft) m_pKeyLeft->m_bButtonDown = TRUE; break;
//     case VK_RIGHT: if(m_pKeyRight) m_pKeyRight->m_bButtonDown = TRUE; break;
    case VK_ESCAPE: if(m_pKeyCancel) m_pKeyCancel->m_bButtonDown = TRUE; break;
    case VK_RETURN: if(m_pKeyOK) m_pKeyOK->m_bButtonDown = TRUE; break;
    }
}

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/
