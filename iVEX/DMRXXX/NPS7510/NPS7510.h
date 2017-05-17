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
//     CMyObjLCD* m_pLCD;

// Key
    CMyObjKey* m_pKeyV;
    CMyObjKey* m_pKeyA;
    CMyObjKey* m_pKeyP;
    CMyObjKey* m_pKeyE;

// MutilLED
    CMyObjLEDStatus* m_pLEDSLogo;
    CMyObjLEDStatus* m_pLEDSNeg1;
    CMyObjLEDStatus* m_pLEDSNeg2;
    CMyObjLEDStatus* m_pLEDSNeg3;
    CMyObjLEDStatus* m_pLEDSNegS;
    CMyObjLEDStatus* m_pLEDSA1;
    CMyObjLEDStatus* m_pLEDSB1;
    CMyObjLEDStatus* m_pLEDSC1;
    CMyObjLEDStatus* m_pLEDSB2;
    CMyObjLEDStatus* m_pLEDSC2;
    CMyObjLEDStatus* m_pLEDSA2;
    CMyObjLEDStatus* m_pLEDSDash1;
    CMyObjLEDStatus* m_pLEDSDash2;
    CMyObjLEDStatus* m_pLEDSDash3;

    CMyObjLEDStatus* m_pLEDSN1;
    CMyObjLEDStatus* m_pLEDSN2;
    CMyObjLEDStatus* m_pLEDSN3;
    CMyObjLEDStatus* m_pLEDSSigma1;
    CMyObjLEDStatus* m_pLEDSSigma2;
    CMyObjLEDStatus* m_pLEDSSigma3;

    CMyObjLEDStatus* m_pLEDSMAX;
    CMyObjLEDStatus* m_pLEDSMIN;
    CMyObjLEDStatus* m_pLEDSDemand;

    CMyObjLEDStatus* m_pLEDSBPH;
    CMyObjLEDStatus* m_pLEDSL;
    CMyObjLEDStatus* m_pLEDSC;
    CMyObjLEDStatus* m_pLEDSAvg;
    CMyObjLEDStatus* m_pLEDSSum;
    CMyObjLEDStatus* m_pLEDSImp;
    CMyObjLEDStatus* m_pLEDSExp;
    CMyObjLEDStatus* m_pLEDSNet;
    CMyObjLEDStatus* m_pLEDSTotal;
    CMyObjLEDStatus* m_pLEDSNum1;
    CMyObjLEDStatus* m_pLEDSNum2;
    CMyObjLEDStatus* m_pLEDSNum3;
    CMyObjLEDStatus* m_pLEDSNum4;
    CMyObjLEDStatus* m_pLEDSTime;

    CMyObjLEDStatus* m_pLEDS2;

    CMyObjLEDStatus* m_pLEDS4;
    CMyObjLEDStatus* m_pLEDS5;
    CMyObjLEDStatus* m_pLEDS5Dot;
    CMyObjLEDStatus* m_pLEDS6;
    CMyObjLEDStatus* m_pLEDS6Dot;
    CMyObjLEDStatus* m_pLEDS7;
    CMyObjLEDStatus* m_pLEDS7Dot;

    CMyObjLEDStatus* m_pLEDS8;
    CMyObjLEDStatus* m_pLEDS9;
    CMyObjLEDStatus* m_pLEDS9Dot;
    CMyObjLEDStatus* m_pLEDS10;
    CMyObjLEDStatus* m_pLEDS10Dot;
    CMyObjLEDStatus* m_pLEDS11;
    CMyObjLEDStatus* m_pLEDS11Dot;

    CMyObjLEDStatus* m_pLEDS12;
    CMyObjLEDStatus* m_pLEDS13;
    CMyObjLEDStatus* m_pLEDS13Dot;
    CMyObjLEDStatus* m_pLEDS14;
    CMyObjLEDStatus* m_pLEDS14Dot;
    CMyObjLEDStatus* m_pLEDS15;
    CMyObjLEDStatus* m_pLEDS15Dot;

    CMyObjLEDStatus* m_pLEDS21;
    CMyObjLEDStatus* m_pLEDS22;
    CMyObjLEDStatus* m_pLEDS22Dot;
    CMyObjLEDStatus* m_pLEDS23;
    CMyObjLEDStatus* m_pLEDS23Dot;
    CMyObjLEDStatus* m_pLEDS24;
    CMyObjLEDStatus* m_pLEDS24Dot;
    CMyObjLEDStatus* m_pLEDS25;
    CMyObjLEDStatus* m_pLEDS25Dot;
    CMyObjLEDStatus* m_pLEDS26;
    CMyObjLEDStatus* m_pLEDS26Dot;
    CMyObjLEDStatus* m_pLEDS27;
    CMyObjLEDStatus* m_pLEDS27Dot;
    CMyObjLEDStatus* m_pLEDS28;
    CMyObjLEDStatus* m_pLEDS28Dot;
    CMyObjLEDStatus* m_pLEDS29;
    CMyObjLEDStatus* m_pLEDS29Dot;

    CMyObjLEDStatus* m_pLEDSCO1;
    CMyObjLEDStatus* m_pLEDSCO2;
    CMyObjLEDStatus* m_pLEDSCO3;
    CMyObjLEDStatus* m_pLEDSCO4;

    CMyObjLEDStatus* m_pLEDSDI;
    CMyObjLEDStatus* m_pLEDSDIOFDI1;
    CMyObjLEDStatus* m_pLEDSDIOHDI1;
    CMyObjLEDStatus* m_pLEDSDIOFDI2;
    CMyObjLEDStatus* m_pLEDSDIOHDI2;
    CMyObjLEDStatus* m_pLEDSDIOFDI3;
    CMyObjLEDStatus* m_pLEDSDIOHDI3;
    CMyObjLEDStatus* m_pLEDSDIOFDI4;
    CMyObjLEDStatus* m_pLEDSDIOHDI4;

    CMyObjLEDStatus* m_pLEDSDO;
    CMyObjLEDStatus* m_pLEDSDIOFDO1;
    CMyObjLEDStatus* m_pLEDSDIOHDO1;
    CMyObjLEDStatus* m_pLEDSDIOFDO2;
    CMyObjLEDStatus* m_pLEDSDIOHDO2;

    CMyObjLEDStatus* m_pLEDSCOM;
    CMyObjLEDStatus* m_pLEDSPC;
    CMyObjLEDStatus* m_pLEDSTX;
    CMyObjLEDStatus* m_pLEDSRX;

    CMyObjLEDStatus* m_pLEDSV;
    CMyObjLEDStatus* m_pLEDSKV;
    CMyObjLEDStatus* m_pLEDSKW;
    CMyObjLEDStatus* m_pLEDSMW;
    CMyObjLEDStatus* m_pLEDSArrow1;
    CMyObjLEDStatus* m_pLEDSBar10;
    CMyObjLEDStatus* m_pLEDSBar11;
    CMyObjLEDStatus* m_pLEDSBar12;
    CMyObjLEDStatus* m_pLEDSBar13;
    CMyObjLEDStatus* m_pLEDSBar14;
    CMyObjLEDStatus* m_pLEDSBar15;
    CMyObjLEDStatus* m_pLEDSBar16;
    CMyObjLEDStatus* m_pLEDSAlarm1;

    CMyObjLEDStatus* m_pLEDSA;
    CMyObjLEDStatus* m_pLEDSKA;
    CMyObjLEDStatus* m_pLEDSPF;
    CMyObjLEDStatus* m_pLEDSKVar;
    CMyObjLEDStatus* m_pLEDSMVar;
    CMyObjLEDStatus* m_pLEDSArrow2;
    CMyObjLEDStatus* m_pLEDSBar20;
    CMyObjLEDStatus* m_pLEDSBar21;
    CMyObjLEDStatus* m_pLEDSBar22;
    CMyObjLEDStatus* m_pLEDSBar23;
    CMyObjLEDStatus* m_pLEDSBar24;
    CMyObjLEDStatus* m_pLEDSBar25;
    CMyObjLEDStatus* m_pLEDSBar26;
    CMyObjLEDStatus* m_pLEDSAlarm2;

    CMyObjLEDStatus* m_pLEDSTHD;
    CMyObjLEDStatus* m_pLEDSPER;
    CMyObjLEDStatus* m_pLEDSHz;
    CMyObjLEDStatus* m_pLEDSKVA;
    CMyObjLEDStatus* m_pLEDSMVA;
    CMyObjLEDStatus* m_pLEDSArrow3;
    CMyObjLEDStatus* m_pLEDSBar30;
    CMyObjLEDStatus* m_pLEDSBar31;
    CMyObjLEDStatus* m_pLEDSBar32;
    CMyObjLEDStatus* m_pLEDSBar33;
    CMyObjLEDStatus* m_pLEDSBar34;
    CMyObjLEDStatus* m_pLEDSBar35;
    CMyObjLEDStatus* m_pLEDSBar36;
    CMyObjLEDStatus* m_pLEDSAlarm3;

    CMyObjLEDStatus* m_pLEDSDegree;
    CMyObjLEDStatus* m_pLEDSKWh;
    CMyObjLEDStatus* m_pLEDSKVarh;

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
    void RefreshLED(void);

};

#endif /*_NPS7510_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/
