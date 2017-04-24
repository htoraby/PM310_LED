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

//-----------------------------------------------------------------------------
class CMyArEEPROM_FM24CL04:public CMyArEEPROM
{
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

#endif/*_CMYAREEPROM_FM24CL04_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/

