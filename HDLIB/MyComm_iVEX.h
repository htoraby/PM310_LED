#ifndef CMYCOMM_IVEX_H
#define CMYCOMM_IVEX_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// extern void COMM_SetComm(CMyComm** ppComm);
extern void COMM_SetComm(void** ppComm);
extern void COMM_OnInit(void);
extern void COMM_OnPolling(void);
extern void COMM_OnTimer10ms(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*CMYCOMM_IVEX_H*/





