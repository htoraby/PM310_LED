#include <Main.h>


//-----------------------------------------------------------------------------
void Output_OnInit(MyOutput* pthis)
{
	pthis->m_wStatus1 = 0x0000;
	pthis->m_wStatus2 = 0x0000;
	pthis->m_wStatus3 = 0x0000;
	pthis->m_wCountPulse = 0;
	pthis->m_wCountTestMode = 0;
	pthis->m_wCountTestMode = OUTPUT_TM_00;
}

void Output_OnTimer10ms(MyOutput* pthis)
{
	WORD wStatus;

	if(pthis->m_wCountTestMode)
	{
		pthis->m_wCountTestMode--;
		wStatus = STATUS_OFF;
		switch(pthis->m_wTestMode)
		{
		case OUTPUT_TM_01: if(pthis->m_wCountTestMode>0 && pthis->m_wCountTestMode<=150) wStatus = STATUS_ON; break;
		case OUTPUT_TM_10: if(pthis->m_wCountTestMode>150 && pthis->m_wCountTestMode<300) wStatus = STATUS_ON; break;
		case OUTPUT_TM_11: if(pthis->m_wCountTestMode>0 && pthis->m_wCountTestMode<300) wStatus = STATUS_ON; break;
		}
		if(wStatus==STATUS_ON)
		{
			pthis->m_wStatus1 = 0x3333;
			pthis->m_wStatus2 = 0x5555;
			pthis->m_wStatus3 = 0xaaaa;
		}
		else
		{
			pthis->m_wStatus1 = 0x0000;
			pthis->m_wStatus2 = 0x0000;
			pthis->m_wStatus3 = 0x0000;
		}
		pthis->m_wCountPulse = 0;
	}
	else if(pthis->m_wCountPulse)
	{
		pthis->m_wCountPulse--;
		if(pthis->m_wCountPulse==0)
		{
			pthis->m_wStatus1 = 0x0000;
			pthis->m_wStatus2 = 0x0000;
			pthis->m_wStatus3 = 0x0000;
		}
	}
}

void Output_SetLevel(MyOutput* pthis,WORD wStatus)
{
	if(pthis->m_wCountTestMode) return;
	pthis->m_wCountPulse = 0;
	if(wStatus==STATUS_ON)
	{
		pthis->m_wStatus1 = 0x3333;
		pthis->m_wStatus2 = 0x5555;
		pthis->m_wStatus3 = 0xaaaa;
	}
	if(wStatus==STATUS_OFF)
	{
		pthis->m_wStatus1 = 0x0000;
		pthis->m_wStatus2 = 0x0000;
		pthis->m_wStatus3 = 0x0000;
	}
}

void Output_SetPulse(MyOutput* pthis,WORD wDelay10ms)
{
	if(pthis->m_wCountTestMode) return;
	Output_SetLevel(pthis,STATUS_ON);
	pthis->m_wCountPulse = wDelay10ms;
}

void Output_EnterTest(MyOutput* pthis,WORD wTestMode,WORD wCountTestMode)
{
	pthis->m_wTestMode = wTestMode;
	pthis->m_wCountTestMode = wCountTestMode;
}

BOOL Output_IsOutputValid(MyOutput* pthis)
{
	return (pthis->m_wStatus1==0x3333 && pthis->m_wStatus2==0x5555 && pthis->m_wStatus3==0xaaaa);
}
