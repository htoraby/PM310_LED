#include <stdio.h>
#include <string.h>
#include <Main.h>


//-----------------------------------------------------------------------------
void CMyArEEPROM_iVEXMain::GetEEPROMFileName(char* pszEEPROMFileName)
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
	strcpy(pszTemp,m_szDeviceType);
	while(*pszTemp)
	{
		if(*pszTemp=='\\'||*pszTemp=='/') *pszTemp = '-';
		pszTemp++;
	}
	*pszTemp++ = '.';
	*pszTemp++ = 'r';
	*pszTemp++ = 'o';
	*pszTemp++ = 'm';
	*pszTemp++ = '1';
	*pszTemp = 0;
}

