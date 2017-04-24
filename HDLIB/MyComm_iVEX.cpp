#include <Main.h>
#include "stdafx.h"

static WORD s_wRcvFlag;
static WORD s_wRXLength;
static WORD s_wTXLength;
static BYTE s_RXBuffer[COMM_BUFFERSIZE];
static BYTE s_TXBuffer[COMM_BUFFERSIZE];
static CMyComm** s_ppComm;

//-----------------------------------------------------------------------------
void COMM_SetComm(void** ppComm)
{
	s_ppComm = (CMyComm**)ppComm;
}

void COMM_OnInit(void)
{
	Protocol_OnInit();
	s_wRcvFlag = 0;
	s_wRXLength = 0;
	s_wTXLength = 0;
	g_wCommLight = 0;
	g_wCommLight = 0;
}

void COMM_OnPolling(void)
{
	WORD i;
	if(s_ppComm==NULL||*s_ppComm==NULL) return;
	Protocol_OnPolling();
	g_wModAddr = 0x01;	// g_deviceParam.wModbusAddr1;
	if(s_wRXLength)
	{
		for(i=0;i<s_wRXLength;i++) Protocol_OnRcvProcess(s_RXBuffer[i]);
		s_wRXLength = 0;
	}
	WORD wResult = 0;
	switch(g_wCommStatus)
	{
	case COMMSTATUS_INIT:
		COMM_OnInit();
		break;
	case COMMSTATUS_SNDING1:
		for(i=0;i<COMM_BUFFERSIZE;i++)
		{
			if(g_wCommStatus!=COMMSTATUS_SNDING1) break;
			s_TXBuffer[i] = Protocol_GetSndData();
		}
		s_wTXLength = i;
		(*s_ppComm)->ClearCom();
		wResult = 0;
		for(i=0;i<20;i++)
		{
			wResult += (WORD)(*s_ppComm)->WriteCom(s_TXBuffer+wResult,s_wTXLength-wResult);
			if(wResult>=s_wTXLength) break;
		}
		break;
	case COMMSTATUS_SNDOPEN:
		break;
	case COMMSTATUS_SNDING2:
	case COMMSTATUS_SNDCLOSE:
		g_wCommStatus = COMMSTATUS_NULL;
		break;
	case COMMSTATUS_NULL:
		COMM_OnInit();
		break;
	}
}

void COMM_OnTimer10ms(void)
{
	Protocol_OnTimer10msCRC();
	if(*s_ppComm==NULL||s_ppComm==NULL)
	{
		s_wRXLength = 0;
		return;
	}
	s_wRcvFlag++;
	if(s_wRcvFlag>=10)
	{
		s_wRcvFlag = 0;
		if(s_wRXLength<COMM_BUFFERSIZE)
		{
			WORD wTemp = (WORD)(*s_ppComm)->ReadCom(s_RXBuffer+s_wRXLength,COMM_BUFFERSIZE-s_wRXLength);
			if(wTemp) 
				s_wRXLength += wTemp;
		}
	}
}
