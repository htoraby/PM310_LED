/*
;*****************************************************************************************************
;*						Copyright (c) 2000-2012 ThinkBon. 
;*						All rights reserved.
;*
;* Header:
;* File Name: NPS7510.h
;* Author: iVexMaker
;* Date: 2015-08-12 13:26:09 32 - Wednesday
;*****************************************************************************************************
;*/
#ifndef _HDIFNPS7510_H
#define _HDIFNPS7510_H

#include "..\PUB\HDIFDMR.h"
// #include "PUB\__LCD.h"
// #include "PUB\__LCDMem.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void MyHDIF_OnInit1Sub(void);
extern WORD MyHDIF_GetFreqINT1(void);

extern const tCRC32INFO* g_pCRCInfo;

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif /*_NPS7510_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/
