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

#ifndef _CMYAREEPROM_AT45DB0X_H
#define _CMYAREEPROM_AT45DB0X_H

struct AT45DB0X_METRICS
{
	WORD wIndexPage;
	WORD wIndexAddr;
	BYTE Address1;
	BYTE Address2;
	BYTE Address3;
};


//-----------------------------------------------------------------------------
class CMyArEEPROM_AT45DB0X:public CMyArEEPROM
{
public:
	BYTE GetStatus(void);
	BYTE IsBusy(void);
	void GetMetrics(DWORD dwAddr,AT45DB0X_METRICS* pMetrics);
	void SendCommand(BYTE Command,AT45DB0X_METRICS* pMetrics);
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

#endif/*_CMYAREEPROM_AT45DB0X_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/
