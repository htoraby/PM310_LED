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

// �������ļ��ж�ȡ�豸������Ϣ��pData��
// ����strDevicName:�豸����
// ����pData:���ݻ�����
// ����nLen:��ȡ����
// ����ֵ:FALSE-��ȡʧ��,TRUE-��ȡ�ɹ�
extern CLASS_EXPORT BOOL ReadConfig(CString strDevicName,void* pData,UINT nLen);
// ��pData���豸������Ϣд�������ļ���,��������ļ�����������½������ļ�
// ����strDevicName:�豸����
// ����pData:���ݻ�����
// ����nLen:��ȡ����
// ����ֵ:FALSE-д��ʧ��,TRUE-д��ɹ�
extern CLASS_EXPORT BOOL WriteConfig(CString strDevicName,void* pData,UINT nLen);

extern CLASS_EXPORT CMyIED* g_pIED;
extern CLASS_EXPORT CString g_strIVEX;

#endif/*_PUBLIC_H_*/
