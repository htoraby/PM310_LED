#ifndef CMYPG_PROTECT_H
#define CMYPG_PROTECT_H

//-----------------------------------------------------------------------------
extern WORD g_wPGP_LINEY;								// 每行间距;
extern WORD g_wPGP_LINENUM;							// 每页行数;
extern WORD g_wPGP_LINEOFFSET;							// 起始行Y坐标;
extern WORD g_wPGP_LINECFGX1;							// 保护配置:保护名称X坐标;
extern WORD g_wPGP_LINECFGX2;							// 保护配置:保护配置X坐标;
extern WORD g_wPGP_LINESETX1;							// 保护定值:保护名称X坐标;
extern WORD g_wPGP_LINESETX2;							// 保护定值:定值名称X坐标(右边靠齐);
extern WORD g_wPGP_LINESETX3;							// 保护定值:保护定值X坐标;
extern WORD g_wPGP_FONTWIDTH;							// 字体宽度;
extern WORD g_wOffset;
extern WORD g_wCountLine;
extern BOOL g_bDisplaySetpoint;

extern void PGPRT_GetLinePosY(void);
extern void PGPRT_GetLinePosYExt(void);
extern void PGPRT_OutProtectText(char* pszText);
extern void PGPRT_OutProtectName(WORD wIndex);
extern void PGPRT_OutProtectSetX(char* pszName,char* pszUnitage,WORD* pSetX);
extern void PGPRT_OutProtectTog(char* pszName,WORD* pStatusTog);
extern void PGPRT_OutProtectINsetpoint(WORD wIndex);
// extern void PGPRT_OutProtectUsersetpoint(WORD wIndex);
// extern void SetMetrics(void){};
extern void PGPRT_OnRPProtectConfig(DWORD dwProtectCFG,WORD wSetpointCfg,BOOL bINSetpoint,BOOL bUserSetpoint);
// extern void PGPRT_OnRPProtectTripMatrix(DWORD dwProtectCFG,BOOL bUserSetpoint);
// extern void PGPRT_OnRPSetpointAreaSelect(void);
extern void PGPRT_OnRefreshPage(WORD* pDeviceSetpoint,BOOL bDisplaySetpoint);
// 	VIRTUAL void iiiOnRefreshPage(WORD* pDeviceSetpoint){};

#endif/*CMYPG_PROTECT_H*/



