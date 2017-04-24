#ifndef __TIME_H
#define __TIME_H


//-----------------------------------------------------------------------------
typedef struct _DEVICETIME
{
	WORD wYear;						//年(实际年-2000,0-100);
	WORD wMonth;					//月(1-12);
	WORD wDay;						//日(1-31);
	WORD wHour;						//时(0-23);
	WORD wMinute;					//分(0-59);
	WORD wSecond;					//秒(0-59);
	WORD wMilliSecond;				//毫秒(0-999);
}DEVICETIME;


#ifdef __cplusplus
extern "C" {
#endif

//说明:返回指定年月的月天数;
extern WORD Time_GetDayOfMonth(WORD wYear,WORD wMonth);
//说明:检查时间是否正确;
extern BOOL Time_IsTimeOK(DEVICETIME* pDeviceTime);
//说明:初始化程序,将系统时间初始化为2000-01-01 00:00:00.000;
extern void Time_OnInit(void);
//说明:定时服务程序(严格)调用,用于时间刷新;
extern void Time_OnTimer1ms(void);
//说明:定时服务程序调用,用于保存时间和重读时间;
extern void Time_OnTimer1000ms(void);
//说明:由g_app的OnUpdateDevice()进行调用,用于置保存更新标志;
extern void Time_OnUpdateDevice(WORD* pData);
//说明:判断毫秒计数是否小于450(考虑了闪烁效果),用于每秒一次闪烁控制;
extern BOOL Time_IsFlashing(void);

extern DEVICETIME g_deviceTime;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__TIME_H*/

/******************************************************************************
模块功能:
实现时间管理;
使用步骤:
1.创建CMyTime实例,建议变量名:g_time;
2.在g_app.OnInit()中调用g_time.OnInit();
3.在g_app.OnTimer1ms()中调用g_time.OnTimer1ms();
4.在g_app.OnTimer1000ms()中调用g_time.OnTimer1000ms();
5.其它用户程序通过公共变量g_time.m_deviceTime访问设备时间;
6.校时命令或时间设置要求改变时间的,直接修改g_time.m_deviceTime,并调用
  g_time.OnUpdateDevice((WORD*)&g_time.m_deviceTime),以置保存更新标志;
  正常每半小时从时钟芯片重读一次最新时间,待保存更新标志被置后自动将更
  新的时间保存到时钟芯片中;
*/
//ThinkBoy,ShenBo,2006/04/30;
