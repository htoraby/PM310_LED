#include <Main.h>

DEVICEPARAM_UNIT* g_pDeviceParam;
ANALOGDATA g_analogData;
ANALOGDATAEXT g_analogDataExt;
CMyData g_dataIa;
CMyData g_dataIb;
CMyData g_dataIc;
CMyData g_dataIA;
CMyData g_dataIB;
CMyData g_dataIC;
CMyData g_dataUa;
CMyData g_dataUb;
CMyData g_dataUc;
CMyData g_dataUab;
CMyData g_dataUbc;
CMyData g_dataUca;
CMyData g_data3I0;
CMyData g_data3U0;
CMyData g_data3I2;
CMyData g_data3U2;
CMyData g_dataF;
CMyData g_dataP;
CMyData g_dataQ;
CMyData g_dataPF;
CMyData g_dataIx;
CMyData g_dataUxab;
CMyData g_dataUxbc;
CMyData g_dataUxca;
CMyData g_data3Ux2;
CMyData g_dataFx;
CMyBreakerOperate g_breaker;


//-----------------------------------------------------------------------------
void CMyAppDMRUnit::OnInitParams(void)
{
	CMyAppDMR::OnInitParams();
	g_pDeviceParam = (DEVICEPARAM_UNIT*)&g_deviceParam.wReserved[0];
	MemoryClear((WORD*)&g_analogData,SIZEOFWORD(g_analogData));
	MemoryClear((WORD*)&g_analogDataExt,SIZEOFWORD(g_analogDataExt));
	m_bLockStatus = FALSE;
	g_pDeviceParam->wToggleAlarmKM = TOGGLE_ON;
	g_pDeviceParam->wToggleAlarmClose = TOGGLE_ON;
	g_pDeviceParam->wToggleAlarmOpen = TOGGLE_ON;
	g_pDeviceParam->wToggleAlarmCT = TOGGLE_ON;
	g_pDeviceParam->wToggleAlarmPT = TOGGLE_ON;
	g_pDeviceParam->wModeCTM = MODECT_2CT;
	g_pDeviceParam->wModeCTP = MODECT_2CT;
	g_pDeviceParam->wModePT = MODEPT_Y;
	g_pDeviceParam->wScaleCT = 40;
	g_pDeviceParam->wScalePT = 100;
	g_pDeviceParam->wScale2IM = 600;
	g_pDeviceParam->wScale2IP = 10000;
	g_pDeviceParam->wScale2Uln = 10000;
	g_pDeviceParam->wScale23I0 = 600;
	g_pDeviceParam->wScale23U0 = 17320;
	g_pDeviceParam->wScale2Ix = 10000;
	g_pDeviceParam->wScale2Ux = 17320;
#ifndef DFT_3I0
	g_pDeviceParam->wScale23I0 = g_pDeviceParam->wScale2IP;
#endif
#ifndef DFT_3U0
	g_pDeviceParam->wScale23U0 = g_pDeviceParam->wScale2Uln;
#endif
	g_pDeviceParam->wLinkInPE[0] = LINKIN_NULL;
	g_pDeviceParam->wLinkInPE[1] = LINKIN_NULL;
	g_pDeviceParam->wLinkInPE[2] = LINKIN_NULL;
	g_pDeviceParam->wLinkInPE[3] = LINKIN_NULL;
	g_pDeviceParam->wPulsesPerkWh[0] = 1000;
	g_pDeviceParam->wPulsesPerkWh[1] = 1000;
	g_pDeviceParam->wPulsesPerkWh[2] = 1000;
	g_pDeviceParam->wPulsesPerkWh[3] = 1000;
}

void CMyAppDMRUnit::OnInit(void)
{
	CMyAppDMR::OnInit();
	g_arRTC.ReadBlock(0,(WORD*)&g_analogDataExt,SIZEOFWORD(g_analogDataExt));
// 	g_arRTC.ReadBlock(SIZEOFWORD(g_analogDataExt),(WORD*)&m_bLockStatus,SIZEOFWORD(m_bLockStatus));
	g_arRTC.ReadBlock(SIZEOFBYTE(g_analogDataExt)+4,(WORD*)&m_bLockStatus,SIZEOFWORD(m_bLockStatus));
	m_alarmgroupCTM.OnInit();
	m_alarmgroupCTP.OnInit();
	m_alarmgroupPT.OnInit();
	m_wHardEnableLocal = BOM_NULL;
	m_wHardEnableRemote = BOM_NULL;
	m_wLADEnableLocal = BOM_NULL;
	m_wLADEnableRemote = BOM_NULL;
	g_dataIa.OnInit();
	g_dataIb.OnInit();
	g_dataIc.OnInit();
	g_dataIA.OnInit();
	g_dataIB.OnInit();
	g_dataIC.OnInit();
	g_dataUa.OnInit();
	g_dataUb.OnInit();
	g_dataUc.OnInit();
	g_dataUab.OnInit();
	g_dataUbc.OnInit();
	g_dataUca.OnInit();
	g_data3I0.OnInit();
	g_data3U0.OnInit();
	g_data3I2.OnInit();
	g_data3U2.OnInit();
	g_dataF.OnInit();
	g_dataP.OnInit();
	g_dataQ.OnInit();
	g_dataPF.OnInit();
	g_dataIx.OnInit();
	g_dataUxab.OnInit();
	g_dataUxbc.OnInit();
	g_dataUxca.OnInit();
	g_data3Ux2.OnInit();
	g_dataFx.OnInit();
	g_breaker.OnInit();
	g_breaker.m_boinfo = g_analogDataExt.boinfo;
}

void CMyAppDMRUnit::OnTimer1ms(void)
{
	CMyAppDMR::OnTimer1ms();
	g_breaker.OnTimer1ms();
}

void CMyAppDMRUnit::OnTimer10ms(void)
{
	m_wLADEnableLocal = BOM_NULL;
	m_wLADEnableRemote = BOM_NULL;
	g_breaker.m_wLockClose = 0x0000;
	CMyAppDMR::OnTimer10ms();
	WORD wDataIMax = GetMax(g_dataIA.m_nData,g_dataIB.m_nData,g_dataIC.m_nData);
	WORD wDataIMax100mA = (WORD)((g_dataIA.GetValueSecondaryFix(wDataIMax)+5)/10);
	g_breaker.SetDataIMax(wDataIMax,wDataIMax100mA);
	g_breaker.OnTimer10ms();
	SETBIT(g_breaker.m_wLockClose==0xaaaa,g_deviceInfo.wDeviceStatus2,DS2_LockClose);
}

void CMyAppDMRUnit::OnTimer1000ms(void)
{
	CMyAppDMR::OnTimer1000ms();
	g_analogDataExt.boinfo = g_breaker.m_boinfo;
	g_arRTC.WriteBlock(0,(WORD*)&g_analogDataExt,SIZEOFWORD(g_analogDataExt));
// 	g_arRTC.WriteBlock(SIZEOFWORD(g_analogDataExt),(WORD*)&m_bLockStatus,SIZEOFWORD(m_bLockStatus));
	g_arRTC.WriteBlock(SIZEOFBYTE(g_analogDataExt)+4,(WORD*)&m_bLockStatus,SIZEOFWORD(m_bLockStatus));
}

void CMyAppDMRUnit::OnInitDevice(void)
{
	CMyAppDMR::OnInitDevice();
	MemoryClear((WORD*)&g_breaker.m_boinfo,SIZEOFWORD(g_breaker.m_boinfo));
	MemoryClear((WORD*)&g_analogDataExt,SIZEOFWORD(g_analogDataExt));
}

void CMyAppDMRUnit::OnResetDevice(void)
{
	CMyAppDMR::OnResetDevice();
	m_alarmgroupCTM.OnReset();
	m_alarmgroupCTP.OnReset();
	m_alarmgroupPT.OnReset();
	g_breaker.OnReset();
	g_deviceInfo.wDeviceStatus2 &= 0xffff^DS2_ErrorClose;
	g_deviceInfo.wDeviceStatus2 &= 0xffff^DS2_ErrorOpen;
}

void CMyAppDMRUnit::OnUpdateDevice(WORD* pData)
{
#ifndef DFT_3I0
	g_pDeviceParam->wScale23I0 = g_pDeviceParam->wScale2IP;
#endif
#ifndef DFT_3U0
	g_pDeviceParam->wScale23U0 = g_pDeviceParam->wScale2Uln;
#endif
	CMyAppDMR::OnUpdateDevice(pData);
}

WORD CMyAppDMRUnit::GetBOStatus(void)
{
	if(g_deviceInfo.wDeviceStatus1&DS1_ErrorDC) return 0x0000;
	return (g_deviceInfo.wSwitchStatus&SS_IN01)?BOSTATUS_CLOSED:BOSTATUS_OPENED;
}

void CMyAppDMRUnit::SetBOErrorCloseFlag(BOOL bError)
{
	SETBIT(bError,g_deviceInfo.wDeviceStatus2,DS2_ErrorClose);
}

void CMyAppDMRUnit::SetBOErrorOpenFlag(BOOL bError)
{
	SETBIT(bError,g_deviceInfo.wDeviceStatus2,DS2_ErrorOpen);
}

BOOL CMyAppDMRUnit::IsCTMBreak(void)
{
	return m_alarmgroupCTM.IsAlarmStarted();
}

BOOL CMyAppDMRUnit::IsCTPBreak(void)
{
	return m_alarmgroupCTP.IsAlarmStarted();
}

BOOL CMyAppDMRUnit::IsPTBreak(void)
{
	return m_alarmgroupPT.IsAlarmStarted();
}

void CMyAppDMRUnit::SetBreakerOperateMode(void)
{
	BOOL bEnableLocal = FALSE;
	BOOL bEnableRemote = FALSE;
	if(m_wLADEnableLocal==BOM_ENABLE||(m_wLADEnableLocal==BOM_NULL&&m_wHardEnableLocal==BOM_ENABLE)) bEnableLocal = TRUE;
	if(m_wLADEnableRemote==BOM_ENABLE||(m_wLADEnableRemote==BOM_NULL&&m_wHardEnableRemote==BOM_ENABLE)) bEnableRemote = TRUE;
	SETBIT(bEnableLocal,g_deviceInfo.wDeviceStatus2,DS2_EnableLocal);
	SETBIT(bEnableRemote,g_deviceInfo.wDeviceStatus2,DS2_EnableRemote);
}

void CMyAppDMRUnit::HardEnableLocal(BOOL bEnable)
{
	m_wHardEnableLocal = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMRUnit::HardEnableRemote(BOOL bEnable)
{
	m_wHardEnableRemote = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMRUnit::LADEnableLocal(BOOL bEnable)
{
	m_wLADEnableLocal = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMRUnit::LADEnableRemote(BOOL bEnable)
{
	m_wLADEnableRemote = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMRUnit::CalculatePE(WORD wIndex)
{
	if(g_pDeviceParam->wLinkInPE[wIndex]!=LINKIN_NULL)
	{
		g_analogDataExt.wDataPE[wIndex] += 1000*g_switch[g_pDeviceParam->wLinkInPE[wIndex]-1].GetCountON();
		WORD wPulsePerkWh = g_pDeviceParam->wPulsesPerkWh[wIndex];
		if(wPulsePerkWh==0) return;
		g_analogDataExt.dwDataPE[wIndex] += g_analogDataExt.wDataPE[wIndex]/wPulsePerkWh;
		g_analogDataExt.wDataPE[wIndex] %= wPulsePerkWh;
	}
}

void CMyAppDMRUnit::iiiOnSetDataMetrics(void)
{
	CMyAppDMR::iiiOnSetDataMetrics();
	g_pDeviceParam = (DEVICEPARAM_UNIT*)&g_deviceParam.wReserved[0];
	DWORD dwScaleSecondary = (DWORD)g_pDeviceParam->wScale2IM*(DWORD)g_pDeviceParam->wScale2Uln*3/100;
	DWORD dwScale = (DWORD)g_pDeviceParam->wScaleCT*(DWORD)g_pDeviceParam->wScalePT;
	g_dataIa.SetMetrics(g_pDeviceParam->wScale2IM,g_pDeviceParam->wScaleCT,"Ia","A");
	g_dataIb.SetMetrics(g_pDeviceParam->wScale2IM,g_pDeviceParam->wScaleCT,"Ib","A");
	g_dataIc.SetMetrics(g_pDeviceParam->wScale2IM,g_pDeviceParam->wScaleCT,"Ic","A");
	g_dataIA.SetMetrics(g_pDeviceParam->wScale2IP,g_pDeviceParam->wScaleCT,"IA","A");
	g_dataIB.SetMetrics(g_pDeviceParam->wScale2IP,g_pDeviceParam->wScaleCT,"IB","A");
	g_dataIC.SetMetrics(g_pDeviceParam->wScale2IP,g_pDeviceParam->wScaleCT,"IC","A");
	g_dataUa.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Ua","V");
	g_dataUb.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Ub","V");
	g_dataUc.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Uc","V");
	g_dataUab.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Uab","V");
	g_dataUbc.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Ubc","V");
	g_dataUca.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Uca","V");
	g_data3I2.SetMetrics(g_pDeviceParam->wScale2IP,1,"3I2","A");
	g_data3U2.SetMetrics(g_pDeviceParam->wScale2Uln,1,"3U2","V");
	g_data3I0.SetMetrics(g_pDeviceParam->wScale23I0,1,"3I0","A");
	g_data3U0.SetMetrics(g_pDeviceParam->wScale23U0,1,"3U0","V");
	g_dataF.SetMetrics(3000,1,"F","Hz");
	g_dataP.SetMetrics(dwScaleSecondary,dwScale,"P","W");
	g_dataQ.SetMetrics(dwScaleSecondary,dwScale,"Q","Var");
	g_dataPF.SetMetrics(3000,1,"PF","%");
	g_dataIx.SetMetrics(g_pDeviceParam->wScale2Ix,1,"Ix","A");
	g_dataUxab.SetMetrics(g_pDeviceParam->wScale2Ux,1,"Uxab","V");
	g_dataUxbc.SetMetrics(g_pDeviceParam->wScale2Ux,1,"Uxbc","V");
	g_dataUxca.SetMetrics(g_pDeviceParam->wScale2Ux,1,"Uxca","V");
	g_data3Ux2.SetMetrics(g_pDeviceParam->wScale2Ux,1,"3Ux2","V");
	g_dataFx.SetMetrics(3000,1,"Fx","Hz");
}

void CMyAppDMRUnit::iiiOnCalculateData(void)
{
	CMyAppDMR::iiiOnCalculateData();
	// 硬件通道计算:
#ifdef DFT_IA
	g_measure.SetData(DFT_IA,g_dataIA);
#endif
#ifdef DFT_IB
	g_measure.SetData(DFT_IB,g_dataIB);
#endif
#ifdef DFT_IC
	g_measure.SetData(DFT_IC,g_dataIC);
#endif
#ifdef DFT_Ia
	g_measure.SetData(DFT_Ia,g_dataIa);
#else
	short nRa = short(long(g_dataIA.m_nR)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	short nXa = short(long(g_dataIA.m_nX)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	short nAa = short(long(g_dataIA.m_nData)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	g_dataIa.SetData(nRa,nXa,nAa);
#endif
#ifdef DFT_Ib
	g_measure.SetData(DFT_Ib,g_dataIb);
#endif
#ifdef DFT_Ic
	g_measure.SetData(DFT_Ic,g_dataIc);
#else
	short nRc = short(long(g_dataIC.m_nR)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	short nXc = short(long(g_dataIC.m_nX)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	short nAc = short(long(g_dataIC.m_nData)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	g_dataIc.SetData(nRc,nXc,nAc);
#endif
#ifdef DFT_Ua
	g_measure.SetData(DFT_Ua,g_dataUa);
#endif
#ifdef DFT_Ub
	g_measure.SetData(DFT_Ub,g_dataUb);
#endif
#ifdef DFT_Uc
	g_measure.SetData(DFT_Uc,g_dataUc);
#endif
#ifdef DFT_3I0
	g_measure.SetData(DFT_3I0,g_data3I0);
#endif
#ifdef DFT_3U0
	g_measure.SetData(DFT_3U0,g_data3U0);
#endif
#ifdef DFT_Ix
	g_measure.SetData(DFT_Ix,g_dataIx);
#endif
#ifdef DFT_Uxab
	g_measure.SetData(DFT_Uxab,g_dataUxab);
#endif
#ifdef DFT_Uxbc
	g_measure.SetData(DFT_Uxbc,g_dataUxbc);
#endif
	// 软件通道计算:
#ifndef DFT_Ib
	g_dataIb.SetData(-(g_dataIa.m_nR+g_dataIc.m_nR),-(g_dataIa.m_nX+g_dataIc.m_nX));
#endif
	g_dataUab.SetData(g_dataUa.m_nR-g_dataUb.m_nR,g_dataUa.m_nX-g_dataUb.m_nX);
	g_dataUbc.SetData(g_dataUb.m_nR-g_dataUc.m_nR,g_dataUb.m_nX-g_dataUc.m_nX);
	g_dataUca.SetData(g_dataUc.m_nR-g_dataUa.m_nR,g_dataUc.m_nX-g_dataUa.m_nX);
#ifndef DFT_3I0
	g_data3I0.SetData(g_dataIA.m_nR+g_dataIB.m_nR+g_dataIC.m_nR,g_dataIA.m_nX+g_dataIB.m_nX+g_dataIC.m_nX);
#endif
#ifndef DFT_3U0
	g_data3U0.SetData(g_dataUa.m_nR+g_dataUb.m_nR+g_dataUc.m_nR,g_dataUa.m_nX+g_dataUb.m_nX+g_dataUc.m_nX);
#endif
	g_data3I2.SetData(CMyMeasure::CalculateNegSeq(&g_dataIA,(g_pDeviceParam->wModeCTP==MODECT_2CT)?NULL:&g_dataIB,&g_dataIC));
	g_data3U2.SetData(CMyMeasure::CalculateNegSeq(&g_dataUa,&g_dataUb,&g_dataUc));
	g_dataUxca.SetData(-(g_dataUxab.m_nR+g_dataUxbc.m_nR),-(g_dataUxab.m_nX+g_dataUxbc.m_nX));
	WORD wData3Ux2 = CMyMeasure::CalculateNegSeq(&g_dataUxab,&g_dataUxbc,&g_dataUxca);
	g_data3Ux2.SetData((WORD)(((DWORD)wData3Ux2*1000L+1732)/1732L));
	g_dataF.SetData(g_hdif.GetFreqINT1());
	g_dataFx.SetData(g_hdif.GetFreqINT2());
	// 功率电度计算:
	CMyPQPhQh pqphqh;
	pqphqh.Calculate(&g_dataIa,&g_dataIb,&g_dataIc,&g_dataUa,&g_dataUb,&g_dataUc,g_pDeviceParam->wScale2IM,g_pDeviceParam->wScale2Uln,FALSE);
	g_dataP.SetData(pqphqh.m_nPabc);
	g_dataQ.SetData(pqphqh.m_nQabc);
	g_dataPF.SetData(pqphqh.m_nPFabc);
	SETBIT(g_dataP.m_nData<0,g_deviceInfo.wDeviceStatus2,DS2_DirectP);
	SETBIT(g_dataQ.m_nData<0,g_deviceInfo.wDeviceStatus2,DS2_DirectQ);
	g_analogDataExt.dwDataPhImpW10ms += pqphqh.m_dwPhImpW10ms;
	g_analogDataExt.dwDataQhImpW10ms += pqphqh.m_dwQhImpW10ms;
	g_analogDataExt.dwDataPhExpW10ms += pqphqh.m_dwPhExpW10ms;
	g_analogDataExt.dwDataQhExpW10ms += pqphqh.m_dwQhExpW10ms;
	if(g_analogDataExt.dwDataPhImpW10ms>=36000000L)
	{
		g_analogDataExt.dwDataPhImp++;
		g_analogDataExt.dwDataPhImpW10ms -= 36000000L;
	}
	if(g_analogDataExt.dwDataQhImpW10ms>=36000000L)
	{
		g_analogDataExt.dwDataQhImp++;
		g_analogDataExt.dwDataQhImpW10ms -= 36000000L;
	}
	if(g_analogDataExt.dwDataPhExpW10ms>=36000000L)
	{
		g_analogDataExt.dwDataPhExp++;
		g_analogDataExt.dwDataPhExpW10ms -= 36000000L;
	}
	if(g_analogDataExt.dwDataQhExpW10ms>=36000000L)
	{
		g_analogDataExt.dwDataQhExp++;
		g_analogDataExt.dwDataQhExpW10ms -= 36000000L;
	}
	CalculatePE(0);
	CalculatePE(1);
	CalculatePE(2);
	CalculatePE(3);
}

void CMyAppDMRUnit::iiiOnRefreshData(void)
{
	CMyAppDMR::iiiOnRefreshData();
	g_analogData.wDataIa = (WORD)g_dataIa.RefreshData(FALSE);
	g_analogData.wDataIb = (WORD)g_dataIb.RefreshData(FALSE);
	g_analogData.wDataIc = (WORD)g_dataIc.RefreshData(FALSE);
	g_analogData.wDataIA = (WORD)g_dataIA.RefreshData(FALSE);
	g_analogData.wDataIB = (WORD)g_dataIB.RefreshData(FALSE);
	g_analogData.wDataIC = (WORD)g_dataIC.RefreshData(FALSE);
	g_analogData.wDataUa = (WORD)g_dataUa.RefreshData(FALSE);
	g_analogData.wDataUb = (WORD)g_dataUb.RefreshData(FALSE);
	g_analogData.wDataUc = (WORD)g_dataUc.RefreshData(FALSE);
	g_analogData.wDataUab = (WORD)g_dataUab.RefreshData(FALSE);
	g_analogData.wDataUbc = (WORD)g_dataUbc.RefreshData(FALSE);
	g_analogData.wDataUca = (WORD)g_dataUca.RefreshData(FALSE);
	g_analogData.wData3I2 = (WORD)g_data3I2.RefreshData(FALSE);
	g_analogData.wData3U2 = (WORD)g_data3U2.RefreshData(FALSE);
	g_analogData.wData3I0 = (WORD)g_data3I0.RefreshData(FALSE);
	g_analogData.wData3U0 = (WORD)g_data3U0.RefreshData(FALSE);
	g_analogData.wDataF = (WORD)g_dataF.RefreshData(FALSE);
	g_analogData.nDataP = g_dataP.RefreshData(TRUE);
	g_analogData.nDataQ = g_dataQ.RefreshData(TRUE);
	g_analogData.nDataPF = g_dataPF.RefreshData(TRUE);
	g_analogData.wDataIx = (WORD)g_dataIx.RefreshData(FALSE);
	g_analogData.wDataUxab = (WORD)g_dataUxab.RefreshData(FALSE);
	g_analogData.wDataUxbc = (WORD)g_dataUxbc.RefreshData(FALSE);
	g_analogData.wDataUxca = (WORD)g_dataUxca.RefreshData(FALSE);
	g_analogData.wData3Ux2 = (WORD)g_data3Ux2.RefreshData(FALSE);
	g_analogData.wDataFx = (WORD)g_dataFx.RefreshData(FALSE);
}

void CMyAppDMRUnit::iiiOnAlarmDetect(void)
{
	CMyAppDMR::iiiOnAlarmDetect();
#ifdef ALARM_CTM
	m_alarmgroupCTM.ExeDetect(g_dataIa,g_dataIb,g_dataIc,g_pDeviceParam->wModeCTM,g_pDeviceParam->wToggleAlarmCT,EVENTCODE_ALARMCTMA);
#endif
#ifdef ALARM_CTP
	m_alarmgroupCTP.ExeDetect(g_dataIA,g_dataIB,g_dataIC,g_pDeviceParam->wModeCTP,g_pDeviceParam->wToggleAlarmCT,EVENTCODE_ALARMCTPA);
#endif
#ifdef ALARM_PT
	WORD wDataIMax = GetMax(g_dataIA.m_nData,g_dataIB.m_nData,g_dataIC.m_nData);
	m_alarmgroupPT.ExeDetect(g_dataUa,g_dataUb,g_dataUc,g_dataUab,g_dataUbc,g_dataUca,g_pDeviceParam->wModePT,wDataIMax,g_pDeviceParam->wToggleAlarmPT,EVENTCODE_ALARMPT3);
#endif
	SETBIT(m_alarmgroupCTM.IsAlarmed(),g_deviceInfo.wDeviceStatus2,DS2_AlarmCTM);
	SETBIT(m_alarmgroupCTP.IsAlarmed(),g_deviceInfo.wDeviceStatus2,DS2_AlarmCTP);
	SETBIT(m_alarmgroupPT.IsAlarmed(),g_deviceInfo.wDeviceStatus2,DS2_AlarmPT);
	g_breaker.ExeDetect(g_pDeviceParam->wToggleAlarmKM,g_pDeviceParam->wToggleAlarmClose,g_pDeviceParam->wToggleAlarmOpen);
	SETBIT(g_breaker.IsAlarmedKM(),g_deviceInfo.wDeviceStatus2,DS2_AlarmKM);
	SETBIT(g_breaker.IsAlarmedClose(),g_deviceInfo.wDeviceStatus2,DS2_AlarmClose);
	SETBIT(g_breaker.IsAlarmedOpen(),g_deviceInfo.wDeviceStatus2,DS2_AlarmOpen);
}

void CMyAppDMRUnit::iiiOnRelayOut(void)
{
	CMyAppDMR::iiiOnRelayOut();
	g_breaker.m_lockProtect.Unlock1();
	g_breaker.m_lockProtect.Unlock2();
	if(g_protect.m_wProtectOpenFlag==0xaaaa)
	{
		g_breaker.m_lockProtect.Unlock3();
		g_breaker.ExecuteOpen(BOMODE_PROTECT);
		g_breaker.m_lockProtect.Lock3();
	}
	else if(g_protect.m_wProtectCloseFlag==0xaaaa)
	{
		g_breaker.m_lockProtect.Unlock3();
		g_breaker.ExecuteClose(BOMODE_PROTECT);
		g_breaker.m_lockProtect.Lock3();
	}
	g_breaker.m_lockProtect.Lock2();
	g_breaker.m_lockProtect.Lock1();

	if(g_breaker.m_wCountAfterTripped>457)
	{
		g_relayKH[2].SetPulse(KPUTIME);
	}
}

