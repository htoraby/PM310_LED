#ifndef _MYMENU_H
#define _MYMENU_H

#define MICFG_SUBMENU		0x0001		//�˵���Ŀ����:�Ӳ˵�;
#define MICFG_PASSWORD		0x0002		//�˵���Ŀ����:�����;

#define MM_SingleLine		0x0000		//��ʾ����ͼ;
#define MM_MENUMAIN			0x0001		//��ʾ���˵�ģʽ;
#define MM_MENUSUB			0x0002		//��ʾ�Ӳ˵�ģʽ;
#define MM_MENUPAGE			0x0003		//��ʾҳ����ʾģʽ;

#define RM_TIMER1S			0x0000		//ÿ��1�붨ʱˢ��;
#define RM_PAGEENTER		0x0001		//ҳ���ʼ����ˢ��;
#define RM_PAGEUP			0x0002		//ҳ���Ϸ�����ˢ��;
#define RM_PAGEDOWN			0x0003		//ҳ���·�����ˢ��;
#define RM_PAGELEFT			0x0004		//ҳ�������ˢ��;
#define RM_PAGERIGHT		0x0005		//ҳ���Ҳ���ˢ��;
#define RM_PAGEOK			0x0006		//ҳ��ȷ�ϲ���ˢ��;
#define RM_PAGECANCEL		0x0007		//ҳ��ȡ������ˢ��;
#define RM_EXTERNAL			0x0008		//�ⲿ�����ҳ��ˢ��(��ͨ��,�¼���¼��);
#define RM_PAGEADD			0x0009		//+;
#define RM_PAGESUB			0x000a		//-;

#ifndef PAGEWAVERECORD
#define PAGEWAVERECORD		5			// �����˲��˵����к�
#endif

//�رձ���ʱ�䣬��λ����
#ifndef MENU_TIMECLOSELCD
#define MENU_TIMECLOSELCD	60			//300
#endif

extern void DrawScroll(WORD wPosX,WORD wPosY,WORD wWidth,WORD wHeight,WORD wTotalLines,WORD wLinesPerPage,WORD wCurTop);

//-----------------------------------------------------------------------------
//�ṹ����:
typedef struct _MENUITEM
{
	char* pszMenu;
	WORD wConfig;
}MENUITEM;
//pszMenu:�˵��ı�;
//wConfig:�˵���Ŀ����,���MICFG_PASSWORD��MICFG_SUBMENU;

#define SET_MENUITEM1(a) {pMenuItem->pszMenu=(char*)a;}
#define SET_MENUITEM2(a,b) {pMenuItem->pszMenu=(char*)a;pMenuItem->wConfig=b;}
//˵��:���ڼ򻯳���,��GetMenuItemMain(pMenuItem)��GetMenuItemSub(pMenuItem)������ʹ��;


//-----------------------------------------------------------------------------
extern WORD g_wMenuMode;
extern WORD g_wMenuMainCurTop;
extern WORD g_wMenuMainCurSel;
extern WORD g_wMenuMainLineMax;
extern WORD g_wMenuSubCurTop;
extern WORD g_wMenuSubCurSel;
extern WORD g_wMenuSubLineMax;
extern WORD g_wPageCount;
extern WORD g_wPageCurSel;
extern BOOL g_bPageLargeFont;
extern BOOL g_bPageHead;
extern BOOL g_bScroll;
extern BOOL g_bPageCaptureKeyCancel;
extern WORD g_wInputPassword;
extern WORD g_wInputPasswordMode;
extern WORD g_wCountCloseLCD;

extern WORD g_wMenuMainPosX;
extern WORD g_wMenuMainPosY;
extern WORD g_wMenuMainCX;
extern WORD g_wMenuMainCY;
extern BOOL g_bMenuMainLargeFont;
extern WORD g_wMenuSubPosX;
extern WORD g_wMenuSubPosY;
extern WORD g_wMenuSubCX;
extern WORD g_wMenuSubCY;
extern BOOL g_bMenuSubLargeFont;
extern BOOL g_bDisplayEvent;
extern BOOL g_bRefreshEdit;

extern void Menu_DispayEvent(void);
extern void Menu_OnInit(void);
// extern void Menu_DrawMenuMain(void);
extern void Menu_ReDrawAll(void);
extern void Menu_DisableSaveScreen(void);
extern void Menu_SetPageCount(WORD wPageCount);
extern void Menu_SetPageCurSel(WORD wPageCurSel);
extern WORD Menu_GetIndexMenuMain(void);
extern WORD Menu_GetIndexMenuSub(void);
extern void Menu_OnKeyMsg(WORD wKeyCode);
extern void Menu_OnTimer1000ms(void);
extern void Menu_OnRefreshPage(WORD wRefreshMode);
extern BOOL Menu_EnterSubMenuSetup(WORD* pData);
extern void Menu_OnKeyMsgMenuMain(WORD wKeyCode);
extern void Menu_OnKeyMsgMenuSub(WORD wKeyCode);
extern void Menu_OnKeyMsgPage(WORD wKeyCode);

// extern void iiiDrawMenuMain(void){};
// extern void iiiDrawMenuSub(void){};
// extern void iiiDrawPasswordPrompt(void){};
// extern void iiiMenuMainCursorON(void){};
// extern void iiiMenuMainCursorOFF(void){};
// extern void iiiMenuSubCursorON(void){};
// extern void iiiMenuSubCursorOFF(void){};
extern WORD Menu_GetMenuMainColor(void);
extern WORD Menu_GetMenuMainColorBK(void);
extern WORD Menu_GetMenuSubColor(void);
extern WORD Menu_GetMenuSubColorBK(void);
extern WORD Menu_GetMenuPageColor(void);
extern WORD Menu_GetMenuPageColorBK(void);
extern WORD Menu_GetMenuPasswordColor(void);
// extern void iiiGetMenuItemMain(WORD wIndexMenuMain,MENUITEM* pMenuItem){};
// extern void iiiGetMenuItemSub(WORD wIndexMenuMain,WORD wIndexMenuSub,MENUITEM* pMenuItem){};
// extern WORD iiiGetMenuMainCount(void){ return 0; };
// extern WORD iiiGetMenuSubCount(WORD wIndexMenuMain){ return 0; };

#ifndef SCROLLW
#define SCROLLW			3
#endif

// extern void Menu_SetMenuMetrics(void);
extern void Menu_DrawScrollMain(WORD wTotalLines);
extern void Menu_DrawScrollSub(WORD wTotalLines);
extern void Menu_DrawMenuSL(WORD wRefreshMode);
extern void Menu_DrawMenuMain(void);
extern void Menu_DrawMenuSub(void);
extern void Menu_DrawPasswordPrompt(void);
extern void Menu_MenuMainCursorON(void);
extern void Menu_MenuMainCursorOFF(void);
extern void Menu_MenuSubCursorON(void);
extern void Menu_MenuSubCursorOFF(void);

#endif/*_MYMENU_H*/



