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

#include "Main.h"

#include <Main.h>

static tCRC32INFO s_CRCInfo = 
{
    0xFF01FF02,
    0xFF03FF04,
    0xFFFFFFFF,
//     0xFFFFFFFF,
    0x12345678,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
};

const tCRC32INFO* g_pCRCInfo = &s_CRCInfo;

//-----------------------------------------------------------------------------
void MyHDIF_OnInit1Sub(void)
{
    g_wHDIFPanelDiagCode = 0x54;
}

WORD MyHDIF_GetFreqINT1(void)
{
    if(g_dataUa.m_nData>60||g_dataUc.m_nData>60)
        return g_wHDIFFreqINT1;
    else return 0;
}


/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/
