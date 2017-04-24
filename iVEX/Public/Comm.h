#ifndef _COMM_H
#define _COMM_H

//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyComm:public CObject
{
public:
	DECLARE_SERIAL(CMyComm);
	CMyComm();
public:
	virtual void OpenCom(void);
	virtual void CloseCom(void);
	virtual void ClearCom(void);
	virtual int ReadCom(BYTE* pRXData,int nRXLength);
	virtual int WriteCom(BYTE* pTXData,int nTXLength);
};


//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyCommComX:public CMyComm
{
public:
	DECLARE_SERIAL(CMyCommComX);
	CMyCommComX();
public:
	int m_nComm;
	int m_nBaud;
protected:
	HANDLE m_hFile;
public:
	virtual void OpenCom(void);
	virtual void CloseCom(void);
	virtual void ClearCom(void);
	virtual int ReadCom(BYTE* pRXData,int nRXLength);
	virtual int WriteCom(BYTE* pTXData,int nTXLength);
};


//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyCommUDP:public CMyComm
{
public:
	DECLARE_SERIAL(CMyCommUDP);
	CMyCommUDP();
public:
	DWORD m_dwIPSrc;
	DWORD m_dwIPDest;
	int m_nPortSrc;
	int m_nPortDest;
protected:
	SOCKET m_hSocket;
	struct sockaddr_in m_sadSrc;
	struct sockaddr_in m_sadDest;
public:
	virtual void OpenCom(void);
	virtual void CloseCom(void);
	virtual void ClearCom(void);
	virtual int ReadCom(BYTE* pRXData,int nRXLength);
	virtual int WriteCom(BYTE* pTXData,int nTXLength);
};

//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyCommTCPIPServer:public CMyComm
{
public:
	DECLARE_SERIAL(CMyCommTCPIPServer);
	CMyCommTCPIPServer();
public:
	BOOL m_bExit;
	BOOL m_bThreadRun;
	DWORD m_dwIPSrc;
	int m_nSrcPort;
	WSAEVENT m_hEventServer;	//事件对象句柄
	WSAEVENT m_hEventClient;	//事件对象句柄
protected:
	SOCKET m_hSocket;
	SOCKET m_hClient;
	struct sockaddr_in m_sadSrc;
// 	struct sockaddr_in m_sadDest;
public:
	void OnAccept(void);
	void MyEndThread(void);
public:
	virtual void OpenCom(void);
	virtual void CloseCom(void);
	virtual void ClearCom(void);
	virtual int ReadCom(BYTE* pRXData,int nRXLength);
	virtual int WriteCom(BYTE* pTXData,int nTXLength);
};

extern CLASS_EXPORT CMyComm* g_pComm1;
extern CLASS_EXPORT CMyComm* g_pComm2;

#endif/*_COMM_H*/