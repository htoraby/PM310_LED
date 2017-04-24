#ifndef FLASH_IVEX_H
#define FLASH_IVEX_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
extern char g_szFlashDeviceType[256];

// extern void EEPROM_GetEEPROMFileName(char* pszEEPROMFileName);
// extern BOOL EEPROM_IsError(void);
// extern BOOL EEPROM_ReadBlockHead(DWORD dwAddr,WORD* pCount);
// extern BOOL EEPROM_ReadBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord);
// extern void EEPROM_WriteBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord);
// extern void EEPROM_ReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
// extern void EEPROM_ReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
// extern void EEPROM_WriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
// extern void EEPROM_WriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);

extern void Flash_GetEEPROMFileName(char* pszEEPROMFileName);
extern BOOL Flash_IsError(void);
extern BOOL Flash_ReadBlockHead(DWORD dwAddr,WORD* pCount);
extern BOOL Flash_ReadBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord);
extern void Flash_WriteBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord);
extern void Flash_ReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
extern void Flash_ReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
extern void Flash_WriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
extern void Flash_WriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*FLASH_IVEX_H*/