#include <Main.h>


//-----------------------------------------------------------------------------
void Menu_GetMenuItemMain(WORD wIndexMenuMain,MENUITEM* pMenuItem)
{
    switch(wIndexMenuMain)
    {
    case  0: SET_MENUITEM2("  1. 交流采样", MICFG_SUBMENU); break;
    case  1: SET_MENUITEM1("  2. 遥信开入"); break;
    case  2: SET_MENUITEM1("  3. 实时波形"); break;
//     case  3: SET_MENUITEM1("  4.\1矢量图形"); break;
    case  3: SET_MENUITEM1("  4. 事件记录"); break;
    case  4: SET_MENUITEM1("  5. 故障录波"); break;
//     case  6: SET_MENUITEM1("  7.\1定值查看"); break;
    case  5: SET_MENUITEM1("  6. 设备信息"); break;
    case  6: SET_MENUITEM2("  7. 参数设置",MICFG_SUBMENU|MICFG_PASSWORD); break;
    case  7: SET_MENUITEM1("  8. 液晶调节"); break;
    }
}

void Menu_GetMenuItemSub(WORD wIndexMenuMain,WORD wIndexMenuSub,MENUITEM* pMenuItem)
{
	if(wIndexMenuMain==0)
	{
		switch(wIndexMenuSub)
		{
		case 0: SET_MENUITEM1(" 1. \1一次值"); break;
		case 1: SET_MENUITEM1(" 2. \1二次值"); break;
		case 2: SET_MENUITEM1(" 3. \1电度量"); break;
		}
	}
	else if(wIndexMenuMain==6)
	{
		switch(wIndexMenuSub)
		{
		case  0: SET_MENUITEM1(" 1. \1压板设置"); break;
		case  1: SET_MENUITEM1(" 2. \1定值设置"); break;
		case  2: SET_MENUITEM1(" 3. \1通信参数"); break;
        case  3: SET_MENUITEM1(" 4. \1电度设置"); break;
		case  4: SET_MENUITEM1(" 5. \1时间设置"); break;
		case  5: SET_MENUITEM1(" 6. \1开出传动"); break;
		case  6: SET_MENUITEM1(" 7. \1精度设置"); break;
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
