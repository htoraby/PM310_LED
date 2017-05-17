//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef _LED_H
#define _LED_H

#ifdef __cplusplus
extern "C" {
#endif

extern BOOL g_bLEDOpened;
extern BOOL g_bRefresh;
extern WORD g_bFormatRealFillBlank;
extern WORD g_wLEDAutoPosX;
extern WORD g_wLEDAutoPosY;

extern const WORD c_wLEDX;
extern const WORD c_wLEDY;

extern void LED_OnInit(void);
extern void LED_Open(void);
extern void LED_Close(void);
extern void LED_Setup(void);
extern void LED_Flush(void);
extern void LED_Clear(void);

extern void LED_ASCIIOut(WORD wPosX, WORD wPosY, char* pszText);
extern void LED_SetCode(WORD wIndex, char ch);
extern void LED_SetLight(WORD wIndex, BOOL bLight);
extern BOOL LED_GetLight(WORD wIndex);

extern void LED_ByteOut(WORD wPosX, WORD wPosY, BYTE Data, WORD wFormat);
extern void LED_WordOut(WORD wPosX, WORD wPosY, WORD wData, WORD wFormat);
extern void LED_RealOut(WORD wPosX, WORD wPosY, long lData, WORD wFormat);
extern void LED_FormatReal(char* pszText, long lData, WORD wFormat);

extern void LED_BinOut(WORD wPosX, WORD wPosY, WORD wData, WORD wFormat);
extern void LED_FormatBin(char* pszText, DWORD dwData, WORD wFormat);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // _LED_H

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

