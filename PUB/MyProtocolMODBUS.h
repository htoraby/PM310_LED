#ifndef _MYPROTOCOLMODBUS_H
#define _MYPROTOCOLMODBUS_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
extern void Protocol_CopyByteToWord(WORD* pDest,BYTE* pSrc,WORD wCountWord);
extern void Protocol_CopyWordToByte(BYTE* pDest,WORD* pSrc,WORD wCountWord);
extern void Protocol_CopyDwordToByte(BYTE* pDest,DWORD* pSrc,WORD wCountWord);
extern void Protocol_CopyByteToByte(BYTE* pDest,BYTE* pSrc,WORD wCountWord);
extern void Protocol_OnTimer10msCRC(void);
extern void Protocol_OnTimer10ms(void);
extern void Protocol_OnRcvProcess(BYTE RcvData);
extern WORD Protocol_OnTaskProcess(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*_MYPROTOCOLMODBUS_H*/

