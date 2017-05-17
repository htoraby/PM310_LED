//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __LEDEDIT_H
#define __LEDEDIT_H

#ifdef __cplusplus
extern "C" {
#endif

extern void Edit_OnInit(void);
extern void Edit_AddEditEnumMul(WORD* pData);
extern void Edit_AddEditDataWord(WORD* pData);
extern void Edit_AddEditDataDWord(DWORD* pData);
extern void Edit_OnRefreshPage(void);
extern void Edit_EnableEdit(WORD wRefreshMode);
extern WORD Edit_OnKeyMsg(WORD wKeyCode);
extern void Edit_OnTimer250ms(void);
extern void Edit_SetEditEnumMetricsTog(void);
extern void Edit_SetEditEnumMetricsMul(WORD wCountEnum, WORD wCountChar, char** pszEnum);
extern void Edit_SetEditDataMetricsInteger(WORD wDataMin, WORD wDataMax);
extern void Edit_SetEditDataMetricsReal(DWORD dwDataMin, DWORD dwDataMax, WORD wFormat);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /*__LEDEDIT_H*/

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------


