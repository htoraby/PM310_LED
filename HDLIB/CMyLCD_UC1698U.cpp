#include <Main.h>

//-----------------------------------------------------------------------------
void CMyLCD_UC1698U::LCDSndData(BYTE Data)
{
	IOLCD_UC1698U_D = Data;
}

void CMyLCD_UC1698U::LCDSndCommand(BYTE Command)
{
	IOLCD_UC1698U_C = Command;
}

void CMyLCD_UC1698U::HWRest(void)
{
	LCDSndCommand(0xe2);	// system reset
	DelayOnce(20000);
}

void CMyLCD_UC1698U::iiiSetup(void)
{
	LCDSndCommand(0x2b);	// internal power control
	LCDSndCommand(0x25);	// set TC=-0.05%
	LCDSndCommand(0xa2);	// set line rate //A2:37.0Klps
	LCDSndCommand(0xea);	// 0XEA//set bias1/11
	LCDSndCommand(0xf1);	// set com end
	LCDSndCommand(0x9f);	// set duty :1/160
	LCDSndCommand(0x81);	// set VLCD value
	LCDSndCommand(0xbf);	// VLCD=(CV0+Cpm*pm)*(1+(T-25)*CT%)
// 	LCDSndCommand(0x8f);	// VLCD=(CV0+Cpm*pm)*(1+(T-25)*CT%)
	LCDSndCommand(0xc4);	// 0XC4 //set LCD mapping control  //scan dirction com0~127
	LCDSndCommand(0x89);	// set RAM address control
	LCDSndCommand(0xd1);	// R_G_B
	LCDSndCommand(0xd5);	// 4k color
	LCDSndCommand(0xc8);
	LCDSndCommand(0x18);
	LCDSndCommand(0x25);

// 	LCDSndCommand(0xa5);	// 0xa5//display  on
	LCDSndCommand(0xad);	// 0xad//display  on
}

void CMyLCD_UC1698U::iiiFlush(void)
{
	if(g_lcd.m_bOpened) LCDSndCommand(0xad);	// 0xad//display  on
	else LCDSndCommand(0xac);	// 0xad//display  on

	LCDSndCommand(0x81);	// set VLCD value
	WORD wLCDContrast = 112 + g_deviceParam.wLCDContrast * 6;
	if(wLCDContrast>208) wLCDContrast = 208;
	LCDSndCommand(wLCDContrast);	// VLCD=(CV0+Cpm*pm)*(1+(T-25)*CT%)

	if(g_lcd.m_bRefresh==FALSE) return;
	WORD* pLCDBuffer = g_lcd.GetLCDBuffer();
	if(pLCDBuffer==NULL) return;

	LCDSndCommand(0xf4);	// set column start address
	LCDSndCommand(0x25);	// start address
	LCDSndCommand(0xf6);	// set column end address
	LCDSndCommand(0x5a);	// (0x4f+1)*3=240  5a   //90

	LCDSndCommand(0xf5);	// set row start address
	LCDSndCommand(0x00);	// start address=0x00
	LCDSndCommand(0xf7);	// set row end address
	LCDSndCommand(0x9f);	// row end address=9f

	LCDSndCommand(0x70);	// set row MSB address
	LCDSndCommand(0x60);	// set row LSB address
	LCDSndCommand(0x12);	// set column MSB address  //    12
	LCDSndCommand(0x05);	// set column LSB address  //37  05

	LCDSndCommand(0xf8);	// inside mode

	for(int i=0;i<160;i++)
	{
		for(int j=0;j<20;j++)
		{
			WORD wLCDData = 0;
			if(j%2==0) wLCDData = *pLCDBuffer&0x00ff;
			else wLCDData = ((*pLCDBuffer)>>8)&0x00ff;
			for(int k=0;k<4;k++)
			{
				WORD wData = 0;
				WORD wMask1 = (1<<(7-k*2));
				WORD wMask2 = (1<<(6-k*2));
				if(wLCDData&wMask1) wData |= 0xf0;
				if(wLCDData&wMask2) wData |= 0x0f;
				LCDSndData(wData);
			}
			if(j%2) pLCDBuffer++;
		}
		LCDSndData(0x00);
	}
}
