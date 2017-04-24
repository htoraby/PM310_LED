#include <Main.h>

const SETPOINTCFGINFO c_setpointCfgInfo[8] = 
{
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL}
};

const PROTECTACTINFO c_protectActInfo[32] = 
{
	{"1#PT过电压",	"1# OVERVOLTAGE",			PROTECTACT_U},
	{"1#PT低电压",	"1# UNDERVOLTAGE",			PROTECTACT_U},
	{"1#PT负序电压","1# NEGATIVE OVERVOLTAGE",	PROTECTACT_U},
	{"1#PT零序电压","1# RESIDUAL OVERVOLTAGE",	PROTECTACT_3U0},
	{"2#PT过电压",	"2# OVERVOLTAGE",			PROTECTACT_U},
	{"2#PT低电压",	"2# UNDERVOLTAGE",			PROTECTACT_U},
	{"2#PT负序电压","2# NEGATIVE OVERVOLTAGE",	PROTECTACT_U},
	{"2#PT零序电压","2# RESIDUAL OVERVOLTAGE",	PROTECTACT_3U0},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL}
};

const DEVICESETPOINT_DMRX81P c_setpointDMRX81P = 
{
	//【1#PT过电压】
	3600,						//电压定值:120V;
	1000,						//时间定值:10s;
	//【1#PT低电压】
	0,							//电压定值:0V;
	1000,						//时间定值:10s;
	//【1#PT负序电压】
	3600,						//电压定值:120V;
	1000,						//时间定值:10s;
	//【1#PT零序电压】
	3000,						//电压定值:173.2V;
	1000,						//时间定值:10s;
	//【2#PT过电压】
	3600,						//电压定值:120V;
	1000,						//时间定值:10s;
	//【2#PT低电压】
	0,							//电压定值:0V;
	1000,						//时间定值:10s;
	//【2#PT负序电压】
	3600,						//电压定值:120V;
	1000,						//时间定值:10s;
	//【2#PT零序电压】
	3000,						//电压定值:173.2V;
	1000,						//时间定值:10s;
};


DEVICESETPOINT_DMRX81P* g_pDeviceSetpoint;

static WORD s_wDataUllMax1;
static WORD s_wDataUllMin1;
static WORD s_wDataUllMax2;
static WORD s_wDataUllMin2;


//-----------------------------------------------------------------------------
//1#PT过电压:
void CMyProtectItemGDY1::Run(void)
{
	ProtectXGE(PROTECT_GDY1,s_wDataUllMax1,SETPOINT(wGDY1_SetU),SETPOINT(wGDY1_SetT),FALSE);
}


//-----------------------------------------------------------------------------
//1#PT低电压:
void CMyProtectItemDDY1::Run(void)
{
	BOOL bLock = FALSE;
	if(g_app.Is1XPTBreak()) bLock = TRUE;
	ProtectXLE(PROTECT_DDY1,s_wDataUllMin1,SETPOINT(wDDY1_SetU),SETPOINT(wDDY1_SetT),bLock);
}


//-----------------------------------------------------------------------------
//1#PT负序电压:
void CMyProtectItemFXDY1::Run(void)
{
	BOOL bLock = FALSE;
	if(g_app.Is1XPTBreak()) bLock = TRUE;
	ProtectXGE(PROTECT_FXDY1,g_data1X3U2.m_nData,SETPOINT(wFXDY1_SetU),SETPOINT(wFXDY1_SetT),bLock);
}


//-----------------------------------------------------------------------------
//1#PT零序电压:
void CMyProtectItemLXDY1::Run(void)
{
	ProtectXGE(PROTECT_LXDY1,g_data1X3U0.m_nData,SETPOINT(wLXDY1_SetU),SETPOINT(wLXDY1_SetT),FALSE);
}


//-----------------------------------------------------------------------------
//2#PT过电压:
void CMyProtectItemGDY2::Run(void)
{
	ProtectXGE(PROTECT_GDY2,s_wDataUllMax2,SETPOINT(wGDY2_SetU),SETPOINT(wGDY2_SetT),FALSE);
}


//-----------------------------------------------------------------------------
//2#PT低电压:
void CMyProtectItemDDY2::Run(void)
{
	BOOL bLock = FALSE;
	if(g_app.Is2XPTBreak()) bLock = TRUE;
	ProtectXLE(PROTECT_DDY2,s_wDataUllMin2,SETPOINT(wDDY2_SetU),SETPOINT(wDDY2_SetT),bLock);
}


//-----------------------------------------------------------------------------
//2#PT负序电压:
void CMyProtectItemFXDY2::Run(void)
{
	BOOL bLock = FALSE;
	if(g_app.Is2XPTBreak()) bLock = TRUE;
	ProtectXGE(PROTECT_FXDY2,g_data2X3U2.m_nData,SETPOINT(wFXDY2_SetU),SETPOINT(wFXDY2_SetT),bLock);
}


//-----------------------------------------------------------------------------
//2#PT零序电压:
void CMyProtectItemLXDY2::Run(void)
{
	ProtectXGE(PROTECT_LXDY2,g_data2X3U0.m_nData,SETPOINT(wLXDY2_SetU),SETPOINT(wLXDY2_SetT),FALSE);
}


//-----------------------------------------------------------------------------
void CMyProtectDMRX81P::OnInit(void)
{
	CMyProtect::OnInit();
	g_pDeviceSetpoint = (DEVICESETPOINT_DMRX81P*)g_protect.GetSetpointArea();
	m_piGDY1.OnInit();
	m_piDDY1.OnInit();
	m_piFXDY1.OnInit();
	m_piLXDY1.OnInit();
	m_piGDY2.OnInit();
	m_piDDY2.OnInit();
	m_piFXDY2.OnInit();
	m_piLXDY2.OnInit();
}

void CMyProtectDMRX81P::OnInitSetpoint(WORD* pSetpoint)
{
	*(DEVICESETPOINT_DMRX81P*)pSetpoint = c_setpointDMRX81P;
}

void CMyProtectDMRX81P::iiiRun(void)
{
	CMyProtect::iiiRun();
	g_pDeviceSetpoint = (DEVICESETPOINT_DMRX81P*)g_protect.GetSetpointArea();
	s_wDataUllMax1 = GetMax(g_data1XUab.m_nData,g_data1XUbc.m_nData,g_data1XUca.m_nData);
	s_wDataUllMin1 = GetMin(g_data1XUab.m_nData,g_data1XUbc.m_nData,g_data1XUca.m_nData);
	s_wDataUllMax2 = GetMax(g_data2XUab.m_nData,g_data2XUbc.m_nData,g_data2XUca.m_nData);
	s_wDataUllMin2 = GetMin(g_data2XUab.m_nData,g_data2XUbc.m_nData,g_data2XUca.m_nData);

	if((g_deviceInfo.wDeviceStatus1&(DS1_ErrorAD&DS1_ErrorSetpoint))==0)
	{
		if(g_protect.m_wProtectRun[PROTECT_GDY1]==PROTECTTOG_ON) m_piGDY1.Run();
		else m_piGDY1.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_DDY1]==PROTECTTOG_ON) m_piDDY1.Run();
		else m_piDDY1.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_FXDY1]==PROTECTTOG_ON) m_piFXDY1.Run();
		else m_piFXDY1.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_LXDY1]==PROTECTTOG_ON) m_piLXDY1.Run();
		else m_piLXDY1.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_GDY2]==PROTECTTOG_ON) m_piGDY2.Run();
		else m_piGDY2.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_DDY2]==PROTECTTOG_ON) m_piDDY2.Run();
		else m_piDDY2.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_FXDY2]==PROTECTTOG_ON) m_piFXDY2.Run();
		else m_piFXDY2.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_LXDY2]==PROTECTTOG_ON) m_piLXDY2.Run();
		else m_piLXDY2.OnInit();
	}
}

WORD CMyProtectDMRX81P::GetProtectPickupInfo(WORD wProtectIndex)
{
	switch(wProtectIndex)
	{
	case PROTECT_GDY1: return m_piGDY1.GetProtectPickupInfo();
	case PROTECT_DDY1: return m_piDDY1.GetProtectPickupInfo();
	case PROTECT_FXDY1: return m_piFXDY1.GetProtectPickupInfo();
	case PROTECT_LXDY1: return m_piLXDY1.GetProtectPickupInfo();
	case PROTECT_GDY2: return m_piGDY2.GetProtectPickupInfo();
	case PROTECT_DDY2: return m_piDDY2.GetProtectPickupInfo();
	case PROTECT_FXDY2: return m_piFXDY2.GetProtectPickupInfo();
	case PROTECT_LXDY2: return m_piLXDY2.GetProtectPickupInfo();
	}
	return 0x0000;
}

void CMyProtectDMRX81P::OnUpdateDevice(WORD* pData)
{
	CMyProtect::OnUpdateDevice(pData);
}
