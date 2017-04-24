#include <Main.h>

WORD g_wMenuMode;
WORD g_wMenuMainCurTop;
WORD g_wMenuMainCurSel;
WORD g_wMenuMainLineMax;
WORD g_wMenuSubCurTop;
WORD g_wMenuSubCurSel;
WORD g_wMenuSubLineMax;
WORD g_wPageCount;
WORD g_wPageCurSel;
BOOL g_bPageLargeFont;
BOOL g_bPageHead;
BOOL g_bScroll;
BOOL g_bPageCaptureKeyCancel;
WORD g_wInputPassword;
WORD g_wInputPasswordMode;
WORD g_wCountCloseLCD;

WORD g_wMenuMainPosX;
WORD g_wMenuMainPosY;
WORD g_wMenuMainCX;
WORD g_wMenuMainCY;
BOOL g_bMenuMainLargeFont;
WORD g_wMenuSubPosX;
WORD g_wMenuSubPosY;
WORD g_wMenuSubCX;
WORD g_wMenuSubCY;
BOOL g_bMenuSubLargeFont;
BOOL g_bDisplayEvent = FALSE;

BOOL g_bRefreshEdit = FALSE;

WORD g_wMenuModeOld = 0xff;
WORD g_wMenuMainCurSelOld = 0xff;
WORD g_wMenuSubCurSelOld = 0xff;
WORD g_wPageCurSelOld = 0xff;

//-----------------------------------------------------------------------------
void DrawScroll(WORD wPosX,WORD wPosY,WORD wWidth,WORD wHeight,WORD wTotalLines,WORD wLinesPerPage,WORD wCurTop)
{
	short nFillDotY1,nFillDotY2,nScrollY1,i;
	WORD wScrollPosY1,wScrollPosY2;
	WORD wScrollPosYMax;

	nFillDotY1 = (wHeight * wLinesPerPage + wTotalLines / 2) / wTotalLines;

	nScrollY1 = (wHeight * wCurTop + wTotalLines / 2) / wTotalLines + wPosY;
	nFillDotY2 = nFillDotY1;
	if((wCurTop+wLinesPerPage)==wTotalLines) nFillDotY2 = (short)wHeight;				// 由于nDotperLine有误差,补足最后少的部分

	wScrollPosYMax = wPosY+wHeight;
	for(i=0;i<wWidth;++i)
	{
		if(i%2==0) LCD_DrawVLineExt(wPosX+i,wPosY,wScrollPosYMax,0xaa);
		else LCD_DrawVLineExt(wPosX+i,wPosY,wScrollPosYMax,0x55);
		if(nFillDotY1>2)
		{
			wScrollPosY1 = nScrollY1;
			wScrollPosY2 = (WORD)(nScrollY1+nFillDotY2);
		}
		else if(wCurTop<2)
		{
			wScrollPosY1 = nScrollY1;
			wScrollPosY2 = (WORD)(nScrollY1+3);
		}
		else if(wCurTop>wTotalLines-3)
		{
			wScrollPosY1 = nScrollY1 - 2;
			wScrollPosY2 = (WORD)(nScrollY1+nFillDotY2);
		}
		else
		{
			wScrollPosY1 = nScrollY1 - 1;
			wScrollPosY2 = (WORD)(nScrollY1+2);
		}
		wScrollPosY2 = (wScrollPosY2>wScrollPosYMax)?wScrollPosYMax:wScrollPosY2;
		LCD_DrawVLineExt(wPosX+i,wScrollPosY1,wScrollPosY2,0xff);			// 滑块太小
	}
}

//-----------------------------------------------------------------------------
void Menu_OnInit(void)
{
	g_wMenuMode = MM_SingleLine;
	g_wMenuMainCurTop = 0;
	g_wMenuMainCurSel = 0;
	g_wMenuMainLineMax = 0;
	g_wMenuSubCurTop = 0;
	g_wMenuSubCurSel = 0;
	g_wMenuSubLineMax = 0;
	g_wPageCount = 0;
	g_wPageCurSel = 0;
	g_bPageHead = TRUE;
	g_bScroll = FALSE;
	g_bPageLargeFont = FALSE;
	g_bPageCaptureKeyCancel = FALSE;
	g_wInputPassword = 0;
	g_wInputPasswordMode = 0;
	g_wCountCloseLCD = MENU_TIMECLOSELCD;
    g_bRefreshEdit = FALSE;

	Menu_SetMenuMetrics();
}

// void Menu_DrawMenuMain(void)
// {
// 	g_menu.iiiDrawMenuMain();
// }

void Menu_ReDrawAll(void)
{
	switch(g_wMenuMode)
	{
    case MM_SingleLine: Menu_DrawMenuSL(RM_EXTERNAL); break;
	case MM_MENUMAIN: Menu_DrawMenuMain(); break;
	case MM_MENUSUB: Menu_DrawMenuSub(); break;
	case MM_MENUPAGE: Menu_OnRefreshPage(RM_EXTERNAL); break;
	}
}

void Menu_DisableSaveScreen(void)
{
	if(g_wCountCloseLCD==0) g_wCountCloseLCD = 2;
	LCD_Open();
}

void Menu_SetPageCount(WORD wPageCount)
{
	g_wPageCount = MAX(wPageCount,1);
	if(g_wPageCurSel>=g_wPageCount) g_wPageCurSel = g_wPageCount-1;
}

void Menu_SetPageCurSel(WORD wPageCurSel)
{
	g_wPageCurSel = wPageCurSel;
	if(g_wPageCurSel>=g_wPageCount) g_wPageCurSel = g_wPageCount-1;
}

WORD Menu_GetIndexMenuMain(void)
{
	return g_wMenuMainCurTop+g_wMenuMainCurSel;
}

WORD Menu_GetIndexMenuSub(void)
{
	return g_wMenuSubCurTop+g_wMenuSubCurSel;
}

void Menu_OnTimer1000ms(void)
{
    if(g_bDisplayEvent)
    {
        Menu_DispayEvent();
        g_bDisplayEvent = FALSE;
		g_wCountCloseLCD = MENU_TIMECLOSELCD;
    }
	Menu_OnRefreshPage(RM_TIMER1S);
	if(g_wCountCloseLCD==0)
	{
		if(g_wMenuMode!=MM_SingleLine)
		{
			g_wMenuMode = MM_SingleLine;
			Menu_DrawMenuSL(RM_PAGEENTER);
		}

        LCD_Close();
	}
	else
	{
		g_wCountCloseLCD--;
		LCD_Open();
	}
	switch(g_wMenuMode)
	{
    case MM_SingleLine: break;
	case MM_MENUMAIN: if(Menu_GetIndexMenuMain()>=Menu_GetMenuMainCount()) Menu_OnInit(); break;
	case MM_MENUSUB: if(Menu_GetIndexMenuSub()>=Menu_GetMenuSubCount(g_wMenuMainCurTop+g_wMenuMainCurSel)) Menu_OnInit(); break;
	case MM_MENUPAGE: if(g_wPageCurSel>=g_wPageCount) Menu_OnInit(); break;
	default: Menu_OnInit(); break;
	}
}

void Menu_DispayEvent(void)
{
    if(g_wMenuMainCurSel==6 && g_wMenuMode!=MM_MENUMAIN) return;
    if(g_wMenuModeOld>MM_MENUPAGE)
    {
        g_wMenuModeOld = g_wMenuMode;
        g_wMenuMainCurSelOld = g_wMenuMainCurSel;
        g_wMenuSubCurSelOld = g_wMenuSubCurSel;
        g_wPageCurSelOld = g_wPageCurSel;
    }

    g_wMenuMode = MM_MENUPAGE;
    g_wMenuMainCurSel = 3;
    g_deviceInfo.wCountEventTable = g_wEventTableCountNew;
    g_bPageCaptureKeyCancel = FALSE;
    LCD_Clear();
    Page_OnRefreshPageEvent(RM_PAGEENTER);
}

void Menu_OnKeyMsg(WORD wKeyCode)
{
	if(g_wCountCloseLCD==0)
	{
		wKeyCode = KEY_NULL;
		LCD_Setup();
	}
	g_wCountCloseLCD = MENU_TIMECLOSELCD;
	LCD_Open();
	if(wKeyCode==KEY_NULL) return;
	switch(g_wMenuMode)
	{
    case MM_SingleLine:
        if(wKeyCode!=KEY_CANCEL && wKeyCode!=KEY_RESET)
        {
            g_wMenuMode = MM_MENUMAIN;
            Menu_DrawMenuMain();
        }
        break;
	case MM_MENUMAIN: Menu_OnKeyMsgMenuMain(wKeyCode); break;
	case MM_MENUSUB: Menu_OnKeyMsgMenuSub(wKeyCode); break;
	case MM_MENUPAGE: Menu_OnKeyMsgPage(wKeyCode); break;
	default: Menu_OnInit(); break;
	}
}

void Menu_OnRefreshPage(WORD wRefreshMode)
{
	BOOL bLCDClear;
	BOOL bRefreshPage;
	BOOL bEnterEdit;
	MENUITEM menuitem;

    if(g_wMenuMode==MM_SingleLine) Menu_DrawMenuSL(wRefreshMode);
	if(g_wMenuMode!=MM_MENUPAGE) return;
	bLCDClear = FALSE;
	bRefreshPage = FALSE;
	bEnterEdit = FALSE;
	menuitem.pszMenu = NULL;
	menuitem.wConfig = 0;
	g_bScroll = TRUE;
// 	g_IsSetTime = FALSE;
	Menu_GetMenuItemMain(g_wMenuMainCurTop+g_wMenuMainCurSel,&menuitem);
	if((menuitem.wConfig&MICFG_PASSWORD)==0)
	{
		if(wRefreshMode) bLCDClear = TRUE;
		bRefreshPage = TRUE;
	}
	else if(g_wInputPasswordMode)
	{
        if(g_bRefreshEdit)
        {
            if(wRefreshMode) bLCDClear = TRUE;
            bRefreshPage = TRUE;
        }
        else
        {
            if(wRefreshMode==RM_EXTERNAL) EditG_OnRefreshPage();
            else if(wRefreshMode)
            {
                bLCDClear = TRUE;
                bRefreshPage = TRUE;
                bEnterEdit = TRUE;
            }
        }
	}
	if(bLCDClear)
	{
		LCD_CursorOFF();
		LCD_SetColor(Menu_GetMenuPageColor());
		LCD_SetColorBK(Menu_GetMenuPageColorBK());
		LCD_Clear();
	}
	LCD_SetTextAlignMode(TAMODE_LEFT);
	if(g_bPageLargeFont) LCD_SetLargeFont();
	else LCD_SetSmallFont();
	g_wLCDAutoPosX = 0;
	g_wLCDAutoPosY = 0;
	g_wLCDAutoEnter = 12;
	if(bRefreshPage)
	{
		g_bPageHead = TRUE;
		if(wRefreshMode==RM_PAGEENTER) g_bPageCaptureKeyCancel = FALSE;
		EditG_OnInit();
		Page_OnRefreshPage(wRefreshMode);
// 		MyHMI_OnRefreshPage(wRefreshMode);
		EditG_OnRefreshPage();
		if(bEnterEdit) EditG_EnableEdit(wRefreshMode);
	}
}

BOOL Menu_EnterSubMenuSetup(WORD* pData)
{
	if(pData==&g_wInputPassword)
	{
		g_wInputPasswordMode = MyHMI_GetPasswordMode(g_wInputPassword);
		if(g_wInputPasswordMode)
		{
			g_wMenuMode = MM_MENUSUB;
			g_wMenuSubCurTop = 0;
			g_wMenuSubCurSel = 0;
			Menu_DrawMenuSub();
			return TRUE;
		}
	}
	return FALSE;
}

void Menu_OnKeyMsgMenuMain(WORD wKeyCode)
{
	MENUITEM menuitem;

	if(wKeyCode==KEY_UP)
	{
		if(g_wMenuMainCurSel>0)
		{
			Menu_MenuMainCursorOFF();
			g_wMenuMainCurSel--;
			Menu_MenuMainCursorON();
		}
		else if(g_wMenuMainCurTop>0)
		{
			g_wMenuMainCurTop--;
			Menu_DrawMenuMain();
		}
	}
	else if(wKeyCode==KEY_DOWN)
	{
		if(g_wMenuMainCurSel<g_wMenuMainLineMax-1)
		{
			if(g_wMenuMainCurTop+g_wMenuMainCurSel<Menu_GetMenuMainCount()-1)
			{
				Menu_MenuMainCursorOFF();
				g_wMenuMainCurSel++;
				Menu_MenuMainCursorON();
			}
		}
// 		else if(m_wMenuMainCurTop<g_menu.iiiGetMenuMainCount()-m_wMenuMainLineMax)
		else if(g_wMenuMainCurTop+g_wMenuMainLineMax<Menu_GetMenuMainCount())
		{
			g_wMenuMainCurTop++;
			Menu_DrawMenuMain();
		}
	}
	else if(wKeyCode==KEY_LEFT)
	{
		if(g_wMenuMainCurTop>0)
		{
			if(g_wMenuMainCurTop>g_wMenuMainLineMax)
				g_wMenuMainCurTop -= g_wMenuMainLineMax;
			else
				g_wMenuMainCurTop = 0;
			Menu_DrawMenuMain();
		}
	}
	else if(wKeyCode==KEY_RIGHT)
	{
		if((short)g_wMenuMainCurTop<(short)Menu_GetMenuMainCount()-(short)g_wMenuMainLineMax)
		{
			g_wMenuMainCurTop += g_wMenuMainLineMax;
			if(g_wMenuMainCurTop+g_wMenuMainLineMax>=Menu_GetMenuMainCount())
				g_wMenuMainCurTop = Menu_GetMenuMainCount()-g_wMenuMainLineMax;
			Menu_DrawMenuMain();
		}
	}
	else if(wKeyCode==KEY_OK)
	{
		menuitem.pszMenu = NULL;
		menuitem.wConfig = 0;
		Menu_GetMenuItemMain(g_wMenuMainCurTop+g_wMenuMainCurSel,&menuitem);
		if(menuitem.pszMenu==NULL) return;
		g_wInputPassword = 0;
		g_wInputPasswordMode = 0;
		if(menuitem.wConfig&MICFG_SUBMENU)
		{
			if((menuitem.wConfig&MICFG_PASSWORD)==0)
			{
				g_wMenuMode = MM_MENUSUB;
				g_wMenuSubCurTop = 0;
				g_wMenuSubCurSel = 0;
				LCD_Setup();
				Menu_DrawMenuSub();
			}
			else
			{
				g_wMenuMode = MM_MENUPAGE;
				Menu_SetPageCount(1);
				Menu_SetPageCurSel(0);
				EditG_OnInit();
				Menu_DrawPasswordPrompt();
				EditG_OnRefreshPage();
				EditG_EnableEdit(RM_PAGEENTER);
			}
		}
		else
		{
			g_wMenuMode = MM_MENUPAGE;
			Menu_SetPageCount(1);
			Menu_SetPageCurSel(0);
			LCD_Setup();
			Menu_OnRefreshPage(RM_PAGEENTER);
		}
	}
    else if(wKeyCode==KEY_CANCEL)
    {
        g_wMenuMode = MM_SingleLine;
		g_wMenuMainCurTop = 0;
		g_wMenuMainCurSel = 0;
        Menu_DrawMenuSL(RM_PAGEENTER);
    }
}

void Menu_OnKeyMsgMenuSub(WORD wKeyCode)
{
	MENUITEM menuitem;

	if(wKeyCode==KEY_UP)
	{
		if(g_wMenuSubCurSel>0)
		{
			Menu_MenuSubCursorOFF();
			g_wMenuSubCurSel--;
			Menu_MenuSubCursorON();
		}
		else if(g_wMenuSubCurTop>0)
		{
			g_wMenuSubCurTop--;
			Menu_DrawMenuSub();
		}
	}
	else if(wKeyCode==KEY_DOWN)
	{
		if(g_wMenuSubCurSel<g_wMenuSubLineMax-1)
		{
			if(g_wMenuSubCurTop+g_wMenuSubCurSel<Menu_GetMenuSubCount(g_wMenuMainCurTop+g_wMenuMainCurSel)-1)
			{
				Menu_MenuSubCursorOFF();
				g_wMenuSubCurSel++;
				Menu_MenuSubCursorON();
			}
		}
		else if(g_wMenuSubCurTop<Menu_GetMenuSubCount(g_wMenuMainCurTop+g_wMenuMainCurSel)-g_wMenuSubLineMax)
		{
			g_wMenuSubCurTop++;
			Menu_DrawMenuSub();
		}
	}
	else if(wKeyCode==KEY_LEFT)
	{
		if(g_wMenuSubCurTop>0)
		{
			if(g_wMenuSubCurTop>g_wMenuSubLineMax) g_wMenuSubCurTop -= g_wMenuSubLineMax;
			else g_wMenuSubCurTop = 0;
			Menu_DrawMenuSub();
		}
	}
	else if(wKeyCode==KEY_RIGHT)
	{
		WORD wTemp = Menu_GetMenuSubCount((WORD)(g_wMenuMainCurTop+g_wMenuMainCurSel));
		if(wTemp<g_wMenuSubLineMax) return;
		if(g_wMenuSubCurTop<wTemp-g_wMenuSubLineMax)
		{
			g_wMenuSubCurTop += g_wMenuSubLineMax;
			if(g_wMenuSubCurTop+g_wMenuSubLineMax>=wTemp) g_wMenuSubCurTop = wTemp-g_wMenuSubLineMax;
			Menu_DrawMenuSub();
		}
	}
	else if(wKeyCode==KEY_OK)
	{
		menuitem.pszMenu = NULL;
		menuitem.wConfig = 0;
		Menu_GetMenuItemSub(g_wMenuMainCurTop+g_wMenuMainCurSel,g_wMenuSubCurTop+g_wMenuSubCurSel,&menuitem);
		if(menuitem.pszMenu==NULL) return;
		g_wMenuMode = MM_MENUPAGE;
		Menu_SetPageCount(1);
		Menu_SetPageCurSel(0);
		LCD_Setup();
		Menu_OnRefreshPage(RM_PAGEENTER);
	}
	else if(wKeyCode==KEY_CANCEL)
	{
		g_wInputPassword = 0;
		g_wInputPasswordMode = 0;
		g_wMenuMode = MM_MENUMAIN;
		g_IsSetTime = FALSE;
        g_bRefreshEdit = FALSE;
		LCD_Setup();
		Menu_DrawMenuMain();
	}
}

void Menu_OnKeyMsgPage(WORD wKeyCode)
{
	MENUITEM menuitem;

    wKeyCode = EditG_OnKeyMsg(wKeyCode);

    wKeyCode = Page_OnKeyMsg(wKeyCode);

	if(wKeyCode==KEY_UP||wKeyCode==KEY_LEFT)
	{
		if(g_wPageCurSel>0)
		{
			g_wPageCurSel--;
			Menu_OnRefreshPage(RM_PAGEUP);
		}
	}
	else if(wKeyCode==KEY_DOWN||wKeyCode==KEY_RIGHT)
	{
		if(g_wPageCurSel<g_wPageCount-1)
		{
			g_wPageCurSel++;
			Menu_OnRefreshPage(RM_PAGEDOWN);
		}
	}
	else if(wKeyCode==KEY_OK)
	{
		Menu_OnRefreshPage(RM_PAGEOK);
	}
	else if(wKeyCode==KEY_CANCEL)
	{
// 		g_IsSetTime = FALSE;		// 退出时间设置模式
//         g_bRefreshEdit = FALSE;
// 		if(g_bPageCaptureKeyCancel)
// 		{
// 			Menu_OnRefreshPage(RM_PAGECANCEL);
// 			return;
// 		}
// 		menuitem.pszMenu = NULL;
// 		menuitem.wConfig = 0;
// 		Menu_GetMenuItemMain(g_wMenuMainCurTop+g_wMenuMainCurSel,&menuitem);
// 		if(menuitem.wConfig&MICFG_SUBMENU)
// 		{
// 			if((menuitem.wConfig&MICFG_PASSWORD) && g_wInputPasswordMode==0)
// 			{
// 				g_wMenuMode = MM_MENUMAIN;
// 				LCD_Setup();
// 				Menu_DrawMenuMain();
// 			}
// 			else
// 			{
// 				g_wMenuMode = MM_MENUSUB;
// 				LCD_Setup();
// 				Menu_DrawMenuSub();
// 			}
// 		}
// 		else
// 		{
// 			g_wInputPassword = 0;
// 			g_wInputPasswordMode = 0;
// 			g_wMenuMode = MM_MENUMAIN;
// 			LCD_Setup();
// 			Menu_DrawMenuMain();
// 		}

        g_IsSetTime = FALSE;		// 退出时间设置模式
        g_bRefreshEdit = FALSE;

        if(g_wMenuModeOld>MM_MENUPAGE)
        {
            if(g_bPageCaptureKeyCancel)
            {
                Menu_OnRefreshPage(RM_PAGECANCEL);
                return;
            }
            menuitem.pszMenu = NULL;
            menuitem.wConfig = 0;
            Menu_GetMenuItemMain(g_wMenuMainCurTop+g_wMenuMainCurSel,&menuitem);
            if(menuitem.wConfig&MICFG_SUBMENU)
            {
                if((menuitem.wConfig&MICFG_PASSWORD) && g_wInputPasswordMode==0)
                {
                    g_wMenuMode = MM_MENUMAIN;
                    LCD_Setup();
                    Menu_DrawMenuMain();
                }
                else
                {
                    g_wMenuMode = MM_MENUSUB;
                    LCD_Setup();
                    Menu_DrawMenuSub();
                }
            }
            else
            {
                g_wInputPassword = 0;
                g_wInputPasswordMode = 0;
                g_wMenuMode = MM_MENUMAIN;
                LCD_Setup();
                Menu_DrawMenuMain();
            }
        }
        else
        {
            g_wMenuMode = g_wMenuModeOld;
            g_wMenuMainCurSel = g_wMenuMainCurSelOld;
            g_wMenuSubCurSel = g_wMenuSubCurSelOld;
            g_wPageCurSel = g_wPageCurSelOld;

            Menu_ReDrawAll();
            g_wMenuModeOld = 0xff;
//          g_wMenuMainCurSelOld = 0xff;
//          g_wMenuSubCurSelOld = 0xff;
//          g_wPageCurSelOld = 0xff;
        }
    }
    else if(wKeyCode==KEY_ADD)
    {
        Menu_OnRefreshPage(RM_PAGEADD);
    }
    else if(wKeyCode==KEY_SUB)
    {
        Menu_OnRefreshPage(RM_PAGESUB);
    }
}

WORD Menu_GetMenuMainColor(void)
{
	return COLOR_WHITE;
}

WORD Menu_GetMenuMainColorBK(void)
{
	return COLOR_BLACK;
}

WORD Menu_GetMenuSubColor(void)
{
	return COLOR_WHITE;
}

WORD Menu_GetMenuSubColorBK(void)
{
	return COLOR_BLACK;
}

WORD Menu_GetMenuPageColor(void)
{
	return COLOR_WHITE;
}

WORD Menu_GetMenuPageColorBK(void)
{
	return COLOR_BLACK;
}

WORD Menu_GetMenuPasswordColor(void)
{
	return COLOR_WHITE;
}


//-----------------------------------------------------------------------------
// void Menu_SetMenuMetrics(void)
// {
// 	g_wMenuMainLineMax = 5;
// 	g_wMenuSubLineMax = 5;
// 	g_wMenuMainPosX = 0;
// 	g_wMenuMainPosY = 0;
// 	g_wMenuMainCX = 128 -SCROLLW-1;
// 	g_wMenuMainCY = 13;
// 	g_bMenuMainLargeFont = FALSE;
// 	g_wMenuSubPosX = 0;
// 	g_wMenuSubPosY = 0;
// 	g_wMenuSubCX = 128 -SCROLLW-1;
// 	g_wMenuSubCY = 13;
// 	g_bMenuSubLargeFont = FALSE;
// }

void Menu_DrawScrollMain(WORD wTotalLines)
{
	DrawScroll(g_wMenuMainCX+1,0,SCROLLW,LCD_CYDOT,wTotalLines,
		g_wMenuMainLineMax,g_wMenuMainCurTop);
}

void Menu_DrawScrollSub(WORD wTotalLines)
{
	DrawScroll(g_wMenuMainCX+1,0,SCROLLW,LCD_CYDOT,wTotalLines,
		g_wMenuSubLineMax,g_wMenuSubCurTop);
}

// 电池空:7*13
// const WORD c_wDCBitmap1[8] = 
// {0xf83f,0x0820,0x08e0,0x08a0,0x08e0,0x0820,0xf83f,0x0000};
// 电池满:7*13
// const WORD c_wDCBitmap2[8] = 
// {0xf83f,0xf83f,0xf8ff,0xf8ff,0xf8ff,0xf83f,0xf83f,0x0000};

void Menu_DrawMenuSL(WORD wRefreshMode)
{
    if(wRefreshMode)
    {
        LCD_Clear();
        
        LCD_DrawBlock(10, 20, 100, 22);
        LCD_DrawBlock(29, 22, 31, 132);
        LCD_DrawHLine(132, 24, 37);
        LCD_DrawXLine(24, 132, 31,142);
        LCD_DrawXLine(37, 132, 30,142);
        
        LCD_AsciiOut(60, 33+13*0, " Ia:");
        LCD_AsciiOut(60, 33+13*1, "  P:");
        LCD_AsciiOut(60, 33+13*2, "  Q:");
        LCD_AsciiOut(60, 33+13*3, " PF:");
        LCD_AsciiOut(60, 33+13*4, "Uab:");
        
    }

    g_wLCDAutoPosX = 22;
    g_wLCDAutoPosY = 4;
    LCD_AsciiOut(10, 4, "20");
    MyHMI_AutoLCDDataOut(INDEX_DATE);
    g_wLCDAutoPosX = 75;
    g_wLCDAutoPosY = 4;
    MyHMI_AutoLCDDataOut(INDEX_TIME);

    LCD_SetTextAlignMode(TAMODE_CENTER);
    LCD_TextOut(80, 146, "南京国铁电气有限责任公司");
    LCD_SetTextAlignMode(TAMODE_LEFT);
    {
        static short s_nFlash = 0;
        s_nFlash++;
        LCD_ClearBlock(136, 2, 157, 12);
        if((Protect_GetAct())||(g_deviceInfo.wDeviceStatus1&DS1_Errored))           // 告警,可返回
        {
            LCD_AsciiOut(138, 4, "ALM");
        }
        else                                                                // run
        {
            LCD_AsciiOut(138, 4, "RUN");
        }
        if(s_nFlash&0x01)
        {
            g_bLCDSetDataXor = TRUE;
            LCD_DrawBlock(136, 2, 157, 12);
            g_bLCDSetDataXor = FALSE;
        }
    }

    {
        short nIndex = g_pDeviceParam->wSLType;
        WORD wMask;
        if(nIndex>SWITCH_COUNT || nIndex<1) nIndex = 1;
        wMask = 1<<(nIndex-1);
        if(g_deviceInfo.wSwitchStatus1&wMask)              // 合闸
        {
            LCD_DrawBlock(24, 63, 36, 93);
        }
        else // if(g_deviceInfo.wSwitchStatus1&0x0400)              // 分闸
        {
            LCD_ClearBlock(24, 63, 36, 93);
            LCD_DrawRect(24, 63, 36, 93);
        }
    }


    LCD_SetTextAlignMode(TAMODE_RIGHT);
    g_wLCDAutoPosX = 60 + 8*8;
    g_wLCDAutoPosY = 33;
    g_wLCDAutoEnter = 13;
    MyHMI_AutoLCDDataOut(INDEX_1Ia);
    MyHMI_AutoLCDDataOut(INDEX_1P);
    MyHMI_AutoLCDDataOut(INDEX_1Q);
    MyHMI_AutoLCDDataOut(INDEX_PF);
    MyHMI_AutoLCDDataOut(INDEX_1Uab);

    LCD_SetTextAlignMode(TAMODE_LEFT);
    {
        char* pszUnit = NULL;
        pszUnit = Data_GetUnitageText(&g_dataIa,"%P");
        LCD_AsciiOut(65+8*8, 33+13*0, pszUnit);
        pszUnit = Data_GetUnitageText(&g_dataP,"%P");
        LCD_AsciiOut(65+8*8, 33+13*1, pszUnit);
        pszUnit = Data_GetUnitageText(&g_dataQ,"%P");
        LCD_AsciiOut(65+8*8, 33+13*2, pszUnit);
        pszUnit = Data_GetUnitageText(&g_dataUab,"%P");
        LCD_AsciiOut(65+8*8, 33+13*4, pszUnit);
    }
}

void Menu_DrawMenuMain(void)
{
	WORD wMenuMainCount;
	WORD wOffsetY,i;
	MENUITEM menuitem;

	wMenuMainCount = Menu_GetMenuMainCount();
	Menu_SetMenuMetrics();
// 	g_lcd.Setup();
	LCD_SetColor(Menu_GetMenuMainColor());
	LCD_SetColorBK(Menu_GetMenuMainColorBK());
	LCD_Clear();

	if(g_bMenuMainLargeFont)
	{
		LCD_SetLargeFont();
		wOffsetY = g_wMenuMainCY-15;
	}
	else
	{
		LCD_SetSmallFont();
		wOffsetY = g_wMenuMainCY-11;
	}
	wOffsetY >>= 1;

	for(i=0;i<g_wMenuMainLineMax;i++)
	{
		if(g_wMenuMainCurTop+i>=wMenuMainCount) break;
		menuitem.pszMenu = NULL;
		menuitem.wConfig = 0;
		Menu_GetMenuItemMain(g_wMenuMainCurTop+i,&menuitem);
		if(menuitem.pszMenu) LCD_TextOut(g_wMenuMainPosX+2,g_wMenuMainPosY+i*g_wMenuMainCY+wOffsetY,menuitem.pszMenu);
	}

	if(wMenuMainCount>g_wMenuMainLineMax)
	{
		g_bScroll = TRUE;
		Menu_DrawScrollMain(wMenuMainCount);
	}
	else g_bScroll = FALSE;
	Menu_MenuMainCursorON();
	EditG_OnInit();
}

void Menu_DrawMenuSub(void)
{
	WORD wMenuSubCount;
	WORD wOffsetY,i;
	MENUITEM menuitem;

	wMenuSubCount = Menu_GetMenuSubCount(g_wMenuMainCurTop+g_wMenuMainCurSel);
	Menu_SetMenuMetrics();

// 	g_lcd.Setup();
	LCD_SetColor(Menu_GetMenuSubColor());
	LCD_SetColorBK(Menu_GetMenuSubColorBK());
	LCD_Clear();

	if(g_bMenuSubLargeFont)
	{
		LCD_SetLargeFont();
		wOffsetY = g_wMenuSubCY-15;
	}
	else
	{
		LCD_SetSmallFont();
		wOffsetY = g_wMenuSubCY-11;
	}
	wOffsetY >>= 1;

	for(i=0;i<g_wMenuSubLineMax;i++)
	{
		if(g_wMenuSubCurTop+i>=wMenuSubCount) break;
		menuitem.pszMenu = NULL;
		menuitem.wConfig = 0;
		Menu_GetMenuItemSub(g_wMenuMainCurTop+g_wMenuMainCurSel,g_wMenuSubCurTop+i,&menuitem);
		if(menuitem.pszMenu) LCD_TextOut(g_wMenuSubPosX+2,g_wMenuSubPosY+i*g_wMenuSubCY+wOffsetY,menuitem.pszMenu);
	}

	if(wMenuSubCount>g_wMenuSubLineMax)
	{
		g_bScroll = TRUE;
		Menu_DrawScrollSub(wMenuSubCount);
	}
	else g_bScroll = FALSE;
	Menu_MenuSubCursorON();
	EditG_OnInit();
}

void Menu_DrawPasswordPrompt(void)
{
	WORD wPosX,wPosY;

	Menu_SetMenuMetrics();
	LCD_SetColor(Menu_GetMenuSubColor());
	LCD_SetColorBK(Menu_GetMenuSubColorBK());
	LCD_Clear();
	wPosX = LCD_CXDOT/2;
	wPosY = LCD_CYDOT/2;
	LCD_SetSmallFont();
	LCD_SetTextAlignMode(TAMODE_RIGHT);
	LCD_TextOut((WORD)(wPosX-6),(WORD)(wPosY-6),MULTITEXT("口令:","PASSWORD:"));
	LCD_SetTextAlignMode(TAMODE_LEFT);
	LCD_SetColor(Menu_GetMenuPasswordColor());
	if(g_bPageLargeFont)
	{
		LCD_SetLargeFont();
		g_wLCDAutoPosX = wPosX;
		g_wLCDAutoPosY = wPosY-8;
	}
	else
	{
		LCD_SetSmallFont();
		g_wLCDAutoPosX = wPosX;
		g_wLCDAutoPosY = wPosY-4;
	}
	EditG_AddEditDataWord(&g_wInputPassword);
}

void Menu_MenuMainCursorON(void)
{
	WORD wCursorWith;

	Menu_SetMenuMetrics();
	if(g_bScroll) wCursorWith = g_wMenuMainCX - g_wMenuMainPosX;
	else wCursorWith = g_wMenuMainCX - g_wMenuMainPosX + SCROLLW + 1;

	LCD_SetCursorPosX(g_wMenuMainPosX,wCursorWith);
	LCD_SetCursorPosY(g_wMenuMainPosY+g_wMenuMainCurSel*g_wMenuMainCY,g_wMenuMainCY);
	LCD_CursorON();
}

void Menu_MenuMainCursorOFF(void)
{
	LCD_CursorOFF();
}

void Menu_MenuSubCursorON(void)
{
	WORD wCursorWith;
	Menu_SetMenuMetrics();

	if(g_bScroll) wCursorWith = g_wMenuSubCX - g_wMenuSubPosX;
	else wCursorWith = g_wMenuSubCX - g_wMenuSubPosX + SCROLLW + 1;

	LCD_SetCursorPosX(g_wMenuSubPosX,wCursorWith);
	LCD_SetCursorPosY(g_wMenuSubPosY+g_wMenuSubCurSel*g_wMenuSubCY,g_wMenuSubCY);
	LCD_CursorON();
}

void Menu_MenuSubCursorOFF(void)
{
	LCD_CursorOFF();
}

