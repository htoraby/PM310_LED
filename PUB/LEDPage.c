#include "main.h"
/*******************************************************************/
//static char c_szProtectTOG[12][4];
//static char c_szProtectCFG[5][4];
static char s_szTemp[6];
//**************************************************************
const char c_szProtectTOG[12][4]=
{
	"oFF"," oN","S01","S02","S03","S04","S05","S06","S07","S08","S09","S10"
};

const char c_szProtectCFG[4][4]=
{
	"---","ALm","trE","trP"
};

const char c_szIDMTType[4][5] = 
{
	"Extr","vEry","Norm","LoNG"
};

const char c_szSelectKH[4][5] = 
{
	"----","Kh01","Kh02","Kh03"
};

const char c_szSwitchDCAC[2][3] = 
{
	"dc","Ac"
};
const char c_sz2P3P[2][3] = 
{
	"2P","3P"
};

const char c_szSwitchEVENTTYPE[3][5] = 
{
	"----","SWch","rNIF"
};

const char c_szRateFrequency[2][5] = 
{
	"50hz","60hz"
};

const char c_szLinkIn[][5] = 
{
	"----"
#if (SWITCH_COUNT>=1)
		," IN1"
#endif
#if (SWITCH_COUNT>=2)
		," IN2"
#endif
#if (SWITCH_COUNT>=3)
		," IN3"
#endif
#if (SWITCH_COUNT>=4)
		," IN4"
#endif
#if (SWITCH_COUNT>=5)
		," IN5"
#endif
#if (SWITCH_COUNT>=6)
		," IN6"
#endif
#if (SWITCH_COUNT>=7)
		," IN7"
#endif
#if (SWITCH_COUNT>=8)
		," IN8"
#endif
#if (SWITCH_COUNT>=9)
		," IN9"
#endif
#if (SWITCH_COUNT>=10)
		,"IN10"
#endif
#if (SWITCH_COUNT>=11)
		,"IN11"
#endif
#if (SWITCH_COUNT>=12)
		,"IN12"
#endif
#if (SWITCH_COUNT>=13)
		,"IN13"
#endif
#if (SWITCH_COUNT>=14)
		,"IN14"
#endif
#if (SWITCH_COUNT>=15)
		,"IN15"
#endif
#if (SWITCH_COUNT>=16)
		,"IN16"
#endif
#if (SWITCH_COUNT>=17)
		,"IN17"
#endif
#if (SWITCH_COUNT>=18)
		,"IN18"
#endif
#if (SWITCH_COUNT>=19)
		,"IN19"
#endif
#if (SWITCH_COUNT>=20)
		,"IN20"
#endif
#if (SWITCH_COUNT>=21)
		,"IN21"
#endif
#if (SWITCH_COUNT>=22)
		,"IN22"
#endif
#if (SWITCH_COUNT>=23)
		,"IN23"
#endif
#if (SWITCH_COUNT>=24)
		,"IN24"
#endif
#if (SWITCH_COUNT>=25)
		,"IN25"
#endif
#if (SWITCH_COUNT>=26)
		,"IN26"
#endif
#if (SWITCH_COUNT>=27)
		,"IN27"
#endif
#if (SWITCH_COUNT>=28)
		,"IN28"
#endif
#if (SWITCH_COUNT>=29)
		,"IN29"
#endif
#if (SWITCH_COUNT>=30)
		,"IN30"
#endif
#if (SWITCH_COUNT>=31)
		,"IN31"
#endif
#if (SWITCH_COUNT>=32)
		,"IN32"
#endif
};
/*
static char c_szBaudrate[7][6] =
{
	" 300"," 600","1200","2400","4800","9600","1.92K"//,"3.84K"
};
*/
/*******************************************************************/
/*
static void SetConstString1(char* pString,char ch1)
{
	*pString++ = ch1;
	*pString++ = 0;
}
*/
static void SetConstString3(char* pString,char ch1,char ch2,char ch3)
{
	*pString++ = ch1;
	*pString++ = ch2;
	*pString++ = ch3;
	*pString++ = 0;
}

static void SetConstString4(char* pString,char ch1,char ch2,char ch3,char ch4)
{
	*pString++ = ch1;
	*pString++ = ch2;
	*pString++ = ch3;
	*pString++ = ch4;
	*pString++ = 0;
}
/*
static void SetConstString5(char* pString,char ch1,char ch2,char ch3,char ch4,char ch5)
{
	*pString++ = ch1;
	*pString++ = ch2;
	*pString++ = ch3;
	*pString++ = ch4;
	*pString++ = ch5;
	*pString++ = 0;
}

static void SetConstString(void)
{
	SetConstString3(c_szProtectTOG[0],'o','F','F');
	SetConstString3(c_szProtectTOG[1],' ','o','N');
	SetConstString3(c_szProtectTOG[2],'S','0','1');
	SetConstString3(c_szProtectTOG[3],'S','0','2');
	SetConstString3(c_szProtectTOG[4],'S','0','3');
	SetConstString3(c_szProtectTOG[5],'S','0','4');
	SetConstString3(c_szProtectTOG[6],'S','0','5');
	SetConstString3(c_szProtectTOG[7],'S','0','6');
	SetConstString3(c_szProtectTOG[8],'S','0','7');
	SetConstString3(c_szProtectTOG[9],'S','0','8');
	SetConstString3(c_szProtectTOG[10],'S','0','9');
	SetConstString3(c_szProtectTOG[11],'S','1','0');

	SetConstString3(c_szProtectCFG[0],'-','-','-');
	SetConstString3(c_szProtectCFG[1],'A','L','m');
	SetConstString3(c_szProtectCFG[2],'t','r','E');
	SetConstString3(c_szProtectCFG[3],'t','r','P');
	SetConstString3(c_szProtectCFG[4],'t','A','P');
}
*/
void OnRefreshPageData1(void)
{
	DWORD dwData;
	//IA
	dwData = (DWORD)g_dataIA.m_dwDataSecondary*g_deviceParam.wScaleCT;
	if(dwData<10000) LEDRealOut(0,0,(WORD)dwData,0x42);
	else if(dwData<100000) 
	{
		dwData += 5;
		dwData /= 10;
		LEDRealOut(0,0,(WORD)dwData,0x41);
	}
	else
	{
		dwData += 50;
		dwData /= 100;
		LEDRealOut(0,0,(WORD)dwData,0x40);
	}
	//IB
	dwData = (DWORD)g_dataIB.m_dwDataSecondary*g_deviceParam.wScaleCT;
	if(dwData<10000) LEDRealOut(0,1,(WORD)dwData,0x42);
	else if(dwData<100000) 
	{
		dwData += 5;
		dwData /= 10;
		LEDRealOut(0,1,(WORD)dwData,0x41);
	}
	else
	{
		dwData += 50;
		dwData /= 100;
		LEDRealOut(0,1,(WORD)dwData,0x40);
	}
	//IC
	dwData = (DWORD)g_dataIC.m_dwDataSecondary*g_deviceParam.wScaleCT;
	if(dwData<10000) LEDRealOut(0,2,(WORD)dwData,0x42);
	else if(dwData<100000) 
	{
		dwData += 5;
		dwData /= 10;
		LEDRealOut(0,2,(WORD)dwData,0x41);
	}
	else
	{
		dwData += 50;
		dwData /= 100;
		LEDRealOut(0,2,(WORD)dwData,0x40);
	}
	//3I0
	dwData = (DWORD)g_data3I0.m_dwDataSecondary*g_deviceParam.wScaleCT;
	if(dwData<10000) LEDRealOut(0,3,(WORD)dwData,0x43);
	else if(dwData<100000) 
	{
		dwData += 5;
		dwData /= 10;
		LEDRealOut(0,3,(WORD)dwData,0x42);
	}
	else if(dwData<1000000) 
	{
		dwData += 50;
		dwData /= 100;
		LEDRealOut(0,3,(WORD)dwData,0x41);
	}
	else
	{
		dwData += 500;
		dwData /= 1000;
		LEDRealOut(0,3,(WORD)dwData,0x40);
	}
}

void OnRefreshPageData2(void)	//开关量显示
{
	LEDClear();
	SetConstString4(s_szTemp,'-','I','N','-');
	LEDAsciiOut(0,0,s_szTemp);
	
	if(g_deviceInfo.wSwitchStatus1&SS_IN01) LEDByteOut(0,1,1,1);
	else LEDByteOut(0,1,0,1);
	if(g_deviceInfo.wSwitchStatus1&SS_IN02) LEDByteOut(1,1,1,1);
	else LEDByteOut(1,1,0,1);
	if(g_deviceInfo.wSwitchStatus1&SS_IN03) LEDByteOut(2,1,1,1);
	else LEDByteOut(2,1,0,1);
	if(g_deviceInfo.wSwitchStatus1&SS_IN04) LEDByteOut(3,1,1,1);
	else LEDByteOut(3,1,0,1);
	if(g_deviceInfo.wSwitchStatus1&SS_IN05) LEDByteOut(0,2,1,1);
	else LEDByteOut(0,2,0,1);
	if(g_deviceInfo.wSwitchStatus1&SS_IN06) LEDByteOut(1,2,1,1);
	else LEDByteOut(1,2,0,1);
	if(g_deviceInfo.wSwitchStatus1&SS_IN07) LEDByteOut(2,2,1,1);
	else LEDByteOut(2,2,0,1);
	if(g_deviceInfo.wSwitchStatus1&SS_IN08) LEDByteOut(3,2,1,1);
	else LEDByteOut(3,2,0,1);
	if(g_deviceInfo.wSwitchStatus1&SS_IN09) LEDByteOut(0,3,1,1);
	else LEDByteOut(0,3,0,1);
	if(g_deviceInfo.wSwitchStatus1&SS_IN10) LEDByteOut(1,3,1,1);
	else LEDByteOut(1,3,0,1);
}

void OnRefreshPageData3(void)
{
	unsigned short wMouthDay;
	unsigned short wHourMinute;
	unsigned short wEventOldest;
	EVENT* pEvent;
	LEDClear();
	if(g_deviceInfo.wCountEventTable==0)
	{
		SetConstString4(s_szTemp,'N','U','L','L');
		LEDAsciiOut(0,1,s_szTemp);
		return;
	}
	if(g_deviceInfo.wCountEventTable>=EVENT_COUNT)
	{
		wEventOldest = g_deviceInfo.wCountEventTable - EVENT_COUNT;
		SetPageCount(EVENT_COUNT);
	}
	else
	{
		wEventOldest = 0;
		SetPageCount(g_deviceInfo.wCountEventTable);
	}
	wEventOldest += g_wCycleCurSel;
	if(wEventOldest>=g_deviceInfo.wCountEventTable) return;
	pEvent = Event_GetEvent(wEventOldest);
	if(pEvent->wType!=EVENTTYPE_NULL)
	{
//		LEDByteOut(0,0,pEvent->wCode,1);
		LEDRealOut(0,0,(WORD)(g_wCycleCurSel+1)*1000,0x43);
		if(pEvent->wType==EVENTTYPE_SWITCH)
		{
			SetConstString3(s_szTemp,'S','W','h');
			LEDAsciiOut(1,0,s_szTemp);
		}
		else if(pEvent->wType==EVENTTYPE_RUNINFO)
		{
			SetConstString3(s_szTemp,'r','N','F');
			LEDAsciiOut(1,0,s_szTemp);
		}
		else if(pEvent->wType==EVENTTYPE_ALARMED)
		{
			SetConstString3(s_szTemp,'A','L','m');
			LEDAsciiOut(1,0,s_szTemp);
		}
		else if(pEvent->wType==EVENTTYPE_TRIPPED)
		{
			SetConstString3(s_szTemp,'t','r','P');
			LEDAsciiOut(1,0,s_szTemp);
		}
//		LEDByteOut(1,1,pEvent->wCode,2);
		LEDRealOut(0,1,pEvent->wCode,0x40);
		wMouthDay = (pEvent->time.wMonth) *100;
		wMouthDay += pEvent->time.wDay;
		LEDRealOut(0,2,wMouthDay,0x42);
		wHourMinute = (pEvent->time.wHour)*100;
		wHourMinute += pEvent->time.wMinute;
		LEDRealOut(0,3,wHourMinute,0x42);
	}
}

void JumpToEventDisplay(void)
{
	if(g_wMenuMode==MM_DATA)
	{
		g_wCycleCurSel = EVENT_COUNT;
		g_wPageCurSel = 2;
	}
}

void OnRefreshPageData4(void)
{
	WORD wDaTa;
	SetConstString4(s_szTemp,'t','I','m','E');
	LEDAsciiOut(0,0,s_szTemp);	
	wDaTa = g_deviceTime.wYear*100 + g_deviceTime.wMonth;
	LEDRealOut(0,1,wDaTa,0x42);
	wDaTa = g_deviceTime.wDay*100 + g_deviceTime.wHour;
	LEDRealOut(0,2,wDaTa,0x42);
	wDaTa = g_deviceTime.wMinute*100 + g_deviceTime.wSecond;
	LEDRealOut(0,3,wDaTa,0x42);
}

/*******************************************************************/
void OnRefreshPageData(void)
{
	g_wLEDX = 0;
	g_wLEDY = 0;	
	if(g_wPageCurSel>=4) return;
	switch(g_wPageCurSel)
	{
	case 0: OnRefreshPageData1(); break;
	case 1: OnRefreshPageData2(); break;
	case 2: OnRefreshPageData3(); break;
	case 3: OnRefreshPageData4(); break;
	}
}

void OnRefreshPagePassword(void)
{
	SetPageCount(1);
	LEDClear();
	g_wLEDX = 0;
	g_wLEDY = 3;
	EditAddInteger(&g_wPassword,0,9999,1);
}

void SetOnRefreshPageData1(void)					//保护投退
{
	short i,nPageCnt;
	char chr;
	g_wLEDX = 1;
	nPageCnt = 0;

	for(i=0;i<4;i++)
	{
		if(SETPOINTCFG(i)==PROTECTCFG_NULL) continue;
		nPageCnt++;
		if(nPageCnt==g_wCycleCurSel+1)
		{
			chr = '1' + i;
			SetConstString4(s_szTemp,'P','1','0',chr);
			LEDAsciiOut(0,2,s_szTemp);
			EditAddEnum(&SETPOINTTOG(i),(char*)&c_szProtectTOG,12,3);
		}
	}
	for(i=0;i<4;i++)
	{
		if(g_deviceSetpoint.INSetpoint[i].wConfig==PROTECTCFG_NULL) continue;
		nPageCnt++;
		if(nPageCnt==g_wCycleCurSel+1)
		{
			chr = '5' + i;
			SetConstString4(s_szTemp,'P','1','0',chr);
			LEDAsciiOut(0,2,s_szTemp);
			EditAddEnum(&g_deviceSetpoint.INSetpoint[i].wToggle,(char*)&c_szProtectTOG,12,3);
		}
	}

	SetPageCount(nPageCnt);
	if(nPageCnt==0)
	{
		SetConstString4(s_szTemp,'P','1','0','0');
		LEDAsciiOut(0,2,s_szTemp);
		SetConstString4(s_szTemp,'N','U','L','L');
		LEDAsciiOut(0,3,s_szTemp);
		EdiQuittEdit();
	}
	else EditEnterEdit();
}

void SetOnRefreshPageData2(void)				//系统参数
{
	if(g_wCycleCurSel>12) return;
	
	switch(g_wCycleCurSel)
	{
/*	case 0:
		SetConstString4(s_szTemp,'P','2','0','1');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 1;
		EditAddInteger(&g_deviceParam.wModbusAddr1,1,254,0);
		break;		
	case 1:
		SetConstString4(s_szTemp,'P','2','0','2');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_deviceParam.wBaudrate1,(char*)&c_szBaudrate,7,5);
		break;
*/		
	case 0:
		SetConstString4(s_szTemp,'P','2','0','1');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_deviceParam.wLinkOutAlarmed,(char*)&c_szSelectKH,4,4);
		break;
	case 1:
		SetConstString4(s_szTemp,'P','2','0','2');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_deviceParam.wLinkOutTripped,(char*)&c_szSelectKH,4,4);
		break;
	case 2:
		SetConstString4(s_szTemp,'P','2','0','3');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_deviceParam.wLinkOutErrored,(char*)&c_szSelectKH,4,4);
		break;	
	case 3:
		SetConstString4(s_szTemp,'P','2','0','4');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_deviceParam.wToggleInDC,(char*)&c_szLinkIn,(SWITCH_COUNT+1),4);
		break;
	case 4:
		SetConstString4(s_szTemp,'P','2','0','5');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 2;
		EditAddEnum(&g_deviceParam.wINPowerType,(char*)&c_szSwitchDCAC,2,2);
		break;
// 	case 5:
// 		SetConstString4(s_szTemp,'P','2','0','6');
// 		LEDAsciiOut(0,2,s_szTemp);
// 		g_wLEDX = 1;
// 		EditAddEnum(&g_pDeviceParam->wToggleAlarmKM,(char*)&c_szProtectTOG,2,3);
// 		break;		
	case 5:
		SetConstString4(s_szTemp,'P','2','0','6');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 1;
		EditAddEnum(&g_pDeviceParam->wToggleAlarmOpen,(char*)&c_szProtectTOG,2,3);
		break;
	case 6:
		SetConstString4(s_szTemp,'P','2','0','7');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 1;
		EditAddEnum(&g_pDeviceParam->wToggleAlarmCT,(char*)&c_szProtectTOG,2,3);
		break;
	case 7:
		SetConstString4(s_szTemp,'P','2','0','8');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 2;
		EditAddEnum(&g_pDeviceParam->wModeProtect,(char*)&c_sz2P3P,2,2);
		break;
	case 8:
		SetConstString4(s_szTemp,'P','2','0','9');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_deviceParam.wScaleCT,1,9999,0);
		break;
	case 9:
		SetConstString4(s_szTemp,'P','2','1','0');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_deviceParam.wRatedFrequency,(char*)&c_szRateFrequency,2,4);
		break;
	case 10:
		SetConstString4(s_szTemp,'P','2','1','1');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_deviceParam.wPassword1,0,9999,0);
		break;
	case 11:
		SetConstString4(s_szTemp,'P','2','1','2');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_deviceParam.wPassword2,0,9999,0);
		break;
	}
	EditEnterEdit();
}

void SetOnRefreshPageData3(void)				//开关量参数
{
	if(g_wCycleCurSel>19) return;

	switch(g_wCycleCurSel)
	{
	case 0:
		SetConstString4(s_szTemp,'P','3','0','1');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_inparamTable.inparam[0].wAckDelayTime,1,9999,0);
		break;
	case 1:
		SetConstString4(s_szTemp,'P','3','0','2');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_inparamTable.inparam[0].wEventType,(char*)&c_szSwitchEVENTTYPE,3,4);
		break;
	case 2:
		SetConstString4(s_szTemp,'P','3','0','3');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_inparamTable.inparam[1].wAckDelayTime,1,9999,0);
		break;
	case 3:
		SetConstString4(s_szTemp,'P','3','0','4');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_inparamTable.inparam[1].wEventType,(char*)&c_szSwitchEVENTTYPE,3,4);
		break;

	case 4:
		SetConstString4(s_szTemp,'P','3','0','5');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_inparamTable.inparam[2].wAckDelayTime,1,9999,0);
		break;
	case 5:
		SetConstString4(s_szTemp,'P','3','0','6');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_inparamTable.inparam[2].wEventType,(char*)&c_szSwitchEVENTTYPE,3,4);
		break;

	case 6:
		SetConstString4(s_szTemp,'P','3','0','7');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_inparamTable.inparam[3].wAckDelayTime,1,9999,0);
		break;
	case 7:
		SetConstString4(s_szTemp,'P','3','0','8');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_inparamTable.inparam[3].wEventType,(char*)&c_szSwitchEVENTTYPE,3,4);
		break;

	case 8:
		SetConstString4(s_szTemp,'P','3','0','9');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_inparamTable.inparam[4].wAckDelayTime,1,9999,0);
		break;
	case 9:
		SetConstString4(s_szTemp,'P','3','1','0');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_inparamTable.inparam[4].wEventType,(char*)&c_szSwitchEVENTTYPE,3,4);
		break;

	case 10:
		SetConstString4(s_szTemp,'P','3','1','1');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_inparamTable.inparam[5].wAckDelayTime,1,9999,0);
		break;
	case 11:
		SetConstString4(s_szTemp,'P','3','1','2');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_inparamTable.inparam[5].wEventType,(char*)&c_szSwitchEVENTTYPE,3,4);
		break;

	case 12:
		SetConstString4(s_szTemp,'P','3','1','3');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_inparamTable.inparam[6].wAckDelayTime,1,9999,0);
		break;
	case 13:
		SetConstString4(s_szTemp,'P','3','1','4');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_inparamTable.inparam[6].wEventType,(char*)&c_szSwitchEVENTTYPE,3,4);
		break;

	case 14:
		SetConstString4(s_szTemp,'P','3','1','5');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_inparamTable.inparam[7].wAckDelayTime,1,9999,0);
		break;
	case 15:
		SetConstString4(s_szTemp,'P','3','1','6');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_inparamTable.inparam[7].wEventType,(char*)&c_szSwitchEVENTTYPE,3,4);
		break;

	case 16:
		SetConstString4(s_szTemp,'P','3','1','7');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_inparamTable.inparam[8].wAckDelayTime,1,9999,0);
		break;
	case 17:
		SetConstString4(s_szTemp,'P','3','1','8');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_inparamTable.inparam[8].wEventType,(char*)&c_szSwitchEVENTTYPE,3,4);
		break;

	case 18:
		SetConstString4(s_szTemp,'P','3','1','9');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddInteger(&g_inparamTable.inparam[9].wAckDelayTime,1,9999,0);
		break;
	case 19:
		SetConstString4(s_szTemp,'P','3','2','0');
		LEDAsciiOut(0,2,s_szTemp);
		g_wLEDX = 0;
		EditAddEnum(&g_inparamTable.inparam[9].wEventType,(char*)&c_szSwitchEVENTTYPE,3,4);
		break;
	}
	EditEnterEdit();
}

void SetOnRefreshPageData4(void)				//保护定值
{
	short i,nPageCnt;
	char chrProectIndex,chrSetpointIndex;
	nPageCnt = 0;
	
	g_wLEDX = 0;
	for(i=0;i<4;i++)
	{
		if(SETPOINTCFG(i)==PROTECTCFG_NULL) continue;
		switch(i)
		{
		case 0:
			nPageCnt++;
			chrProectIndex = '1';
			if(nPageCnt==g_wCycleCurSel+1)
			{
				chrSetpointIndex = '1';
				SetConstString4(s_szTemp,'P','4',chrProectIndex,chrSetpointIndex);
				LEDAsciiOut(0,2,s_szTemp);
				EditAddDataWord(&SETPOINT(wSD_SetI),0,9999,0x42,1,1);
			}
			nPageCnt++;
			if(nPageCnt==g_wCycleCurSel+1)
			{
				chrSetpointIndex = '2';
				SetConstString4(s_szTemp,'P','4',chrProectIndex,chrSetpointIndex);
				LEDAsciiOut(0,2,s_szTemp);
				EditAddDataWord(&SETPOINT(wSD_SetT),0,9999,0x42,1,1);
			}
			break;
		case 1:
			nPageCnt++;
			chrProectIndex = '2';
			if(nPageCnt==g_wCycleCurSel+1)
			{
				chrSetpointIndex = '1';
				SetConstString4(s_szTemp,'P','4',chrProectIndex,chrSetpointIndex);
				LEDAsciiOut(0,2,s_szTemp);
				EditAddDataWord(&SETPOINT(wDSXGL_SetI),0,9999,0x42,1,1);
			}
			nPageCnt++;
			if(nPageCnt==g_wCycleCurSel+1)
			{
				chrSetpointIndex = '2';
				SetConstString4(s_szTemp,'P','4',chrProectIndex,chrSetpointIndex);
				LEDAsciiOut(0,2,s_szTemp);
				EditAddDataWord(&SETPOINT(wDSXGL_SetT),0,9999,0x42,1,1);
			}
			break;
		case 2:
			nPageCnt++;
			chrProectIndex = '3';
			if(nPageCnt==g_wCycleCurSel+1)
			{
				chrSetpointIndex = '1';
				SetConstString4(s_szTemp,'P','4',chrProectIndex,chrSetpointIndex);
				LEDAsciiOut(0,2,s_szTemp);
				EditAddDataWord(&SETPOINT(wFSXGL_SetI),0,9999,0x42,1,1);
			}
			nPageCnt++;
			if(nPageCnt==g_wCycleCurSel+1)
			{
				chrSetpointIndex = '2';
				SetConstString4(s_szTemp,'P','4',chrProectIndex,chrSetpointIndex);
				LEDAsciiOut(0,2,s_szTemp);
				EditAddDataWord(&SETPOINT(wFSXGL_SetK),0,9999,0x42,1,1);
			}
			nPageCnt++;
			if(nPageCnt==g_wCycleCurSel+1)
			{
				chrSetpointIndex = '3';
				SetConstString4(s_szTemp,'P','4',chrProectIndex,chrSetpointIndex);
				LEDAsciiOut(0,2,s_szTemp);
				EditAddEnum(&SETPOINT(wFSXGL_IDMT),(char*)&c_szIDMTType,4,4);
			}
			break;
		case 3:
			nPageCnt++;
			chrProectIndex = '4';
			if(nPageCnt==g_wCycleCurSel+1)
			{
				chrSetpointIndex = '1';
				SetConstString4(s_szTemp,'P','4',chrProectIndex,chrSetpointIndex);
				LEDAsciiOut(0,2,s_szTemp);
				EditAddDataWord(&SETPOINT(wLXDL_SetI),0,9999,0x42,1,1);
			}
			nPageCnt++;
			if(nPageCnt==g_wCycleCurSel+1)
			{
				chrSetpointIndex = '2';
				SetConstString4(s_szTemp,'P','4',chrProectIndex,chrSetpointIndex);
				LEDAsciiOut(0,2,s_szTemp);
				EditAddDataWord(&SETPOINT(wLXDL_SetT),0,9999,0x42,1,1);
			}
			break;
		}
	}
	SetPageCount(nPageCnt);
	if(nPageCnt==0)
	{
		SetConstString4(s_szTemp,'P','4','0','0');
		LEDAsciiOut(0,2,s_szTemp);
		SetConstString4(s_szTemp,'N','U','L','L');
		LEDAsciiOut(0,3,s_szTemp);
		EdiQuittEdit();
	}
	else EditEnterEdit();
}


void SetOnRefreshPageData5(void)				//保护配置
{
	if(g_wCycleCurSel>3) return;
	g_wLEDX = 1;
	switch(g_wCycleCurSel)
	{
	case 0:
		SetConstString4(s_szTemp,'P','5','0','1');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddEnum(&SETPOINTCFG(0),(char*)&c_szProtectCFG,4,3);
		break;
	case 1:
		SetConstString4(s_szTemp,'P','5','0','2');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddEnum(&SETPOINTCFG(1),(char*)&c_szProtectCFG,4,3);
		break;
	case 2:
		SetConstString4(s_szTemp,'P','5','0','3');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddEnum(&SETPOINTCFG(2),(char*)&c_szProtectCFG,4,3);
		break;
	case 3:
		SetConstString4(s_szTemp,'P','5','0','4');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddEnum(&SETPOINTCFG(3),(char*)&c_szProtectCFG,4,3);
		break;
	}
	EditEnterEdit();
}

void SetOnRefreshPageData6(void)					//时间设置
{
	if(g_wCycleCurSel>5) return;
	g_wLEDX = 2;
	switch(g_wCycleCurSel)
	{
	case 0:
		SetConstString4(s_szTemp,'P','6','0','1');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddInteger(&g_deviceTime.wYear,0,99,0);
		break;
	case 1:
		SetConstString4(s_szTemp,'P','6','0','2');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddInteger(&g_deviceTime.wMonth,1,12,0);
		break;
	case 2:
		SetConstString4(s_szTemp,'P','6','0','3');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddInteger(&g_deviceTime.wDay,1,31,0);
		break;
	case 3:
		SetConstString4(s_szTemp,'P','6','0','4');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddInteger(&g_deviceTime.wHour,0,23,0);
		break;
	case 4:
		SetConstString4(s_szTemp,'P','6','0','5');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddInteger(&g_deviceTime.wMinute,0,59,0);
		break;
	case 5:
		SetConstString4(s_szTemp,'P','6','0','6');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddInteger(&g_deviceTime.wSecond,0,59,0);
		break;
	}
	EditEnterEdit();
}

void SetOnRefreshPageData7(void)					//测试
{
	if(g_wCycleCurSel>5) return;
	g_wLEDX = 1;
	switch(g_wCycleCurSel)
	{
	case 0:
		SetConstString4(s_szTemp,'P','7','0','1');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddToggle(&g_TestDevice.wKOT);
		break;
	case 1:
		SetConstString4(s_szTemp,'P','7','0','2');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddToggle(&g_TestDevice.wKH01);
		break;
	case 2:
		SetConstString4(s_szTemp,'P','7','0','3');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddToggle(&g_TestDevice.wKH02);
		break;
	case 3:
		SetConstString4(s_szTemp,'P','7','0','4');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddToggle(&g_TestDevice.wKH03);
		break;
	case 4:
		SetConstString4(s_szTemp,'P','7','0','5');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddToggle(&g_TestDevice.wLight);
		break;
	case 5:
		SetConstString4(s_szTemp,'P','7','0','6');
		LEDAsciiOut(0,2,s_szTemp);
		EditAddToggle(&g_TestDevice.wInitDevice);
		break;
	}
	EditEnterEdit();
}

void OnRefreshPageSetup(void)
{
//	SetConstString();
	LEDClear();
	g_wLEDY = 3;
	if(g_wPageCurSel>g_wPageAllCount) g_wPageCurSel = 0;
	switch(g_wPageCurSel)
	{
	case 0:
		SetOnRefreshPageData1();		//保护投退
		break;
	case 1:
		SetPageCount(12);
		SetOnRefreshPageData2();		//系统参数
		break;
	case 2:
		SetPageCount(20);
		SetOnRefreshPageData3();		//开关量参数
		break;
	case 3:
		SetOnRefreshPageData4();		//保护定值
		break;
	case 4:
		SetPageCount(4);
		SetOnRefreshPageData5();		//保护配置
		break;
	case 5:
		SetPageCount(6);
		SetOnRefreshPageData6();		//时间设置
		break;
	case 6:
		SetPageCount(6);
		SetOnRefreshPageData7();		//测试
		break;
	}
}
