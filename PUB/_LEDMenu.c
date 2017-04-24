#include "main.h"
/*****************************************************************/
unsigned short g_wMenuMode;
unsigned short g_wPageCount;
unsigned short g_wPageCurSel;
unsigned short g_wPassword;
WORD g_wPasswordLevel;
unsigned short g_wCycleCurSel;

static WORD s_wScreenSave = 0;

/*******************************************************************/
void SetPageCount(unsigned short wPageCount)
{
	g_wPageCount = wPageCount;
	if(g_wCycleCurSel>=g_wPageCount) g_wCycleCurSel = g_wPageCount-1;
}

void SetPageCurSel(unsigned short wPageCurSel)
{
	g_wCycleCurSel = wPageCurSel;
	if(g_wCycleCurSel>=g_wPageCount) g_wCycleCurSel = g_wPageCount-1;
}

void OnRefreshPage(void)
{
	EditRemoveAll();
	switch(g_wMenuMode)
	{
	case MM_DATA: OnRefreshPageData(); break;
	case MM_PASSWORD:
		EditEnterEdit();
		OnRefreshPagePassword();
		break;
	case MM_SETUP:
		OnRefreshPageSetup();
// 		EditEnterEdit();
		break;
	}
}

/*******************************************************************/
void OnInitMenu(void)
{
	g_wMenuMode = MM_DATA;
	g_wPageCount = 0;
	g_wPageCurSel = 0;
	g_wCycleCurSel = 0;
	g_wPassword = 0;
	g_wPasswordLevel = PASSWORD_NULL;
	s_wScreenSave = SREENSAVETIME;
	EditRemoveAll();
}

void OnMenuTimer10ms(void)
{
	if(s_wScreenSave) s_wScreenSave--;
	if(!s_wScreenSave) 
	{
		g_wMenuMode = MM_DATA;		//实时数据显示页面
		g_wPageCurSel = 0;
	}
}

void OnTaskMenu(void)
{
	if(g_wMenuMode==MM_DATA) OnRefreshPage();
	if(g_bLEDtestOK)
	{
		g_bLEDtestOK = FALSE;
		OnRefreshPage();
	}
// 	if(g_wMenuMode==MM_SETUP)
// 	{
// 		OnRefreshPage();
// 		EditEnterEdit();
// 	}
}

void OnTaskMenuKey(unsigned short wKeyCode)
{
	s_wScreenSave = SREENSAVETIME;

	wKeyCode = OnEditKeyMsg(wKeyCode);
	if(wKeyCode==KEY_UP)
	{
		if(g_wCycleCurSel>0) SetPageCurSel(g_wCycleCurSel-1);
		LEDClear();
		OnRefreshPage();
	}
	else if(wKeyCode==KEY_DOWN)
	{
		if(g_wCycleCurSel<g_wPageCount-1) SetPageCurSel(g_wCycleCurSel+1);
		LEDClear();
		OnRefreshPage();
	}
	else if(wKeyCode==KEY_SETUP)
	{
		if(g_wMenuMode==MM_DATA)
		{
			g_wMenuMode = MM_PASSWORD;
			g_wPassword = 0;
			g_wPasswordLevel = PASSWORD_NULL;
			SetPageCurSel(0);
			LEDClear();
			OnRefreshPage();
		}
	}
	else if(wKeyCode==KEY_LEFT)
	{
		if(g_wMenuMode==MM_DATA)
		{
			g_wCycleCurSel = 0;
			if(g_wPageCurSel>0) g_wPageCurSel--;
			LEDClear();
			OnRefreshPage();
		}
		else if(g_wMenuMode==MM_SETUP)
		{
			g_wCycleCurSel = 0;
			if(g_wPageCurSel>0) g_wPageCurSel--;
			OnRefreshPageSetup();
// 			EditEnterEdit();
		}
	}
	else if(wKeyCode==KEY_RIGHT)
	{
		if(g_wMenuMode==MM_DATA)
		{
			g_wCycleCurSel = 0;
			if(g_wPageCurSel<3)	g_wPageCurSel++;
			LEDClear();
			OnRefreshPage();
		}
		else if(g_wMenuMode==MM_SETUP)
		{
			g_wCycleCurSel = 0;
			if(g_wPageCurSel<g_wPageAllCount)
			g_wPageCurSel++;
			OnRefreshPageSetup();
// 			EditEnterEdit();
		}
	}
	else if(wKeyCode==KEY_CANCEL)
	{
		if(g_wMenuMode!=MM_DATA)
		{
			g_wMenuMode = MM_DATA;
			g_wCycleCurSel = 0;
			g_wPageCurSel = 0;
			LEDClear();
			OnRefreshPage();
		}
	}
	else if(wKeyCode==KEY_RESET)
	{
		MyApp_OnResetDevice();
	}
}

void EnterPageSetup(void)
{
	g_wMenuMode = MM_SETUP;
	g_wCycleCurSel = 0;
	g_wPageCurSel = 0;
	OnRefreshPage();
}
