#include <Main.h>
#include "stdafx.h"

WORD g_wHDIFFreqINT1;
WORD g_wHDIFFreqINT2;
WORD g_wHDIFPanelDiagCode;
WORD g_wHDIFPWRUPS;
WORD g_wCommLight;
// WORD g_wFsam = 5000;
DWORD g_dwFsam = 6000;   // 8333;
DWORD g_dwSysTimerUs = 0;

//-----------------------------------------------------------------------------
void MyHDIF_OnInit1(void)
{
	g_wHDIFFreqINT1 = 5000;
	g_wHDIFFreqINT2 = 5000;
	g_wHDIFPanelDiagCode = 0x0055;
// 	g_wHDIFPWRUPS = POWERUPS;
//     g_wFsam = 5000;
    g_dwSysTimerUs--;
	MyHDIF_OnInit1Sub();
}

void MyHDIF_OnInit2(void)
{
	COMM_SetComm((void**)&g_pComm1);
	COMM_OnInit();
}

void MyHDIF_OnPollingComm(void)
{
	COMM_OnPolling();
}

void MyHDIF_OnPollingCommET(void)
{

}

void MyHDIF_OnTimer1ms(void)
{
}

void MyHDIF_OnTimer10ms(void)
{
	COMM_OnTimer10ms();
}

void MyHDIF_OnTimer1000ms(void)
{

}

WORD MyHDIF_GetPanelDiagCode(void)
{
	return g_wHDIFPanelDiagCode;
}

void MyHDIF_RestExProtocol(void)
{
	return;
}

void MyHDIF_OnWhileLoop(void)
{

}
