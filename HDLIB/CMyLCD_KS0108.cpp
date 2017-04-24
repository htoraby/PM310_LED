#include <Main.h>


//-----------------------------------------------------------------------------
void CMyLCD_KS0108::LCDWhile(BYTE BlockSel)
{
	WORD wCountDelay = 1000;
	if(BlockSel==0) while((IOLCD_C1&0x90)&&(wCountDelay--));
	else if(BlockSel==1) while((IOLCD_C2&0x90)&&(wCountDelay--));
}

void CMyLCD_KS0108::LCDSndData(BYTE BlockSel,BYTE Data)
{
	LCDWhile(BlockSel);
	if(BlockSel==0) IOLCD_D1 = Data;
	else if(BlockSel==1) IOLCD_D2 = Data;
}

void CMyLCD_KS0108::LCDSndCommand(BYTE BlockSel,BYTE Command)
{
	LCDWhile(BlockSel);
	if(BlockSel==0) IOLCD_C1 = Command;
	else if(BlockSel==1) IOLCD_C2 = Command;
}

void CMyLCD_KS0108::iiiSetup(void)
{
	CMyLCDMem::iiiSetup();
	LCDSndCommand(0,0xc0);
	LCDSndCommand(1,0xc0);
	LCDSndCommand(0,0xb8);
	LCDSndCommand(1,0xb8);
	LCDSndCommand(0,0x40);
	LCDSndCommand(1,0x40);
}

void CMyLCD_KS0108::iiiFlush(void)
{
	CMyLCDMem::iiiFlush();
	if(m_bOpened)
	{
		LCDSndCommand(0,0x3f);
		LCDSndCommand(1,0x3f);
	}
	else
	{
		LCDSndCommand(0,0x3e);
		LCDSndCommand(1,0x3e);
	}
	if(m_bRefresh==FALSE) return;
	WORD* pLCDBuffer = GetLCDBuffer();
	if(pLCDBuffer==NULL) return;	
	for(WORD k=0;k<2;k++)
	{
		//设置显示起始行为第一行:
		LCDSndCommand(k,0xc0);
		for(WORD i=0;i<8;i++)
		{
			//设置显示页为第一页:
			LCDSndCommand(k,0xb8+i);
			//设置显示列为第一列:
			LCDSndCommand(k,0x40);
			for(WORD j=0;j<64;j++)
			{
				WORD wAddress = (WORD)(k*512+j*8+(7-i));
				BYTE Data;
				if(wAddress&0x0001) Data = (BYTE)(pLCDBuffer[wAddress>>1]>>8);
				else Data = (BYTE)(pLCDBuffer[wAddress>>1]&0xff);
				LCDSndData(k,Data);
			}
		}
	}
	m_bRefresh = FALSE;
}
