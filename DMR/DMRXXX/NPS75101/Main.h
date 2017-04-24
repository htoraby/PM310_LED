#ifndef MAIN_H
#define MAIN_H

#define DEVICETYPE_NAME     "NPS7510"
#define DEVICETYPE_CODE     ((WORD)7510)

//-----------------------------------------------------------------------------
#define KEY_NULL            0x0000
#define KEY_UP              0x0001  // 上;
#define KEY_DOWN            0x0002  // 下;
#define KEY_LEFT            0x0004  // 左;
#define KEY_RIGHT           0x0008  // 右;
#define KEY_ENT             0x0010  // 确认;
#define KEY_ESC             0x0020  // 取消;
#define KEY_RESET           0x0040  // 复归;
#define KEY_ADD             0x0080  // +;
#define KEY_SUB             0x0100  // -;

#define KEY_REPEATCODE		(KEY_UP|KEY_DOWN|KEY_LEFT|KEY_RIGHT)

#define DFT_DOT24
#define SWITCH_COUNT        9
#define RELAYKH_COUNT       6
#define SWITCH_COUNT_TO     (SWITCH_COUNT)              // 开关量总数
#define RELAYKH_COUNT_TO    (RELAYKH_COUNT)             // 继电器总数

#define FILTER_DEPTH        20
#define EVENT_COUNT         128
#define COMM_BUFFERSIZE     1200
// #define DISKBUFF            0x800
#define MAIN_VERSION        100
#define SUB_VERSION         00

#define DFT_Ia              0x00
#define DFT_Ib              0x01
#define DFT_Ic              0x02
#define DFT_IA              0x03
#define DFT_IB              0x04
#define DFT_IC              0x05
#define DFT_3I0             0x06
#define DFT_Ua              0x08
#define DFT_Ub              0x09
#define DFT_Uc              0x0a

#define DFT_CHANNEL_HARD    (DFT_Uc-DFT_Ia+1)

#define ANALOGDATA_EXT      // 扩展模拟量(功率,断路器信息)
#define BREAKERINTERFACE
// #define MULTISETPOINTAREA


//-----------------------------------------------------------------------------
#define LCD_CXDOT           160
#define LCD_CYDOT           160
#ifndef LCD_MULTICOLOR
#define LCD_BUFFSIZEMAX     (LCD_CXDOT/16*LCD_CYDOT)    // (160*160/8/2)
#else
#define LCD_BUFFSIZEMAX     (LCD_CXDOT/2*LCD_CYDOT)     // (160*160/8*4)
#endif

// #define WAVEDATABUFF			LCD_CXDOT
#define LCD_HZ16

#define EDIT_COUNTMAX           20
#define EDIT_ENUMSZMAX          35  // (2+SWITCH_COUNT)
#define EDIT_BUFFERSIZE         96

// #define LIGHTBAKCNT             12
// #define MENUHEAD				15

#define __INLINE				inline

// #define MET					// Measurand with Time

// #define COMM_TIMEOUT			(10000)		// 10s
// #define SWITCH_PERMS			6

// #define DSGICNT					119// 71					// GI中双点信息个数
// #define DSUSERDATA2_P			4					// 电度数据个数
// #define DSUSERDATA2_M			41					// 测量数据个数
// #define DSUSERDATA2_H			192					// 谐波数据个数
// #define DSUSERDATA2CNT			(DSUSERDATA2_M+DSUSERDATA2_H)					// 遥测数据个数

#define ALARMCTM_DELAY			900					// 测量CT断线告警延时9秒;
#define ALARMCTP_DELAY			900					// 保护CT断线告警延时9秒;


//-----------------------------------------------------------------------------
#include "DMR\PUB\_Main1DMR.h"
// #include "DMR\DMRXXX\pub\PromptiBCU3.h"
#include "PUB\__DevSet.h"
#include "PUB\__Event.h"
#include "PUB\__Alarm.h"
#include "PUB\__Switch.h"
#include "PUB\__Output.h"
#include "PUB\__DFT.h"
#include "PUB\__Data.h"
// #include "PUB\__Measure.h"
// #include "PUB\__WaveRecord.h"
// #include "PUB\CMyQueue.h"
// #include "DMR\PUB\CMyWaveForm.h"
// #include "DMR\PUB\CMyDCProcess.h"
// #include "DMR\DMRXXX\PUB\CMyDCProcess3X4X.h"
// // Protocol:
// #include "PUB\CMyProtocol.h"
// #include "PUB\CMyProtocolMODBUS.h"
// #include "PUB\CMyProtocolMODBUSTCP.h"
// #include "PUB\CMyProtocol103.h"
// HDIF:
#include ".\HDIFNPS7510.h"
// // Protect:
// #include "DMR\PUB\CMyProtect.h"
// #include "DMR\DMRXXX\iBCU3340\CMyProtectiBCU3340.h"
// 
// #include "DMR\PUB\CMyWaveFormSource.h"
// #include "DMR\DMRXXX\iBCU3340\CMyWaveFormSourceiBCU3340.h"
// 
// // App:
// #include "DMR\PUB\CMyAppDMR.h"
// #include "PUB\__Breaker.h"
// #include "PUB\__AlarmCTPT.h"
// #include "PUB\__PQPhQh.h"
// #include "DMR\DMRXXX\iBCU3340\CMyAppiBCU3340.h"
// // Table:
// #include "PUB\CMyTable.h"
// #include "DMR\PUB\CMyTableDMR.h"
// #include "DMR\DMRXXX\PUB\CMyTableDMRUnit.h"
// #include "DMR\PUB\CMy103ProtocolTable.h"
// #include "DMR\DMRXXX\iBCU3340\CMy103ProtocolTable3340.h"
// // LAD:
// #include "DMR\PUB\CMyLAD.h"
// #include "DMR\PUB\CMyLADDMR4.h"
// #include "DMR\DMRXXX\iBCU3340\CMyLADiBCU3340.h"
//Menu:
#include "PUB\Menu.h"
// #include "DMR\PUB\CMyMenuDMR4.h"
#include "DMR\DMRXXX\NPS7510\MenuNPS7510.h"
// // Page:
// #include "PUB\CMyPage.h"
// #include "DMR\PUB\CMyPage160x160.h"
// #include "DMR\PUB\CMyPage240x320.h"
// #include "DMR\PUB\CMyDRW.h"
// #include "DMR\PUB\CMyPG_DRW.h"
// #include "DMR\PUB\CMyPG_LAD.h"
// #include "DMR\PUB\CMyPG_Protect.h"
// #include "DMR\PUB\CMyPG_WaveRecord.h"
// #include "DMR\DMRXXX\PUB\CMyPG_WaveForm.h"
// #include "DMR\DMRXXX\iBCU3340\CMyPG_ProtectiBCU3340.h"
// #include "DMR\DMRXXX\iBCU3340\CMyPageiBCU3340160x160.h"
// #include "DMR\DMRXXX\iBCU3340\CMyPageiBCU3340240x320.h"
// // HMI:
// #include "DMR\PUB\CMyHMIDMR.h"
// #include "DMR\DMRXXX\iBCU3340\CMyHMIiBCU3340.h"
// 
// #include "DMR\PUB\_Main2DMR.h"

#endif /*MAIN_H*/

