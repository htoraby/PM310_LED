#ifndef CMYCOMM_IVEX_H
#define CMYCOMM_IVEX_H

//-----------------------------------------------------------------------------
class CMyComm_iVEX
{
protected:
	CLASSNAME_PROTOCOL m_protocol;
	WORD m_wRcvFlag;
	WORD m_wRXLength;
	WORD m_wTXLength;
	BYTE m_RXBuffer[COMM_BUFFERSIZE];
	BYTE m_TXBuffer[COMM_BUFFERSIZE];
	CMyComm** m_ppComm;
public:
	void SetComm(CMyComm** ppComm);
public:
	void OnInit(void);
	void OnPolling(void);
	void OnTimer10ms(void);
};

#endif/*CMYCOMM_IVEX_H*/





