#include <Main.h>

//-----------------------------------------------------------------------------
void CMyComm_iVEX::SetComm(CMyComm** ppComm)
{
	m_ppComm = ppComm;
}

void CMyComm_iVEX::OnInit(void)
{
	m_protocol.OnInit();
	m_wRcvFlag = 0;
	m_wRXLength = 0;
	m_wTXLength = 0;
}

void CMyComm_iVEX::OnPolling(void)
{
	WORD i;
	if(*m_ppComm==NULL||m_ppComm==NULL) return;
	m_protocol.OnPolling();
	m_protocol.m_wModAddr = 0x01;	// g_deviceParam.wModbusAddr1;
	if(m_wRXLength)
	{
		for(i=0;i<m_wRXLength;i++) m_protocol.OnRcvProcess(m_RXBuffer[i]);
		m_wRXLength = 0;
	}
	WORD wResult = 0;
	switch(m_protocol.m_wCommStatus)
	{
	case COMMSTATUS_INIT:
		OnInit();
		break;
	case COMMSTATUS_SNDING1:
		for(i=0;i<COMM_BUFFERSIZE;i++)
		{
			if(m_protocol.m_wCommStatus!=COMMSTATUS_SNDING1) break;
			m_TXBuffer[i] = m_protocol.GetSndData();
		}
		m_wTXLength = i;
		(*m_ppComm)->ClearCom();
		wResult = 0;
		for(i=0;i<20;i++)
		{
			wResult += (WORD)(*m_ppComm)->WriteCom(m_TXBuffer+wResult,m_wTXLength-wResult);
			if(wResult>=m_wTXLength) break;
		}
		break;
	case COMMSTATUS_SNDOPEN:
		break;
	case COMMSTATUS_SNDING2:
	case COMMSTATUS_SNDCLOSE:
		m_protocol.m_wCommStatus = COMMSTATUS_NULL;
		break;
	case COMMSTATUS_NULL:
		OnInit();
		break;
	}
}

void CMyComm_iVEX::OnTimer10ms(void)
{
	m_protocol.OnTimer10msCRC();
	if(*m_ppComm==NULL||m_ppComm==NULL)
	{
		m_wRXLength = 0;
		return;
	}
	m_wRcvFlag++;
	if(m_wRcvFlag>=10)
	{
		m_wRcvFlag = 0;
		if(m_wRXLength<COMM_BUFFERSIZE)
		{
			WORD wTemp = (WORD)(*m_ppComm)->ReadCom(m_RXBuffer+m_wRXLength,COMM_BUFFERSIZE-m_wRXLength);
			if(wTemp) 
			m_wRXLength += wTemp;
		}
	}
}
