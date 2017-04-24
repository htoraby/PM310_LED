#define MODULE__SWITCH_H

#define SS_IN01			0x0001		//状态屏蔽码:IN01;
#define SS_IN02			0x0002		//状态屏蔽码:IN02;
#define SS_IN03			0x0004		//状态屏蔽码:IN03;
#define SS_IN04			0x0008		//状态屏蔽码:IN04;
#define SS_IN05			0x0010		//状态屏蔽码:IN05;
#define SS_IN06			0x0020		//状态屏蔽码:IN06;
#define SS_IN07			0x0040		//状态屏蔽码:IN07;
#define SS_IN08			0x0080		//状态屏蔽码:IN08;
#define SS_IN09			0x0100		//状态屏蔽码:IN09;
#define SS_IN10			0x0200		//状态屏蔽码:IN10;
#define SS_IN11			0x0400		//状态屏蔽码:IN11;
#define SS_IN12			0x0800		//状态屏蔽码:IN12;
#define SS_IN13			0x1000		//状态屏蔽码:IN13;
#define SS_IN14			0x2000		//状态屏蔽码:IN14;
#define SS_IN15			0x4000		//状态屏蔽码:IN15;
#define SS_IN16			0x8000		//状态屏蔽码:IN16;

#define SWITCHSetStatus(wIndex,wStatus)											\
	do																			\
	{																			\
		if(wStatus==STATUS_NULL||wStatus==STATUS_OFF||wStatus==STATUS_ON)		\
		{																		\
			g_wStatusNew[wIndex]     = wStatus;									\
			g_wStatusNewExt1[wIndex] = wStatus;									\
			g_wStatusNewExt2[wIndex] = wStatus;									\
		}																		\
	}																			\
	while(0)

//-----------------------------------------------------------------------------
// typedef struct _INPARAM
// {
// 	WORD wEventType;				//开关量状态发生变化时触发的事件类型;
// 	WORD wAckDelayTime;				//开关量状态变化确认时间,相当于软件滤波功能;
// //  	WORD wszName[21];				//开关量名称,最多16个字符或8个汉字;
// //  	WORD wszStatus0[9];				//开关量状态0时名称,最多8个字符或4个汉字;
// //  	WORD wszStatus1[9];				//开关量状态1时名称,最多8个字符或4个汉字;
// 	WORD wName;
// 	WORD wStatus0;
// 	WORD wStatus1;
// }INPARAM;
// 
// typedef struct _INPARAMTABLE
// {
// 	INPARAM inparam[SWITCH_COUNT];
// }INPARAMTABLE;


#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//说明:设定指定开关量的参数;
// extern void Switch_SetInParam(INPARAM* pInParam,WORD wEventType,WORD wName,WORD wStatus0,WORD wStatus1);
// 说明:初始化程序;
extern void Switch_OnInit(void);
// 说明:定时服务程序(严格)调用,用于确认状态;wIndex:开关量索引号(只用于事件记录和开关量保护);pInParam:开关量参数;
extern void Switch_OnTimer1ms(void);
// extern void Switch_OnTimer1msDC(INPARAMTABLE* pInParamTable);
// extern void Switch_OnTimer1msAC(INPARAMTABLE* pInParamTable);

// extern INPARAMTABLE g_inparamTable;

extern WORD g_wStatusNew[SWITCH_COUNT];				// 确认前状态;
extern WORD g_wStatusNewExt1[SWITCH_COUNT];			// 确认前状态,扩展以防止误动作;
extern WORD g_wStatusNewExt2[SWITCH_COUNT];			// 确认前状态,扩展以防止误动作;
extern WORD g_wSwitchStatus1;
extern WORD g_wSwitchStatus2;
extern DWORD g_dwChangtoON1;						// 本周期内变为高电平的开关量;
// 主要用于开关量保护,跳闸后清除;
extern DWORD g_dwChangtoON2;						// 值与m_dwChangtoON1相同，用于确保开关量保护不误动
extern WORD g_wStatusOld[SWITCH_COUNT];				// 确认后状态;
extern WORD g_wCountAck[SWITCH_COUNT];				// 确认计数;
extern WORD g_wCountStatus0[SWITCH_COUNT];				// 0状态计数
extern WORD g_wCountStatus1[SWITCH_COUNT];				// 1状态计数


#ifdef __cplusplus
}
#endif /* extern "C" */

/******************************************************************************
模块功能:
实现开关量输入管理,能自动根据设定的参数要求产生各种事件,并支持可设长度的变位确认时间;
使用步骤:
1.根据应用要求定义SWITCH_COUNT;
2.创建SWITCH_COUNT个CMySwitch的实例,建议变量名:g_switch[SWITCH_COUNT];
3.在用户参数初始化程序中通过调用SetInParam()预设开关量参数;
4.在g_app.OnInit()中调用OnInit();
5.在g_app.OnTimer1ms()中调用OnTimer1ms();
6.在g_hdif.OnTimer1ms()中将新的确认前状态从硬件读出后通过Setatus(wStatus)进行设定;
7.其它用户程序通过调用GetStatus()得到经确认后的开关量输入状态;
8.脉冲电度的计数通过GetCountON()读出;
*/
//ThinkBoy,ShenBo,2006/04/30;
