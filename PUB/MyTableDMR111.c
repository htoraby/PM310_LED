#include <Main.h>


//-----------------------------------------------------------------------------
WORD* Table_GetDeviceAddr(WORD wLogAddr,WORD wLength,BOOL bAccessWrite)
{
	WORD* pDevAddr = NULL;
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICETIME,SIZEOFWORD(g_deviceTime),(WORD*)&g_deviceTime);
	if(pDevAddr) return pDevAddr;
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEINFO,SIZEOFWORD(g_deviceInfo),(WORD*)&g_deviceInfo);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_ANALOGDATA,SIZEOFWORD(g_analogData),(WORD*)&g_analogData);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
// 	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_ANALOGDATAEXT,SIZEOFWORD(g_analogDataExt),(WORD*)&g_analogDataExt);
// 	if(pDevAddr)
// 	{
// 		if(bAccessWrite) pDevAddr = NULL;
// 		return pDevAddr;
// 	}
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_ANALOGWAVE,SIZEOFWORD(g_analogWave),(WORD*)&g_analogWave);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DFTDATASET,SIZEOFWORD(g_dftDataSet),(WORD*)&g_dftDataSet);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEPARAM,SIZEOFWORD(g_deviceParam),(WORD*)&g_deviceParam);
	if(pDevAddr) return pDevAddr;
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEINPARAM,SIZEOFWORD(g_inparamTable),(WORD*)&g_inparamTable);
	if(pDevAddr) return pDevAddr;
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEREGULATE,SIZEOFWORD(g_regulateSet),(WORD*)&g_regulateSet);
	if(pDevAddr) return pDevAddr;
#ifdef _CMYPROTECT_H
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICESETPOINT,SIZEOFWORD(g_deviceSetpoint),(WORD*)&g_deviceSetpoint);
	if(pDevAddr) return pDevAddr;
#endif/*_CMYPROTECT_H*/
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_EVENTTABLE,SIZEOFWORD(g_eventTable),(WORD*)&g_eventTable);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
	return NULL;
}

void Table_ControlOut(WORD wControlOutCode,WORD wCommand)
{
	WORD i;
	if(wCommand!=0xaaaa&&wCommand!=0x3333&&wCommand!=0x5555) return;
	if(wControlOutCode==CONTROLOUT_INITDEVICE){ MyApp_OnInitDevice(); return; }
	if(wControlOutCode==CONTROLOUT_RESETDEVICE){ MyApp_OnResetDevice(); return; }
#ifdef MODULE__WAVERECORD_H
	if(wControlOutCode==CONTROLOUT_FREEZEWAVE){ g_waveRecord.FreezeRecord(); return; }
#endif
	for(i=0;i<RELAYKH_COUNT;i++)
	{
		if(wControlOutCode==CONTROLOUT_KH01+i)
		{
			if(wCommand==0xaaaa) Output_SetPulse(&g_relayKH[i],20);
			else if(wCommand==0x3333) Output_SetLevel(&g_relayKH[i],STATUS_OFF);
			else if(wCommand==0x5555) Output_SetLevel(&g_relayKH[i],STATUS_ON);
			return;
		}
	}
#ifdef RELAYKOT_COUNT
	for(i=0;i<RELAYKOT_COUNT;i++)
	{
		if(wControlOutCode==CONTROLOUT_KOT01+i)
		{
			if(wCommand==0xaaaa) Output_SetPulse(&g_relayKOT[i],20);
			else if(wCommand==0x3333) Output_SetLevel(&g_relayKOT[i],STATUS_OFF);
			else if(wCommand==0x5555) Output_SetLevel(&g_relayKOT[i],STATUS_ON);
			return;
		}
	}
#endif
}
