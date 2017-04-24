#include "main.h"
/*******************************************************************/
unsigned short g_bFormatRealFillBlank;
    
static unsigned short s_wRefreshNo;

unsigned short g_wCodeLED[16];
unsigned short g_wMaskLED[16];

static char s_szTextBuffer[6];
unsigned short g_wLEDTestFlag;
BOOL g_bLEDtestOK = FALSE;
/*******************************************************************/
static unsigned short GetCodeLED(char cAscii)
{
	unsigned short wCodeLED;
	switch(cAscii)
	{
	case '0': wCodeLED = 0x003f; break;
 	case '1': wCodeLED = 0x0006; break;
	case '2': wCodeLED = 0x005b; break;
	case '3': wCodeLED = 0x004f; break;
	case '4': wCodeLED = 0x0066; break;
	case '5': wCodeLED = 0x006d; break;
	case '6': wCodeLED = 0x007d; break;
	case '7': wCodeLED = 0x0007; break;
	case '8': wCodeLED = 0x007f; break;
	case '9': wCodeLED = 0x006f; break;
	case 'A': wCodeLED = 0x0077; break;
	case 'b': wCodeLED = 0x007c; break;
	case 'c': wCodeLED = 0x0058; break;
	case 'd': wCodeLED = 0x005e; break;
	case 'E': wCodeLED = 0x0079; break;
	case 'F': wCodeLED = 0x0071; break;
	case 'G': wCodeLED = 0x007b; break;
	case 'h': wCodeLED = 0x0074; break;
	case 'I': wCodeLED = 0x0030; break;
	case 'J': wCodeLED = 0x000e; break;
	case 'K': wCodeLED = 0x0072; break;
	case 'L': wCodeLED = 0x0038; break;
	case 'm': wCodeLED = 0x0054; break;
	case 'N': wCodeLED = 0x0037; break;
	case 'o': wCodeLED = 0x005c; break;
	case 'P': wCodeLED = 0x0073; break;
	case 'q': wCodeLED = 0x0067; break;
	case 'r': wCodeLED = 0x0050; break;
	case 'S': wCodeLED = 0x006d; break;
	case 't': wCodeLED = 0x0078; break;
	case 'U': wCodeLED = 0x003e; break;
	case 'v': wCodeLED = 0x001c; break;
	case 'W': wCodeLED = 0x001d; break;
	case 'x': wCodeLED = 0x0076; break;
	case 'y': wCodeLED = 0x006e; break;
	case 'z': wCodeLED = 0x005f; break;
	case '-': wCodeLED = 0x0040; break;
	case '_': wCodeLED = 0x0008; break;
	case '.': wCodeLED = 0x0080; break;
	default: wCodeLED = 0x0000; break;
	}
	return wCodeLED;
}

void SetLevelLight(unsigned short wLightCode,unsigned short wStatus)
{
	if(wLightCode>=16) return;
	g_wCodeLED[wLightCode] |= wStatus<<8;
}

void ResetLevelLight(unsigned short wLightCode,unsigned short wStatus)
{
	if(wLightCode>=16) return;
	g_wCodeLED[wLightCode] &= (wStatus<<8)^0xffff;
}

void LEDClearBarStatus(void)
{
	unsigned char i;
	for(i=5;i<16;i++)
	{
		g_wCodeLED[i] = 0x0000;
	}	
}

void LEDClear(void)
{
	unsigned char i;
	for(i=0;i<16;i++)
	{
		g_wCodeLED[i] = 0x0000;
		g_wMaskLED[i] = 0x0000;
	}
}

void OnInitLED(void)
{
	unsigned char i;
	s_wRefreshNo = 0;
	for(i=0;i<16;i++)
	{
		g_wCodeLED[i] = 0x00ff;
		g_wMaskLED[i] = 0x0000;
	}
	g_wLEDTestFlag = LEDTESTTIME;
	g_bFormatRealFillBlank = 1;
}

void OnTimer1000msLED(void)
{
	short i;
	if(g_wLEDTestFlag)
	{
		g_wLEDTestFlag--;
		if(g_wLEDTestFlag==0) g_bLEDtestOK = TRUE;
		for(i=0;i<16;i++)
		{
			g_wCodeLED[i] = 0x00ff;
			g_wMaskLED[i] = 0x0000;
		}
	}
}

void TestLED(void)
{
	g_wLEDTestFlag = LEDTESTTIME;
}
/*
void OnRefreshLED(void)
{
	unsigned short wSelectLED;
	s_wRefreshNo++;
	s_wRefreshNo %= 16;
	if(g_wLEDTestFlag==0x55) g_wCodeLED[s_wRefreshNo] = 0xffff;////////////////////////////
	if(g_wMaskLED[s_wRefreshNo])
	{
		if(g_wMaskLED[s_wRefreshNo]&0xff) IO_WriteData(1,0xff);
		else 
		{
			IO_WriteData(3,0xff);
			IO_WriteData(1,(unsigned char)((g_wCodeLED[s_wRefreshNo]&0xff)^0xff));
		}
		if(g_wMaskLED[s_wRefreshNo]>>8) IO_WriteData(2,0xff);
		else 
		{
			IO_WriteData(4,0xff);
			IO_WriteData(2,(unsigned char)((g_wCodeLED[s_wRefreshNo]>>8)^0xff));
		}
	}
	else 
	{
		IO_WriteData(3,0xff);
		IO_WriteData(1,(unsigned char)((g_wCodeLED[s_wRefreshNo]&0xff)^0xff));
		IO_WriteData(4,0xff);
		IO_WriteData(2,(unsigned char)((g_wCodeLED[s_wRefreshNo]>>8)^0xff));
	}
	switch(s_wRefreshNo)
	{
	case  0: wSelectLED = 0xfffe; break;
	case  1: wSelectLED = 0xfffd; break;
	case  2: wSelectLED = 0xfffb; break;
	case  3: wSelectLED = 0xfff7; break;
	case  4: wSelectLED = 0xffef; break;
	case  5: wSelectLED = 0xffdf; break;
	case  6: wSelectLED = 0xffbf; break;
	case  7: wSelectLED = 0xff7f; break;
	case  8: wSelectLED = 0xfeff; break;
	case  9: wSelectLED = 0xfdff; break;
	case 10: wSelectLED = 0xfbff; break;
	case 11: wSelectLED = 0xf7ff; break;
	case 12: wSelectLED = 0xefff; break;
	case 13: wSelectLED = 0xdfff; break;
	case 14: wSelectLED = 0xbfff; break;
	case 15: wSelectLED = 0x7fff; break;
	}
	IO_WriteData(3,(unsigned char)(wSelectLED&0xff));
	IO_WriteData(4,(unsigned char)(wSelectLED>>8));
}
*/
void LEDResetMask(void)
{
	MemoryClear(g_wMaskLED,sizeof(g_wMaskLED)/2);
}

void LEDSetMask(unsigned short wPosX,unsigned short wPosY,unsigned short wLength)
{
	unsigned int i;
	if(wPosY>3) return;
	if(wPosY<4)
	{
		for(i=0;i<wLength;i++)
		{
			if(i+wPosX>=4) break;
			g_wMaskLED[wPosY*4+i+wPosX] |= 1;
		}
	}
}

void LEDAsciiOut(unsigned short wPosX,unsigned short wPosY,char* pszText)
{
	unsigned int i;
	unsigned short wCodeLED;
	if(wPosY>4) return;
	if(wPosY<4)
	{
		for(i=0;i<4;i++)
		{
			if(i+wPosX>=4) break;
			if(*pszText==0) break;
			wCodeLED = GetCodeLED(*pszText);
			pszText++;
			if(*pszText=='.')
			{
				wCodeLED |= 0x0080;
				pszText++;
			}
			g_wCodeLED[wPosY*4+i+wPosX] &= 0xff00;
			g_wCodeLED[wPosY*4+i+wPosX] |= wCodeLED;
		}
	}

	else
	{
		if(*pszText==0) return;
		wCodeLED = GetCodeLED(*pszText);
		pszText++;
		g_wCodeLED[4] &= 0x00ff;
		g_wCodeLED[4] |= wCodeLED<<8;
	}
}

void LEDByteOut(unsigned short wPosX,unsigned short wPosY,unsigned short wData,unsigned short wFormat)
{
	char* pText;
	pText = s_szTextBuffer;
	wData &= 0xff;
	if(wFormat>=3) *pText++ = '0'+(char)(wData/100);
	if(wFormat>=2) *pText++ = '0'+(char)(wData%100/10);
	*pText++ = '0'+(char)(wData%10);
	*pText = 0;
	LEDAsciiOut(wPosX,wPosY,s_szTextBuffer);
}

void LEDWordOut(unsigned short wPosX,unsigned short wPosY,unsigned short wData)
{
	FormatReal(s_szTextBuffer,wData,0x50);
	LEDAsciiOut(wPosX,wPosY,s_szTextBuffer);
}

void LEDRealOut(unsigned short wPosX,unsigned short wPosY,unsigned long fData,unsigned short wFormat)
{
	FormatReal(s_szTextBuffer,fData,wFormat);
	LEDAsciiOut(wPosX,wPosY,s_szTextBuffer);
}

void FormatReal(char* pszText,unsigned long dwData,unsigned short wFormat)
{
	char* pszTemp;
	unsigned short wCountAfterDot;
	pszTemp = pszText;
	*pszTemp = 0;
	wCountAfterDot = wFormat&0x000f;
	if(wCountAfterDot>4) return;
	switch(wFormat>>4)
	{
// 	case 8: if(dwData>99999999) dwData = 99999999; break;
// 	case 7: if(dwData>9999999) dwData = 9999999; break;
// 	case 6: if(dwData>999999) dwData = 999999; break;
// 	case 5: if(dwData>99999) dwData = 99999; break;
	case 4: if(dwData>9999) dwData = 9999; break;
	case 3: if(dwData>999) dwData = 999; break;
	case 2: if(dwData>99) dwData = 99; break;
	default: return;
	}
	switch(wFormat>>4)
	{
// 	case 8: *pszTemp++ = '0'+(char)(dwData%100000000L/10000000L);
// 			if(wCountAfterDot==7) *pszTemp++ = '.';
// 	case 7: *pszTemp++ = '0'+(char)(dwData%10000000L/1000000L);
// 			if(wCountAfterDot==6) *pszTemp++ = '.';
// 	case 6: *pszTemp++ = '0'+(char)(dwData%1000000L/100000L);
// 			if(wCountAfterDot==5) *pszTemp++ = '.';
// 	case 5: *pszTemp++ = '0'+(char)(dwData%100000L/10000L);
// 			if(wCountAfterDot==4) *pszTemp++ = '.';
	case 4: *pszTemp++ = '0'+(char)(dwData%10000L/1000L);
			if(wCountAfterDot==3) *pszTemp++ = '.';
	case 3: *pszTemp++ = '0'+(char)(dwData%1000L/100L);
			if(wCountAfterDot==2) *pszTemp++ = '.';
	case 2: *pszTemp++ = '0'+(char)(dwData%100L/10L);
			if(wCountAfterDot==1) *pszTemp++ = '.';
			*pszTemp++ = '0'+(char)(dwData%10L);
			break;
	default: return;
	}
	*pszTemp = 0;
	if(g_bFormatRealFillBlank)
	{
		pszTemp = pszText;
		wCountAfterDot = (wFormat>>4) - wCountAfterDot - 1;
		while(wCountAfterDot--)
		{
			if(*pszTemp=='0') *pszTemp = ' ';
			else break;
			pszTemp++;
		}
	}
	g_bFormatRealFillBlank = 1;
}
