#ifndef CMYPG_PROTECT_H
#define CMYPG_PROTECT_H

//-----------------------------------------------------------------------------
extern WORD g_wPGP_LINEY;								// ÿ�м��;
extern WORD g_wPGP_LINENUM;							// ÿҳ����;
extern WORD g_wPGP_LINEOFFSET;							// ��ʼ��Y����;
extern WORD g_wPGP_LINECFGX1;							// ��������:��������X����;
extern WORD g_wPGP_LINECFGX2;							// ��������:��������X����;
extern WORD g_wPGP_LINESETX1;							// ������ֵ:��������X����;
extern WORD g_wPGP_LINESETX2;							// ������ֵ:��ֵ����X����(�ұ߿���);
extern WORD g_wPGP_LINESETX3;							// ������ֵ:������ֵX����;
extern WORD g_wPGP_FONTWIDTH;							// ������;
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



