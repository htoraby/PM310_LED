#include "main.h"

//-----------------------------------------------------------------------------
void Lock_OnInit(MyLock* pthis)
{
	pthis->m_wLockStatus1 = 0x0000;
	pthis->m_wLockStatus2 = 0x0000;
	pthis->m_wLockStatus3 = 0x0000;
}

void Lock_Unlock1(MyLock* pthis)
{
	pthis->m_wLockStatus1 = 0x1111;
}

void Lock_Unlock2(MyLock* pthis)
{
	pthis->m_wLockStatus2 = 0x2222;
}

void Lock_Unlock3(MyLock* pthis)
{
	pthis->m_wLockStatus3 = 0x3333;
}

void Lock_Lock1(MyLock* pthis)
{
	pthis->m_wLockStatus1 = 0x0000;
}

void Lock_Lock2(MyLock* pthis)
{
	pthis->m_wLockStatus2 = 0x0000;
}

void Lock_Lock3(MyLock* pthis)
{
	pthis->m_wLockStatus3 = 0x0000;
}

BOOL Lock_IsUnlocked(MyLock* pthis)
{
	return (pthis->m_wLockStatus1==0x1111 && pthis->m_wLockStatus2==0x2222 && pthis->m_wLockStatus3==0x3333);
}

