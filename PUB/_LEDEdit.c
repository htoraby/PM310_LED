#include "main.h"
/********************************************************/

#define EM_NONE			0x0000
#define EM_ENUM			0x0001
#define EM_DATAWORD		0x0002
#define EM_DATADWORD	0x0003

#define ES_NULL			0x0000
#define ES_SELECT		0x0001
#define ES_EDITING		0x0002

struct EDIT
{
	unsigned short wMode;
	unsigned short wPosX;
	unsigned short wPosY;
	unsigned short* pData;
	unsigned short wReserved[27];
};

struct EDITENUM
{
	unsigned short wMode;
	unsigned short wPosX;
	unsigned short wPosY;
	unsigned short* pData;
	unsigned short wData;
	unsigned short wCountChar;
	unsigned short wCountEnum;
	char* pszEnum[12];
};

struct EDITDATA
{
	unsigned short wMode;
	unsigned short wPosX;
	unsigned short wPosY;
	unsigned short* pData;
	unsigned long dwData;
	unsigned long dwDataMin;
	unsigned long dwDataMax;
	unsigned short wFormat;
	unsigned short wScale2XX;
	unsigned short wDataRunTime;
	unsigned short wCountBCD;
	unsigned short wCountBCDAfterDot;
	unsigned short wCountBCDBeforDot;
	unsigned short bReserveZero;
};

static struct EDIT s_edit;
static unsigned short s_wEditStatus;
static unsigned short s_bEditShining;
static unsigned short s_wEditDataBCD;
static struct EDITENUM* s_pEditEnum;
static struct EDITDATA* s_pEditData;
unsigned short g_wLEDX;
unsigned short g_wLEDY;
unsigned short g_wPageAllCount;
//WORD g_wPasswordLevel;

//*******************************************************************
static void AddEdit(unsigned short* pData)
{
	s_pEditEnum = 0;
	s_pEditData = 0;
	if(g_wLEDY>=4) return;
	s_edit.wPosX = g_wLEDX;
	s_edit.wPosY = g_wLEDY;
	s_edit.pData = pData;
}

static void DisplayEditEnum(void)
{
	unsigned short wEnumIndex;
	if(s_pEditEnum->wCountEnum==0)
	{
		if(s_pEditEnum->wData==0x5555) wEnumIndex = 1;
		else wEnumIndex = 0;
	}
	else wEnumIndex = s_pEditEnum->wData;
	if(wEnumIndex>32) wEnumIndex = 32;
	LEDAsciiOut(s_pEditEnum->wPosX,s_pEditEnum->wPosY,s_pEditEnum->pszEnum[wEnumIndex]);
}

static void DisplayEditData(void)
{
	if(s_pEditData->bReserveZero) g_bFormatRealFillBlank = 0;
	if(s_wEditStatus==ES_EDITING) g_bFormatRealFillBlank = 0;
	LEDRealOut(s_pEditData->wPosX,s_pEditData->wPosY,s_pEditData->dwData,s_pEditData->wFormat);
}

static void OnEditKeyMsgEnum(unsigned short wKeyCode)
{
	s_pEditEnum = (struct EDITENUM*)&s_edit;
	if(s_pEditEnum->wCountEnum==0)
	{
		if(wKeyCode==KEY_UP)
		{
			if(s_pEditEnum->wData==0x5555) s_pEditEnum->wData = 0x3333;
// 			else s_pEditEnum->wData = 0x5555;
		}
		if(wKeyCode==KEY_DOWN)
		{
			if(s_pEditEnum->wData==0x3333) s_pEditEnum->wData = 0x5555;
// 			else s_pEditEnum->wData = 0x5555;
		}
	}
	else
	{
		if(wKeyCode==KEY_UP)
		{
			if(s_pEditEnum->wData>0) s_pEditEnum->wData--;
// 			else s_pEditEnum->wData = s_pEditEnum->wCountEnum-1;
		}
		if(wKeyCode==KEY_DOWN)
		{
			if(s_pEditEnum->wData<s_pEditEnum->wCountEnum-1) s_pEditEnum->wData++;
// 			else s_pEditEnum->wData = 0;
		}
	}
	if(wKeyCode==KEY_OK)
	{
		*(s_pEditEnum->pData) = s_pEditEnum->wData;
		MyApp_OnUpdateDevice(s_pEditEnum->pData);
		s_wEditStatus = ES_SELECT;
		LEDResetMask();
	}
	if(wKeyCode==KEY_CANCEL)
	{
		s_pEditEnum->wData = *(s_pEditEnum->pData);
		s_wEditStatus = ES_SELECT;
		LEDResetMask();
	}
	DisplayEditEnum();
}

static unsigned long GetBaseOfBCD(void)
{
	switch(s_pEditData->wCountBCD-s_wEditDataBCD)
	{
	case 1: return 1L;
	case 2: return 10L;
	case 3: return 100L;
	case 4: return 1000L;
// 	case 5: return 10000L;
// 	case 6: return 100000L;
// 	case 7: return 1000000L;
// 	case 8: return 10000000L;
	}
	return 1L;
}

static void DataWordRTtoBCD(void)
{
	if(s_pEditData->wDataRunTime==0) return;
	if(s_pEditData->wMode==EM_DATAWORD)
	{
		s_pEditData->dwData = *(s_pEditData->pData);
		s_pEditData->dwData *= s_pEditData->wScale2XX;
		s_pEditData->dwData += s_pEditData->wDataRunTime>>1;
		s_pEditData->dwData /= s_pEditData->wDataRunTime;
	}
	else s_pEditData->dwData = *((unsigned long*)(s_pEditData->pData));
	if(s_pEditData->dwData<s_pEditData->dwDataMin) s_pEditData->dwData = s_pEditData->dwDataMin;
	if(s_pEditData->dwData>s_pEditData->dwDataMax) s_pEditData->dwData = s_pEditData->dwDataMax;
}

static void DataWordBCDtoRT(void)
{
	unsigned long dwData;
	if(s_pEditData->wScale2XX==0) return;
	if(s_pEditData->wMode==EM_DATAWORD)
	{
		dwData = s_pEditData->dwData;
		dwData *= s_pEditData->wDataRunTime;
		dwData += s_pEditData->wScale2XX>>1;
		dwData /= s_pEditData->wScale2XX;
		*(s_pEditData->pData) = (unsigned short)dwData;
	}
	else *((unsigned long*)(s_pEditData->pData)) = s_pEditData->dwData;
}

static void OnEditKeyMsgData(unsigned short wKeyCode)
{
	unsigned long dwBaseOfBCD;
	unsigned short wCurSelBCD;

	dwBaseOfBCD = GetBaseOfBCD();
	wCurSelBCD = (unsigned short)((s_pEditData->dwData/dwBaseOfBCD)%10);
	s_pEditData = (struct EDITDATA*)&s_edit;
	if(wKeyCode==KEY_DOWN)
	{
		if(wCurSelBCD==0) s_pEditData->dwData += 9*dwBaseOfBCD;
		else s_pEditData->dwData -= dwBaseOfBCD;
	}
	if(wKeyCode==KEY_UP)
	{
		if(wCurSelBCD>=9) s_pEditData->dwData -= 9*dwBaseOfBCD;
		else s_pEditData->dwData += dwBaseOfBCD;
	}
	if(wKeyCode==KEY_LEFT)
	{
		if(s_wEditDataBCD>0)
		s_wEditDataBCD--;
	}
	if(wKeyCode==KEY_RIGHT)
	{
		if(s_wEditDataBCD<s_pEditData->wCountBCD-1)
		s_wEditDataBCD++;
	}
	if(wKeyCode==KEY_OK)
	{
		if(s_pEditData->dwData>=s_pEditData->dwDataMin&&s_pEditData->dwData<=s_pEditData->dwDataMax)
		{
			DataWordBCDtoRT();
			if(s_pEditData->pData==&g_wPassword)
			{
				if(g_wPassword==g_deviceParam.wPassword1) g_wPasswordLevel = PASSWORD_LEVEL1;
				if(g_wPassword==g_deviceParam.wPassword2) g_wPasswordLevel = PASSWORD_LEVEL2;
				if(g_wPassword==(6969-g_deviceTime.wMonth*100-g_deviceTime.wDay)) g_wPasswordLevel = PASSWORD_LEVEL3;

				if(g_wPasswordLevel)
				{
					if(g_wPasswordLevel==PASSWORD_LEVEL1) g_wPageAllCount = 0;		//一级密码显示页面
					else g_wPageAllCount = 6;							//二级密码显示页面
					EnterPageSetup();
					return;
				}
			}
			MyApp_OnUpdateDevice(s_pEditData->pData);
		}
		else DataWordRTtoBCD();
		s_wEditStatus = ES_SELECT;
		LEDResetMask();
	}
	if(wKeyCode==KEY_CANCEL)
	{
		DataWordRTtoBCD();
		s_wEditStatus = ES_SELECT;
		LEDResetMask();
	}
	DisplayEditData();
}


/*******************************************************************/
void EditRemoveAll(void)
{
	s_pEditEnum = 0;
	s_pEditData = 0;
	s_wEditStatus = ES_NULL;
	s_bEditShining = 0;
	MemoryClear((unsigned short*)&s_edit,SIZEOFWORD(s_edit));
}

void EditAddEnum(unsigned short* pData,char* pszEnum,unsigned short wCountEnum,unsigned short wCountChar)
{
	unsigned int i;
	AddEdit(pData);
	s_pEditEnum = (struct EDITENUM*)&s_edit;
	s_pEditEnum->wMode = EM_ENUM;
	s_pEditEnum->wCountChar = wCountChar;
	s_pEditEnum->wCountEnum = wCountEnum;
	for(i=0;i<wCountEnum;i++)
		s_pEditEnum->pszEnum[i] = pszEnum+i*(wCountChar+1);
	s_pEditEnum->wData = *pData;
	DisplayEditEnum();
}

static char c_szOFF[4];
static char c_sz_ON[4];

void EditAddToggle(unsigned short* pData)
{
	c_szOFF[0] = 'o';
	c_szOFF[1] = 'F';
	c_szOFF[2] = 'F';
	c_szOFF[3] = 0;
	c_sz_ON[0] = ' ';
	c_sz_ON[1] = 'o';
	c_sz_ON[2] = 'N';
	c_sz_ON[3] = 0;
	AddEdit(pData);
	s_pEditEnum = (struct EDITENUM*)&s_edit;
	s_pEditEnum->wMode = EM_ENUM;
	s_pEditEnum->wCountEnum = 0;
	s_pEditEnum->wCountChar = 3;
	s_pEditEnum->pszEnum[0] = c_szOFF;
	s_pEditEnum->pszEnum[1] = c_sz_ON;
	s_pEditEnum->wData = *pData;
	DisplayEditEnum();
}

void EditAddInteger(unsigned short* pData,unsigned short wDataMin,unsigned short wDataMax,unsigned short bReserveZero)
{
	unsigned short wFormat;
	if(wDataMax<=99) wFormat = 0x20;
	else if(wDataMax<=999) wFormat = 0x30;
	else if(wDataMax<=9999) wFormat = 0x40;
	else wFormat = 0x50;
	EditAddDataWord(pData,wDataMin,wDataMax,wFormat,1,1);
	s_pEditData->bReserveZero = bReserveZero;
	DisplayEditData();
}

void EditAddDataWord(unsigned short* pData,unsigned long dwDataMin,unsigned long dwDataMax,
	unsigned short wFormat,unsigned short wScale2XX,unsigned short wDataRunTime)
{
	AddEdit(pData);
	s_pEditData = (struct EDITDATA*)&s_edit;
	s_pEditData->wMode = EM_DATAWORD;
	s_pEditData->dwDataMin = dwDataMin;
	s_pEditData->dwDataMax = dwDataMax;
	s_pEditData->wFormat = wFormat;
	s_pEditData->wScale2XX = wScale2XX;
	s_pEditData->wDataRunTime = wDataRunTime;
	s_pEditData->wCountBCD = wFormat>>4;
	s_pEditData->wCountBCDAfterDot = wFormat&0x0f;
	s_pEditData->wCountBCDBeforDot = (wFormat>>4)-(wFormat&0x0f);
	DataWordRTtoBCD();
	DisplayEditData();
}

void EditAddPhQh(unsigned long* pData)
{
	AddEdit((unsigned short*)pData);
	s_pEditData = (struct EDITDATA*)&s_edit;
	s_pEditData->wMode = EM_DATADWORD;
	s_pEditData->dwDataMin = 0;
	s_pEditData->dwDataMax = 99999999;
	s_pEditData->wFormat = 0x81;
	s_pEditData->wScale2XX = 1;
	s_pEditData->wDataRunTime = 1;
	s_pEditData->wCountBCD = 8;
	s_pEditData->wCountBCDAfterDot = 1;
	s_pEditData->wCountBCDBeforDot = 7;
	DataWordRTtoBCD();
	DisplayEditData();
}

void EditEnterEdit(void)
{
	s_wEditStatus = ES_SELECT;
}

void EdiQuittEdit(void)
{
	s_wEditStatus = ES_NULL;
}

unsigned short OnEditKeyMsg(unsigned short wKeyCode)
{
	if(s_wEditStatus==ES_NULL) return wKeyCode;
	if(s_wEditStatus==ES_SELECT)
	{
		if(wKeyCode==KEY_OK)
		{
			s_wEditStatus = ES_EDITING;
			s_bEditShining = 0;
			s_wEditDataBCD = 0;
			wKeyCode = KEY_NULL;
		}
	}
	if(s_wEditStatus==ES_EDITING)
	{
		if(s_edit.wMode==EM_ENUM) OnEditKeyMsgEnum(wKeyCode);
		else OnEditKeyMsgData(wKeyCode);
		return KEY_NULL;
	}
	return wKeyCode;
}

void OnTaskEdit(void)
{
	if(s_wEditStatus==ES_EDITING)
	{
		if(s_bEditShining)
		{
			s_bEditShining = 0;
			LEDResetMask();
		}
		else
		{
			s_bEditShining = 1;
			if(s_edit.wMode==EM_ENUM)
			{
				s_pEditEnum = (struct EDITENUM*)&s_edit;
				LEDSetMask(s_pEditEnum->wPosX,s_pEditEnum->wPosY,s_pEditEnum->wCountChar);
			}
			else
			{
				s_pEditData = (struct EDITDATA*)&s_edit;
				LEDSetMask(s_pEditData->wPosX+s_wEditDataBCD,s_pEditData->wPosY,1);
			}
		}
	}
}

