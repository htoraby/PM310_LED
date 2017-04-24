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

// ��ʾ���:���߱߿�
#define WFRSTYLE_FRAME_DOT				0x0001

// ��ʾ���:ʵ�߱߿�
#define WFRSTYLE_FRAME_SOLID			0x0002

// ��������ʾ���:��ͼ
// ȱ��:���������ٶ���ʱ��������Ļ�ֱ��ʲ������޷��ֱ�
#define WFRBISTYLE_BLOCK				0x0004

// ��������ʾ���:����
// ȱ��:�������Ե���
#define WFRBISTYLE_LINE					0x0008

// ��������ʾ���:������
// ȱ��:�ڿؼ������խʱ�޷��ֱ�ߵ��ƽ,
//      �ںܿ�ʱ���������߿�Ȳ��̫��
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

