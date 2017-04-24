#ifndef __STM32_SCI_H
#define __STM32_SCI_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// extern void COMM_SetComm(CMyComm** ppComm);
// extern void COMM_SetComm(void** ppComm);
extern void COMM_HardWareInit(void);
extern void COMM_OnInit(void);
extern void COMM_OnPolling(void);
extern void COMM_OnTimer10ms(void);
    
extern BOOL g_bComInit;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __STM32_SCI_H
