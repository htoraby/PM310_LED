#ifdef __cplusplus
extern "C" {
#endif

#ifndef LEDTESTTIME
#define LEDTESTTIME			2			// 2s
#endif/*LEDTESTTIME*/

extern unsigned short g_wCodeLED[16];
extern unsigned short g_wMaskLED[16];

extern unsigned short g_wLEDTestFlag;
extern BOOL g_bLEDtestOK;

extern unsigned short g_bFormatRealFillBlank;
extern void OnInitLED(void);
extern void OnTimer1000msLED(void);
//extern void OnRefreshLED(void);
extern void LEDClearBarStatus(void);
extern void LEDClear(void);
extern void LEDResetMask(void);
extern void LEDSetMask(unsigned short wPosX,unsigned short wPosY,unsigned short wLength);
extern void LEDAsciiOut(unsigned short wPosX,unsigned short wPosY,char* pszText);
extern void LEDByteOut(unsigned short wPosX,unsigned short wPosY,unsigned short wData,unsigned short wFormat);
extern void LEDWordOut(unsigned short wPosX,unsigned short wPosY,unsigned short wData);
extern void LEDRealOut(unsigned short wPosX,unsigned short wPosY,unsigned long fData,unsigned short wFormat);
extern void FormatReal(char* pszText,unsigned long dwData,unsigned short wFormat);
extern void SetLevelLight(unsigned short wLightCode,unsigned short wStatus);
extern void ResetLevelLight(unsigned short wLightCode,unsigned short wStatus);
extern void TestLED(void);


#ifdef __cplusplus
}
#endif /* extern "C" */
