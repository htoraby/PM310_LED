

#include "PUB\__Tool.h"


//-----------------------------------------------------------------------------
const WORD c_wTableCRC[256] = 
{
	0x0000,0xc0c1,0xc181,0x0140,0xc301,0x03c0,0x0280,0xc241,
	0xc601,0x06c0,0x0780,0xc741,0x0500,0xc5c1,0xc481,0x0440,
	0xcc01,0x0cc0,0x0d80,0xcd41,0x0f00,0xcfc1,0xce81,0x0e40,
	0x0a00,0xcac1,0xcb81,0x0b40,0xc901,0x09c0,0x0880,0xc841,
	0xd801,0x18c0,0x1980,0xd941,0x1b00,0xdbc1,0xda81,0x1a40,
	0x1e00,0xdec1,0xdf81,0x1f40,0xdd01,0x1dc0,0x1c80,0xdc41,
	0x1400,0xd4c1,0xd581,0x1540,0xd701,0x17c0,0x1680,0xd641,
	0xd201,0x12c0,0x1380,0xd341,0x1100,0xd1c1,0xd081,0x1040,
	0xf001,0x30c0,0x3180,0xf141,0x3300,0xf3c1,0xf281,0x3240,
	0x3600,0xf6c1,0xf781,0x3740,0xf501,0x35c0,0x3480,0xf441,
	0x3c00,0xfcc1,0xfd81,0x3d40,0xff01,0x3fc0,0x3e80,0xfe41,
	0xfa01,0x3ac0,0x3b80,0xfb41,0x3900,0xf9c1,0xf881,0x3840,
	0x2800,0xe8c1,0xe981,0x2940,0xeb01,0x2bc0,0x2a80,0xea41,
	0xee01,0x2ec0,0x2f80,0xef41,0x2d00,0xedc1,0xec81,0x2c40,
	0xe401,0x24c0,0x2580,0xe541,0x2700,0xe7c1,0xe681,0x2640,
	0x2200,0xe2c1,0xe381,0x2340,0xe101,0x21c0,0x2080,0xe041,
	0xa001,0x60c0,0x6180,0xa141,0x6300,0xa3c1,0xa281,0x6240,
	0x6600,0xa6c1,0xa781,0x6740,0xa501,0x65c0,0x6480,0xa441,
	0x6c00,0xacc1,0xad81,0x6d40,0xaf01,0x6fc0,0x6e80,0xae41,
	0xaa01,0x6ac0,0x6b80,0xab41,0x6900,0xa9c1,0xa881,0x6840,
	0x7800,0xb8c1,0xb981,0x7940,0xbb01,0x7bc0,0x7a80,0xba41,
	0xbe01,0x7ec0,0x7f80,0xbf41,0x7d00,0xbdc1,0xbc81,0x7c40,
	0xb401,0x74c0,0x7580,0xb541,0x7700,0xb7c1,0xb681,0x7640,
	0x7200,0xb2c1,0xb381,0x7340,0xb101,0x71c0,0x7080,0xb041,
	0x5000,0x90c1,0x9181,0x5140,0x9301,0x53c0,0x5280,0x9241,
	0x9601,0x56c0,0x5780,0x9741,0x5500,0x95c1,0x9481,0x5440,
	0x9c01,0x5cc0,0x5d80,0x9d41,0x5f00,0x9fc1,0x9e81,0x5e40,
	0x5a00,0x9ac1,0x9b81,0x5b40,0x9901,0x59c0,0x5880,0x9841,
	0x8801,0x48c0,0x4980,0x8941,0x4b00,0x8bc1,0x8a81,0x4a40,
	0x4e00,0x8ec1,0x8f81,0x4f40,0x8d01,0x4dc0,0x4c80,0x8c41,
	0x4400,0x84c1,0x8581,0x4540,0x8701,0x47c0,0x4680,0x8641,
	0x8201,0x42c0,0x4380,0x8341,0x4100,0x81c1,0x8081,0x4040
};


//-----------------------------------------------------------------------------
const WORD c_wTableSQRT[193] = 
{
	0x7eff,
	0x8000,0x80ff,0x81fc,0x82f7,0x83f0,0x84e7,0x85dd,0x86d1,
	0x87c3,0x88b4,0x89a3,0x8a90,0x8b7c,0x8c66,0x8d4e,0x8e36,
	0x8f1b,0x9000,0x90e2,0x91c4,0x92a4,0x9383,0x9460,0x953c,
	0x9617,0x96f1,0x97ca,0x98a1,0x9977,0x9a4c,0x9b20,0x9bf2,
	0x9cc4,0x9d94,0x9e64,0x9f32,0xa000,0xa0cc,0xa197,0xa261,
	0xa32b,0xa3f3,0xa4ba,0xa581,0xa646,0xa70b,0xa7cf,0xa892,
	0xa953,0xaa15,0xaad5,0xab94,0xac53,0xad11,0xadcd,0xae8a,
	0xaf45,0xb000,0xb0b9,0xb172,0xb22b,0xb2e2,0xb399,0xb44f,
	0xb504,0xb5b9,0xb66d,0xb720,0xb7d3,0xb885,0xb936,0xb9e7,
	0xba97,0xbb46,0xbbf5,0xbca3,0xbd50,0xbdfd,0xbea9,0xbf55,
	0xc000,0xc0aa,0xc154,0xc1fd,0xc2a5,0xc34e,0xc3f5,0xc49c,
	0xc542,0xc5e8,0xc68e,0xc732,0xc7d7,0xc87a,0xc91d,0xc9c0,
	0xca62,0xcb04,0xcba5,0xcc46,0xcce6,0xcd86,0xce25,0xcec3,
	0xcf62,0xd000,0xd09d,0xd13a,0xd1d6,0xd272,0xd30d,0xd3a8,
	0xd443,0xd4dd,0xd577,0xd610,0xd6a9,0xd742,0xd7da,0xd871,
	0xd908,0xd99f,0xda35,0xdacb,0xdb61,0xdbf6,0xdc8b,0xdd1f,
	0xddb3,0xde47,0xdeda,0xdf6d,0xe000,0xe092,0xe123,0xe1b5,
	0xe246,0xe2d6,0xe367,0xe3f7,0xe486,0xe515,0xe5a4,0xe633,
	0xe6c1,0xe74f,0xe7dc,0xe869,0xe8f6,0xe983,0xea0f,0xea9b,
	0xeb26,0xebb1,0xec3c,0xecc7,0xed51,0xeddb,0xee65,0xeeee,
	0xef77,0xf000,0xf088,0xf110,0xf198,0xf21f,0xf2a6,0xf32d,
	0xf3b4,0xf43a,0xf4c0,0xf546,0xf5cb,0xf651,0xf6d6,0xf75a,
	0xf7de,0xf863,0xf8e6,0xf96a,0xf9ed,0xfa70,0xfaf3,0xfb75,
	0xfbf7,0xfc79,0xfcfb,0xfd7c,0xfdfd,0xfe7e,0xfeff,0xff7f
};

// #define CalcCRC(Data,wCRC)								\
// 	do													\
// 	{													\
// 		BYTE _CRC;										\
// 		wCRC =0^((WORD)Data);							\
// 		for(_CRC=0;_CRC<8;_CRC++)						\
// 		{												\
// 			BYTE chk;									\
// 			chk = wCRC&1;								\
// 			wCRC = wCRC>>1;								\
// 			wCRC = wCRC&0x7fff;							\
// 			if(chk==1) wCRC ^= 0xa001;					\
// 			wCRC = wCRC&0xffff;							\
// 		}												\
// 	}													\
// 	while(0)
// 
// WORD CalculateCRCByte(BYTE* pData,WORD wLength)
// {
// 	WORD wCRC = 0xffff;
// 	WORD wCRCTbl;
// 	while(wLength--)
// 	{
// 		CalcCRC((wCRC^*pData++)&0xff,wCRCTbl);
// 		wCRC = (wCRC>>8)^wCRCTbl;
// 	}
// 	return wCRC;
// }
// 
// WORD CalculateCRCWord(WORD* pwData,WORD wLength)
// {
// 	WORD wCRC = 0xffff;
// 	WORD wCRCTbl;
// 	WORD* pData;
// // 	pData = (WORD*)((WORD)pwData);
// //	pData = (WORD*)((WORD)(pwData)&0x00ff);
// 	pData = pwData;
// 	wCRCTbl = *pData;
// 	while(wLength--)
// 	{
// 		CalcCRC((wCRC^(*pData&0xff))&0xff,wCRCTbl);
// 		wCRC = (wCRC>>8)^wCRCTbl;	
// 		CalcCRC((wCRC^(*pData>>8))&0xff,wCRCTbl);
// 		wCRC = (wCRC>>8)^wCRCTbl;
// 		pData++;
// 	}
// 	return wCRC;
// }

// WORD GetSqrt(DWORD dwData)
// {
// 	DWORD i,dwc;
// 	DWORD dwb = 0;
// 	for(i = 0x40000000; i != 0; i >>= 2)
// 	{
// 		dwc = i + dwb;
// 		dwb >>= 1;
// 		if(dwc <= dwData)
// 		{
// 			dwData -= dwc;
// 			dwb += i;
// 		}
// 	}
// 	return (WORD)dwb;
// } 

//-----------------------------------------------------------------------------
WORD GetStringLength(char* pszString)
{
	WORD wLength = 0;
	while(*pszString)
	{
		wLength++;
		pszString++;
	}
	return wLength;
}

void StringCopy(char* pszDest,char* pszSrc)
{
	while(*pszSrc) *pszDest++ = *pszSrc++;
	*pszDest = 0;
}

// void CopyWSZToChar(char* pszDest,WORD* pwszSrc)
// {
// 	while(*pwszSrc) *pszDest++ = (char)(short)*pwszSrc++;
// 	*pszDest = 0;
// }

void CopyCharToWSZ(WORD* pwszDest,char* pszSrc)
{
	while(*pszSrc) *pwszDest++ = (WORD)(short)*pszSrc++;
	*pwszDest = 0;
}

void MemoryCopy(WORD* pDest,WORD* pSrc,WORD wCountWord)
{
	while(wCountWord--) *pDest++ = *pSrc++;
}

void MemoryClear(WORD* pMemory,WORD wCountWord)
{
	while(wCountWord--) *pMemory++ = 0;
}

WORD GetMin(WORD wData1,WORD wData2,WORD wData3)
{
	WORD wDataMin = wData1;
	if(wDataMin>wData2) wDataMin = wData2;
	if(wDataMin>wData3) wDataMin = wData3;
	return wDataMin;
}

WORD GetMax(WORD wData1,WORD wData2,WORD wData3)
{
	WORD wDataMax = wData1;
	if(wDataMax<wData2) wDataMax = wData2;
	if(wDataMax<wData3) wDataMax = wData3;
	return wDataMax;
}

WORD GetAddSum(WORD* pData,WORD wLength)
{
	WORD wAddSum = 0;
	while(wLength--) wAddSum += *pData++;
	return wAddSum;
}

WORD CalculateCRCByte(BYTE* pData,WORD wLength)
{
	WORD wCRC = 0xffff;
	while(wLength--) wCRC = (wCRC>>8)^c_wTableCRC[(wCRC^*pData++)&0xff];
	return wCRC;
}

WORD CalculateCRCWord(WORD* pData,WORD wLength)
{
	WORD wCRC = 0xffff;
	while(wLength--)
	{
		wCRC = (wCRC>>8)^c_wTableCRC[(wCRC^(*pData&0xff))&0xff];
		wCRC = (wCRC>>8)^c_wTableCRC[(wCRC^(*pData>>8))&0xff];
		pData++;
	}
	return wCRC;
}

WORD GetSqrt(DWORD dwData)
{
	WORD wCountShift,wResult;
	if(dwData==0) return 0;
	if(dwData>0xfffe0000) return 0xffff;
	wCountShift = 0;
	while(dwData<0x3fff8000)
	{
		dwData <<= 2;
		wCountShift++;
	}
	wResult = c_wTableSQRT[(dwData>>24)-0x003f];
	dwData -= (DWORD)(wResult-1)*wResult;
	dwData >>= 1;
	wResult += (WORD)(dwData/wResult);
	if(wCountShift)
	{
		wCountShift--;
		wResult >>= wCountShift;
		if(wResult==0xffff) return 0x8000;
		if(wResult&0x0001) wResult++;
		wResult >>= 1;
	}
	return wResult;
}

WORD GetSqrtX(short nData1,short nData2)
{
	return GetSqrt((long)nData1*(long)nData1+(long)nData2*(long)nData2);
}

char BinToStr(BYTE Data)
{
    if(Data<10) return ('0' + Data);
    else if(Data<16) return ('A' + Data - 10);
    return 0;
}

//-----------------------------------------------------------------------------------------------------
//											End Of File
//-----------------------------------------------------------------------------------------------------
