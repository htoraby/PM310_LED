#include <Main.h>

//-----------------------------------------------------------------------------
void Page_DrawHead(char* pszHead)
{
	LCD_SetSmallFont();
	LCD_SetTextAlignMode(TAMODE_CENTER);
	LCD_TextOut(LCD_CXDOT/2,1,pszHead);
	LCD_DrawHLineExt(13,0,160,0xff);
}

void Page_DrawScroll(WORD wPosX,WORD wPages,WORD wCurSel)
{
	DrawScroll(wPosX,MENUHEAD,3,(LCD_CYDOT-MENUHEAD),wPages,1,wCurSel);
}

void Page_DrawTable(WORD wPosX,WORD wPosY,WORD wCX,WORD wCY,WORD wNum,char* pszLabel)
{
	WORD i;
	WORD wColorOld;
	BOOL bLargeFont;

	for(i=0;i<=wNum;i++) LCD_DrawHLineExt((WORD)(wPosY+i*wCY),wPosX,(WORD)(wPosX+wCX),0xaa);
	LCD_DrawVLineExt((WORD)(wPosX),wPosY,(WORD)(wPosY+wNum*wCY),0xaa);
	LCD_DrawVLineExt((WORD)(wPosX+wCX),wPosY,(WORD)(wPosY+wNum*wCY+1),0xaa);

	wColorOld = g_wLCDColor;
	bLargeFont = g_bLCDLargeFont;
	LCD_SetSmallFont();
	LCD_SetColor(COLOR_WHITE);
	if(pszLabel)
	{
		LCD_SetTextAlignMode(TAMODE_CENTER);
		LCD_TextOut((WORD)(wPosX+wCX/2),wPosY+(WORD)((wCY-10)>>1),pszLabel);
		LCD_SetTextAlignMode(TAMODE_LEFT);
	}
	LCD_SetColor(wColorOld);
	if(bLargeFont) LCD_SetLargeFont();
	else LCD_SetSmallFont();
}

void Page_DrawRTWaveGrid(void)
{
	Page_DrawRTWaveGrid1(0,MENUHEAD,126,46);
	Page_DrawRTWaveGrid1(0,MENUHEAD+48,126,46);
	Page_DrawRTWaveGrid1(0,MENUHEAD+96,126,46);
}

void Page_DrawRTWave(WORD wIndex,MyData* data,WORD wScale,WORD wDataIndex,WORD wColor)
{
	WORD wPosY;
	g_wLCDAutoPosX = 128;

	wPosY = MENUHEAD+wIndex%3*48;
	g_wLCDAutoPosY = wPosY+23;
	g_wLCDAutoEnter = 12;
	LCD_SetTextAlignMode(TAMODE_LEFT);
	LCD_SetSmallFont();
	LCD_SetColor(wColor);
	LCD_AutoAsciiOut(data->m_pszName);
	Page_DrawRTWave1(0,wPosY,126,46,data->m_wIndexDFT,wScale);
}

static short s_nBaseR;
static short s_nBaseX;
void Page_DrawVectorGrid(MyData* dataUa)
{
	LCD_DrawCircle(80,MENUHEAD+50,50);
	LCD_DrawCircle(80,MENUHEAD+50,40);
	LCD_DrawHLineExt(MENUHEAD+50,0,160,0xaa);
	LCD_DrawVLineExt(80,MENUHEAD,MENUHEAD+100,0xaa);
	s_nBaseR = 0;
	s_nBaseX = 0;
	if(dataUa->m_nData)
	{
		s_nBaseR = (short)(1000L*(long)dataUa->m_nX/(long)dataUa->m_nData);
		s_nBaseX = (short)(1000L*(long)dataUa->m_nR/(long)dataUa->m_nData);
	}
}

void Page_DrawVectorHead(WORD nPosX,WORD nPosY,WORD wHeadSharp)
{
	switch(wHeadSharp)
	{
	case 0:
		LCD_DrawRect((WORD)(nPosX-1),(WORD)(nPosY-1),(WORD)(nPosX+1),(WORD)(nPosY+1));
		LCD_DrawRect((WORD)(nPosX-2),(WORD)(nPosY-2),(WORD)(nPosX+2),(WORD)(nPosY+2));
		break;
	case 1:
		LCD_DrawRect((WORD)(nPosX-3),(WORD)(nPosY-3),(WORD)(nPosX+3),(WORD)(nPosY+3));
		break;
	case 2:
		LCD_DrawCircle(nPosX,nPosY,4);
		break;
	}
}

void Page_DrawVector(MyData* data,WORD wColor,WORD wRadian,WORD wScale,WORD wHeadSharp)
{
	long lR,lX;
	short nPosX,nPosY;

	if(s_nBaseR==0&&s_nBaseX==0) return;
	if(wScale==0) return;
	LCD_SetColor(wColor);
	lR = ((long)data->m_nR*s_nBaseR-(long)data->m_nX*s_nBaseX)/1000L;
	lX = ((long)data->m_nX*s_nBaseR+(long)data->m_nR*s_nBaseX)/1000L;
	nPosX = 80+(short)((long)wRadian*lR/(long)wScale);
	nPosY = MENUHEAD+50-(short)((long)wRadian*lX/(long)wScale);
	LCD_DrawXLine(80,MENUHEAD+50,nPosX,nPosY);
	LCD_DrawPoint(nPosX,nPosY);
	Page_DrawVectorHead(nPosX,nPosY,wHeadSharp);
}

void Page_DrawVectorData(WORD wIndex,char* pszName,WORD wDataIndex,WORD wColor)
{
	LCD_SetSmallFont();
	LCD_SetTextAlignMode(TAMODE_LEFT);
	LCD_SetColor(wColor);
	g_wLCDAutoPosX = 63+wIndex/3*80;
	g_wLCDAutoPosY = MENUHEAD+106+wIndex%3*12;
	LCD_AutoAsciiOut(pszName);
	g_wLCDAutoPosX += 42;
	g_wLCDAutoPosY -= 12;
	MyHMI_AutoLCDDataOut(wDataIndex);
	LCD_SetTextAlignMode(TAMODE_LEFT);
}

#define PAGE_EVENTNUM		4
#define PAGE_EVENTHEIGHT	36
#define PAGE_EVENTCOUNT		EVENT_COUNT

void Page_OnRefreshPageEvent(WORD wRefreshMode)
{
	WORD wEventIndex;
	WORD wCharCnt;
	WORD wEventOldest;
	short i;
	EVENT* pEvent;
	WORD wPosY;

	wEventIndex = 0;
	wCharCnt = 2;

	if(!wRefreshMode) return;
	Page_DrawHead(MULTITEXT("事 件 记 录","EVENT RECORDING"));
	LCD_SetTextAlignMode(TAMODE_LEFT);
	LCD_SetSmallFont();
	if(g_deviceInfo.wCountEventTable==0)
	{
		LCD_SetTextAlignMode(TAMODE_CENTER);
		LCD_TextOut(LCD_CXDOT/2,LCD_CYDOT/2-6,MULTITEXT("(无事件记录)","(NO EVENT RECORDED)"));
		LCD_SetTextAlignMode(TAMODE_LEFT);
		Menu_SetPageCount(1);
		return;
	}
	if(g_deviceInfo.wCountEventTable>=PAGE_EVENTCOUNT)
	{
		wEventOldest = g_deviceInfo.wCountEventTable-PAGE_EVENTCOUNT;
		Menu_SetPageCount((PAGE_EVENTCOUNT-1)/PAGE_EVENTNUM+1);
	}
	else
	{
		wEventOldest = 0;
		Menu_SetPageCount((WORD)((g_deviceInfo.wCountEventTable-1)/PAGE_EVENTNUM+1));
	}
	if(wRefreshMode==RM_PAGEENTER) Menu_SetPageCurSel(PAGE_EVENTCOUNT/PAGE_EVENTNUM);
	wEventOldest += g_wPageCurSel*PAGE_EVENTNUM;
	for(i=0;i<PAGE_EVENTNUM;i++)
	{
		//IsTimeOK();
		if(wEventOldest>=g_deviceInfo.wCountEventTable) break;
		pEvent = Event_GetEvent(wEventOldest);
		if(pEvent->wType!=EVENTTYPE_NULL)
		{
			wPosY = MENUHEAD+i*PAGE_EVENTHEIGHT;
			LCD_SetColor(COLOR_BLACK);
			LCD_DrawBlock(0,wPosY,LCD_CXDOT,(WORD)(wPosY+PAGE_EVENTHEIGHT-2));
			g_wLCDColorBK = g_wLCDColor;
			LCD_SetColor(COLOR_WHITE);
			LCD_DrawHLineExt((WORD)(wPosY+PAGE_EVENTHEIGHT-1),0,LCD_CYDOT,0xaa);
			wPosY += 2;
			wEventIndex = g_wPageCurSel*PAGE_EVENTNUM+i+1;
			if(wEventIndex<10) wCharCnt = 1;
			else if(wEventIndex<100) wCharCnt = 2;
			else wCharCnt = 3;
			LCD_ByteOut(0+(3-wCharCnt)*6,wPosY,(BYTE)wEventIndex,wCharCnt);
			LCD_DateOut(24,wPosY,pEvent->time.wYear,pEvent->time.wMonth,pEvent->time.wDay);
			LCD_TimeOut(78,wPosY,pEvent->time.wHour,pEvent->time.wMinute,pEvent->time.wSecond,pEvent->time.wMilliSecond);
			LCD_TextOut(3,(WORD)(wPosY+9),MyHMI_GetEventText(pEvent));
		}
		wEventOldest++;
	}
}


void Page_OnRefreshPageLCDContrast(WORD wRefreshMode)
{
	WORD i;
	WORD wPosX;
	WORD wPosY;
    
//    static WORD s_wLCDContrast;
    g_bScroll = FALSE;
    Menu_SetPageCount(17);
    if(wRefreshMode==RM_TIMER1S) return;
    else if(wRefreshMode==RM_PAGEUP||wRefreshMode==RM_PAGEDOWN)
    {
        g_deviceParam.wLCDContrast = g_wPageCurSel;
        MyApp_OnUpdateDevice(&g_deviceParam.wLCDContrast, FALSE);
    }
    else Menu_SetPageCurSel((g_deviceParam.wLCDContrast>16)?16:g_deviceParam.wLCDContrast);
    for(i=0;i<10;i++)
    {
        LCD_SetColor(i);
        wPosX = 21+i%5*24;
        wPosY = 10+i/5*24;
        LCD_DrawBlock(wPosX,wPosY,(WORD)(wPosX+20),(WORD)(wPosY+20));
        LCD_DrawHLine((WORD)(60+i*5), 20, 140);
    }
    LCD_SetColor(COLOR_WHITE);
    LCD_DrawRect(14,127,144,142);
    LCD_SetSmallFont();
    LCD_AsciiOut(16,118,"0%");
    LCD_AsciiOut(70,118,"50%");
    LCD_AsciiOut(119,118,"100%");
    LCD_SetColor(COLOR_LIGHTYELLOW);
    for(i=0;i<g_wPageCurSel;i++) LCD_DrawBlock((WORD)(16+i*8),129,(WORD)(16+i*8+6),140);
}

void Page_OnRPSetupDeviceTime(void)
{
// 	g_IsSetTime = TRUE;
	LCD_SetSmallFont();
//	LCD_SetLargeFont();
	g_wLCDAutoPosX = LCD_CXDOT/2-20;
	g_wLCDAutoPosY = LCD_CYDOT/2-18;
	g_wLCDAutoEnter = 20;
	LCD_AutoAsciiOut("-   -");
	LCD_AutoAsciiOut(":   :");
	LCD_SetColor(COLOR_LIGHTCYAN);
	g_wLCDAutoPosX = LCD_CXDOT/2-40;
	g_wLCDAutoPosY = LCD_CYDOT/2-18;
	EditG_AddEditDataWord(&g_deviceTime.wYear);
	g_wLCDAutoPosX += 32;
	g_wLCDAutoPosY -= 20;
	EditG_AddEditDataWord(&g_deviceTime.wMonth);
	g_wLCDAutoPosX += 32;
	g_wLCDAutoPosY -= 20;
	EditG_AddEditDataWord(&g_deviceTime.wDay);
	g_wLCDAutoPosX = LCD_CXDOT/2-40;
	g_wLCDAutoPosY = LCD_CYDOT/2+2;
	EditG_AddEditDataWord(&g_deviceTime.wHour);
	g_wLCDAutoPosX += 32;
	g_wLCDAutoPosY -= 20;
	EditG_AddEditDataWord(&g_deviceTime.wMinute);
	g_wLCDAutoPosX += 32;
	g_wLCDAutoPosY -= 20;
	EditG_AddEditDataWord(&g_deviceTime.wSecond);
}
