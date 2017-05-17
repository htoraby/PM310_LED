//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#include <Main.h>

void Page_OnInit(void)
{
    g_wDisplayType = 0;
    g_wPageCount = 0;
    g_wPageCurSel = 0;
    g_wPageLineNum = 0;
    g_wPageLines = 0;
    LED_Clear();
}

void Page_OnTimer10ms(void)
{

}

void Page_RefreshU(WORD wMode)
{
    Page_SetMetrics(3);

    Page_AutoDataOut(0, INDEX_2Ua);
    Page_AutoDataOut(0, INDEX_2Ub);
    Page_AutoDataOut(0, INDEX_2Uc);
    LED_SetCode(LED_02,'U');

    Page_SetPageCount((g_wPageLines+g_wPageLineNum-1)/g_wPageLineNum);
}

void Page_RefreshI(WORD wMode)
{
    
}

void Page_RefreshP(WORD wMode)
{
    
}

void Page_RefreshE(WORD wMode)
{
    
}

void RefreshSet(WORD wMode)
{
    
}

void Page_Refresh(WORD wMode)
{
    switch(g_wDisplayType)
    {
    case DISPLAY_U: Page_RefreshU(wMode); break;
    case DISPLAY_I: Page_RefreshI(wMode); break;
    case DISPLAY_P: Page_RefreshP(wMode); break;
    case DISPLAY_E: Page_RefreshE(wMode); break;
    case DISPLAY_SET:
        {
            RefreshSet(wMode);
//             pEdit->EnableEdit(wMode);
        }
        break;
    default:
        Page_OnInit();
        break;
    }
}

WORD Page_OnKeyMsg(WORD wKeyCode)
{
    return wKeyCode;
}

void Page_RefreshCommon(WORD wMode)
{
    BOOL bFlash = (g_dwSystick&0x3ff)>400?TRUE:FALSE;
    LED_SetLight(LED_Logo, bFlash);
    LED_SetLight(LED_DI, TRUE);
    LED_SetLight(LED_DO, TRUE);
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------


