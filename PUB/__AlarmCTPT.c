#include <Main.h>


//-----------------------------------------------------------------------------
// void AlarmGCTM_ExeDetect(MyAlarmGroup3* pthis,MyData* dataIa,MyData* dataIb,MyData* dataIc,WORD wModeCTM,WORD wAlarmToggle,WORD wAlarmEventCode)
// {
// 	WORD wDataIa;
// 	WORD wDataIb;
// 	WORD wDataIc;
// 
// 	wDataIa = (WORD)(dataIa->m_nData);
// 	wDataIb = (WORD)(dataIb->m_nData);
// 	wDataIc = (WORD)(dataIc->m_nData);
// 
// 	if(wDataIa>ALARMCTM_0_1A||wDataIb>ALARMCTM_0_1A||wDataIc>ALARMCTM_0_1A)
// 	{
// 		Alarm_ExeDetect(&pthis->m_alarmone[0],wAlarmToggle,ALARMCTM_DELAY,(wDataIa==0),wAlarmEventCode);
// 		if(wModeCTM==MODECT_3CT) Alarm_ExeDetect(&pthis->m_alarmone[1],wAlarmToggle,ALARMCTM_DELAY,(wDataIb==0),(WORD)(wAlarmEventCode+1));
// 		Alarm_ExeDetect(&pthis->m_alarmone[2],wAlarmToggle,ALARMCTM_DELAY,(wDataIc==0),(WORD)(wAlarmEventCode+2));
// 	}
// 	else AlarmG_OnReset(pthis);
// }


//-----------------------------------------------------------------------------
void AlarmGCTP_ExeDetect(MyAlarmGroup3* pthis,MyData* dataIA,MyData* dataIB,MyData* dataIC,WORD wModeCTP,WORD wAlarmToggle,WORD wAlarmEventCode)
{
	WORD wDataIA;
	WORD wDataIB;
	WORD wDataIC;

	wDataIA = (WORD)(dataIA->m_nData);
	wDataIB = (WORD)(dataIB->m_nData);
	wDataIC = (WORD)(dataIC->m_nData);

	if(wDataIA>ALARMCTP_0_5A||wDataIB>ALARMCTP_0_5A||wDataIC>ALARMCTP_0_5A)
	{
		Alarm_ExeDetect(&pthis->m_alarmone[0],wAlarmToggle,ALARMCTP_DELAY,(wDataIA==0),wAlarmEventCode);
		if(wModeCTP==MODECT_3CT) Alarm_ExeDetect(&pthis->m_alarmone[1],wAlarmToggle,ALARMCTP_DELAY,(wDataIB==0),(WORD)(wAlarmEventCode+1));
		Alarm_ExeDetect(&pthis->m_alarmone[2],wAlarmToggle,ALARMCTP_DELAY,(wDataIC==0),(WORD)(wAlarmEventCode+2));
	}
	else AlarmG_OnReset(pthis);
}

//-----------------------------------------------------------------------------
void AlarmGPT_ExeDetect(MyAlarmGroup3* pthis,MyData* dataUa,MyData* dataUb,MyData* dataUc,
								MyData* dataUab,MyData* dataUbc,MyData* dataUca,
								WORD wModePT,WORD wDataIMax,WORD wAlarmToggle,WORD wAlarmEventCode)
{
	WORD wDataUa;
	WORD wDataUb;
	WORD wDataUc;
	WORD wDataUab;
	WORD wDataUbc;
	WORD wDataUca;
	WORD wDataUllMin;
	WORD wDataUllMax;
	short n3U0R;
	short n3U0X;
	WORD w3U0A;
	BOOL bAlarmPT1;
	BOOL bAlarmPT2;
	short n3U0;

	wDataUa = (WORD)(dataUa->m_nData);
	wDataUb = (WORD)(dataUb->m_nData);
	wDataUc = (WORD)(dataUc->m_nData);
	wDataUab = (WORD)(dataUab->m_nData);
	wDataUbc = (WORD)(dataUbc->m_nData);
	wDataUca = (WORD)(dataUca->m_nData);
	wDataUllMin = GetMin(wDataUab,wDataUbc,wDataUca);
	wDataUllMax = GetMax(wDataUab,wDataUbc,wDataUca);

	Alarm_ExeDetect(&pthis->m_alarmone[0],wAlarmToggle,ALARMPT_DELAY,(wDataUa<ALARMPT_10V && wDataUb<ALARMPT_10V && wDataUc<ALARMPT_10V && wDataIMax>0),wAlarmEventCode);
	if(wModePT==MODEPT_WYE)
	{
		n3U0R = dataUa->m_nR + dataUb->m_nR + dataUc->m_nR;
		n3U0X = dataUa->m_nX + dataUb->m_nX + dataUc->m_nX;
		w3U0A = GetSqrtX(n3U0R,n3U0X);
		bAlarmPT1 = (w3U0A>ALARMPT_10V*4 && wDataUllMax>ALARMPT_10V*7 && wDataUllMax-wDataUllMin>ALARMPT_10V*3);
		bAlarmPT2 = (w3U0A>ALARMPT_10V*4 && wDataUa+wDataUb+wDataUc<w3U0A+ALARMPT_10V);
		if(bAlarmPT2) bAlarmPT1 = FALSE;
		Alarm_ExeDetect(&pthis->m_alarmone[1],wAlarmToggle,ALARMPT_DELAY,bAlarmPT1,(WORD)(wAlarmEventCode+2));
		Alarm_ExeDetect(&pthis->m_alarmone[2],wAlarmToggle,ALARMPT_DELAY,bAlarmPT2,(WORD)(wAlarmEventCode+1));
	}
	else
	{
		w3U0A = wDataUab + wDataUbc + wDataUca;
		n3U0 = (short)(2*wDataUllMax-w3U0A);
		if(n3U0<0) n3U0 = -n3U0;
		Alarm_ExeDetect(&pthis->m_alarmone[1],wAlarmToggle,ALARMPT_DELAY,(n3U0<ALARMPT_10V && wDataUllMax>ALARMPT_10V*7),(WORD)(wAlarmEventCode+2));
		Alarm_OnReset(&pthis->m_alarmone[2]);
	}
}
