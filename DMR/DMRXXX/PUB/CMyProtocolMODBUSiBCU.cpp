#include <Main.h>

BOOL g_bQuit1ms;

//-----------------------------------------------------------------------------
void CMyProtocolMODBUSiBCU::OnInit(void)
{
	CMyProtocolMODBUS::OnInit();
	if(g_bQuit1ms)
	{
		for(WORD i=0;i<SWITCH_COUNT;i++)
		{
			g_switch[i].m_bPwrDC = FALSE;
			g_switch[i].m_wCntSt1 = 0;
			g_switch[i].m_wCntSt0 = 0;
		}
	}
	g_bQuit1ms = FALSE;
}

