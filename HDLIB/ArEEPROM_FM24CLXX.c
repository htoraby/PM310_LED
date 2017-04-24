#include "Main.h"

#define EEPROM_DEV_ADDR			0x80a0				// RAM

#ifdef FM24CL04
#define EEPROM_DATA_COUNTBYTE	(512-2)				// 最前2个字节用于自检
#endif

#ifdef FM24CL64
#define EEPROM_DATA_COUNTBYTE	(16384-2)			// 最前2个字节用于自检
#endif

#ifdef FM24V01
#define EEPROM_DATA_COUNTBYTE	(16384-2)			// 最前2个字节用于自检
#endif

typedef struct
{
	WORD wAddSum;
	WORD wCount1;					// 配置版本
	WORD wCount2;
}BLOCKINFO;

///----------------------------------------------------------------------------
BOOL EEPROM_IsError(void)
{
	BYTE Temp[2];
// 	if(g_i2c.GetStatus(EEPROM_DEV_ADDR)==0) return FALSE;

	Temp[0] = 0xeb;
	Temp[1] = 0x90;
	I2C1WriteDataByte(EEPROM_DEV_ADDR,0x00,Temp,2);

	Temp[0] = 0x00;
	Temp[1] = 0x00;
	I2C1ReadDataByte(EEPROM_DEV_ADDR,0x00,Temp,2);
	if(Temp[0]!=0xeb && Temp[1]!=0x90)
		return TRUE;

	return FALSE;
}

//********************************************************************

void EEPROM_ReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	if(dwAddr+wCountByte>EEPROM_DATA_COUNTBYTE) return;

	I2C1ReadDataByte(EEPROM_DEV_ADDR,(WORD)(dwAddr+2),pData,wCountByte);
}

void EEPROM_ReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	if(dwAddr+wCountWord*2>EEPROM_DATA_COUNTBYTE) return;
	I2C1ReadDataWord(EEPROM_DEV_ADDR,(WORD)(dwAddr+2),pData,wCountWord);
}

void EEPROM_WriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	if(dwAddr+wCountByte>EEPROM_DATA_COUNTBYTE) return;
	I2C1WriteDataByte(EEPROM_DEV_ADDR,(WORD)(dwAddr+2),pData,wCountByte);
}

void EEPROM_WriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	if(dwAddr+wCountWord*2>EEPROM_DATA_COUNTBYTE) return;
	I2C1WriteDataWord(EEPROM_DEV_ADDR,(WORD)(dwAddr+2),pData,wCountWord);
}


//-----------------------------------------------------------------------------
BOOL EEPROM_ReadBlockHead(DWORD dwAddr,WORD* pCount)
{
	WORD wDeviceType;
	BLOCKINFO blockinfo;
	EEPROM_ReadDataWord(dwAddr,&wDeviceType,1);
	if(wDeviceType==(WORD)DEVICETYPE_CODE)
	{
		EEPROM_ReadDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
		if(blockinfo.wCount1==blockinfo.wCount2)
		{
			if(pCount!=NULL) *pCount = blockinfo.wCount1;
			return TRUE;
		}
	}
	*pCount = 0;				// 读取失败
	return FALSE;
}

BOOL EEPROM_ReadBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord)
{
	WORD wDeviceType;
	BLOCKINFO blockinfo;
	EEPROM_ReadDataWord(dwAddr,&wDeviceType,1);
	if(wDeviceType==(WORD)DEVICETYPE_CODE)
	{
		EEPROM_ReadDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
		EEPROM_ReadDataWord(dwAddr+2+SIZEOFBYTE(blockinfo),pData,wCountWord);
		if(blockinfo.wAddSum==CalculateCRCWord(pData,wCountWord)&&blockinfo.wCount1==blockinfo.wCount2)
		{
			if(pCount!=NULL) *pCount = blockinfo.wCount1;
			return TRUE;
		}
	}
	return FALSE;
}

void EEPROM_WriteBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord)
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
		blockinfo.wCount1 = 0;
		blockinfo.wCount2 = 0;
	}
	wDeviceType = (WORD)DEVICETYPE_CODE;
	EEPROM_WriteDataWord(dwAddr,&wDeviceType,1);
	EEPROM_WriteDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
	EEPROM_WriteDataWord(dwAddr+2+SIZEOFBYTE(blockinfo),pData,wCountWord);
}


