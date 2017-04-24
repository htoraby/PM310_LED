#include <Main.h>

//#ifndef _WIN32
//#pragma DATA_SECTION(s_wLCDBuffer,"extsram");
//#endif
static WORD s_wLCDBuffer[LCD_WBUFFERSIZE];

BOOL g_bLCDOpened;
BOOL g_bLCDRefresh;
DWORD g_wLCDRefreshAddrMin;
DWORD g_wLCDRefreshAddrMax;


//-----------------------------------------------------------------------------
void LCD_OnInitMem(void)
{
	LCD_OnInitA();
	g_bLCDOpened = TRUE;
	g_bLCDRefresh = FALSE;
	g_wLCDRefreshAddrMin = 0;
	g_wLCDRefreshAddrMax = LCD_WBUFFERSIZE-1;
}

WORD* LCD_GetLCDBuffer(void)
{
#ifdef LCD_WBUFFERPOINTER
	return (WORD*)LCD_WBUFFERPOINTER;
#else
	return s_wLCDBuffer;
#endif
}

void LCD_Open(void)
{
	if(g_bLCDOpened==FALSE) g_bLCDRefresh = TRUE;
	g_bLCDOpened = TRUE;
}

void LCD_Close(void)
{
	if(g_bLCDOpened==TRUE) g_bLCDRefresh = TRUE;
	g_bLCDOpened = FALSE;
}

void LCD_Clear(void)
{
	WORD* pLCDBuffer;
	WORD i;

	pLCDBuffer = LCD_GetLCDBuffer();
	if(pLCDBuffer==NULL) return;
	g_bLCDCursorON = FALSE;
	for(i=0;i<LCD_WBUFFERSIZE;i++)
	{
#ifndef LCD_MULTICOLOR
		pLCDBuffer[i] = (g_wLCDColorBK==COLOR_BLACK)?0x0000:0xffff;
#else
		pLCDBuffer[i] = (g_wLCDColorBK&0x0f)+((g_wLCDColorBK&0x0f)<<8);
#endif
	}
	g_bLCDRefresh = TRUE;
	g_wLCDRefreshAddrMin = 0;
	g_wLCDRefreshAddrMax = LCD_WBUFFERSIZE-1;
}

void LCD_SetData(WORD wAddress,BYTE Data,BYTE Mask)
{
	WORD* pLCDBuffer;
	BOOL bHighByte;
#ifndef LCD_MULTICOLOR
	BYTE DataOld;
#else
	WORD wAddressData;
	WORD i;
	WORD wDataOld;
#endif

	pLCDBuffer = LCD_GetLCDBuffer();
	if(pLCDBuffer==NULL) return;
	if(Mask==0) return;
	if(wAddress>=LCD_SCANALLBYTES) return;
#ifndef LCD_MULTICOLOR
	bHighByte = (wAddress&0x0001)?TRUE:FALSE;
	wAddress >>= 1;
	if(wAddress>=LCD_WBUFFERSIZE) return;

	if(bHighByte) DataOld = (BYTE)(pLCDBuffer[wAddress]>>8);
	else DataOld = (BYTE)(pLCDBuffer[wAddress]&0x00ff);
	if(g_bLCDSetDataXor) Data = (Data&Mask)^DataOld;
	else
	{
		if(g_wLCDColor==COLOR_BLACK) Data ^= 0xff;
		if(Mask!=0xff) Data = (Data&Mask)|(DataOld&(0xff^Mask));
	}
	Data &= 0xff;
	if(DataOld!=Data)
	{
		if(bHighByte)
		{
			pLCDBuffer[wAddress] &= 0x00ff;
			pLCDBuffer[wAddress] |= ((WORD)Data)<<8;
		}
		else
		{
			pLCDBuffer[wAddress] &= 0xff00;
			pLCDBuffer[wAddress] |= (WORD)Data;
		}
		if(wAddress<=g_wLCDRefreshAddrMin) g_wLCDRefreshAddrMin = wAddress;
		if(wAddress>=g_wLCDRefreshAddrMax) g_wLCDRefreshAddrMax = wAddress;
		g_bLCDRefresh = TRUE;
	}
#else
	for(i=0;i<8;i++)
	{
		if(Mask&(0x80>>i))
		{
			wAddressData = wAddress*8L+i;
			bHighByte = (wAddressData&0x0001)?TRUE:FALSE;
			wAddressData >>= 1;
			if(wAddress>=LCD_WBUFFERSIZE) return;
			wDataOld = pLCDBuffer[wAddressData];
			if(g_bLCDSetDataXor)
			{
				if(bHighByte) pLCDBuffer[wAddressData] ^= 0x0f00;
				else pLCDBuffer[wAddressData] ^= 0x000f;
			}
			else
			{
				if(bHighByte)
				{
					pLCDBuffer[wAddressData] &= 0x00ff;
					pLCDBuffer[wAddressData] |= ((Data&(0x80>>i))?g_wLCDColor:g_wLCDColorBK)<<8;
				}
				else
				{
					pLCDBuffer[wAddressData] &= 0xff00;
					pLCDBuffer[wAddressData] |= ((Data&(0x80>>i))?g_wLCDColor:g_wLCDColorBK);
				}
			}
			if(wDataOld!=pLCDBuffer[wAddressData])
			{
				if(wAddressData<=g_wLCDRefreshAddrMin) g_wLCDRefreshAddrMin = wAddressData;
				if(wAddressData>=g_wLCDRefreshAddrMax) g_wLCDRefreshAddrMax = wAddressData;
				g_bLCDRefresh = TRUE;
			}
		}
	}
#endif
}

