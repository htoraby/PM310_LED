#include <Main.h>

CMyLCD_UC1698U s_lcdUC1698U;
#if LCD_CXDOT>160
CMyLCD_SED1335 s_lcdSED1335;
#endif

//-----------------------------------------------------------------------------
void CMyLCDiBCU3::HWRest(void)
{
	switch(g_wPanelTest)
	{
#if LCD_CXDOT>160
	case 0x0055: s_lcdSED1335.HWRest(); break;
#endif
	case 0x0054:
	default:
		s_lcdUC1698U.HWRest();
		break;
	}
}

void CMyLCDiBCU3::iiiSetup(void)
{
	switch(g_wPanelTest)
	{
#if LCD_CXDOT>160
	case 0x0055: s_lcdSED1335.iiiSetup(); break;
#endif
	case 0x0054:
	default:
		s_lcdUC1698U.iiiSetup();
		break;
	}
}

void CMyLCDiBCU3::iiiFlush(void)
{
	switch(g_wPanelTest)
	{
#if LCD_CXDOT>160
	case 0x0055: s_lcdSED1335.iiiFlush(); break;
#endif
	case 0x0054:
	default:
		s_lcdUC1698U.iiiFlush();
		break;
	}
}
