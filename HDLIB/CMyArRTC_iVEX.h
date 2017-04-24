#ifndef CMYAERTC_IVEX_H
#define CMYAERTC_IVEX_H

//-----------------------------------------------------------------------------
#undef CLASSNAME_AR_RTC
#define CLASSNAME_AR_RTC CMyArRTC_iVEX
class CMyArRTC_iVEX:public CMyArRTC
{
public:
	char m_szDeviceType[256];
protected:
	void GetRTCFileName(char* pszRTCRAMFileName);
public:
	BOOL IsError(void);
	void Star(void) {};
	void OnInit(const DEVICETIME* pDeviceTime) {};
	void ReadTime(DEVICETIME* pDeviceTime);
	void WriteTime(DEVICETIME* pDeviceTime);
public:
	VIRTUAL void iiiReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
	VIRTUAL void iiiReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
	VIRTUAL void iiiWriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
	VIRTUAL void iiiWriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
};

#endif/*CMYAERTC_IVEX_H*/
