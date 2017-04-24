#ifndef _MYLOCK_H
#define _MYLOCK_H

//-----------------------------------------------------------------------------
typedef struct _MYLOCK
{
	WORD m_wLockStatus1;			//锁1状态;
	WORD m_wLockStatus2;			//锁2状态;
	WORD m_wLockStatus3;			//锁3状态;
}MyLock;

#ifdef __cplusplus
extern "C" {
#endif

//说明:初始化程序;
extern void Lock_OnInit(MyLock* pthis);
//说明:解锁1;
extern void Lock_Unlock1(MyLock* pthis);
//说明:解锁2;
extern void Lock_Unlock2(MyLock* pthis);
//说明:解锁3;
extern void Lock_Unlock3(MyLock* pthis);
//说明:锁1;
extern void Lock_Lock1(MyLock* pthis);
//说明:锁2;
extern void Lock_Lock2(MyLock* pthis);
//说明:锁3;
extern void Lock_Lock3(MyLock* pthis);
//说明:是否已经全部解锁;
extern BOOL Lock_IsUnlocked(MyLock* pthis);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*_MYLOCK_H*/

