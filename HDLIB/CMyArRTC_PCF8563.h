//-----------------------------------------------------------------------------
#undef CLASSNAME_AR_RTC
#define CLASSNAME_AR_RTC CMyArRTC_PCF8563
class CMyArRTC_PCF8563// :public CMyArRTC
{
public:
	BOOL IsError(void);
	void Start(void);
	void OnInit(const DEVICETIME* pDeviceTime);
	void ReadTime(DEVICETIME* pDeviceTime);
	void WriteTime(DEVICETIME* pDeviceTime);
public:
	VIRTUAL void iiiReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
	VIRTUAL void iiiReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
	VIRTUAL void iiiWriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
	VIRTUAL void iiiWriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
};
