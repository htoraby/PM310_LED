#ifndef _MYPROTOCOL_H
#define _MYPROTOCOL_H

#define COMMSTATUS_NULL			0x0000		//通信空闲状态;
#define COMMSTATUS_INIT			0x1111		//通信初始化状态,不接收任何报文,等待延时到达;
#define COMMSTATUS_RCV_ADDR		0x2222		//接收通信地址状态;
#define COMMSTATUS_RCV_HEAD		0x3333		//接收通信头信息状态;
#define COMMSTATUS_RCV_DATA		0x4444		//接收通信数据状态;
#define COMMSTATUS_SNDOPEN		0x5555		//等待报文处理,发送打开;
#define COMMSTATUS_SNDING1		0x6666		//发送报文;
#define COMMSTATUS_SNDING2		0x7777		//发送报文;
#define COMMSTATUS_SNDING3		0x8888		//发送报文;
#define COMMSTATUS_SNDCLOSE		0x9999		//发送报文完毕,等待发送关闭;
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


