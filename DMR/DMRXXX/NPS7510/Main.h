#ifndef MAIN_H
#define MAIN_H

#define COMM_MODEBUS
#define MULTI_LANGUAGE
#define RATE_FREQUENCY
#define DEVICETYPE_NAME         "KT90R"
#define DEVICETYPE_CODE         (310)

#define APP_OnInitParams		MyApp_OnInitParams
#define APP_OnInit				MyApp_OnInit
#define APP_OnTimer1ms			MyApp_OnTimer1ms
#define APP_OnTimer10ms			MyApp_OnTimer10ms
#define APP_OnTimer250ms()
#define APP_OnTimer1000ms		MyApp_OnTimer1000ms
#define APP_OnWhileLoop			MyApp_OnWhileLoop

#define HMI_OnInit				MyHMI_OnInit
#define HMI_OnTimer1ms()
#define HMI_OnTimer10ms			MyHMI_OnTimer10ms
#define HMI_OnTimer250ms		EditG_OnTimer250ms
#define HMI_OnTimer1000ms		MyHMI_OnTimer1000ms
#define HMI_OnWhileLoop			MyHMI_OnWhileLoop

#define HDIF_OnInit1			MyHDIF_OnInit1
#define HDIF_OnInit2			MyHDIF_OnInit2
#define HDIF_OnTimer1ms			MyHDIF_OnTimer1ms
#define HDIF_OnTimer10ms		MyHDIF_OnTimer10ms
#define HDIF_OnTimer250ms()
#define HDIF_OnTimer1000ms		MyHDIF_OnTimer1000ms
#define HDIF_OnWhileLoop		MyHDIF_OnWhileLoop
#define HDIF_OnPollingComm		MyHDIF_OnPollingComm

//-----------------------------------------------------------------------------
#define KEY_REPEATCODE		(KEY_UP|KEY_DOWN)    // (KEY_UP|KEY_DOWN|KEY_LEFT|KEY_RIGHT)

#define ALARMPT_10V			325		// µçÑ¹10V

#define DFT_DOT24
#define SWITCH_COUNT		4
#define RELAYKH_COUNT		2

#define FILTER_DEPTH		5
#define EVENT_COUNT			100
#define COMM_BUFFERSIZE		256
#define MAIN_VERSION		106
#define SUB_VERSION			000

#define SCALE2IM            600
#define SCALE2ULN           26000

// #define DFT_Ia				0x00
// #define DFT_Ib				0x01
// #define DFT_Ic				0x02
// #define DFT_IA				0x03
// #define DFT_IB				0x04
// #define DFT_IC				0x05
// #define DFT_3I0				0x06
// #define DFT_Ua				0x07
// #define DFT_Ub				0x08
// #define DFT_Uc				0x09

#define DFT_Ia				0x00
#define DFT_Ib				0x01
#define DFT_Ic				0x02
#define DFT_Ua				0x03
#define DFT_Ub				0x04
#define DFT_Uc				0x05

#define DFT_CHANNEL_HARD	(DFT_Uc-DFT_Ia+1)
//-----------------------------------------------------------------------------
#define LCD_HZ12
#define LCD_CXDOT				160
#define LCD_CYDOT				160
#ifndef LCD_MULTICOLOR
#define LCD_BUFFSIZEMAX			(LCD_CXDOT/16*LCD_CYDOT)		// (160*160/8/2)
#else
#define LCD_BUFFSIZEMAX			(LCD_CXDOT/2*LCD_CYDOT)		// (160*160/8*4)
#endif
#define WAVEDATABUFF			LCD_CXDOT

#define INNAMECNT			17
#define INNAMEWIDTH			17
#define INSTATUSCNT			15
#define INSTATUSWIDTH		7
#define INENUMMAX			MAX(INNAMECNT,INSTATUSCNT)

#define EDIT_COUNTMAX		10
#define EDIT_ENUMSZMAX		MAX((2+SWITCH_COUNT),INENUMMAX)

#define MENUHEAD			15

// #define PANELID				0x54

#define JumpToEventDisplay g_bDisplayEvent = TRUE

// WAVERECORD
#define WAVERECORD_WAVECNT	10			// ÖÜ²¨Êý
#define WAVERECORD_DOTNUM	(DFT_DOTNUM*WAVERECORD_WAVECNT)
#define WAVERECORD_WAVENUM	6
#define WAVERECORDCHANMEL   6

//-----------------------------------------------------------------------------
#include "DMR\PUB\_Main1DMR.h"
// TOOL
#include "PUB\__DevSet.h"
#include "PUB\__Output.h"
#include "PUB\__Key.h"
#include "PUB\__Edit.h"
#include "PUB\__Event.h"
#include "PUB\__Data.h"
#include "PUB\__DFT.h"
#include "PUB\__Measure.h"
#include "PUB\__switch.h"
#include "PUB\__Alarm.h"
#include "PUB\__ALARMCTPT.h"
#include "PUB\__PQPhQh.h"
#include "Pub\__WaveRecord.h"
//Protocol:
#include "PUB\MyProtocol.h"
#include "PUB\MyProtocolMODBUS.h"
// HDIF
// #include "PUB\__LCD.h"
// #include "PUB\__LCDMem.h"
#include ".\HDIFNPS7510.h"
// Protect
#include "DMR\PUB\__Protect.h"
#include "DMR\DMRXXX\NPS7510\Protect.h"
// APP
#include "DMR\DMRXXX\NPS7510\_MyAppNPS7510.h"
#include "DMR\PUB\MyApp.h"
//Table:
#include "PUB\MyTable.h"
#include "DMR\PUB\MyTableDMR.h"
// #include "DMR\DMRXXX\PUB\CMyTableDMRUnit.h"
// HMI
#include "DMR\PUB\MyHmiDMR.h"
#include "DMR\DMRXXX\NPS7510\_MyHMINPS7510.h"
//Menu:
#include "PUB\MyMenu.h"
#include "DMR\PUB\MyMenu160x160.h"
#include "DMR\DMRXXX\NPS7510\MyMenuNPS7510.h"
//Page:
#include "PUB\MyPage.h"
#include "DMR\PUB\MyPage160x160.h"
#include "DMR\PUB\MyPG_Protect.h"
#include "DMR\DMRXXX\NPS7510\MyPG_ProtectNPS7510.h"
#include "DMR\DMRXXX\NPS7510\MyPageNPS7510.h"
#include "DMR\Pub\MyPG_WaveRecord.h"

#endif /*MAIN_H*/

