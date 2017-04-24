#ifndef CMYPAGEiBCU2140L_H
#define CMYPAGEiBCU2140L_H

//-----------------------------------------------------------------------------
extern WORD Page_OnKeyMsg(WORD wKeyCode);
extern void Page_OnRefreshPage(WORD wRefreshMode);

extern void Page_OnRefreshACData(WORD wRefreshMode);
extern void Page_OnRPProtectData(WORD wRefreshMode);
extern void Page_OnRPMeansureData(WORD wRefreshMode);
extern void Page_OnRPPrimaryData(WORD wRefreshMode);

extern void Page_OnRefreshPageSwitch(WORD wRefreshMode);

extern void Page_OnRefreshPageWaveRecord(WORD wRefreshMode);
extern void Page_OnRefreshSetpoint(WORD wRefreshMode, BOOL bEdit);

extern void Page_OnRefreshPageParamSetup(WORD wRefreshMode);
extern void Page_OnRefreshPageVector(WORD wRefreshMode);
extern void Page_OnRefreshPageRTWave(WORD wRefreshMode);
extern void Page_OnRefreshInfo(WORD wRefreshMode);
extern void Page_OnRPParamBase(WORD wRefreshMode);
extern void Page_OnRPSetupEnergy(WORD wRefreshMode);
extern void Page_OnRefreshPageSetpoint(WORD* pDeviceSetpoint,BOOL bDisplaySetpoint);
extern void Page_OnRPBOTest(WORD wRefreshMode);
extern void Page_OnRPAdjust(WORD wRefreshMode);
extern void Page_OnRPEngeryData(WORD wRefreshMode);


#endif/*CMYPAGEiBCU2140L_H*/


