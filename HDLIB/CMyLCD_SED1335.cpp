#include <Main.h>

#ifdef LCDSED1335_DIRECT_0
#define LCD_SCANHLINE				(LCDSED1335_CXDOT)
#define LCD_SCANHBYTE				(LCDSED1335_CXDOT/8)
#define LCD_SCANVLINE				(LCDSED1335_CYDOT)
#endif
#ifdef LCDSED1335_DIRECT_90
#define LCD_SCANHLINE				(LCDSED1335_CYDOT)
#define LCD_SCANHBYTE				(LCSED1335D_CYDOT/8)
#define LCD_SCANVLINE				(LCDSED1335_CXDOT)
#endif
#ifdef LCDSED1335_DIRECT_180
#define LCD_SCANHLINE				(LCDSED1335_CXDOT)
#define LCD_SCANHBYTE				(LCDSED1335_CXDOT/8)
#define LCD_SCANVLINE				(LCDSED1335_CYDOT)
#endif
#ifdef LCDSED1335_DIRECT_270
#define LCD_SCANHLINE				(LCDSED1335_CYDOT)
#define LCD_SCANHBYTE				(LCDSED1335_CYDOT/8)
#define LCD_SCANVLINE				(LCDSED1335_CXDOT)
#endif

//-----------------------------------------------------------------------------
void CMyLCD_SED1335::LCDSndData(BYTE Data)
{
	IOLCD_SED1335_D = Data;
}

void CMyLCD_SED1335::LCDSndCommand(BYTE Command)
{
	IOLCD_SED1335_C = Command;
}

void CMyLCD_SED1335::iiiSetup(void)
{
	LCDSndCommand(0x40);
	LCDSndData(0x30);
	LCDSndData(0x87);
	LCDSndData(0x07);
	LCDSndData(LCD_SCANHBYTE-1);
#ifdef SED1335_TCR
	LCDSndData(SED1335_TCR);
#else
	LCDSndData(15000/LCD_SCANVLINE);
#endif
	LCDSndData(LCD_SCANVLINE-1);
	LCDSndData(LCD_SCANHBYTE);
	LCDSndData(0x00);
	LCDSndCommand(0x44);
	LCDSndData(0x00);
	LCDSndData(0x00);
	LCDSndData(LCD_SCANVLINE);
	LCDSndData(LCD_SCANALLBYTES&0xff);
	LCDSndData(LCD_SCANALLBYTES>>8);
	LCDSndData(LCD_SCANVLINE);
	LCDSndData(0x00);
	LCDSndData(0x00);
	LCDSndData(0x00);
	LCDSndData(0x00);
	LCDSndCommand(0x5a);
	LCDSndData(0x00);
	LCDSndCommand(0x5b);
	LCDSndData(0x04);
	LCDSndCommand(0x59);
	LCDSndData(0x04);
}

void CMyLCD_SED1335::iiiFlush(void)
{
	if(g_lcd.m_bOpened)
	{
		LCDSndCommand(0x59);
		LCDSndData(0x04);
	}
	else
	{
		LCDSndCommand(0x58);
		LCDSndData(0x00);
	}
	if(g_lcd.m_bRefresh==FALSE) return;
	if(g_lcd.m_wRefreshAddrMin>=g_lcd.m_wRefreshAddrMax) return;
	WORD* pLCDBuffer = g_lcd.GetLCDBuffer();
	if(pLCDBuffer==NULL) return;
	LCDSndCommand(0x4c);
	LCDSndCommand(0x46);
	LCDSndData((g_lcd.m_wRefreshAddrMin<<1)&0xff);
	LCDSndData((g_lcd.m_wRefreshAddrMin<<1)>>8);
	LCDSndCommand(0x42);
	for(WORD i=g_lcd.m_wRefreshAddrMin;i<=g_lcd.m_wRefreshAddrMax;i++)
	{	
		LCDSndData(pLCDBuffer[i]&0xff);
		LCDSndData(pLCDBuffer[i]>>8);
	}
	g_lcd.m_bRefresh = FALSE;
	g_lcd.m_wRefreshAddrMin = (LCD_SCANALLBYTES>>1)-1;
	g_lcd.m_wRefreshAddrMax = 0;
}
