#include <Main.h>
#include "math.h"

DEVICEPARAM_IBCU2* g_pDeviceParam;
ANALOGDATA g_analogData;
ANALOGDATAEXT g_analogDataExt;
MyData g_dataIa;
MyData g_dataIb;
MyData g_dataIc;
// MyData g_dataIA;
// MyData g_dataIB;
// MyData g_dataIC;
// MyData g_data3I0;
MyData g_dataUa;
MyData g_dataUb;
MyData g_dataUc;
MyData g_dataUab;
MyData g_dataUbc;
MyData g_dataUca;
MyData g_dataF;

MyData g_dataP;
MyData g_dataQ;
MyData g_dataS;
MyData g_dataPF;

// MyAlarmGroup3 s_alarmgroupCTP;
MyAlarmGroup3 s_alarmgroupPT;
MyAlarm s_alarmKM;


// IM = 3413
// Ull = 3466
const REGULATE g_Ref[DFT_CHANNEL_HARD] = 
{
    { 2956, -1707},
    {-2956, -1707},
    {    0,  3413},
    { 3466,     0},
    { -1733, -3002},
    { -1733,  3002},
};


//===========================================================================
void MyApp_OnInitSubParam(void)
{
    g_pDeviceParam = (DEVICEPARAM_IBCU2*)&g_deviceParam.wReserved[0];
    MemoryClear((WORD*)&g_analogData,SIZEOFWORD(g_analogData));
    MemoryClear((WORD*)&g_analogDataExt,SIZEOFWORD(g_analogDataExt));
    g_pDeviceParam->wModePT = MODEPT_WYE;
    g_pDeviceParam->wToggleAlarmPT = TOGGLE_OFF;			// PT¶ÏÏß¸æ¾¯
    g_pDeviceParam->wScaleCT = 40;
    g_pDeviceParam->wScalePT = 100;
    g_pDeviceParam->wSLType = 1;

    g_deviceSetpoint.INSetpoint[0].wLinkIN = LINKIN_IN01;
    g_deviceSetpoint.INSetpoint[1].wLinkIN = LINKIN_IN02;
    g_deviceSetpoint.INSetpoint[2].wLinkIN = LINKIN_IN03;
    g_deviceSetpoint.INSetpoint[3].wLinkIN = LINKIN_IN04;
}

void MyApp_OnInitsub(void)
{
    EEPROM_ReadBlock(EEPROMADDR_ANALOGEXT1, NULL, (WORD*)&g_analogDataExt, SIZEOFWORD(g_analogDataExt));

// 	m_alarmgroupCTP.OnInit();
    Data_OnInit(&g_dataIa);
    Data_OnInit(&g_dataIb);
    Data_OnInit(&g_dataIc);

//     Data_OnInit(&g_dataIA);
// 	Data_OnInit(&g_dataIB);
// 	Data_OnInit(&g_dataIC);
// 	Data_OnInit(&g_data3I0);
// 	Data_OnInit(&g_data3I2);

	Data_OnInit(&g_dataUa);
	Data_OnInit(&g_dataUb);
	Data_OnInit(&g_dataUc);
	Data_OnInit(&g_dataUab);
	Data_OnInit(&g_dataUbc);
	Data_OnInit(&g_dataUca);
// 	Data_OnInit(&g_data3U0);
// 	Data_OnInit(&g_data3U2);
	Data_OnInit(&g_dataF);

    Data_OnInit(&g_dataP);
    Data_OnInit(&g_dataQ);
    Data_OnInit(&g_dataS);
    Data_OnInit(&g_dataPF);

// 	AlarmG_OnInit(&s_alarmgroupCTP);
	AlarmG_OnInit(&s_alarmgroupPT);
    Alarm_OnInit(&s_alarmKM);

// 	BreakerStatus_OnInit();

}

void MyApp_OnSetDataMetrics(void)
{
    WORD wScale2IM = SCALE2IM;
    WORD wScale2Uln= SCALE2ULN;

    DWORD dwScaleSecondary, dwScale;
    g_pDeviceParam = (DEVICEPARAM_IBCU2*)&g_deviceParam.wReserved[0];
    dwScaleSecondary = (DWORD)wScale2IM*wScale2Uln*3/100;
    dwScale = (DWORD)g_pDeviceParam->wScaleCT*(DWORD)g_pDeviceParam->wScalePT;

    Data_SetMetrics(&g_dataIa,wScale2IM,g_pDeviceParam->wScaleCT,"Ia","A");
    Data_SetMetrics(&g_dataIb,wScale2IM,g_pDeviceParam->wScaleCT,"Ib","A");
    Data_SetMetrics(&g_dataIc,wScale2IM,g_pDeviceParam->wScaleCT,"Ic","A");
//     Data_SetMetrics(&g_dataIA,wScale2IP,g_pDeviceParam->wScaleCT,"IA","A");
//     Data_SetMetrics(&g_dataIB,wScale2IP,g_pDeviceParam->wScaleCT,"IB","A");
//     Data_SetMetrics(&g_dataIC,wScale2IP,g_pDeviceParam->wScaleCT,"IC","A");
//     Data_SetMetrics(&g_data3I0,wScale2IP,1,"3I0","A");
//     Data_SetMetrics(&g_data3I2,wScale2IP,1,"3I2","A");

    Data_SetMetrics(&g_dataUa,wScale2Uln,g_pDeviceParam->wScalePT,"Ua","V");
    Data_SetMetrics(&g_dataUb,wScale2Uln,g_pDeviceParam->wScalePT,"Ub","V");
    Data_SetMetrics(&g_dataUc,wScale2Uln,g_pDeviceParam->wScalePT,"Uc","V");
    Data_SetMetrics(&g_dataUab,wScale2Uln,g_pDeviceParam->wScalePT,"Uab","V");
    Data_SetMetrics(&g_dataUbc,wScale2Uln,g_pDeviceParam->wScalePT,"Ubc","V");
    Data_SetMetrics(&g_dataUca,wScale2Uln,g_pDeviceParam->wScalePT,"Uca","V");

// 	Data_SetMetrics(&g_data3U0,wScale2Uln,1,"3U0","V");
// 	Data_SetMetrics(&g_data3U2,wScale2Uln,1,"3U2","V");
    Data_SetMetrics(&g_dataF, 4096,1,"Freq","Hz");

    Data_SetMetrics(&g_dataP,dwScaleSecondary,dwScale,"P","W");
    Data_SetMetrics(&g_dataQ,dwScaleSecondary,dwScale,"Q","Var");
    Data_SetMetrics(&g_dataS,dwScaleSecondary,dwScale,"S","VA");
    Data_SetMetrics(&g_dataPF, 410,1,"PF","%");
}

void MyApp_OnResetSubDevice(void)
{
    AlarmG_OnReset(&s_alarmgroupPT);
    Alarm_OnReset(&s_alarmKM);
}

void MyApp_OnCalculateData(void)
{
    Measure_SetData(DFT_Ia,&g_dataIa);
    Measure_SetData(DFT_Ib,&g_dataIb);
    Measure_SetData(DFT_Ic,&g_dataIc);
// 	Measure_SetData(DFT_IA,&g_dataIA);
// 	Measure_SetData(DFT_IB,&g_dataIB);
// 	Measure_SetData(DFT_IC,&g_dataIC);
// 	Measure_SetData(DFT_3I0,&g_data3I0);

	Measure_SetData(DFT_Ua,&g_dataUa);
	Measure_SetData(DFT_Ub,&g_dataUb);
	Measure_SetData(DFT_Uc,&g_dataUc);

	Data_SetData2(&g_dataUab,g_dataUa.m_nR-g_dataUb.m_nR,g_dataUa.m_nX-g_dataUb.m_nX);
	Data_SetData2(&g_dataUbc,g_dataUb.m_nR-g_dataUc.m_nR,g_dataUb.m_nX-g_dataUc.m_nX);
	Data_SetData2(&g_dataUca,g_dataUc.m_nR-g_dataUa.m_nR,g_dataUc.m_nX-g_dataUa.m_nX);

    PQ_Calculate1(&g_dataIa,&g_dataIb,&g_dataIc,&g_dataUa,&g_dataUb,&g_dataUc,SCALE2IM,SCALE2ULN,TRUE);
//    PQ_Calculate2(&g_dataIa, &g_dataIc, &g_dataUab, &g_dataUbc, SCALE2IM, SCALE2ULN);
    Data_SetData1(&g_dataP, g_nPabc);
    Data_SetData1(&g_dataQ, g_nQabc);
    g_nPFabc = g_nPFabc/10;
    Data_SetData1(&g_dataPF, g_nPFabc);
    {
        short nS = (short)GetSqrtX(g_nPabc, g_nQabc);
        Data_SetData1(&g_dataS, nS);
    }

    Data_SetData1(&g_dataF,g_wFreq);

//     SETBIT(g_dataP.m_nData<0,g_deviceInfo.wDeviceStatus2,DS2_DirectP);
//     SETBIT(g_dataQ.m_nData<0,g_deviceInfo.wDeviceStatus2,DS2_DirectQ);
    g_analogDataExt.dwDataPhImpW10ms += g_dwPhImpW10ms;
    g_analogDataExt.dwDataQhImpW10ms += g_dwQhImpW10ms;
    g_analogDataExt.dwDataPhExpW10ms += g_dwPhExpW10ms;
    g_analogDataExt.dwDataQhExpW10ms += g_dwQhExpW10ms;
//     if(g_analogDataExt.dwDataPhImpW10ms>=36000000L)
//     {
//         g_analogDataExt.dwDataPhImp++;
//         g_analogDataExt.dwDataPhImpW10ms -= 36000000L;
//     }
//     if(g_analogDataExt.dwDataQhImpW10ms>=36000000L)
//     {
//         g_analogDataExt.dwDataQhImp++;
//         g_analogDataExt.dwDataQhImpW10ms -= 36000000L;
//     }
//     if(g_analogDataExt.dwDataPhExpW10ms>=36000000L)
//     {
//         g_analogDataExt.dwDataPhExp++;
//         g_analogDataExt.dwDataPhExpW10ms -= 36000000L;
//     }
//     if(g_analogDataExt.dwDataQhExpW10ms>=36000000L)
//     {
//         g_analogDataExt.dwDataQhExp++;
//         g_analogDataExt.dwDataQhExpW10ms -= 36000000L;
//     }
    if(g_analogDataExt.dwDataPhImpW10ms>=3600000000L)
    {
        g_analogDataExt.dwDataPhImp++;
        if(g_analogDataExt.dwDataPhImp>999999999) g_analogDataExt.dwDataPhImp = 0;
        g_analogDataExt.dwDataPhImpW10ms -= 3600000000L;
    }
    if(g_analogDataExt.dwDataQhImpW10ms>=3600000000L)
    {
        g_analogDataExt.dwDataQhImp++;
        if(g_analogDataExt.dwDataQhImp>999999999) g_analogDataExt.dwDataQhImp = 0;
        g_analogDataExt.dwDataQhImpW10ms -= 3600000000L;
    }
    if(g_analogDataExt.dwDataPhExpW10ms>=3600000000L)
    {
        g_analogDataExt.dwDataPhExp++;
        if(g_analogDataExt.dwDataPhExp>999999999) g_analogDataExt.dwDataPhExp = 0;
        g_analogDataExt.dwDataPhExpW10ms -= 3600000000L;
    }
    if(g_analogDataExt.dwDataQhExpW10ms>=3600000000L)
    {
        g_analogDataExt.dwDataQhExp++;
        if(g_analogDataExt.dwDataQhExp>999999999) g_analogDataExt.dwDataQhExp = 0;
        g_analogDataExt.dwDataQhExpW10ms -= 3600000000L;
    }
}

BOOL MyApp_IsPTBreak(void)
{
	return AlarmG_IsAlarmStarted(&s_alarmgroupPT);
}

void MyApp_OnAlarmDetect(void)
{
//     BOOL bAlarm;
// 	WORD wDataIMax;
// 	wDataIMax = GetMax(g_dataIA.m_nData,g_dataIB.m_nData,g_dataIC.m_nData);
// 	AlarmGPT_ExeDetect(&s_alarmgroupPT,&g_dataUa,&g_dataUb,&g_dataUc,&g_dataUab,&g_dataUbc,&g_dataUca,g_pDeviceParam->wModePT,wDataIMax,g_pDeviceParam->wToggleAlarmPT,EVENTCODE_ALARMPT3);
// 
//     bAlarm = FALSE;
//     if((g_deviceInfo.wSwitchStatus1&0x0600)==0x00) bAlarm = TRUE;
//     Alarm_ExeDetect(&s_alarmKM, TOGGLE_ON, 1500, bAlarm,EVENTCODE_ALARMKM);
// 
// 	SETBIT(AlarmG_IsAlarmed(&s_alarmgroupPT),g_deviceInfo.wDeviceStatus2,DS2_AlarmPT);
// 	SETBIT(s_alarmKM.m_bAlarmed,g_deviceInfo.wDeviceStatus2,DS2_AlarmKM);
}

short MyApp_GetAng(MyData* pData, float fAngOffset)
{
    short nAng;
    float fAng = atan2(pData->m_nX, pData->m_nR);
    fAng = fAng - fAngOffset;
    fAng = 572.9578f*fAng; // 1800.0f/3.1415926f*fAng;
    nAng = (fAng>0)?(short)(fAng+0.5f):(short)(fAng-0.5f);
    while(nAng<=-1800) nAng += 3600;
    while(nAng>1800) nAng -= 3600;
    return nAng;
}

short MyApp_GetDataSecondary(MyData* pData, short nData, BOOL bSignedType)
{
    DWORD dwDataSecondary;
//     short nData = pData->m_nDataAvg;
    dwDataSecondary = (DWORD)((nData>=0)?nData:(-nData));
    dwDataSecondary = (dwDataSecondary*pData->m_dwScaleSecondary+2048L)/4096L;
    nData = dwDataSecondary;
    if(bSignedType) nData = (pData->m_nDataAvg>=0)?nData:-nData;

    return nData;
}

void MyApp_OnRefreshData(void)
{
    WORD wFreq = 0;

    EEPROM_WriteBlock(EEPROMADDR_ANALOGEXT1, NULL, (WORD*)&g_analogDataExt,SIZEOFWORD(g_analogDataExt));

    Data_RefreshData(&g_dataIa,FALSE);
    Data_RefreshData(&g_dataIb,FALSE);
    Data_RefreshData(&g_dataIc,FALSE);
    Data_RefreshData(&g_dataUa,FALSE);
    Data_RefreshData(&g_dataUb,FALSE);
    Data_RefreshData(&g_dataUc,FALSE);
    Data_RefreshData(&g_dataUab,FALSE);
    Data_RefreshData(&g_dataUbc,FALSE);
    Data_RefreshData(&g_dataUca,FALSE);
    Data_RefreshData(&g_dataP,TRUE);
    Data_RefreshData(&g_dataQ,TRUE);
    Data_RefreshData(&g_dataS,TRUE);
    Data_RefreshData(&g_dataPF,TRUE);

    g_analogData.wDataIa = MyApp_GetDataSecondary(&g_dataIa, g_dataIa.m_nDataAvg, FALSE);
    g_analogData.wDataIb = MyApp_GetDataSecondary(&g_dataIb, g_dataIb.m_nDataAvg, FALSE);
    g_analogData.wDataIc = MyApp_GetDataSecondary(&g_dataIc, g_dataIc.m_nDataAvg, FALSE);
    g_analogData.wDataUa = MyApp_GetDataSecondary(&g_dataUa, g_dataUa.m_nDataAvg, FALSE);
    g_analogData.wDataUb = MyApp_GetDataSecondary(&g_dataUb, g_dataUb.m_nDataAvg, FALSE);
    g_analogData.wDataUc = MyApp_GetDataSecondary(&g_dataUc, g_dataUc.m_nDataAvg, FALSE);
    g_analogData.wDataUab = MyApp_GetDataSecondary(&g_dataUab, g_dataUab.m_nDataAvg, FALSE);
    g_analogData.wDataUbc = MyApp_GetDataSecondary(&g_dataUbc, g_dataUbc.m_nDataAvg, FALSE);
    g_analogData.wDataUca = MyApp_GetDataSecondary(&g_dataUca, g_dataUca.m_nDataAvg, FALSE);
    g_analogData.nDataP = MyApp_GetDataSecondary(&g_dataP, g_dataP.m_nDataAvg, TRUE);
    g_analogData.nDataQ = MyApp_GetDataSecondary(&g_dataQ, g_dataQ.m_nDataAvg, TRUE);
    g_analogData.nDataS = MyApp_GetDataSecondary(&g_dataS, g_dataS.m_nDataAvg, TRUE);
    g_analogData.nDataPF = MyApp_GetDataSecondary(&g_dataPF, g_dataPF.m_nDataAvg, TRUE);

    
    wFreq = (WORD)Data_RefreshData(&g_dataF,FALSE);
    if(wFreq>=7500 || wFreq<=4500) wFreq = 0;
    g_analogData.wDataF = wFreq;

    {
        float fAngUa;
        g_analogData.nAngUa = 0;
        if(g_dataUa.m_nData>315)
        {
            fAngUa = atan2(g_dataUa.m_nX, g_dataUa.m_nR);
            if(g_dataIa.m_nData>68) g_analogData.nAngIa = MyApp_GetAng(&g_dataIa, fAngUa);
            else g_analogData.nAngIa = 0;
            
            if(g_dataIb.m_nData>68) g_analogData.nAngIb = MyApp_GetAng(&g_dataIb, fAngUa);
            else g_analogData.nAngIb = 0;
            
            if(g_dataIc.m_nData>68) g_analogData.nAngIc = MyApp_GetAng(&g_dataIc, fAngUa);
            else g_analogData.nAngIc = 0;

            if(g_dataUb.m_nData>315) g_analogData.nAngUb = MyApp_GetAng(&g_dataUb, fAngUa);
            else g_analogData.nAngUb = 0;

            if(g_dataUc.m_nData>315) g_analogData.nAngUc = MyApp_GetAng(&g_dataUc, fAngUa);
            else g_analogData.nAngUc = 0;

            if(g_dataUab.m_nData>315) g_analogData.nAngUab = MyApp_GetAng(&g_dataUab, fAngUa);
            else g_analogData.nAngUab = 0;

            if(g_dataUbc.m_nData>315) g_analogData.nAngUbc = MyApp_GetAng(&g_dataUbc, fAngUa);
            else g_analogData.nAngUbc = 0;

            if(g_dataUca.m_nData>315) g_analogData.nAngUca = MyApp_GetAng(&g_dataUca, fAngUa);
            else g_analogData.nAngUca = 0;
        }
        else
        {
            g_analogData.nAngIa = 0;
            g_analogData.nAngIb = 0;
            g_analogData.nAngIc = 0;
//             g_analogData.wAngUa = 0;
            g_analogData.nAngUb = 0;
            g_analogData.nAngUc = 0;
            g_analogData.nAngUab = 0;
            g_analogData.nAngUbc = 0;
            g_analogData.nAngUca = 0;
        }
    }
}

void MyApp_OnWaveRecord(WORD wCountAD)
{
//     WORD wData3I0 = 2000;
// #ifdef DFT_3I0
//     wData3I0 = g_analogWave.wData[DFT_3I0][wCountAD];
// #endif
    MyApp_OnWaveRecordEx(g_deviceInfo.wSwitchStatus1,
        g_analogWave.wData[DFT_Ua][wCountAD],
        g_analogWave.wData[DFT_Ub][wCountAD],
        g_analogWave.wData[DFT_Uc][wCountAD],
        g_analogWave.wData[DFT_Ia][wCountAD],
        g_analogWave.wData[DFT_Ib][wCountAD],
        g_analogWave.wData[DFT_Ic][wCountAD],
        2000,
        2000);
}

const long c_lKI = 0.0690527f*SCALE2IM+0.5f;    //(1.4142f*SCALE2IM)/2048*100;
const long c_lKU = 0.0690527f*SCALE2ULN+0.5f;    //(1.4142f*SCALE2ULN)/2048*100;

void MyApp_SetWaveRecordK(WAVERECORD* pWaveRecord)
{
    short i;
    REGULATE* pReg[6];
    long lKUI[6];
    pReg[0] = &g_regulateSet.regulate[DFT_Ua];
    pReg[1] = &g_regulateSet.regulate[DFT_Ub];
    pReg[2] = &g_regulateSet.regulate[DFT_Uc];
    pReg[3] = &g_regulateSet.regulate[DFT_Ia];
    pReg[4] = &g_regulateSet.regulate[DFT_Ib];
    pReg[5] = &g_regulateSet.regulate[DFT_Ic];
    
    lKUI[0] = lKUI[1] = lKUI[2] = c_lKU;
    lKUI[3] = lKUI[4] = lKUI[5] = c_lKI;
    
    for(i=0;i<6;++i)
    {
        long lK = GetSqrtX(pReg[i]->nRegulateR, pReg[i]->nRegulateX);
        lK = (lK*lKUI[i]+5000L)/10000L;
        pWaveRecord->nK[i] = (short)lK;
    }
    pWaveRecord->nK[6] = 10000;
}
