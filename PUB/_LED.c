//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#include "main.h"

/*******************************************************************/
BOOL g_bLEDOpened = TRUE;
BOOL g_bRefresh = FALSE;
WORD g_bFormatRealFillBlank = TRUE;
WORD g_wLEDAutoPosX = 0;
WORD g_wLEDAutoPosY = 0;

void LED_ByteOut(WORD wPosX, WORD wPosY, BYTE Data, WORD wFormat)
{
    char szTextBuffer[16];
    char* pszText = szTextBuffer;
    Data &= 0xff;
    if(wFormat>=3) *pszText++ = '0'+(char)(Data/100);
    if(wFormat>=2) *pszText++ = '0'+(char)(Data%100/10);
    *pszText++ = '0'+(char)(Data%10);
    *pszText = 0;
    LED_ASCIIOut(wPosX, wPosY, szTextBuffer);
}

void LED_WordOut(WORD wPosX, WORD wPosY, WORD wData, WORD wFormat)
{
    char szTextBuffer[16];
    wFormat = wFormat&0xf0;
    LED_FormatReal(szTextBuffer, wData, wFormat);
    LED_ASCIIOut(wPosX, wPosY, szTextBuffer);
}

char szTextBuffer[16];
void LED_RealOut(WORD wPosX, WORD wPosY, long lData, WORD wFormat)
{
//     char szTextBuffer[16];
    LED_FormatReal(szTextBuffer, lData, wFormat);
    LED_ASCIIOut(wPosX, wPosY, szTextBuffer);
}

void LED_FormatReal(char* pszText, long lData, WORD wFormat)
{
    char* pszTemp = pszText;
    WORD wCountAfterDot;
    WORD wSignFlag = 0;
    *pszTemp = 0;
    wFormat &= 0x00ff;
    wCountAfterDot = wFormat&0x000f;
    if(wCountAfterDot>8) return;
    if(lData<0)
    {
        wSignFlag = 1;
        lData = -lData;
    }

    switch(wFormat>>4)
    {
    case 9: if(lData>999999999) lData = 999999999; break;
    case 8: if(lData>99999999) lData = 99999999; break;
    case 7: if(lData>9999999) lData = 9999999; break;
    case 6: if(lData>999999) lData = 999999; break;
    case 5: if(lData>99999) lData = 99999; break;
    case 4: if(lData>9999) lData = 9999; break;
    case 3: if(lData>999) lData = 999; break;
    case 2: if(lData>99) lData = 99; break;
    case 1: if(lData>9) lData = 9; break;
    default: return;
    }
//     if(wSignFlag) *pszTemp++ = ' ';
    *pszTemp++ = ' ';
    switch(wFormat>>4)
    {
    case 9: *pszTemp++ = '0'+(char)(lData%1000000000L/100000000L);
         if(wCountAfterDot==8) *pszTemp++ = '.';
    case 8: *pszTemp++ = '0'+(char)(lData%100000000L/10000000L);
        if(wCountAfterDot==7) *pszTemp++ = '.';
    case 7: *pszTemp++ = '0'+(char)(lData%10000000L/1000000L);
        if(wCountAfterDot==6) *pszTemp++ = '.';
    case 6: *pszTemp++ = '0'+(char)(lData%1000000L/100000L);
         if(wCountAfterDot==5) *pszTemp++ = '.';
    case 5: *pszTemp++ = '0'+(char)(lData%100000L/10000L);
        if(wCountAfterDot==4) *pszTemp++ = '.';
    case 4: *pszTemp++ = '0'+(char)(lData%10000L/1000L);
        if(wCountAfterDot==3) *pszTemp++ = '.';
    case 3: *pszTemp++ = '0'+(char)(lData%1000L/100L);
        if(wCountAfterDot==2) *pszTemp++ = '.';
    case 2: *pszTemp++ = '0'+(char)(lData%100L/10L);
        if(wCountAfterDot==1) *pszTemp++ = '.';
    case 1: *pszTemp++ = '0'+(char)(lData%10L);
        break;
    default: return;
    }
    *pszTemp = 0;
    if(g_bFormatRealFillBlank)
    {
        pszTemp = pszText;
//        if(wSignFlag) pszTemp++;
        pszTemp++;
        wCountAfterDot = (wFormat>>4) - wCountAfterDot - 1;
        while(wCountAfterDot--)
        {
            if(*pszTemp=='0') *pszTemp = ' ';
            else break;
            pszTemp++;
        }
        if(wSignFlag==1) *(pszTemp-1) = '-';
    }
    g_bFormatRealFillBlank = TRUE;
}

void LED_BinOut(WORD wPosX,WORD wPosY,WORD wData,WORD wFormat)
{
    char szTextBuffer[16];
    wFormat = wFormat&0xF0;
    LED_FormatBin(szTextBuffer, wData, wFormat);
    LED_ASCIIOut(wPosX, wPosY, szTextBuffer);
}

void LED_FormatBin(char* pszText, DWORD dwData, WORD wFormat)
{
    char* pszTemp = pszText;
    *pszTemp = 0;
    switch(wFormat>>4)
    {
    case 8: *pszTemp++ = BinToStr((BYTE)(dwData>>28)&0x0f);
    case 7: *pszTemp++ = BinToStr((BYTE)(dwData>>24)&0x0f);
    case 6: *pszTemp++ = BinToStr((BYTE)(dwData>>20)&0x0f);
    case 5: *pszTemp++ = BinToStr((BYTE)(dwData>>16)&0x0f);
    case 4: *pszTemp++ = BinToStr((BYTE)(dwData>>12)&0x0f);
    case 3: *pszTemp++ = BinToStr((BYTE)(dwData>>8)&0x0f);
    case 2: *pszTemp++ = BinToStr((BYTE)(dwData>>4)&0x0f);
        *pszTemp++ = BinToStr((BYTE)dwData&0x0f);
        break;
    default: return;
    }
    *pszTemp = 0;
    if(g_bFormatRealFillBlank)
    {
        WORD wCount;
        pszTemp = pszText;
        wCount = (wFormat>>4) - 1;
        while(wCount--)
        {
            if(*pszTemp=='0') *pszTemp = ' ';
            else break;
            pszTemp++;
        }
    }
    g_bFormatRealFillBlank = TRUE;
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

