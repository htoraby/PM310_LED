#include <stdio.h>
#include <Main.h>

#define RTC_DATA_COUNTBYTE		1024

//-----------------------------------------------------------------------------
void CMyArRTC_iVEX::GetRTCFileName(char* pszRTCRAMFileName)
{
	GetCurrentDirectory(255,pszRTCRAMFileName);
	char* pszTemp = pszRTCRAMFileName;
	while(*pszTemp) pszTemp++;
	*pszTemp++ = '\\';
	*pszTemp++ = 'T';
	*pszTemp++ = 'E';
	*pszTemp++ = 'M';
	*pszTemp++ = 'P';
	*pszTemp++ = '\\';
	strcpy(pszTemp,m_szDeviceType);
	while(*pszTemp)
	{
		if(*pszTemp=='\\'||*pszTemp=='/') *pszTemp = '-';
		pszTemp++;
	}
	*pszTemp++ = '.';
	*pszTemp++ = 'r';
	*pszTemp++ = 'a';
	*pszTemp++ = 'm';
	*pszTemp = 0;
}

BOOL CMyArRTC_iVEX::IsError(void)
{
	return FALSE;
}

void CMyArRTC_iVEX::ReadTime(DEVICETIME* pDeviceTime)
{
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	pDeviceTime->wYear = systemTime.wYear-2000;
	pDeviceTime->wMonth = systemTime.wMonth;
	pDeviceTime->wDay = systemTime.wDay;
	pDeviceTime->wHour = systemTime.wHour;
	pDeviceTime->wMinute = systemTime.wMinute;
	pDeviceTime->wSecond = systemTime.wSecond;
	pDeviceTime->wMilliSecond = systemTime.wMilliseconds;
}

void CMyArRTC_iVEX::WriteTime(DEVICETIME* pDeviceTime)
{
}

void CMyArRTC_iVEX::iiiReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	if(dwAddr+wCountByte>RTC_DATA_COUNTBYTE) return;
	char szRTCFileName[256];
	GetRTCFileName(szRTCFileName);
	FILE* fp = fopen(szRTCFileName,"rb");
	if(fp==NULL) return;
	fseek(fp,dwAddr,SEEK_SET);
	fread(pData,sizeof(BYTE),wCountByte,fp);
	fclose(fp);
}

void CMyArRTC_iVEX::iiiReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	if(dwAddr+wCountWord*2>RTC_DATA_COUNTBYTE) return;
	char szRTCFileName[256];
	GetRTCFileName(szRTCFileName);
	FILE* fp = fopen(szRTCFileName,"rb");
	if(fp==NULL) return;
	fseek(fp,dwAddr,SEEK_SET);
	fread(pData,sizeof(WORD),wCountWord,fp);
	fclose(fp);
}

void CMyArRTC_iVEX::iiiWriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	if(dwAddr+wCountByte>RTC_DATA_COUNTBYTE) return;
	char szRTCFileName[256];
	GetRTCFileName(szRTCFileName);
	FILE* fp = fopen(szRTCFileName,"r+b");
	if(fp==NULL)
	{
		fp = fopen(szRTCFileName,"wb");
		if(fp==NULL) return;
		BYTE Temp = 0;
		for(WORD i=0;i<RTC_DATA_COUNTBYTE;i++) fwrite(&Temp,sizeof(BYTE),1,fp);
	}
	fseek(fp,dwAddr,SEEK_SET);
	fwrite(pData,sizeof(BYTE),wCountByte,fp);
	fclose(fp);
}

void CMyArRTC_iVEX::iiiWriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	if(dwAddr+wCountWord*2>RTC_DATA_COUNTBYTE) return;
	char szRTCFileName[256];
	GetRTCFileName(szRTCFileName);
	FILE* fp = fopen(szRTCFileName,"r+b");
	if(fp==NULL)
	{
		fp = fopen(szRTCFileName,"wb");
		if(fp==NULL) return;
		BYTE Temp = 0;
		for(WORD i=0;i<RTC_DATA_COUNTBYTE;i++) fwrite(&Temp,sizeof(BYTE),1,fp);
	}
	fseek(fp,dwAddr,SEEK_SET);
	fwrite(pData,sizeof(WORD),wCountWord,fp);
	fclose(fp);
}
