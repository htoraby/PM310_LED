#include <Main.h>


//-----------------------------------------------------------------------------
WORD* CMyTableDMR::GetDeviceAddr(WORD wLogAddr,WORD wLength,BOOL bAccessWrite)
{
	WORD* pDevAddr = NULL;
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICETIME,SIZEOFWORD(g_time.m_deviceTime),(WORD*)&g_time.m_deviceTime);
	if(pDevAddr) return pDevAddr;
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEINFO,SIZEOFWORD(g_deviceInfo),(WORD*)&g_deviceInfo);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_ANALOGDATA,SIZEOFWORD(g_analogData),(WORD*)&g_analogData);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_ANALOGDATAEXT,SIZEOFWORD(g_analogDataExt),(WORD*)&g_analogDataExt);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_ANALOGWAVE,SIZEOFWORD(g_measure.m_analogWave),(WORD*)&g_measure.m_analogWave);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_DFTDATASET,SIZEOFWORD(g_measure.m_dftDataSet),(WORD*)&g_measure.m_dftDataSet);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEPARAM,SIZEOFWORD(g_deviceParam),(WORD*)&g_deviceParam);
	if(pDevAddr) return pDevAddr;
// 	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEINPARAM,SIZEOFWORD(g_inparamTable),(WORD*)&g_inparamTable);
// 	if(pDevAddr) return pDevAddr;
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEREGULATE,SIZEOFWORD(g_measure.m_regulateSet),(WORD*)&g_measure.m_regulateSet);
	if(pDevAddr) return pDevAddr;
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEINPARAM,SIZEOFWORD(g_inparamTable),(WORD*)&g_inparamTable);
	if(pDevAddr)
	{
		g_bQuit1ms = TRUE;
		return pDevAddr;
	}
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICESETPOINT,SIZEOFWORD(g_deviceSetpoint),(WORD*)&g_deviceSetpoint);
	if(pDevAddr)
	{
		g_bQuit1ms = TRUE;
		return pDevAddr;
	}
#ifdef MODULE__DRW_H
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEDRW,SIZEOFWORD(g_deviceDRW),(WORD*)&g_deviceDRW);
	if(pDevAddr)
	{
		g_bQuit1ms = TRUE;
		return pDevAddr;
	}
#endif
#ifdef MODULE__LAD_H
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICELAD,SIZEOFWORD(g_deviceLAD),(WORD*)&g_deviceLAD);
	if(pDevAddr)
	{
		g_bQuit1ms = TRUE;
		return pDevAddr;
	}
#endif
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_EVENTTABLE,SIZEOFWORD(g_eventTable.m_eventTable),(WORD*)&g_eventTable.m_eventTable);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
#ifdef MODULE__WAVERECORD_H
	pDevAddr = GetDevAddr(wLogAddr,wLength,LOGADDR_WAVERECORD,(WORD)WAVERECORD_ALLWORDS,(WORD*)g_waveRecord.GetWaveRecord(0));
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
#endif
	return NULL;
}

void CMyTableDMR::ControlOut(WORD wControlOutCode,WORD wCommand)
{
	WORD i;
	if(wCommand!=0xaaaa&&wCommand!=0x3333&&wCommand!=0x5555) return;
	if(wControlOutCode==CONTROLOUT_INITDEVICE){ g_app.OnInitDevice(); return; }
	if(wControlOutCode==CONTROLOUT_RESETDEVICE){ g_app.OnResetDevice(); return; }
#ifdef MODULE__WAVERECORD_H
	if(wControlOutCode==CONTROLOUT_FREEZEWAVE){ g_waveRecord.FreezeRecord(); return; }
#endif
	for(i=0;i<RELAYKH_COUNT;i++)
	{
		if(wControlOutCode==CONTROLOUT_KH01+i)
		{
			if(wCommand==0xaaaa) g_relayKH[i].SetPulse(20);
			else if(wCommand==0x3333) g_relayKH[i].SetLevel(STATUS_OFF);
			else if(wCommand==0x5555) g_relayKH[i].SetLevel(STATUS_ON);
			return;
		}
	}

#ifdef KPU
		if(wControlOutCode==CONTROLOUT_KPU)
		{
			if(wCommand==0xaaaa) g_relayKPU.SetPulse(20);
			else if(wCommand==0x3333) g_relayKPU.SetLevel(STATUS_OFF);
			else if(wCommand==0x5555) g_relayKPU.SetLevel(STATUS_ON);
			return;
		}
#endif

#ifdef MODULE__LAD_H
	for(i=0;i<8;i++)
	{
		if(wControlOutCode==CONTROLOUT_VKH1+i)
		{
			if(wCommand==0xaaaa) g_lad.m_wCountVKH[i] = 20;
			else if(wCommand==0x3333) g_lad.m_wCountVKH[i] = STATUS_OFF;
			else if(wCommand==0x5555) g_lad.m_wCountVKH[i] = STATUS_ON;
			return;
		}
	}
#endif
}
