#include "main.h"

//-----------------------------------------------------------------------------------
void MyHMI_OnInit(void)
{
	OnInitLED();
	Key_OnInit();
	OnInitMenu();
	MemoryClear((WORD*)&g_Light,SIZEOFWORD(LIGHT));
	MyHMI_OnInitSub();
}

void MyHMI_OnTimer10ms(void)
{
	Key_SetKeyRepeatCode(KEY_REPEATCODE);
	Key_OnTimer10ms();
	OnMenuTimer10ms();
	MyHMI_OnTimer10msSub();
}

void MyHMI_OnTimer1000ms(void)
{
	OnTaskMenu();
	MyHMI_OnTimer1000msSub();
}

void MyHMI_OnWhileLoop(void)
{
	unsigned short wKeyCode;
	wKeyCode = Key_GetKeyQueue();
	if(wKeyCode!=KEY_NULL) OnTaskMenuKey(wKeyCode);
}

