#include <Main.h>


//-----------------------------------------------------------------------------
void CMyAppiBCU24X::OnInitParams(void)
{
	CMyAppiBCU::OnInitParams();
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 0],EVENTTYPE_SWITCH,"��·��λ��","��λ","��λ");
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 1],EVENTTYPE_RUNINFO,"�ֳ�����λ��","�ǹ���","����");
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 2],EVENTTYPE_RUNINFO,"�ֳ�����λ��","������","����");
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 3],EVENTTYPE_RUNINFO,"�ӵص�λ��","��λ","��λ");
	CMySwitch::SetInParam(&g_inparamTable.inparam[ 4],EVENTTYPE_RUNINFO,"���ɴ���״̬","����","δ����");
}

void CMyAppiBCU24X::OnTimer10ms(void)
{
	g_protect.m_piBZT.SetCloseRelay(&g_relayKH[2]);
	CMyAppiBCU::OnTimer10ms();
	BOOL bLightCHZ = FALSE;
	WORD wChargeStatusCHZ = g_protect.m_piCHZ.GetChargeStatus();
	if(wChargeStatusCHZ==1) bLightCHZ = g_time.IsFlashing();
	else if(wChargeStatusCHZ==2) bLightCHZ = TRUE;
	SETBIT(bLightCHZ,g_deviceInfo.wDeviceStatus2,DS2_ChargedCHZ);
	SETBIT(g_protect.GetMotorStartTime(),g_deviceInfo.wDeviceStatus2,DS2_MotorStart);
	SETBIT(g_protect.m_piGR.GetPercentGR()>=50,g_deviceInfo.wDeviceStatus3,DS3_GR50);
	SETBIT(g_protect.m_piGR.GetPercentGR()>=75,g_deviceInfo.wDeviceStatus3,DS3_GR75);
}

void CMyAppiBCU24X::OnWaveRecord(WORD wCountAD)
{
	WORD wData3I0 = 2000;
#ifndef DFT_3I0
	if(g_pDeviceParam->wScale23I0>800)
	{
	#ifdef DFT_3I0B
		wData3I0 = g_measure.m_analogWave.wData[DFT_3I0B][wCountAD];
	#endif
	}
	else
	{
	#ifdef DFT_3I0S
		wData3I0 = g_measure.m_analogWave.wData[DFT_3I0S][wCountAD];
	#endif
	}
#else
	wData3I0 = g_measure.m_analogWave.wData[DFT_3I0][wCountAD];
#endif
	CMyAppDMR::OnWaveRecord(g_deviceInfo.wSwitchStatus,
		g_measure.m_analogWave.wData[DFT_IA][wCountAD],
// 		g_measure.m_analogWave.wData[DFT_IB][wCountAD],
		g_measure.m_analogWave.wData[DFT_IC][wCountAD],
		g_measure.m_analogWave.wData[DFT_Ia][wCountAD],
		g_measure.m_analogWave.wData[DFT_Ic][wCountAD],
		wData3I0,
		g_measure.m_analogWave.wData[DFT_Ua][wCountAD],
		g_measure.m_analogWave.wData[DFT_Ub][wCountAD],
		g_measure.m_analogWave.wData[DFT_Uc][wCountAD]
		);
}

void CMyAppiBCU24X::OnUpdateDevice(WORD* pData)
{
	g_pDeviceParam->wModeCTM = g_pDeviceParam->wModeCTP;		// ����CTģʽ�뱣��CTģʽһ���޸�
	CMyAppiBCU::OnUpdateDevice(pData);
}
