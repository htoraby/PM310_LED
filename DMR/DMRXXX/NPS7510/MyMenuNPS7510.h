#ifndef MYMENUiBCU2140L_H
#define MYMENUiBCU2140L_H

//-----------------------------------------------------------------------------
extern void Menu_GetMenuItemMain(WORD wIndexMenuMain,MENUITEM* pMenuItem);
extern void Menu_GetMenuItemSub(WORD wIndexMenuMain,WORD wIndexMenuSub,MENUITEM* pMenuItem);
extern WORD Menu_GetMenuMainCount(void);
extern WORD Menu_GetMenuSubCount(WORD wIndexMenuMain);

#endif/*MYMENUiBCU2140L_H*/
