#ifndef CMyHDIFDMR_H
#define CMyHDIFDMR_H

#include "HDLIB\ArEEPROM_iVEX.h"
#include "HDLIB\Flash_iVEX.h"
#include "HDLIB\ArRTC_iVEX.h"
#include "HDLIB\MyComm_iVEX.h"

//-----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

extern void MyHDIF_OnInit1(void);
extern void MyHDIF_OnInit2(void);
extern void MyHDIF_OnPollingComm(void);
extern void MyHDIF_OnPollingCommET(void);
extern void MyHDIF_OnTimer1ms(void);
extern void MyHDIF_OnTimer10ms(void);
extern void MyHDIF_OnTimer1000ms(void);
extern WORD MyHDIF_GetPanelDiagCode(void);
extern void MyHDIF_OnWhileLoop(void);

// extern CMyComm_iVEX g_comm1;
// extern CMyComm_iVEX g_comm2;
extern WORD g_wHDIFFreqINT1;
extern WORD g_wHDIFFreqINT2;
extern WORD g_wHDIFPanelDiagCode;
extern WORD g_wHDIFPWRUPS;
extern WORD g_wCommLight;
extern DWORD g_dwFsam;
extern DWORD g_dwSysTimerUs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*CMyHDIFDMR_H*/