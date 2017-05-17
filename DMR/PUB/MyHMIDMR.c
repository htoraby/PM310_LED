#include <Main.h>

// MyOutput g_lightRun;
// MyOutput g_lightErrored;
// MyOutput g_lightAlarmed;
// MyOutput g_lightTripped;

// #ifdef MULTI_LANGUAGE
// const char c_szMultiLanguage[2][8] = 
// {
// 	"Chinese","English"
// };
// #endif
// 
// const char c_szProtectTOG[][4] = 
// {
// 	"OFF"," ON"
// };
// 
// char g_szEventText[41];
// WORD g_wCountEventText;

//-----------------------------------------------------------------------------
void MyHMI_OnInit(void)
{
//     LCD_OnInit();
    Key_OnInit();
    Edit_OnInit();

    Page_OnInit();
//     DisableSavescreen();
    MyHMI_OnRefresh(RM_PAGEENTER);
}

void MyHMI_OnTimer10ms(void)
{
    BOOL bGJ = FALSE;
    Key_SetKeyRepeatCode(KEY_REPEATCODE);
    Key_OnTimer10ms();
    Page_OnTimer10ms();
//     Output_SetLevel(&g_lightRun,(Time_IsFlashing())?STATUS_ON:STATUS_OFF);
//     // 	Output_SetLevel(&g_lightComm,(g_wCommLight)?STATUS_ON:STATUS_OFF);
// 
//     if(g_deviceInfo.wDeviceStatus1&DS1_Alarmed) bGJ = TRUE;
//     if(g_deviceInfo.wDeviceStatus1&DS1_Errored) bGJ = TRUE;
//     Output_SetLevel(&g_lightAlarmed,bGJ?STATUS_ON:STATUS_OFF);
//     Output_SetLevel(&g_lightTripped,(g_deviceInfo.wDeviceStatus1&DS1_Tripped)?STATUS_ON:STATUS_OFF);
//     Output_SetLevel(&g_lightErrored,(g_deviceInfo.wDeviceStatus1&DS1_Errored)?STATUS_ON:STATUS_OFF);
//     Output_OnTimer10ms(&g_lightRun);
//     // 	Output_OnTimer10ms(&g_lightComm);
//     Output_OnTimer10ms(&g_lightAlarmed);
//     Output_OnTimer10ms(&g_lightTripped);
//     Output_OnTimer10ms(&g_lightErrored);

    MyHMI_OnTimer10msSub();
}

void MyHMI_OnTimer250ms(void)
{
    Edit_OnTimer250ms();
}

void MyHMI_OnTimer1000ms(void)
{
    MyHMI_OnRefresh(RM_TIMER1S);
}

void MyHMI_OnWhileLoop(void)
{
    WORD wKeyCode;
    wKeyCode = Key_GetKeyQueue();
    if(wKeyCode!=KEY_NULL)
    {
// 		Menu_OnKeyMsg(wKeyCode);
        Page_OnKeyMsg(wKeyCode);
        MyHMI_iiiOnWhileLoopExt(wKeyCode);
    }
// 	if(g_deviceInfo.wDeviceStatus1&(DS1_Alarmed|DS1_Tripped|DS1_Errored)) Menu_DisableSaveScreen();
// 	LCD_Flush();
    Page_RefreshCommon(RM_EXTERNAL);
    
    LED_Flush();
}

void MyHMI_iiiOnWhileLoopExt(WORD wKeyCode)
{
//     if(wKeyCode==KEY_RESET) MyApp_OnResetDevice();
}

void MyHMI_OnUpdateDevice(void)
{
// 	if(g_wMenuMode==MM_MENUPAGE) Menu_OnRefreshPage(RM_EXTERNAL);
}

WORD MyHMI_GetPasswordMode(WORD wInputPassword)
{
//     if(wInputPassword==99) return PASSWORD_LEVEL2;
//     return PASSWORD_NULL;
    return 0;
}

void MyHMI_AddEventText(char* pszText)
{
// 	WORD i;
// 	for(i=0;i<40;i++)
// 	{
// 		if(*pszText && g_wCountEventText<40)
// 		{
// 			g_szEventText[g_wCountEventText] = *pszText;
// 			g_wCountEventText++;
// 			pszText++;
// 		}
// 	}
}

void MyHMI_AddEventTextW(WORD* pszwText)
{
// 	WORD i;
// 	for(i=0;i<40;i++)
// 	{
// 		if(*pszwText && g_wCountEventText<40)
// 		{
// 			g_szEventText[g_wCountEventText] = (char)(*pszwText);
// 			g_wCountEventText++;
// 			pszwText++;
// 		}
// 	}
}

// char* MyHMI_GetEventText(EVENT* pEvent)
// {
// 	WORD i;
// // 	INPARAM* pInParam;
// 	WORD wProtectIndexExt;
// 	WORD wProtectIndex;
// 	PROTECTACTDATAINFO protectActDataInfo;
// 	const PROTECTACTINFO* pprotectActInfo;
// 	char szProtectActData[10];
// 
// 	for(i=0;i<41;i++) g_szEventText[i] = 0;
// 	g_wCountEventText = 0;
// 	if(pEvent->wCode>=EVENTCODE_SWITCH && pEvent->wCode<EVENTCODE_SWITCH+SWITCH_COUNT)
// 	{
//         MyHMI_AddEventText((char*)g_pszInName[pEvent->wCode-EVENTCODE_SWITCH]);
//         MyHMI_AddEventText("->");
//         MyHMI_AddEventText((pEvent->wData==0)?"分位":"合位");
// 	}
//     if(pEvent->wCode>=EVENTCODE_REMOTE && pEvent->wCode<EVENTCODE_REMOTE+RELAYKH_COUNT)
//     {
//         MyHMI_AddEventText((char*)g_pszDoName[pEvent->wCode-EVENTCODE_REMOTE]);
//         MyHMI_AddEventText("->");
//         MyHMI_AddEventText("遥控出口");
//     }    
// #ifdef _CMYPROTECT_H
// 	if(pEvent->wCode>=EVENTCODE_PROTECT && pEvent->wCode<EVENTCODE_PROTECT+256)
// 	{
// 		wProtectIndexExt = (WORD)(pEvent->wCode-EVENTCODE_PROTECT);
// 		if((wProtectIndexExt&0x003f)<PROTECT_IN1)
// 		{
// 			wProtectIndex = wProtectIndexExt&0x001f;
// 			protectActDataInfo.pszDataName = 0;
// 			protectActDataInfo.pszUnitage = 0;
// 			protectActDataInfo.wFormat = 0x42;
// 			protectActDataInfo.dwActData = 0;
// 			pprotectActInfo = c_protectActInfo;
// 			MyHMI_GetProtectActDataInfo(pprotectActInfo[wProtectIndex].wProtectAct,wProtectIndexExt,pEvent->wData,&protectActDataInfo);
// 			if(pprotectActInfo[wProtectIndex].pszName)
// 			{
// 				MyHMI_AddEventText(pprotectActInfo[wProtectIndex].pszName);
// 				MyHMI_AddEventText("保护动作");
// 				if((pEvent->wData!=0xffff)&&(pprotectActInfo[wProtectIndex].wProtectAct!=PROTECTACT_NULL))
// 				{
// 					MyHMI_AddEventText(",");
// 					MyHMI_AddEventText(protectActDataInfo.pszDataName);
// 					MyHMI_AddEventText("=");
// //					LCD_FormatReal(szProtectActData, pEvent->wData, protectActDataInfo.wFormat);
// 					MyHMI_AddEventText(szProtectActData);
// 					MyHMI_AddEventText(protectActDataInfo.pszUnitage);
// 				}
// 			}
// 		}
// 	}
// 	if(pEvent->wCode>=EVENTCODE_PROTECT+PROTECT_IN1 && pEvent->wCode<EVENTCODE_PROTECT+PROTECT_MAX)
// 	{
// 		wProtectIndexExt = (WORD)(pEvent->wCode-EVENTCODE_PROTECT-PROTECT_IN1);
//         MyHMI_AddEventText((char*)g_pszInName[wProtectIndexExt]);
//         MyHMI_AddEventText("保护动作");
// 	}
// #endif/*_CMYPROTECT_H*/
// 	MyHMI_GetEventTextSub(pEvent);
// 	return g_szEventText;
//     return NULL;
// }

void MyHMI_AutoLCDDataOut(WORD wIndex)
{
	switch(wIndex)
	{
	case INDEX_DEVICETYPE: // LCD_AutoAsciiOutW(g_deviceParam.wszDeviceType); break;
	case INDEX_VERSION:
// 		LCD_AutoRealOut(MAIN_VERSION+SUB_VERSION,0x42);
// 		g_wLCDAutoPosY -= g_wLCDAutoEnter;
// 		LCD_AutoAsciiOut("V\4");
		break;
	case INDEX_NUMPWRUPS: // LCD_AutoRealOut(g_deviceInfo.wNumPwrup,0x50); break;
	case INDEX_WRMSTR: // LCD_AutoRealOut(g_deviceInfo.wWrmStr,0x50); break;
// #ifdef COMM_MODEBUS   
// 	case INDEX_PARAM_COMMADDR: EditG_AddEditDataWord(&g_deviceParam.wModbusAddr1); break;
// 	case INDEX_PARAM_COMMBUADRATE: EditG_AddEditEnumMul(&g_deviceParam.wBaudrate1); break;
// #endif
// 
// #ifdef MULTI_LANGUAGE
// 	case INDEX_PARAM_MULTILANGUAGE: EditG_AddEditEnumMul(&g_deviceParam.wMultiLanguage); break;
// #endif
	case INDEX_DATE:
//         LCD_DateOut(g_wLCDAutoPosX,g_wLCDAutoPosY,g_deviceTime.wYear,g_deviceTime.wMonth,g_deviceTime.wDay);
//         g_wLCDAutoPosY += g_wLCDAutoEnter;
		break;
	case INDEX_TIME:
// 		LCD_TimeOut(g_wLCDAutoPosX,g_wLCDAutoPosY,g_deviceTime.wHour,g_deviceTime.wMinute,g_deviceTime.wSecond,0xffff);
// 		g_wLCDAutoPosY += g_wLCDAutoEnter;
		break;
	case INDEX_ERRORED_PARAM: // LCD_AutoOutERR_OK((WORD)(g_deviceInfo.wDeviceStatus1&DS1_ErrorParam)); break;
	case INDEX_ERRORED_REGULATE: // LCD_AutoOutERR_OK((WORD)(g_deviceInfo.wDeviceStatus1&DS1_ErrorRegulate)); break;
	case INDEX_ERRORED_SETPOINT: // LCD_AutoOutERR_OK((WORD)(g_deviceInfo.wDeviceStatus1&DS1_ErrorSetpoint)); break;
	case INDEX_ERRORED_AD: // LCD_AutoOutERR_OK((WORD)(g_deviceInfo.wDeviceStatus1&DS1_ErrorAD)); break;
	case INDEX_ERRORED_TIME: // LCD_AutoOutERR_OK((WORD)(g_deviceInfo.wDeviceStatus1&DS1_ErrorTime)); break;
    case INDEX_CRCINFO:
        {
//             char ch[9];
//             short i, ChCnt = 8;
//             DWORD dwCRC32 = g_pCRCInfo->dwCRC32;
//             const char c_ch[16] = {'0', '1', '2', '3', '4', '5',
//                                    '6', '7', '8', '9', 'A', 'B',
//                                    'C', 'D', 'E', 'F'};
//             if(g_pCRCInfo->dwType==CRCINFO_TYPE_CRC16) ChCnt = 4;
//             for(i=0;i<ChCnt;i++)
//             {
//                 ch[ChCnt-1-i] = c_ch[dwCRC32&0xf];
//                 dwCRC32 = dwCRC32>>4;
//             }
//             ch[ChCnt] = '\0';
//             LCD_AutoAsciiOut(ch);
        }        
        break;
	}
	MyHMI_AutoLCDDataOutSub(wIndex);
}

void MyHMI_GetEditMetrics(WORD* pData)
{
// 	WORD i;
// #ifdef COMM_MODEBUS
// 	if(pData==&g_deviceParam.wModbusAddr1) EditG_SetEditDataMetricsInteger(1,247,FALSE);
// 	if(pData==&g_deviceParam.wBaudrate1) EditG_SetEditEnumMetricsMul(3,6,(char*)c_szSCIBaudRate[0]);
// #endif
// 
// #ifdef MULTI_LANGUAGE
// 	if(pData==&g_deviceParam.wMultiLanguage) EditG_SetEditEnumMetricsMul(2,8,(char*)c_szMultiLanguage[0]);
// #endif
// 
// 	if(pData==&g_deviceTime.wYear) EditG_SetEditDataMetricsInteger(0,50,TRUE);
// 	if(pData==&g_deviceTime.wMonth) EditG_SetEditDataMetricsInteger(1,12,TRUE);
// 	if(pData==&g_deviceTime.wDay) EditG_SetEditDataMetricsInteger(1,31,TRUE);
// 	if(pData==&g_deviceTime.wHour) EditG_SetEditDataMetricsInteger(0,23,TRUE);
// 	if(pData==&g_deviceTime.wMinute) EditG_SetEditDataMetricsInteger(0,59,TRUE);
// 	if(pData==&g_deviceTime.wSecond) EditG_SetEditDataMetricsInteger(0,59,TRUE);
// #ifdef _CMYPROTECT_H
// 	for(i=0;i<PROTECT_MAX1;i++)
// 	{
//         if(pData==&SETPOINTCFG(i)) EditG_SetEditEnumMetricsTog();
// 		if(pData==&SETPOINTTOG(i)) EditG_SetEditEnumMetricsMul(2,4,(char*)c_szProtectTOG[0]);
// 	}
// 	for(i=0;i<INSETPOINTNUM;i++)
// 	{
//         if(pData==&g_deviceSetpoint.INSetpoint[i].wConfig) EditG_SetEditEnumMetricsTog();
//     	if(pData==&g_deviceSetpoint.INSetpoint[i].wToggle) EditG_SetEditEnumMetricsMul(2,4,(char*)c_szProtectTOG[0]);
// 	}
// // 	PGPRT_GetEditMetrics(pData,&g_deviceSetpoint.wSetpointArea1[0]);
// #endif/*_CMYPROTECT_H*/
	MyHMI_GetEditMetricsSub(pData);
}

void MyHMI_TestLights(void)
{
// 	Output_EnterTest(&g_lightRun,OUTPUT_TM_11,300);
// // 	Output_EnterTest(&g_lightComm,OUTPUT_TM_11,300);
// 	Output_EnterTest(&g_lightErrored,OUTPUT_TM_11,300);
// 	Output_EnterTest(&g_lightAlarmed,OUTPUT_TM_11,300);
// 	Output_EnterTest(&g_lightTripped,OUTPUT_TM_11,300);
	MyHMI_TestLightsSub();
}

void MyHMI_OnResetDevice(void)
{
}

void MyHMI_OnRefresh(WORD wRefreshMode)
{
    if(wRefreshMode==RM_TIMER1S)
    {
        Page_Refresh(wRefreshMode);
        Edit_OnRefreshPage();
    }
    else
    {
        LED_Clear();
        Edit_OnInit();
        if(wRefreshMode==RM_PAGEENTER)
        {
            g_wPageCurSel = 0;
        }
        Page_Refresh(wRefreshMode);
        Edit_OnRefreshPage();
    }
}