#include <Main.h>

// INPARAMTABLE g_inparamTable;

WORD g_wStatusNew[SWITCH_COUNT];				// ȷ��ǰ״̬;
WORD g_wStatusNewExt1[SWITCH_COUNT];			// ȷ��ǰ״̬,��չ�Է�ֹ����;
WORD g_wStatusNewExt2[SWITCH_COUNT];			// ȷ��ǰ״̬,��չ�Է�ֹ����;
WORD g_wSwitchStatus1;
WORD g_wSwitchStatus2;
DWORD g_dwChangtoON1;							// �������ڱ�Ϊ�ߵ�ƽ�Ŀ�����;
// ��Ҫ���ڿ���������,��բ�����;
DWORD g_dwChangtoON2;							// ֵ��m_dwChangtoON1��ͬ������ȷ����������������
WORD g_wStatusOld[SWITCH_COUNT];				// ȷ�Ϻ�״̬;
WORD g_wCountAck[SWITCH_COUNT];					// ȷ�ϼ���;
WORD g_wCountStatus0[SWITCH_COUNT];				// 0״̬����
WORD g_wCountStatus1[SWITCH_COUNT];				// 1״̬����

//-----------------------------------------------------------------------------
// void Switch_SetInParam(INPARAM* pInParam,WORD wEventType,WORD wName,WORD wStatus0,WORD wStatus1)
// {
// 	if(pInParam==NULL) return;
// 	pInParam->wEventType = wEventType;
// 	pInParam->wAckDelayTime = 5;
// 	pInParam->wName = wName;
// 	pInParam->wStatus0 = wStatus0;
// 	pInParam->wStatus1 = wStatus1;
// }

//-----------------------------------------------------------------------------
void Switch_OnInit(void)
{
	short i;
	for(i=0;i<SWITCH_COUNT;i++)
	{
		g_wStatusOld[i] = STATUS_NULL;
		g_wStatusNew[i] = STATUS_NULL;
		g_wStatusNewExt1[i] = STATUS_NULL;
		g_wStatusNewExt2[i] = STATUS_NULL;
		g_wCountAck[i] = 0;
	}
	g_dwChangtoON1 = 0;
	g_dwChangtoON2 = 0;
	g_wSwitchStatus1 = 0x0000;
	g_wSwitchStatus2 = 0x0000;
}

void Switch_OnTimer1ms(void)
{
	WORD i;

	for(i=0;i<SWITCH_COUNT;i++)
	{
		if(g_wStatusOld[i]!=STATUS_ON && g_wStatusOld[i]!=STATUS_OFF) g_wStatusOld[i] = g_wStatusNew[i];
		if(g_wStatusNew[i]!=STATUS_ON && g_wStatusNew[i]!=STATUS_OFF) g_wStatusOld[i] = g_wStatusNew[i];
		if(g_wStatusOld[i]!=g_wStatusNew[i])
		{
			if(g_wCountAck[i])
			{
				g_wCountAck[i]--;
				if(g_wCountAck[i]==0)
				{
					g_wStatusOld[i] = g_wStatusNew[i];
					if(g_wStatusNew[i]==STATUS_ON)
					{
						Event_AddEvent(EVENTTYPE_RUNINFO,EVENTCODE_SWITCH+i,1);
					}
					else if(g_wStatusNew[i]==STATUS_OFF)
					{
						Event_AddEvent(EVENTTYPE_RUNINFO,EVENTCODE_SWITCH+i,0);
					}
				}
			}
			else g_wCountAck[i] = 5+(i&0x0001);
		}
		else g_wCountAck[i] = 0;
#ifdef _CMYPROTECT_H
		if(g_wStatusOld[i]==STATUS_ON)
		{
			if(g_wStatusNewExt1[i]==STATUS_ON && g_wStatusNewExt2[i]==STATUS_ON)
			{
				g_dwChangtoON1 |= 1L<<i;
				g_dwChangtoON2 |= 1L<<i;
			}
		}
#endif
		if(g_wStatusOld[i]==STATUS_ON)
		{ g_wSwitchStatus1 |= (SS_IN01<<i); }
		else
		{ g_wSwitchStatus1 &= (SS_IN01<<i)^0xffff; }
	}
}

// void Switch_OnTimer1msAC(INPARAMTABLE* pInParamTable)
// {
// 	short i;
// 	if(pInParamTable==NULL) return;
// 	for(i=0;i<SWITCH_COUNT;i++)
// 	{
// 		if(g_wStatusOld[i]!=STATUS_ON && g_wStatusOld[i]!=STATUS_OFF) g_wStatusOld[i] = g_wStatusNew[i];
// 		if(g_wStatusNew[i]!=STATUS_ON && g_wStatusNew[i]!=STATUS_OFF) g_wStatusOld[i] = g_wStatusNew[i];
// 		if(g_wStatusNew[i] == STATUS_ON)
// 		{
// 			g_wCountStatus0[i] = 0;
// 			g_wCountStatus1[i]++;
// 			if(g_wCountStatus1[i]>=4)
// 			{
// 				g_wCountStatus1[i] = 5;
// 				if(g_wStatusOld[i]!=g_wStatusNew[i])
// 					Event_AddEvent(pInParamTable->inparam[i].wEventType,EVENTCODE_SWITCH+i,1);
// 				g_wStatusOld[i] = STATUS_ON;
// 			}
// 		}
// 		if(g_wStatusNew[i] == STATUS_OFF)
// 		{
// 			g_wCountStatus1[i] = 0;
// 			g_wCountStatus0[i]++;
// 			if(g_wCountStatus0[i]>=20)
// 			{
// 				g_wCountStatus0[i] = 20;
// 				if(g_wStatusOld[i]!=g_wStatusNew[i])
// 					Event_AddEvent(pInParamTable->inparam[i].wEventType,EVENTCODE_SWITCH+i,0);
// 				g_wStatusOld[i] = STATUS_OFF;
// 			}
// 		}
// #ifdef _CMYPROTECT_H
// 		if(g_wStatusOld[i]==STATUS_ON)
// 		{
// 			if(g_wStatusNewExt1[i]==STATUS_ON && g_wStatusNewExt2[i]==STATUS_ON)
// 			{
// 				g_dwChangtoON1 |= 1L<<i;
// 				g_dwChangtoON2 |= 1L<<i;
// 			}
// 		}
// #endif
// 		if(g_wStatusOld[i]==STATUS_ON) g_wSwitchStatus1 |= (SS_IN01<<i);
// 		else g_wSwitchStatus1 &= (SS_IN01<<i)^0xffff;
// 	}
// }

