#ifndef __OUTPUT_H
#define __OUTPUT_H

#define OUTPUT_TM_00		0			//测试模式:全分
#define OUTPUT_TM_01		1			//测试模式:先分后合
#define OUTPUT_TM_10		2			//测试模式:先合后分
#define OUTPUT_TM_11		3			//测试模式:全合

typedef struct _MyOutput
{
	WORD m_wStatus1;					//输出量状态1;
	WORD m_wStatus2;					//输出量状态2;
	WORD m_wStatus3;					//输出量状态3;
	WORD m_wCountPulse;					//脉冲式动作时计数;
	WORD m_wCountTestMode;				//测试动作时计数;
	WORD m_wTestMode;					//测试模式;
}MyOutput;

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//说明:初始化程序,将状态初始化为分;
extern void Output_OnInit(MyOutput* pthis);
//说明:定时服务程序(严格)调用,用于对状态进行刷新;
extern void Output_OnTimer10ms(MyOutput* pthis);
//说明:电平式动作;wStatus:STATUS_OFF分;STATUS_ON:合;
extern void Output_SetLevel(MyOutput* pthis,WORD wStatus);
//说明:脉冲式动作,先合,经wDelay10ms后自动分;
extern void Output_SetPulse(MyOutput* pthis,WORD wDelay10ms);
//说明:进入测试模式,测试模式累计延时2秒后自动返回;
extern void Output_EnterTest(MyOutput* pthis,WORD wTestMode,WORD wCountTestMode);
//说明:返回当前状态,TRUE:表示动作;FALSE:未动作;
extern BOOL Output_IsOutputValid(MyOutput* pthis);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__OUTPUT_H*/

/******************************************************************************
模块功能:
实现输出量(指示灯或继电器)管理;
使用步骤:
1.创建CMyOutput实例,建议变量名:g_lightXXX或g_relayXXX;
2.在g_app.OnInit()中调用OnInit();
3.在g_app.OnTimer10ms()中调用OnTimer10ms();
4.通过SetLevel()或SetPulse()设定输出量状态;
5.通过IsOutputValid()得到继电器状态并输出;
6.通过EnterTest()对输出量进行测试,测试支持四种模式;
*/
