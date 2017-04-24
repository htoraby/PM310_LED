#include <Main.h>

DEVICEPARAM_DMRX81P* g_pDeviceParam;
ANALOGDATA g_analogData;
ANALOGDATAEXT g_analogDataExt;
CMyData g_data1XUa;
CMyData g_data1XUb;
CMyData g_data1XUc;
CMyData g_data1XUab;
CMyData g_data1XUbc;
CMyData g_data1XUca;
CMyData g_data1X3U0;
CMyData g_data1X3U2;
CMyData g_data1XF;
CMyData g_data2XUa;
CMyData g_data2XUb;
CMyData g_data2XUc;
CMyData g_data2XUab;
CMyData g_data2XUbc;
CMyData g_data2XUca;
CMyData g_data2X3U0;
CMyData g_data2X3U2;
CMyData g_data2XF;
CMyBreakerOperate g_breaker;


//-----------------------------------------------------------------------------
static void CalculateTHD(THDINFO* pTHDInfo)
{
	DWORD dwSum = 0L;
	dwSum += (DWORD)pTHDInfo->wTHD2*(DWORD)pTHDInfo->wTHD2;
	dwSum += (DWORD)pTHDInfo->wTHD3*(DWORD)pTHDInfo->wTHD3;
	dwSum += (DWORD)pTHDInfo->wTHD4*(DWORD)pTHDInfo->wTHD4;
	dwSum += (DWORD)pTHDInfo->wTHD5*(DWORD)pTHDInfo->wTHD5;
	dwSum += (DWORD)pTHDInfo->wTHD6*(DWORD)pTHDInfo->wTHD6;
	dwSum += (DWORD)pTHDInfo->wTHD7*(DWORD)pTHDInfo->wTHD7;
	dwSum += (DWORD)pTHDInfo->wTHD8*(DWORD)pTHDInfo->wTHD8;
	dwSum += (DWORD)pTHDInfo->wTHD9*(DWORD)pTHDInfo->wTHD9;
	dwSum += (DWORD)pTHDInfo->wTHD10*(DWORD)pTHDInfo->wTHD10;
	dwSum += (DWORD)pTHDInfo->wTHD11*(DWORD)pTHDInfo->wTHD11;
	pTHDInfo->wTHD = GetSqrt(dwSum);
}

static void CalculateTHDn(WORD wTHD,WORD wIndexDFTa,WORD wIndexDFTb,WORD wIndexDFTc,WORD* pTHDa,WORD* pTHDb,WORD* pTHDc)
{
	short nRa,nRb,nRc;
	short nXa,nXb,nXc;
	g_measure.CalculateDFTn(wIndexDFTa,wTHD,&nRa,&nXa);
	g_measure.CalculateDFTn(wIndexDFTb,wTHD,&nRb,&nXb);
	g_measure.CalculateDFTn(wIndexDFTc,wTHD,&nRc,&nXc);
	if(g_pDeviceParam->wModeTHD==0)
	{
		*pTHDa = GetSqrtX(nRa,nXa);
		*pTHDb = GetSqrtX(nRb,nXb);
		*pTHDc = GetSqrtX(nRc,nXc);
	}
	else
	{
		*pTHDa = GetSqrtX(nRa-nRb,nXa-nXb);
		*pTHDb = GetSqrtX(nRb-nRc,nXb-nXc);
		*pTHDc = GetSqrtX(nRc-nRa,nXc-nXa);
	}
}

static WORD GetTHDPercent(WORD wTHD,WORD wData)
{
	if(wData>0) return WORD((10000L*(DWORD)wTHD+(wData>>1))/wData);
	return 0;
}


//-----------------------------------------------------------------------------
void CMyAppDMRX81P::OnInitParams(void)
{
	CMyAppDMR::OnInitParams();
	g_pDeviceParam = (DEVICEPARAM_DMRX81P*)&g_deviceParam.wReserved[0];
	MemoryClear((WORD*)&g_analogData,SIZEOFWORD(g_analogData));
	MemoryClear((WORD*)&g_analogDataExt,SIZEOFWORD(g_analogDataExt));
	g_pDeviceParam->wToggleAlarm1XPT = TOGGLE_ON;
	g_pDeviceParam->wToggleAlarm2XPT = TOGGLE_ON;
	g_pDeviceParam->wToggleProtect1XPT = TOGGLE_ON;
	g_pDeviceParam->wToggleProtect2XPT = TOGGLE_ON;
	g_pDeviceParam->wModePT = MODEPT_Y;
	g_pDeviceParam->wScalePT = 100;
	g_pDeviceParam->wScale2Uln = 10000;
	g_pDeviceParam->wScale23U0 = 17320;
	g_pDeviceParam->wModeTHD = 0;
	CMySwitch::SetInParam(&g_inparamTable.inparam[0],EVENTTYPE_RUNINFO,"PT并列状态","解列","并列");
	CMySwitch::SetInParam(&g_inparamTable.inparam[1],EVENTTYPE_RUNINFO,"PT并列闭锁","未闭锁","闭锁");
	CMySwitch::SetInParam(&g_inparamTable.inparam[2],EVENTTYPE_RUNINFO,"1#PT工作位置","非工作","工作");
	CMySwitch::SetInParam(&g_inparamTable.inparam[3],EVENTTYPE_RUNINFO,"1#PT试验位置","非试验","试验");
	CMySwitch::SetInParam(&g_inparamTable.inparam[4],EVENTTYPE_RUNINFO,"2#PT工作位置","非工作","工作");
	CMySwitch::SetInParam(&g_inparamTable.inparam[5],EVENTTYPE_RUNINFO,"2#PT试验位置","非试验","试验");
	CMySwitch::SetInParam(&g_inparamTable.inparam[6],EVENTTYPE_NULL,"母分开关位置","分位","合位");
	CMySwitch::SetInParam(&g_inparamTable.inparam[7],EVENTTYPE_NULL,"母分工作位置","非工作","工作");
	CMySwitch::SetInParam(&g_inparamTable.inparam[8],EVENTTYPE_NULL,"隔离工作位置","非工作","工作");
}

void CMyAppDMRX81P::OnInit(void)
{
	CMyAppDMR::OnInit();
	m_alarmgroup1XPT.OnInit();
	m_alarmgroup2XPT.OnInit();
	m_wHardEnableAuto = BOM_NULL;
	m_wHardEnableLocal = BOM_NULL;
	m_wHardEnableRemote = BOM_NULL;
	m_wLADEnableAuto = BOM_NULL;
	m_wLADEnableLocal = BOM_NULL;
	m_wLADEnableRemote = BOM_NULL;
	m_wLADHandClose = 0x0000;
	m_wLADHandOpen = 0x0000;
	g_data1XUa.OnInit();
	g_data1XUb.OnInit();
	g_data1XUc.OnInit();
	g_data1XUab.OnInit();
	g_data1XUbc.OnInit();
	g_data1XUca.OnInit();
	g_data1X3U0.OnInit();
	g_data1X3U2.OnInit();
	g_data1XF.OnInit();
	g_data2XUa.OnInit();
	g_data2XUb.OnInit();
	g_data2XUc.OnInit();
	g_data2XUab.OnInit();
	g_data2XUbc.OnInit();
	g_data2XUca.OnInit();
	g_data2X3U0.OnInit();
	g_data2X3U2.OnInit();
	g_data2XF.OnInit();
	g_breaker.OnInit();
	m_wTimerTHD = 0;
	for(WORD i=0;i<10;i++)
	{
		m_filter1XUa[i].OnInit();
		m_filter1XUb[i].OnInit();
		m_filter1XUc[i].OnInit();
		m_filter2XUa[i].OnInit();
		m_filter2XUb[i].OnInit();
		m_filter2XUc[i].OnInit();
	}
}

void CMyAppDMRX81P::OnTimer1ms(void)
{
	CMyAppDMR::OnTimer1ms();
	g_breaker.OnTimer1ms();
}

void CMyAppDMRX81P::OnTimer10ms(void)
{
	// PT并列条件判断(硬件):
	BOOL bEnableLink = TRUE;
	if(g_deviceInfo.wSwitchStatus&SS_IN02) bEnableLink = FALSE;
	if((g_deviceInfo.wSwitchStatus&SS_IN07)==0) bEnableLink = FALSE;
	if((g_deviceInfo.wSwitchStatus&SS_IN08)==0) bEnableLink = FALSE;
	if((g_deviceInfo.wSwitchStatus&SS_IN09)==0) bEnableLink = FALSE;
	// PT保护判断:
	BOOL bProtect1XPT = FALSE;
	BOOL bProtect2XPT = FALSE;
	if((g_deviceInfo.wSwitchStatus&SS_IN03)==0) bProtect1XPT = TRUE;
	if((g_deviceInfo.wSwitchStatus&SS_IN05)==0) bProtect2XPT = TRUE;
	if(bEnableLink)
	{
		if(g_pDeviceParam->wToggleProtect1XPT==TOGGLE_ON && (g_deviceInfo.wDeviceStatus2&DS2_Alarm1XPT)) bProtect1XPT = TRUE;
		if(g_pDeviceParam->wToggleProtect2XPT==TOGGLE_ON && (g_deviceInfo.wDeviceStatus2&DS2_Alarm2XPT)) bProtect2XPT = TRUE;
	}
	WORD wDeviceStatus2 = g_deviceInfo.wDeviceStatus2;
	SETBIT((bProtect1XPT==FALSE),g_deviceInfo.wDeviceStatus2,DS2_Status1XPT);
	SETBIT((bProtect2XPT==FALSE),g_deviceInfo.wDeviceStatus2,DS2_Status2XPT);
	if((wDeviceStatus2^g_deviceInfo.wDeviceStatus2)&DS2_Status1XPT)
	{
		g_eventTable.AddEvent(EVENTTYPE_RUNINFO,EVENTCODE_STATUS1XPT,bProtect1XPT?0:1);
	}
	if((wDeviceStatus2^g_deviceInfo.wDeviceStatus2)&DS2_Status2XPT)
	{
		g_eventTable.AddEvent(EVENTTYPE_RUNINFO,EVENTCODE_STATUS2XPT,bProtect2XPT?0:1);
	}
	// PT并列条件判断(软件):
	if(bProtect1XPT==bProtect2XPT) bEnableLink = FALSE;
	SETBIT(bEnableLink,g_deviceInfo.wDeviceStatus2,DS2_EnableLink);
	g_breaker.m_wLockClose = (bEnableLink)?0x0000:0xaaaa;

	m_wLADEnableAuto = BOM_NULL;
	m_wLADEnableLocal = BOM_NULL;
	m_wLADEnableRemote = BOM_NULL;
	m_wLADHandClose = 0x0000;
	m_wLADHandOpen = 0x0000;
	CMyAppDMR::OnTimer10ms();
	g_breaker.SetDataIMax(0,0);
	g_breaker.OnTimer10ms();
	if(g_breaker.m_wLockClose==0xaaaa) bEnableLink = FALSE;

	// 自动并列处理:
	if(g_deviceInfo.wDeviceStatus2&DS2_AutoMode)
	{
		if(bEnableLink)
		{
			if(!g_breaker.m_relayKOC.IsOutputValid() && (g_deviceInfo.wSwitchStatus&SS_IN01)==0)
			{
				g_eventTable.AddEvent(EVENTTYPE_OPERATE,EVENTCODE_AUTOLINK,1);
			}
			g_breaker.m_relayKOT.SetLevel(STATUS_OFF);
			g_breaker.m_relayKOC.SetPulse(20);
		}
		else
		{
			if(!g_breaker.m_relayKOT.IsOutputValid() && (g_deviceInfo.wSwitchStatus&SS_IN01)==SS_IN01)
			{
				g_eventTable.AddEvent(EVENTTYPE_OPERATE,EVENTCODE_AUTOLINK,0);
			}
			g_breaker.m_relayKOC.SetLevel(STATUS_OFF);
			g_breaker.m_relayKOT.SetPulse(20);
		}
	}
	// 手动并列处理:
	else
	{
		if(bEnableLink)
		{
			if(m_wLADHandClose==0xaaaa && (g_deviceInfo.wSwitchStatus&SS_IN01)==0) g_breaker.m_relayKOC.SetPulse(20);
			if(m_wLADHandOpen==0xaaaa && (g_deviceInfo.wSwitchStatus&SS_IN01)) g_breaker.m_relayKOT.SetPulse(20);
		}
		else
		{
			if(g_deviceInfo.wSwitchStatus&SS_IN01) g_breaker.m_relayKOT.SetPulse(20);
		}
	}
}

void CMyAppDMRX81P::OnTimer1000ms(void)
{
	CMyAppDMR::OnTimer1000ms();
}

void CMyAppDMRX81P::OnInitDevice(void)
{
	CMyAppDMR::OnInitDevice();
}

void CMyAppDMRX81P::OnResetDevice(void)
{
	CMyAppDMR::OnResetDevice();
	m_alarmgroup1XPT.OnReset();
	m_alarmgroup2XPT.OnReset();
}

void CMyAppDMRX81P::OnUpdateDevice(WORD* pData)
{
	CMyAppDMR::OnUpdateDevice(pData);
}

void CMyAppDMRX81P::OnWaveRecord(WORD wCountAD)
{
	CMyAppDMR::OnWaveRecord(g_deviceInfo.wSwitchStatus,
		g_measure.m_analogWave.wData[DFT_1XUa][wCountAD],
		g_measure.m_analogWave.wData[DFT_1XUb][wCountAD],
		g_measure.m_analogWave.wData[DFT_1XUc][wCountAD],
		g_measure.m_analogWave.wData[DFT_2XUa][wCountAD],
		g_measure.m_analogWave.wData[DFT_2XUb][wCountAD],
		g_measure.m_analogWave.wData[DFT_2XUc][wCountAD],
		g_measure.m_analogWave.wData[DFT_1X3U0][wCountAD],
		g_measure.m_analogWave.wData[DFT_2X3U0][wCountAD]);
}

WORD CMyAppDMRX81P::GetBOStatus(void)
{
	return (g_deviceInfo.wSwitchStatus&SS_IN01)?BOSTATUS_CLOSED:BOSTATUS_OPENED;
}

BOOL CMyAppDMRX81P::Is1XPTBreak(void)
{
	return m_alarmgroup1XPT.IsAlarmStarted();
}

BOOL CMyAppDMRX81P::Is2XPTBreak(void)
{
	return m_alarmgroup2XPT.IsAlarmStarted();
}

void CMyAppDMRX81P::SetBreakerOperateMode(void)
{
	BOOL bEnableAuto = FALSE;
	BOOL bEnableLocal = FALSE;
	BOOL bEnableRemote = FALSE;
	if(m_wLADEnableAuto==BOM_ENABLE||(m_wLADEnableAuto==BOM_NULL&&m_wHardEnableAuto==BOM_ENABLE)) bEnableAuto = TRUE;
	else
	{
		if(m_wLADEnableLocal==BOM_ENABLE||(m_wLADEnableLocal==BOM_NULL&&m_wHardEnableLocal==BOM_ENABLE)) bEnableLocal = TRUE;
		if(m_wLADEnableRemote==BOM_ENABLE||(m_wLADEnableRemote==BOM_NULL&&m_wHardEnableRemote==BOM_ENABLE)) bEnableRemote = TRUE;
	}
	SETBIT(bEnableAuto,g_deviceInfo.wDeviceStatus2,DS2_AutoMode);
	SETBIT(bEnableLocal,g_deviceInfo.wDeviceStatus2,DS2_EnableLocal);
	SETBIT(bEnableRemote,g_deviceInfo.wDeviceStatus2,DS2_EnableRemote);
}

void CMyAppDMRX81P::HardEnableAuto(BOOL bEnable)
{
	m_wHardEnableAuto = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMRX81P::HardEnableLocal(BOOL bEnable)
{
	m_wHardEnableLocal = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMRX81P::HardEnableRemote(BOOL bEnable)
{
	m_wHardEnableRemote = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMRX81P::LADEnableAuto(BOOL bEnable)
{
	m_wLADEnableAuto = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMRX81P::LADEnableLocal(BOOL bEnable)
{
	m_wLADEnableLocal = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMRX81P::LADEnableRemote(BOOL bEnable)
{
	m_wLADEnableRemote = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMRX81P::LADHandClose(void)
{
	m_wLADHandClose = 0xaaaa;
}

void CMyAppDMRX81P::LADHandOpen(void)
{
	m_wLADHandOpen = 0xaaaa;
}

void CMyAppDMRX81P::iiiOnSetDataMetrics(void)
{
	CMyAppDMR::iiiOnSetDataMetrics();
	g_pDeviceParam = (DEVICEPARAM_DMRX81P*)&g_deviceParam.wReserved[0];
	g_data1XUa.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"1#Ua","V");
	g_data1XUb.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"1#Ub","V");
	g_data1XUc.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"1#Uc","V");
	g_data1XUab.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"1#Uab","V");
	g_data1XUbc.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"1#Ubc","V");
	g_data1XUca.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"1#Uca","V");
	g_data1X3U2.SetMetrics(g_pDeviceParam->wScale2Uln,1,"1#3U2","V");
	g_data1X3U0.SetMetrics(g_pDeviceParam->wScale23U0,1,"1#3U0","V");
	g_data1XF.SetMetrics(3000,1,"1#F","Hz");
	g_data2XUa.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"2#Ua","V");
	g_data2XUb.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"2#Ub","V");
	g_data2XUc.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"2#Uc","V");
	g_data2XUab.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"2#Uab","V");
	g_data2XUbc.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"2#Ubc","V");
	g_data2XUca.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"2#Uca","V");
	g_data2X3U2.SetMetrics(g_pDeviceParam->wScale2Uln,1,"2#3U2","V");
	g_data2X3U0.SetMetrics(g_pDeviceParam->wScale23U0,1,"2#3U0","V");
	g_data2XF.SetMetrics(3000,1,"2#F","Hz");
}

void CMyAppDMRX81P::iiiOnCalculateData(void)
{
	CMyAppDMR::iiiOnCalculateData();
	// 硬件通道计算:
	g_measure.SetData(DFT_1XUa,g_data1XUa);
	g_measure.SetData(DFT_1XUb,g_data1XUb);
	g_measure.SetData(DFT_1XUc,g_data1XUc);
	g_measure.SetData(DFT_1X3U0,g_data1X3U0);
	g_measure.SetData(DFT_2XUa,g_data2XUa);
	g_measure.SetData(DFT_2XUb,g_data2XUb);
	g_measure.SetData(DFT_2XUc,g_data2XUc);
	g_measure.SetData(DFT_2X3U0,g_data2X3U0);
	// 软件通道计算:
	g_data1XUab.SetData(g_data1XUa.m_nR-g_data1XUb.m_nR,g_data1XUa.m_nX-g_data1XUb.m_nX);
	g_data1XUbc.SetData(g_data1XUb.m_nR-g_data1XUc.m_nR,g_data1XUb.m_nX-g_data1XUc.m_nX);
	g_data1XUca.SetData(g_data1XUc.m_nR-g_data1XUa.m_nR,g_data1XUc.m_nX-g_data1XUa.m_nX);
	g_data2XUab.SetData(g_data2XUa.m_nR-g_data2XUb.m_nR,g_data2XUa.m_nX-g_data2XUb.m_nX);
	g_data2XUbc.SetData(g_data2XUb.m_nR-g_data2XUc.m_nR,g_data2XUb.m_nX-g_data2XUc.m_nX);
	g_data2XUca.SetData(g_data2XUc.m_nR-g_data2XUa.m_nR,g_data2XUc.m_nX-g_data2XUa.m_nX);
	g_data1X3U2.SetData(g_measure.CalculateNegSeq(&g_data1XUa,&g_data1XUb,&g_data1XUc));
	g_data2X3U2.SetData(g_measure.CalculateNegSeq(&g_data2XUa,&g_data2XUb,&g_data2XUc));
	g_data1XF.SetData(g_hdif.GetFreqINT1());
	g_data2XF.SetData(g_hdif.GetFreqINT2());
	// 谐波计算:
	WORD w1XUa,w1XUb,w1XUc;
	WORD w2XUa,w2XUb,w2XUc;
	m_wTimerTHD++;
	m_wTimerTHD %= 10;
	::CalculateTHDn(m_wTimerTHD+2,DFT_1XUa,DFT_1XUb,DFT_1XUc,&w1XUa,&w1XUb,&w1XUc);
	::CalculateTHDn(m_wTimerTHD+2,DFT_2XUa,DFT_2XUb,DFT_2XUc,&w2XUa,&w2XUb,&w2XUc);
	m_filter1XUa[m_wTimerTHD].AddData((short)w1XUa);
	m_filter1XUb[m_wTimerTHD].AddData((short)w1XUb);
	m_filter1XUc[m_wTimerTHD].AddData((short)w1XUc);
	m_filter2XUa[m_wTimerTHD].AddData((short)w2XUa);
	m_filter2XUb[m_wTimerTHD].AddData((short)w2XUb);
	m_filter2XUc[m_wTimerTHD].AddData((short)w2XUc);
}

void CMyAppDMRX81P::iiiOnRefreshData(void)
{
	CMyAppDMR::iiiOnRefreshData();
	g_analogData.wData1XUa = (WORD)g_data1XUa.RefreshData(FALSE);
	g_analogData.wData1XUb = (WORD)g_data1XUb.RefreshData(FALSE);
	g_analogData.wData1XUc = (WORD)g_data1XUc.RefreshData(FALSE);
	g_analogData.wData1XUab = (WORD)g_data1XUab.RefreshData(FALSE);
	g_analogData.wData1XUbc = (WORD)g_data1XUbc.RefreshData(FALSE);
	g_analogData.wData1XUca = (WORD)g_data1XUca.RefreshData(FALSE);
	g_analogData.wData1X3U2 = (WORD)g_data1X3U2.RefreshData(FALSE);
	g_analogData.wData1X3U0 = (WORD)g_data1X3U0.RefreshData(FALSE);
	g_analogData.wData1XF = (WORD)g_data1XF.RefreshData(FALSE);
	g_analogData.wData2XUa = (WORD)g_data2XUa.RefreshData(FALSE);
	g_analogData.wData2XUb = (WORD)g_data2XUb.RefreshData(FALSE);
	g_analogData.wData2XUc = (WORD)g_data2XUc.RefreshData(FALSE);
	g_analogData.wData2XUab = (WORD)g_data2XUab.RefreshData(FALSE);
	g_analogData.wData2XUbc = (WORD)g_data2XUbc.RefreshData(FALSE);
	g_analogData.wData2XUca = (WORD)g_data2XUca.RefreshData(FALSE);
	g_analogData.wData2X3U2 = (WORD)g_data2X3U2.RefreshData(FALSE);
	g_analogData.wData2X3U0 = (WORD)g_data2X3U0.RefreshData(FALSE);
	g_analogData.wData2XF = (WORD)g_data2XF.RefreshData(FALSE);
	WORD w1XUa,w1XUb,w1XUc;
	WORD w2XUa,w2XUb,w2XUc;
	if(g_pDeviceParam->wModeTHD==0)
	{
		w1XUa = g_analogData.wData1XUa;
		w1XUb = g_analogData.wData1XUb;
		w1XUc = g_analogData.wData1XUc;
		w2XUa = g_analogData.wData2XUa;
		w2XUb = g_analogData.wData2XUb;
		w2XUc = g_analogData.wData2XUc;
	}
	else
	{
		w1XUa = g_analogData.wData1XUab;
		w1XUb = g_analogData.wData1XUbc;
		w1XUc = g_analogData.wData1XUca;
		w2XUa = g_analogData.wData2XUab;
		w2XUb = g_analogData.wData2XUbc;
		w2XUc = g_analogData.wData2XUca;
	}
	for(WORD i=0;i<10;i++)
	{
		*(&g_analogDataExt.ti1XUa.wTHD2+i) = GetTHDPercent((WORD)m_filter1XUa[i].GetData(TRUE),w1XUa);
		*(&g_analogDataExt.ti1XUb.wTHD2+i) = GetTHDPercent((WORD)m_filter1XUb[i].GetData(TRUE),w1XUb);
		*(&g_analogDataExt.ti1XUc.wTHD2+i) = GetTHDPercent((WORD)m_filter1XUc[i].GetData(TRUE),w1XUc);
		*(&g_analogDataExt.ti2XUa.wTHD2+i) = GetTHDPercent((WORD)m_filter2XUa[i].GetData(TRUE),w2XUa);
		*(&g_analogDataExt.ti2XUb.wTHD2+i) = GetTHDPercent((WORD)m_filter2XUb[i].GetData(TRUE),w2XUb);
		*(&g_analogDataExt.ti2XUc.wTHD2+i) = GetTHDPercent((WORD)m_filter2XUc[i].GetData(TRUE),w2XUc);
	}
	CalculateTHD(&g_analogDataExt.ti1XUa);
	CalculateTHD(&g_analogDataExt.ti1XUb);
	CalculateTHD(&g_analogDataExt.ti1XUc);
	CalculateTHD(&g_analogDataExt.ti2XUa);
	CalculateTHD(&g_analogDataExt.ti2XUb);
	CalculateTHD(&g_analogDataExt.ti2XUc);
}

void CMyAppDMRX81P::iiiOnAlarmDetect(void)
{
	CMyAppDMR::iiiOnAlarmDetect();
	m_alarmgroup1XPT.ExeDetect(g_data1XUa,g_data1XUb,g_data1XUc,g_data1XUab,g_data1XUbc,g_data1XUca,g_pDeviceParam->wModePT,100,g_pDeviceParam->wToggleAlarm1XPT,EVENTCODE_ALARM1XPT3);
	m_alarmgroup2XPT.ExeDetect(g_data2XUa,g_data2XUb,g_data2XUc,g_data2XUab,g_data2XUbc,g_data2XUca,g_pDeviceParam->wModePT,100,g_pDeviceParam->wToggleAlarm2XPT,EVENTCODE_ALARM2XPT3);
	SETBIT(m_alarmgroup1XPT.IsAlarmed(),g_deviceInfo.wDeviceStatus2,DS2_Alarm1XPT);
	SETBIT(m_alarmgroup2XPT.IsAlarmed(),g_deviceInfo.wDeviceStatus2,DS2_Alarm2XPT);
}

void CMyAppDMRX81P::iiiOnRelayOut(void)
{
	CMyAppDMR::iiiOnRelayOut();
}


