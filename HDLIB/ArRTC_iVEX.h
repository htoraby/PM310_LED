#ifndef CMYAERTC_IVEX_H
#define CMYAERTC_IVEX_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
extern BOOL RTC_IsError(void);
extern void RTC_Star(void);
extern void RTC_OnInit(const DEVICETIME* pDeviceTime);
extern void RTC_ReadTime(DEVICETIME* pDeviceTime);
extern void RTC_WriteTime(DEVICETIME* pDeviceTime);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*CMYAERTC_IVEX_H*/
