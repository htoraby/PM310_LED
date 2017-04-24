#ifndef CMYAREEPROM_IVEX_H
#define CMYAREEPROM_IVEX_H

//-----------------------------------------------------------------------------
class CMyArEEPROM_iVEX
{
public:
	char m_szDeviceType[256];
protected:
	virtual void GetEEPROMFileName(char* pszEEPROMFileName);
public:
	BOOL IsError(void);
	BOOL ReadBlockHead(DWORD dwAddr,WORD* pCount);
	BOOL ReadBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord);
	void WriteBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord);
	VIRTUAL void iiiReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
	VIRTUAL void iiiReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
	VIRTUAL void iiiWriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
	VIRTUAL void iiiWriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
};

#endif/*CMYAREEPROM_IVEX_H*/