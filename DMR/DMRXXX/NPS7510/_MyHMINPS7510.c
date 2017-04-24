#include <Main.h>

MyOutput g_lightOpened;
MyOutput g_lightClosed;

//----------------------------------------------------
const char c_szSCIBaudRate[3][6] = 
{
    " 2400"," 4800"," 9600"
};

// const char* g_pszInName[SWITCH_COUNT] =
// {
//     "闭锁重合闸/重瓦斯",
//     "弹簧未储能",
//     "遥信1/轻瓦斯",
//     "遥信2/温高跳闸",
//     "遥信3/温高告警",
//     "小车工作位置",
//     "小车试验位置",
//     "接地刀闸合位",
//     "远方/就地",
//     "HWJ",
//     "TWJ",
//     "KKJ",
// };

// const char* g_pszINSETName[INSETPOINTNUM] =
// {
//     "重瓦斯",
//     "轻瓦斯",
//     "温高跳闸",
//     "温高告警",
// };

//     AddINChannel("HWJ", "分位", "合位", 0);11
//     AddINChannel("TWJ", "分位", "合位", 0);12
//     AddINChannel("KKJ", "分位", "合位", 0);13

const char* g_pszInName[SWITCH_COUNT] =
{
    "DI1",
    "DI2",
    "DI3",
    "DI4",
};

const char* g_pszDoName[RELAYKH_COUNT] =
{
    "Do1",
    "Do2",
};


//----------------------------------------------------
void MyHMI_OnInitSub(void)
{
    Output_OnInit(&g_lightOpened);
    Output_OnInit(&g_lightClosed);
    MyHMI_TestLights();
}

void MyHMI_OnTimer10msSub(void)
{
    Output_SetLevel(&g_lightOpened,(g_deviceInfo.wSwitchStatus1&0x0400)?STATUS_ON:STATUS_OFF);
    Output_SetLevel(&g_lightClosed,(g_deviceInfo.wSwitchStatus1&0x0200)?STATUS_ON:STATUS_OFF);
    Output_OnTimer10ms(&g_lightOpened);
    Output_OnTimer10ms(&g_lightClosed);
}

char* MyHMI_GetEventTextSub(EVENT* pEvent)
{
    char* pszAlarmMsg = NULL;
    switch(pEvent->wCode)
    {
    case EVENTCODE_ALARMPT3: pszAlarmMsg = "三相PT断线"; break;
    case EVENTCODE_ALARMPT2: pszAlarmMsg = "两相PT断线"; break;
    case EVENTCODE_ALARMPT1: pszAlarmMsg = "单相PT断线"; break;
    case EVENTCODE_ALARMKM: pszAlarmMsg = "控制回路断线"; break;
    }
    if(pszAlarmMsg)
    {
    MyHMI_AddEventText(pszAlarmMsg);
    if(pEvent->wData==0) MyHMI_AddEventText(MULTITEXT("恢复"," RESET"));
    }
    return g_szEventText;
}

static void SetDataMetricsPhQh(void)
{
    EditG_SetEditDataMetricsReal(0,999999999,0x91);
}

void MyHMI_GetEditMetricsSub(WORD* pData)
{
    if(pData==&g_pDeviceParam->wToggleAlarmPT) EditG_SetEditEnumMetricsTog();
    if(pData==&g_pDeviceParam->wModePT) EditG_SetEditEnumMetricsTog();
    if(pData==&g_pDeviceParam->wScaleCT) EditG_SetEditDataMetricsInteger(1,9999,FALSE);
    if(pData==&g_pDeviceParam->wScalePT) EditG_SetEditDataMetricsInteger(1,9999,FALSE);
    if(pData==&g_pDeviceParam->wSLType) EditG_SetEditDataMetricsInteger(1,4,FALSE);
    if(pData==(WORD*)&g_analogDataExt.dwDataPhImp) SetDataMetricsPhQh();
    if(pData==(WORD*)&g_analogDataExt.dwDataQhImp) SetDataMetricsPhQh();
    if(pData==(WORD*)&g_analogDataExt.dwDataPhExp) SetDataMetricsPhQh();
    if(pData==(WORD*)&g_analogDataExt.dwDataQhExp) SetDataMetricsPhQh();
}

void MyHMI_GetProtectActDataInfo(WORD wProtectAct,WORD wProtectIndexExt,WORD wActData,PROTECTACTDATAINFO* pProtectActDataInfo)
{
    pProtectActDataInfo->wFormat = 0x40;
    switch(wProtectAct)
    {
    case PROTECTACT_IP:
        pProtectActDataInfo->pszDataName = (char*)"I";
        pProtectActDataInfo->pszUnitage = (char*)"A";
        pProtectActDataInfo->wFormat = pProtectActDataInfo->wFormat | (g_dataIa.m_wFormatSecondary&0x0f);
        pProtectActDataInfo->dwActData = MyApp_GetDataSecondary(&g_dataIa, wActData, FALSE); // Data_GetValueSecondaryFix2(&g_dataIa,wActData);
        break;
    case PROTECTACT_U:
        pProtectActDataInfo->pszDataName = (char*)"U";
        pProtectActDataInfo->pszUnitage = (char*)"V";
        pProtectActDataInfo->wFormat = pProtectActDataInfo->wFormat | (g_dataUa.m_wFormatSecondary&0x0f);
        pProtectActDataInfo->dwActData = MyApp_GetDataSecondary(&g_dataUa, wActData, FALSE);    // Data_GetValueSecondaryFix2(&g_dataUa,wActData);
        break;
// 	case PROTECTACT_3I0:
// 		pProtectActDataInfo->pszDataName = (char*)"3I0";
// 		pProtectActDataInfo->pszUnitage = (char*)"A";
// 		pProtectActDataInfo->dwActData = Data_GetValueSecondaryFix2(&g_data3I0,wActData);
// 		break;
    }
}

DWORD DataConver(short nData)
{
    DWORD dwData = (DWORD)((nData>=0)?nData:(-nData));
    dwData += (nData<0)?0xc0000000:0x80000000;
    return dwData;
}

void MyHMI_AutoLCDDataOutSub(WORD wIndex)
{
    MyData* pData = NULL;
    BOOL bDataPrimary = FALSE;
    DWORD dwData = 0xffffffff;
    WORD wFormat = 0x52;
    switch(wIndex)
    {
    case INDEX_1Ia: pData = &g_dataIa; bDataPrimary = TRUE; break;
    case INDEX_1Ib: pData = &g_dataIb; bDataPrimary = TRUE; break;
    case INDEX_1Ic: pData = &g_dataIc; bDataPrimary = TRUE; break;
    case INDEX_1Ua: pData = &g_dataUa; bDataPrimary = TRUE; break;
    case INDEX_1Ub: pData = &g_dataUb; bDataPrimary = TRUE; break;
    case INDEX_1Uc: pData = &g_dataUc; bDataPrimary = TRUE; break;
    case INDEX_1Uab: pData = &g_dataUab; bDataPrimary = TRUE; break;
    case INDEX_1Ubc: pData = &g_dataUbc; bDataPrimary = TRUE; break;
    case INDEX_1Uca: pData = &g_dataUca; bDataPrimary = TRUE; break;
    case INDEX_1P: pData = &g_dataP; bDataPrimary = TRUE; break;
    case INDEX_1Q: pData = &g_dataQ; bDataPrimary = TRUE; break;
    case INDEX_1S: pData = &g_dataS; bDataPrimary = TRUE; break;
    case INDEX_2P: pData = &g_dataP; break;
    case INDEX_2Q: pData = &g_dataQ; break;
    case INDEX_2S: pData = &g_dataS; break;
    case INDEX_PF: pData = &g_dataPF; break;
    case INDEX_2Ia: pData = &g_dataIa; break;
    case INDEX_2Ib: pData = &g_dataIb; break;
    case INDEX_2Ic: pData = &g_dataIc; break;
//     case INDEX_2IA: pData = &g_dataIA; break;
//     case INDEX_2IB: pData = &g_dataIB; break;
//     case INDEX_2IC: pData = &g_dataIC; break;
    case INDEX_2Ua: pData = &g_dataUa; break;
    case INDEX_2Ub: pData = &g_dataUb; break;
    case INDEX_2Uc: pData = &g_dataUc; break;
    case INDEX_2Uab: pData = &g_dataUab; break;
    case INDEX_2Ubc: pData = &g_dataUbc; break;
    case INDEX_2Uca: pData = &g_dataUca; break;
//     case INDEX_23I0: pData = &g_data3I0; break;
    case INDEX_AngIa: LCD_AutoRealOut(DataConver(g_analogData.nAngIa), 0x41); break;
    case INDEX_AngIb: LCD_AutoRealOut(DataConver(g_analogData.nAngIb), 0x41); break;
    case INDEX_AngIc: LCD_AutoRealOut(DataConver(g_analogData.nAngIc), 0x41); break;
    case INDEX_AngUa: LCD_AutoRealOut(DataConver(g_analogData.nAngUa), 0x41); break;
    case INDEX_AngUb: LCD_AutoRealOut(DataConver(g_analogData.nAngUb), 0x41); break;
    case INDEX_AngUc: LCD_AutoRealOut(DataConver(g_analogData.nAngUc), 0x41); break;
    case INDEX_AngUab: LCD_AutoRealOut(DataConver(g_analogData.nAngUab), 0x41); break;
    case INDEX_AngUbc: LCD_AutoRealOut(DataConver(g_analogData.nAngUbc), 0x41); break;
    case INDEX_AngUca: LCD_AutoRealOut(DataConver(g_analogData.nAngUca), 0x41); break;
    case INDEX_F:
        pData = &g_dataF;
        if(g_dataF.m_nDataAvg>=7500 || g_dataF.m_nDataAvg<4500)
        {
            LCD_AutoRealOut(0, pData->m_wFormatSecondary);
            pData = NULL;
        }
        break;
    case INDEX_PARAM_ALARMPT: EditG_AddEditEnumMul(&g_pDeviceParam->wToggleAlarmPT); break;
    case INDEX_PARAM_MODEPT: EditG_AddEditEnumMul(&g_pDeviceParam->wModePT); break;
    case INDEX_ALARMED_PT: LCD_AutoOutALM_OK((WORD)(g_deviceInfo.wDeviceStatus2&DS2_AlarmPT)); break;
    case INDEX_PhI: dwData = (g_analogDataExt.dwDataPhImp); wFormat = 0x91; break;
    case INDEX_QhI: dwData = (g_analogDataExt.dwDataQhImp); wFormat = 0x91; break;
    case INDEX_PhE: dwData = (g_analogDataExt.dwDataPhExp); wFormat = 0x91; break;
    case INDEX_QhE: dwData = (g_analogDataExt.dwDataQhExp); wFormat = 0x91; break;
    case INDEX_PARAM_PhI: EditG_AddEditDataDWord(&g_analogDataExt.dwDataPhImp); break;
    case INDEX_PARAM_QhI: EditG_AddEditDataDWord(&g_analogDataExt.dwDataQhImp); break;
    case INDEX_PARAM_PhE: EditG_AddEditDataDWord(&g_analogDataExt.dwDataPhExp); break;
    case INDEX_PARAM_QhE: EditG_AddEditDataDWord(&g_analogDataExt.dwDataQhExp); break;
    }
    if(pData!=NULL)
    {
        dwData = (bDataPrimary)?pData->m_dwDataPrimary:pData->m_dwDataSecondary;
        wFormat = (bDataPrimary)?pData->m_wFormatPrimary:pData->m_wFormatSecondary;
    }
    if(dwData!=0xffffffff) LCD_AutoRealOut(dwData,wFormat);
}

void MyHMI_TestLightsSub(void)
{
    Output_EnterTest(&g_lightOpened,OUTPUT_TM_11,300);
    Output_EnterTest(&g_lightClosed,OUTPUT_TM_11,300);
}
