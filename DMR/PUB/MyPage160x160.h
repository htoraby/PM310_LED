#ifndef CMYPAGE160x160_H
#define CMYPAGE160x160_H

//-----------------------------------------------------------------------------
extern void Page_DrawHead(char* pszHead);
extern void Page_DrawScroll(WORD wPosX,WORD wPages,WORD wCurSel);
extern void Page_DrawTable(WORD wPosX,WORD wPosY,WORD wCX,WORD wCY,WORD wNum,char* pszLabel);
extern void Page_DrawRTWaveGrid(void);
extern void Page_DrawRTWave(WORD wIndex,MyData* data,WORD wScale,WORD wDataIndex,WORD wColor);
extern void Page_DrawVectorGrid(MyData* dataUa);
extern void Page_DrawVectorHead(WORD nPosX,WORD nPosY,WORD wHeadSharp);
extern void Page_DrawVector(MyData* data,WORD wColor,WORD wRadian,WORD wScale,WORD wHeadSharp);
extern void Page_DrawVectorData(WORD wIndex,char* pszName,WORD wDataIndex,WORD wColor);
extern void Page_OnRefreshPageEvent(WORD wRefreshMode);
extern void Page_OnRefreshPageLCDContrast(WORD wRefreshMode);
extern void Page_OnRPSetupDeviceTime(void);

#endif/*CMYPAGE160x160_H*/



