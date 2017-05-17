//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#include "main.h"

//-----------------------------------------------------------------------------
enum EDITMODE
{
    EM_NULL = 0x0000,
    EM_ENUMMUL,
    EM_DATAWORD,
    EM_DATADWORD,
};

enum EDITSTATUS
{
    ES_NULL = 0x0000,
    ES_SELECT,
    ES_EDITING,
};

typedef struct
{
    WORD wMode;             // 编辑项模式
    WORD wPosX;             // 编辑项X坐标
    WORD wPosY;             // 编辑项Y坐标
    WORD wBlinkStatus;      // 闪烁状态
    WORD* pData;            // 编辑项数据指针
}stEDIT;

typedef struct
{
    stEDIT Base;
    WORD wData;             // 编辑项暂存数据,无须关心;
    WORD wCountChar;        // 枚举类型的最大字符数,须赋值;
    WORD wCountEnum;        // 枚举类型的最大枚举项,须赋值;
    char* pszEnum;          // 枚举类型的所有枚举项文本,须赋值;
}stEDITENUM;

typedef struct
{
    stEDIT Base;
    DWORD dwData;           // 编辑项暂存数据,无须关心;
    DWORD dwDataMin;        // 编辑数据下限,须赋值;
    DWORD dwDataMax;        // 编辑数据上限,须赋值;
    WORD wFormat;           // 编辑数据的格式
}stEDITDATA;

#define BUFFERSIZE          MAX(SIZEOFWORD(stEDITDATA), SIZEOFWORD(stEDITENUM))
#define EDIT_BUFFERSIZE     (((WORD)(BUFFERSIZE+1))&0xfffe)      // 4字节对齐

//-----------------------------------------------------------------------------
BOOL EditBase_OnCreate(stEDIT* pEdit, WORD wMode, WORD* pData)
{
    pEdit->wMode = wMode;
    pEdit->wPosX = g_wLEDAutoPosX;
    pEdit->wPosY = g_wLEDAutoPosY;
    pEdit->pData = pData;
    pEdit->wBlinkStatus = 0;
    return TRUE;
}

void EditBase_Blinking(stEDIT* pEdit, WORD wASCIIIndex, char ch)
{
    WORD wPosX;
    char pch[2];
    wPosX = pEdit->wPosX + wASCIIIndex;
    pch[0] = (pEdit->wBlinkStatus&0x01)?ch:' ';
    pch[1] = 0;
    LED_ASCIIOut(wPosX, pEdit->wPosY, pch);
}


//-----------------------------------------------------------------------------
BOOL EditEnum_OnCreate(stEDITENUM* pEditEnum, WORD wMode, WORD* pData)
{
    stEDIT* pEdit = &pEditEnum->Base;
    if(EditBase_OnCreate(pEdit, wMode, pData)==FALSE) return FALSE;
    pEditEnum->wCountEnum = 0xffff;
    pEditEnum->wCountChar = 0xffff;
    MyHMI_GetEditMetrics(pData);
    if(pEditEnum->wCountEnum || pEditEnum->wCountChar) return FALSE;
    pEditEnum->wData = *pData;
    return TRUE;
}

void EditEnum_Display(stEDITENUM* pEditEnum, BOOL bCurSel)
{
    if(!bCurSel)
    {
        stEDIT* pEdit = &pEditEnum->Base;
        char** pch = (char**)&pEditEnum->pszEnum;
        if(pEditEnum->wCountEnum>0 && pEditEnum->wData>=pEditEnum->wCountEnum) pEditEnum->wData = 0;
        LED_ASCIIOut(pEdit->wPosX, pEdit->wPosY, pch[pEditEnum->wData]);
        pEdit->wBlinkStatus = 0;
    }
}

void EditEnum_Blinking(stEDITENUM* pEditEnum)
{
    short i;
    short nLen;
    char* pChTmp;

    stEDIT* pEdit = &pEditEnum->Base;
    char** pch = (char**)&pEditEnum->pszEnum;
    char ch[16];
    if(pEditEnum->wCountEnum>0 && pEditEnum->wData>=pEditEnum->wCountEnum) pEditEnum->wData = 0;
    nLen = pEditEnum->wCountChar;
    if(nLen>=15) nLen = 15;
    for(i=0;i<nLen;i++)
    {
        ch[i] = ' ';
    }
    ch[i] = '\0';
    
    pChTmp = (pEdit->wBlinkStatus&0x01)?pch[pEditEnum->wData]:ch;
    LED_ASCIIOut(pEdit->wPosX, pEdit->wPosY, pChTmp);
    pEdit->wBlinkStatus++;
}

void EditEnum_EnterEditing(stEDITENUM* pEditEnum)
{
    EditEnum_Display(pEditEnum, TRUE);
}

WORD EditEnum_OnKeyMsg(stEDITENUM* pEditEnum, WORD wKeyCode, WORD* pwEditStatus)
{
    switch(wKeyCode)
    {
    case KEY_UP:
        pEditEnum->wData += pEditEnum->wCountEnum;
        pEditEnum->wData--;
        pEditEnum->wData %= pEditEnum->wCountEnum;
        wKeyCode = KEY_NULL;
        break;
    case KEY_DOWN:
        pEditEnum->wData++;
        pEditEnum->wData %= pEditEnum->wCountEnum;
        wKeyCode = KEY_NULL;
        break;
    case KEY_ENTER:
        *pEditEnum->Base.pData = pEditEnum->wData;
        MyApp_OnUpdateDevice(pEditEnum->Base.pData, FALSE);
        *pwEditStatus = ES_SELECT;
        wKeyCode = KEY_NULL;
        break;
    case KEY_CANCEL:
        pEditEnum->wData = *pEditEnum->Base.pData;
        *pwEditStatus = ES_SELECT;
        break;
    }
    EditEnum_Display(pEditEnum, *pwEditStatus==ES_EDITING);
    return wKeyCode;
}

WORD EditEnum_GetCountChar(stEDITENUM* pEditEnum)
{
    return pEditEnum->wCountChar;
}


//-----------------------------------------------------------------------------
void EditData_RuntimeDataToEditData(stEDITDATA* pEditData)
{
    DWORD dwData;
    stEDIT* pEdit = &pEditData->Base;

    if(pEdit->wMode==EM_DATAWORD) dwData = *((WORD*)pEdit->pData);
    else dwData = *((DWORD*)pEdit->pData);
    if(dwData<pEditData->dwDataMin) dwData = pEditData->dwDataMin;
    if(dwData>pEditData->dwDataMax) dwData = pEditData->dwDataMax;
    pEditData->dwData = dwData;
}

void EditData_EditDataToRuntimeData(stEDITDATA* pEditData)
{
    DWORD dwData = pEditData->dwData;
    stEDIT* pEdit = &pEditData->Base;
    if(dwData>=pEditData->dwDataMin&&dwData<=pEditData->dwDataMax)
    {
        if(pEdit->wMode==EM_DATAWORD) *pEdit->pData = (WORD)dwData;
        else *((DWORD*)pEdit->pData) = dwData;
        MyApp_OnUpdateDevice(pEdit->pData, FALSE);
    }
    else EditData_RuntimeDataToEditData(pEditData);
}

BOOL EditData_OnCreate(stEDITDATA* pEditData, WORD wMode, WORD* pData)
{
    stEDIT* pEdit = &pEditData->Base;
    if(EditBase_OnCreate(pEdit, wMode, pData)==FALSE) return FALSE;
    pEditData->dwDataMin = 0xffffffff;
    pEditData->dwDataMax = 0xffffffff;
    MyHMI_GetEditMetrics(pData);
    if(pEditData->dwDataMin==0xffffffff || pEditData->dwDataMax==0xffffffff) return FALSE;
    if((pEditData->wFormat>>4)<=(pEditData->wFormat&0x0f)) return FALSE;
    EditData_RuntimeDataToEditData(pEditData);
    return TRUE;
}

void EditData_Display(stEDITDATA* pEditData, BOOL bCurSel)
{
    if(!bCurSel)
    {
        LED_RealOut(pEditData->Base.wPosX, pEditData->Base.wPosY,
            pEditData->dwData, pEditData->wFormat);
        pEditData->Base.wBlinkStatus = 0;
    }
}

void EditData_Blinking(stEDITDATA* pEditData)
{
    if(pEditData->Base.wBlinkStatus&0x01)
    {
        LED_RealOut(pEditData->Base.wPosX, pEditData->Base.wPosY,
            pEditData->dwData, pEditData->wFormat);
    }
    else
    {
        short i;
        char ch[16];
        short nLen = pEditData->wFormat>>4;
        if(nLen>=15) nLen = 15;
        for(i=0;i<nLen;i++)
        {
            ch[i] = ' ';
        }
        ch[i] = '\0';

        LED_ASCIIOut(pEditData->Base.wPosX, pEditData->Base.wPosY, ch);
    }
    pEditData->Base.wBlinkStatus++;
}

void EditData_EnterEditing(stEDITDATA* pEditData)
{
    EditData_Display(pEditData, TRUE);
}

WORD EditData_OnKeyMsg(stEDITDATA* pEditData, WORD wKeyCode, WORD* pwEditStatus)
{
    switch(wKeyCode)
    {
    case KEY_UP:
        if(pEditData->dwData>pEditData->dwDataMin) pEditData->dwData--;
        else pEditData->dwData = pEditData->dwDataMax;
        wKeyCode = KEY_NULL;
        break;
    case KEY_DOWN:
        if(pEditData->dwData<pEditData->dwDataMax) pEditData->dwData++;
        else pEditData->dwData = pEditData->dwDataMin;
        wKeyCode = KEY_NULL;
        break;
    case KEY_ENTER:
        EditData_EditDataToRuntimeData(pEditData);
        *pwEditStatus = ES_SELECT;
        wKeyCode = KEY_NULL;
        break;
    case KEY_CANCEL:
        EditData_RuntimeDataToEditData(pEditData);
        *pwEditStatus = ES_SELECT;
        break;
    }
    EditData_Display(pEditData, *pwEditStatus==ES_EDITING);
    return wKeyCode;
}

WORD EditData_GetCountChar(stEDITDATA* pEditData)
{
    WORD wCountChar = (pEditData->wFormat>>4);
    return wCountChar;
}

static WORD s_wEditCount = 0 ;           // 编辑项个数
static WORD s_wEditCurSel = 0;           // 当前选中的编辑项
static WORD s_wEditStatus = 0;           // 当前编辑状态
// static WORD s_wEditMaxCount = 0;
// static WORD s_wEnumMaxCount = 0;
// static WORD s_wEditBuffsize = 0;
static WORD s_wEditBuffer[EDIT_COUNTMAX][EDIT_BUFFERSIZE];
// static stEDITENUM* s_pEditEnum;
// static stEDITDATA* s_pEditData;

//-----------------------------------------------------------------------------
stEDITENUM* Edit_GetEditEnumCurSel(void)
{
    if(s_wEditCurSel<s_wEditCount)
    {
        stEDIT* pEdit = (stEDIT*)&s_wEditBuffer[s_wEditCurSel];
        if(pEdit->wMode==EM_ENUMMUL) return (stEDITENUM*)pEdit;
    }
    return NULL;
}

stEDITDATA* Edit_GetEditDataCurSel(void)
{
    if(s_wEditCurSel<s_wEditCount)
    {
        stEDIT* pEdit = (stEDIT*)&s_wEditBuffer[s_wEditCurSel];
        if(pEdit->wMode==EM_DATAWORD || pEdit->wMode==EM_DATADWORD) return (stEDITDATA*)pEdit;
    }
    return NULL;
}

void Edit_AddEdit(WORD wMode, WORD* pData)
{
    stEDIT* pEdit;
    if(pData==NULL) return;
    if(g_wLEDAutoPosX>=c_wLEDX) return;
    if(g_wLEDAutoPosY>=c_wLEDY) return;
    if(s_wEditCount>=EDIT_COUNTMAX) return;
    pEdit = (stEDIT*)&s_wEditBuffer[s_wEditCount];
    s_wEditCurSel = s_wEditCount;
    if(wMode==EM_ENUMMUL)
    {
        stEDITENUM* pEditEnum = (stEDITENUM*)pEdit;
        if(SIZEOFWORD(stEDITENUM)>EDIT_BUFFERSIZE) return;
        if(EditEnum_OnCreate(pEditEnum, wMode,pData)==FALSE) return;
    }
    else if(wMode==EM_DATAWORD || wMode==EM_DATADWORD)
    {
        stEDITDATA* pEditData = (stEDITDATA*)pEdit;
        if(SIZEOFWORD(stEDITDATA)>EDIT_BUFFERSIZE) return;
        if(EditData_OnCreate(pEditData, wMode,pData)==FALSE) return;
    }
    else return;
    s_wEditCount++;
}

void Edit_OnInit(void)
{
    s_wEditCount = 0;
    s_wEditCurSel = 0;
    s_wEditStatus = ES_NULL;
}

void Edit_AddEditEnumMul(WORD* pData)
{
    Edit_AddEdit(EM_ENUMMUL, pData);
}

void Edit_AddEditDataWord(WORD* pData)
{
    Edit_AddEdit(EM_DATAWORD,pData);
}

void Edit_AddEditDataDWord(DWORD* pData)
{
    Edit_AddEdit(EM_DATADWORD, (WORD*)pData);
}

void Edit_OnRefreshPage(void)
{
    short i;
    for(i=0; i<s_wEditCount; i++)
    {
        stEDITENUM* pEditEnum;
        stEDITDATA* pEditData;
        WORD wEditCurSelOld = s_wEditCurSel;
        if(s_wEditStatus==ES_EDITING && i==s_wEditCurSel) continue;
        s_wEditCurSel = i;
        pEditEnum = Edit_GetEditEnumCurSel();
        pEditData = Edit_GetEditDataCurSel();
        if(pEditEnum)
        {
            EditEnum_Display(pEditEnum, FALSE);
        }
        if(pEditData)
        {
            EditData_Display(pEditData, FALSE);
        }
        s_wEditCurSel = wEditCurSelOld;
    }
}

void Edit_EnableEdit(WORD wRefreshMode)
{
    if(s_wEditStatus!=ES_NULL) return;
    s_wEditStatus = ES_SELECT;
}


WORD Edit_OnKeyMsg(WORD wKeyCode)
{
    stEDITENUM* pEditEnum = Edit_GetEditEnumCurSel();
    stEDITDATA* pEditData = Edit_GetEditDataCurSel();

    if(s_wEditStatus==ES_NULL) return wKeyCode;

    if(s_wEditStatus==ES_SELECT)
    {
        if(wKeyCode==KEY_UP)
        {
            if(s_wEditCurSel>=1)
            {
                s_wEditCurSel -= 1;
                wKeyCode = KEY_NULL;
            }
        }
        else if(wKeyCode==KEY_DOWN)
        {
            if(s_wEditCurSel+1<s_wEditCount)
            {
                s_wEditCurSel += 1;
                wKeyCode = KEY_NULL;
            }
        }
        else if(wKeyCode==KEY_ENTER)
        {
            s_wEditStatus = ES_EDITING;
            if(pEditEnum) EditEnum_EnterEditing(pEditEnum);
            if(pEditData) EditData_EnterEditing(pEditData);
            wKeyCode = KEY_NULL;
        }
    }
    else if(s_wEditStatus==ES_EDITING)
    {
        if(pEditEnum) wKeyCode = EditEnum_OnKeyMsg(pEditEnum, wKeyCode, &s_wEditStatus);
        if(pEditData) wKeyCode = EditData_OnKeyMsg(pEditData, wKeyCode, &s_wEditStatus);
    }
    
    return wKeyCode;
}

void Edit_OnTimer250ms(void)
{
    stEDITENUM* pEditEnum = Edit_GetEditEnumCurSel();
    stEDITDATA* pEditData = Edit_GetEditDataCurSel();

    if(s_wEditStatus!=ES_EDITING) return;

    if(pEditEnum) EditEnum_Blinking(pEditEnum);
    if(pEditData) EditData_Blinking(pEditData);
}

void Edit_SetEditEnumMetricsTog(void)
{
    char** pCh;
    stEDITENUM* pEditEnum = Edit_GetEditEnumCurSel();
    if(pEditEnum==NULL) return;
    pEditEnum->wCountEnum = 2;
    pEditEnum->wCountChar = 3;
    pCh = &pEditEnum->pszEnum;
    pCh[0] = "OFF";
    pCh[1] = " ON";
}

void Edit_SetEditEnumMetricsMul(WORD wCountEnum, WORD wCountChar, char** pszEnum)
{
    short i;
    char ** pCh, **pChEnum;
    stEDITENUM* pEditEnum = Edit_GetEditEnumCurSel();
    if(wCountChar==0) return;
    if(pEditEnum==NULL) return;
//     if(wCountEnum>EDIT_COUNTMAX) wCountEnum = s_wEnumMaxCount;
    pEditEnum->wCountEnum = wCountEnum;
    pEditEnum->wCountChar = wCountChar-1;
    pCh = &pEditEnum->pszEnum;
    pChEnum = pszEnum;
    for(i=0; i<wCountEnum; i++)
    {
        pCh[i] = pChEnum[i];
    }
}

void Edit_SetEditDataMetricsInteger(WORD wDataMin, WORD wDataMax)
{
    stEDITDATA* pEditData = Edit_GetEditDataCurSel();
    if(pEditData==NULL) return;
    pEditData->dwDataMin = wDataMin;
    pEditData->dwDataMax = wDataMax;
    if(wDataMax<=9) pEditData->wFormat = 0x10;
    else if(wDataMax<=99) pEditData->wFormat = 0x20;
    else if(wDataMax<=999) pEditData->wFormat = 0x30;
    else if(wDataMax<=9999) pEditData->wFormat = 0x40;
}

void Edit_SetEditDataMetricsReal(DWORD dwDataMin, DWORD dwDataMax, WORD wFormat)
{
    stEDITDATA* pEditData = Edit_GetEditDataCurSel();
    if(pEditData==NULL) return;
    pEditData->dwDataMin = dwDataMin;
    pEditData->dwDataMax = dwDataMax;
    pEditData->wFormat = wFormat;
}