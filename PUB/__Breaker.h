//-----------------------------------------------------------------------------------------------------
//									Copyright (c) 2009 by ThinkBoy.
//										All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __BREAKER_H
#define __BREAKER_H

#define MODULE__BREAKER_H

#define BOMODE_LOCAL			1			//断路器操作模式:本地;
#define BOMODE_REMOTE			2			//断路器操作模式:遥控;
#define BOMODE_PROTECT			3			//断路器操作模式:保护;

#define BOSTATUS_NULL			0x0000		//断路器状态:无效,一般为开入电源异常引起;
#define BOSTATUS_OPENED			0x3333		//断路器状态:分位;
#define BOSTATUS_CLOSED			0x5555		//断路器状态:合位;
#define BOSTATUS_TOCLOSED		0x3355		//断路器状态:分->合;
#define BOSTATUS_TOOPENED		0x5533		//断路器状态:合->分;

#ifndef BOALARM_DELAYKM
#define BOALARM_DELAYKM			50			//控制电源断线告警延时0.5秒;
#endif
#ifndef BOALARM_DELAYCLOSE
#define BOALARM_DELAYCLOSE		3000		//合闸回路断线告警延时30秒;
#endif
#ifndef BOALARM_DELAYOPEN
#define BOALARM_DELAYOPEN		100			//跳闸回路断线告警延时1秒;
#endif

#ifndef EVENTCODE_LOCALBO
#define EVENTCODE_LOCALBO		(EVENTCODE_OTHER+0x00)		//本地操作断路器;
#endif
#ifndef EVENTCODE_REMOTEBO
#define EVENTCODE_REMOTEBO		(EVENTCODE_OTHER+0x01)		//遥控操作断路器;
#endif
#ifndef EVENTCODE_ALARMKM
#define EVENTCODE_ALARMKM		(EVENTCODE_ALARMED+0x10)	//控制电源失电;
#endif
#ifndef EVENTCODE_ALARMCLOSE
#define EVENTCODE_ALARMCLOSE	(EVENTCODE_ALARMED+0x11)	//合闸回路断线;
#endif
#ifndef EVENTCODE_ALARMOPEN
#define EVENTCODE_ALARMOPEN		(EVENTCODE_ALARMED+0x12)	//跳闸回路断线;
#endif
#ifndef EVENTCODE_ERRORCLOSE
#define EVENTCODE_ERRORCLOSE	(EVENTCODE_ALARMED+0x13)	//合闸拒动;
#endif
#ifndef EVENTCODE_ERROROPEN
#define EVENTCODE_ERROROPEN		(EVENTCODE_ALARMED+0x14)	//跳闸拒动;
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void BreakerStatus_OnInit(void);
//说明:执行告警检测;
extern void BreakerStatus_ExeDetect(WORD wAlarmToggleKM,WORD wAlarmToggleClose,WORD wAlarmToggleOpen);
//说明:判断跳闸回路断线是否告警;
extern BOOL BreakerStatus_IsAlarmedOpen(void);
// 说明:判断控制电源失电是否告警;
extern BOOL BreakerStatus_IsAlarmedKM(void);
// 说明:判断合闸回路断线是否告警;
extern BOOL BreakerStatus_IsAlarmedClose(void);
extern void BreakerStatus_OnTimer1ms(void);
extern void BreakerStatus_Rest(void);

extern WORD g_wStatusKM;				//控制电源信号状态,0:表示无信号,非0:表示有信号;
// extern WORD g_wStatusPosOpened;		//分位信号状态,0:表示无信号,非0:表示有信号;
extern WORD g_wStatusPosClosed;		//合位信号状态,0:表示无信号,非0:表示有信号;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__BREAKER_H*/

/******************************************************************************
模块功能:
实现断路器操作接口的相关功能,包括断路器告警,操作信息统计,断路器拒动告警,断路器分/合闸出口,
本地操作处理,并提供相关状态供保护或面板显示用;
使用步骤:
1.创建CMyBreakerOperate实例,建议变量名:g_breaker;
2.在g_app.OnInit()中调用OnInit();
3.分别在g_app.OnTimer1ms()和g_app.OnTimer10ms()中调用OnTimer1ms()和OnTimer10ms();
4.在用户程序中提供g_app.GetBOStatus(),可能的返回值为:BOSTATUS_NULL/BOSTATUS_OPENED/BOSTATUS_CLOSED;
5.在用户程序中提供g_app.SetBOErrorCloseFlag(),g_app.SetBOErrorOpenFlag(),用于设定合闸拒动和跳闸拒动标志;
6.在g_hdif.OnTimer1ms()中根据硬件检测信息执行HitStatusKM(),HitStatusPosOpened(),HitStatusPosClosed();
7.在g_app.OnTimer10ms()中调用OnTimer10ms(),再调用ExeDetect()进行告警检测;
8.其它用户程序通过IsAlarmedKM(),IsAlarmedClose(),IsAlarmedOpen()得到告警检测信息;
9.在按键处理程序中调用LocalClose(),LocalOpen(),注意先执行g_breaker.m_lockLocal.Unlock1();
10.对保护或遥控操作断路器的直接调用ExecuteClose(),ExecuteOpen(),注意操作模式参数wBOMode和对应的软件闭锁;
11.有断路器操作信息要求的,必须加以下步骤:
	1.将从FLASH中保存的断路器操作信息内容复制到m_boinfo;
	2.在数据计算模块后面对通过SetDataIMax()对m_wDataIMax,m_wDataIMax100mA赋值,注意其单位;
	3.定期保存m_boinfo到FLASH中,以防掉电丢失;
12.在保护程序中可使用m_wCountAfterClosed,m_wCountAfterOpened,m_wCountAfterTripped提供的信息;

针对不同的断路器操作模式:本地/遥控/保护,提供软件闭锁功能;
本地操作:
1.m_lockLocal.Unlock1();
2.合闸执行LocalClose(),分闸执行LocalOpen();
3.m_lockLocal.Lock1();
遥控操作:
1.m_lockRemote.Unlock1();
2.合闸执行RemoteClose(),分闸执行RemoteOpen();
3.m_lockRemote.Lock1();
保护操作:
1.m_lockProtect.Unlock1();
2.m_lockProtect.Unlock2();
3.m_lockProtect.Unlock3();
4.合闸执行ExecuteClose(BOMODE_PROTECT),分闸执行ExecuteOpen(BOMODE_PROTECT);
5.m_lockProtect.Lock3();
6.m_lockProtect.Lock2();
7.m_lockProtect.Lock1();
说明:在不同的分支中插入1,2,3项,防止程序异常时断路器误动作;
*/

//ThinkBoy,ShenBo,2006/04/30;
//-----------------------------------------------------------------------------------------------------
//											End Of File
//-----------------------------------------------------------------------------------------------------
