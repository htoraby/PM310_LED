#include <Main.h>


//-----------------------------------------------------------------------------
void Menu_GetMenuItemMain(WORD wIndexMenuMain,MENUITEM* pMenuItem)
{
    switch(wIndexMenuMain)
    {
    case  0: SET_MENUITEM2("  1. ��������", MICFG_SUBMENU); break;
    case  1: SET_MENUITEM1("  2. ң�ſ���"); break;
    case  2: SET_MENUITEM1("  3. ʵʱ����"); break;
//     case  3: SET_MENUITEM1("  4.\1ʸ��ͼ��"); break;
    case  3: SET_MENUITEM1("  4. �¼���¼"); break;
    case  4: SET_MENUITEM1("  5. ����¼��"); break;
//     case  6: SET_MENUITEM1("  7.\1��ֵ�鿴"); break;
    case  5: SET_MENUITEM1("  6. �豸��Ϣ"); break;
    case  6: SET_MENUITEM2("  7. ��������",MICFG_SUBMENU|MICFG_PASSWORD); break;
    case  7: SET_MENUITEM1("  8. Һ������"); break;
    }
}

void Menu_GetMenuItemSub(WORD wIndexMenuMain,WORD wIndexMenuSub,MENUITEM* pMenuItem)
{
	if(wIndexMenuMain==0)
	{
		switch(wIndexMenuSub)
		{
		case 0: SET_MENUITEM1(" 1. \1һ��ֵ"); break;
		case 1: SET_MENUITEM1(" 2. \1����ֵ"); break;
		case 2: SET_MENUITEM1(" 3. \1�����"); break;
		}
	}
	else if(wIndexMenuMain==6)
	{
		switch(wIndexMenuSub)
		{
		case  0: SET_MENUITEM1(" 1. \1ѹ������"); break;
		case  1: SET_MENUITEM1(" 2. \1��ֵ����"); break;
		case  2: SET_MENUITEM1(" 3. \1ͨ�Ų���"); break;
        case  3: SET_MENUITEM1(" 4. \1�������"); break;
		case  4: SET_MENUITEM1(" 5. \1ʱ������"); break;
		case  5: SET_MENUITEM1(" 6. \1��������"); break;
		case  6: SET_MENUITEM1(" 7. \1��������"); break;
		}
	}
}

WORD Menu_GetMenuMainCount(void)
{
	return 8;
}

WORD Menu_GetMenuSubCount(WORD wIndexMenuMain)
{
	if(wIndexMenuMain==0) return 3;
	else if(wIndexMenuMain==6)
	{
		switch(g_wInputPasswordMode)
		{
		case PASSWORD_LEVEL1:
		case PASSWORD_LEVEL2: return 7;
// 		case PASSWORD_LEVEL1: return 1;
// 		case PASSWORD_LEVEL2: return 7;
// 		case PASSWORD_LEVEL3: return 7;
		}
	}
	return 0;
}
