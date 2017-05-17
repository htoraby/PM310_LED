//-----------------------------------------------------------------------------------------------------
//									Copyright (c) 2009 by ThinkBoy.
//										All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __TOOL_H
#define __TOOL_H

typedef unsigned char BYTE;
typedef int BOOL;
typedef unsigned short WORD;
typedef unsigned long DWORD;
#define FALSE			0
#define TRUE			1
#define NULL			0
#define TOGGLE_OFF		0
#define TOGGLE_ON		1
#define STATUS_NULL		0x0000
#define STATUS_OFF		0x3333
#define STATUS_ON		0x5555
#define VIRTUAL

#ifndef SIZEOFBYTE
#define SIZEOFBYTE(n)		((sizeof(n)/sizeof(WORD))*2)
#endif

#ifndef SIZEOFWORD
#define SIZEOFWORD(n)		(sizeof(n)/sizeof(WORD))
#endif

#ifndef SIZEOFDWORD
#define SIZEOFDWORD(n)		(sizeof(n)/sizeof(DWORD))
#endif

#ifndef MIN
#define MIN(a,b)			(((a)>(b))?(b):(a))
#endif

#ifndef MAX
#define MAX(a,b)			(((a)>(b))?(a):(b))
#endif

#ifndef MAKEW
#define MAKEW(a,b)			((WORD)(((BYTE)(a))|((WORD)((BYTE)(b)))<<8))
#endif

#define SETBIT(bCondition,Data,bitMask)		if((BOOL)(bCondition)) (Data) |= (bitMask); \
											else (Data) &= 0xffff^(bitMask);

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//说明:计算字符串的长度;
extern WORD GetStringLength(char* pszString);
//说明:字符串复制,pszDest为目标,pszSrc为源,自动识别字符串长度;
extern void StringCopy(char* pszDest,char* pszSrc);
//说明:字符串复制,pszDest为目标,pwszSrc为源,自动识别字符串长度;
// extern void CopyWSZToChar(char* pszDest,WORD* pwszSrc);
//说明:字符串复制,pwszDest为目标,pszSrc为源,自动识别字符串长度;
extern void CopyCharToWSZ(WORD* pwszDest,char* pszSrc);
//说明:内存复制,pszDest为目标,pszSrc为源,wCountWord为复制字数;
extern void MemoryCopy(WORD* pDest,WORD* pSrc,WORD wCountWord);
//说明:内存清零,wCountWord为清零字数;
extern void MemoryClear(WORD* pMemory,WORD wCountWord);
//说明:取三个数中的最小值;
extern WORD GetMin(WORD wData1,WORD wData2,WORD wData3);
//说明:取三个数中的最大值;
extern WORD GetMax(WORD wData1,WORD wData2,WORD wData3);
//说明:取连续一段数据的累加和,高字部分自动舍弃;
extern WORD GetAddSum(WORD* pData,WORD wLength);
//说明:以BYTE方式取连续一段数据的CRC校验和;
extern WORD CalculateCRCByte(BYTE* pData,WORD wLength);
//说明:以WORD方式取连续一段数据的CRC校验和;
extern WORD CalculateCRCWord(WORD* pData,WORD wLength);
//说明:取长字的平方根,全范围;
extern WORD GetSqrt(DWORD dwData);
//说明:取两个数据的模(平方和的平方根);
extern WORD GetSqrtX(short nData1,short nData2);

extern char BinToStr(BYTE Data);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__TOOL_H*/

/******************************************************************************/
//ThinkBoy,ShenBo,2006/04/30;

//-----------------------------------------------------------------------------------------------------
//											End Of File
//-----------------------------------------------------------------------------------------------------
