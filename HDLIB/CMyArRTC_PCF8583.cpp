#include <Main.h>

#define RTC_DEV_ADDR		0xa0
#define RTC_DATA_ADDR		16
#define RTC_DATA_COUNTBYTE	240


///----------------------------------------------------------------------------
BOOL CMyArRTC_PCF8583::IsError(void)
{
	BYTE Temp[2];
	if(g_i2c.GetStatus(RTC_DEV_ADDR)==0) return FALSE;
	Temp[0] = 0xeb;
	Temp[1] = 0x90;
	g_i2c.WriteDataByte(RTC_DEV_ADDR,12,Temp,2);
	Temp[0] = 0x00;
	Temp[1] = 0x00;
	g_i2c.ReadDataByte(RTC_DEV_ADDR,12,Temp,2);
//	return (Temp[0]==0xeb && Temp[1]==0x90)?FALSE:TRUE;
	if(Temp[0]==0xeb && Temp[1]==0x90) return FALSE;
	return TRUE;
}

void CMyArRTC_PCF8583::ReadTime(DEVICETIME* pDeviceTime)
{
	BYTE Temp[11];
	BYTE TempYear;
	g_i2c.ReadDataByte(RTC_DEV_ADDR,0,Temp,11);
	TempYear = Temp[10];
	Temp[10] = ((Temp[10]+3-(Temp[5]>>6))&0xfc) + (Temp[5]>>6);
	if(Temp[10]>20) return;
	if(TempYear!=Temp[10]) g_i2c.WriteDataByte(RTC_DEV_ADDR,10,Temp+10,1);
	pDeviceTime->wMilliSecond = (WORD)((Temp[1]&0x0f)+10*((Temp[1])>>4))*10;
	pDeviceTime->wSecond = (WORD)(Temp[2]&0x0f)+10*((Temp[2])>>4);
	pDeviceTime->wMinute = (WORD)(Temp[3]&0x0f)+10*((Temp[3])>>4);
	pDeviceTime->wHour = (WORD)(Temp[4]&0x0f)+10*((Temp[4]&0x30)>>4);
	pDeviceTime->wDay = (WORD)(Temp[5]&0x0f)+10*((Temp[5]&0x30)>>4);
	pDeviceTime->wMonth = (WORD)(Temp[6]&0x0f)+10*((Temp[6]&0x10)>>4);
	pDeviceTime->wYear = (WORD)Temp[10];
}

void CMyArRTC_PCF8583::WriteTime(DEVICETIME* pDeviceTime)
{
	BYTE Temp[11];
	Temp[0] = 0x00;
	Temp[1] = (BYTE)(pDeviceTime->wMilliSecond/10)%10+((pDeviceTime->wMilliSecond/100)<<4);
	Temp[2] = (BYTE)(pDeviceTime->wSecond%10+((pDeviceTime->wSecond/10)<<4));
	Temp[3] = (BYTE)(pDeviceTime->wMinute%10+((pDeviceTime->wMinute/10)<<4));
	Temp[4] = (BYTE)(pDeviceTime->wHour%10+((pDeviceTime->wHour/10)<<4));
	Temp[5] = (BYTE)(pDeviceTime->wDay%10+((pDeviceTime->wDay/10)<<4));
	Temp[6] = (BYTE)(pDeviceTime->wMonth%10+((pDeviceTime->wMonth/10)<<4));
	Temp[8] = 0x00;
	Temp[10] = (BYTE)(pDeviceTime->wYear);
	Temp[5] |= (Temp[10]<<6);
	g_i2c.WriteDataByte(RTC_DEV_ADDR,0,Temp,11);
}

void CMyArRTC_PCF8583::iiiReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	if(dwAddr+wCountByte>RTC_DATA_COUNTBYTE) return;
	g_i2c.ReadDataByte(RTC_DEV_ADDR,(WORD)(RTC_DATA_ADDR+dwAddr),pData,wCountByte);
}

void CMyArRTC_PCF8583::iiiReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	if(dwAddr+wCountWord*2>RTC_DATA_COUNTBYTE) return;
	g_i2c.ReadDataWord(RTC_DEV_ADDR,(WORD)(RTC_DATA_ADDR+dwAddr),pData,wCountWord);
}

void CMyArRTC_PCF8583::iiiWriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
{
	if(dwAddr+wCountByte>RTC_DATA_COUNTBYTE) return;
	g_i2c.WriteDataByte(RTC_DEV_ADDR,(WORD)(RTC_DATA_ADDR+dwAddr),pData,wCountByte);
}

void CMyArRTC_PCF8583::iiiWriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	if(dwAddr+wCountWord*2>RTC_DATA_COUNTBYTE) return;
	g_i2c.WriteDataWord(RTC_DEV_ADDR,(WORD)(RTC_DATA_ADDR+dwAddr),pData,wCountWord);
}
