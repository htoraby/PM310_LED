#include "main.h"

// void LCDWrite(BYTE Data,     // 
//                 BOOL bCmd,   // 0:cmd;1:Data
//                 BOOL blight) // ±³¹â:0:Ãð,1:ÁÁ
//-----------------------------------------------------------------------------

void LCD_LCDSndData(BYTE Data)
{
    LCDWrite(Data, TRUE);
}

void LCD_LCDSndCommand(BYTE Command)
{
    LCDWrite(Command, FALSE);
}

void LCD_HWRest(void)
{
    LCD_LCDSndCommand(0xe2);	// system reset
    DelayOnce(20000);
}

void LCD_Setup(void)
{
	LCD_LCDSndCommand(0x2b);	// internal power control
	LCD_LCDSndCommand(0x25);	// set TC=-0.05%
	LCD_LCDSndCommand(0xa2);	// set line rate //A2:37.0Klps
	LCD_LCDSndCommand(0xea);	// 0XEA//set bias1/11
	LCD_LCDSndCommand(0xf1);	// set com end
	LCD_LCDSndCommand(0x9f);	// set duty :1/160
	LCD_LCDSndCommand(0x81);	// set VLCD value
	LCD_LCDSndCommand(0xbf);	// VLCD=(CV0+Cpm*pm)*(1+(T-25)*CT%)
// 	LCD_LCDSndCommand(0x8f);	// VLCD=(CV0+Cpm*pm)*(1+(T-25)*CT%)
	LCD_LCDSndCommand(0xc4);	// 0XC4 //set LCD mapping control  //scan dirction com0~127
	LCD_LCDSndCommand(0x89);	// set RAM address control
	LCD_LCDSndCommand(0xd1);	// R_G_B
	LCD_LCDSndCommand(0xd5);	// 4k color
	LCD_LCDSndCommand(0xc8);
	LCD_LCDSndCommand(0x18);
	LCD_LCDSndCommand(0x25);

// 	LCD_LCDSndCommand(0xa5);	// 0xa5//display  on
	LCD_LCDSndCommand(0xad);	// 0xad//display  on
	
	LCD_LCDSndCommand(0xf4);	// set column start address
	LCD_LCDSndCommand(0x25);	// start address
	LCD_LCDSndCommand(0xf6);	// set column end address
	LCD_LCDSndCommand(0x5a);	// (0x4f+1)*3=240  5a   //90

	LCD_LCDSndCommand(0xf5);	// set row start address
	LCD_LCDSndCommand(0x00);	// start address=0x00
	LCD_LCDSndCommand(0xf7);	// set row end address
	LCD_LCDSndCommand(0x9f);	// row end address=9f

/*	LCD_LCDSndCommand(wRow1);	// set row MSB address
	LCD_LCDSndCommand(wRow2);	// set row LSB address
	LCD_LCDSndCommand(0x12);	// set column MSB address  //    12
	LCD_LCDSndCommand(0x05);	// set column LSB address  //37  05
*/
 	LCD_LCDSndCommand(0xf8);	// inside mode
}

void LCD_Flush(void)
{
    WORD* pLCDBuffer;
    WORD i,j,k;
    WORD wLCDContrast;
    WORD wData;
    WORD wMask1;
    WORD wMask2; 
    WORD wLCDData;
    WORD wRow1,wRow2,wRow,wRowstart;

    LCD_LCDSndCommand(0xad);
//    if(g_bLCDOpened)
//    {
////         LCD_LCDSndCommand(0xad);	// 0xad//display  on
//        s_blight = TRUE;
//    }
//    else
//    {
////         LCD_LCDSndCommand(0xac);	// 0xad//display  on
//        s_blight = FALSE;
//    }

    LCD_LCDSndCommand(0x81);	// set VLCD value
    wLCDContrast = 112 + g_deviceParam.wLCDContrast * 6;
    if(wLCDContrast>208) wLCDContrast = 208;
    LCD_LCDSndCommand(wLCDContrast);	// VLCD=(CV0+Cpm*pm)*(1+(T-25)*CT%)

    if(g_bLCDRefresh==FALSE) return;
    if(g_wLCDRefreshAddrMin>g_wLCDRefreshAddrMax) return;
    pLCDBuffer = LCD_GetLCDBuffer();
    if(pLCDBuffer==NULL) return;
    wRow1 = g_wLCDRefreshAddrMin/10;
    wRow2 = g_wLCDRefreshAddrMax/10;
    wRow = wRow2 - wRow1;
    wRowstart = wRow1;

    wRow2 = 0x60 | (wRow1&0xf);
    wRow1 = 0x70 | ((wRow1>>4)&0xf);

    LCD_LCDSndCommand(0xf4);	// set column start address
    LCD_LCDSndCommand(0x25);	// start address
    LCD_LCDSndCommand(0xf6);	// set column end address
    LCD_LCDSndCommand(0x5a);	// (0x4f+1)*3=240  5a   //90

    LCD_LCDSndCommand(0xf5);	// set row start address
    LCD_LCDSndCommand(0x00);	// start address=0x00
    LCD_LCDSndCommand(0xf7);	// set row end address
    LCD_LCDSndCommand(0x9f);	// row end address=9f*/

    LCD_LCDSndCommand(wRow1);	// set row MSB address
    LCD_LCDSndCommand(wRow2);	// set row LSB address
    LCD_LCDSndCommand(0x12);	// set column MSB address  //    12
    LCD_LCDSndCommand(0x05);	// set column LSB address  //37  05

    LCD_LCDSndCommand(0xf8);	// inside mode

    pLCDBuffer = &pLCDBuffer[(wRowstart)*10];
    if(wRow>160) wRow = 160;
    for(i=0;i<wRow+1;i++)
    {
        for(j=0;j<20;j++)
        {
            wLCDData = *pLCDBuffer;
            if(j%2==0) wLCDData = wLCDData&0x00ff;
            else wLCDData = (wLCDData>>8)&0x00ff;
            for(k=0;k<4;k++)
            {
                wData = 0;
                wMask1 = (1<<(7-k*2));
                wMask2 = (1<<(6-k*2));
                if(wLCDData&wMask1) wData |= 0xf0;
                if(wLCDData&wMask2) wData |= 0x0f;
                LCD_LCDSndData(wData);
            }
            if(j%2) pLCDBuffer++;
        }
        LCD_LCDSndData(0x00);
    }

    g_bLCDRefresh = FALSE;
    g_wLCDRefreshAddrMin = (LCD_SCANALLBYTES>>1)-1;
    g_wLCDRefreshAddrMax = 0;
}
