#include <Main.h>

// #ifndef LCD_SetData
// #error "please define LCD_SetData"
// #endif

#ifdef _WIN32
#define LCD_DIRECT_0
#endif

#ifdef LCD_DIRECT_0
#define LCD_DIRECTH
#define LCD_SCANHLINE				(LCD_CXDOT)
#define LCD_SCANHBYTE				(LCD_CXDOT/8)
#define LCD_SCANVLINE				(LCD_CYDOT)
#endif
#ifdef LCD_DIRECT_90
#define LCD_DIRECTV
#define LCD_SCANHLINE				(LCD_CYDOT)
#define LCD_SCANHBYTE				(LCD_CYDOT/8)
#define LCD_SCANVLINE				(LCD_CXDOT)
#endif
#ifdef LCD_DIRECT_180
#define LCD_DIRECTH
#define LCD_SCANHLINE				(LCD_CXDOT)
#define LCD_SCANHBYTE				(LCD_CXDOT/8)
#define LCD_SCANVLINE				(LCD_CYDOT)
#endif
#ifdef LCD_DIRECT_270
#define LCD_DIRECTV
#define LCD_SCANHLINE				(LCD_CYDOT)
#define LCD_SCANHBYTE				(LCD_CYDOT/8)
#define LCD_SCANVLINE				(LCD_CXDOT)
#endif

WORD g_wLCDColor;
WORD g_wLCDColorBK;
BOOL g_bLCDSetDataXor;
BOOL g_bLCDLargeFont;
BOOL g_bLCDFormatRealFillBlank;
WORD g_wLCDTextAlignMode;
BOOL g_bLCDCursorON;
WORD g_wLCDCursorPosX;
WORD g_wLCDCursorPosY;
WORD g_wLCDCursorWidth;
WORD g_wLCDCursorHeight;
WORD g_wLCDAutoPosX;
WORD g_wLCDAutoPosY;
WORD g_wLCDAutoEnter;

const WORD c_wAscii6Bitmap[95][3]=
{
	{0x0000,0x0000,0x0000},// ;
	{0x6000,0x60fa,0x0000},//!;
	{0xc0e0,0xe000,0x00c0},//";
	{0x7e24,0x7e24,0x0024},//#;
	{0xd424,0x4856,0x0000},//$;
	{0xc8c6,0x2610,0x00c6},//%;
	{0x926c,0x046a,0x000a},//&;
	{0xe000,0x00c0,0x0000},//';
	{0x7c00,0x0082,0x0000},//(;
	{0x8200,0x007c,0x0000},//);
	{0x7c10,0x7c38,0x0010},//*;
	{0x1010,0x107c,0x0010},//+;
	{0x0700,0x0006,0x0000},//,;
	{0x1010,0x1010,0x0010},//-;
	{0x0600,0x0006,0x0000},//.;
	{0x0804,0x2010,0x0040},///;
	{0x8a7c,0xa282,0x007c},//0;
	{0x4200,0x02fe,0x0000},//1;
	{0x8a46,0x9292,0x0062},//2;
	{0x9244,0x9292,0x006c},//3;
	{0x2818,0xfe48,0x0008},//4;
	{0x92f4,0x9292,0x008c},//5;
	{0x523c,0x9292,0x000c},//6;
	{0x8e80,0xa090,0x00c0},//7;
	{0x926c,0x9292,0x006c},//8;
	{0x9260,0x9492,0x0078},//9;
	{0x3600,0x0036,0x0000},//:;
	{0x3700,0x0036,0x0000},//;;
	{0x2810,0x8244,0x0000},//<;
	{0x2424,0x2424,0x0024},//=;
	{0x8200,0x2844,0x0010},//>;
	{0x8040,0x909a,0x0060},//?;
	{0x827c,0xaaba,0x0078},//@;
	{0x887e,0x8888,0x007e},//A;
	{0x92fe,0x9292,0x006c},//B;
	{0x827c,0x8282,0x0044},//C;
	{0x82fe,0x8282,0x007c},//D;
	{0x92fe,0x9292,0x0082},//E;
	{0x90fe,0x9090,0x0080},//F;
	{0x827c,0x9292,0x005e},//G;
	{0x10fe,0x1010,0x00fe},//H;
	{0x8200,0x82fe,0x0000},//I;
	{0x020c,0x0202,0x00fc},//J;
	{0x10fe,0x4428,0x0082},//K;
	{0x02fe,0x0202,0x0002},//L;
	{0x40fe,0x4020,0x00fe},//M;
	{0x40fe,0x1020,0x00fe},//N;
	{0x827c,0x8282,0x007c},//O;
	{0x90fe,0x9090,0x0060},//P;
	{0x827c,0x848a,0x007a},//Q;
	{0x90fe,0x9890,0x0066},//R;
	{0x9264,0x9292,0x004c},//S;
	{0x8080,0x80fe,0x0080},//T;
	{0x02fc,0x0202,0x00fc},//U;
	{0x04f8,0x0402,0x00f8},//V;
	{0x02fc,0x023c,0x00fc},//W;
	{0x28c6,0x2810,0x00c6},//X;
	{0x10e0,0x100e,0x00e0},//Y;
	{0x928e,0xc2a2,0x0000},//Z;
	{0xfe00,0x8282,0x0000},//[;
	{0x2040,0x0810,0x0004},//\;
	{0x8200,0xfe82,0x0000},//];
	{0x9060,0x6090,0x0000},//^;
	{0x0101,0x0101,0x0101},//_;
	{0xc000,0x00e0,0x0000},//`;
	{0x2a04,0x2a2a,0x001e},//a;
	{0x22fe,0x2222,0x001c},//b;
	{0x221c,0x2222,0x0014},//c;
	{0x221c,0x2222,0x00fe},//d;
	{0x2a1c,0x2a2a,0x0010},//e;
	{0x7e10,0x9090,0x0000},//f;
	{0x2518,0x2525,0x003e},//g;
	{0x20fe,0x1e20,0x0000},//h;
	{0x0000,0x02be,0x0000},//i;
	{0x0102,0xbe21,0x0000},//j;
	{0x08fe,0x2214,0x0000},//k;
	{0x0000,0x02fe,0x0000},//l;
	{0x203e,0x2018,0x001e},//m;
	{0x203e,0x1e20,0x0000},//n;
	{0x221c,0x2222,0x001c},//o;
	{0x223f,0x2222,0x001c},//p;
	{0x221c,0x2222,0x003f},//q;
	{0x1e22,0x2022,0x0010},//r;
	{0x2a10,0x2a2a,0x0004},//s;
	{0x7c20,0x2422,0x0000},//t;
	{0x023c,0x3e04,0x0000},//u;
	{0x0438,0x0402,0x0038},//v;
	{0x063c,0x060c,0x003c},//w;
	{0x0836,0x3608,0x0000},//x;
	{0x0539,0x3c06,0x0000},//y;
	{0x2a26,0x322a,0x0000},//z;
	{0x7c10,0x8282,0x0000},//{;
	{0x0000,0x00ee,0x0000},//|;
	{0x8200,0x7c82,0x0010},//};
	{0x8040,0x8040,0x0000} //~;
};

/*const WORD c_wAscii8Bitmap[95][8]=
{
	{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},// ;
	{0x0000,0x000e,0xb01f,0xb01f,0x000e,0x0000,0x0000,0x0000},//!;
	{0x001c,0x001c,0x0000,0x0000,0x001c,0x001c,0x0000,0x0000},//";
	{0x4004,0xf01f,0xf01f,0x4004,0xf01f,0xf01f,0x4004,0x0000},//#;
	{0x200c,0x301e,0x1c73,0x9c71,0xf018,0x6008,0x0000,0x0000},//$;
	{0x0018,0x603c,0xc024,0xb03d,0x781b,0x4806,0x780c,0x3000},//%;
	{0xe00d,0xf01f,0x1012,0x901e,0xe00c,0xf000,0x9000,0x0000},//&;
	{0x0000,0x0000,0x001c,0x001c,0x0000,0x0000,0x0000,0x0000},//';
	{0x0000,0xe003,0xf80f,0x1c1c,0x0410,0x0000,0x0000,0x0000},//(;
	{0x0000,0x0410,0x1c1c,0xf80f,0xe003,0x0000,0x0000,0x0000},//);
	{0x0001,0x4005,0xc007,0x8003,0xc007,0x4005,0x0001,0x0000},;
	{0x0001,0x0001,0xc007,0xc007,0x0001,0x0001,0x0000,0x0000},//+;
	{0x0000,0x0000,0x3400,0x3c00,0x3800,0x0000,0x0000,0x0000},//,;
	{0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0000,0x0000},//-;
	{0x0000,0x0000,0x3000,0x3000,0x3000,0x0000,0x0000,0x0000},//.;
	{0x1800,0x7800,0xe001,0x8007,0x001e,0x0018,0x0000,0x0000},///;
	{0xe00f,0xf01f,0xd010,0x1016,0xf01f,0xe00f,0x0000,0x0000},//0;
	{0x0004,0x0004,0x000c,0xf01f,0xf01f,0x0000,0x0000,0x0000},//1;
	{0x300c,0x701c,0xd010,0x9011,0x101f,0x100e,0x0000,0x0000},//2;
	{0x600c,0x701c,0x1011,0x1011,0xf01f,0xe00e,0x0000,0x0000},//3;
	{0xc000,0xc01f,0x401f,0x4000,0xf007,0xf007,0x4000,0x0000},//4;
	{0x101f,0x101f,0x1011,0x3011,0xe011,0xc010,0x0000,0x0000},//5;
	{0xe003,0xf007,0x101e,0x101a,0xf013,0xe001,0x0000,0x0000},//6;
	{0x0010,0x7010,0xf011,0x8017,0x001e,0x0018,0x0000,0x0000},//7;
	{0xe00e,0xf01f,0x1013,0x9011,0xf01f,0xe00e,0x0000,0x0000},//8;
	{0x000f,0x901f,0xb010,0xf010,0xc01f,0x800f,0x0000,0x0000},//9;
	{0x0000,0x0000,0x3006,0x3006,0x3006,0x0000,0x0000,0x0000},//:;
	{0x0000,0x0000,0x3406,0x3c06,0x3806,0x0000,0x0000,0x0000},//;;
	{0x0001,0x8003,0xc006,0x600c,0x3018,0x1010,0x0000,0x0000},//<;
	{0x8002,0x8002,0x8002,0x8002,0x8002,0x8002,0x0000,0x0000},//=;
	{0x1010,0x3018,0x600c,0xc006,0x8003,0x0001,0x0000,0x0000},//>;
	{0x000c,0x001c,0xb011,0xb013,0x001e,0x000c,0x0000,0x0000},//?;
	{0xf01f,0x1010,0x9011,0xd013,0x5012,0xd01f,0xd00f,0x0000},//@;
	{0xf007,0xf00f,0x8018,0x8018,0xf00f,0xf007,0x0000,0x0000},//A;
	{0xf01f,0xf01f,0x1011,0x1011,0xf01f,0xe00e,0x0000,0x0000},//B;
	{0xe00f,0xf01f,0x1010,0x1010,0x701c,0x600c,0x0000,0x0000},//C;
	{0xf01f,0xf01f,0x1010,0x3018,0xe00f,0xc007,0x0000,0x0000},//D;
	{0xf01f,0xf01f,0x1011,0x1011,0x1011,0x1010,0x0000,0x0000},//E;
	{0xf01f,0xf01f,0x0011,0x0011,0x0011,0x0010,0x0000,0x0000},//F;
	{0xe00f,0xf01f,0x1010,0x9010,0xf01c,0xf00c,0x0000,0x0000},//G;
	{0xf01f,0xf01f,0x0001,0x0001,0xf01f,0xf01f,0x0000,0x0000},//H;
	{0x0000,0x1010,0xf01f,0xf01f,0x1010,0x0000,0x0000,0x0000},//I;
	{0x6000,0x7000,0x1000,0x1000,0xf01f,0xe01f,0x0000,0x0000},//J;
	{0xf01f,0xf01f,0x0001,0xc007,0xf01e,0x3018,0x0000,0x0000},//K;
	{0xf01f,0xf01f,0x1000,0x1000,0x1000,0x1000,0x0000,0x0000},//L;
	{0xf01f,0xf01f,0x0004,0x8003,0x0004,0xf01f,0xf01f,0x0000},//M;
	{0xf01f,0xf01f,0x0006,0x0003,0x8001,0xf01f,0xf01f,0x0000},//N;
	{0xe00f,0xf01f,0x1010,0x1010,0xf01f,0xe00f,0x0000,0x0000},//O;
	{0xf01f,0xf01f,0x0011,0x0011,0x001f,0x000e,0x0000,0x0000},//P;
	{0xe00f,0xf01f,0x1010,0x1810,0xfc1f,0xe40f,0x0000,0x0000},//Q;
	{0xf01f,0xf01f,0x0011,0x8011,0xf01f,0x700e,0x0000,0x0000},//R;
	{0x200c,0x301e,0x1013,0x9011,0xf018,0x6008,0x0000,0x0000},//S;
	{0x0010,0x0010,0xf01f,0xf01f,0x0010,0x0010,0x0000,0x0000},//T;
	{0xe01f,0xf01f,0x1000,0x1000,0xf01f,0xe01f,0x0000,0x0000},//U;
	{0xc01f,0xe01f,0x3000,0x3000,0xe01f,0xc01f,0x0000,0x0000},//V;
	{0x801f,0xf01f,0x7000,0x8003,0x7000,0xf01f,0x801f,0x0000},//W;
	{0x7018,0xf01c,0x0007,0x8003,0xf01c,0x7018,0x0000,0x0000},//X;
	{0x001e,0x001f,0xf001,0xf001,0x001f,0x001e,0x0000,0x0000},//Y;
	{0x7010,0xf010,0x9011,0x1013,0x101e,0x101c,0x0000,0x0000},//Z;
	{0x0000,0xff1f,0xff1f,0x0310,0x0310,0x0000,0x0000,0x0000},//[;
	{0x0018,0x001e,0x8007,0xe001,0x7800,0x1800,0x0000,0x0000},//\;
	{0x0000,0x0310,0x0310,0xff1f,0xff1f,0x0000,0x0000,0x0000},//];
	{0x0018,0x0024,0x0024,0x0018,0x0000,0x0000,0x0000,0x0000},//^;
	{0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0000},//_;
	{0x0000,0x0040,0x0060,0x0070,0x0010,0x0000,0x0000,0x0000},//`;
	{0x6000,0xf004,0x9004,0x9004,0xf007,0xf003,0x0000,0x0000},//a;
	{0xf01f,0xf01f,0x1004,0x1004,0xf007,0xe003,0x0000,0x0000},//b;
	{0xe003,0xf007,0x1004,0x1004,0x3006,0x2002,0x0000,0x0000},//c;
	{0xe003,0xf007,0x1004,0x1004,0xf01f,0xf01f,0x0000,0x0000},//d;
	{0xe003,0xf007,0x9004,0x9004,0x9007,0x8003,0x0000,0x0000},//e;
	{0x0001,0xf00f,0xf01f,0x0011,0x0011,0x0011,0x0000,0x0000},//f;
	{0xe303,0xf307,0x1304,0x1304,0xff07,0xfc07,0x0000,0x0000},//g;
	{0xf01f,0xf01f,0x0004,0x0004,0xf007,0xf003,0x0000,0x0000},//h;
	{0x1004,0x1004,0xf037,0xf037,0x1000,0x1000,0x0000,0x0000},//i;
	{0x0300,0x0304,0x0304,0xff37,0xfc37,0x0000,0x0000,0x0000},//j;
	{0xf01f,0xf01f,0x8000,0xc001,0x7007,0x3006,0x0000,0x0000},//k;
	{0x1010,0x1010,0xf01f,0xf01f,0x1000,0x1000,0x0000,0x0000},//l;
	{0xf007,0xf007,0x0004,0xe007,0x0004,0xf007,0xf003,0x0000},//m;
	{0xf007,0xf007,0x0004,0x0004,0xf007,0xf003,0x0000,0x0000},//n;
	{0xe003,0xf007,0x1004,0x1004,0xf007,0xe003,0x0000,0x0000},//o;
	{0xff07,0xff07,0x1004,0x1004,0xf007,0xe003,0x0000,0x0000},//p;
	{0xe003,0xf007,0x1004,0x1004,0xff07,0xff07,0x0000,0x0000},//q;
	{0xf007,0xf007,0x0001,0x0002,0x0006,0x0006,0x0000,0x0000},//r;
	{0x1003,0x9007,0x9004,0x9004,0xf004,0x6004,0x0000,0x0000},//s;
	{0x0004,0xe01f,0xf01f,0x1004,0x1004,0x1004,0x0000,0x0000},//t;
	{0xe007,0xf007,0x1000,0x1000,0xf007,0xf007,0x0000,0x0000},//u;
	{0xc007,0xe007,0x3000,0x3000,0xe007,0xc007,0x0000,0x0000},//v;
	{0xc007,0xf007,0x3000,0xc003,0x3000,0xf007,0xc007,0x0000},//w;
	{0x3006,0x7007,0xc001,0xc001,0x7007,0x3006,0x0000,0x0000},//x;
	{0xe307,0xf307,0x1700,0x1c00,0xf807,0xe007,0x0000,0x0000},//y;
	{0x3004,0x7004,0xd004,0x9005,0x1007,0x1006,0x0000,0x0000},//z;
	{0x8000,0xc001,0x780f,0x3c1e,0x0410,0x0000,0x0000,0x0000},//{;
	{0x0000,0x0000,0xff1f,0xff1f,0x0000,0x0000,0x0000,0x0000},//|;
	{0x0000,0x0410,0x3c1e,0x780f,0xc001,0x8000,0x0000,0x0000},//};
	{0x0018,0x0010,0x0018,0x000c,0x0004,0x000c,0x0018,0x0000} //~;
};*/

extern void GetHZ12x12Bitmap(WORD wNeiMa,WORD* pHZBitmap);
extern void GetHZ16x16Bitmap(WORD wNeiMa,WORD* pHZBitmap);

//-----------------------------------------------------------------------------
void LCD_DrawCursor(void)
{
	WORD i;
#ifdef LCD_DIRECTH
	for(i=0;i<g_wLCDCursorHeight;i++)
	{
		LCD_DrawHLine(g_wLCDCursorPosY+i,g_wLCDCursorPosX,g_wLCDCursorPosX+g_wLCDCursorWidth);
	}
#endif
#ifdef LCD_DIRECTV
	for(i=0;i<g_wLCDCursorWidth;i++)
	{
		LCD_DrawVLine(g_wLCDCursorPosX+i,g_wLCDCursorPosY,g_wLCDCursorPosY+g_wLCDCursorHeight);
	}
#endif
}

BYTE LCD_ReverseLineStyle(BYTE LineStyle)
{
	BYTE LineStyleNew;
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

void LCD_OnInitA(void)
{
	g_wLCDColor = COLOR_WHITE;
	g_wLCDColorBK = COLOR_BLACK;
	g_bLCDSetDataXor = FALSE;
	g_bLCDLargeFont = FALSE;
	g_bLCDFormatRealFillBlank = TRUE;
	g_wLCDTextAlignMode = TAMODE_LEFT;
	g_wLCDAutoPosX = 0;
	g_wLCDAutoPosY = 0;
	g_wLCDAutoEnter = 12;
	g_bLCDCursorON = FALSE;
	g_wLCDCursorPosX = 0;
	g_wLCDCursorPosY = 0;
	g_wLCDCursorWidth = LCD_CXDOT;
	g_wLCDCursorHeight = 13;
// 	g_lcd.iiiSetup();
// 	g_lcd.iiiClear();
// 	g_lcd.iiiOpen();
	LCD_Setup();
	LCD_Clear();
	LCD_Open();
}

void LCD_SetColor(WORD wColor)
{
	g_wLCDColor = wColor;
}

void LCD_SetColorBK(WORD wColorBK)
{
	g_wLCDColorBK = wColorBK;
}

WORD LCD_GetFontWidth(void)
{
	return (g_bLCDLargeFont)?8:6;
}

WORD LCD_GetFontHeight(void)
{
	return (g_bLCDLargeFont)?16:8;
}

void LCD_CursorON(void)
{
	if(g_bLCDCursorON==FALSE)
	{
		g_bLCDCursorON = TRUE;
		g_bLCDSetDataXor = TRUE;
		LCD_DrawCursor();
		g_bLCDSetDataXor = FALSE;
	}
}

void LCD_CursorOFF(void)
{
	if(g_bLCDCursorON==TRUE)
	{
		g_bLCDCursorON = FALSE;
		g_bLCDSetDataXor = TRUE;
		LCD_DrawCursor();
		g_bLCDSetDataXor = FALSE;
	}
}

void LCD_EraseCursor(void)
{
	WORD wColor;
	wColor = g_wLCDColor;
	g_wLCDColor = g_wLCDColorBK;
	LCD_DrawCursor();
	g_wLCDColor = wColor;
}

void LCD_SetCursorPosX(WORD wCursorPosX,WORD wCursorWidth)
{
	g_wLCDCursorPosX = wCursorPosX;
	g_wLCDCursorWidth = wCursorWidth;
}

void LCD_SetCursorPosY(WORD wCursorPosY,WORD wCursorHeight)
{
	g_wLCDCursorPosY = wCursorPosY;
	g_wLCDCursorHeight = wCursorHeight;
}

void LCD_SetTextAlignMode(WORD wTextAlignMode)
{
	g_wLCDTextAlignMode = wTextAlignMode;
}

void LCD_SetSmallFont(void)
{
	g_bLCDLargeFont = FALSE;
}

void LCD_SetLargeFont(void)
{
	g_bLCDLargeFont = TRUE;
}

void LCD_DrawPoint(WORD wPosX,WORD wPosY)
{
	WORD wAddress;
	BYTE DataAndMask;

	if(wPosX>=LCD_CXDOT) return;
	if(wPosY>=LCD_CYDOT) return;
#ifdef LCD_DIRECT_90
	wPosY = LCD_SCANHLINE-1-wPosY;
#endif
#ifdef LCD_DIRECT_180
	wPosX = LCD_SCANHLINE-1-wPosX;
	wPosY = LCD_SCANVLINE-1-wPosY;
#endif
#ifdef LCD_DIRECT_270
	wPosX = LCD_SCANVLINE-1-wPosX;
#endif
#ifdef LCD_DIRECTH
	wAddress = LCD_SCANHBYTE*wPosY+(wPosX>>3);
	DataAndMask = 0x80>>(wPosX%8);
#endif
#ifdef LCD_DIRECTV
	wAddress = LCD_SCANHBYTE*wPosX+(wPosY>>3);
	DataAndMask = 0x80>>(wPosY%8);
#endif
	LCD_SetData(wAddress,DataAndMask,DataAndMask);
}

void LCD_DrawHLineExt(WORD wPosY,WORD wPosX1,WORD wPosX2,BYTE LineStyle)
{
	WORD wSetX1;
	WORD wSetX2;
	WORD wAddress,i;
	BYTE Mask1,Mask2;

	if(wPosX1>=32768) wPosX1 = 0;
	if(wPosX2>=32768) wPosX2 = 0;
	if(wPosX1==wPosX2) return;
	if(wPosX1>wPosX2)
	{
		wSetX1 = wPosX1;
		wSetX2 = wPosX2;
		wPosX1 = wSetX2;
		wPosX2 = wSetX1;
	}
	if(wPosX1>=LCD_CXDOT) return;
	if(wPosX2>=LCD_CXDOT) wPosX2 = LCD_CXDOT;
	if(wPosY>=LCD_CYDOT) return;
#ifdef LCD_DIRECT_0
	LineStyle = ((LineStyle<<8)|LineStyle)>>(wPosX1%8);
#endif
#ifdef LCD_DIRECT_180
	wPosY = LCD_SCANVLINE-1-wPosY;
	wSetX1 = wPosX1;
	wSetX2 = wPosX2;
	wPosX1 = LCD_SCANHLINE-wSetX2;
	wPosX2 = LCD_SCANHLINE-wSetX1;
	LineStyle = LCD_ReverseLineStyle(LineStyle);
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
		LCD_SetData(wAddress,LineStyle,Mask1&Mask2);
		wAddress++;
	}
#endif
#ifdef LCD_DIRECT_90
	wPosY = LCD_SCANHLINE-1-wPosY;
	wAddress = LCD_SCANHBYTE*wPosX1+(wPosY>>3);
	Mask2 = 0x80>>(wPosY%8);
	for(i=0;i<wPosX2-wPosX1;i++)
	{
		Mask1 = (LineStyle&(0x80>>(i%8)))?Mask2:0x00;
		LCD_SetData(wAddress,Mask1,Mask2);
		wAddress += LCD_SCANHBYTE;
	}
#endif
#ifdef LCD_DIRECT_270
	wPosX1 = LCD_SCANVLINE-1-wPosX1;
	wPosX2 = LCD_SCANVLINE-1-wPosX2;
	wAddress = LCD_SCANHBYTE*wPosX1+(wPosY>>3);
	Mask2 = 0x80>>(wPosY%8);
	for(i=0;i<wPosX1-wPosX2;i++)
	{
		Mask1 = (LineStyle&(0x80>>(i%8)))?Mask2:0x00;
		LCD_SetData(wAddress,Mask1,Mask2);
		wAddress -= LCD_SCANHBYTE;
	}
#endif
}

void LCD_DrawVLineExt(WORD wPosX,WORD wPosY1,WORD wPosY2,BYTE LineStyle)
{
	WORD wSetY1;
	WORD wSetY2;
	WORD wAddress,i;
	BYTE Mask1,Mask2;

	if(wPosY1>=32768) wPosY1 = 0;
	if(wPosY2>=32768) wPosY2 = 0;
	if(wPosY1==wPosY2) return;
	if(wPosY1>wPosY2)
	{
		wSetY1 = wPosY1;
		wSetY2 = wPosY2;
		wPosY1 = wSetY2;
		wPosY2 = wSetY1;
	}
	if(wPosY1>=LCD_CYDOT) return;
	if(wPosY2>=LCD_CYDOT) wPosY2 = LCD_CYDOT;
	if(wPosX>=LCD_CXDOT) return;
#ifdef LCD_DIRECT_0
	wAddress = LCD_SCANHBYTE*wPosY1+(wPosX>>3);
	Mask2 = 0x80>>(wPosX%8);
	for(i=0;i<wPosY2-wPosY1;i++)
	{
		Mask1 = (LineStyle&(0x80>>(i%8)))?Mask2:0x00;
		LCD_SetData(wAddress,Mask1,Mask2);
		wAddress += LCD_SCANHBYTE;
	}
#endif
#ifdef LCD_DIRECT_180
	wPosX = LCD_SCANHLINE-1-wPosX;
	wPosY1 = LCD_SCANVLINE-wPosY1;
	wPosY2 = LCD_SCANVLINE-wPosY2;
	wAddress = LCD_SCANHBYTE*wPosY1+(wPosX>>3);
	Mask2 = 0x80>>(wPosX%8);
	for(i=0;i<wPosY1-wPosY2;i++)
	{
		Mask1 = (LineStyle&(0x80>>(i%8)))?Mask2:0x00;
		LCD_SetData(wAddress,Mask1,Mask2);
		wAddress -= LCD_SCANHBYTE;
	}
#endif
#ifdef LCD_DIRECT_90
	wSetY1 = wPosY1;
	wSetY2 = wPosY2;
	wPosY1 = LCD_SCANHLINE-wSetY2;
	wPosY2 = LCD_SCANHLINE-wSetY1;
	LineStyle = LCD_ReverseLineStyle(LineStyle);
	LineStyle = ((LineStyle<<8)|LineStyle)>>(wPosY2%8);
#endif
#ifdef LCD_DIRECT_270
	wPosX = LCD_SCANVLINE-1-wPosX;
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
		LCD_SetData(wAddress,LineStyle,Mask1&Mask2);
		wAddress++;
	}
#endif
}

void LCD_ClearBlock(WORD wPosX1,WORD wPosY1,WORD wPosX2,WORD wPosY2)
{
    WORD wTemp,i;
#ifdef LCD_DIRECTH
    if(wPosY1>wPosY2)
    {
        wTemp = wPosY1;
        wPosY1 = wPosY2;
        wPosY2 = wTemp;
    }
    for(i=wPosY1;i<=wPosY2;i++) LCD_DrawHLineExt(i,wPosX1,wPosX2+1,0x00);
#endif

#ifdef LCD_DIRECTV
    if(wPosX1>wPosX2)
    {
        wTemp = wPosX1;
        wPosX1 = wPosX2;
        wPosX2 = wTemp;
    }
    for(i=wPosX1;i<=wPosX2;i++) LCD_DrawVLineExt(i,wPosY1,wPosY2+1,0x00);
#endif
}


void LCD_DrawHLine(WORD wPosY,WORD wPosX1,WORD wPosX2)
{
	LCD_DrawHLineExt(wPosY,wPosX1,wPosX2,0xff);
}

void LCD_DrawVLine(WORD wPosX,WORD wPosY1,WORD wPosY2)
{
	LCD_DrawVLineExt(wPosX,wPosY1,wPosY2,0xff);
}

void LCD_DrawXLine(short nPosX1,short nPosY1,short nPosX2,short nPosY2)
{
	short dx,dy,dm,dn;
	short m,n,u,v,l,sum;
	dx = nPosX2 - nPosX1;
	dy = nPosY2 - nPosY1;
	dm = 1;
	dn = 1;
	if(dx<0){ dx = -dx; dm = -1; }
	if(dy<0){ dy = -dy; dn = -1; }
	if(dx<dy)
	{
		m = dy;
		n = dx;
		u = dm;
		dm = dn;
		dn = u;
		u = nPosY1;
		v = nPosX1;
	}
	else
	{
		m = dx;
		n = dy;
		u = nPosX1;
		v = nPosY1;
	}
	l = 0;
	sum = m;
	while(sum>0)
	{
		if(dx<dy) LCD_DrawPoint((WORD)v,(WORD)u);
		else LCD_DrawPoint((WORD)u,(WORD)v);
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

void LCD_DrawRect(WORD wPosX1,WORD wPosY1,WORD wPosX2,WORD wPosY2)
{
	LCD_DrawHLine(wPosY1,wPosX1,wPosX2);
	LCD_DrawHLine(wPosY2,wPosX1,wPosX2);
	LCD_DrawVLine(wPosX1,wPosY1,wPosY2);
	LCD_DrawVLine(wPosX2,wPosY1,wPosY2+1);
}

void LCD_DrawBlock(WORD wPosX1,WORD wPosY1,WORD wPosX2,WORD wPosY2)
{
	WORD wTemp,i;

#ifdef LCD_DIRECTH
	if(wPosY1>wPosY2)
	{
		wTemp = wPosY1;
		wPosY1 = wPosY2;
		wPosY2 = wTemp;
	}
	for(i=wPosY1;i<=wPosY2;i++) LCD_DrawHLine(i,wPosX1,wPosX2+1);
#endif
#ifdef LCD_DIRECTV
	if(wPosX1>wPosX2)
	{
		wTemp = wPosX1;
		wPosX1 = wPosX2;
		wPosX2 = wTemp;
	}
	for(i=wPosX1;i<=wPosX2;i++) LCD_DrawVLine(i,wPosY1,wPosY2+1);
#endif
}

void LCD_DrawCircle(WORD wPosX0,WORD wPosY0,WORD wR)
{
	WORD wDotNum,wR2,i;

	if(wR>120) return;
	wDotNum = (wR*7+5)/10+1;
	wR2 = wR*wR+wR;
	for(i=0;i<wDotNum;i++)
	{
		if((wR*wR+i*i)>wR2) wR--;
		LCD_DrawPoint(wPosX0-wR,wPosY0+i-1);
		LCD_DrawPoint(wPosX0+wR-1,wPosY0+i-1);
		LCD_DrawPoint(wPosX0-wR,wPosY0-i);
		LCD_DrawPoint(wPosX0+wR-1,wPosY0-i);
		LCD_DrawPoint(wPosX0-i,wPosY0+wR-1);
		LCD_DrawPoint(wPosX0+i-1,wPosY0+wR-1);
		LCD_DrawPoint(wPosX0-i,wPosY0-wR);
		LCD_DrawPoint(wPosX0+i-1,wPosY0-wR);
	}
}

void LCD_ImageOut(WORD wPosX,WORD wPosY,WORD wCX,WORD wCY,WORD* pData)
{
	WORD wIndex,wCount;
	WORD i,j;
	BYTE LineStyle;
	WORD wLength;

	wIndex = 0;
	wCount = (wCY+7)/8;
	for(i=0;i<wCX;i++)
	{
		for(j=0;j<wCount;j++)
		{
			if(j==wCount-1&&wCY%8) wLength = wCY%8;
			else wLength = 8;
			if(wIndex%2==0) LineStyle = (*(pData+wIndex/2))&0xff;
			else LineStyle = (*(pData+wIndex/2))>>8;
			wIndex++;
			LCD_DrawVLineExt(wPosX+i,wPosY+j*8,wPosY+j*8+wLength,LineStyle);
		}
	}
}

WORD LCD_GetStringWidth(char* pszText)
{
	WORD wWidth,i;

	wWidth = 0;
	for(i=0;i<256;i++)
	{
		if(*pszText==0) break;
		else if(*pszText==1) wWidth += (g_bLCDLargeFont)?4:3;
		else if(*pszText>1&&*pszText<8) wWidth += *pszText*((g_bLCDLargeFont)?8:6);
		else if(*pszText>=32&&*pszText<127) wWidth += (g_bLCDLargeFont)?8:6;
		else
		{
			wWidth += (g_bLCDLargeFont)?16:12;
			pszText++;
			if(*pszText==0) break;
			i++;
		}
		pszText++;
	}
	return wWidth;
}

void LCD_TextOut(WORD wPosX,WORD wPosY,char* pszText)
{
	WORD wWidth,i;
	WORD wPosXOld;
	WORD wHZBitmap[16];
	WORD wNeiMa;

	if(g_wLCDTextAlignMode==TAMODE_CENTER)
	{
		wWidth = LCD_GetStringWidth(pszText);
		wWidth /= 2;
		if(wPosX>=wWidth) wPosX -= wWidth;
		else wPosX = 0;
	}
	else if(g_wLCDTextAlignMode==TAMODE_RIGHT)
	{
		wWidth = LCD_GetStringWidth(pszText);
		if(wPosX>=wWidth) wPosX -= wWidth;
		else wPosX = 0;
	}
	wPosXOld = wPosX;
	MemoryClear(wHZBitmap,16);
	for(i=0;i<256;i++)
	{
		if(*pszText==0) break;
		else if(*pszText==1) wPosX += (g_bLCDLargeFont)?4:3;
		else if(*pszText>1&&*pszText<8) wPosX += *pszText*((g_bLCDLargeFont)?8:6);
		else if(*pszText>=32&&*pszText<127)
		{
// 			if(g_bLCDLargeFont)
// 			{
// 				if((wPosX+7)>LCD_CXDOT)
// 				{
// 					wPosX = wPosXOld;
// 					wPosY += 16;
// 				}
// 				LCD_ImageOut(wPosX,wPosY,8,16,(WORD*)c_wAscii8Bitmap[*pszText-32]);
// 				wPosX += 8;
// 			}
// 			else
			{
				if((wPosX+5)>LCD_CXDOT)
				{
					wPosX = wPosXOld;
					wPosY += 12;
				}
				LCD_ImageOut(wPosX,wPosY+2,6,8,(WORD*)c_wAscii6Bitmap[*pszText-32]);
				wPosX += 6;
			}
		}
		else
		{
			wNeiMa = (WORD)(BYTE)*pszText+((WORD)(BYTE)*(pszText+1)<<8);
			if(g_bLCDLargeFont)
			{
				if((wPosX+15)>LCD_CXDOT)
				{
					wPosX = wPosXOld;
					wPosY += 16;
				}
				GetHZ16x16Bitmap(wNeiMa,&wHZBitmap[0]);
				LCD_ImageOut(wPosX,wPosY,16,16,&wHZBitmap[0]);
				wPosX += 16;
			}
			else
			{
				if((wPosX+11)>LCD_CXDOT)
				{
					wPosX = wPosXOld;
					wPosY += 12;
				}
				GetHZ12x12Bitmap(wNeiMa,&wHZBitmap[0]);
				LCD_ImageOut(wPosX,wPosY,12,12,&wHZBitmap[0]);
				wPosX += 12;
			}
			pszText++;
			if(*pszText==0) break;
			i++;
		}
		pszText++;
	}
}

void LCD_TextOutW(WORD wPosX,WORD wPosY,WORD* pwszText)
{
#ifdef _WIN32
	char szText[256];
	char* pszTemp = szText;
	while(*pwszText) *pszTemp++ = (char)(short)*pwszText++;
	*pszTemp= 0;
	LCD_TextOut(wPosX,wPosY,szText);
#else
	LCD_TextOut(wPosX,wPosY,(char*)pwszText);
#endif
}

void LCD_AsciiOut(WORD wPosX,WORD wPosY,char* pszText)
{
	WORD wWidth,i;

	if(g_wLCDTextAlignMode==TAMODE_CENTER)
	{
		wWidth = LCD_GetStringWidth(pszText);
		wWidth /= 2;
		if(wPosX>=wWidth) wPosX -= wWidth;
		else wPosX = 0;
	}
	else if(g_wLCDTextAlignMode==TAMODE_RIGHT)
	{
		wWidth = LCD_GetStringWidth(pszText);
		if(wPosX>=wWidth) wPosX -= wWidth;
		else wPosX = 0;
	}
	for(i=0;i<256;i++)
	{
		if(*pszText==0) break;
		else if(*pszText==1) wPosX += (g_bLCDLargeFont)?4:3;
		else if(*pszText>1&&*pszText<8) wPosX += *pszText*((g_bLCDLargeFont)?8:6);
		else if(*pszText>=32&&*pszText<127)
		{
// 			if(g_bLCDLargeFont)
// 			{
// 				LCD_ImageOut(wPosX,wPosY,8,16,(WORD*)c_wAscii8Bitmap[*pszText-32]);
// 				wPosX += 8;
// 			}
// 			else
			{
				LCD_ImageOut(wPosX,wPosY,6,8,(WORD*)c_wAscii6Bitmap[*pszText-32]);
				wPosX += 6;
			}
		}
		pszText++;
		if(wPosX>=LCD_CXDOT) break;
	}
}

void LCD_AsciiOutW(WORD wPosX,WORD wPosY,WORD* pwszText)
{
#ifdef _WIN32
	char szText[256];
	char* pszTemp = szText;
	while(*pwszText) *pszTemp++ = (char)(short)*pwszText++;
	*pszTemp= 0;
	LCD_AsciiOut(wPosX,wPosY,szText);
#else
	char szText[17];
	char* pszTemp = szText;
	while(*pwszText) *pszTemp++ = (char)(short)*pwszText++;
	*pszTemp= 0;
	LCD_AsciiOut(wPosX,wPosY,szText);
//	LCD_AsciiOut(wPosX,wPosY,(char*)pwszText);
#endif
}

void LCD_TimeOut(WORD wPosX,WORD wPosY,WORD wHour,WORD wMinute,WORD wSecond,WORD wMilliSecond)
{
	char szTextBuffer[16];
	char* pszText;
	pszText = szTextBuffer;
	*pszText++ = '0'+(char)(wHour/10);
	*pszText++ = '0'+(char)(wHour%10);
	*pszText++ = ':';
	*pszText++ = '0'+(char)(wMinute/10);
	*pszText++ = '0'+(char)(wMinute%10);
	*pszText++ = ':';
	*pszText++ = '0'+(char)(wSecond/10);
	*pszText++ = '0'+(char)(wSecond%10);
	if(wMilliSecond!=0xffff)
	{
		*pszText++ = '.';
		*pszText++ = '0'+(char)(wMilliSecond/100);
		*pszText++ = '0'+(char)(wMilliSecond%100/10);
		*pszText++ = '0'+(char)(wMilliSecond%10);
	}
	*pszText = 0;
	LCD_AsciiOut(wPosX,wPosY,szTextBuffer);
}

void LCD_DateOut(WORD wPosX,WORD wPosY,WORD wYear,WORD wMonth,WORD wDay)
{
	char szTextBuffer[16];
	char* pszText;
	pszText = szTextBuffer;
	if(wYear!=0xffff)
	{
		*pszText++ = '0'+(char)(wYear/10);
		*pszText++ = '0'+(char)(wYear%10);
		*pszText++ = '-';
	}
	*pszText++ = '0'+(char)(wMonth/10);
	*pszText++ = '0'+(char)(wMonth%10);
	*pszText++ = '-';
	*pszText++ = '0'+(char)(wDay/10);
	*pszText++ = '0'+(char)(wDay%10);
	*pszText = 0;
	LCD_AsciiOut(wPosX,wPosY,szTextBuffer);
}

void LCD_ByteOut(WORD wPosX,WORD wPosY,BYTE Data,WORD wFormat)
{
	char szTextBuffer[16];
	char* pszText;
	pszText = szTextBuffer;
	Data &= 0xff;
	if(wFormat>=3) *pszText++ = '0'+(char)(Data/100);
	if(wFormat>=2) *pszText++ = '0'+(char)(Data%100/10);
	*pszText++ = '0'+(char)(Data%10);
	*pszText = 0;
	LCD_AsciiOut(wPosX,wPosY,szTextBuffer);
}

void LCD_WordOut(WORD wPosX,WORD wPosY,WORD wData)
{
	char szTextBuffer[16];
	LCD_FormatReal(szTextBuffer,wData,0x50);
	LCD_AsciiOut(wPosX,wPosY,szTextBuffer);
}

void LCD_RealOut(WORD wPosX,WORD wPosY,DWORD fData,WORD wFormat)
{
	char szTextBuffer[16];
	LCD_FormatReal(szTextBuffer,fData,wFormat);
	LCD_AsciiOut(wPosX,wPosY,szTextBuffer);
}

void LCD_FormatReal(char* pszText,DWORD fData,WORD wFormat)
{
	char* pszTemp;
	WORD wCountAfterDot;
	WORD wSignFlag;

	pszTemp = pszText;
	*pszTemp = 0;
	wFormat &= 0x00ff;
	wCountAfterDot = wFormat&0x000f;
	if(wCountAfterDot>4) return;
	wSignFlag = (WORD)(fData>>30);
	fData &= 0x3fffffff;
	switch(wFormat>>4)
	{
    case 9: if(fData>999999999) fData = 999999999; break;
	case 8: if(fData>99999999) fData = 99999999; break;
	case 7: if(fData>9999999) fData = 9999999; break;
	case 6: if(fData>999999) fData = 999999; break;
	case 5: if(fData>99999) fData = 99999; break;
	case 4: if(fData>9999) fData = 9999; break;
	case 3: if(fData>999) fData = 999; break;
	case 2: if(fData>99) fData = 99; break;
    case 1: if(fData>9) fData = 9; break;
	default: return;
	}
	if(wSignFlag) *pszTemp++ = ' ';
	switch(wFormat>>4)
	{
    case 9: *pszTemp++ = '0'+(char)(fData%1000000000L/100000000L);
	case 8: *pszTemp++ = '0'+(char)(fData%100000000L/10000000L);
	case 7: *pszTemp++ = '0'+(char)(fData%10000000L/1000000L);
	case 6: *pszTemp++ = '0'+(char)(fData%1000000L/100000L);
	case 5: *pszTemp++ = '0'+(char)(fData%100000L/10000L);
			if(wCountAfterDot==4) *pszTemp++ = '.';
	case 4: *pszTemp++ = '0'+(char)(fData%10000L/1000L);
			if(wCountAfterDot==3) *pszTemp++ = '.';
	case 3: *pszTemp++ = '0'+(char)(fData%1000L/100L);
			if(wCountAfterDot==2) *pszTemp++ = '.';
	case 2: *pszTemp++ = '0'+(char)(fData%100L/10L);
			if(wCountAfterDot==1) *pszTemp++ = '.';
// 			*pszTemp++ = '0'+(char)(fData%10L);
// 			break;
    case 1: *pszTemp++ = '0'+(char)(fData%10L);
			break;
	default: return;
	}
	*pszTemp = 0;
	if(g_bLCDFormatRealFillBlank)
	{
		pszTemp = pszText;
		if(wSignFlag) pszTemp++;
		wCountAfterDot = (wFormat>>4) - wCountAfterDot - 1;
		while(wCountAfterDot--)
		{
			if(*pszTemp=='0') *pszTemp = ' ';
			else break;
			pszTemp++;
		}
		if(wSignFlag==3) *(pszTemp-1) = '-';
	}
	g_bLCDFormatRealFillBlank = TRUE;
}

void LCD_AutoTextOut(char* pszText)
{
	LCD_TextOut(g_wLCDAutoPosX,g_wLCDAutoPosY,pszText);
	g_wLCDAutoPosY += g_wLCDAutoEnter;
}

void LCD_AutoTextOutW(WORD* pwszText)
{
	LCD_TextOutW(g_wLCDAutoPosX,g_wLCDAutoPosY,pwszText);
	g_wLCDAutoPosY += g_wLCDAutoEnter;
}

void LCD_AutoAsciiOut(char* pszText)
{
	LCD_AsciiOut(g_wLCDAutoPosX,g_wLCDAutoPosY,pszText);
	g_wLCDAutoPosY += g_wLCDAutoEnter;
}

void LCD_AutoAsciiOutW(WORD* pwszText)
{
	LCD_AsciiOutW(g_wLCDAutoPosX,g_wLCDAutoPosY,pwszText);
	g_wLCDAutoPosY += g_wLCDAutoEnter;
}

void LCD_AutoByteOut(BYTE Data,WORD wFormat)
{
	LCD_ByteOut(g_wLCDAutoPosX,g_wLCDAutoPosY,Data,wFormat);
	g_wLCDAutoPosY += g_wLCDAutoEnter;
}

void LCD_AutoWordOut(WORD wData)
{
	LCD_WordOut(g_wLCDAutoPosX,g_wLCDAutoPosY,wData);
	g_wLCDAutoPosY += g_wLCDAutoEnter;
}

void LCD_AutoRealOut(DWORD fData,WORD wFormat)
{
	LCD_RealOut(g_wLCDAutoPosX,g_wLCDAutoPosY,fData,wFormat);
	g_wLCDAutoPosY += g_wLCDAutoEnter;
}

void LCD_AutoOutERR_OK(BOOL bERR)
{
	LCD_AutoAsciiOut(bERR?(char*)"ERR":(char*)" OK");
}

void LCD_AutoOutALM_OK(BOOL bALM)
{
	LCD_AutoAsciiOut(bALM?(char*)"ALM":(char*)" OK");
}

void LCD_AutoOutYES_NO(BOOL bYES)
{
	LCD_AutoAsciiOut(bYES?(char*)"YES":(char*)" NO");
}

void LCD_AutoOutOFF_ON(BOOL bOFF)
{
	LCD_AutoAsciiOut(bOFF?(char*)"OFF":(char*)" ON");
}

void LCD_AutoOut__1__0(BOOL b__1)
{
	LCD_AutoAsciiOut(b__1?(char*)"  1":(char*)"  0");
}

