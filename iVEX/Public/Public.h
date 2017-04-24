#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include <afxmt.h>
// #include <afxsock.h>
// #include <WINSOCK.H>
#include <WINSOCK2.H>
#include <afxtempl.h>
#include <afxcview.h>
#include <io.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <conio.h>
#include <direct.h>
#include <mmsystem.h>
#include <vfw.h>

#ifdef _PUBLIC_IMPL
	#define CLASS_EXPORT AFX_CLASS_EXPORT
#else
	#define CLASS_EXPORT AFX_CLASS_IMPORT
#endif

#include "Obj.h"
#include "IED.h"
#include "Comm.h"

extern CLASS_EXPORT void MyLoadAllLibrary(void);
extern CLASS_EXPORT void MyFreeAllLibrary(void);
extern CLASS_EXPORT void MyStartTimerThread(void);
extern CLASS_EXPORT void MyEndTimerThread(void);

// 从配置文件中读取设备配置信息到pData中
// 参数strDevicName:设备名称
// 参数pData:数据缓冲区
// 参数nLen:读取长度
// 返回值:FALSE-读取失败,TRUE-读取成功
extern CLASS_EXPORT BOOL ReadConfig(CString strDevicName,void* pData,UINT nLen);
// 将pData中设备配置信息写入配置文件中,如果配置文件不存在则会新建配置文件
// 参数strDevicName:设备名称
// 参数pData:数据缓冲区
// 参数nLen:读取长度
// 返回值:FALSE-写入失败,TRUE-写入成功
extern CLASS_EXPORT BOOL WriteConfig(CString strDevicName,void* pData,UINT nLen);

extern CLASS_EXPORT CMyIED* g_pIED;
extern CLASS_EXPORT CString g_strIVEX;

#endif/*_PUBLIC_H_*/
