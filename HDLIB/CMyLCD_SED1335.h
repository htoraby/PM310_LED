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

#ifndef _CMYLCD_SED1335_H
#define _CMYLCD_SED1335_H

//-----------------------------------------------------------------------------
class CMyLCD_SED1335
{
public:
	void HWRest(void){};
protected:
	void LCDSndData(BYTE Data);
	void LCDSndCommand(BYTE Command);
public:
	VIRTUAL void iiiSetup(void);
	VIRTUAL void iiiFlush(void);
};

#endif/*_CMYLCD_SED1335_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/

