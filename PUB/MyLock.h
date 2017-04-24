#ifndef _MYLOCK_H
#define _MYLOCK_H

//-----------------------------------------------------------------------------
typedef struct _MYLOCK
{
	WORD m_wLockStatus1;			//��1״̬;
	WORD m_wLockStatus2;			//��2״̬;
	WORD m_wLockStatus3;			//��3״̬;
}MyLock;

#ifdef __cplusplus
extern "C" {
#endif

//˵��:��ʼ������;
extern void Lock_OnInit(MyLock* pthis);
//˵��:����1;
extern void Lock_Unlock1(MyLock* pthis);
//˵��:����2;
extern void Lock_Unlock2(MyLock* pthis);
//˵��:����3;
extern void Lock_Unlock3(MyLock* pthis);
//˵��:��1;
extern void Lock_Lock1(MyLock* pthis);
//˵��:��2;
extern void Lock_Lock2(MyLock* pthis);
//˵��:��3;
extern void Lock_Lock3(MyLock* pthis);
//˵��:�Ƿ��Ѿ�ȫ������;
extern BOOL Lock_IsUnlocked(MyLock* pthis);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*_MYLOCK_H*/

