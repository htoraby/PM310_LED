#ifndef __LCDMEM_H
#define __LCDMEM_H

// #undef LCD_Open
// #define LCD_Open	LCD_OpenMem

// #undef LCD_Close
// #define LCD_Close	LCD_CloseMem

// #undef LCD_Clear
// #define LCD_Clear	LCD_ClearMem

// #undef LCD_SetData
// #define LCD_SetData	LCD_SetDataMem

#undef LCD_OnInit
#define LCD_OnInit LCD_OnInitMem

//-----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

extern BOOL g_bLCDOpened;
extern BOOL g_bLCDRefresh;
extern DWORD g_wLCDRefreshAddrMin;
extern DWORD g_wLCDRefreshAddrMax;

extern void LCD_OnInitMem(void);
extern WORD* LCD_GetLCDBuffer(void);
extern void LCD_Open(void);
extern void LCD_Close(void);
extern void LCD_Clear(void);
extern void LCD_SetData(WORD wAddress,BYTE Data,BYTE Mask);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__LCDMEM_H*/
