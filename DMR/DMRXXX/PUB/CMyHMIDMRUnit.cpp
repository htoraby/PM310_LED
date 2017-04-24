#include <Main.h>

CMyOutput g_lightEnableLocal;
CMyOutput g_lightEnableRemote;


//-----------------------------------------------------------------------------
static const char c_szModeCT[2][4] = 
{
	"2CT","3CT"
};

static const char c_szModePT[2][4] = 
{
	"Y/Y","V/V"
};

static void DisplayPE(WORD wIndex)
{
	if(g_pDeviceParam->wLinkInPE[wIndex]==LINKIN_NULL) g_lcd.AutoAsciiOut("---------");
	else g_lcd.AutoRealOut(g_analogDataExt.dwDataPE[wIndex],0x83);
}

static void SetDataMetricsPhQh(void)
{
	g_edit.SetEditDataMetricsReal(0,99999999,0x83,1,1);
}

static void SetDataMetricsPE(void)
{
	g_edit.SetEditDataMetricsReal(0,99999999,0x83,1,1);
}


//-----------------------------------------------------------------------------
void CMyHMIDMRUnit::OnInit(void)
{
	CMyHMIDMR::OnInit();
	g_lightEnableLocal.OnInit();
	g_lightEnableRemote.OnInit();
	m_wLockCnt = 0;
	m_wLockRelease = 0;
	m_bLockRelease = FALSE;
}

void CMyHMIDMRUnit::OnTimer10ms(void)
{
	CMyHMIDMR::OnTimer10ms();
	g_lightEnableLocal.SetLevel((g_deviceInfo.wDeviceStatus2&DS2_EnableLocal)?STATUS_ON:STATUS_OFF);
	g_lightEnableRemote.SetLevel((g_deviceInfo.wDeviceStatus2&DS2_EnableRemote)?STATUS_ON:STATUS_OFF);
	g_lightEnableLocal.OnTimer10ms();
	g_lightEnableRemote.OnTimer10ms();
}

char* CMyHMIDMRUnit::GetEventText(EVENT* pEvent)
{
	CMyHMIDMR::GetEventText(pEvent);
	char* pszAlarmMsg = NULL;
	switch(pEvent->wCode)
	{
	case EVENTCODE_LOCALBO:
		AddEventText(MULTITEXT("本地操作<断路器","LOCALLY OPERATE "));
		if(pEvent->wData==0) AddEventText(MULTITEXT("分闸>","<OPEN C.B.>"));
		else AddEventText(MULTITEXT("合闸>","<CLOSE C.B.>"));
		break;
	case EVENTCODE_REMOTEBO:
		AddEventText(MULTITEXT("遥控操作<断路器","REMOTELY OPERATE "));
		if(pEvent->wData==0) AddEventText(MULTITEXT("分闸>","<OPEN C.B.>"));
		else AddEventText(MULTITEXT("合闸>","<CLOSE C.B.>"));
		break;
	case EVENTCODE_ALARMCTPA: pszAlarmMsg = MULTITEXT("A相保护CT断线","T.A.(P) PHASE A FAILURE"); break;
	case EVENTCODE_ALARMCTPB: pszAlarmMsg = MULTITEXT("B相保护CT断线","T.A.(P) PHASE B FAILURE"); break;
	case EVENTCODE_ALARMCTPC: pszAlarmMsg = MULTITEXT("C相保护CT断线","T.A.(P) PHASE C FAILURE"); break;
	case EVENTCODE_ALARMCTMA: pszAlarmMsg = MULTITEXT("A相测量CT断线","T.A.(M) PHASE A FAILURE"); break;
	case EVENTCODE_ALARMCTMB: pszAlarmMsg = MULTITEXT("B相测量CT断线","T.A.(M) PHASE B FAILURE"); break;
	case EVENTCODE_ALARMCTMC: pszAlarmMsg = MULTITEXT("C相测量CT断线","T.A.(M) PHASE C FAILURE"); break;
	case EVENTCODE_ALARMPT3: pszAlarmMsg = MULTITEXT("三相PT断线","T.V. THREE-PHASE FAILURE"); break;
	case EVENTCODE_ALARMPT2: pszAlarmMsg = MULTITEXT("两相PT断线","T.V. TWO-PHASE FAILURE"); break;
	case EVENTCODE_ALARMPT1: pszAlarmMsg = MULTITEXT("单相PT断线","T.V. SINGLE-PHASE FAILURE"); break;
	case EVENTCODE_ALARMKM: pszAlarmMsg = MULTITEXT("控制电源失电","OPERATING POWER FAILURE"); break;
	case EVENTCODE_ALARMCLOSE: pszAlarmMsg = MULTITEXT("合闸回路断线","CLOSING CIRCUIT FAILURE"); break;
	case EVENTCODE_ALARMOPEN: pszAlarmMsg = MULTITEXT("跳闸回路断线","TRIPPING CIRCUIT FAILURE"); break;
	case EVENTCODE_ERRORCLOSE: AddEventText(MULTITEXT("合闸拒动","CLOSE-COMMAND REJECTED")); break;
	case EVENTCODE_ERROROPEN: AddEventText(MULTITEXT("跳闸拒动","TRIP-COMMAND REJECTED")); break;
	}
	if(pszAlarmMsg)
	{
		AddEventText(pszAlarmMsg);
		if(pEvent->wData==0) AddEventText(MULTITEXT("恢复"," RESET"));
	}
	return m_szEventText;
}

void CMyHMIDMRUnit::GetProtectActDataInfo(WORD wProtectAct,WORD wProtectIndexExt,WORD wActData,PROTECTACTDATAINFO* pProtectActDataInfo)
{
	pProtectActDataInfo->wFormat = 0x42;
	switch(wProtectAct)
	{
	case PROTECTACT_IP:
		pProtectActDataInfo->pszDataName = (char*)"I";
		pProtectActDataInfo->pszUnitage = (char*)"A";
		pProtectActDataInfo->dwActData = g_dataIA.GetValueSecondaryFix(wActData);
		break;
	case PROTECTACT_U:
		pProtectActDataInfo->pszDataName = (char*)"U";
		pProtectActDataInfo->pszUnitage = (char*)"V";
		pProtectActDataInfo->dwActData = g_dataUa.GetValueSecondaryFix(wActData);
		break;
	case PROTECTACT_3I0:
		pProtectActDataInfo->pszDataName = (char*)"3I0";
		pProtectActDataInfo->pszUnitage = (char*)"A";
		pProtectActDataInfo->dwActData = g_data3I0.GetValueSecondaryFix(wActData);
		break;
	case PROTECTACT_3U0:
		pProtectActDataInfo->pszDataName = (char*)"3U0";
		pProtectActDataInfo->pszUnitage = (char*)"V";
		pProtectActDataInfo->dwActData = g_data3U0.GetValueSecondaryFix(wActData);
		break;
	case PROTECTACT_Ix:
		pProtectActDataInfo->pszDataName = (char*)"Ix";
		pProtectActDataInfo->pszUnitage = (char*)"A";
		pProtectActDataInfo->dwActData = g_dataIx.GetValueSecondaryFix(wActData);
		break;
	case PROTECTACT_Ux:
		pProtectActDataInfo->pszDataName = (char*)"Ux";
		pProtectActDataInfo->pszUnitage = (char*)"V";
		pProtectActDataInfo->dwActData = g_dataUxab.GetValueSecondaryFix(wActData);
		break;
	case PROTECTACT_F:
		pProtectActDataInfo->pszDataName = (char*)"F";
		pProtectActDataInfo->pszUnitage = (char*)"Hz";
		pProtectActDataInfo->dwActData = g_dataF.GetValueSecondaryFix(wActData);
		break;
	}
}

void CMyHMIDMRUnit::AutoLCDDataOut(WORD wIndex)
{
	CMyHMIDMR::AutoLCDDataOut(wIndex);
	CMyData* pData = NULL;
	BOOL bDataPrimary = FALSE;
	DWORD dwData = 0xffffffff;
	WORD wFormat = 0x52;
	switch(wIndex)
	{
	case INDEX_1Ia: pData = &g_dataIa; bDataPrimary = TRUE; break;
	case INDEX_1Ib: pData = &g_dataIb; bDataPrimary = TRUE; break;
	case INDEX_1Ic: pData = &g_dataIc; bDataPrimary = TRUE; break;
	case INDEX_1Ua: pData = &g_dataUa; bDataPrimary = TRUE; break;
	case INDEX_1Ub: pData = &g_dataUb; bDataPrimary = TRUE; break;
	case INDEX_1Uc: pData = &g_dataUc; bDataPrimary = TRUE; break;
	case INDEX_1Uab: pData = &g_dataUab; bDataPrimary = TRUE; break;
	case INDEX_1Ubc: pData = &g_dataUbc; bDataPrimary = TRUE; break;
	case INDEX_1Uca: pData = &g_dataUca; bDataPrimary = TRUE; break;
	case INDEX_1P: pData = &g_dataP; bDataPrimary = TRUE; break;
	case INDEX_1Q: pData = &g_dataQ; bDataPrimary = TRUE; break;
	case INDEX_2P: pData = &g_dataP; break;
	case INDEX_2Q: pData = &g_dataQ; break;
	case INDEX_PF: pData = &g_dataPF; break;
	case INDEX_2Ia: pData = &g_dataIa; break;
	case INDEX_2Ib: pData = &g_dataIb; break;
	case INDEX_2Ic: pData = &g_dataIc; break;
	case INDEX_2IA: pData = &g_dataIA; break;
	case INDEX_2IB: pData = &g_dataIB; break;
	case INDEX_2IC: pData = &g_dataIC; break;
	case INDEX_2Ua: pData = &g_dataUa; break;
	case INDEX_2Ub: pData = &g_dataUb; break;
	case INDEX_2Uc: pData = &g_dataUc; break;
	case INDEX_2Uab: pData = &g_dataUab; break;
	case INDEX_2Ubc: pData = &g_dataUbc; break;
	case INDEX_2Uca: pData = &g_dataUca; break;
	case INDEX_23I0: pData = &g_data3I0; break;
	case INDEX_23I2: pData = &g_data3I2; break;
	case INDEX_23U0: pData = &g_data3U0; break;
	case INDEX_23U2: pData = &g_data3U2; break;
	case INDEX_F: pData = &g_dataF; break;
	case INDEX_2Ix: pData = &g_dataIx; break;
	case INDEX_2Uxab: pData = &g_dataUxab; break;
	case INDEX_2Uxbc: pData = &g_dataUxbc; break;
	case INDEX_2Uxca: pData = &g_dataUxca; break;
	case INDEX_23Ux2: pData = &g_data3Ux2; break;
	case INDEX_Fx: pData = &g_dataFx; break;
	case INDEX_PhI: dwData = (g_analogDataExt.dwDataPhImp); wFormat = 0x83; break;
	case INDEX_QhI: dwData = (g_analogDataExt.dwDataQhImp); wFormat = 0x83; break;
	case INDEX_PhE: dwData = (g_analogDataExt.dwDataPhExp); wFormat = 0x83; break;
	case INDEX_QhE: dwData = (g_analogDataExt.dwDataQhExp); wFormat = 0x83; break;
	case INDEX_PE1: DisplayPE(0); break;
	case INDEX_PE2: DisplayPE(1); break;
	case INDEX_PE3: DisplayPE(2); break;
	case INDEX_PE4: DisplayPE(3); break;
	case INDEX_PARAM_ALARMKM: g_edit.AddEditEnumMul(&g_pDeviceParam->wToggleAlarmKM); break;
	case INDEX_PARAM_ALARMCLOSE: g_edit.AddEditEnumMul(&g_pDeviceParam->wToggleAlarmClose); break;
	case INDEX_PARAM_ALARMOPEN: g_edit.AddEditEnumMul(&g_pDeviceParam->wToggleAlarmOpen); break;
	case INDEX_PARAM_ALARMCT: g_edit.AddEditEnumMul(&g_pDeviceParam->wToggleAlarmCT); break;
	case INDEX_PARAM_ALARMPT: g_edit.AddEditEnumMul(&g_pDeviceParam->wToggleAlarmPT); break;
	case INDEX_PARAM_MODECTM: g_edit.AddEditEnumMul(&g_pDeviceParam->wModeCTM); break;
	case INDEX_PARAM_MODECTP: g_edit.AddEditEnumMul(&g_pDeviceParam->wModeCTP); break;
	case INDEX_PARAM_MODEPT: g_edit.AddEditEnumMul(&g_pDeviceParam->wModePT); break;
	case INDEX_PARAM_SCALECT: g_edit.AddEditDataWord(&g_pDeviceParam->wScaleCT); break;
	case INDEX_PARAM_SCALEPT: g_edit.AddEditDataWord(&g_pDeviceParam->wScalePT); break;
	case INDEX_PARAM_LINKINPE1: g_edit.AddEditEnumMul(&g_pDeviceParam->wLinkInPE[0]); break;
	case INDEX_PARAM_LINKINPE2: g_edit.AddEditEnumMul(&g_pDeviceParam->wLinkInPE[1]); break;
	case INDEX_PARAM_LINKINPE3: g_edit.AddEditEnumMul(&g_pDeviceParam->wLinkInPE[2]); break;
	case INDEX_PARAM_LINKINPE4: g_edit.AddEditEnumMul(&g_pDeviceParam->wLinkInPE[3]); break;
	case INDEX_PARAM_PULSESPERKWH1: g_edit.AddEditDataWord(&g_pDeviceParam->wPulsesPerkWh[0]); break;
	case INDEX_PARAM_PULSESPERKWH2: g_edit.AddEditDataWord(&g_pDeviceParam->wPulsesPerkWh[1]); break;
	case INDEX_PARAM_PULSESPERKWH3: g_edit.AddEditDataWord(&g_pDeviceParam->wPulsesPerkWh[2]); break;
	case INDEX_PARAM_PULSESPERKWH4: g_edit.AddEditDataWord(&g_pDeviceParam->wPulsesPerkWh[3]); break;
	case INDEX_PARAM_SCALE2IM: g_lcd.AutoRealOut(g_pDeviceParam->wScale2IM,0x52); break;
	case INDEX_PARAM_SCALE2IP: g_lcd.AutoRealOut(g_pDeviceParam->wScale2IP,0x52); break;
	case INDEX_PARAM_SCALE2ULN: g_lcd.AutoRealOut(g_pDeviceParam->wScale2Uln,0x52); break;
	case INDEX_PARAM_SCALE23I0: g_lcd.AutoRealOut(g_pDeviceParam->wScale23I0,0x52); break;
	case INDEX_PARAM_SCALE23U0: g_lcd.AutoRealOut(g_pDeviceParam->wScale23U0,0x52); break;
	case INDEX_PARAM_SCALE2IX: g_lcd.AutoRealOut(g_pDeviceParam->wScale2Ix,0x52); break;
	case INDEX_PARAM_SCALE2UX: g_lcd.AutoRealOut(g_pDeviceParam->wScale2Ux,0x52); break;
	case INDEX_ALARMED_CTM: g_lcd.AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&DS2_AlarmCTM)); break;
	case INDEX_ALARMED_CTP: g_lcd.AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&DS2_AlarmCTP)); break;
	case INDEX_ALARMED_CT: g_lcd.AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&(DS2_AlarmCTM|DS2_AlarmCTP))); break;
	case INDEX_ALARMED_PT: g_lcd.AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&DS2_AlarmPT)); break;
	case INDEX_ALARMED_KM: g_lcd.AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&DS2_AlarmKM)); break;
	case INDEX_ALARMED_CLOSE: g_lcd.AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&DS2_AlarmClose)); break;
	case INDEX_ALARMED_OPEN: g_lcd.AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&DS2_AlarmOpen)); break;
	case INDEX_ALARMED_ERRORCLOSE: g_lcd.AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&DS2_ErrorClose)); break;
	case INDEX_ALARMED_ERROROPEN: g_lcd.AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&DS2_ErrorOpen)); break;
	case INDEX_ALARMED_LOCKCLOSE: g_lcd.AutoOutYES_NO((WORD)(!(g_deviceInfo.wDeviceStatus2&DS2_LockClose))); break;
	case INDEX_ALARMED_DIRECTP: g_lcd.AutoOutYES_NO((WORD)(!(g_deviceInfo.wDeviceStatus2&DS2_DirectP))); break;
	case INDEX_ALARMED_DIRECTQ: g_lcd.AutoOutYES_NO((WORD)(!(g_deviceInfo.wDeviceStatus2&DS2_DirectQ))); break;
	case INDEX_BOINFO_COUNTCLOSE: g_lcd.AutoWordOut(g_breaker.m_boinfo.wCountClose); break;
	case INDEX_BOINFO_TIMECLOSEMIN: g_lcd.AutoWordOut(g_breaker.m_boinfo.wTimeCloseMin); break;
	case INDEX_BOINFO_TIMECLOSEAVG: g_lcd.AutoWordOut((WORD)((g_breaker.m_boinfo.wCountCloseX==0)?0:(g_breaker.m_boinfo.dwTimeCloseSum/g_breaker.m_boinfo.wCountCloseX))); break;
	case INDEX_BOINFO_TIMECLOSEMAX: g_lcd.AutoWordOut(g_breaker.m_boinfo.wTimeCloseMax); break;
	case INDEX_BOINFO_COUNTOPEN: g_lcd.AutoWordOut(g_breaker.m_boinfo.wCountOpen); break;
	case INDEX_BOINFO_TIMEOPENMIN: g_lcd.AutoWordOut(g_breaker.m_boinfo.wTimeOpenMin); break;
	case INDEX_BOINFO_TIMEOPENAVG: g_lcd.AutoWordOut((WORD)((g_breaker.m_boinfo.wCountOpenX==0)?0:(g_breaker.m_boinfo.dwTimeOpenSum/g_breaker.m_boinfo.wCountOpenX))); break;
	case INDEX_BOINFO_TIMEOPENMAX: g_lcd.AutoWordOut(g_breaker.m_boinfo.wTimeOpenMax); break;
	case INDEX_BOINFO_TRIPIMAX: g_lcd.AutoRealOut(g_dataIA.GetValueSecondaryFix(g_breaker.m_boinfo.wTripIMax),g_dataIA.m_wFormatSecondary); break;
	case INDEX_BOINFO_TRIPI2TSUM: g_lcd.AutoRealOut((g_breaker.m_boinfo.dwTripI2tSum+50L)/100,0x80); break;
	}
	if(pData!=NULL)
	{
		dwData = (bDataPrimary)?pData->m_dwDataPrimary:pData->m_dwDataSecondary;
		wFormat = (bDataPrimary)?pData->m_wFormatPrimary:pData->m_wFormatSecondary;
	}
	if(dwData!=0xffffffff) g_lcd.AutoRealOut(dwData,wFormat);
}

void CMyHMIDMRUnit::GetEditMetrics(WORD* pData)
{
	CMyHMIDMR::GetEditMetrics(pData);
	if(pData==&g_pDeviceParam->wToggleAlarmKM) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceParam->wToggleAlarmClose) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceParam->wToggleAlarmOpen) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceParam->wToggleAlarmCT) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceParam->wToggleAlarmPT) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceParam->wModeCTM) g_edit.SetEditEnumMetricsMul(2,4,(char*)c_szModeCT[0]);
	if(pData==&g_pDeviceParam->wModeCTP) g_edit.SetEditEnumMetricsMul(2,4,(char*)c_szModeCT[0]);
	if(pData==&g_pDeviceParam->wModePT) g_edit.SetEditEnumMetricsMul(2,4,(char*)c_szModePT[0]);
	if(pData==&g_pDeviceParam->wScaleCT) g_edit.SetEditDataMetricsInteger(1,9999,FALSE);
	if(pData==&g_pDeviceParam->wScalePT) g_edit.SetEditDataMetricsInteger(1,9999,FALSE);
	if(pData==(WORD*)&g_analogDataExt.dwDataPhImp) SetDataMetricsPhQh();
	if(pData==(WORD*)&g_analogDataExt.dwDataQhImp) SetDataMetricsPhQh();
	if(pData==(WORD*)&g_analogDataExt.dwDataPhExp) SetDataMetricsPhQh();
	if(pData==(WORD*)&g_analogDataExt.dwDataQhExp) SetDataMetricsPhQh();
	for(WORD i=0;i<4;i++)
	{
		if(pData==&g_pDeviceParam->wLinkInPE[i]) g_edit.SetEditEnumMetricsMul(1+SWITCH_COUNT,5,(char*)c_szLinkIn[0]);
		if(pData==&g_pDeviceParam->wPulsesPerkWh[i]) g_edit.SetEditDataMetricsInteger(1,9999,FALSE);
		if(pData==(WORD*)&g_analogDataExt.dwDataPE[i]) SetDataMetricsPE();
	}
}

void CMyHMIDMRUnit::TestLights(void)
{
	CMyHMIDMR::TestLights();
	g_breaker.m_lightPosClosed.EnterTest(OUTPUT_TM_11);
	g_breaker.m_lightPosOpened.EnterTest(OUTPUT_TM_11);
	g_lightEnableLocal.EnterTest(OUTPUT_TM_11);
	g_lightEnableRemote.EnterTest(OUTPUT_TM_11);
}

void CMyHMIDMRUnit::iiiOnWhileLoopExt(WORD wKeyCode)
{
	CMyHMIDMR::iiiOnWhileLoopExt(wKeyCode);
	if(g_deviceInfo.wDeviceStatus2&DS2_EnableLocal)
	{
#ifdef KEY_OPEN
		g_breaker.m_lockLocal.Unlock1();
		if(wKeyCode==KEY_OPEN) g_breaker.LocalOpen();
		g_breaker.m_lockLocal.Lock1();
#endif
#ifdef KEY_CLOSE
		g_breaker.m_lockLocal.Unlock1();
		if(wKeyCode==KEY_CLOSE) g_breaker.LocalClose();
		g_breaker.m_lockLocal.Lock1();
#endif
	}
#ifdef KEY_LOCK
	if(wKeyCode==KEY_LOCK)
	{
		if(m_wLockCnt<=LOCKCOUNT) m_wLockCnt++;
	}
	else m_wLockCnt = 0;
	if(m_wLockCnt==LOCKCOUNT) // g_app.m_wLockCnt = LOCKCOUNT;
		g_app.m_bLockStatus = !g_app.m_bLockStatus;
#endif
}


