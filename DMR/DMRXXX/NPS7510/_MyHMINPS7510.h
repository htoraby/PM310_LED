#ifndef __MyHMIIBCU2140L_H
#define __MyHMIIBCU2140L_H

#define LINKOUT_ALARMED
#define LINKOUT_TRIPPED
#define LINKOUT_ERRORED

enum IndexAnalog
{
	_INDEX_ANALOG = INDEX_ANALOG
    ,INDEX_1Ia
    ,INDEX_1Ib
    ,INDEX_1Ic
    ,INDEX_1Ua
    ,INDEX_1Ub
    ,INDEX_1Uc
    ,INDEX_1Uab
    ,INDEX_1Ubc
    ,INDEX_1Uca
    ,INDEX_1P
    ,INDEX_1Q
    ,INDEX_1S
    ,INDEX_2P
    ,INDEX_2Q
    ,INDEX_2S
    ,INDEX_PF
    ,INDEX_2Ia
    ,INDEX_2Ib
    ,INDEX_2Ic
    ,INDEX_2IA
    ,INDEX_2IB
    ,INDEX_2IC
    ,INDEX_2Ua
    ,INDEX_2Ub
    ,INDEX_2Uc
    ,INDEX_2Uab
    ,INDEX_2Ubc
    ,INDEX_2Uca
    ,INDEX_23I0
    ,INDEX_23I2
    ,INDEX_23U0
    ,INDEX_23U2
    ,INDEX_F
    ,INDEX_AngIa
    ,INDEX_AngIb
    ,INDEX_AngIc
    ,INDEX_AngUa
    ,INDEX_AngUb
    ,INDEX_AngUc
    ,INDEX_AngUab
    ,INDEX_AngUbc
    ,INDEX_AngUca
    ,INDEX_PhI
    ,INDEX_QhI
    ,INDEX_PhE
    ,INDEX_QhE
};

enum IndexParamUnit
{
	_INDEX_PARAM_UNIT = INDEX_PARAM_RESERVED
	,INDEX_PARAM_ALARMKM
	,INDEX_PARAM_ALARMCLOSE
	,INDEX_PARAM_ALARMOPEN
	,INDEX_PARAM_ALARMCT
	,INDEX_PARAM_ALARMPT
	,INDEX_PARAM_MODEPROTECT
	,INDEX_PARAM_MODEPT
    ,INDEX_PARAM_PhI
    ,INDEX_PARAM_QhI
    ,INDEX_PARAM_PhE
    ,INDEX_PARAM_QhE
};

// enum IndexParamScale2
// {
// 	_INDEX_PARAM_SCALE2 = INDEX_PARAM_SCALE2
// 	,INDEX_PARAM_SCALE2IM
// 	,INDEX_PARAM_SCALE2IP
// 	,INDEX_PARAM_SCALE2ULN
// 	,INDEX_PARAM_SCALE23I0
// 	,INDEX_PARAM_SCALE23U0
// 	,INDEX_PARAM_SCALE2IX
// 	,INDEX_PARAM_SCALE2UX
// };

enum IndexAlarmed
{
	_INDEX_ALARMED = INDEX_ALARMED
	,INDEX_ALARMED_CT
	,INDEX_ALARMED_PT
	,INDEX_ALARMED_KM
};


#ifdef __cplusplus
extern "C" {
#endif

// extern void MyHMI_DispayEvent(void);
extern void MyHMI_OnInitSub(void);
extern void MyHMI_OnTimer10msSub(void);
// extern void MyHMI_OnTimer1000msSub(void);
extern char* MyHMI_GetEventTextSub(EVENT* pEvent);
extern void MyHMI_GetEditMetricsSub(WORD* pData);
extern void MyHMI_AutoLCDDataOutSub(WORD wIndex);
extern void MyHMI_TestLightsSub(void);
#ifdef _CMYPROTECT_H
extern void MyHMI_GetProtectActDataInfo(WORD wProtectAct,WORD wProtectIndexExt,WORD wActData,PROTECTACTDATAINFO* pProtectActDataInfo);
#endif/*_CMYPROTECT_H*/

extern MyOutput g_lightOpened;
extern MyOutput g_lightClosed;

extern const char* g_pszInName[SWITCH_COUNT];
extern const char* g_pszINSETName[INSETPOINTNUM];
extern const char* g_pszDoName[RELAYKH_COUNT];    

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__MyHMIIBCU2140L_H*/
