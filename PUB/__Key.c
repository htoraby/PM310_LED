#include <Main.h>

static WORD s_wKeyHardCodeOld;			//��ǰ��Ӳ����ʽ������;
static WORD s_wKeyHardCodeNew;			//���µ�Ӳ����ʽ������;
static WORD s_wKeyCode;				//��ǰ�İ�����;
static WORD s_wKeyQueue[4];			//�����뻺�����;
static WORD s_wKeyRepeatCode;			//��������İ��������;
static WORD s_wKeyRepeatDelay;			//������ⰴ������ʱ����;
static WORD s_wKeyTime;

//-----------------------------------------------------------------------------
void Key_OnInit(void)
{
	s_wKeyHardCodeOld = KEY_NULL;
	s_wKeyHardCodeNew = KEY_NULL;
	s_wKeyCode = KEY_NULL;
	s_wKeyQueue[0] = KEY_NULL;
	s_wKeyQueue[1] = KEY_NULL;
	s_wKeyQueue[2] = KEY_NULL;
	s_wKeyQueue[3] = KEY_NULL;
	s_wKeyRepeatCode = KEY_NULL;
	s_wKeyRepeatDelay = 0;
	s_wKeyTime = 0;
}

void Key_OnTimer10ms(void)
{
	WORD wKeyCodeOld,i;
	if(s_wKeyTime<30) s_wKeyTime++;
	if(s_wKeyHardCodeOld!=s_wKeyHardCodeNew)
	{
		s_wKeyHardCodeOld = s_wKeyHardCodeNew;
		return;
	}
	if(s_wKeyHardCodeNew==KEY_NULL)
	{
		s_wKeyCode = KEY_NULL;
		return;
	}
	wKeyCodeOld = s_wKeyCode;
	for(i=0;i<16;i++)
	{
		if(s_wKeyHardCodeNew&(1<<i))
		{
			s_wKeyCode = 1<<i;
			break;
		}
	}
	if(wKeyCodeOld==s_wKeyCode)
	{
		s_wKeyRepeatDelay++;
		if(s_wKeyRepeatDelay>=50)
		{
			s_wKeyRepeatDelay = 30;
// 			m_wKeyRepeatDelay = 0;
			if(s_wKeyCode&s_wKeyRepeatCode) Key_AddKeyQueue(s_wKeyCode);
		}
	}
	else
	{
		s_wKeyRepeatDelay = 0;
		if(s_wKeyTime>=20)
		{
			s_wKeyTime = 0;
			Key_AddKeyQueue(s_wKeyCode);
		}
	}
}

void Key_SetKeyHardCode(WORD wKeyHardCode)
{
	s_wKeyHardCodeNew = wKeyHardCode;
}

void Key_SetKeyRepeatCode(WORD wKeyRepeatCode)
{
	s_wKeyRepeatCode = wKeyRepeatCode;
}

void Key_AddKeyQueue(WORD wKeyCode)
{
	WORD i;
	for(i=0;i<4;i++)
	{
		if(s_wKeyQueue[i]==KEY_NULL)
		{
			s_wKeyQueue[i] = wKeyCode;
			break;
		}
	}
}

WORD Key_GetKeyQueue(void)
{
	WORD wKeyCode;
	wKeyCode = s_wKeyQueue[0];
	if(wKeyCode!=KEY_NULL)
	{
		s_wKeyQueue[0] = s_wKeyQueue[1];
		s_wKeyQueue[1] = s_wKeyQueue[2];
		s_wKeyQueue[2] = s_wKeyQueue[3];
		s_wKeyQueue[3] = KEY_NULL;
	}
	return wKeyCode;
}


