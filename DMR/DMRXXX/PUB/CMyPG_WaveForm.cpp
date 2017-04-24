/*
;*****************************************************************************************************
;*						Copyright (c) 2009 by ThinkBoy. 
;*						All rights reserved.
;*
;* Header:
;* File Name: 
;* Author: jimmy
;* Date:
;*****************************************************************************************************
;*/

#include "main.h"

extern CMyPG_WaveForm g_pageWaveForm;

void OnClickWFRStart(CMyEditButton* pButton)
{
	if(pButton==NULL) return;
	WORD wStatus = g_waveform.GetStatus();
	if(wStatus==WFRS_Recording)
	{
		g_waveform.Start(FALSE);
		pButton->ShowText(PROMPTINDEX_BUTTON_WFR_START_TEXT);
		pButton->SetPrompt(PROMPTINDEX_BUTTON_WFR_START);
	}
	else
	{
		g_pageWaveForm.m_pWaveForm = g_waveform.GetRecord(g_waveform.m_wCountNew);
		g_waveform.Start(TRUE);
		pButton->ShowText(PROMPTINDEX_BUTTON_WFR_STOP_TEXT);
		pButton->SetPrompt(PROMPTINDEX_BUTTON_WFR_STOP);
// 		g_hmi.DrawPrompt(PROMPTINDEX_ERROR);
// 		g_edit.DisablePrompt();
	}
	pButton->Display(FALSE);
}

void OnClickWFRSet(CMyEditButton* pButton)
{
	if(g_waveform.GetStatus()==WFRS_Recording)
	{
		g_hmi.DrawPrompt(PROMPTINDEX_ERROR_STOPRECORD);
		g_edit.DisablePrompt();
		return;
	}
	g_pageWaveForm.m_wDisplayType = DISPLAYTYPE_SET;
	g_pageWaveForm.DrawSet(RM_PAGEENTER);
// 	g_waveform.Start(FALSE);
}

void OnClickWFROpen(CMyEditButton* pButton)
{
	if(g_waveform.GetStatus()==WFRS_Recording)
	{
		g_hmi.DrawPrompt(PROMPTINDEX_ERROR_STOPRECORD);
		g_edit.DisablePrompt();
		return;
	}
	g_pageWaveForm.m_wDisplayType = DISPLAYTYPE_OPEN;
	g_pageWaveForm.DrawOpen(RM_PAGEENTER);
}

void CMyPG_WaveForm::OnRefresh(WORD wRefreshMode)
{
	if(wRefreshMode==RM_PAGEENTER || wRefreshMode==RM_PAGECANCEL)
	{
		m_wDisplayType = DISPLAYTYPE_DIS;
		m_wPageCnt = 0;
		m_wPageCur = 0;
		m_wWaveCnt = 0;
		if(wRefreshMode==RM_PAGEENTER) m_pWaveForm = g_waveform.GetRecord(g_waveform.m_wCountNew);
		g_lcd.CursorOFF();
		g_lcd.Clear();
		g_edit.OnInit();
		g_lcd.SetSmallFont();
		g_edit.SetCursorOffset(1,0);
		g_lcd.m_wAutoPosX = 15;
		// 	g_lcd.m_wAutoPosY = 20;
		g_lcd.m_wAutoPosY = g_deviceInfo.wLCDHeigh - 12*2 - 6 - 24;
		g_edit.AddEditButton(NULL,OnClickWFRStart,60,20,
			(g_waveform.GetStatus()!=WFRS_Recording)?PROMPTINDEX_BUTTON_WFR_START_TEXT:PROMPTINDEX_BUTTON_WFR_STOP_TEXT,
			BTST_ALIANVC|BTST_ALIANHC,
			(g_waveform.GetStatus()!=WFRS_Recording)?PROMPTINDEX_BUTTON_WFR_START:PROMPTINDEX_BUTTON_WFR_STOP);
		
		g_lcd.m_wAutoPosY = g_deviceInfo.wLCDHeigh - 12*2 - 6 - 24;
		g_lcd.m_wAutoPosX = 90;
		// 	g_lcd.m_wAutoPosY = 100;
		g_edit.AddEditButton(NULL,OnClickWFRSet,60,20,PROMPTINDEX_BUTTON_SET_TEXT,BTST_ALIANVC|BTST_ALIANHC,PROMPTINDEX_BUTTON_SET_TEXT);
		
		g_lcd.m_wAutoPosY = g_deviceInfo.wLCDHeigh - 12*2 - 6 - 24;
		g_lcd.m_wAutoPosX = 165;
		// 	g_lcd.m_wAutoPosY = 100;
		g_edit.AddEditButton(NULL,OnClickWFROpen,60,20,PROMPTINDEX_BUTTON_OPEN_TEXT,BTST_ALIANVC|BTST_ALIANHC,PROMPTINDEX_BUTTON_OPEN_TEXT);
		
		g_menu.m_bEditMode = TRUE;
		g_menu.m_bPrompt = TRUE;
		g_edit.EnableEdit(wRefreshMode);
		g_edit.OnRefreshPage();
	}

	if(m_wDisplayType==DISPLAYTYPE_SET)						// 显示设置
	{
		if(wRefreshMode) DrawSet(wRefreshMode);
	}
	else if(m_wDisplayType==DISPLAYTYPE_OPEN)				// 显示打开
	{
// 		if(wRefreshMode)
		DrawOpen(wRefreshMode);
	}
	else													// 显示主界面
	{
		DrawWave(wRefreshMode);
	}
}

WORD CMyPG_WaveForm::OnKeyMsg(WORD wKeyCode)
{
	if(wKeyCode==KEY_CANCEL)
	{
		if(m_wDisplayType!=DISPLAYTYPE_DIS)
		{
			m_wDisplayType = DISPLAYTYPE_DIS;
			OnRefresh(RM_PAGECANCEL);
			wKeyCode = KEY_NULL;
		}
	}
	else if(wKeyCode==KEY_UP || wKeyCode==KEY_LEFT)
	{
		if(m_wPageCur>0)
		{
			m_wPageCur--;
			OnRefresh((wKeyCode==KEY_UP)?RM_PAGEUP:RM_PAGELEFT);
			wKeyCode = KEY_NULL;
		}
	}
	else if(wKeyCode==KEY_DOWN || wKeyCode==KEY_RIGHT)
	{
		if(m_wPageCur+1<m_wPageCnt)
		{
			m_wPageCur++;
			OnRefresh((wKeyCode==KEY_DOWN)?RM_PAGEDOWN:RM_PAGERIGHT);
			wKeyCode = KEY_NULL;
		}
	}
	else if(wKeyCode==KEY_OK)
	{
		if(m_wDisplayType==DISPLAYTYPE_OPEN)
		{
			if(m_wWaveCnt)
				m_pWaveForm = g_waveform.GetRecord(m_wWaveNo[m_wPageCur]);
			wKeyCode = KEY_NULL;
			m_wDisplayType = DISPLAYTYPE_DIS;
// 			OnRefresh(RM_TIMER1S);
			OnRefresh(RM_PAGECANCEL);
		}
	}
	return wKeyCode;
}

void CMyPG_WaveForm::DrawSet(WORD wRefreshMode)
{
	short i;
	m_wDisplayType = DISPLAYTYPE_SET;
	g_lcd.CursorOFF();
	g_edit.OnInit();
	g_lcd.ClearBlock(46,46,194,274);
	g_lcd.DrawRect(46,46,194,274);
	g_lcd.DrawRect(50,50,190,270);
	g_lcd.DrawVLineExt(195,47,276,0xaa);
	g_lcd.DrawVLineExt(196,48,277,0xaa);
	g_lcd.DrawHLineExt(275,47,195,0xaa);
	g_lcd.DrawHLineExt(276,48,196,0xaa);

	m_wPageCnt = 2;
	
	g_lcd.SetSmallFont();
	g_lcd.SetTextAlignMode(TAMODE_LEFT);
	
	g_lcd.TextOut(108,54,MULTITEXT("设置","SET"));
	g_lcd.DrawHLine(68,50,190);
	for(i=0;i<10;i++) g_lcd.DrawHLineExt(68+(i+1)*18,50,190,0xaa);
	
	WORD wPosY;
	if(m_wPageCur==0)
	{
		for(i=0;i<8;i++)
		{
			// 		g_lcd.TextOut(54,54*i*12,"CH :");
			// 		g_lcd.TextOut(60,54*i*12,"0"+i);
			wPosY = 74 + i*18;
			g_lcd.AsciiOut(60,wPosY," CH :");
			g_lcd.ByteOut(78,wPosY,(BYTE)(i+1),1);
			g_lcd.m_wAutoPosY = 74 + 18*i;
			if(g_waveform.m_Setting.wOSCMode==0)
			{
				g_lcd.m_wAutoPosX = 160;
				g_edit.AddEditEnumMul(&g_waveform.m_Setting.wBIID[i]);
			}
			else
			{
				g_lcd.m_wAutoPosX = 154;
				g_edit.AddEditDataWord(&g_waveform.m_Setting.wBIID[i]);
			}
		}
		for(i=0;i<3;i++)
		{
			wPosY = 74 + (8+i)*18;
			if(i+9<10)
			{
				g_lcd.AsciiOut(60,wPosY," CH :");
				g_lcd.ByteOut(78,wPosY,(BYTE)(i+9),1);
			}
			else
			{
				g_lcd.AsciiOut(60,wPosY,"CH  :");
				g_lcd.ByteOut(72,wPosY,(BYTE)(i+9),2);
			}

			g_lcd.m_wAutoPosY = 74 + 18*(i+8);
			if(g_waveform.m_Setting.wOSCMode==0)
			{
				g_lcd.m_wAutoPosX = 160;
				g_edit.AddEditEnumMul(&g_waveform.m_Setting.wAIID[i]);
			}
			else
			{
				g_lcd.m_wAutoPosX = 154;
				g_edit.AddEditDataWord(&g_waveform.m_Setting.wAIID[i]);
			}
		}
	}
	else
	{
// 		wPosY = 72;		// + i*18;
		g_lcd.TextOut(60,72,MULTITEXT("采样间隔","SampleInteval"));
		g_lcd.m_wAutoPosX = 154;
		g_lcd.m_wAutoPosY = 74;//  + 18*i;
		g_edit.AddEditEnumMul(&g_waveform.m_Setting.wSampleInteval);

		g_lcd.TextOut(60,90,MULTITEXT("触发源","TrigSource"));
		g_lcd.m_wAutoPosX = 160;
		g_lcd.m_wAutoPosY = 92;//  + 18*i;
		g_edit.AddEditEnumMul(&g_waveform.m_Setting.wTrigSource);

		g_lcd.TextOut(60,108,MULTITEXT("触发方式","TrigType"));
		g_lcd.m_wAutoPosX = 160;
		g_lcd.m_wAutoPosY = 110;//  + 18*i;
		g_edit.AddEditEnumMul(&g_waveform.m_Setting.wTrigType);

		g_lcd.TextOut(60,126,MULTITEXT("触发门限","TrigThreshold"));
		g_lcd.m_wAutoPosX = 148;
		g_lcd.m_wAutoPosY = 128;//  + 18*i;
		g_edit.AddEditDataWord(&g_waveform.m_Setting.wTrigThreshold);

		g_lcd.TextOut(60,144,MULTITEXT("触发模式","TrigMode"));
		g_lcd.m_wAutoPosX = 160;
		g_lcd.m_wAutoPosY = 146;//  + 18*i;
		g_edit.AddEditEnumMul(&g_waveform.m_Setting.wTrigMode);
	}
	DrawScroll(190-SCROLLW,69,SCROLLW,201,m_wPageCnt,1,m_wPageCur);
	g_menu.m_bEditMode = TRUE;
	g_menu.m_bPrompt = TRUE;
	g_edit.EnableEdit(wRefreshMode);
	g_edit.OnRefreshPage();
}

void CMyPG_WaveForm::DrawOpen(WORD wRefreshMode)
{
	short i;
	g_edit.OnInit();
	g_lcd.CursorOFF();
	g_lcd.ClearBlock(40,46,200,274);
	g_lcd.DrawRect(40,46,200,274);
	g_lcd.DrawRect(44,50,196,270);
	g_lcd.DrawVLineExt(201,47,276,0xaa);
	g_lcd.DrawVLineExt(202,48,277,0xaa);
	g_lcd.DrawHLineExt(275,41,201,0xaa);
	g_lcd.DrawHLineExt(276,42,202,0xaa);
	m_wWaveCnt = 0;
	for(i=0;i<WFR_NUM-1;i++)
	{
		WORD wWaveNo = (g_deviceInfo.wCountWaveForm+1+i)%WFR_NUM;
		WAVEFORMRECORD* pWFR = g_waveform.GetRecord(wWaveNo);
		if(pWFR->wStatus!=WFRS_Recorded) continue;
		if(!CMyTime::IsTimeOK(&pWFR->TimeofRecord)) continue;
		m_wWaveNo[m_wWaveCnt++] = wWaveNo;
// 		m_wWaveCnt++;
	}
	g_lcd.SetSmallFont();
	g_lcd.SetTextAlignMode(TAMODE_LEFT);

	g_lcd.TextOut(108,54,MULTITEXT("打开","OPEN"));
	g_lcd.DrawHLine(68,44,196);
// 	for(i=0;i<10;i++) g_lcd.DrawHLineExt(68+(i+1)*18,50,190,0xaa);
	if(m_wWaveCnt==0)
	{
		g_lcd.SetTextAlignMode(TAMODE_CENTER);
		g_lcd.TextOut(g_lcd.m_wLCDCX/2,g_lcd.m_wLCDCY/2-6,MULTITEXT("(无录波)","(No recorded)"));
		g_lcd.SetTextAlignMode(TAMODE_LEFT);
		m_wPageCnt = 0;
		return;
	}
	for(i=0;i<10;i++) g_lcd.DrawHLineExt(69+(i+1)*18,44,196,0xaa);
	m_wPageCnt = m_wWaveCnt;
	for(i=0;i<m_wWaveCnt;i++)
	{
		DEVICETIME* pTime = &g_waveform.GetRecord(m_wWaveNo[i])->TimeofRecord;
		g_lcd.TextOut(46,72+18*i,"□");
		g_lcd.DateOut(61,74+18*i,pTime->wYear,pTime->wMonth,pTime->wDay);
		g_lcd.TimeOut(115,74+18*i,pTime->wHour,pTime->wMinute,pTime->wSecond,pTime->wMilliSecond);
	}
	g_lcd.m_bSetDataXor = TRUE;
	g_lcd.DrawBlock(46,70+18*m_wPageCur,194,70+16+18*m_wPageCur);
	g_lcd.m_bSetDataXor = FALSE;
}

void CMyPG_WaveForm::DrawWave(WORD wRefreshMode)
{
	MYRECT Rect;
	short i;
	WORD wPosY;
	m_wPageCnt = 0;
	g_lcd.SetSmallFont();
	g_lcd.SetTextAlignMode(TAMODE_LEFT);
// 	g_lcd.AsciiOut(2,3,"CH1");
	wPosY = 3;
	for(i=0;i<8;i++,wPosY += 12)
	{
		g_lcd.AsciiOut(2,wPosY," CH :");
		g_lcd.ByteOut(20,wPosY,i+1,1);
		Rect.wleft = 26;
		Rect.wtop = wPosY - 2;
		Rect.wbottom = Rect.wtop + 10;
		Rect.wright = g_lcd.m_wLCDCX - 2;
		ShowRTBinWave(&Rect,WFRSTYLE_FRAME_DOT|WFRBISTYLE_LINE,i);
	}

	for(i=0;i<3;i++,wPosY += 56)
	{
		if(i==0)
		{
			g_lcd.AsciiOut(2,wPosY," CH :");
			g_lcd.ByteOut(20,wPosY,i+9,1);
		}
		else
		{
			g_lcd.AsciiOut(2,wPosY,"CH  :");
			g_lcd.ByteOut(14,wPosY,i+9,2);
		}
		Rect.wleft = 26;
		Rect.wtop = wPosY-2;
		Rect.wbottom = Rect.wtop + 54;
		Rect.wright = g_lcd.m_wLCDCX - 2;
		WORD wID = g_waveform.m_Setting.wAIID[i];
		WORD wScale = g_waveforsource.GetAISacle(wID);
		if(g_waveform.m_Setting.wOSCMode==0)
			wScale= g_waveforsource.GetAISacleB(wID);
		ShowRTWave(&Rect,WFRSTYLE_FRAME_DOT,i,wScale);
	}

	CMyEdit* pEdit = g_edit.GetEditwithIndex(0);
	CMyEditButton* pEditButton = NULL;
	if(pEdit->m_wMode==EDITMODE_BUTTON)
	{
		WAVEFORMRECORD* pWFR = m_pWaveForm;
		WORD wStatus = g_waveform.m_wStatus;
		if(g_waveform.m_Setting.wTrigMode==TRIGMOD_AUTO)
		{
			if(wStatus==WFRS_Recording)				// 正在录波,切换到当前录波
			{
				pWFR = g_waveform.GetRecord(g_waveform.m_wCountNew);
				m_pWaveForm = pWFR;
			}
		}
		pEditButton = (CMyEditButton*)pEdit;
		if(wStatus!=WFRS_Recording)
		{
			pEditButton->ShowText(PROMPTINDEX_BUTTON_WFR_START_TEXT);
			pEditButton->SetPrompt(PROMPTINDEX_BUTTON_WFR_START);
		}
		else
		{
			pEditButton->ShowText(PROMPTINDEX_BUTTON_WFR_STOP_TEXT);
			pEditButton->SetPrompt(PROMPTINDEX_BUTTON_WFR_STOP);
		}
		
	}
}

// *************************************************************
// 
// 显示实时开关量波形
// 
// \param pRect:显示矩形框
// \param wStyle:显示风格
// \param wIndex:显示开关量索引
// 
// \return NULL
// 
// *************************************************************
void CMyPG_WaveForm::ShowBinWave(PMYRECT pRect,WAVEFORMRECORD* pWFR,WORD wStyle,WORD wIndex)
{
	g_lcd.ClearBlock(pRect->wleft,pRect->wtop,pRect->wright,pRect->wbottom);
	BYTE LineStyle = 0;
	if(wStyle&WFRSTYLE_FRAME_DOT) LineStyle = 0xaa;
	else if(wStyle&WFRSTYLE_FRAME_SOLID) LineStyle = 0xff;
	if(LineStyle)
	{
		g_lcd.DrawHLineExt(pRect->wtop,pRect->wleft,pRect->wright,LineStyle);
		g_lcd.DrawHLineExt(pRect->wbottom,pRect->wleft,pRect->wright,LineStyle);
		g_lcd.DrawVLineExt(pRect->wleft,pRect->wtop,pRect->wbottom,LineStyle);
		g_lcd.DrawVLineExt(pRect->wright,pRect->wtop,pRect->wbottom+1,LineStyle);
	}

	if(pWFR==NULL) return;
	long lDataHead = pWFR->wDataHead;
	long lDataTrail = pWFR->wDataTrail;
	if(lDataHead==lDataTrail) return;					// 没有数据
	if(wIndex>=8) return;

	WORD wStart = 0;
	DWORD dwPixs = ((DWORD)(pRect->wright-pRect->wleft)*1000L+ (WFR_DOTNUM-1)/2 )/(WFR_DOTNUM-1);			// 每个点占的像素点,保留3位小数
	BOOL bBIOld = pWFR->wData[lDataTrail][0]&(0x01<<wIndex);
	lDataTrail = (lDataTrail+1)%WFR_DOTNUM;

	if(wStyle&WFRBISTYLE_BLOCK)
	{
		short i = 0;
		for(i=1;lDataHead!=lDataTrail;i++,lDataTrail = (lDataTrail+1)%WFR_DOTNUM)
		{
			BOOL bBINew = pWFR->wData[lDataTrail][0]&(0x01<<wIndex);
			if(bBIOld!=bBINew)
			{
				if(bBIOld)
				{
					WORD wPosX1 = pRect->wleft+(WORD)((DWORD)wStart*dwPixs/1000);
					WORD wPosX2 = pRect->wleft+(WORD)((DWORD)i*dwPixs/1000);
					g_lcd.DrawBlock(wPosX1,pRect->wtop+1,wPosX2,pRect->wbottom-1);
				}
				wStart = i;
				bBIOld = bBINew;
			}
		}
		if(bBIOld)
		{
			WORD wPosX1 = pRect->wleft+(WORD)((DWORD)wStart*dwPixs/1000);
			WORD wPosX2;
// 			wDataCnt = (pWFR->wDataHead+i)%WFR_DOTNUM;
			if(i==WFR_DOTNUM-1) wPosX2 = pRect->wright;
			else wPosX2 = pRect->wleft+(WORD)((DWORD)i*dwPixs/1000);
			g_lcd.DrawBlock(wPosX1,pRect->wtop+1,wPosX2,pRect->wbottom-1);
		}
	}
	else if(wStyle&WFRBISTYLE_LINE)
	{
		short i = 0;
		for(i=1;lDataHead!=lDataTrail;i++,lDataTrail = (lDataTrail+1)%WFR_DOTNUM)
		{
// 			wDataCnt = (pWFR->wDataHead+i)%WFR_DOTNUM;
			BOOL bBINew = pWFR->wData[lDataTrail][0]&(0x01<<wIndex);
			if(bBIOld!=bBINew)
			{
				WORD wPosX1 = pRect->wleft+(WORD)((DWORD)wStart*dwPixs/1000);
				WORD wPosX2 = pRect->wleft+(WORD)((DWORD)i*dwPixs/1000);
				if(bBIOld) g_lcd.DrawHLine(pRect->wtop+2,wPosX1,wPosX2);
				else g_lcd.DrawHLine(pRect->wbottom-2,wPosX1,wPosX2);
				if(wStart) g_lcd.DrawVLine(wPosX1,pRect->wtop+2,pRect->wbottom-1);		// 不是第一次变化时画跳竖线
				wStart = i;
				bBIOld = bBINew;
			}
		}
		WORD wPosX1 = pRect->wleft+(WORD)((DWORD)wStart*dwPixs/1000);
		WORD wPosX2;
// 		WORD wDataCnt = (pWFR->wDataHead+i)%WFR_DOTNUM;
		if(i==WFR_DOTNUM-1) wPosX2 = pRect->wright;
		else wPosX2 = pRect->wleft+(WORD)((DWORD)i*dwPixs/1000);
		if(bBIOld) g_lcd.DrawHLine(pRect->wtop+2,wPosX1,wPosX2);
		else g_lcd.DrawHLine(pRect->wbottom-2,wPosX1,wPosX2);
		if(wStart) g_lcd.DrawVLine(wPosX1,pRect->wtop+2,pRect->wbottom-1);
	}
	else if(wStyle&WFRBISTYLE_BLINE)
	{
		short i = 0;
		for(i=1;lDataHead!=lDataTrail;i++,lDataTrail = (lDataTrail+1)%WFR_DOTNUM)
		{
//			wDataCnt = (pWFR->wDataHead+i)%WFR_DOTNUM;
			BOOL bBINew = pWFR->wData[lDataTrail][0]&(0x01<<wIndex);
			if(bBIOld!=bBINew)
			{
				WORD wPosX1 = pRect->wleft+(WORD)((DWORD)wStart*dwPixs/1000);
				WORD wPosX2 = pRect->wleft+(WORD)((DWORD)i*dwPixs/1000);
				WORD wLineWidth = (pRect->wbottom - pRect->wtop - 6)/2;
				if(wLineWidth==0) wLineWidth = 1;
				else if(wLineWidth>5) wLineWidth = 5;
				if(bBIOld) g_lcd.DrawBlock(wPosX1,pRect->wtop+2,wPosX2,pRect->wtop+wLineWidth+2);
				else g_lcd.DrawBlock(wPosX1,pRect->wbottom-wLineWidth-2,wPosX2,pRect->wbottom-2);
				if(wStart) g_lcd.DrawVLine(wPosX1,pRect->wtop+2,pRect->wbottom-1);		// 不是第一次变化时画跳竖线
				wStart = i;
				bBIOld = bBINew;
			}
		}
		WORD wPosX1 = pRect->wleft+(WORD)((DWORD)wStart*dwPixs/1000);
		WORD wPosX2;
// 		WORD wDataIndex = (pWFR->wDataHead+i)%WFR_DOTNUM;
		if(i==WFR_DOTNUM-1) wPosX2 = pRect->wright;
		else wPosX2 = pRect->wleft+(WORD)((DWORD)i*dwPixs/1000);
		WORD wLineWidth = (pRect->wbottom - pRect->wtop - 6)/2;
		if(wLineWidth==0) wLineWidth = 1;
		else if(wLineWidth>5) wLineWidth = 5;
		if(bBIOld) g_lcd.DrawBlock(wPosX1,pRect->wtop+2,wPosX2,pRect->wtop+wLineWidth+2);
		else g_lcd.DrawBlock(wPosX1,pRect->wbottom-wLineWidth-2,wPosX2,pRect->wbottom-2);
		if(wStart) g_lcd.DrawVLine(wPosX1,pRect->wtop+2,pRect->wbottom-1);
	}
}

// *************************************************************
// 
// 显示实时数据波形
// 
// \param pRect:显示矩形框
// \param wStyle:显示风格
// \param wIndex:显示数据索引
// \param dwMaxY:数据最大值
// 
// \return NULL
// 
// *************************************************************
void CMyPG_WaveForm::ShowWave(PMYRECT pRect,WAVEFORMRECORD* pWFR,WORD wStyle,WORD wIndex,DWORD dwMaxY)
{
	g_lcd.ClearBlock(pRect->wleft,pRect->wtop,pRect->wright,pRect->wbottom);
	BYTE LineStyle = 0;
	if(wStyle&WFRSTYLE_FRAME_DOT) LineStyle = 0xaa;
	else if(wStyle&WFRSTYLE_FRAME_SOLID) LineStyle = 0xff;
	if(LineStyle)
	{
		g_lcd.DrawHLineExt(pRect->wtop,pRect->wleft,pRect->wright,LineStyle);
		g_lcd.DrawHLineExt(pRect->wbottom,pRect->wleft,pRect->wright,LineStyle);
		g_lcd.DrawVLineExt(pRect->wleft,pRect->wtop,pRect->wbottom,LineStyle);
		g_lcd.DrawVLineExt(pRect->wright,pRect->wtop,pRect->wbottom+1,LineStyle);
	}

	if(pWFR==NULL) return;
	long lDataHead = pWFR->wDataHead;
	long lDataTrail = pWFR->wDataTrail;
	if(lDataHead==lDataTrail) return;					// 没有数据
	if(wIndex>=3) return;
// 	WAVEFORMRECORD* pwfr = g_waveformRecord.GetRecord(g_waveformRecord.m_wCountNew);
	DWORD dwPixsX = ((DWORD)(pRect->wright-pRect->wleft)*1000L+ WFR_DOTNUM/2 )/WFR_DOTNUM;			// 每个点占的像素点,保留3位小数
	DWORD dwPixsY = ((DWORD)(pRect->wbottom-pRect->wtop)*1000L+ dwMaxY/2 )/dwMaxY;					// 每个点占的像素点,保留3位小数

// 	g_app.GetWaveformData(&pWFR->wData[pWFR->wDataHead][0],FALSE);
	DWORD dwData1 = pWFR->wData[lDataTrail][wIndex+1];					// g_app.// pwfr->wData[0][0]&(0x01<<wIndex);
	lDataTrail = (lDataTrail + 1)%WFR_DOTNUM;
	DWORD dwData2 = 0;
	
	WORD wPosX1 = pRect->wleft;
	WORD wPosY1 = pRect->wbottom - (WORD)(dwData1*dwPixsY/1000);
	if(wPosY1<pRect->wtop) wPosY1 = pRect->wtop;

	short i = 0;
	for(i=1;lDataHead!=lDataTrail;i++,lDataTrail = (lDataTrail+1)%WFR_DOTNUM)
	{
		dwData2 = pWFR->wData[lDataTrail][wIndex+1];
		WORD wPosX2 = pRect->wleft + (WORD)((DWORD)i*dwPixsX/1000);
		WORD wPosY2 = pRect->wbottom - (WORD)(dwData2*dwPixsY/1000);
		if(wPosY2<pRect->wtop) wPosY2 = pRect->wtop;

		g_lcd.DrawXLine(wPosX1,wPosY1,wPosX2,wPosY2);
		wPosX1 = wPosX2;
		wPosY1 = wPosY2;
	}
}

void CMyPG_WaveForm::ShowRTBinWave(PMYRECT pRect,WORD wStyle,WORD wIndex)
{
	ShowBinWave(pRect,m_pWaveForm,wStyle,wIndex);
}

void CMyPG_WaveForm::ShowRTWave(PMYRECT pRect,WORD wStyle,WORD wIndex,DWORD dwMaxY)
{
	ShowWave(pRect,m_pWaveForm,wStyle,wIndex,dwMaxY);
}

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/

