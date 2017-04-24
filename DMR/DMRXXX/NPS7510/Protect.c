#include <Main.h>

const PROTECTACTINFO c_protectActInfo[PROTECT_MAX1] = 
{
    {"�������",		"OVERCUR I",		    PROTECTACT_IP},
    {"�������",		"OVERCUR II",			PROTECTACT_IP},
    {"��ѹ���",		"OVERVOL I",			PROTECTACT_U},
    {"��ѹ���",		"OVERVOL II",			PROTECTACT_U},
    {"Ƿѹ���",		"UNDERVOL I",			PROTECTACT_U},
    {"Ƿѹ���",		"UNDERVOL II",			PROTECTACT_U},
//     {NULL,			    NULL,		            0},
};

const DEVICESETPOINT_iBCU c_setpointiBCU = 
{
    10000,					// ����I�ε���;
    1000,					// ����I��ʱ��;
//     TOGGLE_OFF,

    10000,					// ����II�ε���;
    1000,					// ����II��ʱ��;
//     TOGGLE_OFF,

    10000,					// ��ѹI��;
    1000,					// ��ѹI��ʱ��;
//     TOGGLE_OFF,

    10000,					// ��ѹII��;
    1000,					// ��ѹII��ʱ��;
//     TOGGLE_OFF,

    1000,					// ǷѹI��;
    1000,					// ǷѹI��ʱ��;
//     TOGGLE_OFF,
    
    1000,					// ǷѹII��;
    1000,					// ǷѹII��ʱ��;
//     TOGGLE_OFF,
};


DEVICESETPOINT_iBCU* g_pDeviceSetpoint;

static WORD s_wDataIMax;
static WORD s_wDataUllMax;
static WORD s_wDataUllMin;

//-----------------------------------------------------------------------------
static WORD IPtoRun(WORD wIPSetpoint)
{
    return (WORD)(((DWORD)wIPSetpoint*4096L+SCALE2IM/2)/SCALE2IM);
}

static WORD UlltoRun(WORD wUllSetpoint)
{
    return (WORD)(((DWORD)wUllSetpoint*4096L+SCALE2ULN/2)/SCALE2ULN);
}

//-----------------------------------------------------------------------------
// ����1��:
static WORD s_wDL1_Time;
void Protect_DL1_OnInit(void)
{
    s_wDL1_Time = 0;
}

void Protect_DL1_Run(void)
{
    WORD wSetI = IPtoRun(SETPOINT(wDL1_SetI));

    s_wDL1_Time = Protect_ProtectXGE(PROTECT_DL1, s_wDataIMax, s_wDL1_Time, wSetI, SETPOINT(wDL1_SetT), FALSE);
}

//-----------------------------------------------------------------------------
// ����2��:
static WORD s_wDL2_Time;
void Protect_DL2_OnInit(void)
{
    s_wDL2_Time = 0;
}

void Protect_DL2_Run(void)
{
    WORD wSetI = IPtoRun(SETPOINT(wDL2_SetI));

    s_wDL2_Time = Protect_ProtectXGE(PROTECT_DL2, s_wDataIMax, s_wDL2_Time, wSetI, SETPOINT(wDL2_SetT), FALSE);
}

//-----------------------------------------------------------------------------
// ��ѹ1��:
static WORD s_wGY1_Time;
void Protect_GY1_OnInit(void)
{
    s_wGY1_Time = 0;
}

void Protect_GY1_Run(void)
{
    WORD wSetU = UlltoRun(SETPOINT(wGY1_SetU));
    
    s_wGY1_Time = Protect_ProtectXGE(PROTECT_GY1, s_wDataUllMax, s_wGY1_Time, wSetU, SETPOINT(wGY1_SetT), FALSE);
}

//-----------------------------------------------------------------------------
// ��ѹ2��:
static WORD s_wGY2_Time;
void Protect_GY2_OnInit(void)
{
    s_wGY2_Time = 0;
}

void Protect_GY2_Run(void)
{
    WORD wSetU = UlltoRun(SETPOINT(wGY2_SetU));
    
    s_wGY2_Time = Protect_ProtectXGE(PROTECT_GY2, s_wDataUllMax, s_wGY2_Time, wSetU, SETPOINT(wGY2_SetT), FALSE);
}

//-----------------------------------------------------------------------------
// Ƿѹ1��:
static WORD s_wQY1_Time;
static BOOL s_bQY1_OK;
void Protect_QY1_OnInit(void)
{
    s_wQY1_Time = 0;
    s_bQY1_OK = FALSE;
}

void Protect_QY1_Run(void)
{
    WORD wSetU;
    BOOL bOK;

    wSetU = UlltoRun(SETPOINT(wQY1_SetU));
//    if(wSetU<750) wSetU = 750;

    if(s_bQY1_OK==FALSE)
    {
        s_wQY1_Time = 0;
        bOK = (s_wDataUllMin>wSetU)?TRUE:FALSE;
        s_bQY1_OK = bOK;
        return;
    }
    else
    {
        s_wQY1_Time = Protect_ProtectXLE(PROTECT_QY1, s_wDataUllMax, s_wQY1_Time, wSetU,SETPOINT(wQY1_SetT),FALSE);
    }
}

//-----------------------------------------------------------------------------
// Ƿѹ2��:
static WORD s_wQY2_Time;
static BOOL s_bQY2_OK;
void Protect_QY2_OnInit(void)
{
    s_wQY2_Time = 0;
    s_bQY2_OK = FALSE;
}

void Protect_QY2_Run(void)
{
    WORD wSetU;
    BOOL bOK;
    
    wSetU = UlltoRun(SETPOINT(wQY2_SetU));
//    if(wSetU<750) wSetU = 750;
    
    if(s_bQY2_OK==FALSE)
    {
        s_wQY2_Time = 0;
        bOK = (s_wDataUllMin>wSetU)?TRUE:FALSE;
        s_bQY2_OK = bOK;
        return;
    }
    else
    {
        s_wQY2_Time = Protect_ProtectXLE(PROTECT_QY2, s_wDataUllMax, s_wQY2_Time, wSetU,SETPOINT(wQY2_SetT),FALSE);
    }
}

//-----------------------------------------------------------------------------
void Protect_OnInit(void)
{
    Protect_OnInit1();
    g_pDeviceSetpoint = (DEVICESETPOINT_iBCU*)g_deviceSetpoint.wSetpointArea1;
    Protect_DL1_OnInit();
    Protect_DL2_OnInit();
    Protect_GY1_OnInit();
    Protect_GY2_OnInit();
    Protect_QY1_OnInit();
    Protect_QY2_OnInit();
}

void Protect_OnInitSetpoint(WORD* pSetpoint)
{
	*(DEVICESETPOINT_iBCU*)pSetpoint = c_setpointiBCU;
}

void Protect_OnActTripped(WORD wProtectIndex)
{
}

WORD g_wHWOld = 0;

void Protect_Run(void)
{
    g_pDeviceSetpoint = (DEVICESETPOINT_iBCU*)&g_deviceSetpoint.wSetpointArea1;
    s_wDataIMax = GetMax(g_dataIa.m_nData,g_dataIb.m_nData,g_dataIc.m_nData);
    s_wDataUllMax = GetMax(g_dataUab.m_nData,g_dataUbc.m_nData,g_dataUca.m_nData);
    s_wDataUllMin = GetMin(g_dataUab.m_nData,g_dataUbc.m_nData,g_dataUca.m_nData);

    if((g_deviceInfo.wDeviceStatus1&(DS1_ErrorAD|DS1_ErrorSetpoint))==0)
    {
        if(g_deviceSetpoint.wToggle[PROTECT_DL1]==PROTECTTOG_ON) Protect_DL1_Run();
        else Protect_DL1_OnInit();
        if(g_deviceSetpoint.wToggle[PROTECT_DL2]==PROTECTTOG_ON) Protect_DL2_Run();
        else Protect_DL2_OnInit();
        if(g_deviceSetpoint.wToggle[PROTECT_GY1]==PROTECTTOG_ON) Protect_GY1_Run();
        else Protect_GY1_OnInit();
        if(g_deviceSetpoint.wToggle[PROTECT_GY2]==PROTECTTOG_ON) Protect_GY2_Run();
        else Protect_GY2_OnInit();
        if(g_deviceSetpoint.wToggle[PROTECT_QY1]==PROTECTTOG_ON) Protect_QY1_Run();
        else Protect_QY1_OnInit();
        if(g_deviceSetpoint.wToggle[PROTECT_QY2]==PROTECTTOG_ON) Protect_QY2_Run();
        else Protect_QY2_OnInit();
    }
}
