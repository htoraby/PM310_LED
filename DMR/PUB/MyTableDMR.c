#include <Main.h>


//-----------------------------------------------------------------------------
WORD* Table_GetDeviceAddr(WORD wLogAddr,WORD wLength,BOOL bAccessWrite)
{
//	int nWaveRecordedDot = WAVERECORD_DOTNUM;
//	int i=0;
//	int nWaveStartDotNo = 0;
//	WORD* pWaveData;


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
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_ANALOGDATAEXT,SIZEOFWORD(g_analogDataExt),(WORD*)&g_analogDataExt);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
// 	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_ANALOGWAVE,SIZEOFWORD(g_analogWave),(WORD*)&g_analogWave);
// 	if(pDevAddr)
// 	{
// 		if(bAccessWrite) pDevAddr = NULL;
// 		return pDevAddr;
// 	}
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DFTDATASET,SIZEOFWORD(g_dftDataSet),(WORD*)&g_dftDataSet);
	if(pDevAddr)
	{
		if(bAccessWrite) pDevAddr = NULL;
		return pDevAddr;
	}
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEPARAM,SIZEOFWORD(g_deviceParam),(WORD*)&g_deviceParam);
	if(pDevAddr) return pDevAddr;
// 	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEINPARAM,SIZEOFWORD(g_inparamTable),(WORD*)&g_inparamTable);
	if(pDevAddr) return pDevAddr;
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICEREGULATE,SIZEOFWORD(g_regulateSet),(WORD*)&g_regulateSet);
	if(pDevAddr) return pDevAddr;
#ifdef _CMYPROTECT_H
	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_DEVICESETPOINT,SIZEOFWORD(g_deviceSetpoint),(WORD*)&g_deviceSetpoint);
	if(pDevAddr) return pDevAddr;
#endif/*_CMYPROTECT_H*/
// 	pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_EVENTTABLE,EVENT_SIZE,(WORD*)&g_eventTable);
// 	if(pDevAddr)
// 	{
// 		if(bAccessWrite) pDevAddr = NULL;
// 		if(g_eventTable.wEventReadCnt>=g_wEventTableCountNew)
// 		{
// 			pDevAddr = NULL;
// 		}
// 		else
// 		{
// 			pDevAddr = Table_GetDevAddr(wLogAddr,wLength,LOGADDR_EVENTTABLE,EVENT_SIZE,(WORD*)&g_eventTable.event[g_eventTable.wEventReadCnt%EVENT_COUNT]);
// 			if(pDevAddr)
// 			{
// 				if(bAccessWrite) pDevAddr = NULL;
// 			}
// 			g_eventTable.wEventReadCnt++;
// 		}
// 		return pDevAddr;
// 	}
    return NULL;
    
}

void Table_ControlOut(WORD wControlOutCode,WORD wCommand)
{
	WORD i;
// 	if((g_deviceInfo.wSwitchStatus1&0x100)!=0x100)
// 	{
// 		g_CommBuffer[1] |= 0X80;
// 		return;
// 	}
	if(wCommand!=0xaaaa&&wCommand!=0x3333&&wCommand!=0x5555) return;
	if(wControlOutCode==CONTROLOUT_INITDEVICE){ MyApp_OnInitDevice(); return; }
	if(wControlOutCode==CONTROLOUT_RESETDEVICE){ MyApp_OnResetDevice(); return; }
// 	if(wControlOutCode==CONTROLOUT_FREEZEWAVE){ WaveRecord_FreezeRecord(); return; }
    if(wControlOutCode==CONTROLOUT_ADJUST){ Measure_StartReg(); return; }

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
// #ifdef RELAYKOT_COUNT
// 	for(i=0;i<RELAYKOT_COUNT;i++)
// 	{
// 		if(wControlOutCode==CONTROLOUT_KOT)
// 		{
// //			if(wCommand==0xaaaa) Output_SetPulse(&g_relayKOT[i],20);
// 			if(wCommand==0xaaaa) Output_SetPulse(&g_relayKH[Relay_KOT],20);
// 			else if(wCommand==0x3333) Output_SetLevel(&g_relayKH[Relay_KOT],STATUS_OFF);
// 			else if(wCommand==0x5555) Output_SetLevel(&g_relayKH[Relay_KOT],STATUS_ON);
// 			return;
// 		}
// 	}
// #endif
}

void Table_RemoteControlOut(WORD wControlOutCode,WORD wCommand)
{
    WORD i;
    if(wCommand!=0xFF00) return;

    for(i=0;i<RELAYKH_COUNT;i++)
    {
        if(wControlOutCode==CONTROLOUT_KH01+i)
        {
            Output_SetPulse(&g_relayKH[i],20);
//             Event_AddEvent(EVENTTYPE_RUNINFO,EVENTCODE_REMOTE+i,1);
        }
    }
}

short Table_ReadExt(WORD wLogAddr, WORD wLength)
{
//     short nRes = -1;
//     nRes = Table_ReadWaveRecod(wLogAddr, wLength);
//     if(nRes>0) return nRes;            // 
//     else if(nRes==-1) return 0;
    return 0;
}

// typedef struct
// {
//     DEVICETIME timeFreeze;                              // 录波器录波冻结时间;
//     WORD wRecordStatus;                                 // 录波器当前录波状态;
//     WORD wFreezeDotNo;                                  // 录波器录波冻结点号;
//     WORD wCycleFlag;                                    // 录波器是否循环标志;
//     short nK[WAVERECORD_DATASIZE];                      // 校正系数
//     WORD wOffset;                                       // 直流分量
//     short nData[WAVERECORD_DATASIZE][WAVERECORD_DOTNUM]; // 录波器录波数据;
// }WAVERECORDR;
// 
// // 返回值: FALSE: 时间相等
// //          TURE: 时间不相等
// BOOL TimeNEQ(DEVICETIME* pTime1, DEVICETIME* pTime2)
// {
//     if(pTime1->wYear!=pTime2->wYear) return TRUE;
//     if(pTime1->wMonth!=pTime2->wMonth) return TRUE;
//     if(pTime1->wDay!=pTime2->wDay) return TRUE;
//     if(pTime1->wHour!=pTime2->wHour) return TRUE;
//     if(pTime1->wMinute!=pTime2->wMinute) return TRUE;
//     if(pTime1->wSecond!=pTime2->wSecond) return TRUE;
//     if(pTime1->wMilliSecond!=pTime2->wMilliSecond) return TRUE;
//     return FALSE;
// }
// 
// static WORD s_wWRCount = 0;
// static WORD s_wWRNo[WAVERECORD_WAVENUM-1] = {0};
// 
// static void SearchRecord(void)
// {
//     short i;
//     s_wWRCount = 0;
//     for(i=0;i<WAVERECORD_WAVENUM-1;i++)
//     {
//         WORD wWaveNo = (g_deviceInfo.wCountWaveRecord+1+i)%WAVERECORD_WAVENUM;
//         WAVERECORD* pWaveRecord = WaveRecord_GetRecord(wWaveNo);
//         if(pWaveRecord->wRecordStatus!=WRS_RECORDED) continue;
//         if(!Time_IsTimeOK(&pWaveRecord->timeFreeze)) continue;
//         s_wWRNo[s_wWRCount] = wWaveNo;
//         s_wWRCount++;
//     }
// }
// 
// const WORD s_wWaveRecordLen = SIZEOFWORD(WAVERECORDR)*(WAVERECORD_WAVENUM-1);
// 
// // 返回值:  0: 不在数据范围内
// //         -1: 在数据范围内,但要读取的数据不存在
// //         >0: 发送的数据长度,数据以填到缓冲区中
// static DEVICETIME s_WaveRecordTime = { 0, 0, 0, 0, 0, 0, 0};          // 要读的录波时间,作为录波的唯一标识
// static WAVERECORDR s_wWaveRecordR;                                    // 重新排列的数据
// short Table_ReadWaveRecod(WORD wLogAddr, WORD wLength)
// {
//     WORD* pDevAddr = NULL;
//     WORD wOffset = 0;
//     WORD wWaveRecordNo = 0;
//     WAVERECORD* pWaveRecord = NULL;
//     pDevAddr = Table_GetDevAddr(wLogAddr, wLength, LOGADDR_WAVERECORD, s_wWaveRecordLen, (WORD*)WaveRecord_GetRecord(0));
//     if(pDevAddr==NULL) return 0;                        // 不在此数据范围内
// 
//     SearchRecord();
// 
//     wOffset = wLogAddr - LOGADDR_WAVERECORD;
//     wWaveRecordNo = wOffset/SIZEOFWORD(WAVERECORD);
//     if(wWaveRecordNo>=s_wWRCount) return 0;             // 
// 
//     wWaveRecordNo = s_wWRNo[wWaveRecordNo];
//     pWaveRecord = WaveRecord_GetRecord(wWaveRecordNo);
//     if(pWaveRecord==NULL) return -1;
//     if(pWaveRecord->wRecordStatus!=WRS_RECORDED) return -1;
//     if(TimeNEQ(&s_WaveRecordTime, &pWaveRecord->timeFreeze))                  // 排数据
//     {
//         short i;
//         short nWaveStartDotNo = 0;
//         short nWaveRecordedDot = WAVERECORD_DOTNUM;
//         s_wWaveRecordR.timeFreeze = pWaveRecord->timeFreeze;
//         s_wWaveRecordR.wRecordStatus = pWaveRecord->wRecordStatus;
//         s_wWaveRecordR.wFreezeDotNo = pWaveRecord->wFreezeDotNo;
//         s_wWaveRecordR.wCycleFlag = pWaveRecord->wCycleFlag;
//         for(i=0;i<7;++i) s_wWaveRecordR.nK[i] = pWaveRecord->nK[i];
//         s_wWaveRecordR.wOffset = pWaveRecord->wOffset;
// 
//         if(pWaveRecord->wCycleFlag==0) nWaveRecordedDot = MIN(pWaveRecord->wFreezeDotNo, WAVERECORD_DOTNUM);
//         if(nWaveRecordedDot<24*5) return -1;
//         nWaveStartDotNo = (pWaveRecord->wFreezeDotNo+WAVERECORD_DOTNUM-nWaveRecordedDot)%WAVERECORD_DOTNUM;
//         s_wWaveRecordR.wFreezeDotNo = nWaveRecordedDot;
//         for(i=0;i<nWaveRecordedDot;i++)
//         {
//             short nDotNo = (nWaveStartDotNo+i)%WAVERECORD_DOTNUM;
//             WORD* pWaveData = &(pWaveRecord->wData[nDotNo][0]);
// //减去偏置后上送            
// //            s_wWaveRecordR.nData[0][i] = (short)pWaveData[0];
// //            s_wWaveRecordR.nData[1][i] = (short)pWaveData[1];
// //            s_wWaveRecordR.nData[2][i] = (short)pWaveData[2];
// //            s_wWaveRecordR.nData[3][i] = (short)pWaveData[3];
// //            s_wWaveRecordR.nData[4][i] = (short)pWaveData[4];
// //            s_wWaveRecordR.nData[5][i] = (short)pWaveData[5];
// //            s_wWaveRecordR.nData[6][i] = (short)pWaveData[6];
//             s_wWaveRecordR.nData[0][i] = (short)pWaveData[0] - pWaveRecord->wOffset;
//             s_wWaveRecordR.nData[1][i] = (short)pWaveData[1] - pWaveRecord->wOffset;
//             s_wWaveRecordR.nData[2][i] = (short)pWaveData[2] - pWaveRecord->wOffset;
//             s_wWaveRecordR.nData[3][i] = (short)pWaveData[3] - pWaveRecord->wOffset;
//             s_wWaveRecordR.nData[4][i] = (short)pWaveData[4] - pWaveRecord->wOffset;
//             s_wWaveRecordR.nData[5][i] = (short)pWaveData[5] - pWaveRecord->wOffset;
//             s_wWaveRecordR.nData[6][i] = (short)pWaveData[6];
//         }
//         s_WaveRecordTime = pWaveRecord->timeFreeze;
//     }
//     wOffset = wOffset%SIZEOFWORD(WAVERECORD);       // 数据偏移
// //     if(wLength<=125)
// //     {
// //         Protocol_CopyWordToByte(g_CommBuffer+3, (WORD*)&s_wWaveRecordR + wOffset, wLength);
// //     }
// //     else
// //     {
// //         Protocol_CopyWordToByte(g_CommBuffer+4, (WORD*)&s_wWaveRecordR + wOffset, wLength);
// //     }
//     Protocol_CopyWordToByte(g_CommBuffer+((wLength<=125)?3:4), (WORD*)&s_wWaveRecordR + wOffset, wLength);
//     return wLength*2;
// }
