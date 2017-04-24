#ifndef __KEY_H
#define __KEY_H

#define KEY_NULL			0x0000
#define KEY_UP				0x0001
#define KEY_DOWN			0x0002
#define KEY_LEFT			0x0004
#define KEY_RIGHT			0x0008
#define KEY_OK				0x0010
#define KEY_CANCEL			0x0020
//#define KEY_SETUP			KEY_OK
#define KEY_RESET			0x0040
#define KEY_ADD			    0x0080
#define KEY_SUB			    0x0100

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//说明:初始化程序;
extern void Key_OnInit(void);
//说明:定时检测按键状态;
extern void Key_OnTimer10ms(void);
//说明:设定最新的硬件格式按键码;
extern void Key_SetKeyHardCode(WORD wKeyHardCode);
//说明:设定需持续检测的按键码组合,如KEY_UP,KEY_DOWN;
extern void Key_SetKeyRepeatCode(WORD wKeyRepeatCode);
//说明:将指定的按键码送入按键码缓冲队列;
extern void Key_AddKeyQueue(WORD wKeyCode);
//说明:从按键码缓冲队列中取出最早未处理的按键码,应用程序根据按键码执行相应的操作;
extern WORD Key_GetKeyQueue(void);
//按键处理过程
extern void OnKeyProcess(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__KEY_H*/
/******************************************************************************
模块功能:
主要实现对按键的处理,最多支持16个按键,应用程序根据应用的方便性,可在[Main.h]使用
#define对按键码宏名进行自行重新定义,定义的名称必须和硬件实际对应,如:
使用步骤:
1.创建CMyKey的实例,建议变量名:g_key;
2.在g_hmi.OnInit()中调用OnInit();
3.在g_hmi.OnTimer10ms中调用OnTimer10ms();
4.在g_hmi.OnWhileLoop()中调用GetKeyQueue(),将得到的按键码执行相应的操作;
5.在g_hdif.OnTimer10ms()中根据硬件的信息执行SetKeyHardCode();
*/
//ThinkBoy,ShenBo,2006/04/30;
