#include <Main.h>

static WAVERECORD s_waveRecord[WAVERECORD_WAVENUM];
static WORD s_wWRDotNo = 0;

WORD g_wWRCountNew = 0;
WORD g_wWRCountOld = 0;
WORD g_wWRData[WAVERECORD_DATASIZE];

//-----------------------------------------------------------------------------
void WaveRecord_OnInit(void)
{
    short i;

    g_wWRCountOld = 0;
    MemoryClear(g_wWRData,WAVERECORD_DATASIZE);
    for(i=0;i<WAVERECORD_WAVENUM;i++)
    {
        WAVERECORD* pWaveRecord = WaveRecord_GetRecord(i);
        if(pWaveRecord!=NULL) MemoryClear((WORD*)pWaveRecord,SIZEOFWORD(WAVERECORD));
    }
    WaveRecord_ReadRecord();
    g_wWRCountNew = g_wWRCountOld;
    s_wWRDotNo = 0;
}

void WaveRecord_OnTimer1000ms(void)
{
    while(g_wWRCountOld!=g_wWRCountNew)
    {
//        g_wWRCountOld = g_wWRCountNew;
//        WaveRecord_WriteRecord();
        g_wWRCountOld++;
        WaveRecord_WriteRecord();
    }
}

void WaveRecord_StartRecord(void)
{
//    short i;
    WAVERECORD* pWaveRecord = WaveRecord_GetRecord(g_wWRCountNew);
    if(pWaveRecord==NULL) return;
    pWaveRecord->wRecordStatus = WRS_RECORDING;
    pWaveRecord->wFreezeDotNo = 0xffff;
    pWaveRecord->wCycleFlag = 0;
//     pWaveRecord->nK[i] = g_regulateSet.regulate[DFT_Ua].nRegulateR
    pWaveRecord->wOffset = 2034;
    MyApp_SetWaveRecordK(pWaveRecord);
    s_wWRDotNo = 0;
}

void WaveRecord_FreezeRecord(void)
{
    WAVERECORD* pWaveRecord = WaveRecord_GetRecord(g_wWRCountNew);
    if(pWaveRecord==NULL) return;
    if(pWaveRecord->wFreezeDotNo==0xffff)
    {
        pWaveRecord->wFreezeDotNo = (s_wWRDotNo+DFT_DOTNUM*5)%WAVERECORD_DOTNUM;
        pWaveRecord->timeFreeze = g_deviceTime;
    }
}

void WaveRecord_OnRecord(void)
{
    short i;
    WAVERECORD* pWaveRecord = WaveRecord_GetRecord(g_wWRCountNew);
    if(pWaveRecord==NULL) return;
    for(i=0;i<WAVERECORD_DATASIZE;i++) pWaveRecord->wData[s_wWRDotNo][i] = g_wWRData[i];
    s_wWRDotNo++;
    if(s_wWRDotNo>=WAVERECORD_DOTNUM)
    {
        s_wWRDotNo = 0;
        pWaveRecord->wCycleFlag = 1;
    }
    if(pWaveRecord->wFreezeDotNo!=0xffff && s_wWRDotNo==pWaveRecord->wFreezeDotNo)
    {
        pWaveRecord->wRecordStatus = WRS_RECORDED;
        g_wWRCountNew++;
        //    g_table103.UpdateWaveRecord(m_wCountNew);
        WaveRecord_StartRecord();
    }
}

WAVERECORD* WaveRecord_GetRecord(WORD wWaveRecordNo)
{
    wWaveRecordNo %= WAVERECORD_WAVENUM;
    return &s_waveRecord[wWaveRecordNo];
}

void WaveRecord_ReadRecord(void)
{
#ifdef EEPROMADDR_WaveRecordX
    short i;
    WORD wCountOld = 0;
    for(i=0;i<WAVERECORD_WAVENUM;i++)
    {
        WAVERECORD* pWaveRecord = WaveRecord_GetRecord(i);
        if(pWaveRecord==NULL) continue;
        Flash_ReadBlock(EEPROMADDR_WaveRecordX(i),&wCountOld,(WORD*)pWaveRecord,SIZEOFWORD(WAVERECORD));
        if(g_wWRCountOld<wCountOld) g_wWRCountOld = wCountOld;
    }
#endif
}

void WaveRecord_WriteRecord(void)
{
#ifdef EEPROMADDR_WaveRecordX
    WORD i = (g_wWRCountOld+WAVERECORD_WAVENUM-1)%WAVERECORD_WAVENUM;
    WAVERECORD* pWaveRecord = WaveRecord_GetRecord(i);
    if(pWaveRecord==NULL) return;
    Flash_WriteBlock(EEPROMADDR_WaveRecordX(i),&g_wWRCountOld,(WORD*)pWaveRecord,SIZEOFWORD(WAVERECORD));
#endif
}
