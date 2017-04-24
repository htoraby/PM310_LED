//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef _RTC_RX8025_H
#define _RTC_RX8025_H

#ifdef __cplusplus
extern "C" {
#endif

extern BOOL RTC_IsError(void);
// extern void RTC_Start(void){};
extern void RTC_OnInit(const DEVICETIME* pDeviceTime);
extern void RTC_ReadTime(DEVICETIME* pDeviceTime);
extern void RTC_WriteTime(DEVICETIME* pDeviceTime);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // _RTC_RX8025_H

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------
