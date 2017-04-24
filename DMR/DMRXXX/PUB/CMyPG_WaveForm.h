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

#ifndef __CMYPG_WAVEFORM_H
#define __CMYPG_WAVEFORM_H

enum DISPLAYTYPE
{
	 DISPLAYTYPE_DIS = 0
	,DISPLAYTYPE_SET
	,DISPLAYTYPE_OPEN
};

// 显示风格:虚线边框
#define WFRSTYLE_FRAME_DOT				0x0001

// 显示风格:实线边框
#define WFRSTYLE_FRAME_SOLID			0x0002

// 开关量显示风格:块图
// 缺点:开关量快速抖动时会由于屏幕分辨率不够而无法分辨
#define WFRBISTYLE_BLOCK				0x0004

// 开关量显示风格:线条
// 缺点:线条稍显单薄
#define WFRBISTYLE_LINE					0x0008

// 开关量显示风格:粗线条
// 缺点:在控件区域很窄时无法分辨高点电平,
//      在很宽时横线与竖线宽度差别太大
#define WFRBISTYLE_BLINE				0x0010

class CMyPG_WaveForm
{
// public:
// 	void OnInit(void);
public:
	WORD m_wDisplayType;
	WORD m_wPageCnt;
	WORD m_wPageCur;
	WAVEFORMRECORD * m_pWaveForm;
	WORD m_wWaveNo[WFR_NUM];
	WORD m_wWaveCnt;

public:
	void OnRefresh(WORD wRefreshMode);
	WORD OnKeyMsg(WORD wKeyCode);

public:
	void DrawSet(WORD wRefreshMode);
	void DrawOpen(WORD wRefreshMode);
	void DrawWave(WORD wRefreshMode);

public:
	void ShowRTBinWave(PMYRECT pRect,WORD wStyle,WORD wIndex);
	void ShowRTWave(PMYRECT pRect,WORD wStyle,WORD wIndex,DWORD dwMaxY);

protected:
	void ShowBinWave(PMYRECT pRect,WAVEFORMRECORD* pWFR,WORD wStyle,WORD wIndex);
	void ShowWave(PMYRECT pRect,WAVEFORMRECORD* pWFR,WORD wStyle,WORD wIndex,DWORD dwMaxY);
};

#endif/*__CMYPG_WAVEFORM_H*/


/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/

