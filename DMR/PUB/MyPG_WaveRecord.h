#ifndef CMYPG_WAVERECORD_H
#define CMYPG_WAVERECORD_H

#define PGWAVE_UP           0x01
#define PGWAVE_DOWN         0x02

#ifndef WAVERECORDCHANMEL
#define WAVERECORDCHANMEL   7
#endif


// extern void PGWR_SetProperty(WORD wLCDCX,BOOL bDrawRect);
extern void PGWR_SetMetrics(WORD wPosStart,WORD wLinePix,WORD wHeight);
extern void PGWR_OnRefreshPage(WORD wRefreshMode);
extern WORD PGWR_OnKeyMsg(WORD wKeyCode);
extern void PGWR_OnRefreshPageWaveSelect(WORD wRefreshMode);
extern void PGWR_OnRefreshPageWaveDisplay(WORD wRefreshMode);
extern void PGWR_GetWaveDataSwitch(WORD wStartDotNo);
extern void PGWR_GetWaveDataAnalog(WORD wStartDotNo,WORD wIndex);
extern void PGWR_GotoNextPage(WORD wDir);
extern void PGWR_DrawScrollBar(void);
extern void PGWR_DrawWaveSwitch(WORD wDots);
extern void PGWR_DrawWaveAnalog(WORD wChannel,WORD wDots);

extern MyData* g_pPGWRData[8];

//-----------------------------------------------------------------------------
// class CMyPG_WaveRecord
// {
// protected:
//     WORD m_wPAGE_DOTNUM;
//     WORD m_wPosYStart;          // 模拟量位置Y起始
//     WORD m_wLinePix;            // 每个通道高度
//     WORD m_wHeight;
//     BOOL m_bDrawRect;
// protected:
//     WORD m_wCountWaveRecordOld;
//     WORD m_wWaveNo[WAVERECORD_WAVENUM-1];
//     WORD m_wWaveCount;
//     WORD m_wChannelSelect;
//     WAVERECORD* m_pWaveRecord;
//     WORD m_wWaveData[WAVEDATABUFF];
// public:
//     CMyData* m_pData[8];


#endif/*CMYPG_WAVERECORD_H*/
