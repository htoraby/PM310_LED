#include <Main.h>

CMyOutput g_lightEnableLocal;
CMyOutput g_lightEnableAuto;


//-----------------------------------------------------------------------------
static const char c_szModePT[2][4] = 
{
	"Y/Y","V/V"
};

static const char c_szModeTHD[2][4] = 
{
	"L-N","L-L"
};


//-----------------------------------------------------------------------------
void CMyHMIDMRX81P::OnInit(void)
{
	CMyHMIDMR::OnInit();
	g_lightEnableLocal.OnInit();
	g_lightEnableAuto.OnInit();
}

void CMyHMIDMRX81P::OnTimer10ms(void)
{
	CMyHMIDMR::OnTimer10ms();
	g_lightEnableLocal.SetLevel((g_deviceInfo.wDeviceStatus2&DS2_EnableLocal)?STATUS_ON:STATUS_OFF);
	g_lightEnableAuto.SetLevel((g_deviceInfo.wDeviceStatus2&DS2_AutoMode)?STATUS_ON:STATUS_OFF);
	g_lightEnableLocal.OnTimer10ms();
	g_lightEnableAuto.OnTimer10ms();
}

char* CMyHMIDMRX81P::GetEventText(EVENT* pEvent)
{
	CMyHMIDMR::GetEventText(pEvent);
	char* pszAlarmMsg = NULL;
	switch(pEvent->wCode)
	{
	case EVENTCODE_LOCALBO:
		AddEventText(MULTITEXT("本地操作<PT","LOCALLY OPERATE <T.V. "));
		if(pEvent->wData==0) AddEventText(MULTITEXT("解列>","UNLINK>"));
		else AddEventText(MULTITEXT("并列>","LINK>"));
		break;
	case EVENTCODE_REMOTEBO:
		AddEventText(MULTITEXT("遥控操作<PT","REMOTELY OPERATE <T.V. "));
		if(pEvent->wData==0) AddEventText(MULTITEXT("解列>","UNLINK>"));
		else AddEventText(MULTITEXT("并列>","LINK>"));
		break;
	case EVENTCODE_AUTOLINK:
		AddEventText(MULTITEXT("自动控制<PT","AUTO CONTROL <T.V. "));
		if(pEvent->wData==0) AddEventText(MULTITEXT("解列>","UNLINK>"));
		else AddEventText(MULTITEXT("并列>","LINK>"));
		break;
	case EVENTCODE_STATUS1XPT:
		AddEventText(MULTITEXT("1#PT运行状态->","1# T.V. STATUS->"));
		if(pEvent->wData==0) AddEventText(MULTITEXT("退出","EXITED"));
		else AddEventText(MULTITEXT("投入","RUNNING"));
		break;
	case EVENTCODE_STATUS2XPT:
		AddEventText(MULTITEXT("2#PT运行状态->","2# T.V. STATUS->"));
		if(pEvent->wData==0) AddEventText(MULTITEXT("退出","EXITED"));
		else AddEventText(MULTITEXT("投入","RUNNING"));
		break;
	case EVENTCODE_ALARM1XPT3: pszAlarmMsg = MULTITEXT("1#PT三相断线","1# T.V. THREE-PHASE FAILURE"); break;
	case EVENTCODE_ALARM1XPT2: pszAlarmMsg = MULTITEXT("1#PT两相断线","1# T.V. TWO-PHASE FAILURE"); break;
	case EVENTCODE_ALARM1XPT1: pszAlarmMsg = MULTITEXT("1#PT单相断线","1# T.V. SINGLE-PHASE FAILURE"); break;
	case EVENTCODE_ALARM2XPT3: pszAlarmMsg = MULTITEXT("2#PT三相断线","2# T.V. THREE-PHASE FAILURE"); break;
	case EVENTCODE_ALARM2XPT2: pszAlarmMsg = MULTITEXT("2#PT两相断线","2# T.V. TWO-PHASE FAILURE"); break;
	case EVENTCODE_ALARM2XPT1: pszAlarmMsg = MULTITEXT("2#PT单相断线","2# T.V. SINGLE-PHASE FAILURE"); break;
	}
	if(pszAlarmMsg)
	{
		AddEventText(pszAlarmMsg);
		if(pEvent->wData==0) AddEventText(MULTITEXT("恢复"," RESET"));
	}
	return m_szEventText;
}

void CMyHMIDMRX81P::GetProtectActDataInfo(WORD wProtectAct,WORD wProtectIndexExt,WORD wActData,PROTECTACTDATAINFO* pProtectActDataInfo)
{
	pProtectActDataInfo->wFormat = 0x42;
	switch(wProtectAct)
	{
	case PROTECTACT_U:
		pProtectActDataInfo->pszDataName = (char*)"U";
		pProtectActDataInfo->pszUnitage = (char*)"V";
		pProtectActDataInfo->dwActData = g_data1XUa.GetValueSecondaryFix(wActData);
		break;
	case PROTECTACT_3U0:
		pProtectActDataInfo->pszDataName = (char*)"3U0";
		pProtectActDataInfo->pszUnitage = (char*)"V";
		pProtectActDataInfo->dwActData = g_data1X3U0.GetValueSecondaryFix(wActData);
		break;
	}
}

void CMyHMIDMRX81P::AutoLCDDataOut(WORD wIndex)
{
	CMyHMIDMR::AutoLCDDataOut(wIndex);
	CMyData* pData = NULL;
	BOOL bDataPrimary = FALSE;
	DWORD dwData = 0xffffffff;
	WORD wFormat = 0x52;
	switch(wIndex)
	{
	case INDEX_11XUa: pData = &g_data1XUa; bDataPrimary = TRUE; break;
	case INDEX_11XUb: pData = &g_data1XUb; bDataPrimary = TRUE; break;
	case INDEX_11XUc: pData = &g_data1XUc; bDataPrimary = TRUE; break;
	case INDEX_11XUab: pData = &g_data1XUab; bDataPrimary = TRUE; break;
	case INDEX_11XUbc: pData = &g_data1XUbc; bDataPrimary = TRUE; break;
	case INDEX_11XUca: pData = &g_data1XUca; bDataPrimary = TRUE; break;
	case INDEX_21XUa: pData = &g_data1XUa; break;
	case INDEX_21XUb: pData = &g_data1XUb; break;
	case INDEX_21XUc: pData = &g_data1XUc; break;
	case INDEX_21XUab: pData = &g_data1XUab; break;
	case INDEX_21XUbc: pData = &g_data1XUbc; break;
	case INDEX_21XUca: pData = &g_data1XUca; break;
	case INDEX_21X3U0: pData = &g_data1X3U0; break;
	case INDEX_21X3U2: pData = &g_data1X3U2; break;
	case INDEX_1XF: pData = &g_data1XF; break;
	case INDEX_12XUa: pData = &g_data2XUa; bDataPrimary = TRUE; break;
	case INDEX_12XUb: pData = &g_data2XUb; bDataPrimary = TRUE; break;
	case INDEX_12XUc: pData = &g_data2XUc; bDataPrimary = TRUE; break;
	case INDEX_12XUab: pData = &g_data2XUab; bDataPrimary = TRUE; break;
	case INDEX_12XUbc: pData = &g_data2XUbc; bDataPrimary = TRUE; break;
	case INDEX_12XUca: pData = &g_data2XUca; bDataPrimary = TRUE; break;
	case INDEX_22XUa: pData = &g_data2XUa; break;
	case INDEX_22XUb: pData = &g_data2XUb; break;
	case INDEX_22XUc: pData = &g_data2XUc; break;
	case INDEX_22XUab: pData = &g_data2XUab; break;
	case INDEX_22XUbc: pData = &g_data2XUbc; break;
	case INDEX_22XUca: pData = &g_data2XUca; break;
	case INDEX_22X3U0: pData = &g_data2X3U0; break;
	case INDEX_22X3U2: pData = &g_data2X3U2; break;
	case INDEX_2XF: pData = &g_data2XF; break;
	case INDEX_PARAM_ALARM1XPT: g_edit.AddEditEnumMul(&g_pDeviceParam->wToggleAlarm1XPT); break;
	case INDEX_PARAM_ALARM2XPT: g_edit.AddEditEnumMul(&g_pDeviceParam->wToggleAlarm2XPT); break;
	case INDEX_PARAM_PROTECT1XPT: g_edit.AddEditEnumMul(&g_pDeviceParam->wToggleProtect1XPT); break;
	case INDEX_PARAM_PROTECT2XPT: g_edit.AddEditEnumMul(&g_pDeviceParam->wToggleProtect2XPT); break;
	case INDEX_PARAM_MODEPT: g_edit.AddEditEnumMul(&g_pDeviceParam->wModePT); break;
	case INDEX_PARAM_SCALEPT: g_edit.AddEditDataWord(&g_pDeviceParam->wScalePT); break;
	case INDEX_PARAM_SCALE2ULN: g_lcd.AutoRealOut(g_pDeviceParam->wScale2Uln,0x52); break;
	case INDEX_PARAM_SCALE23U0: g_lcd.AutoRealOut(g_pDeviceParam->wScale23U0,0x52); break;
	case INDEX_PARAM_MODETHD: g_edit.AddEditEnumMul(&g_pDeviceParam->wModeTHD); break;
	case INDEX_ALARMED_1XPT: g_lcd.AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&DS2_Alarm1XPT)); break;
	case INDEX_ALARMED_2XPT: g_lcd.AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&DS2_Alarm2XPT)); break;
	case INDEX_ALARMED_ENABLELOCAL: g_lcd.AutoOutYES_NO((WORD)(g_deviceInfo.wDeviceStatus2&DS2_EnableLocal)); break;
	case INDEX_ALARMED_ENABLEREMOTE: g_lcd.AutoOutYES_NO((WORD)(g_deviceInfo.wDeviceStatus2&DS2_EnableRemote)); break;
	case INDEX_ALARMED_ENABLELINK: g_lcd.AutoOutYES_NO((WORD)(g_deviceInfo.wDeviceStatus2&DS2_EnableLink)); break;
	case INDEX_ALARMED_AUTOMODE: g_lcd.AutoOutYES_NO((WORD)(g_deviceInfo.wDeviceStatus2&DS2_AutoMode)); break;
	case INDEX_ALARMED_STATUS1XPT: g_lcd.AutoOutYES_NO((WORD)(g_deviceInfo.wDeviceStatus2&DS2_Status1XPT)); break;
	case INDEX_ALARMED_STATUS2XPT: g_lcd.AutoOutYES_NO((WORD)(g_deviceInfo.wDeviceStatus2&DS2_Status2XPT)); break;
	}
	if(pData!=NULL)
	{
		dwData = (bDataPrimary)?pData->m_dwDataPrimary:pData->m_dwDataSecondary;
		wFormat = (bDataPrimary)?pData->m_wFormatPrimary:pData->m_wFormatSecondary;
	}
	if(dwData!=0xffffffff) g_lcd.AutoRealOut(dwData,wFormat);
}

void CMyHMIDMRX81P::GetEditMetrics(WORD* pData)
{
	CMyHMIDMR::GetEditMetrics(pData);
	if(pData==&g_pDeviceParam->wToggleAlarm1XPT) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceParam->wToggleAlarm2XPT) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceParam->wToggleProtect1XPT) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceParam->wToggleProtect2XPT) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceParam->wModePT) g_edit.SetEditEnumMetricsMul(2,4,(char*)c_szModePT[0]);
	if(pData==&g_pDeviceParam->wScalePT) g_edit.SetEditDataMetricsInteger(1,9999,FALSE);
	if(pData==&g_pDeviceParam->wModeTHD) g_edit.SetEditEnumMetricsMul(2,4,(char*)c_szModeTHD[0]);
}

void CMyHMIDMRX81P::TestLights(void)
{
	CMyHMIDMR::TestLights();
	g_breaker.m_lightPosClosed.EnterTest(OUTPUT_TM_11);
	g_breaker.m_lightPosOpened.EnterTest(OUTPUT_TM_11);
	g_lightEnableLocal.EnterTest(OUTPUT_TM_11);
	g_lightEnableAuto.EnterTest(OUTPUT_TM_11);
}

void CMyHMIDMRX81P::iiiOnWhileLoopExt(WORD wKeyCode)
{
	CMyHMIDMR::iiiOnWhileLoopExt(wKeyCode);
	if(g_deviceInfo.wDeviceStatus2&DS2_EnableLocal)
	{
		g_breaker.m_lockLocal.Unlock1();
		if(wKeyCode==KEY_OPEN) g_breaker.LocalOpen();
		g_breaker.m_lockLocal.Lock1();
		g_breaker.m_lockLocal.Unlock1();
		if(wKeyCode==KEY_CLOSE) g_breaker.LocalClose();
		g_breaker.m_lockLocal.Lock1();
	}
}


