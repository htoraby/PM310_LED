#ifndef __EVENT_H
#define __EVENT_H

#ifndef EVENT_COUNT
#define EVENT_COUNT			8
#endif

#define EVENTTYPE_NULL		0x0000		//空事件
#define EVENTTYPE_SWITCH	0x0001		//开关变位事件
#define EVENTTYPE_RUNINFO	0x0002		//运行信息事件
#define EVENTTYPE_ALARMED	0x0003		//设备告警事件
#define EVENTTYPE_TRIPPED	0x0004		//设备故障事件
#define EVENTTYPE_OPERATE	0x0005		//操作记录事件
#define EVENTTYPE_ERRORED	0x0006		//自检异常事件
#define EVENTTYPE_NOTUSED	0x0007		//无效事件

#define EVENTCODE_NULL					//空事件代码
#define EVENTCODE_OTHER		0x0100		//设备相关事件
#define EVENTCODE_SWITCH	0x0200		//开关量变位事件
#define EVENTCODE_ALARMED	0x0300		//告警检测事件
#define EVENTCODE_PROTECT	0x0400		//保护动作事件
#define EVENTCODE_ERRORED	0x0500		//自检异常事件
#define EVENTCODE_LAD		0x0600		//梯形图事件
#define EVENTCODE_REMOTE	0x0700		//遥控操作事件

#define EVENT_SIZE			10			//单一一条事件的长度


//-----------------------------------------------------------------------------
typedef struct _EVENT
{
	DEVICETIME time;				//事件发生的时间戳;
	WORD wType;						//事件类型;
	WORD wCode;						//事件代码;
	WORD wData;						//相关数据,其含义取决于事件代码;
}EVENT;


//-----------------------------------------------------------------------------
typedef struct EVENTTABLE
{
	EVENT event[EVENT_COUNT];		// 事件记录表;
    WORD wEventReadCnt;             // 读取计数
}EVENTTABLE;

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//说明:初始化程序;
extern void Event_OnInit(void);
//说明:定时服务程序,用于检测新增事件记录并自动保存;
extern void Event_OnTimer1000ms(void);
//说明:初始化设备,自动清除事件记录;
extern void Event_OnInitDevice(void);
//说明:增加事件记录,wEventType:事件类型,范围1-6,wEventCode:事件代码,wEventData:相关数据;
extern void Event_AddEvent(WORD wEventType,WORD wEventCode,WORD wEventData);
//说明:返回指定位置的事件记录;
extern EVENT* Event_GetEvent(WORD wIndexEvent);
//说明:读事件记录表;
extern void Event_ReadEventTable(void);
//说明:写事件记录表;
extern void Event_WriteEventTable(void);

extern WORD g_wEventTableCountNew;
extern EVENTTABLE g_eventTable;			//事件记录表;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__EVENT_H*/
/******************************************************************************
模块功能:
主要实现对各种事件记录的管理,按循环队列的方式增加事件记录,计数值m_wCountNew初始值
为0(装置第一次运行),每增加一个事件,计数自动加一;事件记录按m_wCountNew%EVENT_COUNT
的方式访问;显示事件记录时建议丢弃最早的1-2个事件记录,以防止临界冲突;
使用步骤:
1.根据应用要求定义EVENT_COUNT;
2.在g_app.OnInit()中调用OnInit(),以完成计数值初始化,并自动装入事件记录表;
3.其它用户程序直接调用AddEvent(wEventType,wEventCode,wEventData)函数增加事件记录;
4.在g_app.OnTimer1000ms()中调用OnTimer1000ms(),以检测检测新增事件并自动保存;
5.主控程序定时将m_wCountNew保存到g_deviceInfo.wCountEventTable中;
6.在页面显示程序显示事件记录表;
*/

