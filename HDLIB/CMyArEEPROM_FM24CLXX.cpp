#include <Main.h>

// #define EEPROM_DEV_ADDR			0x80a0				// RAM
#define EEPROM_DEV_ADDR			0x0050			// 0x00a0>>1			// RAM
#define EEPROM_BAUDRATE			100				// 400k


#ifdef FM24CL04
#define EEPROM_DATA_COUNTBYTE	(512-2)				// 最前2个字节用于自检
#endif

#ifdef FM24CL64
#define EEPROM_DATA_COUNTBYTE	(8192-2)			// 最前2个字节用于自检
#endif

#ifdef FM24V01
#define EEPROM_DATA_COUNTBYTE	(16384-2)			// 最前2个字节用于自检
#endif

///----------------------------------------------------------------------------
BOOL CMyArEEPROM_FM24CL04::IsError(void)
{
	BYTE Temp[2];
// 	if(g_i2c.GetStatus(EEPROM_DEV_ADDR)==0) return FALSE;

	Temp[0] = 0xeb;
	Temp[1] = 0x90;
	g_i2c.pRegs = &I2caRegs;
	g_i2c.wBaudrate = EEPROM_BAUDRATE;
	g_i2c.wAddrDev = EEPROM_DEV_ADDR;
	g_i2c.bAddrDevExt = FALSE;
	g_i2c.bAddrDataExt = TRUE;
	I2CResetHW(&g_i2c);
	I2CWriteDataByte(&g_i2c,0x00,Temp,2);

	Temp[0] = 0x00;
	Temp[1] = 0x00;
	I2CResetHW(&g_i2c);
	I2CReadDataByte(&g_i2c,0x00,Temp,2);
	if(Temp[0]!=0xeb && Temp[1]!=0x90)
		return TRUE;

	return FALSE;
}

void CMyArEEPROM_FM24CL04::iiiReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	if(dwAddr+wCountByte>EEPROM_DATA_COUNTBYTE) return;
	g_i2c.pRegs = &I2caRegs;
	g_i2c.wBaudrate = EEPROM_BAUDRATE;
	g_i2c.wAddrDev = EEPROM_DEV_ADDR;
	g_i2c.bAddrDevExt = FALSE;
	g_i2c.bAddrDataExt = TRUE;
	I2CResetHW(&g_i2c);
	I2CReadDataByte(&g_i2c,(WORD)(dwAddr+2),pData,wCountByte);
}

void CMyArEEPROM_FM24CL04::iiiReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	if(dwAddr+wCountWord*2>EEPROM_DATA_COUNTBYTE) return;
	g_i2c.pRegs = &I2caRegs;
	g_i2c.wBaudrate = EEPROM_BAUDRATE;
	g_i2c.wAddrDev = EEPROM_DEV_ADDR;
	g_i2c.bAddrDevExt = FALSE;
	g_i2c.bAddrDataExt = TRUE;
	I2CResetHW(&g_i2c);
	I2CReadDataWord(&g_i2c,(WORD)(dwAddr+2),pData,wCountWord);
}

void CMyArEEPROM_FM24CL04::iiiWriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	if(dwAddr+wCountByte>EEPROM_DATA_COUNTBYTE) return;
	g_i2c.pRegs = &I2caRegs;
	g_i2c.wBaudrate = EEPROM_BAUDRATE;
	g_i2c.wAddrDev = EEPROM_DEV_ADDR;
	g_i2c.bAddrDevExt = FALSE;
	g_i2c.bAddrDataExt = TRUE;
	I2CResetHW(&g_i2c);
	I2CWriteDataByte(&g_i2c,(WORD)(dwAddr+2),pData,wCountByte);
}

void CMyArEEPROM_FM24CL04::iiiWriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	if(dwAddr+wCountWord*2>EEPROM_DATA_COUNTBYTE) return;
	g_i2c.pRegs = &I2caRegs;
	g_i2c.wBaudrate = EEPROM_BAUDRATE;
	g_i2c.wAddrDev = EEPROM_DEV_ADDR;
	g_i2c.bAddrDevExt = FALSE;
	g_i2c.bAddrDataExt = TRUE;
	I2CResetHW(&g_i2c);
	I2CWriteDataWord(&g_i2c,(WORD)(dwAddr+2),pData,wCountWord);
}

//-----------------------------------------------------------------------------
BOOL CMyArEEPROM_FM24CL04::ReadBlockHead(DWORD dwAddr,WORD* pCount)
{
	WORD wDeviceType;
	BLOCKINFO blockinfo;
	iiiReadDataWord(dwAddr,&wDeviceType,1);
	if(wDeviceType==DEVICETYPE_CODE)
	{
		iiiReadDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
		if(blockinfo.wCount1==blockinfo.wCount2)
		{
			if(pCount!=NULL) *pCount = blockinfo.wCount1;
			return TRUE;
		}
	}
	*pCount = 0;				// 读取失败
	return FALSE;
}

BOOL CMyArEEPROM_FM24CL04::ReadBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord)
{
	WORD wDeviceType;
	BLOCKINFO blockinfo;
	iiiReadDataWord(dwAddr,&wDeviceType,1);
	if(wDeviceType==DEVICETYPE_CODE)
	{
		iiiReadDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
		iiiReadDataWord(dwAddr+2+SIZEOFBYTE(blockinfo),pData,wCountWord);
		if(blockinfo.wAddSum==CalculateCRCWord(pData,wCountWord)&&blockinfo.wCount1==blockinfo.wCount2)
		{
			if(pCount!=NULL) *pCount = blockinfo.wCount1;
			return TRUE;
		}
	}
	return FALSE;
}

void CMyArEEPROM_FM24CL04::WriteBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord)
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
	wDeviceType = DEVICETYPE_CODE;
	iiiWriteDataWord(dwAddr,&wDeviceType,1);
	iiiWriteDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
	iiiWriteDataWord(dwAddr+2+SIZEOFBYTE(blockinfo),pData,wCountWord);
}


