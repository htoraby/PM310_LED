#ifndef _MYPAGE_H
#define _MYPAGE_H

#ifdef __cplusplus
extern "C" {
#endif

extern void Page_SetMetrics(WORD wOffsetY,WORD wPageLineNum);
extern WORD Page_GetLinePosY(void);
extern void Page_DrawRTWaveGrid1(WORD wPosX,WORD wPosY,WORD wCX,WORD wCY);
//˵��:��ָ��λ�û�ʵʱ����;
extern void Page_DrawRTWave1(WORD wPosX,WORD wPosY,WORD wCX,WORD wCY,WORD wDFTIndex,WORD wScale);

extern WORD g_wPageLineNum;            // ÿҳ����
extern WORD g_wPageOffsetY;                // ��ʼƫ��
extern WORD g_wPageLines;              // �м���


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*_MYPAGE_H*/
/******************************************************************************
ģ�鹦��:
ʵ��ҳ��Ŀ��ʽ��ʾ;
ʹ�ò���:
1.����OnInit()��OnInitExt()����ָ����ز���;
2.����AddLabelData()�������ӱ�ǩ��������Ŀ;
3.����g_lcd.m_wAutoPosY,g_lad.m_wAutoEnter�����趨��ʼ��ʾ��Y������о�;
4.����LabelDataOut()������ʾ��ǩ��������Ŀ;
5.����LabelDataOut()��,��ģ���Զ������Ŀ����,��˲���Ҫ�ظ�����OnInit()����;
*/
