//-----------------------------------------------------------------------------
#undef CLASSNAME_AR_RTC
#define CLASSNAME_AR_RTC CMyArRTC_NULL
class CMyArRTC_NULL:public CMyArRTC
{
public:
	BOOL IsError(void);
	void ReadTime(DEVICETIME* pDeviceTime);
	void WriteTime(DEVICETIME* pDeviceTime);
public:
	VIRTUAL void iiiReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
	VIRTUAL void iiiReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
	VIRTUAL void iiiWriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
	VIRTUAL void iiiWriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
};
