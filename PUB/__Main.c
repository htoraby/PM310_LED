#include <Main.h>

//-------------------------------------------------------------------
void OnMainInit(void)
{
	HDIF_OnInit1();
// 	HDIF_OnInit2();
	APP_OnInitParams();
	APP_OnInit();
	HMI_OnInit();
    HDIF_OnInit2();
}

void OnMainTimer1ms(void)
{
	APP_OnTimer1ms();
	HMI_OnTimer1ms();
	HDIF_OnTimer1ms();
}

void OnMainTimer10ms(void)
{
	APP_OnTimer10ms();
	HMI_OnTimer10ms();
	HDIF_OnTimer10ms();
}

void OnMainTimer250ms(void)
{
	APP_OnTimer250ms();
	HMI_OnTimer250ms();
	HDIF_OnTimer250ms();
}

void OnMainTimer1000ms(void)
{
	APP_OnTimer1000ms();
	HMI_OnTimer1000ms();
//	HDIF_OnTimer1000ms();
}

void OnMainWhileLoop(void)
{
	APP_OnWhileLoop();
	HMI_OnWhileLoop();
	HDIF_OnWhileLoop();
}

void OnMainPollingComm(void)
{
	HDIF_OnPollingComm();
}

void GetADCResult(WORD wChSel,WORD DotNum,WORD wResult)
{
// 	g_analogWave.wData[wChSel][DotNum] = wResult;
}

void OnWaveRecord(WORD wCountAD)
{
    MyApp_OnWaveRecord(wCountAD);
}
