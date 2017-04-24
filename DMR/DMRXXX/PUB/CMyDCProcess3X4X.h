/*
;*****************************************************************************************************
;*						Copyright (c) 2009 by ThinkBoy. 
;*						All rights reserved.
;*
;* Header:
;* File Name: 
;* Author: jimmy
;* Date:
;*****************************************************************************************************
;*/

#ifndef _CMYDCPROCESSDMR450F_H
#define _CMYDCPROCESSDMR450F_H

#define DCLINKPARAMW				5

enum DCLINK
{
	 DCLINK_NULL = 0
	,DCLINK_Ia
	,DCLINK_Ib
	,DCLINK_Ic
	,DCLINK_3I0
	,DCLINK_Ua
	,DCLINK_Ub
	,DCLINK_Uc
	,DCLINK_Uab
	,DCLINK_Ubc
	,DCLINK_Uca
	,DCLINK_3U0
	,DCLINK_P
	,DCLINK_Q
	,DCLINK_PF
	,DCLINK_Freq
	,DCLINK_MAX
};

// ===================================================================================================
#undef CLASSNAME_DCPROCESS
#define CLASSNAME_DCPROCESS CMyDCProcessDMR450F
class CMyDCProcessDMR450F:public CMyDCProcess
{
public:
	void GetLinkData(WORD wDataIndex,WORD &wData,WORD &wScale);
};

extern const char g_szDCLinkData[][5];

#endif/*_CMYDCPROCESSDMR450F_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/

