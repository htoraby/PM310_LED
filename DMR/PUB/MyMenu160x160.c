#include <Main.h>


//-----------------------------------------------------------------------------
void Menu_SetMenuMetrics(void)
{
	g_wMenuMainLineMax = 12;
	g_wMenuSubLineMax = 12;
	g_wMenuMainPosX = 0;
	g_wMenuMainPosY = 2;
	g_wMenuMainCX = 160 -SCROLLW-1;
	g_wMenuMainCY = 13;
	g_bMenuMainLargeFont = FALSE;
	g_wMenuSubPosX = 0;
	g_wMenuSubPosY = 2;
	g_wMenuSubCX = 160 -SCROLLW-1;
	g_wMenuSubCY = 13;
	g_bMenuSubLargeFont = FALSE;
}
