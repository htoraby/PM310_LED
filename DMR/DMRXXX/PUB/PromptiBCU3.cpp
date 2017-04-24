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

// #include "Pub\__Tool.h"
// #include "DMR\DMRXXX\PUB\PromptiBCU3.h"

#include "main.h"

const char* s_szPrompt[][2] = 
{
// PROMPTINDEX_BUTTON_WFR_START_TEXT
	{"¿ªÊ¼","Start"}
// PROMPTINDEX_BUTTON_WFR_STOP_TEXT
	,{"Í£Ö¹","Stop"}
// PROMPTINDEX_BUTTON_WFR_START
// 	,{"ÒÑÍ£Ö¹Â¼²¨,µã»÷ENT¿ªÊ¼","Record Stoped,Click ENT to Start"}
	,{"ÒÑÍ£Ö¹Â¼²¨","Record Stoped"}
// PROMPTINDEX_BUTTON_WFR_STOP
// 	,{"ÕýÔÚÂ¼²¨,µã»÷ENTÍ£Ö¹",""}
	,{"ÕýÔÚÂ¼²¨","Recording"}
// PROMPTINDEX_BUTTON_SET_TEXT
	,{"ÉèÖÃ","SET"}
// PROMPTINDEX_BUTTON_OPEN_TEXT
	,{"´ò¿ª","Open"}
// PROMPTINDEX_ERROR_STOPRECORD
	,{"ÇëÏÈÍ£Ö¹Â¼²¨!","Please Stop Record!"}
// PROMPTINDEX_ERROR
	,{"³ö´íÀ²!","Error!"}
};

char* GetPrompt(WORD wIndex)
{
	if(wIndex>=PROMPTINDEX_MAX) return NULL;
	if(wIndex==NULL) return NULL;
	return MULTITEXT(s_szPrompt[wIndex-1][0],s_szPrompt[wIndex-1][1]);
}

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/

