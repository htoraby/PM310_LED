#include <stdio.h>
#include <string.h>
#include <Main.h>
#include "StdAfx.h"

char g_szFlashDeviceType[256];

typedef struct _BLOCKINFO
{
	WORD wAddSum;
	WORD wCount1;					// ≈‰÷√∞Ê±æ
	WORD wCount2;
}BLOCKINFO;

//-----------------------------------------------------------------------------
void Flash_GetEEPROMFileName(char* pszEEPROMFileName)
{
	GetCurrentDirectory(255,pszEEPROMFileName);
	char* pszTemp = pszEEPROMFileName;
	while(*pszTemp) pszTemp++;
	*pszTemp++ = '\\';
	*pszTemp++ = 'T';
	*pszTemp++ = 'E';
	*pszTemp++ = 'M';
	*pszTemp++ = 'P';
	*pszTemp++ = '\\';
	strcpy(pszTemp,g_szFlashDeviceType);
	while(*pszTemp)
	{
		if(*pszTemp=='\\'||*pszTemp=='/') *pszTemp = '-';
		pszTemp++;
	}
	*pszTemp++ = '.';
	*pszTemp++ = 'F';
	*pszTemp++ = 'L';
	*pszTemp++ = 'S';
	*pszTemp = 0;
}

BOOL Flash_IsError(void)
{
	return FALSE;
}

void Flash_ReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	char szEEPROMFileName[256];
	Flash_GetEEPROMFileName(szEEPROMFileName);
	FILE* fp = fopen(szEEPROMFileName,"rb");
	if(fp==NULL) return;
	fseek(fp,dwAddr,SEEK_SET);
	fread(pData,sizeof(BYTE),wCountByte,fp);
	fclose(fp);
}

void Flash_ReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	char szEEPROMFileName[256];
	Flash_GetEEPROMFileName(szEEPROMFileName);
	FILE* fp = fopen(szEEPROMFileName,"rb");
	if(fp==NULL) return;
	fseek(fp,dwAddr,SEEK_SET);
	fread(pData,sizeof(WORD),wCountWord,fp);
	fclose(fp);
}

void Flash_WriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	char szEEPROMFileName[256];
	Flash_GetEEPROMFileName(szEEPROMFileName);
	FILE* fp = fopen(szEEPROMFileName,"r+b");
	if(fp==NULL)
	{
		fp = fopen(szEEPROMFileName,"wb");
		if(fp==NULL) return;
	}
	fseek(fp,0,SEEK_END);
	fpos_t pos;
	fgetpos(fp,&pos);
	if((DWORD)pos<dwAddr)
	{
		BYTE Temp = 0;
		for(DWORD i=0;i<dwAddr-(DWORD)pos;i++) fwrite(&Temp,sizeof(BYTE),1,fp);
	}
	fseek(fp,dwAddr,SEEK_SET);
	fwrite(pData,sizeof(BYTE),wCountByte,fp);
	fclose(fp);
}

void Flash_WriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	char szEEPROMFileName[256];
	Flash_GetEEPROMFileName(szEEPROMFileName);
	FILE* fp = fopen(szEEPROMFileName,"r+b");
	if(fp==NULL)
	{
		fp = fopen(szEEPROMFileName,"wb");
		if(fp==NULL) return;
	}
	fseek(fp,0,SEEK_END);
	fpos_t pos;
	fgetpos(fp,&pos);
	if((DWORD)pos<dwAddr)
	{
		BYTE Temp = 0;
		for(DWORD i=0;i<dwAddr-(DWORD)pos;i++) fwrite(&Temp,sizeof(BYTE),1,fp);
	}
	fseek(fp,dwAddr,SEEK_SET);
	fwrite(pData,sizeof(WORD),wCountWord,fp);
	fclose(fp);
}

//-----------------------------------------------------------------------------
BOOL Flash_ReadBlockHead(DWORD dwAddr,WORD* pCount)
{
	WORD wDeviceType;
	BLOCKINFO blockinfo;
	Flash_ReadDataWord(dwAddr,&wDeviceType,1);
	if(wDeviceType==DEVICETYPE_CODE)
	{
		Flash_ReadDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
		if(blockinfo.wCount1==blockinfo.wCount2)
		{
			if(pCount!=NULL) *pCount = blockinfo.wCount1;
			return TRUE;
		}
	}
	*pCount = 0;				// ∂¡»° ß∞‹
	return FALSE;
}

BOOL Flash_ReadBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord)
{
	WORD wDeviceType;
	BLOCKINFO blockinfo;
	Flash_ReadDataWord(dwAddr,&wDeviceType,1);
	if(wDeviceType==DEVICETYPE_CODE)
	{
		Flash_ReadDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
		Flash_ReadDataWord(dwAddr+2+SIZEOFBYTE(blockinfo),pData,wCountWord);
		if(blockinfo.wAddSum==CalculateCRCWord(pData,wCountWord)&&blockinfo.wCount1==blockinfo.wCount2)
		{
			if(pCount!=NULL) *pCount = blockinfo.wCount1;
			return TRUE;
		}
	}
	return FALSE;
}

void Flash_WriteBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord)
{
	WORD wDeviceType;
	BLOCKINFO blockinfo;
	blockinfo.wAddSum = CalculateCRCWord(pData,wCountWord);
	if(pCount!=NULL)
	{
		blockinfo.wCount1 = *pCount;
		blockinfo.wCount2 = *pCount;
	}
	else
	{
		blockinfo.wCount1 = 0x5555;
		blockinfo.wCount2 = 0x5555;
	}
	wDeviceType = DEVICETYPE_CODE;
	Flash_WriteDataWord(dwAddr,&wDeviceType,1);
	Flash_WriteDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
	Flash_WriteDataWord(dwAddr+2+SIZEOFBYTE(blockinfo),pData,wCountWord);
}
