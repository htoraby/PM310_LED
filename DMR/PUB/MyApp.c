#include "main.h"

DEVICEINFO g_deviceInfo;
DEVICEPARAM g_deviceParam;
MyOutput g_relayKH[RELAYKH_COUNT];
#ifdef RELAYKOT_COUNT
MyOutput g_relayKOT[RELAYKOT_COUNT];
#endif/*RELAYKOT_COUNT*/
// WORD g_wPanelTest;
// BOOL g_bDInfoChanged;			// 需要保存的设备信息改变;
DeviceSet g_devicesetParam;
DeviceSet g_devicesetRegulate;
DeviceSet g_devicesetSetpoint;

WORD g_wCountAllOld;
BOOL g_bDInfoChanged;

WORD g_wFreq;

//-----------------------------------------------------------------------------
WORD MyApp_GetCountAll(void)
{
	WORD wCountAll;
	g_deviceInfo.wCountEventTable = g_wEventTableCountNew;
	g_deviceInfo.wCountDeviceParam = g_devicesetParam.m_wCountNew;
	g_deviceInfo.wCountDeviceRegulate = g_devicesetRegulate.m_wCountNew;
#ifdef _CMYPROTECT_H
	g_deviceInfo.wCountDeviceSetpoint = g_devicesetSetpoint.m_wCountNew;
#else
	g_deviceInfo.wCountDeviceSetpoint = 0;
#endif/*_CMYPROTECT_H*/
    g_deviceInfo.wCountWaveRecord = g_wWRCountNew;
	wCountAll = 0;
	wCountAll += g_deviceInfo.wCountEventTable;
	wCountAll += g_deviceInfo.wCountDeviceParam;
	wCountAll += g_deviceInfo.wCountDeviceRegulate;
	wCountAll += g_deviceInfo.wCountDeviceSetpoint;
    wCountAll += g_deviceInfo.wCountWaveRecord;

	return wCountAll;
}

void MyApp_SetAllDeviceSets(void)
{
	DeviceSet_SetDeviceSet(&g_devicesetParam,(WORD*)&g_deviceParam,SIZEOFWORD(g_deviceParam),DS1_ErrorParam,EEPROMADDR_DeviceParam);
	DeviceSet_SetDeviceSet(&g_devicesetRegulate,(WORD*)&g_regulateSet,SIZEOFWORD(g_regulateSet),DS1_ErrorRegulate,EEPROMADDR_DeviceRegulate);
#ifdef _CMYPROTECT_H
	DeviceSet_SetDeviceSet(&g_devicesetSetpoint,(WORD*)&g_deviceSetpoint,SIZEOFWORD(g_deviceSetpoint),DS1_ErrorSetpoint,EEPROMADDR_DeviceSetpoint);
#endif/*_CMYPROTECT_H*/
}

void MyApp_InitAllDeviceSets(void)
{
	DeviceSet_InitDeviceSet(&g_devicesetParam);
	DeviceSet_InitDeviceSet(&g_devicesetRegulate);
#ifdef _CMYPROTECT_H
	DeviceSet_InitDeviceSet(&g_devicesetSetpoint);
#endif/*_CMYPROTECT_H*/
}

void MyApp_CheckAllDeviceSets(void)
{
	DeviceSet_CheckDeviceSet(&g_devicesetParam);
	DeviceSet_CheckDeviceSet(&g_devicesetRegulate);
#ifdef _CMYPROTECT_H
	DeviceSet_CheckDeviceSet(&g_devicesetSetpoint);
#endif/*_CMYPROTECT_H*/
}

void MyApp_UpdateAllDeviceSets(void)
{
	DeviceSet_UpdateDeviceSet(&g_devicesetParam);
	DeviceSet_UpdateDeviceSet(&g_devicesetRegulate);
#ifdef _CMYPROTECT_H
	DeviceSet_UpdateDeviceSet(&g_devicesetSetpoint);
#endif/*_CMYPROTECT_H*/
}

void MyApp_OnUpdateAllDeviceSet(WORD* pData)
{
	DeviceSet_OnUpdateDevice(&g_devicesetParam,pData);
	DeviceSet_OnUpdateDevice(&g_devicesetRegulate,pData);
#ifdef _CMYPROTECT_H
	if(DeviceSet_OnUpdateDevice(&g_devicesetSetpoint,pData)) Protect_OnInit();
#endif/*_CMYPROTECT_H*/

}


//-----------------------------------------------------------------------------
void MyApp_OnInitParams()
{
// 	short i;
	MemoryClear((WORD*)&g_deviceInfo,SIZEOFWORD(g_deviceInfo));
	MemoryClear((WORD*)&g_deviceParam,SIZEOFWORD(g_deviceParam));
	MemoryClear((WORD*)&g_deviceSetpoint,SIZEOFWORD(g_deviceSetpoint));
	Measure_OnInitParams();

	g_deviceParam.wModbusAddr1 = 1;
	g_deviceParam.wBaudrate1 = BAUDRATE_9600;
    g_deviceParam.wLCDContrast = 8;
	g_deviceParam.wMultiLanguage  = 0;
	CopyCharToWSZ(g_deviceParam.wszDeviceType,(char*)DEVICETYPE_NAME);
	Protect_OnInitSetpoint(&g_deviceSetpoint.wSetpointArea1[0]);
	MyApp_OnInitSubParam();
}

void MyApp_OnInit(void)
{
	short i;
	BOOL bRead;
	WORD wTmp[7];

	MyApp_SetAllDeviceSets();
	MyApp_InitAllDeviceSets();
#ifdef _WIN32
	DeviceSet_ForceUpdateDeviceSet(&g_devicesetParam);
	DeviceSet_ForceUpdateDeviceSet(&g_devicesetRegulate);
#ifdef _CMYPROTECT_H
	DeviceSet_ForceUpdateDeviceSet(&g_devicesetSetpoint);
#endif/*_CMYPROTECT_H*/
#endif
	g_deviceInfo.wSwitchStatus1 = 0;
	g_deviceInfo.wSwitchStatus2 = 0;
	g_deviceInfo.wDeviceStatus1 = 0;
	g_deviceInfo.wDeviceStatus2 = 0;
	g_deviceInfo.wDeviceStatus3 = 0;
	g_deviceInfo.wSelfTestMain = 0;
	g_deviceInfo.wSelfTestSub = 0;
// 	g_wExtID = 0;
// 	g_bDInfoChanged = 0;
// 	
	Time_OnInit();
	Event_OnInit();
	Switch_OnInit();
	for(i=0;i<RELAYKH_COUNT;i++) Output_OnInit(&g_relayKH[i]);
#ifdef RELAYKOT_COUNT
	for(i=0;i<RELAYKOT_COUNT;i++) Output_OnInit(&g_relayKOT[i]);
#endif/*RELAYKOT_COUNT*/
	Measure_OnInit();
#ifdef _CMYPROTECT_H
	Protect_OnInit();
#endif/*_CMYPROTECT_H*/
	g_deviceInfo.wCountAll = MyApp_GetCountAll();
	g_wCountAllOld = g_deviceInfo.wCountAll;
// 	bRead = EEPROM_ReadBlock(EEPROMADDR_DeviceStatus,NULL,wTmp,7);
	bRead = Flash_ReadBlock(EEPROMADDR_DeviceStatus,NULL,wTmp,7);
//	bRead = EEPROM_ReadBlock(EEPROMADDR_DeviceStatus,NULL,wTmp,SIZEOFWORD(g_deviceInfo));	
	if(bRead)
	{
		g_deviceInfo.wNumPwrup = wTmp[0];
		g_deviceInfo.wWrmStr = wTmp[1];
		g_deviceInfo.wDeviceStatus1 |= wTmp[2]&(DS1_Alarmed|DS1_Tripped);
		// 		g_deviceInfo.wDeviceStatus2 |= wTmp[3]&(DS2_ErrorOpen|DS2_ErrorClose);
#ifdef _CMYPROTECT_H
		g_dwProtectActed = ((DWORD)wTmp[3]<<16) | wTmp[4];
		g_wProtectActedIN = wTmp[5];
// 		g_wProtectActedUser = wTmp[6];
#endif/*_CMYPROTECT_H*/
	}
    WaveRecord_OnInit();
    WaveRecord_StartRecord();
    MyApp_OnInitsub();
    MyApp_OnSetDataMetrics();
}

void MyApp_OnInitDevice(void)
{
	Event_OnInitDevice();
}

void MyApp_OnTimer1ms(void)
{
    Time_OnTimer1ms();
    Switch_OnTimer1ms();
    g_deviceInfo.wSwitchStatus1 = g_wSwitchStatus1;
    g_deviceInfo.wSwitchStatus2 = g_wSwitchStatus2;
#ifdef _CMYPROTECT_H
    Protect_OnTimer1ms();
#endif/*_CMYPROTECT_H*/
}

void MyApp_OnTimer10ms(void)
{
	short i;
	g_deviceInfo.wDeviceType = (WORD)DEVICETYPE_CODE;					// 设备类型代码
	g_deviceInfo.wMainVersion = MAIN_VERSION;
	g_deviceInfo.wSubVersion = SUB_VERSION;
    g_deviceInfo.wLCDWidth = LCD_CXDOT;
    g_deviceInfo.wLCDHeigh = LCD_CYDOT;
    g_deviceInfo.wCRC = (WORD)(g_pCRCInfo->dwCRC32);

	g_bAddFilter = !g_bAddFilter;
	Measure_OnTimer10ms();
	MyApp_OnCalculateData();
	MyApp_OnAlarmDetect();
#ifdef _CMYPROTECT_H
	Protect_OnTimer10ms();
#endif/*_CMYPROTECT_H*/
	MyApp_OnRelayOut();
	for(i=0;i<RELAYKH_COUNT;i++) Output_OnTimer10ms(&g_relayKH[i]);
#ifdef RELAYKOT_COUNT
	for(i=0;i<RELAYKOT_COUNT;i++) Output_OnTimer10ms(&g_relayKOT[i]);
#endif/*RELAYKOT_COUNT*/
#ifdef _WIN32
    if(g_bAddFilter)
    {
        for(i=0;i<DFT_DOTNUM;i++) OnWaveRecord(i);
    }
#endif/*_WIN32*/
}

void MyApp_OnTimer1000ms(void)
{
    Time_OnTimer1000ms();
    Event_OnTimer1000ms();
    WaveRecord_OnTimer1000ms();

    MyApp_OnSetDataMetrics();
    MyApp_OnRefreshData();
    if(RTC_IsError()) g_deviceInfo.wDeviceStatus1 |= DS1_ErrorTime;
    else g_deviceInfo.wDeviceStatus1 &= 0xffff^DS1_ErrorTime;
}

void MyApp_OnWhileLoop(void)
{
	WORD wTmp[7];
	MyApp_SetAllDeviceSets();
	MyApp_CheckAllDeviceSets();
	MyApp_UpdateAllDeviceSets();
	
	g_deviceInfo.wCountAll = MyApp_GetCountAll();
	if(g_wCountAllOld!=g_deviceInfo.wCountAll)
	{
		g_wCountAllOld = g_deviceInfo.wCountAll;
		MyHMI_OnUpdateDevice();
	}

	if(g_bDInfoChanged)
	{
		g_bDInfoChanged = FALSE;
		wTmp[0] = g_deviceInfo.wNumPwrup;
		wTmp[1] = g_deviceInfo.wWrmStr;
		wTmp[2] = g_deviceInfo.wDeviceStatus1;
#ifdef _CMYPROTECT_H
		wTmp[3] = (WORD)(g_dwProtectActed>>16);
		wTmp[4] = (WORD)(g_dwProtectActed);
		wTmp[5] = g_wProtectActedIN;
// 		wTmp[6] = g_protect.m_wProtectActedUser;
		wTmp[6] = 0;
#else/*_CMYPROTECT_H*/
		wTmp[3] = 0;
		wTmp[4] = 0;
		wTmp[5] = 0;
		wTmp[6] = 0;
#endif/*_CMYPROTECT_H*/
// 		EEPROM_WriteBlock(EEPROMADDR_DeviceStatus,NULL,wTmp,7);
		Flash_WriteBlock(EEPROMADDR_DeviceStatus,NULL,wTmp,7);
	//	EEPROM_WriteBlock(EEPROMADDR_DeviceStatus,NULL,wTmp,SIZEOFWORD(g_deviceInfo));
	}
}

void MyApp_OnResetDevice(void)
{
#ifdef _CMYPROTECT_H
	g_dwProtectActed = 0;
	g_wProtectActedIN = 0;
#endif
	g_deviceInfo.wDeviceStatus1 &= 0xffff^(DS1_Alarmed|DS1_Tripped);
	g_deviceInfo.wDeviceStatus3 |= DS3_DeviceReset;
	MyHMI_OnResetDevice();
	MyApp_OnResetSubDevice();
	g_bDInfoChanged = TRUE;
}

void MyApp_OnUpdateDevice(WORD* pwData, BOOL bRemote)
{
/*    if((bRemote && (g_deviceInfo.wSwitchStatus1&0x100)==0x100)
        || ((bRemote==FALSE) && (g_deviceInfo.wSwitchStatus1&0x100)!=0x100))*/
//     if((bRemote && (g_deviceInfo.wSwitchStatus1&0x100)==0x100)
//         || (bRemote==FALSE))
//     {
        g_deviceSetpoint.INSetpoint[0].wLinkIN = LINKIN_IN01;
        g_deviceSetpoint.INSetpoint[1].wLinkIN = LINKIN_IN02;
        g_deviceSetpoint.INSetpoint[2].wLinkIN = LINKIN_IN03;
        g_deviceSetpoint.INSetpoint[3].wLinkIN = LINKIN_IN04;
//         g_deviceSetpoint.INSetpoint[0].wLinkIN = LINKIN_NULL;
//         g_deviceSetpoint.INSetpoint[1].wLinkIN = LINKIN_NULL;
//         g_deviceSetpoint.INSetpoint[2].wLinkIN = LINKIN_NULL;
//         g_deviceSetpoint.INSetpoint[3].wLinkIN = LINKIN_NULL;
        MyApp_OnUpdateDeviceSub(pwData);
        Time_OnUpdateDevice(pwData);
// 		CopyCharToWSZ(g_deviceParam.wszDeviceType,(char*)DEVICETYPE_NAME);
        
		MyApp_OnUpdateAllDeviceSet(pwData);
//     }
}

void MyApp_OnRelayOut(void)
{
//    BOOL bGJ = FALSE;
//    if(g_deviceInfo.wDeviceStatus1&DS1_Alarmed) bGJ = TRUE;
//    if(g_deviceInfo.wDeviceStatus1&DS1_Errored) bGJ = TRUE;
//     Output_SetLevel(&g_relayKH[Relay_GJ],bGJ?STATUS_ON:STATUS_OFF);
//     Output_SetLevel(&g_relayKH[Relay_GZ],(g_deviceInfo.wDeviceStatus1&DS1_Tripped)?STATUS_ON:STATUS_OFF);
//     if(bGJ)
//     {
//         Output_SetPulse(&g_relayKH[Relay_GJ],20);
//     }
//     if(g_deviceInfo.wDeviceStatus1&DS1_Tripped)
//     {
//         Output_SetPulse(&g_relayKH[Relay_GZ],20);
//     }
    if(g_wProtectOpenFlag==0xaaaa)
    {
        Output_SetPulse(&g_relayKH[Relay_J1],20);
    }
    if(g_wProtectCloseFlag==0xaaaa)
    {
        Output_SetPulse(&g_relayKH[Relay_J2],20);
    }
}

void MyApp_TestRelay(WORD wIndex)
{

}

// void MyApp_OnTimerSample(WORD wIndex)
// {
//     static short nTold = 0, nTnew = 0;
//     static short nROld = 0;
//     static WORD wTimerF = 15;
//     static WORD wTimerFRest = 2400;
//     static WORD wSamTrace = 0;
// 
//     short nR;
//     WORD wIndexTmp;
//     wIndexTmp = (wIndex+1)%DFT_DOTNUM;
//     
//     nR = DFT_CalculateDFT1R((short*)&g_analogWave.wData[DFT_Ua][wIndexTmp]);
//     if(wTimerF) wTimerF--;
//     if(nROld<=0 && nR>=0 && nROld!=nR && wTimerF==0)
//     {
//         short nT;
//         WORD wFreq;
//         nTnew = (long)wIndex*1000 - (long)nR*1000/(long)(nR - nROld);
//         nT = nTnew - nTold + 24000;
//         if(nT<15000)
//         {
//             nT += 24000;
//         }
//         wFreq = 24000L*g_wFsam/(long)nT;
//         wSamTrace++;
//         wTimerFRest = 2400;
// //         g_wFreq = wFreq;
//         
//         if((wSamTrace&0x01)==0)
//         {
//             if(wFreq<=7550 && wFreq>=4450)
//             {
//                 g_wFreq = wFreq;
//                 g_wFsam = g_wFreq;
//             }
//             else
//             {
//                 g_wFreq = 0;
//                 g_wFsam = 5000;
//             }
//         }
// 
//         nTold = nTnew;
//         wTimerF = 15;
//     }
//     else
//     {
//         if(wTimerFRest)
//         {
//             wTimerFRest--;
//             if(wTimerFRest==0)
//             {
//                 g_wFreq = 0;
//                 g_wFsam = 5000;
//             }
//         }
//     }
//     nROld = nR;
// }


// void MyApp_OnTimerSample(WORD wIndex)
// {
//     static float fTold = 0, fTnew = 0;
// 
// //     static DWORD dwTold = 0, dwTnew = 0;
//     static short nROld = 0;
//     static WORD wTimerF = 15;
//     static WORD wTimerFRest = 2400;
//     static WORD wSamTrace = 0;
// 
//     short nR;
//     WORD wIndexTmp;
//     wIndexTmp = (wIndex+1)%DFT_DOTNUM;
//     
//     nR = DFT_CalculateDFT1R((short*)&g_analogWave.wData[DFT_Ua][wIndexTmp]);
//     if(wTimerF) wTimerF--;
//     if(nROld<=0 && nR>=0 && nROld!=nR && wTimerF==0)
//     {
//         float fT;
//         WORD wFreq;
//         fTnew = (float)g_dwSysTimerUs - (float)g_wFsam*(float)nR/(float)(nR - nROld);
//         fT = fTnew - fTold;
// 
//         if(fT!=0)
//         {
//             wFreq = (WORD)(1000000000/fT + 0.5);
//             wSamTrace++;
//             wTimerFRest = 2400;
//             if((wSamTrace&0x07)==0)
//             {
//                 if(wFreq<=7550 && wFreq>=4450)
//                 {
//                     g_wFreq = wFreq;
//                     g_wFsam = (1000000000+wFreq*DFT_DOTNUM/2)/(wFreq*DFT_DOTNUM);
//                 }
//                 else
//                 {
//                     g_wFreq = 0;
//                     g_wFsam = 8333;
//                 }
//             }
//         }
// 
//         fTold = fTnew;
//         wTimerF = 15;
//     }
//     else
//     {
//         if(wTimerFRest)
//         {
//             wTimerFRest--;
//             if(wTimerFRest==0)
//             {
//                 g_wFreq = 0;
//                 g_wFsam = 5000;
//             }
//         }
//     }
//     nROld = nR;
// }

WORD g_wFreqIndexOld = 0xff;

WORD GetFreqIndex(void)
{
    if(g_dataUa.m_nData>315) return DFT_Ua;        // Ua小于33.33V
    else if(g_dataUb.m_nData>315) return DFT_Ub;
    else if(g_dataUc.m_nData>315) return DFT_Uc;
    else if(g_dataIa.m_nData>68) return DFT_Ia;     // 1A
    else if(g_dataIb.m_nData>68) return DFT_Ib;
    else if(g_dataIc.m_nData>68) return DFT_Ic;

    return 0xff;
}

void MyApp_OnTimerSample(WORD wIndex)
{
    static DWORD dwTold = 0, dwTnew = 0;
    static short nROld = 0;
    static WORD wTimerF = 15;
    static WORD wTimerFRest = 2400;
//     static WORD wSamTrace = 0;

    short nR;
    WORD wFreqIndex;

    WORD wIndexTmp;

    if(wTimerFRest)
    {
        wTimerFRest--;
    }
    
    if(wTimerFRest==0)
    {
        g_wFreq = 0;
        g_dwFsam = 6000L;//8333;     // 5000;
    }

//     if(g_analogData.wDataUa<1000)        // Ua小于33.33V
//     {
//         g_wFreq = 0;
//         g_wFsam = 8333;     // 5000;
//         return;
//     }
    wFreqIndex = GetFreqIndex();
    if(wFreqIndex!=g_wFreqIndexOld || wFreqIndex>=DFT_Uc)
    {
        g_wFreq = 0;
        g_dwFsam = 6000L;       // 8333;     // 5000;
        g_wFreqIndexOld = wFreqIndex;
        return;
    }

    wIndexTmp = (wIndex+1)%DFT_DOTNUM;
    
    nR = DFT_CalculateDFT1R((short*)&g_analogWave.wData[wFreqIndex][wIndexTmp]);
    if(wTimerF) wTimerF--;
    if(nROld<=0 && nR>=0 && nROld!=nR && wTimerF==0)        // 上升沿
    {
        DWORD dwT;
        WORD wFreq;
        WORD wDif = nR - nROld;
        dwTnew = g_dwSysTimerUs + (g_dwFsam*nR + (wDif>>1))/wDif;
//         dwT = dwTnew - dwTold;
        dwT = dwTold - dwTnew;

        if(dwT!=0)
        {
//             wFreq = (WORD)((1000000000 + (dwT>>1))/dwT);
            wFreq = (WORD)((720000000L + (dwT>>1))/dwT);
            wTimerFRest = 2400;
            if(wFreq<=7550 && wFreq>=3450)
            {
                g_wFreq = wFreq;
//              g_wFsam = (1000000000+wFreq*DFT_DOTNUM/2)/(wFreq*DFT_DOTNUM);
//                 g_wFsam = (WORD)((dwT+DFT_DOTNUM/2)/DFT_DOTNUM);
            }
            else
            {
                g_wFreq = 0;
            }
            if(wFreq<=7550 && wFreq>=4400)
            {
                //              g_wFsam = (1000000000+wFreq*DFT_DOTNUM/2)/(wFreq*DFT_DOTNUM);
                g_dwFsam = (dwT+DFT_DOTNUM/2)/DFT_DOTNUM;
            }
            else
            {
                g_dwFsam = 6000L;
            }
        }

        dwTold = dwTnew;
        wTimerF = 15;
    }
    nROld = nR;
}

void MyApp_OnWaveRecordEx(WORD wSwitchStatus,WORD wData1,WORD wData2,WORD wData3,WORD wData4,WORD wData5,WORD wData6,WORD wData7,WORD wData8)
{
    g_wWRData[0] = wData1;
    g_wWRData[1] = wData2;
    g_wWRData[2] = wData3;
    g_wWRData[3] = wData4;
    g_wWRData[4] = wData5;
    g_wWRData[5] = wData6;
    g_wWRData[6] = wSwitchStatus;
    WaveRecord_OnRecord();
}


