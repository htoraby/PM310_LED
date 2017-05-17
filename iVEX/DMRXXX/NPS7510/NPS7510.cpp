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

// --------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

extern BYTE g_LEDBuff[32];
extern const BYTE c_LEDCode[38];

extern void LED_ASCIIOut1(WORD wPosX, WORD wPosY, char* pszText);
extern BYTE GetLEDCode(char ch);

#ifdef __cplusplus
}
#endif /* extern "C" */

short GetLED(BYTE Code)
{
    short nLEDS = sizeof(c_LEDCode);
    for(short i=0;i<nLEDS;i++)
    {
        if((Code&0x7f)==c_LEDCode[i])
        {
            return i;
        }
    }
    return -1;
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

//     m_pLCD = GetObjLCD("LCD");
// 
//     m_pKeyUp = GetObjKey("KeyUp");
//     m_pKeyDown = GetObjKey("KeyDown");
//     m_pKeyOK = GetObjKey("KeyOK");
//     m_pKeyCancel = GetObjKey("KeyCancel");
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

    m_pLEDSLogo = GetObjLEDS("LEDSLOGO");
    m_pLEDSNeg1 = GetObjLEDS("LEDSNeg1");
    m_pLEDSNeg2 = GetObjLEDS("LEDSNeg2");
    m_pLEDSNeg3 = GetObjLEDS("LEDSNeg3");
    m_pLEDSNegS = GetObjLEDS("LEDSNegS");
    m_pLEDSA1 = GetObjLEDS("LEDSA1");
    m_pLEDSB1 = GetObjLEDS("LEDSB1");
    m_pLEDSC1 = GetObjLEDS("LEDSC1");
    m_pLEDSA2 = GetObjLEDS("LEDSA2");
    m_pLEDSB2 = GetObjLEDS("LEDSB2");
    m_pLEDSC2 = GetObjLEDS("LEDSC2");
    m_pLEDSDash1 = GetObjLEDS("LEDSDash1");
    m_pLEDSDash2 = GetObjLEDS("LEDSDash2");
    m_pLEDSDash3 = GetObjLEDS("LEDSDash3");

    m_pLEDSN1 = GetObjLEDS("LEDSN1");
    m_pLEDSN2 = GetObjLEDS("LEDSN2");
    m_pLEDSN3 = GetObjLEDS("LEDSN3");
    m_pLEDSSigma1 = GetObjLEDS("LEDSSigma1");
    m_pLEDSSigma2 = GetObjLEDS("LEDSSigma2");
    m_pLEDSSigma3 = GetObjLEDS("LEDSSigma3");

    m_pLEDSMAX = GetObjLEDS("LEDSMAX");
    m_pLEDSMIN = GetObjLEDS("LEDSMIN");
    m_pLEDSDemand = GetObjLEDS("LEDSDemand");

    m_pLEDSBPH = GetObjLEDS("LEDSBPH");
    m_pLEDSL = GetObjLEDS("LEDSL");
    m_pLEDSC = GetObjLEDS("LEDSC");
    m_pLEDSAvg = GetObjLEDS("LEDSAvg");
    m_pLEDSSum = GetObjLEDS("LEDSSum");
    m_pLEDSImp = GetObjLEDS("LEDSImp");
    m_pLEDSExp = GetObjLEDS("LEDSExp");
    m_pLEDSNet = GetObjLEDS("LEDSNet");
    m_pLEDSTotal = GetObjLEDS("LEDSTotal");
    m_pLEDSNum1 = GetObjLEDS("LEDSNum1");
    m_pLEDSNum2 = GetObjLEDS("LEDSNum2");
    m_pLEDSNum3 = GetObjLEDS("LEDSNum3");
    m_pLEDSNum4 = GetObjLEDS("LEDSNum4");
    m_pLEDSTime = GetObjLEDS("LEDSTime");

    m_pLEDS2 = GetObjLEDS("LEDS2");

    m_pLEDS4 = GetObjLEDS("LEDS4");
    m_pLEDS5 = GetObjLEDS("LEDS5");
    m_pLEDS5Dot = GetObjLEDS("LEDS5Dot");
    m_pLEDS6 = GetObjLEDS("LEDS6");
    m_pLEDS6Dot = GetObjLEDS("LEDS6Dot");
    m_pLEDS7 = GetObjLEDS("LEDS7");
    m_pLEDS7Dot = GetObjLEDS("LEDS7Dot");

    m_pLEDS8 = GetObjLEDS("LEDS8");
    m_pLEDS9 = GetObjLEDS("LEDS9");
    m_pLEDS9Dot = GetObjLEDS("LEDS9Dot");
    m_pLEDS10 = GetObjLEDS("LEDS10");
    m_pLEDS10Dot = GetObjLEDS("LEDS10Dot");
    m_pLEDS11 = GetObjLEDS("LEDS11");
    m_pLEDS11Dot = GetObjLEDS("LEDS11Dot");

    m_pLEDS12 = GetObjLEDS("LEDS12");
    m_pLEDS13 = GetObjLEDS("LEDS13");
    m_pLEDS13Dot = GetObjLEDS("LEDS13Dot");
    m_pLEDS14 = GetObjLEDS("LEDS14");
    m_pLEDS14Dot = GetObjLEDS("LEDS14Dot");
    m_pLEDS15 = GetObjLEDS("LEDS15");
    m_pLEDS15Dot = GetObjLEDS("LEDS15Dot");

    m_pLEDS21 = GetObjLEDS("LEDS21");
    m_pLEDS22 = GetObjLEDS("LEDS22");
    m_pLEDS22Dot = GetObjLEDS("LEDS22Dot");
    m_pLEDS23 = GetObjLEDS("LEDS23");
    m_pLEDS23Dot = GetObjLEDS("LEDS23Dot");
    m_pLEDS24 = GetObjLEDS("LEDS24");
    m_pLEDS24Dot = GetObjLEDS("LEDS24Dot");
    m_pLEDS25 = GetObjLEDS("LEDS25");
    m_pLEDS25Dot = GetObjLEDS("LEDS25Dot");
    m_pLEDS26 = GetObjLEDS("LEDS26");
    m_pLEDS26Dot = GetObjLEDS("LEDS26Dot");
    m_pLEDS27 = GetObjLEDS("LEDS27");
    m_pLEDS27Dot = GetObjLEDS("LEDS27Dot");
    m_pLEDS28 = GetObjLEDS("LEDS28");
    m_pLEDS28Dot = GetObjLEDS("LEDS28Dot");
    m_pLEDS29 = GetObjLEDS("LEDS29");
    m_pLEDS29Dot = GetObjLEDS("LEDS29Dot");

    m_pLEDSCO1 = GetObjLEDS("LEDSCO1");
    m_pLEDSCO2 = GetObjLEDS("LEDSCO2");
    m_pLEDSCO3 = GetObjLEDS("LEDSCO3");
    m_pLEDSCO4 = GetObjLEDS("LEDSCO4");

    m_pLEDSDI = GetObjLEDS("LEDSDI");
    m_pLEDSDIOFDI1 = GetObjLEDS("LEDSDIOFDI1");
    m_pLEDSDIOHDI1 = GetObjLEDS("LEDSDIOHDI1");
    m_pLEDSDIOFDI2 = GetObjLEDS("LEDSDIOFDI2");
    m_pLEDSDIOHDI2 = GetObjLEDS("LEDSDIOHDI2");
    m_pLEDSDIOFDI3 = GetObjLEDS("LEDSDIOFDI3");
    m_pLEDSDIOHDI3 = GetObjLEDS("LEDSDIOHDI3");
    m_pLEDSDIOFDI4 = GetObjLEDS("LEDSDIOFDI4");
    m_pLEDSDIOHDI4 = GetObjLEDS("LEDSDIOHDI4");

    m_pLEDSDO = GetObjLEDS("LEDSDO");
    m_pLEDSDIOFDO1 = GetObjLEDS("LEDSDIOFDO1");
    m_pLEDSDIOHDO1 = GetObjLEDS("LEDSDIOHDO1");
    m_pLEDSDIOFDO2 = GetObjLEDS("LEDSDIOFDO2");
    m_pLEDSDIOHDO2 = GetObjLEDS("LEDSDIOHDO2");

    m_pLEDSCOM = GetObjLEDS("LEDSCOM");
    m_pLEDSPC = GetObjLEDS("LEDSPC");
    m_pLEDSTX = GetObjLEDS("LEDSTX");
    m_pLEDSRX = GetObjLEDS("LEDSRX");

    m_pLEDSV = GetObjLEDS("LEDSV");
    m_pLEDSKV = GetObjLEDS("LEDSKV");
    m_pLEDSKW = GetObjLEDS("LEDSKW");
    m_pLEDSMW = GetObjLEDS("LEDSMW");
    m_pLEDSArrow1 = GetObjLEDS("LEDSArrow1");
    m_pLEDSBar10 = GetObjLEDS("LEDSBar10");
    m_pLEDSBar11 = GetObjLEDS("LEDSBar11");
    m_pLEDSBar12 = GetObjLEDS("LEDSBar12");
    m_pLEDSBar13 = GetObjLEDS("LEDSBar13");
    m_pLEDSBar14 = GetObjLEDS("LEDSBar14");
    m_pLEDSBar15 = GetObjLEDS("LEDSBar15");
    m_pLEDSBar16 = GetObjLEDS("LEDSBar16");
    m_pLEDSAlarm1 = GetObjLEDS("LEDSAlarm1");

    m_pLEDSA = GetObjLEDS("LEDSA");
    m_pLEDSKA = GetObjLEDS("LEDSKA");
    m_pLEDSPF = GetObjLEDS("LEDSPF");
    m_pLEDSKVar = GetObjLEDS("LEDSKVar");
    m_pLEDSMVar = GetObjLEDS("LEDSMVar");
    m_pLEDSArrow2 = GetObjLEDS("LEDSArrow2");
    m_pLEDSBar20 = GetObjLEDS("LEDSBar20");
    m_pLEDSBar21 = GetObjLEDS("LEDSBar21");
    m_pLEDSBar22 = GetObjLEDS("LEDSBar22");
    m_pLEDSBar23 = GetObjLEDS("LEDSBar23");
    m_pLEDSBar24 = GetObjLEDS("LEDSBar24");
    m_pLEDSBar25 = GetObjLEDS("LEDSBar25");
    m_pLEDSBar26 = GetObjLEDS("LEDSBar26");
    m_pLEDSAlarm2 = GetObjLEDS("LEDSAlarm2");

    m_pLEDSTHD = GetObjLEDS("LEDSTHD");
    m_pLEDSPER = GetObjLEDS("LEDSPER");
    m_pLEDSHz = GetObjLEDS("LEDSHZ");
    m_pLEDSKVA = GetObjLEDS("LEDSKVA");
    m_pLEDSMVA = GetObjLEDS("LEDSMVA");
    m_pLEDSArrow3 = GetObjLEDS("LEDSArrow3");
    m_pLEDSBar30 = GetObjLEDS("LEDSBar30");
    m_pLEDSBar31 = GetObjLEDS("LEDSBar31");
    m_pLEDSBar32 = GetObjLEDS("LEDSBar32");
    m_pLEDSBar33 = GetObjLEDS("LEDSBar33");
    m_pLEDSBar34 = GetObjLEDS("LEDSBar34");
    m_pLEDSBar35 = GetObjLEDS("LEDSBar35");
    m_pLEDSBar36 = GetObjLEDS("LEDSBar36");
    m_pLEDSAlarm3 = GetObjLEDS("LEDSAlarm3");

    m_pLEDSDegree = GetObjLEDS("LEDSDegree");
    m_pLEDSKWh = GetObjLEDS("LEDSKWh");
    m_pLEDSKVarh = GetObjLEDS("LEDSKVarh");

}

void CMyIEDNPS7510::OnMainInit()
{
	short i;
	strcpy(g_szFlashDeviceType,(const char*)m_strType);
    strcpy(g_szEEPROMDeviceType,(const char*)m_strType);
// 	if(m_pLCD)
// 	{
// // 		WORD wLCDCX = (WORD)(m_pLCD->m_rect.right - m_pLCD->m_rect.left);
// // 		WORD wLCDCY = (WORD)(m_pLCD->m_rect.bottom - m_pLCD->m_rect.top);
// 		m_pLCD->SetLCDMetrics(160,160,(BYTE*)LCD_GetLCDBuffer(),FALSE);
// 	}

    ::OnMainInit();

    AddACChannel("Ia","(A)",5.0f,-30,1.5f);
    AddACChannel("Ib","(A)",5.0f,-150,1.5f);
    AddACChannel("Ic","(A)",5.0f,-270,1.5f);
    AddACChannel("Ua","(V)",220.0f,0,1.5f);
    AddACChannel("Ub","(V)",220.0f,-120,1.5f);
    AddACChannel("Uc","(V)",220.0f,-240,1.5f);

    for(i=0;i<SWITCH_COUNT;i++)
    {
        CString strName;
        strName.Format("DI%d", i+1);
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
	
// 	WORD wKeyHardStatus = 0;
// 	if(m_pKeyUp&&m_pKeyUp->m_bButtonDown) wKeyHardStatus |= KEY_UP;
// 	if(m_pKeyDown&&m_pKeyDown->m_bButtonDown) wKeyHardStatus |= KEY_DOWN;
// // 	if(m_pKeyLeft&&m_pKeyLeft->m_bButtonDown) wKeyHardStatus |= KEY_LEFT;
// // 	if(m_pKeyRight&&m_pKeyRight->m_bButtonDown) wKeyHardStatus |= KEY_RIGHT;
// 	if(m_pKeyOK&&m_pKeyOK->m_bButtonDown) wKeyHardStatus |= KEY_OK;
// 	if(m_pKeyCancel&&m_pKeyCancel->m_bButtonDown) wKeyHardStatus |= KEY_CANCEL;
// // 	if(m_pKeyReset&&m_pKeyReset->m_bButtonDown) wKeyHardStatus |= KEY_RESET;
// //     if(m_pKeyAdd&&m_pKeyAdd->m_bButtonDown) wKeyHardStatus |= KEY_ADD;
// //     if(m_pKeySub&&m_pKeySub->m_bButtonDown) wKeyHardStatus |= KEY_SUB;
// //	if(m_pKeyLED&&m_pKeyLED->m_bButtonDown) wKeyHardStatus |= KEY_LED;
// 	Key_SetKeyHardCode(wKeyHardStatus);
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

    BOOL bPos = (GetCBStatus()==0x3333) ? FALSE : TRUE;
    GetACWaveDataEx(DFT_Ia, s_wADBuff[DFT_Ia], fFsam, SCALE2IM, DFT_DOTNUM, bPos);
    GetACWaveDataEx(DFT_Ib, s_wADBuff[DFT_Ib], fFsam, SCALE2IM, DFT_DOTNUM, bPos);
    GetACWaveDataEx(DFT_Ic, s_wADBuff[DFT_Ic], fFsam, SCALE2IM, DFT_DOTNUM, bPos);

    GetACWaveDataEx(DFT_Ua, s_wADBuff[DFT_Ua], fFsam, SCALE2ULN, DFT_DOTNUM);
    GetACWaveDataEx(DFT_Ub, s_wADBuff[DFT_Ub], fFsam, SCALE2ULN, DFT_DOTNUM);
    GetACWaveDataEx(DFT_Uc, s_wADBuff[DFT_Uc], fFsam, SCALE2ULN, DFT_DOTNUM);

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
//     for(i=0;i<SWITCH_COUNT;i++)
//     {
//         WORD wData = GetINStatus(i)?STATUS_ON:STATUS_OFF;
//         SWITCHSetStatus(i,wData);
//     }

//     if(GetINStatus(0))
//     {
//         Measure_StartReg();
//         SetINStatus(0,0);
//     }

    ::OnMainTimer10ms();
    
//     if(m_pLCD)
//     {
//         m_pLCD->SetLCDOpened(g_bLCDOpened);
//         if(g_bLCDRefresh) m_pLCD->SetLCDRefresh();
//         g_bLCDRefresh = FALSE;
//     }
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
    
//     for(i=0;i<RELAYKH_COUNT;i++) SetOutStatus(i,Output_IsOutputValid(&g_relayKH[i]));

//     m_bAlarmed = (g_deviceInfo.wDeviceStatus1&DS1_Alarmed)?TRUE:FALSE;
// 	m_bTripped = (g_deviceInfo.wDeviceStatus1&DS1_Tripped)?TRUE:FALSE;

}

void CMyIEDNPS7510::OnMainTimer250ms()
{
	CMyIED::OnMainTimer250ms();
	::OnMainTimer250ms();
}

short i=0;
void CMyIEDNPS7510::OnMainTimer1000ms()
{
    CMyIED::OnMainTimer1000ms();
    ::OnMainTimer1000ms();
    i++;

//     LED_SetLight(LED_Logo, (i%2)==0);
//     LED_SetLight(LED_Colon, (i%2)==0);

//     LED_RealOut(0, 2, -1234, 0x41);
//     LED_RealOut(0, 3, -123456789, 0x98);

//     LED_ASCIIOut(1, 0 , "yes");
//     LED_ASCIIOut(1, 3 , "G");
// 
//     LED_SetCode(LED_02, '3');
//     LED_SetLight(LED_Demand, (i%2)==0);

//     LED_ASCIIOut1(1, 0, "  8.0");
//     LED_SetLight(LED_Num1, (i%2)==0);
}

void CMyIEDNPS7510::OnMainWhileLoop()
{
	CMyIED::OnMainWhileLoop();
	::OnMainWhileLoop();
    if(g_bRefresh) RefreshLED();
}

void CMyIEDNPS7510::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
// 	示例代码
// 	以下分别为电脑键盘的上,下,左,右,ESC,Enter键弹起
//     switch(nChar)
//     {
//     case VK_UP: if(m_pKeyUp) m_pKeyUp->m_bButtonDown = FALSE; break;
//     case VK_DOWN: if(m_pKeyDown) m_pKeyDown->m_bButtonDown = FALSE; break;
// //     case VK_LEFT: if(m_pKeyLeft) m_pKeyLeft->m_bButtonDown = FALSE; break;
// //     case VK_RIGHT: if(m_pKeyRight) m_pKeyRight->m_bButtonDown = FALSE; break;
//     case VK_ESCAPE: if(m_pKeyCancel) m_pKeyCancel->m_bButtonDown = FALSE; break;
//     case VK_RETURN: if(m_pKeyOK) m_pKeyOK->m_bButtonDown = FALSE; break;
//     }
}

void CMyIEDNPS7510::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
// 	示例代码
// 	以下分别为电脑键盘的上,下,左,右,ESC,Enter键按下
//     switch(nChar)
//     {
//     case VK_UP: if(m_pKeyUp) m_pKeyUp->m_bButtonDown = TRUE; break;
//     case VK_DOWN: if(m_pKeyDown) m_pKeyDown->m_bButtonDown = TRUE; break;
// //     case VK_LEFT: if(m_pKeyLeft) m_pKeyLeft->m_bButtonDown = TRUE; break;
// //     case VK_RIGHT: if(m_pKeyRight) m_pKeyRight->m_bButtonDown = TRUE; break;
//     case VK_ESCAPE: if(m_pKeyCancel) m_pKeyCancel->m_bButtonDown = TRUE; break;
//     case VK_RETURN: if(m_pKeyOK) m_pKeyOK->m_bButtonDown = TRUE; break;
//     }
}

void CMyIEDNPS7510::RefreshLED(void)
{
    m_pLEDSLogo->SetStatus(LED_GetLight(LED_Logo));

    m_pLEDSA1->SetStatus(LED_GetLight(LED_ABC));
    m_pLEDSB1->SetStatus(LED_GetLight(LED_ABC));
    m_pLEDSC1->SetStatus(LED_GetLight(LED_ABC));

    m_pLEDSA2->SetStatus(LED_GetLight(LED_BCA));
    m_pLEDSB2->SetStatus(LED_GetLight(LED_BCA));
    m_pLEDSC2->SetStatus(LED_GetLight(LED_BCA));
    m_pLEDSDash1->SetStatus(LED_GetLight(LED_BCA));
    m_pLEDSDash2->SetStatus(LED_GetLight(LED_BCA));
    m_pLEDSDash3->SetStatus(LED_GetLight(LED_BCA));

    m_pLEDSN1->SetStatus(LED_GetLight(LED_N));
    m_pLEDSN2->SetStatus(LED_GetLight(LED_N));
    m_pLEDSN3->SetStatus(LED_GetLight(LED_N));

    m_pLEDSSigma1->SetStatus(LED_GetLight(LED_Sigma));
    m_pLEDSSigma2->SetStatus(LED_GetLight(LED_Sigma));
    m_pLEDSSigma3->SetStatus(LED_GetLight(LED_Sigma));

    m_pLEDSMAX->SetStatus(LED_GetLight(LED_MAX));
    m_pLEDSMIN->SetStatus(LED_GetLight(LED_MIN));
    m_pLEDSDemand->SetStatus(LED_GetLight(LED_Demand));

    m_pLEDSBPH->SetStatus(LED_GetLight(LED_BPH));
    m_pLEDSL->SetStatus(LED_GetLight(LED_L));
    m_pLEDSC->SetStatus(LED_GetLight(LED_C));
    m_pLEDSAvg->SetStatus(LED_GetLight(LED_Avg));
    m_pLEDSSum->SetStatus(LED_GetLight(LED_Sum));
    m_pLEDSImp->SetStatus(LED_GetLight(LED_Imp));
    m_pLEDSExp->SetStatus(LED_GetLight(LED_Exp));
    m_pLEDSNet->SetStatus(LED_GetLight(LED_Net));
    m_pLEDSTotal->SetStatus(LED_GetLight(LED_Total));
    m_pLEDSNum1->SetStatus(LED_GetLight(LED_Num1));
    m_pLEDSNum2->SetStatus(LED_GetLight(LED_Num2));
    m_pLEDSNum3->SetStatus(LED_GetLight(LED_Num3));
    m_pLEDSNum4->SetStatus(LED_GetLight(LED_Num4));
    m_pLEDSTime->SetStatus(LED_GetLight(LED_Time));

    BYTE Code = g_LEDBuff[LED_02];
    m_pLEDS2->SetStatus(GetLED(Code));
//     m_pLEDSDemand->SetStatus((Code&0x80)?1:0);

    Code = g_LEDBuff[LED_04];
    m_pLEDS4->SetStatus(GetLED(Code));
    m_pLEDSNeg1->SetStatus((Code&0x80)?1:0);

    Code = g_LEDBuff[LED_05];
    m_pLEDS5->SetStatus(GetLED(Code));
    m_pLEDS5Dot->SetStatus((Code&0x80)?1:0, m_pLEDS5->IsRefreshed());

    Code = g_LEDBuff[LED_06];
    m_pLEDS6->SetStatus(GetLED(Code));
    m_pLEDS6Dot->SetStatus((Code&0x80)?1:0, m_pLEDS6->IsRefreshed());

    Code = g_LEDBuff[LED_07];
    m_pLEDS7->SetStatus(GetLED(Code));
    m_pLEDS7Dot->SetStatus((Code&0x80)?1:0, m_pLEDS7->IsRefreshed());

    Code = g_LEDBuff[LED_08];
    m_pLEDS8->SetStatus(GetLED(Code));
    m_pLEDSNeg2->SetStatus((Code&0x80)?1:0);

    Code = g_LEDBuff[LED_09];
    m_pLEDS9->SetStatus(GetLED(Code));
    m_pLEDS9Dot->SetStatus((Code&0x80)?1:0, m_pLEDS9->IsRefreshed());

    Code = g_LEDBuff[LED_10];
    m_pLEDS10->SetStatus(GetLED(Code));
    m_pLEDS10Dot->SetStatus((Code&0x80)?1:0, m_pLEDS10->IsRefreshed());

    Code = g_LEDBuff[LED_11];
    m_pLEDS11->SetStatus(GetLED(Code));
    m_pLEDS11Dot->SetStatus((Code&0x80)?1:0, m_pLEDS11->IsRefreshed());

    Code = g_LEDBuff[LED_12];
    m_pLEDS12->SetStatus(GetLED(Code));
    m_pLEDSNeg3->SetStatus((Code&0x80)?1:0);

    Code = g_LEDBuff[LED_13];
    m_pLEDS13->SetStatus(GetLED(Code));
    m_pLEDS13Dot->SetStatus((Code&0x80)?1:0, m_pLEDS13->IsRefreshed());

    Code = g_LEDBuff[LED_14];
    m_pLEDS14->SetStatus(GetLED(Code));
    m_pLEDS14Dot->SetStatus((Code&0x80)?1:0, m_pLEDS14->IsRefreshed());

    Code = g_LEDBuff[LED_15];
    m_pLEDS15->SetStatus(GetLED(Code));
    m_pLEDS15Dot->SetStatus((Code&0x80)?1:0, m_pLEDS15->IsRefreshed());

    Code = g_LEDBuff[LED_21];
    m_pLEDS21->SetStatus(GetLED(Code));
    m_pLEDSNegS->SetStatus((Code&0x80)?1:0);

    Code = g_LEDBuff[LED_22];
    m_pLEDS22->SetStatus(GetLED(Code));
    m_pLEDS22Dot->SetStatus((Code&0x80)?1:0, m_pLEDS22->IsRefreshed());

    Code = g_LEDBuff[LED_23];
    m_pLEDS23->SetStatus(GetLED(Code));
    m_pLEDS23Dot->SetStatus((Code&0x80)?1:0, m_pLEDS23->IsRefreshed());

    Code = g_LEDBuff[LED_24];
    m_pLEDS24->SetStatus(GetLED(Code));
    m_pLEDS24Dot->SetStatus((Code&0x80)?1:0, m_pLEDS24->IsRefreshed());

    Code = g_LEDBuff[LED_25];
    m_pLEDS25->SetStatus(GetLED(Code));
    m_pLEDS25Dot->SetStatus((Code&0x80)?1:0, m_pLEDS25->IsRefreshed());

    Code = g_LEDBuff[LED_26];
    m_pLEDS26->SetStatus(GetLED(Code));
    m_pLEDS26Dot->SetStatus((Code&0x80)?1:0, m_pLEDS26->IsRefreshed());

    Code = g_LEDBuff[LED_27];
    m_pLEDS27->SetStatus(GetLED(Code));
    m_pLEDS27Dot->SetStatus((Code&0x80)?1:0), m_pLEDS27->IsRefreshed();

    Code = g_LEDBuff[LED_28];
    m_pLEDS28->SetStatus(GetLED(Code));
    m_pLEDS28Dot->SetStatus((Code&0x80)?1:0, m_pLEDS28->IsRefreshed());

    Code = g_LEDBuff[LED_29];
    m_pLEDS29->SetStatus(GetLED(Code));
    m_pLEDS29Dot->SetStatus((Code&0x80)?1:0, m_pLEDS29->IsRefreshed());

    m_pLEDSCO1->SetStatus(LED_GetLight(LED_Colon), m_pLEDS25->IsRefreshed());
    m_pLEDSCO2->SetStatus(LED_GetLight(LED_Colon), m_pLEDS25->IsRefreshed());
    m_pLEDSCO3->SetStatus(LED_GetLight(LED_Colon), m_pLEDS22->IsRefreshed());
    m_pLEDSCO4->SetStatus(LED_GetLight(LED_Colon), m_pLEDS22->IsRefreshed());

    m_pLEDSDI->SetStatus(LED_GetLight(LED_DI));
    m_pLEDSDIOFDI1->SetStatus(LED_GetLight(LED_DI1F));
    m_pLEDSDIOHDI1->SetStatus(LED_GetLight(LED_DI1H));
    m_pLEDSDIOFDI2->SetStatus(LED_GetLight(LED_DI2F));
    m_pLEDSDIOHDI2->SetStatus(LED_GetLight(LED_DI2H));
    m_pLEDSDIOFDI3->SetStatus(LED_GetLight(LED_DI3F));
    m_pLEDSDIOHDI3->SetStatus(LED_GetLight(LED_DI3H));
    m_pLEDSDIOFDI4->SetStatus(LED_GetLight(LED_DI4F));
    m_pLEDSDIOHDI4->SetStatus(LED_GetLight(LED_DI4H));

    m_pLEDSDO->SetStatus(LED_GetLight(LED_DO));
    m_pLEDSDIOFDO1->SetStatus(LED_GetLight(LED_DO1F));
    m_pLEDSDIOHDO1->SetStatus(LED_GetLight(LED_DO1H));
    m_pLEDSDIOFDO2->SetStatus(LED_GetLight(LED_DO2F));
    m_pLEDSDIOHDO2->SetStatus(LED_GetLight(LED_DO2H));

    m_pLEDSCOM->SetStatus(LED_GetLight(LED_TX));
    m_pLEDSTX->SetStatus(LED_GetLight(LED_TX));

    m_pLEDSPC->SetStatus(LED_GetLight(LED_RX));
    m_pLEDSRX->SetStatus(LED_GetLight(LED_RX));

    m_pLEDSV->SetStatus(LED_GetLight(LED_V));
    m_pLEDSKV->SetStatus(LED_GetLight(LED_kV));
    m_pLEDSKW->SetStatus(LED_GetLight(LED_kW));
    m_pLEDSMW->SetStatus(LED_GetLight(LED_MW));
    m_pLEDSArrow1->SetStatus(LED_GetLight(LED_Arrow));
    m_pLEDSBar10->SetStatus(LED_GetLight(LED_Bar10));
    m_pLEDSBar11->SetStatus(LED_GetLight(LED_Bar11));
    m_pLEDSBar12->SetStatus(LED_GetLight(LED_Bar12));
    m_pLEDSBar13->SetStatus(LED_GetLight(LED_Bar13));
    m_pLEDSBar14->SetStatus(LED_GetLight(LED_Bar14));
    m_pLEDSBar15->SetStatus(LED_GetLight(LED_Bar15));
    m_pLEDSBar16->SetStatus(LED_GetLight(LED_Bar16));
    m_pLEDSAlarm1->SetStatus(LED_GetLight(LED_Alarm1));

    m_pLEDSA->SetStatus(LED_GetLight(LED_A));
    m_pLEDSKA->SetStatus(LED_GetLight(LED_kA));
    m_pLEDSPF->SetStatus(LED_GetLight(LED_PF));
    m_pLEDSKVar->SetStatus(LED_GetLight(LED_kVar));
    m_pLEDSMVar->SetStatus(LED_GetLight(LED_MVar));
    m_pLEDSArrow2->SetStatus(LED_GetLight(LED_Arrow));
    m_pLEDSBar20->SetStatus(LED_GetLight(LED_Bar20));
    m_pLEDSBar21->SetStatus(LED_GetLight(LED_Bar21));
    m_pLEDSBar22->SetStatus(LED_GetLight(LED_Bar22));
    m_pLEDSBar23->SetStatus(LED_GetLight(LED_Bar23));
    m_pLEDSBar24->SetStatus(LED_GetLight(LED_Bar24));
    m_pLEDSBar25->SetStatus(LED_GetLight(LED_Bar25));
    m_pLEDSBar26->SetStatus(LED_GetLight(LED_Bar26));
    m_pLEDSAlarm2->SetStatus(LED_GetLight(LED_Alarm2));

    m_pLEDSTHD->SetStatus(LED_GetLight(LED_THD));
    m_pLEDSPER->SetStatus(LED_GetLight(LED_PER));
    m_pLEDSHz->SetStatus(LED_GetLight(LED_Hz));
    m_pLEDSKVA->SetStatus(LED_GetLight(LED_kVA));
    m_pLEDSMVA->SetStatus(LED_GetLight(LED_MVA));
    m_pLEDSArrow3->SetStatus(LED_GetLight(LED_Arrow));
    m_pLEDSBar30->SetStatus(LED_GetLight(LED_Bar30));
    m_pLEDSBar31->SetStatus(LED_GetLight(LED_Bar31));
    m_pLEDSBar32->SetStatus(LED_GetLight(LED_Bar32));
    m_pLEDSBar33->SetStatus(LED_GetLight(LED_Bar33));
    m_pLEDSBar34->SetStatus(LED_GetLight(LED_Bar34));
    m_pLEDSBar35->SetStatus(LED_GetLight(LED_Bar35));
    m_pLEDSBar36->SetStatus(LED_GetLight(LED_Bar36));
    m_pLEDSAlarm3->SetStatus(LED_GetLight(LED_Alarm3));

    m_pLEDSDegree->SetStatus(LED_GetLight(LED_Degree));
    m_pLEDSKWh->SetStatus(LED_GetLight(LED_kWh));
    m_pLEDSKVarh->SetStatus(LED_GetLight(LED_kVarh));

//     m_pLEDS5Dot->SetHide(FALSE);
//     m_pLEDS5Dot->SetHide(TRUE);
//     m_pLEDS6Dot->SetHide(FALSE);
//     m_pLEDS6Dot->SetHide(TRUE);
//     m_pLEDS7Dot->SetHide(FALSE);
//     m_pLEDS7Dot->SetHide(TRUE);
//     m_pLEDS9Dot->SetHide(FALSE);
//     m_pLEDS9Dot->SetHide(TRUE);
// 
//     m_pLEDS10Dot->SetHide(FALSE);
//     m_pLEDS10Dot->SetHide(TRUE);
//     m_pLEDS11Dot->SetHide(FALSE);
//     m_pLEDS11Dot->SetHide(TRUE);
//     m_pLEDS13Dot->SetHide(FALSE);
//     m_pLEDS13Dot->SetHide(TRUE);
//     m_pLEDS14Dot->SetHide(FALSE);
//     m_pLEDS14Dot->SetHide(TRUE);
//     m_pLEDS15Dot->SetHide(FALSE);
//     m_pLEDS15Dot->SetHide(TRUE);

}

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/
