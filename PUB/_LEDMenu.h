#define MM_DATA					0x0000
#define MM_PASSWORD				0x0001
#define MM_SETUP				0x0002

#ifndef SREENSAVETIME
#define SREENSAVETIME				(5*60*100)				// 5∑÷÷”
#endif

enum PASSWORD
{
	 PASSWORD_NULL = 0x0000
	,PASSWORD_LEVEL1 = 0x1111
	,PASSWORD_LEVEL2 = 0x2222
	,PASSWORD_LEVEL3 = 0x3333
};

extern unsigned short g_wMenuMode;
extern unsigned short g_wPageCount;
extern unsigned short g_wPageCurSel;
extern unsigned short g_bAutoCycle;
extern unsigned short g_wPassword;
extern WORD g_wPasswordLevel;

extern unsigned short g_wCycleCurSel;
extern unsigned short g_wAutoCycleCount;
extern void SetPageCount(unsigned short wPageCount);
extern void SetPageCurSel(unsigned short wPageCurSel);
extern void OnInitMenu(void);
extern void OnMenuTimer10ms(void);
extern void OnTaskMenu(void);
extern void OnTaskMenuKey(unsigned short wKeyCode);
extern void OnRefreshPage(void);
extern void EnterPageSetup(void);
extern void OnRefreshPageData(void);
extern void OnRefreshPagePassword(void);
extern void OnRefreshPageSetup(void);
