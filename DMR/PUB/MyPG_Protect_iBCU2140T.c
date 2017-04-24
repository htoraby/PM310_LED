#include <Main.h>

WORD g_wPGP_LINEY;								// ÿ�м��;
WORD g_wPGP_LINENUM;							// ÿҳ����;
WORD g_wPGP_LINEOFFSET;							// ��ʼ��Y����;
WORD g_wPGP_LINECFGX1;							// ��������:��������X����;
WORD g_wPGP_LINECFGX2;							// ��������:��������X����;
WORD g_wPGP_LINESETX1;							// ������ֵ:��������X����;
WORD g_wPGP_LINESETX2;							// ������ֵ:��ֵ����X����(�ұ߿���);
WORD g_wPGP_LINESETX3;							// ������ֵ:������ֵX����;
WORD g_wPGP_FONTWIDTH;							// ������;
WORD g_wOffset;
WORD g_wCountLine;
BOOL g_bDisplaySetpoint;

//-----------------------------------------------------------------------------
static char* PGPRT_GetProtectName(WORD wIndex)
{
	if(wIndex>=PROTECT_MAX1) return NULL;
	return MULTITEXT(c_protectActInfo[wIndex].pszName,c_protectActInfo[wIndex].pszNameEnglish);
}

static char* PGPRT_GetSetpointCfgName(WORD wIndex)
{
	if(wIndex>=8) return NULL;
	return MULTITEXT(c_setpointCfgInfo[wIndex].pszName,c_setpointCfgInfo[wIndex].pszNameEnglish);
}


//-----------------------------------------------------------------------------
void PGPRT_GetLinePosY(void)
{
	short nPosY = (short)(g_wCountLine-g_wPageCurSel*g_wPGP_LINENUM);
	if(nPosY>=0 && nPosY<g_wPGP_LINENUM) g_wLCDAutoPosY = (WORD)(g_wPGP_LINEOFFSET+nPosY*g_wPGP_LINEY);
	else g_wLCDAutoPosY = 0xffff;
}

void PGPRT_GetLinePosYExt(void)
{
	if(g_bPageLargeFont)
	{
		LCD_SetLargeFont();
		g_wLCDAutoPosY -= 2;
	}
	else
	{
		LCD_SetSmallFont();
		g_wLCDAutoPosY += 2;
	}
}

void PGPRT_OutProtectText(char* pszText)
{
	if(!g_bDisplaySetpoint) return;
	PGPRT_GetLinePosY();
	if(g_wLCDAutoPosY<LCD_CYDOT)
	{
		LCD_SetSmallFont();
		LCD_SetColor(COLOR_WHITE);
		LCD_TextOut(g_wPGP_LINESETX1,g_wLCDAutoPosY,"��");
		LCD_TextOut(g_wPGP_LINESETX1+12+g_wPGP_LINESETX1/2,g_wLCDAutoPosY,pszText);
	}
	g_wCountLine++;
}

void PGPRT_OutProtectName(WORD wIndex)
{
	PGPRT_GetLinePosY();
	if(g_wLCDAutoPosY<LCD_CYDOT)
	{
		LCD_SetSmallFont();
		LCD_SetColor(COLOR_WHITE);
		if(!g_bPageLargeFont) LCD_DrawHLineExt((WORD)(g_wLCDAutoPosY+5),g_wPGP_LINESETX1+18,g_wPGP_LINESETX3+g_wPGP_FONTWIDTH*4,0xaa);
		LCD_TextOut(g_wPGP_LINESETX1,g_wLCDAutoPosY,"��");
		LCD_TextOut(g_wPGP_LINESETX1+12+g_wPGP_LINESETX1/2,g_wLCDAutoPosY,PGPRT_GetProtectName(wIndex));
		PGPRT_GetLinePosYExt();
		LCD_AsciiOut(g_wPGP_LINESETX3+3*6+g_wPGP_FONTWIDTH,g_wLCDAutoPosY,"[   ]");
		LCD_SetColor(COLOR_LIGHTCYAN);
		g_wLCDAutoPosX = g_wPGP_LINESETX3+3*6+g_wPGP_FONTWIDTH*2;
		if(g_bDisplaySetpoint) LCD_AutoOutOFF_ON((WORD)(g_wProtectRun[wIndex]!=PROTECTTOG_ON));
		else EditG_AddEditEnumMul(&SETPOINTTOG(wIndex));
	}
	g_wCountLine++;
	g_wOffset = 0;
}

void PGPRT_OutProtectSetX(char* pszName,char* pszUnitage,WORD* pSetX)
{
	if(!g_bDisplaySetpoint) return;
	PGPRT_GetLinePosY();
	if(g_wLCDAutoPosY<LCD_CYDOT)
	{
		LCD_SetSmallFont();
		LCD_SetColor(COLOR_WHITE);
		LCD_SetTextAlignMode(TAMODE_RIGHT);
		LCD_TextOut(g_wPGP_LINESETX2,g_wLCDAutoPosY,pszName);
		LCD_SetTextAlignMode(TAMODE_LEFT);
		LCD_TextOut(g_wPGP_LINESETX3+6+6*g_wPGP_FONTWIDTH,g_wLCDAutoPosY,pszUnitage);
		g_wLCDAutoPosX = g_wPGP_LINESETX3+g_wOffset*g_wPGP_FONTWIDTH;
		PGPRT_GetLinePosYExt();
		LCD_SetColor(COLOR_LIGHTCYAN);
		EditG_AddEditDataWord(pSetX);
	}
	g_wCountLine++;
	g_wOffset = 0;
}

void PGPRT_OutProtectTog(char* pszName,WORD* pStatusTog)
{
	if(!g_bDisplaySetpoint) return;
	PGPRT_GetLinePosY();
	if(g_wLCDAutoPosY<LCD_CYDOT)
	{
		LCD_SetSmallFont();
		LCD_SetColor(COLOR_WHITE);
		LCD_SetTextAlignMode(TAMODE_RIGHT);
		LCD_TextOut(g_wPGP_LINESETX2,g_wLCDAutoPosY,pszName);
		LCD_SetTextAlignMode(TAMODE_LEFT);
		g_wLCDAutoPosX = g_wPGP_LINESETX3+g_wOffset*g_wPGP_FONTWIDTH;
		PGPRT_GetLinePosYExt();
		LCD_SetColor(COLOR_LIGHTCYAN);
		EditG_AddEditEnumMul(pStatusTog);
	}
	g_wCountLine++;
	g_wOffset = 0;
}

void PGPRT_OutProtectINsetpoint(WORD wIndex)
{
	INSETPOINT* pINSetpoint;

	if(wIndex>=INSETPOINTNUM) return;
	pINSetpoint = &g_deviceSetpoint.INSetpoint[wIndex];
	if(pINSetpoint->wConfig==PROTECTCFG_NULL||pINSetpoint->wLinkIN==LINKIN_NULL) return;
	PGPRT_GetLinePosY();
	if(g_wLCDAutoPosY<LCD_CYDOT)
	{
		LCD_SetSmallFont();
		LCD_SetColor(COLOR_WHITE);
		LCD_TextOut(g_wPGP_LINESETX1,g_wLCDAutoPosY,"��");
		LCD_TextOut(g_wPGP_LINESETX1+12+g_wPGP_LINESETX1/2,g_wLCDAutoPosY,
			MULTITEXT(&g_szINName[g_inparamTable.inparam[pINSetpoint->wLinkIN-1].wName],&g_szINNameE[g_inparamTable.inparam[pINSetpoint->wLinkIN-1].wName]));
		PGPRT_GetLinePosYExt();
		LCD_AsciiOut(g_wPGP_LINESETX3+3*6+g_wPGP_FONTWIDTH,g_wLCDAutoPosY,"[   ]");
		LCD_SetColor(COLOR_LIGHTCYAN);
		g_wLCDAutoPosX = g_wPGP_LINESETX3+3*6+g_wPGP_FONTWIDTH*2;
		if(g_bDisplaySetpoint) LCD_AutoOutOFF_ON((WORD)(g_wProtectRunIN[wIndex]!=PROTECTTOG_ON));
		else EditG_AddEditEnumMul(&pINSetpoint->wToggle);
	}
	g_wCountLine++;
	g_wOffset = 0;
}

// void PGPRT_OutProtectUsersetpoint(WORD wIndex)
// {
// 	if(wIndex>=USERSETPOINTNUM) return;
// 	USERSETPOINT* pUserSetpoint = &g_deviceSetpoint.userSetpoint[wIndex];
// 	if(pUserSetpoint->wszName[0]==0&&pUserSetpoint->wConfig==PROTECTCFG_NULL) return;
// 	GetLinePosY();
// 	if(g_wLCDAutoPosY<g_wLCDLCDCY)
// 	{
// 		LCD_SetSmallFont();
// 		LCD_SetColor(COLOR_WHITE);
// 		LCD_TextOut(g_wPGP_LINESETX1,g_wLCDAutoPosY,"��");
// 		if(pUserSetpoint->wszNage[0]) LCD_TextOutW(g_wPGP_LINESETX1+12+g_wPGP_LINESETX1/2,g_wLCDAutoPosY,pUserSetpoint->wszName);
// 		else LCD_TextOut(g_wPGP_LINESETX1+12+g_wPGP_LINESETX1/2,g_wLCDAutoPosY,"--------");
// 		GetLinePosYExt();
// 		LCD_AsciiOut(g_wPGP_LINESETX3+3*6+g_wPGP_FONTWIDTH,g_wLCDAutoPosY,"[   ]");
// 		LCD_SetColor(COLOR_LIGHTCYAN);
// 		g_wLCDAutoPosX = g_wPGP_LINESETX3+3*6+g_wPGP_FONTWIDTH*2;
// 		if(g_bDisplaySetpoint) LCD_AutoOutOFF_ON((WORD)(g_protect.g_wProtectRunUser[wIndex]!=PROTECTTOG_ON));
// 		else g_edit.AddEditEnumMul(&pUserSetpoint->wToggle);
// 	}
// 	g_wCountLine++;
// 	g_wOffset = 0;
// }

void PGPRT_OnRPProtectConfig(DWORD dwProtectCFG,WORD wSetpointCfg,BOOL bINSetpoint,BOOL bUserSetpoint)
{
	WORD i;
	char *pszProtectName,*pszSetpointCfgName;
	WORD wOffsetX;
	char Data[2] = {0,0};

	g_wOffset = 0;
	g_wCountLine = 0;
	g_wLCDAutoEnter = g_wPGP_LINEY;

	for(i=0;i<PROTECT_MAX1;i++)
	{
		if((dwProtectCFG&(1L<<i))==0) continue;
		pszProtectName = PGPRT_GetProtectName(i);
		if(pszProtectName==NULL) continue;
		PGPRT_GetLinePosY();
		if(g_wLCDAutoPosY<LCD_CYDOT)
		{
			LCD_SetSmallFont();
			LCD_SetColor(COLOR_WHITE);
			if(g_wCountLine<9)
				LCD_ByteOut(g_wPGP_LINECFGX1+6,(WORD)(g_wLCDAutoPosY+2),(BYTE)(g_wCountLine+1),1);
			else 
				LCD_ByteOut(g_wPGP_LINECFGX1,(WORD)(g_wLCDAutoPosY+2),(BYTE)(g_wCountLine+1),2);
			LCD_AsciiOut(g_wPGP_LINECFGX1+12,(WORD)(g_wLCDAutoPosY+2),".");
			LCD_TextOut(g_wPGP_LINECFGX1+18+g_wPGP_LINECFGX1/2,g_wLCDAutoPosY,pszProtectName);
			PGPRT_GetLinePosYExt();
			LCD_AsciiOut(g_wPGP_LINECFGX2-(g_wPGP_FONTWIDTH*5+2)/4,g_wLCDAutoPosY,"[\1   ]");
			LCD_SetColor(COLOR_LIGHTCYAN);
			g_wLCDAutoPosX = g_wPGP_LINECFGX2;
			EditG_AddEditEnumMul(&SETPOINTCFG(i));
		}
		g_wCountLine++;
	}
//	for(i=0;i<2;i++)
//	{
//		if((wSetpointCfg&(1L<<1))==0) continue;
		pszSetpointCfgName = PGPRT_GetSetpointCfgName(1);
//		if(pszSetpointCfgName==NULL) continue;
		PGPRT_GetLinePosY();
		if(g_wLCDAutoPosY<LCD_CYDOT)
		{
			LCD_SetSmallFont();
			LCD_SetColor(COLOR_WHITE);
			LCD_TextOut(g_wPGP_LINECFGX1,g_wLCDAutoPosY,pszSetpointCfgName);
			PGPRT_GetLinePosYExt();
			LCD_AsciiOut(g_wPGP_LINECFGX2-(g_wPGP_FONTWIDTH*5+2)/4,g_wLCDAutoPosY,"[\1   ]");
			LCD_SetColor(COLOR_LIGHTCYAN);
			g_wLCDAutoPosX = g_wPGP_LINECFGX2;
			EditG_AddEditEnumMul(&g_deviceSetpoint.wSetpointConfig[1]);
		}
		g_wCountLine++;
//	}
	if(bINSetpoint)
	{
		for(i=0;i<INSETPOINTNUM;i++)
		{
			PGPRT_GetLinePosY();
			if(g_wLCDAutoPosY<LCD_CYDOT)
			{
// 				char Data[2] = {0,0};
				LCD_SetSmallFont();
				LCD_SetColor(COLOR_WHITE);
				LCD_ByteOut(g_wPGP_LINECFGX1,(WORD)(g_wLCDAutoPosY+2),(BYTE)(i+1),1);
				LCD_AsciiOut(g_wPGP_LINECFGX1+6,(WORD)(g_wLCDAutoPosY+2),".");
				LCD_TextOut(g_wPGP_LINECFGX1+12+g_wPGP_LINECFGX1/2,g_wLCDAutoPosY,MULTITEXT("����������","BIN. PRO"));
				Data[0] = '0' + (char)(i+1);
				wOffsetX = (g_deviceParam.wMultiLanguage==0)?60:48;
				LCD_TextOut(g_wPGP_LINECFGX1+12+g_wPGP_LINECFGX1/2+wOffsetX,g_wLCDAutoPosY,Data);
				PGPRT_GetLinePosYExt();
				LCD_AsciiOut(g_wPGP_LINECFGX2-(g_wPGP_FONTWIDTH*5+2)/4,g_wLCDAutoPosY,"[\1   ]");
				LCD_SetColor(COLOR_LIGHTCYAN);
				g_wLCDAutoPosX = g_wPGP_LINECFGX2;
				EditG_AddEditEnumMul(&g_deviceSetpoint.INSetpoint[i].wConfig);
			}
			g_wCountLine++;
			PGPRT_GetLinePosY();
			if(g_wLCDAutoPosY<LCD_CYDOT)
			{
				LCD_SetSmallFont();
				LCD_TextOut(g_wPGP_LINECFGX1+12+g_wPGP_LINECFGX1/2,g_wLCDAutoPosY,MULTITEXT("����������","LINK"));
				PGPRT_GetLinePosYExt();
				LCD_AsciiOut(g_wPGP_LINECFGX2-(g_wPGP_FONTWIDTH*9+2)/4,g_wLCDAutoPosY,"[\1    ]");
				LCD_SetColor(COLOR_LIGHTCYAN);
				g_wLCDAutoPosX = g_wPGP_LINECFGX2-g_wPGP_FONTWIDTH;
				EditG_AddEditEnumMul(&g_deviceSetpoint.INSetpoint[i].wLinkIN);
			}
			g_wCountLine++;
		}
	}
	Menu_SetPageCount((WORD)((g_wCountLine+g_wPGP_LINENUM-1)/g_wPGP_LINENUM));
}

// void PGPRT_OnRPProtectTripMatrix(DWORD dwProtectCFG,BOOL bUserSetpoint)
// {
// 	WORD i;
// 	g_wOffset = 0;
// 	g_wCountLine = 0;
// 	g_wLCDAutoEnter = g_wPGP_LINEY;
// 
// 	for(i=0;i<PROTECT_MAX1;i++)
// 	{
// 		if((dwProtectCFG&(1L<<i))==0) continue;
// 		char* pszProtectName = GetProtectName(i);
// 		if(pszProtectName==NULL) continue;
// 		if(SETPOINTCFG(i)==PROTECTCFG_NULL) continue;
// 		GetLinePosY();
// 		if(g_wLCDAutoPosY<g_wLCDLCDCY)
// 		{
// 			LCD_SetSmallFont();
// 			LCD_SetColor(COLOR_WHITE);
// 			LCD_TextOut(g_wPGP_LINESETX1,g_wLCDAutoPosY,"��");
// 			LCD_TextOut(g_wPGP_LINECFGX1+12+g_wPGP_LINECFGX1/2,g_wLCDAutoPosY,pszProtectName);
// 			GetLinePosYExt();
// 			LCD_AsciiOut(g_wPGP_LINECFGX2-(g_wPGP_FONTWIDTH*5+2)/4,g_wLCDAutoPosY,"[\1   ]");
// 			LCD_SetColor(COLOR_LIGHTCYAN);
// 			g_wLCDAutoPosX = g_wPGP_LINECFGX2;
// 			g_edit.AddEditBinWord(&SETPOINTMTX(i));
// 		}
// 		g_wCountLine++;
// 	}
// 	for(i=0;i<INSETPOINTNUM;i++)
// 	{
// 		GetLinePosY();
// 		INSETPOINT* pINSetpoint = &g_deviceSetpoint.INSetpoint[i];
// 		if(pINSetpoint->wConfig==PROTECTCFG_NULL||pINSetpoint->wLinkIN==LINKIN_NULL) continue;
// 		if(g_wLCDAutoPosY<g_wLCDLCDCY)
// 		{
// // 			char Data[2] = {0,0};
// 			LCD_SetSmallFont();
// 			LCD_SetColor(COLOR_WHITE);
// 			LCD_TextOut(g_wPGP_LINESETX1,g_wLCDAutoPosY,"��");
// 			LCD_TextOutW(g_wPGP_LINESETX1+12+g_wPGP_LINESETX1/2,g_wLCDAutoPosY,g_inparamTable.inparam[pINSetpoint->wLinkIN-1].wszName);
// 			GetLinePosYExt();
// 			LCD_AsciiOut(g_wPGP_LINECFGX2-(g_wPGP_FONTWIDTH*5+2)/4,g_wLCDAutoPosY,"[\1   ]");
// 			LCD_SetColor(COLOR_LIGHTCYAN);
// 			g_wLCDAutoPosX = g_wPGP_LINECFGX2;
// 			g_edit.AddEditBinWord(&pINSetpoint->wTripMatrix);
// 		}
// 		g_wCountLine++;
// 	}
// 	if(bUserSetpoint)
// 	{
// 		for(WORD i=0;i<USERSETPOINTNUM;i++)
// 		{
// 			GetLinePosY();
// 			USERSETPOINT* pUserSetpoint = &g_deviceSetpoint.userSetpoint[i];
// 			if(pUserSetpoint->wszName[0]==0&&pUserSetpoint->wConfig==PROTECTCFG_NULL) continue;
// 			if(g_wLCDAutoPosY<g_wLCDLCDCY)
// 			{
// 				LCD_SetSmallFont();
// 				LCD_SetColor(COLOR_WHITE);
// 				LCD_TextOut(g_wPGP_LINESETX1,g_wLCDAutoPosY,"��");
// 				if(g_deviceSetpoint.userSetpoint[i].wszName[0]==0) LCD_TextOut(g_wPGP_LINECFGX1+12+g_wPGP_LINECFGX1/2,g_wLCDAutoPosY,"--------");
// 				else LCD_TextOutW(g_wPGP_LINECFGX1+12+g_wPGP_LINECFGX1/2,g_wLCDAutoPosY,g_deviceSetpoint.userSetpoint[i].wszName);
// 				GetLinePosYExt();
// 				LCD_AsciiOut(m_wPGP_LINECFGX2-(m_wPGP_FONTWIDTH*5+2)/4,g_wLCDAutoPosY,"[\1   ]");
// 				LCD_SetColor(COLOR_LIGHTCYAN);
// 				g_wLCDAutoPosX = m_wPGP_LINECFGX2;
// 				g_edit.AddEditBinWord(&pUserSetpoint->wTripMatrix);
// 			}
// 			m_wCountLine++;
// 		}
// 	}
// 
// 	if(m_wCountLine==0)
// 	{
// 		LCD_Clear();
// 		LCD_SetSmallFont();
// 		LCD_SetColor(COLOR_WHITE);
// 		LCD_SetTextAlignMode(TAMODE_CENTER);
// 		if(g_deviceInfo.wLCDWidth>180)
// 			LCD_TextOut(g_wLCDLCDCX/2,g_wLCDLCDCY/2-6,MULTITEXT("(��������δ����)","(NO PROTECTION CONFIGURED)"));
// 		else 
// 			LCD_TextOut(g_wLCDLCDCX/2,g_wLCDLCDCY/2-6,MULTITEXT("(��������δ����)","(NO PROTEC CONFIG)"));
// 		LCD_SetTextAlignMode(TAMODE_LEFT);
// 		g_menu.SetPageCount(1);
// 		return;
// 	}
// 
// 	g_menu.SetPageCount((WORD)((m_wCountLine+m_wPGP_LINENUM-1)/m_wPGP_LINENUM));
// }

// void PGPRT_OnRPSetpointAreaSelect(void)
// {
// 	g_wLCDAutoPosX = g_wLCDLCDCX/2+18;
// 	g_wLCDAutoPosY = g_wLCDLCDCY/2-4;
// 	LCD_SetSmallFont();
// 	LCD_SetTextAlignMode(TAMODE_RIGHT);
// 	LCD_TextOut(g_wLCDLCDCX/2+12,g_wLCDLCDCY/2-6,MULTITEXT("��ǰ��ֵ��:","SELECTION:"));
// 	LCD_SetTextAlignMode(TAMODE_LEFT);
// 	LCD_SetColor(COLOR_LIGHTCYAN);
// 	if(g_menu.m_bPageLargeFont)
// 	{
// 		LCD_SetLargeFont();
// 		g_wLCDAutoPosY -= 4;
// 	}
// 	g_edit.AddEditEnumMul(&g_deviceSetpoint.wProtectSetpointArea);
// }

void PGPRT_OnRefreshPage(WORD* pDeviceSetpoint,BOOL bDisplaySetpoint)
{
	WORD i = 0;
	WORD wPageCurSel;

	g_wOffset = 0;
	g_wCountLine = 0;
	g_bDisplaySetpoint = bDisplaySetpoint;
	PGPRT_iiiOnRefreshPage(pDeviceSetpoint);
	for(i=0;i<INSETPOINTNUM;i++) PGPRT_OutProtectINsetpoint(i);
	if(g_wCountLine==0)
	{
		LCD_Clear();
		LCD_SetSmallFont();
		LCD_SetColor(COLOR_WHITE);
		LCD_SetTextAlignMode(TAMODE_CENTER);
		LCD_TextOut(LCD_CXDOT/2,LCD_CYDOT/2-6,MULTITEXT("(��������δ����)","(NO PROTECT CONFIG)"));
		LCD_SetTextAlignMode(TAMODE_LEFT);
		Menu_SetPageCount(1);
		return;
	}
	wPageCurSel = g_wPageCurSel;
	Menu_SetPageCount((WORD)((g_wCountLine-1)/g_wPGP_LINENUM+1));
	if(wPageCurSel!=g_wPageCurSel) PGPRT_OnRefreshPage(pDeviceSetpoint,bDisplaySetpoint);
}

