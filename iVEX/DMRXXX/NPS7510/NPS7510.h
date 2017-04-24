/*
;*****************************************************************************************************
;*						Copyright (c) 2000-2012 ThinkBon. 
;*						All rights reserved.
;*
;* Header:
;* File Name: NPS7510.h
;* Author: iVexMaker
;* Date: 2015-08-12 13:26:09 32 - Wednesday
;*****************************************************************************************************
;*/
#ifndef _NPS7510_H
#define _NPS7510_H


class CMyIEDNPS7510:public CMyIED
{
public:
    DECLARE_SERIAL(CMyIEDNPS7510);
    CMyIEDNPS7510();
    ~CMyIEDNPS7510();

public:
// LCD
    CMyObjLCD* m_pLCD;

// Key
    CMyObjKey* m_pKeyUp;
    CMyObjKey* m_pKeyDown;
//     CMyObjKey* m_pKeyLeft;
//     CMyObjKey* m_pKeyRight;
    CMyObjKey* m_pKeyOK;
    CMyObjKey* m_pKeyCancel;
//     CMyObjKey* m_pKeyReset;
//     CMyObjKey* m_pKeyAdd;
//     CMyObjKey* m_pKeySub;

// Light
//     CMyObjLight* m_pLightRun;
//     CMyObjLight* m_pLightTripped;
//     CMyObjLight* m_pLightAlarmed;
//     CMyObjLight* m_pLightOpened;
//     CMyObjLight* m_pLightClosed;

public:
    virtual void OnCreate(void);
    virtual void OnMainInit(void);
    virtual void OnMainTimer1ms(void);
    virtual void OnMainTimer10ms(void);
    virtual void OnMainTimer250ms(void);
    virtual void OnMainTimer1000ms(void);
    virtual void OnMainWhileLoop(void);
    virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

public:
//     void GetACWaveData(int nIndex,unsigned short* pWaveData,float f2Scale,unsigned short wDotNum);
    void GetACWaveDataEx(int nIndex, WORD* pData, float fSampRate, /*float fRate,*/ float f2Scale, short nSampDot, BOOL bBreakPos = TRUE);

};

#endif /*_NPS7510_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/
