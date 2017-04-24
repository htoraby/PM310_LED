#include <Main.h>

DEVICESETPOINT g_deviceSetpoint;			// ���븡�㶨ֵ

WORD g_wProtectAct[PROTECT_MAX1];						// ����������־;
WORD g_wProtectActIN[INSETPOINTNUM];		// ����������������־;
DWORD g_dwProtectActed;						// ����������־(�Ա���),�븴������;
WORD g_wProtectActedIN;						// ����������������־(�Ա���),�븴������;
WORD g_wProtectCloseFlag;					// �������������բ��־;
WORD g_wProtectOpenFlag;					// ��������������բ��־;
WORD g_wSetpointAreaFlag;					// ǿ���л���ֵ����־;

BOOL g_bProtectAct = FALSE;                 // �ܵı���������־

//-----------------------------------------------------------------------------
void Protect_OnInit1(void)
{
	MemoryClear(g_wProtectAct,PROTECT_MAX1);
	MemoryClear(g_wProtectActIN,INSETPOINTNUM);
	g_dwProtectActed = 0x00000000;
	g_wProtectActedIN = 0x00000000;
	g_wSetpointAreaFlag = 0x0000;
	g_wProtectCloseFlag = 0x0000;
	g_wProtectOpenFlag = 0x0000;
}

void Protect_OnTimer1ms(void)
{
#ifdef SWITCH_COUNT
	WORD i;
	if(g_dwChangtoON1!=g_dwChangtoON2) return;
	for(i=0;i<INSETPOINTNUM;i++)
	{
		if(g_deviceSetpoint.INSetpoint[i].wToggle==PROTECTTOG_OFF) continue;
		if(g_deviceSetpoint.INSetpoint[i].wLinkIN==LINKIN_NULL) continue;
		if((g_dwChangtoON1&(1L<<(g_deviceSetpoint.INSetpoint[i].wLinkIN-1)))==0) continue;
		Protect_SetProtectAct(PROTECT_IN1+i,0,0x3333);
	}
	if(g_dwChangtoON1&&(g_dwChangtoON1==g_dwChangtoON2))
	{
		MyApp_OnRelayOut();
		g_dwChangtoON1 = 0;				// �����������1��־
		g_dwChangtoON2 = 0;				// �����������2��־
	}
#endif
}

void Protect_OnTimer10ms(void)
{
    short i;
    for(i=0;i<PROTECT_MAX1;i++)
    {
        if(g_wProtectAct[i]==0xaaaa) g_wProtectAct[i] = 1;
        else g_wProtectAct[i] = 0;
    }
    for(i=0;i<INSETPOINTNUM;i++)
    {
        if(g_wProtectActIN[i]==0xaaaa) g_wProtectActIN[i] = 1;
        else g_wProtectActIN[i] = 0;
    }
    g_bProtectAct=Protect_GetAct();
	g_wProtectCloseFlag = 0x0000;
	g_wProtectOpenFlag = 0x0000;
	Protect_Run();
	g_wSetpointAreaFlag = 0x0000;
}

void Protect_SetProtectAct(WORD wProtectIndexExt,WORD wActData,WORD wActMode)
{
// 	WORD wConfig;
	WORD wProtectAct;
	WORD wProtectIndex;
	WORD wConfig = 0;
    wProtectIndex = wProtectIndexExt&0x003f;
	if(wProtectIndex>=PROTECT_MAX) return;
	if(wProtectIndex<PROTECT_MAX1)
    {
        wProtectAct = g_wProtectAct[wProtectIndex];
        wConfig = g_deviceSetpoint.wConfig[wProtectIndex];
    }
    else if(wProtectIndex<PROTECT_MAX)
    {
        wProtectAct = g_wProtectActIN[wProtectIndex-PROTECT_IN1];
        wConfig = g_deviceSetpoint.INSetpoint[wProtectIndex-PROTECT_IN1].wConfig;
    }

    if(wConfig==0)
    {
        SetAlarmedFlag;
        if(wProtectAct==0)
        {
            PROTECTACTDATAINFO protectActDataInfo;
            const PROTECTACTINFO* pprotectActInfo;
            protectActDataInfo.pszDataName = 0;
            protectActDataInfo.pszUnitage = 0;
            protectActDataInfo.wFormat = 0x42;
            protectActDataInfo.dwActData = 0;
            pprotectActInfo = c_protectActInfo;
            MyHMI_GetProtectActDataInfo(pprotectActInfo[wProtectIndex].wProtectAct,wProtectIndexExt,wActData,&protectActDataInfo);
            Event_AddEvent(EVENTTYPE_ALARMED,EVENTCODE_PROTECT+wProtectIndex,(WORD)protectActDataInfo.dwActData);
        }
    }
    else
    {
        if(wActMode==0x3333) g_wProtectOpenFlag = 0xaaaa;
        else if(wActMode==0x5555) g_wProtectCloseFlag = 0xaaaa;
        SetTrippedFlag;
        Protect_OnActTripped(wProtectIndex);
        if(wProtectAct==0)
        {
            PROTECTACTDATAINFO protectActDataInfo;
            const PROTECTACTINFO* pprotectActInfo;
            protectActDataInfo.pszDataName = 0;
            protectActDataInfo.pszUnitage = 0;
            protectActDataInfo.wFormat = 0x42;
            protectActDataInfo.dwActData = 0;
            pprotectActInfo = c_protectActInfo;
            MyHMI_GetProtectActDataInfo(pprotectActInfo[wProtectIndex].wProtectAct,wProtectIndexExt,wActData,&protectActDataInfo);
//             Event_AddEvent(EVENTTYPE_TRIPPED,EVENTCODE_PROTECT+wProtectIndex,wActData);
            Event_AddEvent(EVENTTYPE_ALARMED,EVENTCODE_PROTECT+wProtectIndex,(WORD)protectActDataInfo.dwActData);
        }
    }
    if(wProtectIndex<PROTECT_MAX1)
    {
        g_wProtectAct[wProtectIndex] = 0xaaaa;
        g_dwProtectActed |= 1L<<wProtectIndex;
    }
    else if(wProtectIndex<PROTECT_MAX)
    {
        g_wProtectActIN[wProtectIndex-PROTECT_IN1] = 0xaaaa;
        g_wProtectActedIN |= 1L<<(wProtectIndex-PROTECT_IN1);
    }
    {
        BOOL bProtectAct = Protect_GetAct();
        if(g_bProtectAct==FALSE && bProtectAct==TRUE)               // ���ϴ��޵���ʱ¼�������ϲ���ʧ����¼��
        {
            WaveRecord_FreezeRecord();
        }
        g_bProtectAct = bProtectAct;
    }
}

WORD Protect_ProtectXGE(WORD wProtectIndexExt,WORD wData,WORD wTime,WORD wDataSet,WORD wTimeSet,BOOL bLock)
{
//     WORD wSetFX = (WORD)((DWORD)wDataSet*97L/100L);
// 	if(bLock==TRUE)
// 	{
// // 		if(wTime) wTime--;
// 		return wTime;
// 	}
// 	if(wTimeSet<3) wTimeSet = 3;
//     if(wTime<wTimeSet)
//     {
//         if(wData>wDataSet)
//         {
//             wTime++;
//             if(wTime>=wTimeSet)
//             {
//                 wTime = wTimeSet;
//                 Protect_SetProtectAct(wProtectIndexExt,wData,0x3333);
//             }
//         }
//         else wTime = 0;
//     }
//     else
//     {
//         if(wData>wSetFX)
//         {
//             wTime++;
//             if(wTime>=wTimeSet)
//             {
//                 wTime = wTimeSet;
//                 Protect_SetProtectAct(wProtectIndexExt,wData,0x3333);
//             }
//         }
//         else
//         {
//             wTime = 0;
//         }
//     }
    if(bLock==TRUE)
    {
        if(wTime) wTime--;
        return wTime;
    }
    if(wTimeSet<3) wTimeSet = 3;

    if(wData>wDataSet)
    {
        wTime++;
        if(wTime>=wTimeSet)
        {
            wTime = wTimeSet;
            Protect_SetProtectAct(wProtectIndexExt,wData,0x3333);
        }
    }
    else if(wData<(wDataSet>>1)) wTime = 0;
    else if(wTime) wTime--;
    return wTime;
}

WORD Protect_ProtectXLE(WORD wProtectIndexExt,WORD wData,WORD wTime,WORD wDataSet,WORD wTimeSet,BOOL bLock)
{
//     WORD wSetFX = (WORD)((DWORD)wDataSet*102L/100L);
// 	if(bLock==TRUE)
// 	{
// // 		if(wTime) wTime--;
// 		return wTime;
// 	}
// 	if(wTimeSet<3) wTimeSet = 3;
//     if(wTime<wTimeSet)
//     {
//         if(wData<wDataSet)
//         {
//             wTime++;
//             if(wTime>=wTimeSet)
//             {
//                 wTime = wTimeSet;
//                 Protect_SetProtectAct(wProtectIndexExt,wData,0x3333);
//             }
//         }
//         else wTime = 0;
//     }
//     else
//     {
//         if(wData<wSetFX)
//         {
//             wTime++;
//             if(wTime>=wTimeSet)
//             {
//                 wTime = wTimeSet;
//                 Protect_SetProtectAct(wProtectIndexExt,wData,0x3333);
//             }
//         }
//         else
//         {
//             wTime = 0;
//         }
//     }

	if(bLock==TRUE)
	{
		if(wTime) wTime--;
		return wTime;
	}
	if(wTimeSet<3) wTimeSet = 3;
    if(wData<wDataSet)
    {
        wTime++;
        if(wTime>=wTimeSet)
        {
            wTime = wTimeSet;
            Protect_SetProtectAct(wProtectIndexExt,wData,0x3333);
        }
    }
    else if(wData>(wDataSet<<1)) wTime = 0;
	else if(wTime) wTime--;

    return wTime;
}

BOOL Protect_GetAct(void)
{
    short i;
    BOOL bAct = FALSE;
    for(i=0;i<PROTECT_MAX1;++i)
    {
        if(g_wProtectAct[i])
        {
            bAct = TRUE;
            break;
        }
    }

    for(i=0;i<INSETPOINTNUM;++i)
    {
        if(g_wProtectActIN[i])
        {
            bAct = TRUE;
            break;
        }
    }
    return bAct;
}



