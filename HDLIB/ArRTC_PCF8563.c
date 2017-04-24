#include <Main.h>

//#define RTC_DEV_ADDR		0x0051			// 0x00a2>>1			// ʱ��оƬ
//#define RTC_BAUDRATE		100				// 400k
// #define RTC_DEV_ADDR2		0x0050			// 0x00a0>>1			// RAM
// #define RTC_BAUDRATE2		100				// 400k
// #define RTC_DATA_COUNTBYTE	(32768-2)		// ��ǰ2���ֽ������Լ�

#define RTC_PCF8563		0xa2
//*******************************************************************************************
//*����: BYTE Bcd_convert_Hex(BYTE bcd_data)												*
//*����: BCD��ת16����																		*
//*����: Bcd_data  Ҫת����BCD������(0-100)													*
//*����: ת�����16��������																	*
//*******************************************************************************************
BYTE Bcd_convert_Hex(BYTE Bcd_data)
{
	BYTE temp;
	temp=((Bcd_data>>4)*10)+(Bcd_data&0x0f);
	return temp;
}

//*******************************************************************************************
//*����: BYTE hex_convert_bcd(BYTE hex_dataa)												*
//*����: 16����תBCD��																		*
//*����: hex_data Ҫת����16��������(0-100)													*
//*����: ת�����BCD������																	*
//*******************************************************************************************
BYTE Hex_convert_Bcd(BYTE hex_data)
{
	BYTE temp;
	BYTE bcd_data;
	temp=hex_data%100;
	bcd_data=(temp/10<<4)|(temp%10);
	return bcd_data;
}

//----------------------------------------------------------------------------
BOOL RTC_IsError(void)
{
	BYTE Temp[2];
	Temp[0] = 0xD5;
	Temp[1] = 0x90;	
	RTC_WriteDataByte(RTC_PCF8563,0x09,Temp,2);
	Temp[0] = 0x00;
	Temp[1] = 0x00;
	RTC_ReadDataByte(RTC_PCF8563,0x09,Temp,2);
	if(Temp[0]!=0xD5 || (Temp[1]&0xbf)!=0x90) return TRUE;
	return FALSE;
}

//*******************************************************************************************
//*����: void Start(void)																	*
//*����: ����PCF8563оƬ����																*
//*����:																					*
//*����:																					*
//*******************************************************************************************
/*
void RTC_Start(void)
{
	BYTE Temp = 0x00;
	RTC_WriteDataByte(RTC_PCF8563,0x00,&Temp,1);
}
*/
//*******************************************************************************************
//*����: void ReadTime(DEVICETIME* pDeviceTime)												*
//*����: ��RTCоƬ��ȡʱ������ ����ŵ�ָ������												*
//*����:																					*
//*����:																					*
//*******************************************************************************************
void RTC_ReadTime(DEVICETIME* pDeviceTime)
{
	BYTE Temp[7];
	RTC_ReadDataByte(RTC_PCF8563,0x02,Temp,7);

	pDeviceTime->wSecond = Bcd_convert_Hex(Temp[0]&0x7F);		// ��
	pDeviceTime->wMinute = Bcd_convert_Hex(Temp[1]&0x7F);		// ��
	pDeviceTime->wHour = Bcd_convert_Hex(Temp[2]&0x3F);			// Сʱ
	pDeviceTime->wDay = Bcd_convert_Hex(Temp[3]&0x3F);			// ��
// 	ptr[4]=ptr[4];
	pDeviceTime->wMonth = Bcd_convert_Hex(Temp[5]&0x1F);		// ��
	pDeviceTime->wYear = Bcd_convert_Hex(Temp[6]);				// ��
}

//*******************************************************************************************
//*����: WriteTime(DEVICETIME* pDeviceTime)													*
//*����: ��ʱ��������д��PCF8563Ƭ															*
//*����: 																					*
//*����: 																					*
//*******************************************************************************************
void RTC_WriteTime(DEVICETIME* pDeviceTime)
{
	BYTE Temp[7];
	BYTE Tmp;
	Temp[0] = Hex_convert_Bcd(pDeviceTime->wSecond);
	Temp[1] = Hex_convert_Bcd(pDeviceTime->wMinute);
	Temp[2] = Hex_convert_Bcd(pDeviceTime->wHour);
	Temp[3] = Hex_convert_Bcd(pDeviceTime->wDay);
	Temp[4] = 0x00;
	Temp[5] = Hex_convert_Bcd(pDeviceTime->wMonth);
	Temp[6] = Hex_convert_Bcd(pDeviceTime->wYear);

	Tmp = 0x20;

	RTC_WriteDataByte(RTC_PCF8563,0x00,&Tmp,1);		// PCF8563ʱ��оֹͣ����
	RTC_WriteDataByte(RTC_PCF8563,0x02,Temp,7);		// ������ʱ��д��PCF8563
	Tmp = 0x00;
	RTC_WriteDataByte(RTC_PCF8563,0x00,&Tmp,1);		// PCF8563ʱ��о��ʼ����
}

//*******************************************************************************************
//*����: void OnInit(void)																	*
//*����: ���ʱ�����ݲ�����д���ʼֵ														*
//*����:																					*
//*����:																					*
//*******************************************************************************************
void RTC_OnInit(const DEVICETIME* pDeviceTime)
{
	DEVICETIME Time;
	BYTE Sencond,Tmp;
	RTC_ReadTime(&Time);
// ------------------��͵�ѹ��־------------------------	
	RTC_ReadDataByte(RTC_PCF8563,0x02,&Sencond,1);
	Tmp = 0x20;
	RTC_WriteDataByte(RTC_PCF8563,0x00,&Tmp,1);
	Sencond &= 0x7f;
	RTC_WriteDataByte(RTC_PCF8563,0x02,&Sencond,1);
	Tmp = 0x00;
	RTC_WriteDataByte(RTC_PCF8563,0x00,&Tmp,1);
// -------------------------------------------------------	 
	if(Time.wSecond>=60||Time.wMinute>=60||Time.wHour>=24||Time.wDay>=32
	||Time.wMonth>=13||Time.wYear>=100)
	{
		Time = *pDeviceTime;
		RTC_WriteTime(&Time);
	}
// ---------------------- for debug ---------------------------------------------
// 	Tmp = 0x20;
// 	g_i2c.WriteDataByte(RTC_DEV_ADDR1,0x00,&Tmp,1);		// PCF8563ʱ��оֹͣ����
// ------------------------------------------------------------------------------
}

