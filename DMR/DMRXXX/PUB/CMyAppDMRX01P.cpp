#include <Main.h>


//-----------------------------------------------------------------------------
void CMyAppDMRX01P::OnInitParams(void)
{
	CMyAppDMRUnit::OnInitParams();
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 0],EVENTTYPE_SWITCH,"断路器位置","分位","合位");
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 1],EVENTTYPE_RUNINFO,"手车工作位置","非工作","工作");
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 2],EVENTTYPE_RUNINFO,"手车试验位置","非试验","试验");
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 3],EVENTTYPE_RUNINFO,"接地刀位置","分位","合位");
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 4],EVENTTYPE_RUNINFO,"弹簧储能状态","储能","未储能");
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 8],EVENTTYPE_ALARMED,"高温信号","正常","告警");
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 9],EVENTTYPE_TRIPPED,"超温信号","正常","故障");
	CMySwitch::SetInParam(&g_inparamTable.inparam[10],EVENTTYPE_ALARMED,"轻瓦斯信号","正常","告警");
	CMySwitch::SetInParam(&g_inparamTable.inparam[11],EVENTTYPE_TRIPPED,"重瓦斯信号","正常","故障");
}

void CMyAppDMRX01P::OnTimer10ms(void)
{
	g_protect.m_piBZT.SetCloseRelay(&g_relayKH[2]);
	CMyAppDMRUnit::OnTimer10ms();
	BOOL bLightCHZ = FALSE;
	WORD wChargeStatusCHZ = g_protect.m_piCHZ.GetChargeStatus();
	if(wChargeStatusCHZ==1) bLightCHZ = g_time.IsFlashing();
	else if(wChargeStatusCHZ==2) bLightCHZ = TRUE;
	BOOL bLightBZT = FALSE;
	WORD wChargeStatusBZT = g_protect.m_piBZT.GetChargeStatus();
	if(wChargeStatusBZT==1) bLightBZT = g_time.IsFlashing();
	else if(wChargeStatusBZT==2) bLightBZT = TRUE;
	SETBIT(bLightCHZ,g_deviceInfo.wDeviceStatus2,DS2_ChargedCHZ);
	SETBIT(bLightBZT,g_deviceInfo.wDeviceStatus2,DS2_ChargedBZT);
	SETBIT(g_protect.GetMotorStartTime(),g_deviceInfo.wDeviceStatus2,DS2_MotorStart);
	SETBIT(g_protect.m_piGR.GetPercentGR()>=50,g_deviceInfo.wDeviceStatus3,DS3_GR50);
	SETBIT(g_protect.m_piGR.GetPercentGR()>=75,g_deviceInfo.wDeviceStatus3,DS3_GR75);
}

void CMyAppDMRX01P::OnWaveRecord(WORD wCountAD)
{
	WORD wData3I0 = 2000;
#ifdef DFT_3I0
	wData3I0 = g_measure.m_analogWave.wData[DFT_3I0][wCountAD];
#endif
	CMyAppDMR::OnWaveRecord(g_deviceInfo.wSwitchStatus,
		g_measure.m_analogWave.wData[DFT_IA][wCountAD],
		g_measure.m_analogWave.wData[DFT_IB][wCountAD],
		g_measure.m_analogWave.wData[DFT_IC][wCountAD],
		g_measure.m_analogWave.wData[DFT_Ua][wCountAD],
		g_measure.m_analogWave.wData[DFT_Ub][wCountAD],
		g_measure.m_analogWave.wData[DFT_Uc][wCountAD],
		wData3I0,
		g_measure.m_analogWave.wData[DFT_Ix][wCountAD]);
}
