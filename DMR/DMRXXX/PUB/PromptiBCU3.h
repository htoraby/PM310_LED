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

#ifndef _PROMPRIBCU3_H
#define _PROMPRIBCU3_H

enum PROMPTINDEX
{
	 PROMPTINDEX = 0
	,PROMPTINDEX_BUTTON_WFR_START_TEXT
	,PROMPTINDEX_BUTTON_WFR_STOP_TEXT
	,PROMPTINDEX_BUTTON_WFR_START
	,PROMPTINDEX_BUTTON_WFR_STOP
	,PROMPTINDEX_BUTTON_SET_TEXT
	,PROMPTINDEX_BUTTON_OPEN_TEXT
	,PROMPTINDEX_ERROR_STOPRECORD
	,PROMPTINDEX_ERROR
	,PROMPTINDEX_MAX
};

extern char* GetPrompt(WORD wIndex);

#endif/*_PROMPRIBCU3_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/

