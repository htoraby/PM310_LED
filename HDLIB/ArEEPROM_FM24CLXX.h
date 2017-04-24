/*
;*****************************************************************************************************
;*						Copyright (c) 2009 by ThinkBoy. 
;*						All rights reserved.
;*
;* Header:
;* File Name: 
;* Author: jimmy
;* Date:
;*****************************************************************************************************
;*/

#ifndef _CMYAREEPROM_FM24CL04_H
#define _CMYAREEPROM_FM24CL04_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//extern char g_szEEPROMDeviceType[256];

extern void OnI2CInit(void);
extern void ReadByteFromI2C(unsigned short wDevAddr,unsigned short wDataAddr,unsigned char* pData,unsigned short wCountByte);
extern void WriteByteToI2C(unsigned short wDevAddr,unsigned short wDataAddr,unsigned char* pData,unsigned short wCountByte);
extern void ReadWordFromI2C(unsigned short wDevAddr,unsigned short wDataAddr,unsigned short* pData,unsigned short wCounWord);
extern void WriteWordToI2C(unsigned short wDevAddr,unsigned short wDataAddr,unsigned short* pData,unsigned short wCountWord);

extern void EEPROM_GetEEPROMFileName(char* pszEEPROMFileName);
extern BOOL EEPROM_IsError(void);
extern BOOL EEPROM_ReadBlockHead(DWORD dwAddr,WORD* pCount);
extern BOOL EEPROM_ReadBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord);
extern void EEPROM_WriteBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord);
extern void EEPROM_ReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
extern void EEPROM_ReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
extern void EEPROM_WriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
extern void EEPROM_WriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);

extern void RTC_WriteDataByte(WORD wDevAddr,DWORD dwAddr,BYTE* pData,WORD wCountByte);
extern void RTC_ReadDataByte(WORD wDevAddr,DWORD dwAddr,BYTE* pData,WORD wCountByte);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*_CMYAREEPROM_FM24CL04_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/

