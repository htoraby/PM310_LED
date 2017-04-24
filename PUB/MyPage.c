#include <Main.h>

WORD g_wPageLineNum;            // 每页行数
WORD g_wPageOffsetY;                // 起始偏移
WORD g_wPageLines = 0;              // 行计数

void Page_SetMetrics(WORD wOffsetY,WORD wPageLineNum)
{
    g_wPageLineNum = wPageLineNum;			// 每页行数
    g_wPageOffsetY = wOffsetY;					// 页眉高度
    g_wPageLines = 0;							// 行计数
}

WORD Page_GetLinePosY(void)
{
    short nLineIndex = (short)(g_wPageLines-g_wPageCurSel*g_wPageLineNum);
    if(nLineIndex>=0 && nLineIndex<g_wPageLineNum) return (WORD)(g_wPageOffsetY+nLineIndex*g_wLCDAutoEnter);
    return 0xffff;
}

void Page_DrawRTWaveGrid1(WORD wPosX,WORD wPosY,WORD wCX,WORD wCY)
{
	WORD i;
	for(i=0;i<=6;i++) LCD_DrawVLineExt((WORD)(wPosX+i*(wCX/6)),wPosY,(WORD)(wPosY+wCY),0xaa);
	for(i=0;i<=2;i++) LCD_DrawHLineExt((WORD)(wPosY+i*(wCY/2)),wPosX,(WORD)(wPosX+wCX+1),0xaa);
}

void Page_DrawRTWave1(WORD wPosX,WORD wPosY,WORD wCX,WORD wCY,WORD wDFTIndex,WORD wScale)
{
	WORD i;
	short nRTWavePosY[DFT_DOTNUM];
	WORD* pRTWaveData;
	WORD wSum;
	short nPosX1,nPosX2,nPosY1,nPosY2;

	if(wDFTIndex>=DFT_CHANNEL_HARD) return;
	pRTWaveData = &g_analogWave.wData[wDFTIndex][0];
	wSum = 0;
	wSum += pRTWaveData[0*DFT_DOTNUM/4];
	wSum += pRTWaveData[1*DFT_DOTNUM/4];
	wSum += pRTWaveData[2*DFT_DOTNUM/4];
	wSum += pRTWaveData[3*DFT_DOTNUM/4];
	wSum += 2;
	wSum >>= 2;

	wCY >>= 1;
	for(i=0;i<DFT_DOTNUM;i++)
	{
		nRTWavePosY[i] = (short)((long)(short)(pRTWaveData[i]-wSum)*(short)wCY/(short)wScale);
		if(nRTWavePosY[i]<-(short)wCY) nRTWavePosY[i] = -(short)wCY;
		if(nRTWavePosY[i]>(short)wCY) nRTWavePosY[i] = (short)wCY;
	}
	wPosY += wCY;
	for(i=0;i<2*DFT_DOTNUM;i++)
	{
		nPosY1 = nRTWavePosY[i%DFT_DOTNUM];
		nPosY2 = nRTWavePosY[(i+1)%DFT_DOTNUM];
		if(nPosY1>=(short)wCY&&nPosY2>=(short)wCY) continue;
		if(nPosY1<=-(short)wCY&&nPosY2<=-(short)wCY) continue;
		nPosX1 = i*wCX/(DFT_DOTNUM*2);
		nPosX2 = (i+1)*wCX/(DFT_DOTNUM*2);
		LCD_DrawXLine((WORD)(wPosX+nPosX1),(WORD)(wPosY-nPosY1),(WORD)(wPosX+nPosX2),(WORD)(wPosY-nPosY2));
	}
}

