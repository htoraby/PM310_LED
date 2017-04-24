#include <Main.h>

//-----------------------------------------------------------------------------
void Page_OnRefreshPage(WORD wRefreshMode)
{
    LCD_SetTextAlignMode(TAMODE_LEFT);
    switch(Menu_GetIndexMenuMain())
    {
    case  0: Page_OnRefreshACData(wRefreshMode); break;
    case  1: Page_OnRefreshPageSwitch(wRefreshMode); break;
    case  2: Page_OnRefreshPageRTWave(wRefreshMode); break;
//     case  3: Page_OnRefreshPageVector(wRefreshMode); break;
    case  3: Page_OnRefreshPageEvent(wRefreshMode); break;
    case  4: Page_OnRefreshPageWaveRecord(wRefreshMode); break;
//     case  5: Page_OnRefreshSetpoint(wRefreshMode, FALSE); break;
    case  5: Page_OnRefreshInfo(wRefreshMode); break;
    case  6: Page_OnRefreshPageParamSetup(wRefreshMode); break;
    case  7: Page_OnRefreshPageLCDContrast(wRefreshMode); break;
    }
    LCD_SetTextAlignMode(TAMODE_LEFT);

    if(g_bScroll&&g_wPageCount>1) Page_DrawScroll(157,g_wPageCount,g_wPageCurSel);
}

void Page_OnRefreshACData(WORD wRefreshMode)
{
    switch(Menu_GetIndexMenuSub())
    {
    case 0: Page_OnRPPrimaryData(wRefreshMode); break;
    case 1: Page_OnRPMeansureData(wRefreshMode); break;
    case 2: Page_OnRPEngeryData(wRefreshMode); break;
//    case 2: Page_OnRPProtectData(wRefreshMode); break;
    }
}

void Page_OnRefreshPageParamSetup(WORD wRefreshMode)
{
    if(!wRefreshMode) return;
    switch(Menu_GetIndexMenuSub())
    {
    case  0:
        {
//             if(!wRefreshMode) return;
            Page_OnRefreshPageSetpoint((WORD*)g_pDeviceSetpoint,FALSE);
        }
        break;
    case  1:
        {
//             if(!wRefreshMode) return;
            Page_OnRefreshPageSetpoint((WORD*)g_pDeviceSetpoint,TRUE);
        }
        break;
    case  2:
        {
//             if(!wRefreshMode) return;
            Page_OnRPParamBase(wRefreshMode);
        }
        break;
    case  3:
        {
            //             if(!wRefreshMode) return;
            Page_OnRPSetupEnergy(wRefreshMode);
        }
        break;
    case  4:
        {
//             if(!wRefreshMode) return;
            Page_OnRPSetupDeviceTime();
        }
        break;
    case  5:
        {
//             if(!wRefreshMode) return;
            Page_OnRPBOTest(wRefreshMode);
        }
        break;
    case  6:
        {
            Page_OnRPAdjust(wRefreshMode);
        }
        break;
    }
}

WORD Page_OnKeyMsg(WORD wKeyCode)
{
    if(Menu_GetIndexMenuMain()==4) wKeyCode = PGWR_OnKeyMsg(wKeyCode);
    return wKeyCode;
}

//-----------------------------------------------------------------------------
void AutoDataOut(char* pszLabel, WORD wData1Index,char* pszUnit, WORD wData2Index, WORD wX1, WORD wX2, WORD wX3, WORD wX4)
{
    g_wLCDAutoPosY = Page_GetLinePosY();
    g_wPageLines++;
    if(g_wLCDAutoPosY>=LCD_CYDOT) return;

    if(pszLabel);
    {
        g_wLCDAutoPosX = wX1;
        LCD_SetTextAlignMode(TAMODE_LEFT);
        LCD_AutoTextOut(pszLabel);
    }

    if(wData1Index>0)
    {
        LCD_SetTextAlignMode(TAMODE_RIGHT);
        g_wLCDAutoPosX = wX2;
        g_wLCDAutoPosY -= g_wLCDAutoEnter - 2;
        MyHMI_AutoLCDDataOut((WORD)(wData1Index&0x0fff));
    }

    if(pszUnit)
    {
        LCD_SetTextAlignMode(TAMODE_LEFT);
        g_wLCDAutoPosX = wX3;
        g_wLCDAutoPosY -= g_wLCDAutoEnter + 2;
        LCD_AutoTextOut(pszUnit);
    }

    if(wData2Index>0)
    {
        LCD_SetTextAlignMode(TAMODE_RIGHT);
        g_wLCDAutoPosX = wX4;
        g_wLCDAutoPosY -= g_wLCDAutoEnter - 2;
        MyHMI_AutoLCDDataOut((WORD)(wData2Index&0x0fff));
    }
}

//void Page_OnRPProtectData(WORD wRefreshMode)
//{
//    Page_DrawHead("电 度 量");
//    Page_SetMetrics(MENUHEAD+2,10);
//    g_wLCDAutoEnter = 14;

//    AutoDataOut("Ep+", INDEX_PhI, "kWh", 0, 10 , 120, 124, 0);
//    AutoDataOut("Eq+", INDEX_QhI, "kVarh", 0, 10 , 120, 124, 0);
//    AutoDataOut("Ep-", INDEX_PhE, "kWh", 0, 10 , 120, 124, 0);
//    AutoDataOut("Eq-", INDEX_QhE, "kVarh", 0, 10 , 120, 124, 0);

//    LCD_SetTextAlignMode(TAMODE_LEFT);

//    Menu_SetPageCount((WORD)((g_wPageLines+g_wPageLineNum-1)/g_wPageLineNum));
//}

void Page_OnRPEngeryData(WORD wRefreshMode)
{
    Page_DrawHead("电 度 量");
    Page_SetMetrics(MENUHEAD+2,10);
    g_wLCDAutoEnter = 14;

    AutoDataOut("Ep+", INDEX_PhI, "kWh", 0, 10 , 120, 124, 0);
    AutoDataOut("Eq+", INDEX_QhI, "kVarh", 0, 10 , 120, 124, 0);
    AutoDataOut("Ep-", INDEX_PhE, "kWh", 0, 10 , 120, 124, 0);
    AutoDataOut("Eq-", INDEX_QhE, "kVarh", 0, 10 , 120, 124, 0);

    LCD_SetTextAlignMode(TAMODE_LEFT);

    Menu_SetPageCount((WORD)((g_wPageLines+g_wPageLineNum-1)/g_wPageLineNum));
}

void Page_OnRPSetupEnergy(WORD wRefreshMode)
{
    Page_DrawHead("电 度 设 置");
    Page_SetMetrics(MENUHEAD+2,10);
    g_wLCDAutoEnter = 14;

    AutoDataOut("Ep+", INDEX_PARAM_PhI, "kWh", 0, 10 , 60, 124, 0);
    AutoDataOut("Eq+", INDEX_PARAM_QhI, "kVarh", 0, 10 , 60, 124, 0);
    AutoDataOut("Ep-", INDEX_PARAM_PhE, "kWh", 0, 10 , 60, 124, 0);
    AutoDataOut("Eq-", INDEX_PARAM_QhE, "kVarh", 0, 10 , 60, 124, 0);
    
    LCD_SetTextAlignMode(TAMODE_LEFT);
    
    Menu_SetPageCount((WORD)((g_wPageLines+g_wPageLineNum-1)/g_wPageLineNum));
}

void Page_OnRPMeansureData(WORD wRefreshMode)
{
    char* pszUnit = NULL;
    Page_DrawHead("二 次 值");
    Page_SetMetrics(MENUHEAD+2,10);
    g_wLCDAutoEnter = 14;
    
    pszUnit = Data_GetUnitageText(&g_dataIa,"%S");
    AutoDataOut("Ia", INDEX_2Ia, pszUnit, INDEX_AngIa, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataIb,"%S");
    AutoDataOut("Ib", INDEX_2Ib, pszUnit, INDEX_AngIb, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataIc,"%S");
    AutoDataOut("Ic", INDEX_2Ic, pszUnit, INDEX_AngIc, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataUa,"%S");
    AutoDataOut("Ua", INDEX_2Ua, pszUnit, INDEX_AngUa, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataUb,"%S");
    AutoDataOut("Ub", INDEX_2Ub, pszUnit, INDEX_AngUb, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataUc,"%S");
    AutoDataOut("Uc", INDEX_2Uc, pszUnit, INDEX_AngUc, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataUab,"%S");
    AutoDataOut("Uab", INDEX_2Uab, pszUnit, INDEX_AngUab, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataUbc,"%S");
    AutoDataOut("Ubc", INDEX_2Ubc, pszUnit, INDEX_AngUbc, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataUca,"%S");
    AutoDataOut("Uca", INDEX_2Uca, pszUnit, INDEX_AngUca, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataP,"%S");
    AutoDataOut("P", INDEX_2P, pszUnit, 0, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataQ,"%S");
    AutoDataOut("Q", INDEX_2Q, pszUnit, 0, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataS,"%S");
    AutoDataOut("S", INDEX_2S, pszUnit, 0, 10 , 103, 106, 155);
    AutoDataOut("PF", INDEX_PF, NULL, 0, 10 , 103, 106, 155);
    pszUnit = Data_GetUnitageText(&g_dataF,"%S");
    AutoDataOut("F", INDEX_F, pszUnit, 0, 10 , 103, 106, 155);

    LCD_SetTextAlignMode(TAMODE_LEFT);
    
    Menu_SetPageCount((WORD)((g_wPageLines+g_wPageLineNum-1)/g_wPageLineNum));
}

void Page_OnRPPrimaryData(WORD wRefreshMode)
{
    char* pszUnit = NULL;
    Page_DrawHead("一 次 值");
    Page_SetMetrics(MENUHEAD+2,10);
    g_wLCDAutoEnter = 14;
    
    pszUnit = Data_GetUnitageText(&g_dataIa,"%P");
    AutoDataOut("Ia", INDEX_1Ia, pszUnit, 0, 10 , 103, 124, 0);
    pszUnit = Data_GetUnitageText(&g_dataIb,"%P");
    AutoDataOut("Ib", INDEX_1Ib, pszUnit, 0, 10 , 103, 124, 0);
    pszUnit = Data_GetUnitageText(&g_dataIc,"%P");
    AutoDataOut("Ic", INDEX_1Ic, pszUnit, 0, 10 , 103, 124, 0);
    pszUnit = Data_GetUnitageText(&g_dataUa,"%P");
    AutoDataOut("Ua", INDEX_1Ua, pszUnit, 0, 10 , 103, 124, 0);
    pszUnit = Data_GetUnitageText(&g_dataUb,"%P");
    AutoDataOut("Ub", INDEX_1Ub, pszUnit, 0, 10 , 103, 124, 0);
    pszUnit = Data_GetUnitageText(&g_dataUc,"%P");
    AutoDataOut("Uc", INDEX_1Uc, pszUnit, 0, 10 , 103, 124, 0);
    pszUnit = Data_GetUnitageText(&g_dataUab,"%P");
    AutoDataOut("Uab", INDEX_1Uab, pszUnit, 0, 10 , 103, 124, 0);
    pszUnit = Data_GetUnitageText(&g_dataUbc,"%P");
    AutoDataOut("Ubc", INDEX_1Ubc, pszUnit, 0, 10 , 103, 124, 0);
    pszUnit = Data_GetUnitageText(&g_dataUca,"%P");
    AutoDataOut("Uca", INDEX_1Uca, pszUnit, 0, 10 , 103, 124, 0);
    pszUnit = Data_GetUnitageText(&g_dataP,"%P");
    AutoDataOut("P", INDEX_1P, pszUnit, 0, 10 , 103, 124, 0);
    pszUnit = Data_GetUnitageText(&g_dataQ,"%P");
    AutoDataOut("Q", INDEX_1Q, pszUnit, 0, 10 , 103, 124, 0);
    pszUnit = Data_GetUnitageText(&g_dataS,"%P");
    AutoDataOut("S", INDEX_1S, pszUnit, 0, 10 , 103, 124, 0);
    AutoDataOut("PF", INDEX_PF, NULL, 0, 10 , 103, 124, 0);

    LCD_SetTextAlignMode(TAMODE_LEFT);
    
    Menu_SetPageCount((WORD)((g_wPageLines+g_wPageLineNum-1)/g_wPageLineNum));
}

void Page_OnRefreshPageSwitch(WORD wRefreshMode)
{
    short i;
    char* pch;
    Page_DrawHead("开 入 状 态");
    Page_SetMetrics(MENUHEAD+2,10);
    g_wLCDAutoEnter = 14;

    for(i=0;i<SWITCH_COUNT;i++)
    {
        WORD wMask = 1<<i;
        pch = "分位";
        if(g_deviceInfo.wSwitchStatus1&wMask)
        {
            pch = "合位";
        }
        AutoDataOut((char*)g_pszInName[i], 0, pch, 0, 2 , 0, 130, 0);
    }

//     pch = "分位";
//     if((g_deviceInfo.wSwitchStatus1&0x0600)==0x00) pch = "合位";
//     AutoDataOut("控制回路断线", 0, pch, 0, 2 , 0, 130, 0);
//     pch = "分位";
//     if(g_deviceInfo.wDeviceStatus1&DS1_Tripped) pch = "合位";
//     AutoDataOut("事故总", 0, pch, 0, 2 , 0, 130, 0);
//     pch = "分位";
//     if(g_deviceInfo.wDeviceStatus1&DS1_Alarmed) pch = "合位";
//     AutoDataOut("告警总", 0, pch, 0, 2 , 0, 130, 0);
    
    Menu_SetPageCount((WORD)((g_wPageLines+g_wPageLineNum-1)/g_wPageLineNum));
}

void Page_OnRefreshSetpoint(WORD wRefreshMode, BOOL bEdit)
{
    char* pch = "定 值 查 看";
    if(bEdit) pch = "定 值 编 辑";
    Page_DrawHead(pch);
    PGPRT_SetMetrics();
    LCD_SetTextAlignMode(TAMODE_LEFT);
    PGPRT_OnRefreshPage((WORD*)g_pDeviceSetpoint,TRUE);
}

void Page_OnRefreshPageRTWave(WORD wRefreshMode)
{
    LCD_Clear();
    Menu_SetPageCount((DFT_CHANNEL_HARD+2)/3);
    Page_DrawHead("实 时 波 形");
    Page_DrawRTWaveGrid();
    switch(g_wPageCurSel)
    {
    case 0:
        Page_DrawRTWave(0,&g_dataUa,2000,INDEX_2Ua,COLOR_LIGHTYELLOW);
        Page_DrawRTWave(1,&g_dataUb,2000,INDEX_2Ub,COLOR_LIGHTGREEN);
        Page_DrawRTWave(2,&g_dataUc,2000,INDEX_2Uc,COLOR_LIGHTRED);
        break;
    case 1:
        Page_DrawRTWave(0,&g_dataIa,2000,INDEX_2Ia,COLOR_LIGHTYELLOW);
        Page_DrawRTWave(1,&g_dataIb,2000,INDEX_2Ib,COLOR_LIGHTGREEN);
        Page_DrawRTWave(2,&g_dataIc,2000,INDEX_2Ic,COLOR_LIGHTRED);
        break;
    }
}

// void Page_OnRefreshPageVector(WORD wRefreshMode)
// {
//     WORD wScaleIP;
// 
//     LCD_Clear();
//     LCD_SetColor(COLOR_BLUE);
//     wScaleIP = (WORD)(1500000L/10000L);
//     Page_DrawHead("矢 量 图");
//     Menu_SetPageCount(3);
//     Page_DrawVectorGrid(&g_dataUa);
//     switch(g_wPageCurSel)
//     {
//     case 0:
//         Page_DrawVector(&g_dataUa,COLOR_YELLOW,50,1875,0);
//         Page_DrawVector(&g_dataUb,COLOR_GREEN,50,1875,1);
//         Page_DrawVector(&g_dataUc,COLOR_RED,50,1875,2);
//         Page_DrawVectorData(0,"\3Ua:\6\2V",INDEX_2Ua,COLOR_YELLOW);
//         Page_DrawVectorData(1,"\3Ub:\6\2V",INDEX_2Ub,COLOR_GREEN);
//         Page_DrawVectorData(2,"\3Uc:\6\2V",INDEX_2Uc,COLOR_RED);
//         break;
//     case 1:
//         Page_DrawVector(&g_dataIA,COLOR_LIGHTYELLOW,40,wScaleIP,0);
//         Page_DrawVector(&g_dataIB,COLOR_LIGHTGREEN,40,wScaleIP,1);
//         Page_DrawVector(&g_dataIC,COLOR_LIGHTRED,40,wScaleIP,2);
//         Page_DrawVectorData(0,"\3IA:\6\2A",INDEX_2IA,COLOR_LIGHTYELLOW);
//         Page_DrawVectorData(1,"\3IB:\6\2A",INDEX_2IB,COLOR_LIGHTGREEN);
//         Page_DrawVectorData(2,"\3IC:\6\2A",INDEX_2IC,COLOR_LIGHTRED);
//         break;
//     case 2:
//         Page_DrawVector(&g_dataIa,COLOR_YELLOW,40,2500,0);
//         Page_DrawVector(&g_dataIb,COLOR_GREEN,40,2500,1);
//         Page_DrawVector(&g_dataIc,COLOR_RED,40,2500,2);
//         Page_DrawVectorData(0,"\3Ia:\6\2A",INDEX_2Ia,COLOR_YELLOW);
//         Page_DrawVectorData(1,"\3Ib:\6\2A",INDEX_2Ib,COLOR_GREEN);
//         Page_DrawVectorData(2,"\3Ic:\6\2A",INDEX_2Ic,COLOR_RED);
//     }
//     Page_DrawVectorHead(20,MENUHEAD+109,0);
//     Page_DrawVectorHead(20,MENUHEAD+121,1);
//     Page_DrawVectorHead(20,MENUHEAD+133,2);
//     LCD_DrawHLineExt(MENUHEAD+109,28,72,0xaa);
//     LCD_DrawHLineExt(MENUHEAD+121,28,72,0xaa);
//     LCD_DrawHLineExt(MENUHEAD+133,28,72,0xaa);
// }

void Page_OnRefreshPageWaveRecord(WORD wRefreshMode)
{
    g_bScroll = FALSE;
    g_pPGWRData[0] = &g_dataUa;
    g_pPGWRData[1] = &g_dataUb;
    g_pPGWRData[2] = &g_dataUc;
    g_pPGWRData[3] = &g_dataIa;
    g_pPGWRData[4] = &g_dataIb;
    g_pPGWRData[5] = &g_dataIc;
    g_pPGWRData[6] = NULL;
    g_pPGWRData[7] = NULL;
    PGWR_SetMetrics(4,52,25);
    PGWR_OnRefreshPage(wRefreshMode);
}

void Page_OnRefreshInfo(WORD wRefreshMode)
{
    Page_DrawHead("保 护 信 息");
    Page_SetMetrics(MENUHEAD+2,10);
    g_wLCDAutoEnter = 14;

    AutoDataOut("型号", INDEX_DEVICETYPE, NULL, 0, 5, 150, 0, 0);
    AutoDataOut("版本", INDEX_VERSION, NULL, 0, 5, 150, 0, 0);
    AutoDataOut("日期", INDEX_DATE, NULL, 0, 5, 150, 0, 0);
    AutoDataOut("时间", INDEX_TIME, NULL, 0, 5, 150, 0, 0);
    AutoDataOut("CRC", INDEX_CRCINFO, NULL, 0, 5, 150, 0, 0);
    AutoDataOut("设备参数", INDEX_ERRORED_PARAM, NULL, 0, 5, 150, 0, 0);
    AutoDataOut("校正系数", INDEX_ERRORED_REGULATE, NULL, 0, 5, 150, 0, 0);
    AutoDataOut("保护定值", INDEX_ERRORED_SETPOINT, NULL, 0, 5, 150, 0, 0);
    AutoDataOut("时钟", INDEX_ERRORED_TIME, NULL, 0, 5, 150, 0, 0);
    AutoDataOut("AD", INDEX_ERRORED_AD, NULL, 0, 5, 150, 0, 0);

    LCD_SetTextAlignMode(TAMODE_LEFT);
    
    Menu_SetPageCount((WORD)((g_wPageLines+g_wPageLineNum-1)/g_wPageLineNum));
}

void Page_OnRPParamBase(WORD wRefreshMode)
{
    Page_DrawHead("通 信 参 数");
    Page_SetMetrics(MENUHEAD+2,10);
    g_wLCDAutoEnter = 14;

    AutoDataOut("通信地址", INDEX_PARAM_COMMADDR, NULL, 0, 5, 120, 0, 0);
    AutoDataOut("通信速率", INDEX_PARAM_COMMBUADRATE, NULL, 0, 5, 120, 0, 0);

    LCD_SetTextAlignMode(TAMODE_LEFT);
    Menu_SetPageCount((WORD)((g_wPageLines+g_wPageLineNum-1)/g_wPageLineNum));
}

void Page_OnRPBOTest(WORD wRefreshMode)
{
    Page_DrawHead("开 出 传 动");
    Menu_SetPageCount(3);
    g_bScroll = FALSE;
    LCD_SetSmallFont();
    LCD_SetTextAlignMode(TAMODE_LEFT);

    if(g_wPageCurSel<9)
    {
//		AutoDataOut((char*)g_pszInName[i], 0, pch, 0, 2 , 0, 130, 0);
        LCD_TextOut(4,MENUHEAD+2+15*0,"□\1DO1");
        LCD_TextOut(4,MENUHEAD+2+15*1,"□\1DO2");
        LCD_TextOut(4,MENUHEAD+2+15*2,"□\1复归");
//         LCD_TextOut(4,MENUHEAD+2+15*7,"□\1LED灯测试");
    }

    g_bLCDSetDataXor = TRUE;
    LCD_DrawBlock(0,(WORD)(MENUHEAD+g_wPageCurSel%9*15),160,(WORD)(MENUHEAD+15+g_wPageCurSel%9*15));
    g_bLCDSetDataXor = FALSE;
    if(wRefreshMode==RM_PAGEOK)
    {
        switch(g_wPageCurSel)
        {
        case  0: Output_SetLevel(&g_relayKH[0],STATUS_ON); break;
        case  1: Output_SetLevel(&g_relayKH[1],STATUS_ON); break;
        case  2:
            {
                short i;
                for(i=0;i<RELAYKH_COUNT;i++)
                {
                    Output_SetLevel(&g_relayKH[i],STATUS_OFF);
                }
            }
            break;
//         case  7: MyHMI_TestLights(); break;
        }
    }

    if(g_wPageCount>9)
    {
        Page_DrawScroll(157,(g_wPageCount+8)/9,g_wPageCurSel/9);
        LCD_DrawVLineExt(156,MENUHEAD,LCD_CYDOT,0x00);
    }
}

void Page_OnRefreshPageSetpoint(WORD* pDeviceSetpoint,BOOL bDisplaySetpoint)
{
    if(bDisplaySetpoint) Page_DrawHead(MULTITEXT("保 护 定 值","PROTECTION SETPOINTS"));
    else Page_DrawHead(MULTITEXT("保 护 投 退","PROTECTION ON/OFF"));
    LCD_SetColor((WORD)(g_wInputPasswordMode?COLOR_LIGHTGRAY:COLOR_BLUE));
    LCD_SetSmallFont();
    g_bPageLargeFont = FALSE;
    LCD_SetTextAlignMode(TAMODE_LEFT);
    PGPRT_SetMetrics();
    PGPRT_OnRefreshPage(pDeviceSetpoint,bDisplaySetpoint);
}

void Page_OnRPAdjust(WORD wRefreshMode)
{
    static BOOL s_bReg = FALSE, bShowMessage = FALSE;
    BOOL bRegStatus;
    if(wRefreshMode==RM_PAGEENTER)
    {
        s_bReg = FALSE;
        bShowMessage = FALSE;
    }
    if(wRefreshMode==RM_PAGECANCEL && bShowMessage)
    {
        bShowMessage = FALSE;
        g_bPageCaptureKeyCancel = FALSE;
    }
    if(s_bReg)
    {
        bRegStatus = Measure_GetRegStatus();
        if(bRegStatus==FALSE)
        {
            g_bPageCaptureKeyCancel = TRUE;
            bShowMessage = TRUE;
            s_bReg = FALSE;
        }
    }

    g_bRefreshEdit = TRUE;
    Page_DrawHead("精 度 设 置");
    Menu_SetPageCount(1);
    g_bScroll = FALSE;
    LCD_SetSmallFont();
    LCD_SetTextAlignMode(TAMODE_LEFT);
    
    if(g_wPageCurSel<9)
    {
        LCD_TextOut(4,MENUHEAD+2+15*0,"□\1自动校准");
    }
    
    g_bLCDSetDataXor = TRUE;
    LCD_DrawBlock(0,(WORD)(MENUHEAD+g_wPageCurSel%9*15),160,(WORD)(MENUHEAD+15+g_wPageCurSel%9*15));
    g_bLCDSetDataXor = FALSE;
    if(wRefreshMode==RM_PAGEOK)
    {
        switch(g_wPageCurSel)
        {
        case  0:
            {
                s_bReg = TRUE;
                Measure_StartReg();
            }
            break;
        }
    }
    
    if(g_wPageCount>9)
    {
        Page_DrawScroll(157,(g_wPageCount+8)/9,g_wPageCurSel/9);
        LCD_DrawVLineExt(156,MENUHEAD,LCD_CYDOT,0x00);
    }

    if(bShowMessage)
    {
        LCD_ClearBlock(20,35,140,125);
        LCD_DrawHLine(35,20,140);
        LCD_DrawHLine(125,20,140);
        LCD_DrawHLineExt(126,21,141,0x55);
        LCD_DrawHLineExt(127,22,142,0x55);
        LCD_DrawVLine(20,35,125);
        LCD_DrawVLine(140,35,125);
        LCD_DrawVLineExt(141,36,126,0x55);
        LCD_DrawVLineExt(142,37,127,0x55);
        LCD_TextOut(50, 74, "校正完成!");
    }
}

