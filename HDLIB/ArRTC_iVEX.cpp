#include <stdio.h>
#include <Main.h>
#include "stdafx.h"

//----------------------------------------------------------------------------
BOOL RTC_IsError(void)
{
	return FALSE;
}

void RTC_ReadTime(DEVICETIME* pDeviceTime)
{
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	pDeviceTime->wYear = systemTime.wYear-2000;
	pDeviceTime->wMonth = systemTime.wMonth;
	pDeviceTime->wDay = systemTime.wDay;
	pDeviceTime->wHour = systemTime.wHour;
	pDeviceTime->wMinute = systemTime.wMinute;
	pDeviceTime->wSecond = systemTime.wSecond;
	pDeviceTime->wMilliSecond = systemTime.wMilliseconds;
}

void RTC_WriteTime(DEVICETIME* pDeviceTime)
{
}

void RTC_Star(void)
{

}

void RTC_OnInit(const DEVICETIME* pDeviceTime)
{

}
