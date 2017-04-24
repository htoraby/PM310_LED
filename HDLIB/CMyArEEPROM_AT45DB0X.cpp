#include <Main.h>

#ifdef AT45DB041B
#define AT45DB0X_STATUSMASK		0x38
#define AT45DB0X_STATUSOK		0x18
#define AT45DB0X_PAGEMAX		2048
#define AT45DB0X_PAGESIZE		264
#define AT45DB0X_PAGEADDRNUM	9
#endif
#ifdef AT45DB081B
#define AT45DB0X_STATUSMASK		0x38
#define AT45DB0X_STATUSOK		0x20
#define AT45DB0X_PAGEMAX		4096
#define AT45DB0X_PAGESIZE		264
#define AT45DB0X_PAGEADDRNUM	9
#endif
#ifdef AT45DB161D
#define AT45DB0X_STATUSMASK		0x3f
#define AT45DB0X_STATUSOK		0x2c
#define AT45DB0X_PAGEMAX		4096
#define AT45DB0X_PAGESIZE		528
#define AT45DB0X_PAGEADDRNUM	10
#endif


//-----------------------------------------------------------------------------
BYTE CMyArEEPROM_AT45DB0X::GetStatus(void)
{
	g_spi.pRegs = &SpiaRegs;
	g_spi.wBaudrate = AT45DB0X_SPIBRR;
	g_spi.wCharMode = AT45DB0X_CHARMODE;
	g_spi.wClockMode = AT45DB0X_SPIMODE;
	g_spi.wDelayFIFO = 0;

	SPIResetHW(&g_spi);
	BYTE DataSnd[2],DataRcv[2];
	DataSnd[0] = 0xd7;
	DataSnd[1] = 0;
	DataRcv[0] = 0;
	DataRcv[1] = 0;
	AT45DB0X_ENABLE;
	SPISndRcvByteSyn(&g_spi,DataSnd,DataRcv,2);
	AT45DB0X_DISABLE;
	return DataRcv[1];
}

BYTE CMyArEEPROM_AT45DB0X::IsBusy(void)
{
	BYTE Status = GetStatus();
	return (Status&0x80)?0:1;
}

void CMyArEEPROM_AT45DB0X::GetMetrics(DWORD dwAddr,AT45DB0X_METRICS* pMetrics)
{
	pMetrics->wIndexPage = (WORD)(dwAddr/AT45DB0X_PAGESIZE);
	pMetrics->wIndexAddr = (WORD)(dwAddr%AT45DB0X_PAGESIZE);
	dwAddr = ((DWORD)pMetrics->wIndexPage<<AT45DB0X_PAGEADDRNUM)+pMetrics->wIndexAddr;
	pMetrics->Address1 = 0xff&(BYTE)(dwAddr>>16);
	pMetrics->Address2 = 0xff&(BYTE)(dwAddr>>8);
	pMetrics->Address3 = 0xff&(BYTE)(dwAddr);
}

void CMyArEEPROM_AT45DB0X::SendCommand(BYTE Command,AT45DB0X_METRICS* pMetrics)
{
	while(IsBusy());
	AT45DB0X_ENABLE;
	BYTE DataSnd[4];
	DataSnd[0] = Command;
	DataSnd[1] = pMetrics->Address1;
	DataSnd[2] = pMetrics->Address2;
	DataSnd[3] = pMetrics->Address3;

	SPISndByteSyn(&g_spi,DataSnd,4);
}


//-----------------------------------------------------------------------------
BOOL CMyArEEPROM_AT45DB0X::IsError(void)
{
	for(WORD i=0;i<1000;i++)
	{
		BYTE Status = GetStatus();
		if((Status&AT45DB0X_STATUSMASK)==AT45DB0X_STATUSOK) return FALSE;
	}

	return TRUE;
}

void CMyArEEPROM_AT45DB0X::iiiReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	if(wCountByte==0) return;
	AT45DB0X_METRICS metrics;
	GetMetrics(dwAddr,&metrics);
	SendCommand(0xe8,&metrics);
	BYTE DataSnd[4];
	DataSnd[0] = 0;
	DataSnd[1] = 0;
	DataSnd[2] = 0;
	DataSnd[3] = 0;
	SPISndByteSyn(&g_spi,DataSnd,4);
	SPIRcvByteSyn(&g_spi,pData,wCountByte);
	AT45DB0X_DISABLE;
}

void CMyArEEPROM_AT45DB0X::iiiReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	if(wCountWord==0) return;
	AT45DB0X_METRICS metrics;
	GetMetrics(dwAddr,&metrics);
	SendCommand(0xe8,&metrics);
	BYTE DataSnd[4];
	DataSnd[0] = 0;
	DataSnd[1] = 0;
	DataSnd[2] = 0;
	DataSnd[3] = 0;
	SPISndByteSyn(&g_spi,DataSnd,4);
	SPIRcvWordSyn(&g_spi,pData,wCountWord);
	AT45DB0X_DISABLE;
}

void CMyArEEPROM_AT45DB0X::iiiWriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	if(wCountByte==0) return;
	AT45DB0X_METRICS metrics;
	while(wCountByte)
	{
		GetMetrics(dwAddr,&metrics);
		SendCommand(0x53,&metrics);
		AT45DB0X_DISABLE;
		SendCommand(0x84,&metrics);
		while(1)
		{
			SPISndByteSyn(&g_spi,pData,1);
			dwAddr++;
			pData++;
			wCountByte--;
			if(wCountByte==0||dwAddr%AT45DB0X_PAGESIZE==0L) break;
		}
		AT45DB0X_DISABLE;
		SendCommand(0x83,&metrics);
		AT45DB0X_DISABLE;
	}
}

void CMyArEEPROM_AT45DB0X::iiiWriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	if(wCountWord==0) return;
	AT45DB0X_METRICS metrics;
	while(wCountWord)
	{
		GetMetrics(dwAddr,&metrics);
		SendCommand(0x53,&metrics);
		AT45DB0X_DISABLE;
		SendCommand(0x84,&metrics);
		while(1)
		{
			SPISndWordSyn(&g_spi,pData,1);
			dwAddr += 2;
			pData++;
			wCountWord--;
			if(wCountWord==0||dwAddr%AT45DB0X_PAGESIZE==0L) break;
		}
		AT45DB0X_DISABLE;
		SendCommand(0x83,&metrics);
		AT45DB0X_DISABLE;
	}
}

//-----------------------------------------------------------------------------
BOOL CMyArEEPROM_AT45DB0X::ReadBlockHead(DWORD dwAddr,WORD* pCount)
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
	*pCount = 0;				// ¶ÁÈ¡Ê§°Ü
	return FALSE;
}

BOOL CMyArEEPROM_AT45DB0X::ReadBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord)
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

void CMyArEEPROM_AT45DB0X::WriteBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord)
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
	iiiWriteDataWord(dwAddr+2+SIZEOFBYTE(blockinfo),pData,wCountWord);}


