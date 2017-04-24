#ifndef _MYPAGE_H
#define _MYPAGE_H

#ifdef __cplusplus
extern "C" {
#endif

extern void Page_SetMetrics(WORD wOffsetY,WORD wPageLineNum);
extern WORD Page_GetLinePosY(void);
extern void Page_DrawRTWaveGrid1(WORD wPosX,WORD wPosY,WORD wCX,WORD wCY);
//说明:在指定位置画实时波形;
extern void Page_DrawRTWave1(WORD wPosX,WORD wPosY,WORD wCX,WORD wCY,WORD wDFTIndex,WORD wScale);

extern WORD g_wPageLineNum;            // 每页行数
extern WORD g_wPageOffsetY;                // 起始偏移
extern WORD g_wPageLines;              // 行计数


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*_MYPAGE_H*/
/******************************************************************************
模块功能:
实现页面的框架式显示;
使用步骤:
1.调用OnInit()或OnInitExt()函数指定相关参数;
2.调用AddLabelData()函数增加标签和数据条目;
3.设置g_lcd.m_wAutoPosY,g_lad.m_wAutoEnter变量设定开始显示的Y坐标和行距;
4.调用LabelDataOut()函数显示标签和数据条目;
5.调用LabelDataOut()后,本模块自动清除条目内容,因此不需要重复调用OnInit()函数;
*/
