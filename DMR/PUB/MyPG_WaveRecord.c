#include <Main.h>

#define PAGE_DOTNUM      ((LCD_CXDOT/DFT_DOTNUM)*DFT_DOTNUM-4)

//     WORD m_wPAGE_DOTNUM;
//     WORD m_wPosYStart;          // 模拟量位置Y起始
//     WORD m_wLinePix;            // 每个通道高度
//     WORD m_wHeight;
//     BOOL m_bDrawRect;
// protected:
//     WORD m_wCountWaveRecordOld;
//     WORD m_wWaveData[WAVEDATABUFF];

MyData* g_pPGWRData[8] = { NULL};

static WAVERECORD* s_pWaveRecord = NULL;
static WORD s_wCountWaveRecordOld = 0;
static WORD s_wWaveCount;
static WORD s_wChannelSelect;
static WORD s_wPageSelect = 0;
static short s_wPageCnt = 0;
static WORD s_wWaveNo[WAVERECORD_WAVENUM-1];
static WORD s_wWaveData[WAVEDATABUFF];

static WORD s_wPosYStart;          // 模拟量位置Y起始
static WORD s_wLinePix;            // 每个通道高度
static WORD s_wHeight;

//-----------------------------------------------------------------------------
// void PGWR_SetProperty(WORD wLCDCX,BOOL bDrawRect)
// {
//     m_wPAGE_DOTNUM = (wLCDCX/DFT_DOTNUM)*DFT_DOTNUM-4;
//     m_bDrawRect = bDrawRect;
// }

WORD PGWR_OnKeyMsg(WORD wKeyCode)
{
    if(wKeyCode==KEY_UP)
    {
        if(s_pWaveRecord==NULL)
        {
            if(g_wPageCurSel>0)
            {
                g_wPageCurSel--;
                PGWR_OnRefreshPage(RM_PAGEUP);
                wKeyCode = NULL;
            }
        }
        else
        {
            PGWR_OnRefreshPage(RM_PAGEUP);
            wKeyCode = NULL;
        }
    }
    else if(wKeyCode==KEY_DOWN)
    {
        if(s_pWaveRecord==NULL)
        {
            if(g_wPageCurSel<g_wPageCount-1)
            {
                g_wPageCurSel++;
                PGWR_OnRefreshPage(RM_PAGEDOWN);
                wKeyCode = NULL;
            }
        }
        else
        {
            PGWR_OnRefreshPage(RM_PAGEDOWN);
            wKeyCode = NULL;
        }
    }
    else if(wKeyCode==KEY_LEFT)
    {
        if(s_pWaveRecord)
        {
            if(g_wPageCurSel>0)
            {
                g_wPageCurSel--;
                PGWR_OnRefreshPage(RM_PAGELEFT);
            }
        }
        wKeyCode = NULL;
    }
    else if(wKeyCode==KEY_RIGHT)
    {
        if(s_pWaveRecord)
        {
            if(g_wPageCurSel<g_wPageCount-1)
            {
                g_wPageCurSel++;
                PGWR_OnRefreshPage(RM_PAGERIGHT);
            }
        }
        wKeyCode = NULL;
    }

    return wKeyCode;
}

void PGWR_OnRefreshPage(WORD wRefreshMode)
{
    g_bScroll = FALSE;
    if(wRefreshMode==RM_PAGEENTER)
    {
        s_pWaveRecord = NULL;
        s_wCountWaveRecordOld = g_deviceInfo.wCountWaveRecord;
    }
    if(s_wCountWaveRecordOld!=g_deviceInfo.wCountWaveRecord)
    {
        s_pWaveRecord = NULL;
        s_wCountWaveRecordOld = g_deviceInfo.wCountWaveRecord;
    }
    else if(wRefreshMode==RM_TIMER1S) return;
    if(s_pWaveRecord==NULL)
    {
        if(wRefreshMode==RM_PAGEOK&&(s_wWaveCount>0))
        {
            s_pWaveRecord = WaveRecord_GetRecord(s_wWaveNo[g_wPageCurSel]);
            s_wChannelSelect = 0;
            s_wPageSelect = 0;
            Menu_SetPageCurSel(0);
            PGWR_OnRefreshPageWaveDisplay(RM_PAGEENTER);
        }
        else PGWR_OnRefreshPageWaveSelect(wRefreshMode);
    }
    else
    {
        if(wRefreshMode==RM_PAGECANCEL)
        {
            WORD i;
            for(i=0;i<s_wWaveCount;i++)
            {
                if(s_pWaveRecord==WaveRecord_GetRecord(s_wWaveNo[i])) break;
            }
            s_pWaveRecord = NULL;
            Menu_SetPageCount(s_wWaveCount);
            Menu_SetPageCurSel(i);
            PGWR_OnRefreshPageWaveSelect(RM_PAGEENTER);
        }
        else PGWR_OnRefreshPageWaveDisplay(wRefreshMode);
    }
}

void PGWR_OnRefreshPageWaveSelect(WORD wRefreshMode)
{
    WORD i;
    s_wWaveCount = 0;
    for(i=0;i<WAVERECORD_WAVENUM-1;i++)
    {
        WORD wWaveNo = (g_deviceInfo.wCountWaveRecord+1+i)%WAVERECORD_WAVENUM;
        WAVERECORD* pWaveRecord = WaveRecord_GetRecord(wWaveNo);
        if(pWaveRecord->wRecordStatus!=WRS_RECORDED) continue;
        if(!Time_IsTimeOK(&pWaveRecord->timeFreeze)) continue;
        s_wWaveNo[s_wWaveCount] = wWaveNo;
        s_wWaveCount++;
    }
    LCD_SetColorBK(COLOR_BLACK);
    LCD_Clear();

    LCD_SetSmallFont();
    LCD_SetTextAlignMode(TAMODE_CENTER);
    LCD_TextOut(LCD_CXDOT/2,1, "故障录波");
    LCD_SetTextAlignMode(TAMODE_LEFT);
    LCD_DrawHLineExt(13,0,160,0xff);
//     LCD_SetSmallFont();
    if(s_wWaveCount==0)
    {
        LCD_SetTextAlignMode(TAMODE_CENTER);
        LCD_TextOut(LCD_CXDOT/2,LCD_CYDOT/2-6,"(无故障录波)");
        LCD_SetTextAlignMode(TAMODE_LEFT);
        Menu_SetPageCount(1);
        return;
    }
    Menu_SetPageCount(s_wWaveCount);
    for(i=0;i<s_wWaveCount;i++)
    {
        DEVICETIME* pTime = &WaveRecord_GetRecord(s_wWaveNo[i])->timeFreeze;
//         if(m_bDrawRect)
//         {
//             g_lcd.TextOut(46,44+15*i,"□");
//             g_lcd.DateOut(61,46+15*i,pTime->wYear,pTime->wMonth,pTime->wDay);
//             g_lcd.TimeOut(115,46+15*i,pTime->wHour,pTime->wMinute,pTime->wSecond,pTime->wMilliSecond);
//         }
        LCD_TextOut(2,MENUHEAD+2+15*i,"□");
        LCD_DateOut(17,MENUHEAD+4+15*i,pTime->wYear,pTime->wMonth,pTime->wDay);
        LCD_TimeOut(71,MENUHEAD+4+15*i,pTime->wHour,pTime->wMinute,pTime->wSecond,pTime->wMilliSecond);
    }
    g_bLCDSetDataXor = TRUE;
//     if(m_bDrawRect) g_lcd.DrawBlock(42,(WORD)(42+g_menu.m_wPageCurSel*15),198,(WORD)(56+g_menu.m_wPageCurSel*15));
    LCD_DrawBlock(2,(WORD)(MENUHEAD+g_wPageCurSel*15),LCD_CXDOT,(WORD)(MENUHEAD+14+g_wPageCurSel*15));
    g_bLCDSetDataXor = FALSE;
    g_bPageCaptureKeyCancel = FALSE;
}

void PGWR_OnRefreshPageWaveDisplay(WORD wRefreshMode)
{
    WORD wWaveRecordedDot;
    WORD wWaveStartDotNo,wPAGE_DOTNUM;
    short i;

    if(wRefreshMode==RM_PAGEUP) PGWR_GotoNextPage(PGWAVE_UP);
    if(wRefreshMode==RM_PAGEDOWN) PGWR_GotoNextPage(PGWAVE_DOWN);
    LCD_SetColorBK(COLOR_BLACK);
    LCD_Clear();
    wWaveRecordedDot = WAVERECORD_DOTNUM;
    if(s_pWaveRecord->wCycleFlag==0) wWaveRecordedDot = MIN(s_pWaveRecord->wFreezeDotNo,WAVERECORD_DOTNUM);
    if(wWaveRecordedDot<DFT_DOTNUM*5) return;

    if(s_pWaveRecord->wCycleFlag==0)
    {
        wWaveStartDotNo = 0;
    }
    else
    {
        wWaveStartDotNo = (s_pWaveRecord->wFreezeDotNo+WAVERECORD_DOTNUM-1)%WAVERECORD_DOTNUM;
    }

    s_wPageCnt = (wWaveRecordedDot+PAGE_DOTNUM-1)/PAGE_DOTNUM;
    if(wRefreshMode==RM_PAGEOK)
    {
        s_wPageSelect++;
        s_wPageSelect %= s_wPageCnt;
    }

    wPAGE_DOTNUM = wWaveRecordedDot - s_wPageSelect*PAGE_DOTNUM;
    if(wPAGE_DOTNUM>PAGE_DOTNUM) wPAGE_DOTNUM = PAGE_DOTNUM;

    PGWR_GetWaveDataSwitch(wWaveStartDotNo);
    PGWR_DrawWaveSwitch(wPAGE_DOTNUM);
    for(i=0;i<3;i++)
    {
        WORD wChannel = s_wChannelSelect*3+i;
        if(wChannel<WAVERECORDCHANMEL)
        {
            PGWR_GetWaveDataAnalog(wWaveStartDotNo,wChannel);
            PGWR_DrawWaveAnalog(wChannel,wPAGE_DOTNUM);
        }
    }

    if(s_wPageCnt>1)
    {
        PGWR_DrawScrollBar();
    }
    DrawScroll(LCD_CXDOT-3,0,3,LCD_CYDOT,(WAVERECORDCHANMEL+2)/3,1,s_wChannelSelect%WAVERECORDCHANMEL);
    g_bPageCaptureKeyCancel = TRUE;
}

void PGWR_GotoNextPage(WORD wDir)
{
    BOOL bChannelValid = FALSE;
    short i;

    if(wDir==PGWAVE_UP) { if(s_wChannelSelect>0) s_wChannelSelect--; }
    else if(wDir==PGWAVE_DOWN) { if(s_wChannelSelect<((WAVERECORDCHANMEL+2)/3-1)) s_wChannelSelect++; }
    s_wChannelSelect %= ((WAVERECORDCHANMEL+2)/3);
    for(i=0;i<3;i++)
    {
        WORD wChannel = s_wChannelSelect*3+i;
        if(wChannel<WAVERECORDCHANMEL && g_pPGWRData[wChannel]) bChannelValid = TRUE;
    }
    if(bChannelValid==FALSE) PGWR_GotoNextPage(wDir);
}

void PGWR_GetWaveDataSwitch(WORD wStartDotNo)
{
    short i;
    for(i=0;i<PAGE_DOTNUM;i++)
    {
        WORD wDotNo = (wStartDotNo+s_wPageSelect*PAGE_DOTNUM+i)%WAVERECORD_DOTNUM;
        s_wWaveData[i] = s_pWaveRecord->wData[wDotNo][6];
    }
}

void PGWR_GetWaveDataAnalog(WORD wStartDotNo,WORD wIndex)
{
    short i;
    for(i=0;i<PAGE_DOTNUM;i++)
    {
        WORD wDotNo = (wStartDotNo+g_wPageCurSel*PAGE_DOTNUM+i)%WAVERECORD_DOTNUM;
        WORD* pWaveData = &(s_pWaveRecord->wData[wDotNo][0]);
        switch(wIndex)
        {
        case 0: s_wWaveData[i] = pWaveData[0]>>2; break;
        case 1: s_wWaveData[i] = pWaveData[1]>>2; break;
        case 2: s_wWaveData[i] = pWaveData[2]>>2; break;
        case 3: s_wWaveData[i] = pWaveData[3]>>2; break;
        case 4: s_wWaveData[i] = pWaveData[4]>>2; break;
        case 5: s_wWaveData[i] = pWaveData[5]>>2; break;
//         case 6: s_wWaveData[i] = pWaveData[6]; break;
//         case 7: s_wWaveData[i] = pWaveData[7]; break;
        default: s_wWaveData[i] = 0; break;
        }
        if(s_wWaveData[i]>2000) s_wWaveData[i] = 2000;
    }
}

void PGWR_DrawScrollBar(void)
{
    short i;
    for(i=1;i<4;++i)
    {
        if(i%2==0)
            LCD_DrawHLineExt(LCD_CYDOT-i,0,PAGE_DOTNUM,0xaa);
        else
            LCD_DrawHLineExt(LCD_CYDOT-i,0,PAGE_DOTNUM,0x55);
        LCD_DrawHLineExt(LCD_CYDOT-i,s_wPageSelect*PAGE_DOTNUM/s_wPageCnt,(s_wPageSelect+1)*PAGE_DOTNUM/s_wPageCnt,0xff);
    }
}

void PGWR_DrawWaveSwitch(WORD wDots)
{
    short i;
    LCD_SetColor(COLOR_LIGHTCYAN);

    for(i=0;i<wDots;i++)
    {
        if(s_wWaveData[i]&SS_IN01)
        {
            LCD_DrawPoint(i,0);
            LCD_DrawPoint(i,1);
            LCD_DrawPoint(i,2);
            LCD_DrawPoint(i,3);
        }
    }
}

void PGWR_SetMetrics(WORD wPosStart,WORD wLinePix,WORD wHeight)
{
    s_wPosYStart = wPosStart;
    s_wLinePix = wLinePix;
    s_wHeight = wHeight;
}

void PGWR_DrawWaveAnalog(WORD wChannel,WORD wDots)
{
    WORD i;
    WORD wPosY = s_wPosYStart+(wChannel%3)*s_wLinePix;
    LCD_SetColor(COLOR_BLUE);
    LCD_DrawHLineExt(wPosY,0,PAGE_DOTNUM,0xaa);
    LCD_DrawHLineExt(wPosY+2*s_wHeight,0,PAGE_DOTNUM,0xaa);
    switch(wChannel%3)
    {
    case 0: LCD_SetColor(COLOR_LIGHTYELLOW); break;
    case 1: LCD_SetColor(COLOR_LIGHTGREEN); break;
    case 2: LCD_SetColor(COLOR_LIGHTRED); break;
    }
    for(i=1;i<wDots;i++)
    {
        WORD wPosY1 = wPosY+2*s_wHeight-(s_wWaveData[i-1]*s_wHeight+250)/500;
        WORD wPosY2 = wPosY+2*s_wHeight-(s_wWaveData[i]*s_wHeight+250)/500;
        LCD_DrawXLine(i-1,wPosY1,i,wPosY2);
    }
    if(g_pPGWRData[wChannel])
    {
        LCD_SetSmallFont();
        LCD_SetTextAlignMode(TAMODE_RIGHT);
        LCD_AsciiOut(LCD_CXDOT-4,wPosY+2,g_pPGWRData[wChannel]->m_pszName);
        LCD_SetTextAlignMode(TAMODE_LEFT);
    }
}

