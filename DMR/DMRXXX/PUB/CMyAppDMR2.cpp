 #include <Main.h>

DEVICEINFO g_deviceInfo;
DEVICEPARAM g_deviceParam;
INPARAMTABLE g_inparamTable;
CMyTime g_time;
CMyMeasure g_measure;
CMyEventTable g_eventTable;
CMyWaveRecord g_waveRecord;
CMySwitch g_switch[SWITCH_COUNT];
CMyOutput g_relayKH[RELAYKH_COUNT];
CMyOutput g_relayKPU;

WORD g_wSwitchStep = 0;


//-----------------------------------------------------------------------------
WORD CMyAppDMR::GetCountAll(void)
{
	g_deviceInfo.wCountEventTable = g_eventTable.m_wCountNew;
	g_deviceInfo.wCountWaveRecord = g_waveRecord.m_wCountNew;
	g_deviceInfo.wCountDeviceParam = m_devicesetParam.m_wCountNew;
	g_deviceInfo.wCountDeviceInParam = m_devicesetInParam.m_wCountNew;
	g_deviceInfo.wCountDeviceRegulate = m_devicesetRegulate.m_wCountNew;
	g_deviceInfo.wCountDeviceSetpoint = m_devicesetSetpoint.m_wCountNew;
	g_deviceInfo.wCountDeviceDRW = m_devicesetDRW.m_wCountNew;
	g_deviceInfo.wCountDeviceLAD = m_devicesetLAD.m_wCountNew;
	WORD wCountAll = 0;
	wCountAll += g_deviceInfo.wCountEventTable;
	wCountAll += g_deviceInfo.wCountWaveRecord;
	wCountAll += g_deviceInfo.wCountDeviceParam;
	wCountAll += g_deviceInfo.wCountDeviceInParam;
	wCountAll += g_deviceInfo.wCountDeviceRegulate;
	wCountAll += g_deviceInfo.wCountDeviceSetpoint;
	wCountAll += g_deviceInfo.wCountDeviceDRW;
	wCountAll += g_deviceInfo.wCountDeviceLAD;
	return wCountAll;
}

void CMyAppDMR::SetAllDeviceSets(void)
{
	m_devicesetParam.SetDeviceSet((WORD*)&g_deviceParam,SIZEOFBYTE(g_deviceParam)>>1,DS1_ErrorParam,EEPROMADDR_DeviceParam);
	m_devicesetInParam.SetDeviceSet((WORD*)&g_inparamTable,SIZEOFBYTE(g_inparamTable)>>1,DS1_ErrorInParam,EEPROMADDR_DeviceInParam);
	m_devicesetRegulate.SetDeviceSet((WORD*)&g_measure.m_regulateSet,SIZEOFBYTE(g_measure.m_regulateSet)>>1,DS1_ErrorRegulate,EEPROMADDR_DeviceRegulate);
	m_devicesetSetpoint.SetDeviceSet((WORD*)&g_deviceSetpoint,SIZEOFBYTE(g_deviceSetpoint)>>1,DS1_ErrorSetpoint,EEPROMADDR_DeviceSetpoint);
#ifdef MODULE__DRW_H
	m_devicesetDRW.SetDeviceSet((WORD*)&g_deviceDRW,SIZEOFBYTE(g_deviceDRW)>>1,DS1_ErrorDRW,EEPROMADDR_DeviceDRW);
#endif
#ifdef MODULE__LAD_H
	m_devicesetLAD.SetDeviceSet((WORD*)&g_deviceLAD,SIZEOFBYTE(g_deviceLAD)>>1,DS1_ErrorLAD,EEPROMADDR_DeviceLAD);
#endif
}

void CMyAppDMR::InitAllDeviceSets(void)
{
	m_devicesetParam.InitDeviceSet();
	m_devicesetInParam.InitDeviceSet();
	m_devicesetRegulate.InitDeviceSet();
	m_devicesetSetpoint.InitDeviceSet();
#ifdef MODULE__DRW_H
	m_devicesetDRW.InitDeviceSet();
#endif
#ifdef MODULE__LAD_H
	m_devicesetLAD.InitDeviceSet();
#endif
}

void CMyAppDMR::CheckAllDeviceSets(void)
{
	m_devicesetParam.CheckDeviceSet();
	m_devicesetInParam.CheckDeviceSet();
	m_devicesetRegulate.CheckDeviceSet();
	m_devicesetSetpoint.CheckDeviceSet();
#ifdef MODULE__DRW_H
	m_devicesetDRW.CheckDeviceSet();
#endif
#ifdef MODULE__LAD_H
	m_devicesetLAD.CheckDeviceSet();
#endif
}

void CMyAppDMR::UpdateAllDeviceSets(void)
{
	m_devicesetParam.UpdateDeviceSet();
	m_devicesetInParam.UpdateDeviceSet();
	m_devicesetRegulate.UpdateDeviceSet();
	m_devicesetSetpoint.UpdateDeviceSet();
#ifdef MODULE__DRW_H
	m_devicesetDRW.UpdateDeviceSet();
#endif
#ifdef MODULE__LAD_H
	m_devicesetLAD.UpdateDeviceSet();
#endif
}

void CMyAppDMR::OnUpdateAllDeviceSet(WORD* pData)
{
// 	if(m_devicesetParam.OnUpdateDevice(pData)) g_DM9KTest.SetStatus(ETSTATUS_SWREST);
	m_devicesetParam.OnUpdateDevice(pData);
	m_devicesetInParam.OnUpdateDevice(pData);
	m_devicesetRegulate.OnUpdateDevice(pData);
	if(m_devicesetSetpoint.OnUpdateDevice(pData)) g_protect.OnInit();
#ifdef MODULE__DRW_H
	m_devicesetDRW.OnUpdateDevice(pData);
#endif
#ifdef MODULE__LAD_H
	if(m_devicesetLAD.OnUpdateDevice(pData)) g_lad.OnInit();
#endif
}


//-----------------------------------------------------------------------------
void CMyAppDMR::OnInitParams(void)
{
	WORD i;
	MemoryClear((WORD*)&g_deviceInfo,SIZEOFWORD(g_deviceInfo));
	MemoryClear((WORD*)&g_deviceParam,SIZEOFWORD(g_deviceParam));
	MemoryClear((WORD*)&g_inparamTable,SIZEOFWORD(g_inparamTable));
	MemoryClear((WORD*)&g_deviceSetpoint,SIZEOFWORD(g_deviceSetpoint));
#ifdef MODULE__DRW_H
	MemoryClear((WORD*)&g_deviceDRW,SIZEOFWORD(g_deviceDRW));
#endif
#ifdef MODULE__LAD_H
	MemoryClear((WORD*)&g_deviceLAD,SIZEOFWORD(g_deviceLAD));
#endif
	g_deviceParam.wSubDeviceType = 0x0000;
	g_deviceParam.wPassword1 = 1111;
	g_deviceParam.wPassword2 = 2222;
	g_deviceParam.wLCDContrast = 8;
	g_deviceParam.wCommAddress = 1;
	g_deviceParam.wSCIBaudRate = BAUDRATE_38400;
	g_deviceParam.wCANBaudRate = BAUDRATE_500k;
	g_deviceParam.wLinkOutAlarmed = LINKOUT_KH02;
	g_deviceParam.wLinkOutTripped = LINKOUT_KH01;
	g_deviceParam.wLinkOutErrored = LINKOUT_KH03;
	g_deviceParam.wMultiLanguage = 0;
	CopyCharToWSZ(g_deviceParam.wszDeviceType,(char*)DEVICETYPE_NAME);
	for(i=0;i<SWITCH_COUNT;i++) CMySwitch::SetInParam(&g_inparamTable.inparam[i],EVENTTYPE_NULL,"±¸ÓÃ","0","1");
	g_measure.OnInitParams();
	g_protect.OnInitSetpoint(&g_deviceSetpoint.wSetpointArea1[0]);
	g_protect.OnInitSetpoint(&g_deviceSetpoint.wSetpointArea2[0]);
	g_protect.OnInitSetpoint(&g_deviceSetpoint.wSetpointArea3[0]);
}

void CMyAppDMR::OnInit(void)
{
	WORD i;
	SetAllDeviceSets();
	InitAllDeviceSets();
#ifdef _WIN32
	m_devicesetParam.ForceUpdateDeviceSet();
	m_devicesetInParam.ForceUpdateDeviceSet();
	m_devicesetRegulate.ForceUpdateDeviceSet();
	m_devicesetSetpoint.ForceUpdateDeviceSet();
#ifdef MODULE__DRW_H
	m_devicesetDRW.ForceUpdateDeviceSet();
#endif
#ifdef MODULE__LAD_H
	m_devicesetLAD.ForceUpdateDeviceSet();
#endif
#endif
	g_deviceInfo.wSwitchStatus = 0;
	g_deviceInfo.wSwitchStatus2 = 0;
	g_deviceInfo.wDeviceStatus1 = 0;
	g_deviceInfo.wDeviceStatus2 = 0;
	g_deviceInfo.wDeviceStatus3 = 0;

	g_time.OnInit();
	g_eventTable.OnInit();
	g_waveRecord.OnInit();
	for(i=0;i<SWITCH_COUNT;i++) g_switch[i].OnInit();
	for(i=0;i<RELAYKH_COUNT;i++) g_relayKH[i].OnInit();
#ifdef KPU
	g_relayKPU.OnInit();
#endif
	g_measure.OnInit();
	g_protect.OnInit();
#ifdef MODULE__LAD_H
	g_lad.OnInit();
#endif
	g_app.iiiOnSetDataMetrics();
	g_waveRecord.StartRecord();
	g_deviceInfo.wCountAll = GetCountAll();
	m_wCountAllOld = g_deviceInfo.wCountAll;
	g_wSwitchStep = 0;
}

void CMyAppDMR::OnTimer1ms(void)
{
	g_time.OnTimer1ms();

#if (SWITCH_COUNT<12)
	WORD wSwitchStatus1 = 0x0000;
	WORD wSwitchStatus2 = 0x0000;
	for(WORD i=0;i<SWITCH_COUNT;i++)
	{
		g_switch[i].OnTimer1ms(i,&g_inparamTable.inparam[i]);
		if(g_switch[i].GetStatus()==STATUS_ON) wSwitchStatus1 |= (SS_IN01<<i);
	}
	g_deviceInfo.wSwitchStatus = wSwitchStatus1;
	g_deviceInfo.wSwitchStatus2 = wSwitchStatus2;
#else
	if(g_wSwitchStep%2==0)
	{
		for(WORD i=0;i<8;i++)
		{
			g_switch[i].OnTimer1ms(i,&g_inparamTable.inparam[i]);
			if(g_switch[i].GetStatus()==STATUS_ON) g_deviceInfo.wSwitchStatus |= (SS_IN01<<i);
			else g_deviceInfo.wSwitchStatus &= (SS_IN01<<i)^0xffff;
		}
	}
	else if(g_wSwitchStep%2==1)
	{
		for(WORD i=8;i<SWITCH_COUNT;i++)
		{
			g_switch[i].OnTimer1ms(i,&g_inparamTable.inparam[i]);
			if(g_switch[i].GetStatus()==STATUS_ON) g_deviceInfo.wSwitchStatus |= (SS_IN01<<i);
			else g_deviceInfo.wSwitchStatus &= (SS_IN01<<i)^0xffff;
		}
	}
#endif
	g_wSwitchStep++;
}

void CMyAppDMR::OnTimer10ms(void)
{
	g_deviceInfo.wDeviceType = DEVICETYPE_CODE;

// ================for debug===============
// 	g_deviceInfo.wDeviceType = 12400;
// ========================================

	g_deviceInfo.wSoftVersion = MAIN_VERSION + SUB_VERSION;
	CMyData::s_bAddFilter = !CMyData::s_bAddFilter;
	g_measure.OnTimer10ms();
	g_app.iiiOnCalculateData();
	g_app.iiiOnAlarmDetect();
	g_protect.OnTimer10ms();
#ifdef MODULE__LAD_H
	g_lad.OnTimer10ms();
#endif
	g_app.iiiOnRelayOut();
//#ifdef MODULE__LAD_H
//		g_lad.OnTimer10ms();
//#endif
	for(WORD i=0;i<RELAYKH_COUNT;i++) g_relayKH[i].OnTimer10ms();
#ifdef KPU
	g_relayKPU.OnTimer10ms();
#endif
#ifdef _WIN32
	if(CMyData::s_bAddFilter)
	{
		for(WORD i=0;i<DFT_DOTNUM;i++) g_app.OnWaveRecord(i);
	}
#endif
}

void CMyAppDMR::OnTimer1000ms(void)
{
	g_time.OnTimer1000ms();
	g_eventTable.OnTimer1000ms();
	g_waveRecord.OnTimer1000ms();
	g_app.iiiOnSetDataMetrics();
	g_app.iiiOnRefreshData();
#ifdef HASTIMEIC
	if(g_arRTC.IsError()) g_deviceInfo.wDeviceStatus1 |= DS1_ErrorTime;
	else g_deviceInfo.wDeviceStatus1 &= 0xffff^DS1_ErrorTime;
#endif
	if(g_arEEPROM.IsError()) g_deviceInfo.wDeviceStatus1 |= DS1_ErrorFlash;
	else g_deviceInfo.wDeviceStatus1 &= 0xffff^DS1_ErrorFlash;
}

void CMyAppDMR::OnWhileLoop(void)
{
	SetAllDeviceSets();
	CheckAllDeviceSets();
	UpdateAllDeviceSets();

	g_deviceInfo.wCountAll = GetCountAll();
	if(m_wCountAllOld!=g_deviceInfo.wCountAll)
	{
		m_wCountAllOld = g_deviceInfo.wCountAll;
		g_hmi.OnUpdateDevice();
	}
}

void CMyAppDMR::OnInitDevice(void)
{
	g_eventTable.OnInitDevice();
}

void CMyAppDMR::OnResetDevice(void)
{
	g_protect.m_dwProtectActed = 0;
	g_deviceInfo.wDeviceStatus1 &= 0xffff^(DS1_Alarmed|DS1_Tripped);
	g_deviceInfo.wDeviceStatus3 |= DS3_DeviceReset;
	g_hmi.OnResetDevice();
}

void CMyAppDMR::SetAlarmedFlag(void)
{
	g_deviceInfo.wDeviceStatus1 |= DS1_Alarmed;
}

void CMyAppDMR::SetTrippedFlag(void)
{
	g_deviceInfo.wDeviceStatus1 |= DS1_Tripped;
}

void CMyAppDMR::OnUpdateDevice(WORD* pData)
{
	for(WORD i=0;i<32;i++) if(SETPOINTCFG(i)==PROTECTCFG_NULL) SETPOINTTOG(i) = PROTECTTOG_OFF;
	g_time.OnUpdateDevice(pData);
	g_protect.OnUpdateDevice(pData);
	OnUpdateAllDeviceSet(pData);
}

void CMyAppDMR::OnRelayOut(void)
{
	g_app.iiiOnRelayOut();
	g_hdif.iiiFlushRelays();
}

void CMyAppDMR::OnWaveRecord(WORD wSwitchStatus,WORD wData1,WORD wData2,WORD wData3,WORD wData4,WORD wData5,WORD wData6,WORD wData7,WORD wData8)
{
	wData1 >>= 2;
	wData2 >>= 2;
	wData3 >>= 2;
	wData4 >>= 2;
	wData5 >>= 2;
	wData6 >>= 2;
	wData7 >>= 2;
	wData8 >>= 2;
	g_waveRecord.m_wWaveData[0] = wSwitchStatus;
	g_waveRecord.m_wWaveData[1] = wData1|(wData2<<10);
	g_waveRecord.m_wWaveData[2] = (wData2>>6)|(wData3<<4)|(wData4<<14);
	g_waveRecord.m_wWaveData[3] = (wData4>>2)|(wData5<<8);
	g_waveRecord.m_wWaveData[4] = (wData5>>8)|(wData6<<2)|(wData7<<12);
	g_waveRecord.m_wWaveData[5] = (wData7>>4)|(wData8<<6);
	g_waveRecord.OnRecord();
}

void CMyAppDMR::iiiOnRelayOut(void)
{
#ifdef LINKOUT_ALARMED
	if(g_deviceParam.wLinkOutAlarmed!=LINKOUT_NULL)
	{
		g_relayKH[g_deviceParam.wLinkOutAlarmed-LINKOUT_KH01].SetLevel((g_deviceInfo.wDeviceStatus1&DS1_Alarmed)?STATUS_ON:STATUS_OFF);
	}
#endif
#ifdef LINKOUT_TRIPPED
	if(g_deviceParam.wLinkOutTripped!=LINKOUT_NULL)
	{
		g_relayKH[g_deviceParam.wLinkOutTripped-LINKOUT_KH01].SetLevel((g_deviceInfo.wDeviceStatus1&DS1_Tripped)?STATUS_ON:STATUS_OFF);
	}
#endif
#ifdef LINKOUT_ERRORED		// ³£±Õ
	if(g_deviceParam.wLinkOutErrored!=LINKOUT_NULL)
	{
//		g_relayKH[g_deviceParam.wLinkOutErrored-LINKOUT_KH01].SetLevel((g_deviceInfo.wDeviceStatus1&DS1_Errored)?STATUS_ON:STATUS_OFF);
		g_relayKH[g_deviceParam.wLinkOutErrored-LINKOUT_KH01].SetLevel((g_deviceInfo.wDeviceStatus1&DS1_Errored)?STATUS_OFF:STATUS_ON);
	}
#endif
}

