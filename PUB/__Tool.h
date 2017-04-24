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
//˵��:�����ַ����ĳ���;
extern WORD GetStringLength(char* pszString);
//˵��:�ַ�������,pszDestΪĿ��,pszSrcΪԴ,�Զ�ʶ���ַ�������;
extern void StringCopy(char* pszDest,char* pszSrc);
//˵��:�ַ�������,pszDestΪĿ��,pwszSrcΪԴ,�Զ�ʶ���ַ�������;
// extern void CopyWSZToChar(char* pszDest,WORD* pwszSrc);
//˵��:�ַ�������,pwszDestΪĿ��,pszSrcΪԴ,�Զ�ʶ���ַ�������;
extern void CopyCharToWSZ(WORD* pwszDest,char* pszSrc);
//˵��:�ڴ渴��,pszDestΪĿ��,pszSrcΪԴ,wCountWordΪ��������;
extern void MemoryCopy(WORD* pDest,WORD* pSrc,WORD wCountWord);
//˵��:�ڴ�����,wCountWordΪ��������;
extern void MemoryClear(WORD* pMemory,WORD wCountWord);
//˵��:ȡ�������е���Сֵ;
extern WORD GetMin(WORD wData1,WORD wData2,WORD wData3);
//˵��:ȡ�������е����ֵ;
extern WORD GetMax(WORD wData1,WORD wData2,WORD wData3);
//˵��:ȡ����һ�����ݵ��ۼӺ�,���ֲ����Զ�����;
extern WORD GetAddSum(WORD* pData,WORD wLength);
//˵��:��BYTE��ʽȡ����һ�����ݵ�CRCУ���;
extern WORD CalculateCRCByte(BYTE* pData,WORD wLength);
//˵��:��WORD��ʽȡ����һ�����ݵ�CRCУ���;
extern WORD CalculateCRCWord(WORD* pData,WORD wLength);
//˵��:ȡ���ֵ�ƽ����,ȫ��Χ;
extern WORD GetSqrt(DWORD dwData);
//˵��:ȡ�������ݵ�ģ(ƽ���͵�ƽ����);
extern WORD GetSqrtX(short nData1,short nData2);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__TOOL_H*/

/******************************************************************************/
//ThinkBoy,ShenBo,2006/04/30;

//-----------------------------------------------------------------------------------------------------
//											End Of File
//-----------------------------------------------------------------------------------------------------
