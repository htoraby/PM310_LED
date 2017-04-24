#ifndef _MYDRW_H
#define _MYDRW_H

#define MODULE__DRW_H

/******************************************************************************
支持文件:
__Time.*;
__LCD.*;
*/

#define DRWTYPE_HLINE			0x0000
#define DRWTYPE_VLINE			0x0001
#define DRWTYPE_XLINE			0x0002
#define DRWTYPE_CIRCLE			0x0003
#define DRWTYPE_ERASE			0x0004
#define DRWTYPE_TEXT			0x0005
#define DRWTYPE_ANALOG			0x0006
#define DRWTYPE_BLOCK			0x0007
#define DRWTYPE_BLOCKDYN		0x0008

//-----------------------------------------------------------------------------
typedef struct _DRW_BASE
{
	WORD wType;
	WORD wPointX;
	WORD wPointY;
}DRW_BASE;

typedef struct _DRW_HLINE
{
	WORD wType;
	WORD wPointX;
	WORD wPointY;
	WORD wLength;
	WORD wLineType;
}DRW_HLINE;

typedef struct _DRW_VLINE
{
	WORD wType;
	WORD wPointX;
	WORD wPointY;
	WORD wLength;
	WORD wLineType;
}DRW_VLINE;

typedef struct _DRW_XLINE
{
	WORD wType;
	WORD wPointX;
	WORD wPointY;
	WORD wWidth;
	WORD wHeight;
	WORD bTopLeft;
}DRW_XLINE;

typedef struct _DRW_CIRCLE
{
	WORD wType;
	WORD wPointX;
	WORD wPointY;
	WORD wRadio;
}DRW_CIRCLE;

typedef struct _DRW_ERASE
{
	WORD wType;
	WORD wPointX;
	WORD wPointY;
	WORD wWidth;
	WORD wHeight;
}DRW_ERASE;

typedef struct _DRW_TEXT
{
	WORD wType;
	WORD wPointX;
	WORD wPointY;
	WORD wszText[5];
}DRW_TEXT;

typedef struct _DRW_ANALOG
{
	WORD wType;
	WORD wPointX;
	WORD wPointY;
	WORD wLinkAnalog;
}DRW_ANALOG;

typedef struct _DRW_BLOCK
{
	WORD wType;
	WORD wPointX;
	WORD wPointY;
	WORD wBlockType;
}DRW_BLOCK;

typedef struct _DRW_BLOCKDYN
{
	WORD wType;
	WORD wPointX;
	WORD wPointY;
	WORD wBlockType;
	WORD wLinkIN1;
	WORD wLinkIN2;
}DRW_BLOCKDYN;

typedef struct _DEVICEDRW
{
	WORD wCount;
	WORD wReserved[511];
}DEVICEDRW;

#ifndef COUNTDRWMAX
#define COUNTDRWMAX		128
#endif
#ifndef INDEX_ANALOG
#define INDEX_ANALOG	0
#endif

extern DEVICEDRW g_deviceDRW;
//说明:全局接线图数据;

#endif /*_MYDRW_H*/
