#ifndef __LCD_H
#define __LCD_H

#define LCD_SCANALLBYTES			(LCD_CXDOT/8*LCD_CYDOT)

#ifndef LCD_MULTICOLOR
#define LCD_WBUFFERSIZE				(LCD_SCANALLBYTES/2)
#else
#define LCD_WBUFFERSIZE				(LCD_SCANALLBYTES*4)
#endif

#define COLOR_BLACK					0x00
#define COLOR_RED					0x01
#define COLOR_GREEN					0x02
#define COLOR_YELLOW				0x03
#define COLOR_BLUE					0x04
#define COLOR_MAGENTA				0x05
#define COLOR_CYAN					0x06
#define COLOR_DARKGRAY				0x07
#define COLOR_LIGHTGRAY				0x08
#define COLOR_LIGHTRED				0x09
#define COLOR_LIGHTGREEN			0x0a
#define COLOR_LIGHTYELLOW			0x0b
#define COLOR_LIGHTBLUE				0x0c
#define COLOR_LIGHTMAGENTA			0x0d
#define COLOR_LIGHTCYAN				0x0e
#define COLOR_WHITE					0x0f

#define TAMODE_LEFT					0x00		//左边对齐;
#define TAMODE_CENTER				0x01		//中心对齐;
#define TAMODE_RIGHT				0x02		//右边对齐;

#ifdef _WIN32
#define LCD_Setup()
#endif/*_WIN32*/

// #ifdef _WIN32
// #define LCD_Clear()
// #endif/*LCD_Clear*/

// #ifndef LCD_Open
// #define LCD_Open
// #endif/*LCD_Open*/

#ifdef _WIN32
#define LCD_Flush()
#endif/*LCD_Flush*/

// #ifndef LCD_Close
// #define LCD_Close
// #endif/*LCD_Close*/

// #ifndef LCD_SetData
// #define LCD_SetData(wAddress,Data,Mask)
// #endif/*SetData*/

#ifndef LCD_OnInit
#define LCD_OnInit	LCD_OnInitA
#endif/*LCD_OnInit*/

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
extern WORD g_wLCDColor;
extern WORD g_wLCDColorBK;
extern BOOL g_bLCDSetDataXor;
extern BOOL g_bLCDLargeFont;
extern BOOL g_bLCDFormatRealFillBlank;
extern WORD g_wLCDTextAlignMode;
extern BOOL g_bLCDCursorON;
extern WORD g_wLCDCursorPosX;
extern WORD g_wLCDCursorPosY;
extern WORD g_wLCDCursorWidth;
extern WORD g_wLCDCursorHeight;
extern WORD g_wLCDAutoPosX;
extern WORD g_wLCDAutoPosY;
extern WORD g_wLCDAutoEnter;


extern void LCD_DrawCursor(void);
extern BYTE LCD_ReverseLineStyle(BYTE LineStyle);
extern void LCD_OnInitA(void);
extern void LCD_ClearBlock(WORD wPosX1,WORD wPosY1,WORD wPosX2,WORD wPosY2);
// extern void LCD_Open(void);
// extern void LCD_Close(void);
// extern void LCD_Setup(void);
// extern void LCD_Flush(void);
// extern void LCD_Clear(void);
extern void LCD_SetColor(WORD wColor);
extern void LCD_SetColorBK(WORD wColorBK);
extern void LCD_CursorON(void);
extern void LCD_CursorOFF(void);
extern void LCD_EraseCursor(void);
extern void LCD_SetCursorPosX(WORD wCursorPosX,WORD wCursorWidth);
extern void LCD_SetCursorPosY(WORD wCursorPosY,WORD wCursorHeight);
extern void LCD_SetTextAlignMode(WORD wTextAlignMode);
extern void LCD_SetSmallFont(void);
extern void LCD_SetLargeFont(void);
extern WORD LCD_GetFontWidth(void);
extern WORD LCD_GetFontHeight(void);
extern WORD LCD_GetStringWidth(char* pszText);
extern void LCD_DrawPoint(WORD wPosX,WORD wPosY);
extern void LCD_DrawHLineExt(WORD wPosY,WORD wPosX1,WORD wPosX2,BYTE LineStyle);
extern void LCD_DrawVLineExt(WORD wPosX,WORD wPosY1,WORD wPosY2,BYTE LineStyle);
extern void LCD_DrawHLine(WORD wPosY,WORD wPosX1,WORD wPosX2);
extern void LCD_DrawVLine(WORD wPosX,WORD wPosY1,WORD wPosY2);
extern void LCD_DrawXLine(short nPosX1,short nPosY1,short nPosX2,short nPosY2);
extern void LCD_DrawRect(WORD wPosX1,WORD wPosY1,WORD wPosX2,WORD wPosY2);
extern void LCD_DrawBlock(WORD wPosX1,WORD wPosY1,WORD wPosX2,WORD wPosY2);
extern void LCD_DrawCircle(WORD wPosX0,WORD wPosY0,WORD wR);
extern void LCD_ImageOut(WORD wPosX,WORD wPosY,WORD wCX,WORD wCY,WORD* pData);
extern void LCD_TextOut(WORD wPosX,WORD wPosY,char* pszText);
extern void LCD_TextOutW(WORD wPosX,WORD wPosY,WORD* pwszText);
extern void LCD_AsciiOut(WORD wPosX,WORD wPosY,char* pszText);
extern void LCD_AsciiOutW(WORD wPosX,WORD wPosY,WORD* pwszText);
extern void LCD_TimeOut(WORD wPosX,WORD wPosY,WORD wHour,WORD wMinute,WORD wSecond,WORD wMilliSecond);
extern void LCD_DateOut(WORD wPosX,WORD wPosY,WORD wYear,WORD wMonth,WORD wDay);
extern void LCD_ByteOut(WORD wPosX,WORD wPosY,BYTE Data,WORD wFormat);
extern void LCD_WordOut(WORD wPosX,WORD wPosY,WORD wData);
extern void LCD_RealOut(WORD wPosX,WORD wPosY,DWORD fData,WORD wFormat);
extern void LCD_FormatReal(char* pszText,DWORD fData,WORD wFormat);
extern void LCD_AutoTextOut(char* pszText);
extern void LCD_AutoTextOutW(WORD* pwszText);
extern void LCD_AutoAsciiOut(char* pszText);
extern void LCD_AutoAsciiOutW(WORD* pwszText);
extern void LCD_AutoByteOut(BYTE Data,WORD wFormat);
extern void LCD_AutoWordOut(WORD wData);
extern void LCD_AutoRealOut(DWORD fData,WORD wFormat);
extern void LCD_AutoOutERR_OK(BOOL bERR);
extern void LCD_AutoOutALM_OK(BOOL bALM);
extern void LCD_AutoOutYES_NO(BOOL bYES);
extern void LCD_AutoOutOFF_ON(BOOL bOFF);
extern void LCD_AutoOut__1__0(BOOL b__1);
// protected:
// 	VIRTUAL void iiiOpen(void){};
// 	VIRTUAL void iiiClose(void){};
// 	VIRTUAL void iiiSetup(void){};
// 	VIRTUAL void iiiFlush(void){};
// 	VIRTUAL void iiiClear(void){};
// 	VIRTUAL void iiiSetData(WORD wAddress,BYTE Data,BYTE Mask){};

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__LCD_H*/

