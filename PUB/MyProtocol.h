//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef _MYPROTOCOL_H
#define _MYPROTOCOL_H

#define COMMSTATUS_NULL			0x0000		//ͨ�ſ���״̬;
#define COMMSTATUS_INIT			0x1111		//ͨ�ų�ʼ��״̬,�������κα���,�ȴ���ʱ����;
#define COMMSTATUS_RCV_ADDR		0x2222		//����ͨ�ŵ�ַ״̬;
#define COMMSTATUS_RCV_HEAD		0x3333		//����ͨ��ͷ��Ϣ״̬;
#define COMMSTATUS_RCV_DATA		0x4444		//����ͨ������״̬;
#define COMMSTATUS_SNDOPEN		0x5555		//�ȴ����Ĵ���,���ʹ�;
#define COMMSTATUS_SNDING1		0x6666		//���ͱ���;
#define COMMSTATUS_SNDING2		0x7777		//���ͱ���;
#define COMMSTATUS_SNDING3		0x8888		//���ͱ���;
#define COMMSTATUS_SNDCLOSE		0x9999		//���ͱ������,�ȴ����͹ر�;
#define COMMSTATUS_RCV_ET		0xaaaa

#ifndef COMM_TIMEOUT
#define COMM_TIMEOUT			(250*DFT_DOTNUM)
#endif
#ifndef COMM_BUFFERSIZE
#define COMM_BUFFERSIZE			256
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern BYTE g_CommBuffer[COMM_BUFFERSIZE];
extern BYTE* g_pRcvPointer;
extern BYTE* g_pRcvEndPointer;
extern BYTE* g_pSndPointer;
extern BYTE* g_pSndEndPointer;
extern WORD g_wModAddr;
extern WORD g_wCommStatus;
extern WORD g_wCountTimeout;
extern WORD g_wCRCCal;

//-----------------------------------------------------------------------------
extern void Protocol_OnInit(void);
extern void Protocol_OnPolling(void);
extern BOOL Protocol_IsCommActive(void);
extern BYTE Protocol_GetSndData(void);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*_MYPROTOCOL_H*/

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------




