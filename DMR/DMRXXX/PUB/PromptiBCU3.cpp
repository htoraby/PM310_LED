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
	{"��ʼ","Start"}
// PROMPTINDEX_BUTTON_WFR_STOP_TEXT
	,{"ֹͣ","Stop"}
// PROMPTINDEX_BUTTON_WFR_START
// 	,{"��ֹͣ¼��,���ENT��ʼ","Record Stoped,Click ENT to Start"}
	,{"��ֹͣ¼��","Record Stoped"}
// PROMPTINDEX_BUTTON_WFR_STOP
// 	,{"����¼��,���ENTֹͣ",""}
	,{"����¼��","Recording"}
// PROMPTINDEX_BUTTON_SET_TEXT
	,{"����","SET"}
// PROMPTINDEX_BUTTON_OPEN_TEXT
	,{"��","Open"}
// PROMPTINDEX_ERROR_STOPRECORD
	,{"����ֹͣ¼��!","Please Stop Record!"}
// PROMPTINDEX_ERROR
	,{"������!","Error!"}
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

