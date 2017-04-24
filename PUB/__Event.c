#include <Main.h>

WORD g_wEventTableCountNew;				//事件记录计数;
static WORD s_wEventTableCountOld;				//事件记录计数(跟踪更新用);
static WORD s_wEventReadCntOld = 0;
EVENTTABLE g_eventTable;			//事件记录表;

//-----------------------------------------------------------------------------


void Event_OnInit(void)
{
	s_wEventTableCountOld = 0;
	MemoryClear((WORD*)&g_eventTable,SIZEOFWORD(EVENTTABLE));
	Event_ReadEventTable();
	g_wEventTableCountNew = s_wEventTableCountOld;
    if(g_wEventTableCountNew-g_eventTable.wEventReadCnt>EVENT_COUNT)
        g_eventTable.wEventReadCnt = g_wEventTableCountNew - EVENT_COUNT;
    if(g_eventTable.wEventReadCnt>g_wEventTableCountNew)
        g_eventTable.wEventReadCnt = 0;
}

void Event_OnTimer1000ms(void)
{
//     if(g_wEventTableCountNew-g_eventTable.wEventReadCnt>EVENT_COUNT)
//         g_eventTable.wEventReadCnt = g_wEventTableCountNew - EVENT_COUNT;
//     if(g_eventTable.wEventReadCnt>g_wEventTableCountNew)
//         g_eventTable.wEventReadCnt = 0;

    if((s_wEventTableCountOld!=g_wEventTableCountNew)
        || (s_wEventReadCntOld!=g_eventTable.wEventReadCnt))
    {
        s_wEventTableCountOld = g_wEventTableCountNew;
        s_wEventReadCntOld = g_eventTable.wEventReadCnt;
        Event_WriteEventTable();
    }
}

void Event_OnInitDevice(void)
{
	g_wEventTableCountNew = 0;
	MemoryClear((WORD*)&g_eventTable,SIZEOFWORD(EVENTTABLE));
}

void Event_AddEvent(WORD wEventType,WORD wEventCode,WORD wEventData)
{
	EVENT* pEvent;
	if(wEventType==EVENTTYPE_NULL||wEventType>=EVENTTYPE_NOTUSED) return;
	pEvent = &g_eventTable.event[g_wEventTableCountNew%EVENT_COUNT];
	g_wEventTableCountNew++;
    if(g_wEventTableCountNew-g_eventTable.wEventReadCnt>EVENT_COUNT)
        g_eventTable.wEventReadCnt = g_wEventTableCountNew - EVENT_COUNT;
    if(g_eventTable.wEventReadCnt>g_wEventTableCountNew)
        g_eventTable.wEventReadCnt = 0;
	pEvent->time = g_deviceTime;
	pEvent->wType = wEventType;
	pEvent->wCode = wEventCode;
	pEvent->wData = wEventData;
	if(wEventType==EVENTTYPE_ALARMED) SetAlarmedFlag;
	if(wEventType==EVENTTYPE_TRIPPED) SetTrippedFlag;
	JumpToEventDisplay;
}

EVENT* Event_GetEvent(WORD wIndexEvent)
{
	return &g_eventTable.event[wIndexEvent%EVENT_COUNT];
}

void Event_ReadEventTable(void)
{
#ifdef EEPROMADDR_EventTable
// 	EEPROM_ReadBlock(EEPROMADDR_EventTable,&s_wEventTableCountOld,(WORD*)&g_eventTable,SIZEOFWORD(g_eventTable));
    Flash_ReadBlock(EEPROMADDR_EventTable,&s_wEventTableCountOld,(WORD*)&g_eventTable,SIZEOFWORD(g_eventTable));
#endif
}

void Event_WriteEventTable(void)
{
#ifdef EEPROMADDR_EventTable
// 	EEPROM_WriteBlock(EEPROMADDR_EventTable,&s_wEventTableCountOld,(WORD*)&g_eventTable,SIZEOFWORD(g_eventTable));
	Flash_WriteBlock(EEPROMADDR_EventTable,&s_wEventTableCountOld,(WORD*)&g_eventTable,SIZEOFWORD(g_eventTable));
#endif
}
