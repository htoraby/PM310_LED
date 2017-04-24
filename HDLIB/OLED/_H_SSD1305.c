#include "Main.h"

#define portData			PORTD		/*LCD数据地址*/
#define portCommand			PORTD		/*LCD命令地址*/
#define portStatus			PORTD		/*LCD状态地址*/

#define LCD_DELAY	65000

#define SCAN_SIZEBYTE		(LCD_SCANHBYTE*LCD_SCANVLINE)

#ifdef LCD_DIRECT0
#define LCD_DIRECTH
#endif

#ifdef LCD_DIRECT90
#define LCD_DIRECTV
#endif

#ifdef LCD_DIRECT180
#define LCD_DIRECTH
#endif

#ifdef LCD_DIRECT270
#define LCD_DIRECTV
#endif

unsigned short g_wLCDX;
unsigned short g_wLCDY;
unsigned short g_wLCDYAuto;
unsigned short g_bSetDataXor;
unsigned short g_bFormatRealFillBlank;

static unsigned short s_wCursorPosX;
static unsigned short s_wCursorPosY;
static unsigned short s_wCursorWidth;
static unsigned short s_wCursorHeight;
static unsigned short s_bCursorON;

struct CURSORARRAY
{
	unsigned short wPosX;
	unsigned short wPosY;
	unsigned short wWidth;
	unsigned short wHeight;
	unsigned short bON;
};
unsigned short g_bCurArrayON[15];
struct CURSORARRAY CursorArray[15];

static char s_szTextBuffer[20];
/*******************************************************************/

/*******************************************************************/

static unsigned char LCDRcvData(void)
{
//	while((portStatus&0x03)!=0x03);
//	return (portData&0xff);
}

static void LCDSndData(unsigned char Data)
{
//	while((portStatus&0x03)!=0x03);
	OLED_DC = 1;
	OLED_WR = 0;
	OLED_RD = 1;
	OLED_CS = 0;
	portData = Data;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	OLED_CS = 1;		NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	OLED_WR = 1;
	OLED_DC = 0;
}

static void LCDSndCommand(unsigned char Command)
{
//	while((portStatus&0x03)!=0x03);
	OLED_CS = 1;
	OLED_DC = 0;
	OLED_WR = 0;
	OLED_RD = 1;
	OLED_CS = 0;
	portCommand = Command;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	OLED_CS = 1;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	OLED_WR = 1;
	OLED_DC = 1;
}

/*
static void LCDSndData(unsigned char Data)
{
//	while((portStatus&0x03)!=0x03);
	OLED_DC = 1;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	portData = Data;
	OLED_CS = 0;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	OLED_WR = 0;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	OLED_WR = 1;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	OLED_CS = 1;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
}

static void LCDSndCommand(unsigned char Command)
{
//	while((portStatus&0x03)!=0x03);
	OLED_DC = 0;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	portCommand = Command;
	OLED_CS = 0;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	OLED_WR = 0;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	OLED_WR = 1;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	OLED_CS = 1;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
}
static void LCDSndDataAuto(unsigned char Data)
{
	while((portStatus&0x08)!=0x08);
	portData = Data;
}

static void LCDSndCommandAuto(unsigned char Command)
{
	while((portStatus&0x08)!=0x08);
	portCommand = Command;
}
*/
/*******************************************************************/

void LCDInit(void)
{
/*	g_wLCDX = 0;
	g_wLCDY = LCD_LINEOFFSET;
	g_wLCDYAuto = LCD_LINEHEIGHT;
	g_bFormatRealFillBlank = 1;
	s_wCursorPosX = 0;
	s_wCursorPosY = 0;
	s_wCursorWidth = LCD_CXDOT;
	s_wCursorHeight = LCD_LINEHEIGHT;
	s_bCursorON = 0;

//	MemoryClearByte((unsigned char*)0x0,0x5F);
	MemoryClearByte((unsigned char*)&CursorArray,sizeof(CursorArray)*2);
	g_bSetDataXor = 0;
*/
	OLED_CS=0;			//片选OLED 
	OLED_RES=0;	NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;	//复位 OLED， 
	OLED_RES=1; NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
	OLED_DC=0;			//指令信号 
	OLED_CS=1;			//片选OLED 

	LCDSndCommand(0xae);	// display off
	LCDSndCommand(0xd5);	// Set Display ClocDivide Ratio/Oscillator Frequency 
	LCDSndCommand(0x70);	// 105HZ

	LCDSndCommand(0xa8);	// Set Multiplex Ratio
	LCDSndCommand(0x3f);	// set 64 mux

	LCDSndCommand(0xd9);	// Set Pre-charge Period 
	LCDSndCommand(0x22);	//

	LCDSndCommand(0x20);	// Set Memory Addressing Mode
	LCDSndCommand(0x00);

	LCDSndCommand(0xa0);	// seg re-map 0->127
//	LCDSndCommand(0xa1);	// seg re-map 127->0
	LCDSndCommand(0xc0);	// COM scan direction COM0-->COM(N-1)
//	LCDSndCommand(0xc8);	// COM scan direction COM(N-1)-->COM0

	LCDSndCommand(0xda);	// Set COM Pins Hardware Configuration 
	LCDSndCommand(0x12);

	LCDSndCommand(0xd8);	// color_mode_set
	LCDSndCommand(0x00);	// monochrome mode & normal power mode
//	LCDSndCommand(0x30);	// Area Color enable & normal power mode  
//	LCDSndCommand(0x05);	// monochrome mode & lower power display mode 
//	LCDSndCommand(0x35);	// Area Color enable & lower power display mode           

	LCDSndCommand(0x81);	//Set Contrast Control
	LCDSndCommand(0xf0);	//

	LCDSndCommand(0xb0);	//Set Page Start Address for Page Addressing Mode 

	LCDSndCommand(0xd3);	//Set Display offset
	LCDSndCommand(0x00);	//

	LCDSndCommand(0x21);	//Set Column Address
	LCDSndCommand(0x00); 	//Colum address start
	LCDSndCommand(0x7f);	//Colum address end

	LCDSndCommand(0x22); 	//Set page Address
	LCDSndCommand(0x00); 	//Page address start
	LCDSndCommand(0x07);	//Page address end

	LCDSndCommand(0x10);	//Set Higher Column Start Address for Page Addressing Mode 
	LCDSndCommand(0x00); 	//Set Lower Column Start Address for Page Addressing Mode 

	LCDSndCommand(0x40);	//Set Display Start Line 

	LCDSndCommand(0xa4);	//Entire Display Off//全屏关闭
//	LCDSndCommand(0xa5);	//Entire Display On	//全屏显示
	LCDSndCommand(0xa6);	//Display Normal	//正常模式‘1’点亮，‘0’熄灭
//	LCDSndCommand(0xa7);	//Display Inverse	//反显模式‘0’点亮，‘1’熄灭
	
	LCDSndCommand(0xdb);	//Set VCOMH Level 
	LCDSndCommand(0x3c); 	//0.83*VCC
	
//	LCDSndCommand(0xe0);	//Enter Read Modify Write 
	LCDSndCommand(0xee); 	//Exit  Read Modify Write 

	LCDClear();
	LCDOpen();
//	LCDSndCommand(0xaf);	//display on//初始化设置完成后，才能打开 OLED显示功能

}

void LCDOpen(void)
{
	LCDSndCommand(0xaf);	//display on
}

void LCDClose(void)
{
	LCDSndCommand(0xae);
}

void LCDClear(void)
{
	LCDFill(0x00);
}

void LCDFill(unsigned char Data)
{
    unsigned char page;
    unsigned char j;
 
	//	OLED_DC=0; 
	//	OLED_DC=1; 
	for(page=0;page<8;page++) 
	{ 
//	LCDSndCommand(0x22); 	//Set page Address
//	LCDSndCommand(0x00); 	//Page address start
//	LCDSndCommand(0x07);	//Page address end
		LCDSndCommand(0xB0+page);		//set page address 
//		LCDSndCommand(0x00);			//set low address 
//		LCDSndCommand(0x10);			//set higher address 
		for(j=0;j<128;j++)LCDSndData(Data); 
    } 
	LCDSndCommand(0xaf);	//display on
}

 
void LCDDisplay(rom unsigned char *p)
{ 
    unsigned char page;
    unsigned char j;
 
	for(page=0;page<8;page++) 
	{ 
		OLED_DC=0; 
		LCDSndCommand(0xB7-page);		//set page address 
		LCDSndCommand(0x00);			//set low address 
		LCDSndCommand(0x10);			//set higher address 
		OLED_DC=1; 
		for(j=0;j<128;j++)
		//	LCDSndData(j<<(page&0x01)); 
		//	LCDSndData(c_wAscii6Bitmap[j+page*128]);
			LCDSndData(*p++);//
    } 
	LCDSndCommand(0xaf);	//display on
} 
/*

static void LCDSetData(unsigned short wAddress,unsigned char Data,unsigned char Mask)
{
	unsigned char DataOld;
	if(wAddress>=SCAN_SIZEBYTE) return;
	//Set Data Address
	LCDSndData(wAddress&0xff);
	LCDSndData(wAddress>>8);
	LCDSndCommand(0x24);
	if(g_bSetDataXor)
	{
		//Read Data
		LCDSndCommand(0xc5);
		DataOld = LCDRcvData();
		Data = (Data&Mask)^DataOld;
	}
	else
	{
		if(Mask!=0xff)
		{
			//Read Data
			LCDSndCommand(0xc5);
			DataOld = LCDRcvData();
			Data = (Data&Mask)|(DataOld&(0xff^Mask));
		}
	}
	//Write Data
	LCDSndData(Data);
	LCDSndCommand(0xc0);
}

static void LCDDrawCursor(void)
{
	unsigned int i;
#ifdef LCD_DIRECTH
	for(i=0;i<s_wCursorHeight;i++)
	{
		LCDDrawHLine(s_wCursorPosY+i,s_wCursorPosX,s_wCursorPosX+s_wCursorWidth);
	}
#endif
#ifdef LCD_DIRECTV
	for(i=0;i<s_wCursorWidth;i++)
	{
		LCDDrawVLine(s_wCursorPosX+i,s_wCursorPosY,s_wCursorPosY+s_wCursorHeight);
	}
#endif
}

void LCDDrawCursorArray(void)
{
	unsigned int m;
	unsigned int i;
	for(m=0;m<sizeof(CursorArray)/sizeof(struct CURSORARRAY);m++)
	{
		if(g_bCurArrayON[m])// != CursorArray[m].bON 
		{
//			CursorArray[m].bON = g_bCurArrayON[m];
			g_bSetDataXor = 1;
		#ifdef LCD_DIRECTH
			for(i=0;i<CursorArray[m].wHeight ;i++)
			{
				LCDDrawHLine(CursorArray[m].wPosY +i,CursorArray[m].wPosX ,CursorArray[m].wPosX +CursorArray[m].wWidth );
			}
		#endif
		#ifdef LCD_DIRECTV
			for(i=0;i<CursorArray[m].wWidth;i++)
			{
				LCDDrawVLine(CursorArray[m].wPosX+i,CursorArray[m].wPosY,CursorArray[m].wPosY+CursorArray[m].wHeight);
			}
		#endif
			g_bSetDataXor = 0;
		}
	}
}

void LCDCursorArrayAddData(unsigned short wCurID,unsigned short wPosX,unsigned short wPosY,unsigned short wWidth,unsigned short wHeight)
{
	CursorArray[wCurID].wPosX   = wPosX;  
	CursorArray[wCurID].wPosY   = wPosY;  
	CursorArray[wCurID].wWidth  = wWidth; 
	CursorArray[wCurID].wHeight = wHeight;
}

static unsigned short LCDHZ1(unsigned short wPosX,unsigned short wPosY,unsigned short wHZCode)
{
	unsigned int i;
	unsigned short* pTemp;
	if(c_nHZCount>=512) return 2;
	pTemp = (unsigned short*)c_wHZBitmap;
	for(i=0;i<c_nHZCount;i++)
	{
		if(wHZCode==*pTemp)
		{
			LCDImageOut(wPosX,wPosY,12,12,pTemp+1);
			return 1;
		}
		pTemp += 13;
	}
	return 0;
}

static unsigned short LCDHZ2(unsigned short wPosX,unsigned short wPosY,unsigned short wHZCode)
{
	unsigned int i;
	for(i=0;i<g_DeviceExtHZ.wCount;i++)
	{
		if(wHZCode==g_DeviceExtHZ.hzbitmap[i].wCode)
		{
			LCDImageOut(wPosX,wPosY,12,12,g_DeviceExtHZ.hzbitmap[i].wBitmap);
			return 1;
		}
	}
	return 0;



void LCDDrawBlock(void)
{
//	if(s_bCursorON==0)
//	{
//		s_bCursorON = 1;
		g_bSetDataXor = 1;
		LCDDrawCursor();
		g_bSetDataXor = 0;
//	}
}

void LCDCursorON(void)
{
	if(s_bCursorON==0)
	{
		s_bCursorON = 1;
		g_bSetDataXor = 1;
		LCDDrawCursor();
		g_bSetDataXor = 0;
	}
}

void LCDCursorOFF(void)
{
	if(s_bCursorON==1)
	{
		s_bCursorON = 0;
		g_bSetDataXor = 1;
		LCDDrawCursor();
		g_bSetDataXor = 0;
	}
}

void LCDCursorClear(void)
{
	LCDDrawCursor();
	g_bSetDataXor = 1;
	LCDDrawCursor();
	g_bSetDataXor = 0;
}

void LCDSetCursorPosX(unsigned short wCursorPosX,unsigned short wCursorWidth)
{
	s_wCursorPosX = wCursorPosX;
	s_wCursorWidth = wCursorWidth;
}

void LCDSetCursorPosY(unsigned short wCursorPosY,unsigned short wCursorHeight)
{
	s_wCursorPosY = wCursorPosY;
	s_wCursorHeight = wCursorHeight;
}

void LCDDrawPoint(unsigned short wPosX,unsigned short wPosY)
{
	unsigned short wAddress;
	unsigned char DataAndMask;
	if(wPosX>=LCD_CXDOT) return;
	if(wPosY>=LCD_CYDOT) return;
#ifdef LCD_DIRECT90
	wPosY = LCD_CYDOT-1-wPosY;
#endif
#ifdef LCD_DIRECT180
	wPosX = LCD_CXDOT-1-wPosX;
	wPosY = LCD_CYDOT-1-wPosY;
#endif
#ifdef LCD_DIRECT270
	wPosX = LCD_CXDOT-1-wPosX;
#endif
#ifdef LCD_DIRECTH
	wAddress = LCD_SCANHBYTE*wPosY+(wPosX>>3);
	DataAndMask = 0x80>>(wPosX%8);
#endif
#ifdef LCD_DIRECTV
	wAddress = LCD_SCANHBYTE*wPosX+(wPosY>>3);
	DataAndMask = 0x80>>(wPosY%8);
#endif
	LCDSetData(wAddress,DataAndMask,DataAndMask);
}

static unsigned char ReverseLineStyle(unsigned char LineStyle)
{
	unsigned char LineStyleNew;
	LineStyleNew = 0;
	if(LineStyle&0x01) LineStyleNew |= 0x80;
	if(LineStyle&0x02) LineStyleNew |= 0x40;
	if(LineStyle&0x04) LineStyleNew |= 0x20;
	if(LineStyle&0x08) LineStyleNew |= 0x10;
	if(LineStyle&0x10) LineStyleNew |= 0x08;
	if(LineStyle&0x20) LineStyleNew |= 0x04;
	if(LineStyle&0x40) LineStyleNew |= 0x02;
	if(LineStyle&0x80) LineStyleNew |= 0x01;
	return LineStyleNew;
}

static void LCDHLine(unsigned short wPosY,unsigned short wPosX1,unsigned short wPosX2,unsigned char LineStyle)
{
	unsigned int i;
	unsigned short wAddress;
	unsigned short wSetX1;
	unsigned short wSetX2;
	unsigned char Mask1;
	unsigned char Mask2;
	if(wPosX1>=32768) wPosX1 = 0;
	if(wPosX2>=32768) wPosX2 = 0;
	if(wPosX1==wPosX2) return;
	if(wPosX1>wPosX2)
	{
		i = wPosX1;
		wPosX1 = wPosX2;
		wPosX2 = i;
	}
	if(wPosX1>=LCD_CXDOT) return;
	if(wPosX2>=LCD_CXDOT) wPosX2 = LCD_CXDOT;
	if(wPosY>=LCD_CYDOT) return;
#ifdef LCD_DIRECT0
	LineStyle = ((LineStyle<<8)|LineStyle)>>(wPosX1%8);
#endif
#ifdef LCD_DIRECT180
	wPosY = LCD_CYDOT-1-wPosY;
	wSetX1 = wPosX1;
	wSetX2 = wPosX2;
	wPosX1 = LCD_CXDOT-wSetX2;
	wPosX2 = LCD_CXDOT-wSetX1;
	LineStyle = ReverseLineStyle(LineStyle);
	LineStyle = ((LineStyle<<8)|LineStyle)>>(wPosX2%8);
#endif
#ifdef LCD_DIRECTH
	wSetX1 = wPosX1 - wPosX1%8;
	wSetX2 = wPosX2 - wPosX2%8;
	wAddress = LCD_SCANHBYTE*wPosY+(wPosX1>>3);
	for(i=wSetX1;i<=wSetX2;i+=8)
	{
		Mask1 = (i==wSetX1)?(0xff>>(wPosX1-wSetX1)):0xff;
		Mask2 = (i==wSetX2)?(0xff^(0xff>>(wPosX2-wSetX2))):0xff;
		LCDSetData(wAddress,LineStyle,Mask1&Mask2);
		wAddress++;
	}
#endif
#ifdef LCD_DIRECT90
	wPosY = LCD_CYDOT-1-wPosY;
	wAddress = LCD_SCANHBYTE*wPosX1+(wPosY>>3);
	Mask2 = 0x80>>(wPosY%8);
	for(i=0;i<wPosX2-wPosX1;i++)
	{
		Mask1 = (LineStyle&(0x80>>(i%8)))?Mask2:0x00;
		LCDSetData(wAddress,Mask1,Mask2);
		wAddress += LCD_SCANHBYTE;
	}
#endif
#ifdef LCD_DIRECT270
	wPosX1 = LCD_CXDOT-1-wPosX1;
	wPosX2 = LCD_CXDOT-1-wPosX2;
	wAddress = LCD_SCANHBYTE*wPosX1+(wPosY>>3);
	Mask2 = 0x80>>(wPosY%8);
	for(i=0;i<wPosX1-wPosX2;i++)
	{
		Mask1 = (LineStyle&(0x80>>(i%8)))?Mask2:0x00;
		LCDSetData(wAddress,Mask1,Mask2);
		wAddress -= LCD_SCANHBYTE;
	}
#endif
}	

static void LCDVLine(unsigned short wPosX,unsigned short wPosY1,unsigned short wPosY2,unsigned char LineStyle)
{
	unsigned int i;
	unsigned short wAddress;
	unsigned short wSetY1;
	unsigned short wSetY2;
	unsigned char Mask1;
	unsigned char Mask2;
	if(wPosY1>=32768) wPosY1 = 0;
	if(wPosY2>=32768) wPosY2 = 0;
	if(wPosY1==wPosY2) return;
	if(wPosY1>wPosY2)
	{
		i = wPosY1;
		wPosY1 = wPosY2;
		wPosY2 = i;
	}
	if(wPosY1>=LCD_CYDOT) return;
	if(wPosY2>=LCD_CYDOT) wPosY2 = LCD_CYDOT;
	if(wPosX>=LCD_CXDOT) return;
#ifdef LCD_DIRECT0
	wAddress = LCD_SCANHBYTE*wPosY1+(wPosX>>3);
	Mask2 = 0x80>>(wPosX%8);
	for(i=0;i<wPosY2-wPosY1;i++)
	{
		Mask1 = (LineStyle&(0x80>>(i%8)))?Mask2:0x00;
		LCDSetData(wAddress,Mask1,Mask2);
		wAddress += LCD_SCANHBYTE;
	}
#endif
#ifdef LCD_DIRECT180
	wPosX = LCD_CXDOT-1-wPosX;
	wPosY1 = LCD_CYDOT-1-wPosY1;
	wPosY2 = LCD_CYDOT-1-wPosY2;
	wAddress = LCD_SCANHBYTE*wPosY1+(wPosX>>3);
	Mask2 = 0x80>>(wPosX%8);
	for(i=0;i<wPosY1-wPosY2;i++)
	{
		Mask1 = (LineStyle&(0x80>>(i%8)))?Mask2:0x00;
		LCDSetData(wAddress,Mask1,Mask2);
		wAddress -= LCD_SCANHBYTE;
	}
#endif
#ifdef LCD_DIRECT90
	wSetY1 = wPosY1;
	wSetY2 = wPosY2;
	wPosY1 = LCD_CYDOT-wSetY2;
	wPosY2 = LCD_CYDOT-wSetY1;
	LineStyle = ReverseLineStyle(LineStyle);
	LineStyle = ((LineStyle<<8)|LineStyle)>>(wPosY2%8);
#endif
#ifdef LCD_DIRECT270
	wPosX = LCD_CXDOT-1-wPosX;
	LineStyle = ((LineStyle<<8)|LineStyle)>>(wPosY1%8);
#endif
#ifdef LCD_DIRECTV
	wSetY1 = wPosY1 - wPosY1%8;
	wSetY2 = wPosY2 - wPosY2%8;
	wAddress = LCD_SCANHBYTE*wPosX+(wPosY1>>3);
	for(i=wSetY1;i<=wSetY2;i+=8)
	{
		Mask1 = (i==wSetY1)?(0xff>>(wPosY1-wSetY1)):0xff;
		Mask2 = (i==wSetY2)?(0xff^(0xff>>(wPosY2-wSetY2))):0xff;
		LCDSetData(wAddress,LineStyle,Mask1&Mask2);
		wAddress++;
	}
#endif
}

void LCDDrawBKLine(unsigned short wPosY,unsigned short wPosX1,unsigned short wPosX2)
{
	LCDHLine(wPosY,wPosX1,wPosX2,0x00);
}

void LCDDrawHLine(unsigned short wPosY,unsigned short wPosX1,unsigned short wPosX2)
{
	LCDHLine(wPosY,wPosX1,wPosX2,0xff);
}

void LCDDrawVLine(unsigned short wPosX,unsigned short wPosY1,unsigned short wPosY2)
{
	LCDVLine(wPosX,wPosY1,wPosY2,0xff);
}

void LCDDrawHLineDot(unsigned short wPosY,unsigned short wPosX1,unsigned short wPosX2)
{
	LCDHLine(wPosY,wPosX1,wPosX2,0xaa);
}

void LCDDrawVLineDot(unsigned short wPosX,unsigned short wPosY1,unsigned short wPosY2)
{
	LCDVLine(wPosX,wPosY1,wPosY2,0xaa);
}

void LCDDrawXLine(unsigned short wX1,unsigned short wY1,unsigned short wX2,unsigned short wY2)
{
	int dx,dy,dm,dn;
	int m,n,u,v,l,sum;
	dx = wX2-wX1;
	dy = wY2-wY1;
	dm = 1;
	dn = 1;
	if(dx<0){ dx=-dx; dm=-1; }
	if(dy<0){ dy=-dy; dn=-1; }
	if(dx<dy)
	{
		m = dy;
		n = dx;
		u = dm;
		dm = dn;
		dn = u;
		u = wY1;
		v = wX1;
	}
	else
	{
		m = dx;
		n = dy;
		u = wX1;
		v = wY1;
	}
	l = 0;
	sum = m;
	while(sum>0)
	{
		if(dx<dy) LCDDrawPoint(v,u);
		else LCDDrawPoint(u,v);
		l += n;
		u += dm;
		if(l>=m)
		{
			v += dn;
			l -= m;
		}
		sum--;
	}
}

void LCDDrawRect(unsigned short wX1,unsigned short wY1,unsigned short wX2,unsigned short wY2)
{
	LCDDrawHLine(wY1,wX1,wX2);
	LCDDrawHLine(wY2,wX1,wX2);
	LCDDrawVLine(wX1,wY1,wY2);
	LCDDrawVLine(wX2,wY1,wY2+1);
}

void LCDDrawCircle(unsigned short wX0,unsigned short wY0,unsigned short wR)
{
	unsigned int i;
	unsigned short wDotNum;
	unsigned short wR2;
	if(wR>64) return;
	wDotNum = (wR*7+5)/10+1;
	wR2 = wR*wR+wR;
	for(i=0;i<wDotNum;i++)
	{
		if((wR*wR+i*i)>wR2) wR--;
		LCDDrawPoint(wX0-wR,wY0+i-1);
		LCDDrawPoint(wX0+wR-1,wY0+i-1);
		LCDDrawPoint(wX0-wR,wY0-i);
		LCDDrawPoint(wX0+wR-1,wY0-i);
		LCDDrawPoint(wX0-i,wY0+wR-1);
		LCDDrawPoint(wX0+i-1,wY0+wR-1);
		LCDDrawPoint(wX0-i,wY0-wR);
		LCDDrawPoint(wX0+i-1,wY0-wR);
	}
}

void LCDImageOut(unsigned short wPosX,unsigned short wPosY,unsigned short wCX,unsigned short wCY,unsigned short* pData)
{
	unsigned int i;
	unsigned int j;
	unsigned int nIndex;
	unsigned int nCount;
	unsigned char LineStyle;
	unsigned short wLength;
	nIndex = 0;
	nCount = (wCY+7)/8;
	for(i=0;i<wCX;i++)
	{
		for(j=0;j<nCount;j++)
		{
			if(j==nCount-1&&wCY%8) wLength = wCY%8;
			else wLength = 8;
			if(nIndex%2==0) LineStyle = (*(pData+nIndex/2))&0xff;
			else LineStyle = (*(pData+nIndex/2))>>8;
			nIndex++;
			LCDVLine(wPosX+i,wPosY+j*8,wPosY+j*8+wLength,LineStyle);
		}
	}
}

void LCDTextOut(unsigned short wPosX,unsigned short wPosY,char* pszText)
{
	unsigned short wHZCode;
	while(*pszText)
	{
		if(*pszText>0&&*pszText<=7) wPosX += (*pszText+2)*6;
		else if(*pszText>=32&&*pszText<127)
		{
			if((wPosX+6)>LCD_CXDOT)
			{
				wPosX = 0;
				wPosY += 12;
			}
			LCDImageOut(wPosX,wPosY+2,6,8,(unsigned short*)c_wAscii6Bitmap[*pszText-32]);
		}
		else
		{
			if((wPosX+12)>LCD_CXDOT)
			{
				wPosX = 0;
				wPosY += 12;
			}
			wHZCode = (unsigned short)*pszText + (((unsigned short)*(pszText+1))<<8);
			if(LCDHZ1(wPosX,wPosY,wHZCode)==0) LCDHZ2(wPosX,wPosY,wHZCode);
			wPosX += 6;
			pszText++;
			if(*pszText==0) break;
		}
		wPosX += 6;
		pszText++;
	}
}

void LCDAsciiOut(unsigned short wPosX,unsigned short wPosY,char* pszText)
{
	unsigned int i;
	for(i=0;i<32;i++)
	{
		if(*pszText==0) break;
		if(*pszText>0&&*pszText<=7) wPosX += (*pszText+2)*6;
		else if(*pszText>=32&&*pszText<127)
		{
			LCDImageOut(wPosX,wPosY,6,8,(unsigned short*)c_wAscii6Bitmap[*pszText-32]);
			wPosX += 6;
		}
		pszText++;
		if(wPosX>=LCD_CXDOT) break;
	}
}

void LCDTimeOut(unsigned short wPosX,unsigned short wPosY,
				unsigned short wHour,unsigned short wMinute,
				unsigned short wSecond,unsigned short wMilliSecond)
{
	char* pText;
	pText = s_szTextBuffer;
	*pText++ = '0'+(char)(wHour/10);
	*pText++ = '0'+(char)(wHour%10);
	*pText++ = ':';
	*pText++ = '0'+(char)(wMinute/10);
	*pText++ = '0'+(char)(wMinute%10);
	*pText++ = ':';
	*pText++ = '0'+(char)(wSecond/10);
	*pText++ = '0'+(char)(wSecond%10);
	if(wMilliSecond!=0xffff)
	{
		*pText++ = '.';
		*pText++ = '0'+(char)(wMilliSecond/100);
		*pText++ = '0'+(char)(wMilliSecond%100/10);
		*pText++ = '0'+(char)(wMilliSecond%10);
	}
	*pText = 0;
	LCDAsciiOut(wPosX,wPosY,s_szTextBuffer);
}

void LCDDateOut(unsigned short wPosX,unsigned short wPosY,
				unsigned short wYear,unsigned short wMonth,unsigned short wDay)
{
	char* pText;
	pText = s_szTextBuffer;
	if(wYear!=0xffff)
	{
		*pText++ = '0'+(char)(wYear/10);
		*pText++ = '0'+(char)(wYear%10);
		*pText++ = '-';
	}
	*pText++ = '0'+(char)(wMonth/10);
	*pText++ = '0'+(char)(wMonth%10);
	*pText++ = '-';
	*pText++ = '0'+(char)(wDay/10);
	*pText++ = '0'+(char)(wDay%10);
	*pText = 0;
	LCDAsciiOut(wPosX,wPosY,s_szTextBuffer);
}

void LCDByteOut(unsigned short wPosX,unsigned short wPosY,unsigned short wData,unsigned short wFormat)
{
	char* pText;
	pText = s_szTextBuffer;
	wData &= 0xff;
	if(wFormat>=3) *pText++ = '0'+(char)(wData/100);
	if(wFormat>=2) *pText++ = '0'+(char)(wData%100/10);
	*pText++ = '0'+(char)(wData%10);
	*pText = 0;
	LCDAsciiOut(wPosX,wPosY,s_szTextBuffer);
}

void LCDWordOut(unsigned short wPosX,unsigned short wPosY,unsigned short wData)
{
	FormatReal(s_szTextBuffer,wData,0x50);
	LCDAsciiOut(wPosX,wPosY,s_szTextBuffer);
}

void LCDRealOut(unsigned short wPosX,unsigned short wPosY,unsigned long fData,unsigned short wFormat)
{
	FormatReal(s_szTextBuffer,fData,wFormat);
	LCDAsciiOut(wPosX,wPosY,s_szTextBuffer);
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
	case 8: if(dwData>99999999) dwData = 99999999; break;
	case 7: if(dwData>9999999) dwData = 9999999; break;
	case 6: if(dwData>999999) dwData = 999999; break;
	case 5: if(dwData>99999) dwData = 99999; break;
	case 4: if(dwData>9999) dwData = 9999; break;
	case 3: if(dwData>999) dwData = 999; break;
	case 2: if(dwData>99) dwData = 99; break;
	case 1: if(dwData>9) dwData = 9; break;
	default: return;
	}
	switch(wFormat>>4)
	{
	case 8: *pszTemp++ = '0'+(char)(dwData%100000000L/10000000L);
	case 7: *pszTemp++ = '0'+(char)(dwData%10000000L/1000000L);
	case 6: *pszTemp++ = '0'+(char)(dwData%1000000L/100000L);
	case 5: *pszTemp++ = '0'+(char)(dwData%100000L/10000L);
			if(wCountAfterDot==4) *pszTemp++ = '.';
	case 4: *pszTemp++ = '0'+(char)(dwData%10000L/1000L);
			if(wCountAfterDot==3) *pszTemp++ = '.';
	case 3: *pszTemp++ = '0'+(char)(dwData%1000L/100L);
			if(wCountAfterDot==2) *pszTemp++ = '.';
	case 2: *pszTemp++ = '0'+(char)(dwData%100L/10L);
			if(wCountAfterDot==1) *pszTemp++ = '.';
	case 1:	*pszTemp++ = '0'+(char)(dwData%10L);
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

void AutoLCDAsciiOut(char* pszText)
{
	LCDAsciiOut(g_wLCDX,g_wLCDY,pszText);
	g_wLCDY += g_wLCDYAuto;
}

void AutoLCDTextOut(char* pszText)
{
	LCDTextOut(g_wLCDX,g_wLCDY,pszText);
	g_wLCDY += g_wLCDYAuto;
}

void AutoLCDByteOut(unsigned short wData,unsigned short wFormat)
{
	LCDByteOut(g_wLCDX,g_wLCDY,wData,wFormat);
	g_wLCDY += g_wLCDYAuto;
}

void AutoLCDWordOut(unsigned short wData)
{
	LCDWordOut(g_wLCDX,g_wLCDY,wData);
	g_wLCDY += g_wLCDYAuto;
}

void AutoLCDRealOut(unsigned long fData,unsigned short wFormat)
{
	LCDRealOut(g_wLCDX,g_wLCDY,fData,wFormat);
	g_wLCDY += g_wLCDYAuto;
}

void AutoLCDOutERR_OK(unsigned short bERR)
{
//	AutoLCDAsciiOut(bERR?"ERR":" OK");
}

*/