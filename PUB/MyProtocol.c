#include <Main.h>

BYTE g_CommBuffer[COMM_BUFFERSIZE];
BYTE* g_pRcvPointer;
BYTE* g_pRcvEndPointer;
BYTE* g_pSndPointer;
BYTE* g_pSndEndPointer;
WORD g_wModAddr;
WORD g_wCommStatus;
WORD g_wCountTimeout;
WORD g_wCRCCal;

//-----------------------------------------------------------------------------
void Protocol_OnInit(void)
{
	g_pRcvPointer = g_CommBuffer;
	g_pRcvEndPointer = g_CommBuffer;
	g_pSndPointer = g_CommBuffer;
	g_pSndEndPointer = g_CommBuffer;
	g_wCommStatus = COMMSTATUS_RCV_ADDR;
	g_wCountTimeout = COMM_TIMEOUT;
	g_wModAddr = 0;
	g_wCRCCal = 0x0000;
}

void Protocol_OnPolling(void)
{
	if(g_wCountTimeout>0)
	{
		g_wCountTimeout--;
		if(g_wCountTimeout==0) g_wCommStatus = COMMSTATUS_NULL;
	}
}
/*
BOOL Protocol_IsCommActive(void)
{
	switch(g_wCommStatus)
	{
	case COMMSTATUS_RCV_HEAD:
	case COMMSTATUS_RCV_DATA:
	case COMMSTATUS_SNDOPEN:
	case COMMSTATUS_SNDING1:
	case COMMSTATUS_SNDING2:
	case COMMSTATUS_SNDING3:
	case COMMSTATUS_SNDCLOSE:
		return TRUE;
	}
	return FALSE;
}
*/
BYTE Protocol_GetSndData(void)
{
	BYTE SndData;
	SndData = 0;
	if(g_wCommStatus==COMMSTATUS_SNDING1)
	{
		SndData = *g_pSndPointer++;
		if(g_pSndPointer>=g_pSndEndPointer) g_wCommStatus = COMMSTATUS_SNDING2;
	}
	return SndData;
}

