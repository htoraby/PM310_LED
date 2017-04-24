#include <Main.h>

#define EDITMODE_NULL			0x0000
#define EDITMODE_ENUMMUL		0x0001
#define EDITMODE_DATAWORD		0x0002
#define EDITMODE_DATADWORD		0x0003
#define EDITMODE_IP				0x0004
#define EDITMODE_ENUMMULHZ		0x0005

#define EDITSTATUS_NULL			0x0000
#define EDITSTATUS_SELECT		0x0001
#define EDITSTATUS_EDITING		0x0002

BOOL g_IsSetTime = FALSE;

//-----------------------------------------------------------------------------
BOOL Edit_OnCreate(MyEdit* pthis,WORD wMode,WORD* pData)
{
	pthis->m_wMode = wMode;
	pthis->m_wPosX = g_wLCDAutoPosX;
	pthis->m_wPosY = g_wLCDAutoPosY;
	pthis->m_pData = pData;
	pthis->m_bLargeFont = g_bLCDLargeFont;
	pthis->m_wColor = g_wLCDColor;
	return TRUE;
}

void Edit_RefreshShining(MyEdit* pthis,WORD wAsciiIndex)
{
	WORD wPosY;
	WORD wPosX1;
	WORD wPosX2;
	if(pthis->m_bLargeFont)
	{
		wPosY = pthis->m_wPosY+16;
		wPosX1 = pthis->m_wPosX+wAsciiIndex*8;
		wPosX2 = wPosX1+7;
	}
	else
	{
		wPosY = pthis->m_wPosY+8;
		wPosX1 = pthis->m_wPosX+wAsciiIndex*6;
		wPosX2 = wPosX1+5;
	}
	g_bLCDSetDataXor = TRUE;
	if(pthis->m_bLargeFont) LCD_DrawHLine((WORD)(wPosY-2),wPosX1,wPosX2);
	LCD_DrawHLine((WORD)(wPosY-1),wPosX1,wPosX2);
	LCD_DrawHLine(wPosY,wPosX1,wPosX2);
	g_bLCDSetDataXor = FALSE;
}


//-----------------------------------------------------------------------------
BOOL EditEnum_OnCreate(MyEditEnum* pthis,WORD wMode,WORD* pData)
{
	if(Edit_OnCreate((MyEdit*)pthis,wMode,pData)==FALSE) return FALSE;
	pthis->m_wCountEnum = 0xffff;
	pthis->m_wCountChar = 0xffff;
	MyHMI_GetEditMetrics(pData);
	if(pthis->m_wCountChar==0xffff && pthis->m_wCountEnum==0xffff) return FALSE;
	pthis->m_wData = *pthis->m_pData;
	return TRUE;
}

void EditEnum_Display(MyEditEnum* pthis,BOOL bCurSel)
{
	WORD wPosY;
	wPosY = pthis->m_wPosY;
	if(pthis->m_bLargeFont) LCD_SetLargeFont();
	else LCD_SetSmallFont();
	LCD_SetColor(pthis->m_wColor);
	if(bCurSel) wPosY--;
	if(pthis->m_wCountEnum>0 && pthis->m_wData>=pthis->m_wCountEnum) LCD_AsciiOut(pthis->m_wPosX,wPosY,"ERR");
	else LCD_AsciiOut(pthis->m_wPosX,wPosY,pthis->m_pszEnum[pthis->m_wData]);
}

void EditEnum_RefreshShining(MyEditEnum* pthis)
{
	WORD i;
	for(i=0;i<pthis->m_wCountChar;i++) Edit_RefreshShining((MyEdit*)pthis,i);
}

void EditEnum_EnterEditing(MyEditEnum* pthis)
{
	EditEnum_Display(pthis,TRUE);
}

void EditEnum_OnKeyMsg(MyEditEnum* pthis,WORD wKeyCode,WORD* wEditStatus)
{
	LCD_CursorOFF();
	switch(wKeyCode)
	{
	case KEY_DOWN:
//     case KEY_SUB:
		if(pthis->m_wData<pthis->m_wCountEnum-1) pthis->m_wData++;
		else pthis->m_wData = 0;
		break;
	case KEY_UP:
//	case KEY_ADD:
		if(pthis->m_wData>0) pthis->m_wData--;
		else pthis->m_wData = pthis->m_wCountEnum-1;
		break;
	case KEY_OK:
		*pthis->m_pData = pthis->m_wData;
		MyApp_OnUpdateDevice(pthis->m_pData, FALSE);
		*wEditStatus = EDITSTATUS_SELECT;
		break;
	case KEY_CANCEL:
		pthis->m_wData = *pthis->m_pData;
		*wEditStatus = EDITSTATUS_SELECT;
		break;
	}
	LCD_EraseCursor();
	EditEnum_Display(pthis,*wEditStatus==EDITSTATUS_EDITING);
	LCD_CursorON();
}

WORD EditEnum_GetCountChar(MyEditEnum* pthis)
{
	return pthis->m_wCountChar;
}

//-----------------------------------------------------------------------------
void EditEnumHz_Display(MyEditEnumHz* pthis,BOOL bCurSel)
{
	WORD wPosY;
	wPosY = pthis->m_wPosY;
	if(pthis->m_bLargeFont) LCD_SetLargeFont();
	else LCD_SetSmallFont();
	LCD_SetColor(pthis->m_wColor);
	if(bCurSel) wPosY--;
	if(pthis->m_wCountEnum>0 && pthis->m_wData>=pthis->m_wCountEnum) LCD_TextOut(pthis->m_wPosX,wPosY,"ERR");
	else LCD_TextOut(pthis->m_wPosX,wPosY,pthis->m_pszEnum[pthis->m_wData]);
}

void EditEnumHz_RefreshShining1(MyEditEnumHz* pthis,WORD wIndex)
{
	WORD wPosY;
	WORD wPosX1;
	WORD wPosX2;
	if(pthis->m_bLargeFont)
	{
		wPosY = pthis->m_wPosY+20;
		wPosX1 = pthis->m_wPosX+wIndex*8;
		wPosX2 = wPosX1+7;
	}
	else
	{
		wPosY = pthis->m_wPosY+13;
		wPosX1 = pthis->m_wPosX+wIndex*6;
		wPosX2 = wPosX1+5;
	}
	g_bLCDSetDataXor = TRUE;
	if(pthis->m_bLargeFont) LCD_DrawHLine((WORD)(wPosY-2),wPosX1,wPosX2);
	LCD_DrawHLine((WORD)(wPosY-1),wPosX1,wPosX2);
	LCD_DrawHLine(wPosY,wPosX1,wPosX2);
	g_bLCDSetDataXor = FALSE;
}

void EditEnumHz_RefreshShining(MyEditEnumHz* pthis)
{
	WORD i;
	for(i=0;i<pthis->m_wCountChar;i++) EditEnumHz_RefreshShining1(pthis,i);
}

void EditEnumHz_EnterEditing(MyEditEnumHz* pthis)
{
	EditEnumHz_Display(pthis,TRUE);
}

void EditEnumHZ_OnKeyMsg(MyEditEnumHz* pthis,WORD wKeyCode,WORD* wEditStatus)
{
	LCD_CursorOFF();
	switch(wKeyCode)
	{
	case KEY_DOWN:
// 	case KEY_SUB:
		if(pthis->m_wData<pthis->m_wCountEnum-1) pthis->m_wData++;
		else pthis->m_wData = 0;
		break;
	case KEY_UP:
// 	case KEY_ADD:
		if(pthis->m_wData>0) pthis->m_wData--;
		else pthis->m_wData = pthis->m_wCountEnum-1;
		break;
	case KEY_OK:
		*pthis->m_pData = pthis->m_wData;
		MyApp_OnUpdateDevice(pthis->m_pData, FALSE);
		*wEditStatus = EDITSTATUS_SELECT;
		break;
	case KEY_CANCEL:
		pthis->m_wData = *pthis->m_pData;
		*wEditStatus = EDITSTATUS_SELECT;
		break;
	}
	LCD_EraseCursor();
	EditEnumHz_Display(pthis,*wEditStatus==EDITSTATUS_EDITING);
	LCD_CursorON();
}


//-----------------------------------------------------------------------------
BOOL EditData_OnCreate(MyEditData* pthis,WORD wMode,WORD* pData)
{
	if(Edit_OnCreate((MyEdit*)pthis,wMode,pData)==FALSE) return FALSE;
	pthis->m_dwDataMin = 0xffffffff;
	pthis->m_dwDataMax = 0xffffffff;
	pthis->m_bReserveZero = 0;
	if(pData==&g_wInputPassword)
	{
		pthis->m_dwDataMin = 0;
		pthis->m_dwDataMax = 99;
		pthis->m_wFormat = 0x20;
		pthis->m_bReserveZero = TRUE;
	}
	else MyHMI_GetEditMetrics(pData);
	if(pthis->m_dwDataMin==0xffffffff && pthis->m_dwDataMax==0xffffffff) return FALSE;
	if((pthis->m_wFormat>>4)<=(pthis->m_wFormat&0x0f)) return FALSE;
	EditData_RuntimeDataToEditData(pthis);
	pthis->m_wEditDataBCD = 0;
	return TRUE;
}

void EditData_Display(MyEditData* pthis,BOOL bCurSel)
{
	WORD wPosY;
	wPosY = pthis->m_wPosY;
	if(pthis->m_bReserveZero) g_bLCDFormatRealFillBlank = FALSE;
	if(bCurSel)
	{
		wPosY--;
		g_bLCDFormatRealFillBlank = FALSE;
	}
	if(pthis->m_bLargeFont) LCD_SetLargeFont();
	else LCD_SetSmallFont();
	LCD_SetColor(pthis->m_wColor);
	LCD_RealOut(pthis->m_wPosX,wPosY,pthis->m_dwData,pthis->m_wFormat);
	g_bLCDFormatRealFillBlank = TRUE;
}

void EditData_RefreshShining(MyEditData* pthis)
{
	if(pthis->m_wEditDataBCD<(pthis->m_wFormat>>4)-(pthis->m_wFormat&0x0f))
		Edit_RefreshShining((MyEdit*)pthis,pthis->m_wEditDataBCD);
	else Edit_RefreshShining((MyEdit*)pthis,(WORD)(pthis->m_wEditDataBCD+1));
}

void EditData_EnterEditing(MyEditData* pthis)
{
	EditData_Display(pthis,TRUE);
	pthis->m_wEditDataBCD = 0;
}

void EditData_OnKeyMsg(MyEditData* pthis,WORD wKeyCode,WORD* wEditStatus)
{
	DWORD dwBaseOfBCD;
	WORD wCurSelBCD;
	switch((pthis->m_wFormat>>4)-pthis->m_wEditDataBCD)
	{
	case 1: dwBaseOfBCD = 1L; break;
	case 2: dwBaseOfBCD = 10L; break;
	case 3: dwBaseOfBCD = 100L; break;
	case 4: dwBaseOfBCD = 1000L; break;
	case 5: dwBaseOfBCD = 10000L; break;
	case 6: dwBaseOfBCD = 100000L; break;
	case 7: dwBaseOfBCD = 1000000L; break;
	case 8: dwBaseOfBCD = 10000000L; break;
	default: dwBaseOfBCD = 1L; break;
	}
	wCurSelBCD = (WORD)((pthis->m_dwData/dwBaseOfBCD)%10);
	LCD_CursorOFF();
	switch(wKeyCode)
	{
	case KEY_DOWN:
// 	case KEY_SUB:
		if(wCurSelBCD==0) pthis->m_dwData += 9*dwBaseOfBCD;
		else pthis->m_dwData -= dwBaseOfBCD;
		break;
	case KEY_UP:
// 	case KEY_ADD:
		if(wCurSelBCD>=9) pthis->m_dwData -= 9*dwBaseOfBCD;
		else pthis->m_dwData += dwBaseOfBCD;
		break;
	case KEY_LEFT:
		if(pthis->m_wEditDataBCD>0)
			--pthis->m_wEditDataBCD;
		break;
	case KEY_RIGHT:
		if(pthis->m_wEditDataBCD<(pthis->m_wFormat>>4)-1)
			++pthis->m_wEditDataBCD;
		break;
	case KEY_OK:
		if(pthis->m_wEditDataBCD<(pthis->m_wFormat>>4)-1)
        {
            ++pthis->m_wEditDataBCD;
            break;
        }
		EditData_EditDataToRuntimeData(pthis);
		if(Menu_EnterSubMenuSetup(pthis->m_pData)) return;
		*wEditStatus = EDITSTATUS_SELECT;
		break;
	case KEY_CANCEL:
		EditData_RuntimeDataToEditData(pthis);
		*wEditStatus = EDITSTATUS_SELECT;
		break;
	}
	LCD_EraseCursor();
	EditData_Display(pthis,*wEditStatus==EDITSTATUS_EDITING);
	LCD_CursorON();
}

WORD EditData_GetCountChar(MyEditData* pthis)
{
	WORD wCountChar = (pthis->m_wFormat>>4);
	if(pthis->m_wFormat&0x0f) wCountChar++;
	return wCountChar;
}

void EditData_RuntimeDataToEditData(MyEditData* pthis)
{
	DWORD dwData;
	if(pthis->m_wMode==EDITMODE_DATAWORD) dwData = *((WORD*)pthis->m_pData);
	else dwData = *((DWORD*)pthis->m_pData);
	if(dwData<pthis->m_dwDataMin) dwData = pthis->m_dwDataMin;
	if(dwData>pthis->m_dwDataMax) dwData = pthis->m_dwDataMax;
	pthis->m_dwData = dwData;
}

void EditData_EditDataToRuntimeData(MyEditData* pthis)
{
	DWORD dwData;
	dwData = pthis->m_dwData;
	if(dwData>=pthis->m_dwDataMin&&dwData<=pthis->m_dwDataMax)
	{
		if(pthis->m_wMode==EDITMODE_DATAWORD) *pthis->m_pData = (WORD)dwData;
		else *((DWORD*)pthis->m_pData) = dwData;
		MyApp_OnUpdateDevice(pthis->m_pData, FALSE);
	}
	else EditData_RuntimeDataToEditData(pthis);
}

static WORD s_wEditBuffer[EDIT_COUNTMAX][EDIT_BUFFERSIZE];
static WORD s_wEditCount;				//编辑项个数;
static WORD s_wEditCurSel;				//当前选中的编辑项;
static WORD s_wEditStatus;				//当前编辑状态;

//-----------------------------------------------------------------------------
MyEditEnum* EditG_GetEditEnumCurSel(void)
{
	if(s_wEditCurSel<EDIT_COUNTMAX)
	{
		MyEdit* pEdit = (MyEdit*)&s_wEditBuffer[s_wEditCurSel][0];
		if(pEdit->m_wMode==EDITMODE_ENUMMUL) return (MyEditEnum*)pEdit;
	}
	return NULL;
}

MyEditEnumHz* EditG_GetEditEnumHzCurSel(void)
{
	if(s_wEditCurSel<EDIT_COUNTMAX)
	{
		MyEdit* pEdit = (MyEdit*)&s_wEditBuffer[s_wEditCurSel][0];
		if(pEdit->m_wMode==EDITMODE_ENUMMULHZ) return (MyEditEnumHz*)pEdit;
	}
	return NULL;
}

MyEditData* EditG_GetEditDataCurSel(void)
{
	if(s_wEditCurSel<EDIT_COUNTMAX)
	{
		MyEdit* pEdit = (MyEdit*)&s_wEditBuffer[s_wEditCurSel][0];
		if(pEdit->m_wMode==EDITMODE_DATAWORD||pEdit->m_wMode==EDITMODE_DATADWORD) return (MyEditData*)pEdit;
	}
	return NULL;
}

void EditG_AddEdit(WORD wMode,WORD* pData)
{
	MyEdit* pEdit;
	MyEditEnum* pEditEnum;
	MyEditEnumHz* pEditEnumHz;
	MyEditData* pEditData;
	if(pData==NULL) return;
	if(g_wLCDAutoPosX>=LCD_CXDOT) return;
	if(g_wLCDAutoPosY>=LCD_CYDOT) return;
	if(s_wEditCount>=EDIT_COUNTMAX) return;
	pEdit = (MyEdit*)&s_wEditBuffer[s_wEditCount][0];
	s_wEditCurSel = s_wEditCount;
	if(wMode==EDITMODE_ENUMMUL)
	{
		if(SIZEOFWORD(MyEditEnum)>EDIT_BUFFERSIZE) return;
		pEditEnum = (MyEditEnum*)pEdit;
		if(EditEnum_OnCreate(pEditEnum,wMode,pData)==FALSE) return;
	}
	else if(wMode==EDITMODE_ENUMMULHZ)
	{
		if(SIZEOFWORD(MyEditEnumHz)>EDIT_BUFFERSIZE) return;
		pEditEnumHz = (MyEditEnumHz*)pEdit;
		if(EditEnum_OnCreate((MyEditEnum*)pEditEnumHz,wMode,pData)==FALSE) return;
	}
	else if(wMode==EDITMODE_DATAWORD||wMode==EDITMODE_DATADWORD)
	{
		if(SIZEOFWORD(MyEditData)>EDIT_BUFFERSIZE) return;
		pEditData = (MyEditData*)pEdit;
		if(EditData_OnCreate(pEditData,wMode,pData)==FALSE) return;
	}
	else return;
	s_wEditCount++;
}

void EditG_EditCursorON(void)
{
	MyEditEnum* pEditEnum;
	MyEditEnumHz* pEditEnumHz;
	MyEditData* pEditData;
	WORD wCountChar;
	WORD wPosX;
	MyEdit* pEdit;
	WORD wCursorHeight,wCharWidth;

	pEditEnum = EditG_GetEditEnumCurSel();
	pEditEnumHz = EditG_GetEditEnumHzCurSel();
	pEditData = EditG_GetEditDataCurSel();

	if(pEditEnum==NULL && pEditEnumHz==NULL && pEditData==NULL) return;
	pEdit = NULL;
	if(pEditEnum)
	{
		wCountChar = EditEnum_GetCountChar(pEditEnum);
		pEdit = (MyEdit*)pEditEnum;
		wPosX = pEdit->m_wPosX;
	}
	if(pEditEnumHz)
	{
		wCountChar = EditEnum_GetCountChar((MyEditEnum*)pEditEnumHz);
		pEdit = (MyEdit*)pEditEnumHz;
		wPosX = pEdit->m_wPosX;
	}
	if(pEditData)
	{
		wCountChar = EditData_GetCountChar(pEditData);
		pEdit = (MyEdit*)pEditData;
		wPosX = pEdit->m_wPosX;
	}

	if(pEdit)
	{
		if(pEdit->m_bLargeFont)
		{
			wCursorHeight = pEditEnumHz?29:21;
			wCharWidth = 8;
		}
		else
		{
			wCursorHeight = pEditEnumHz?18:13;
			wCharWidth = 6;
		}

		LCD_SetCursorPosY((WORD)(pEdit->m_wPosY-3),wCursorHeight);
		LCD_SetCursorPosX((WORD)(wPosX-2),(WORD)(wCountChar*wCharWidth+3));
		LCD_CursorON();
		return;
	}
}


//-----------------------------------------------------------------------------
void EditG_OnInit(void)
{
	s_wEditCount = 0;
	s_wEditCurSel = 0;
	s_wEditStatus = EDITSTATUS_NULL;
}

void EditG_AddEditEnumMul(WORD* pData)
{
	EditG_AddEdit(EDITMODE_ENUMMUL,pData);
	g_wLCDAutoPosY += g_wLCDAutoEnter;
}

void EditG_AddEditEnumHzMul(WORD* pData)
{
	EditG_AddEdit(EDITMODE_ENUMMULHZ,pData);
	g_wLCDAutoPosY += g_wLCDAutoEnter;
}

void EditG_AddEditDataWord(WORD* pData)
{
	EditG_AddEdit(EDITMODE_DATAWORD,pData);
	g_wLCDAutoPosY += g_wLCDAutoEnter;
}

void EditG_AddEditDataDWord(DWORD* pData)
{
	EditG_AddEdit(EDITMODE_DATADWORD,(WORD*)pData);
	g_wLCDAutoPosY += g_wLCDAutoEnter;
}

void EditG_OnRefreshPage(void)
{
	WORD i;
	WORD wEditCurSelOld;
	MyEditEnum* pEditEnum;
	MyEditEnumHz* pEditEnumHz;
	MyEditData* pEditData;

	LCD_CursorOFF();
	for(i=0;i<s_wEditCount;i++)
	{
		if(s_wEditStatus==EDITSTATUS_EDITING && i==s_wEditCurSel) continue;
		wEditCurSelOld = s_wEditCurSel;
		s_wEditCurSel = i;
		pEditEnum = EditG_GetEditEnumCurSel();
		pEditEnumHz = EditG_GetEditEnumHzCurSel();
		pEditData = EditG_GetEditDataCurSel();
		if(pEditEnum) EditEnum_Display(pEditEnum,FALSE);
		if(pEditEnumHz) EditEnumHz_Display(pEditEnumHz,FALSE);
		if(pEditData) EditData_Display(pEditData,FALSE);
		s_wEditCurSel = wEditCurSelOld;
	}
	if(s_wEditStatus!=EDITSTATUS_NULL) EditG_EditCursorON();
}

void EditG_EnableEdit(WORD wRefreshMode)
{
	s_wEditCurSel = 0;
	if(s_wEditCount==0||s_wEditCount>EDIT_COUNTMAX) return;
	if(wRefreshMode==RM_PAGEUP) s_wEditCurSel = s_wEditCount-1;
	EditG_EditCursorON();
	s_wEditStatus = EDITSTATUS_SELECT;
}

WORD EditG_OnKeyMsg(WORD wKeyCode)
{
	MyEditEnum* pEditEnum;
	MyEditEnumHz* pEditEnumHz;
	MyEditData* pEditData;

	if(s_wEditStatus==EDITSTATUS_NULL) return wKeyCode;
	pEditEnum = EditG_GetEditEnumCurSel();
	pEditEnumHz = EditG_GetEditEnumHzCurSel();
	pEditData = EditG_GetEditDataCurSel();

	if(s_wEditStatus==EDITSTATUS_SELECT)
	{
		LCD_CursorOFF();
		if(wKeyCode==KEY_UP)
		{
			if(s_wEditCurSel>(g_IsSetTime?2:0))			// 时间设置必须这种格式:XX-XX-XX
														//						XX:XX:XX
			{
				s_wEditCurSel -= g_IsSetTime?3:1;
				wKeyCode = KEY_NULL;
			}
		}
		else if(wKeyCode==KEY_DOWN)
		{
			if(s_wEditCurSel<(g_IsSetTime?3:(s_wEditCount-1)))
			{
				s_wEditCurSel += g_IsSetTime?3:1;
				wKeyCode = KEY_NULL;
			}
		}
		else if(wKeyCode==KEY_LEFT)
		{
			if(g_IsSetTime)
			if(s_wEditCurSel>0)
			{
				s_wEditCurSel--;
				wKeyCode = KEY_NULL;
			}
		}
		else if(wKeyCode==KEY_RIGHT)
		{
			if(g_IsSetTime)
			if(s_wEditCurSel<s_wEditCount-1)
			{
				s_wEditCurSel++;
				wKeyCode = KEY_NULL;
			}
		}
		else if(wKeyCode==KEY_OK)
		{
			s_wEditStatus = EDITSTATUS_EDITING;
			if(pEditEnum) EditEnum_EnterEditing(pEditEnum);
			if(pEditEnumHz) EditEnumHz_EnterEditing(pEditEnumHz);
			if(pEditData) EditData_EnterEditing(pEditData);
			wKeyCode = KEY_NULL;
		}
		EditG_EditCursorON();
	}
	else if(s_wEditStatus==EDITSTATUS_EDITING)
	{
		if(pEditEnum) EditEnum_OnKeyMsg(pEditEnum,wKeyCode,&s_wEditStatus);
		if(pEditEnumHz) EditEnumHZ_OnKeyMsg(pEditEnumHz,wKeyCode,&s_wEditStatus);
		if(pEditData) EditData_OnKeyMsg(pEditData,wKeyCode,&s_wEditStatus);
		wKeyCode = KEY_NULL;
	}
	return wKeyCode;
}

void EditG_OnTimer250ms(void)
{
	MyEditEnum* pEditEnum;
	MyEditEnumHz* pEditEnumHz;
	MyEditData* pEditData;

	if(s_wEditStatus!=EDITSTATUS_EDITING) return;
	pEditEnum = EditG_GetEditEnumCurSel();
	pEditEnumHz = EditG_GetEditEnumHzCurSel();
	pEditData = EditG_GetEditDataCurSel();
	if(pEditEnum) EditEnum_RefreshShining(pEditEnum);
	if(pEditEnumHz) EditEnumHz_RefreshShining(pEditEnumHz);
	if(pEditData) EditData_RefreshShining(pEditData);
}

void EditG_SetEditEnumMetricsTog(void)
{
	MyEditEnum* pEditEnum;

	pEditEnum = EditG_GetEditEnumCurSel();
	if(pEditEnum==NULL) return;
	pEditEnum->m_wCountEnum = 2;
	pEditEnum->m_wCountChar = 3;
	pEditEnum->m_pszEnum[0] = "OFF";
	pEditEnum->m_pszEnum[1] = " ON";
}

void EditG_SetEditEnumMetricsMul(WORD wCountEnum,WORD wCountChar,char* pszEnum)
{
	MyEditEnum* pEditEnum;
	WORD i;

	if(wCountChar==0) return;
	pEditEnum = EditG_GetEditEnumCurSel();
	if(pEditEnum==NULL) return;
	if(wCountEnum>EDIT_ENUMSZMAX) wCountEnum = EDIT_ENUMSZMAX;
	pEditEnum->m_wCountEnum = wCountEnum;
	pEditEnum->m_wCountChar = wCountChar-1;
	for(i=0;i<wCountEnum;i++) pEditEnum->m_pszEnum[i] = pszEnum+i*(wCountChar);
}

void EditG_SetEditEnumHzMetricsMul(WORD wCountEnum,WORD wCountChar,char* pszEnum)
{
	MyEditEnumHz* pEditEnumHz;
	WORD i;
	
	if(wCountChar==0) return;
	pEditEnumHz = EditG_GetEditEnumHzCurSel();
	if(pEditEnumHz==NULL) return;
	if(wCountEnum>EDIT_ENUMSZMAX) wCountEnum = EDIT_ENUMSZMAX;
	pEditEnumHz->m_wCountEnum = wCountEnum;
	pEditEnumHz->m_wCountChar = wCountChar-1;
	for(i=0;i<wCountEnum;i++) pEditEnumHz->m_pszEnum[i] = pszEnum+i*(wCountChar);
}


void EditG_SetEditDataMetricsInteger(WORD wDataMin,WORD wDataMax,BOOL bReserveZero)
{
	MyEditData* pEditData;
	pEditData = EditG_GetEditDataCurSel();

	if(pEditData==NULL) return;
	pEditData->m_dwDataMin = wDataMin;
	pEditData->m_dwDataMax = wDataMax;
    if(wDataMax<=9) pEditData->m_wFormat = 0x10;
	else if(wDataMax<=99) pEditData->m_wFormat = 0x20;
	else if(wDataMax<=999) pEditData->m_wFormat = 0x30;
	else if(wDataMax<=9999) pEditData->m_wFormat = 0x40;
	pEditData->m_bReserveZero = bReserveZero;
}

void EditG_SetEditDataMetricsReal(DWORD dwDataMin,DWORD dwDataMax,WORD wFormat)
{
	MyEditData* pEditData;
	pEditData = EditG_GetEditDataCurSel();

	if(pEditData==NULL) return;
	pEditData->m_dwDataMin = dwDataMin;
	pEditData->m_dwDataMax = dwDataMax;
	pEditData->m_wFormat = wFormat;
	pEditData->m_bReserveZero = 0;
}

