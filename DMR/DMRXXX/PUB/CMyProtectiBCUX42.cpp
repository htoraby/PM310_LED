#include <Main.h>

const SETPOINTCFGINFO c_setpointCfgInfo[8] = 
{
	{"选项:电动机保护",	"OPT:\1MOTOR PROTECTION"},
	{"选项:方向闭锁",	"OPT:\1DIRECTIONAL BLOCKING"},
	{"选项:低压闭锁",	"OPT:\1UNDERVOLTAGE BLOCKING"},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL}
};

const PROTECTACTINFO c_protectActInfo[32] = 
{
	{"电流速断",	"OVERCURRENT INSTANT.",		PROTECTACT_IP},
	{"限时电流速断","OVERCURRENT HIGH",			PROTECTACT_IP},
	{"定时限过流",	"OVERCURRENT LOW",			PROTECTACT_IP},
	{"反时限过流",	"OVERCURRENT IDMT",			PROTECTACT_IP},
	{"后加速",		"ACCELERATED TRIP",			PROTECTACT_IP},
	{"过负荷",		"OVERLOAD",					PROTECTACT_IP},
	{"负序电流",	"NEGATIVE OVERCURRENT",		PROTECTACT_IP},
	{"零序电流",	"RESIDUAL OVERCURRENT",		PROTECTACT_3I0},
	{"单相接地选线","EARTH-FAULT DETECTION",	PROTECTACT_3I0},
	{"过电压",		"OVERVOLTAGE",				PROTECTACT_U},
	{"低电压",		"UNDERVOLTAGE",				PROTECTACT_U},
	{"失压",		"PRIMARY POWER FAULT",		PROTECTACT_U},
	{"负序电压",	"NEGATIVE OVERVOLTAGE",		PROTECTACT_U},
	{"零序电压",	"RESIDUAL OVERVOLTAGE",		PROTECTACT_3U0},
	{"复合电压过流","COMPOUND OVERCURRENT",		PROTECTACT_IP},
	{"低周减载",	"UNDERFREQENCY SHEDDING",	PROTECTACT_F},
	{"低压解列",	"UNDERVOLTAGE DECOUPLING",	PROTECTACT_U},
	{"重合闸",		"AUTO-RECLOSURE",			PROTECTACT_NULL},
	{"备自投",		"AUTO-SWITCHING",			PROTECTACT_NULL},
	{"过热",		"THERMAL OVERLOAD",			PROTECTACT_IP},
	{"逆功率",		"REVERSE POWER",			PROTECTACT_P},
	{"启动时间过长","MOTOR STARTING TIME",		PROTECTACT_NULL},
	{"定时限Ix过流","Ix OVERCURRENT ",			PROTECTACT_Ix},
	{"反时限Ix过流","Ix OVERCURRENT IDMT",		PROTECTACT_Ix},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL}
};

const DEVICESETPOINT_iBCUX42 c_setpointiBCUX42 = 
{
	500,						//电动机额定电流:5A;
	1000,						//电动机启动时间:10s;
	//【电流速断】
	10000,						//电流定值:100A;
	1000,						//时间定值:10s;
	12000,						//电压定值:120V;
	PROTECTTOG_OFF,				//低压闭锁投退:OFF;
	PROTECTTOG_OFF,				//方向闭锁投退:OFF;
	PROTECTTOG_OFF,				//启动时定值自动加倍投退:OFF;
	//【限时电流速断】
	10000,						//电流定值:100A;
	1000,						//时间定值:10s;
	12000,						//电压定值:120V;
	PROTECTTOG_OFF,				//低压闭锁投退:OFF;
	PROTECTTOG_OFF,				//方向闭锁投退:OFF;
	PROTECTTOG_OFF,				//启动时定值自动加倍投退:OFF;
	//【定时限过流】
	10000,						//电流定值:100A;
	1000,						//时间定值:10s;
	12000,						//电压定值:120V;
	PROTECTTOG_OFF,				//低压闭锁投退:OFF;
	PROTECTTOG_OFF,				//方向闭锁投退:OFF;
	PROTECTTOG_OFF,				//启动时保护自动退出投退:OFF;
	//【反时限过流】
	10000,						//电流定值:100A;
	100,						//时间系数:1.00;
	IDMT_EXTR,					//IDMT类型:Extremely Inverse;
	//【后加速】
	10000,						//电流定值100A;
	1000,						//时间定值10s;
	//【过负荷】
	10000,						//电流定值100A;
	1000,						//时间定值10s;
	//【负序电流】
	10000,						//电流定值:100A;
	1000,						//时间定值:10s;
	//【零序电流】
	600,						//电流定值6A;
	1000,						//时间定值10s;
	//【单相接地选线】
	600,						//电流定值:6A;
	3000,						//电压定值:173.2V;
	PROTECTTOG_OFF,				//五次谐波判据投退:OFF;
	//【过电压】
	12000,						//电压定值:120V;
	1000,						//时间定值:10s;
	//【低电压】
	0,							//电压定值:0V;
	1000,						//时间定值:10s;
	//【失压】
	0,							//电压定值:0V;
	1000,						//时间定值:10s;
	//【负序电压】
	12000,						//电压定值:120V;
	1000,						//时间定值:10s;
	//【零序电压】
	17320,						//电压定值:173.2V;
	1000,						//时间定值:10s;
	//【复合电压过流】
	10000,						//电流定值:100A;
	12000,						//电压定值:120V;
	12000,						//负序电压定值:120V;
	1000,						//时间定值:10s;
	PROTECTTOG_OFF,				//低压闭锁投退:OFF;
	PROTECTTOG_OFF,				//负序电压闭锁投退:OFF;
	//【低周减载】
	4000,						//频率定值:40Hz;
	1000,						//时间定值:10s;
	12000,						//电压定值:120V;
	100,						//滑差定值:1.0Hz/s;
	PROTECTTOG_OFF,				//滑差闭锁投退:OFF;
	PROTECTTOG_OFF,				//电压闭锁投退:OFF;
	PROTECTTOG_OFF,				//电流闭锁投退:OFF;
	//【低压解列】
	0,							//电压定值:0V;
	1000,						//时间定值:10s;
	100,						//滑差定值:1.0V/s;
	PROTECTTOG_OFF,				//滑差闭锁投退:OFF;
	PROTECTTOG_OFF,				//电流闭锁投退:OFF;
	//【重合闸】
	1000,						//时间定值:10s;
	30,							//同期角定值:30度;
	PROTECTTOG_OFF,				//检无压投退:OFF;
	PROTECTTOG_OFF,				//检同期投退:OFF;
	//【备自投】
	0,							//电压定值:0V;
	1000,						//时间定值:10s;
	//【过热】
	10000,						//电流定值:100A;
	1000,						//时间定值:10s;
	600,						//负序分量系数:6.00;
	//【逆功率】
	0,							//功率定值:0w;
	1000,						//时间定值:10s;
	//【定时限Ix过流】
	10000,						//电流定值:100A;
	1000,						//时间定值:10s;
	//【反时限Ix过流】
	10000,						//电流定值:100A;
	100,						//时间系数:1.00;
	IDMT_EXTR					//IDMT类型:Extremely Inverse;
};


DEVICESETPOINT_iBCUX42* g_pDeviceSetpoint;
DEVICESETPOINT_iBCUX42CONFIG* g_pDeviceSetpointConfig;

static WORD s_wDataIMax;
static WORD s_wDataIMax2;
static WORD s_wDataIMaxFX;
static WORD s_wDataIMaxFX2;
static WORD s_wDataUllMax;
static WORD s_wDataUllMin;
static WORD s_wMotorStartPickupData1;
static WORD s_wMotorStartPickupData2;
static WORD s_wMotorStartPickupData3;
static WORD s_wMotorStartPickupData4;
static WORD s_wMotorStartPickupData5;
static WORD s_wMotorStartPickupData6;
static WORD s_wMotorStartPickupData7;
static WORD s_wMotorStartPickupData8;
static WORD s_wMotorStartPickupData9;
static WORD s_wMotorStartTime;

//-----------------------------------------------------------------------------
static WORD IPtoRun(WORD wIPSetpoint)
{
	return WORD(((DWORD)wIPSetpoint*3000L+(DWORD)(g_pDeviceParam->wScale2IP>>1))/(DWORD)(g_pDeviceParam->wScale2IP));
}

static WORD IXtoRun(WORD wIXSetpoint)
{
	return WORD(((DWORD)wIXSetpoint*3000L+(DWORD)(g_pDeviceParam->wScale2Ix>>1))/(DWORD)(g_pDeviceParam->wScale2Ix));
}

static WORD UlltoRun(WORD wUllSetpoint)
{
	return WORD(((DWORD)wUllSetpoint*3000L+(DWORD)(g_pDeviceParam->wScale2Uln>>1))/(DWORD)(g_pDeviceParam->wScale2Uln));
}

static WORD I0toRun(WORD wI0Setpoint)
{
#ifdef DFT_3I0
	return WORD(((DWORD)wI0Setpoint*3000L+(DWORD)(g_pDeviceParam->wScale23I0>>1))/(DWORD)(g_pDeviceParam->wScale23I0));
#else
	return WORD(((DWORD)wI0Setpoint*3000L+(DWORD)(g_pDeviceParam->wScale2IP>>1))/(DWORD)(g_pDeviceParam->wScale2IP));
#endif
}

static WORD U0toRun(WORD wU0Setpoint)
{
#ifdef DFT_3U0
	return WORD(((DWORD)wU0Setpoint*3000L+(DWORD)(g_pDeviceParam->wScale23U0>>1))/(DWORD)(g_pDeviceParam->wScale23U0));
#else
	return WORD(((DWORD)wU0Setpoint*3000L+(DWORD)(g_pDeviceParam->wScale2Uln>>1))/(DWORD)(g_pDeviceParam->wScale2Uln));
#endif
}

//-----------------------------------------------------------------------------
static long GetVP(CMyData* pDataU,CMyData* pDataI)
{
	return (long)pDataU->m_nR*(long)pDataI->m_nR + (long)pDataU->m_nX*(long)pDataI->m_nX;
}

static long GetVQ(CMyData* pDataU,CMyData* pDataI)
{
	return (long)pDataU->m_nX*(long)pDataI->m_nR - (long)pDataU->m_nR*(long)pDataI->m_nX;
}

static void GetPowerDirectABC(CMyData* pDataU,CMyData* pDataI)
{
	if(pDataU->m_nData>=187 && pDataI->m_nData!=0)			//FixTo:160(=10V);
	{
		long lVP = GetVP(pDataU,pDataI);
		long lVQ = GetVQ(pDataU,pDataI);
		if(lVP<lVQ) return;
	}
	if(s_wDataIMaxFX<pDataI->m_nData) s_wDataIMaxFX = pDataI->m_nData;
}


//-----------------------------------------------------------------------------
void CMyProtectItemIDMT::OnInit(void)
{
	m_dwSumIDMT = 0L;
}

WORD CMyProtectItemIDMT::GetProtectPickupInfo(void)
{
	return (m_dwSumIDMT>0L)?0xaaaa:0x0000;
}

WORD CMyProtectItemIDMT::GetLN(DWORD dwData)
{
	WORD wCountLN2 = 0;
	DWORD dwTemp = dwData;
	while(dwTemp)
	{
		dwTemp >>= 1;
		wCountLN2++;
	}
	dwTemp = 10000L*dwData/(1L<<wCountLN2);
	WORD wN005 = (WORD)((dwTemp+500)/500);
	dwTemp = 10000L-(20L*dwTemp+(wN005>>1))/wN005;
	dwTemp = dwTemp+(dwTemp*dwTemp)/20000L+(dwTemp*dwTemp*dwTemp)/300000000L;
	dwTemp = (wCountLN2*693147L+50L)/100L-dwTemp-92103L;
	switch(wN005)
	{
	case 11: dwTemp -= 5978L; break;
	case 12: dwTemp -= 5108L; break;
	case 13: dwTemp -= 4308L; break;
	case 14: dwTemp -= 3567L; break;
	case 15: dwTemp -= 2877L; break;
	case 16: dwTemp -= 2231L; break;
	case 17: dwTemp -= 1625L; break;
	case 18: dwTemp -= 1054L; break;
	case 19: dwTemp -= 513L; break;
	}
	return (WORD)dwTemp;
}

void CMyProtectItemIDMT::ProtectIDMT(WORD wProtectIndex,WORD wTypeIDMT,WORD wSetK,WORD wSetI,WORD wDataI)
{
	if(wSetI==0 || wDataI<=wSetI)
	{
		m_dwSumIDMT = 0L;
		return;
	}
	DWORD dwTemp;
	DWORD dwIDMTSet;
	WORD wTemp = wSetI*20;
	if(wDataI>wTemp) wDataI = wTemp;
	if(wDataI>6000) wDataI = 6000;
	switch(wTypeIDMT)
	{
	case IDMT_EXTR: dwIDMTSet =   8000L; break;
	case IDMT_VERY: dwIDMTSet =  13500L; break;
	case IDMT_NORM: dwIDMTSet = 140000L; break;
	case IDMT_LONG: dwIDMTSet = 120000L; break;
	default: return;
	}
	if(m_dwSumIDMT==0L && wDataI<(11*wSetI+5)/10) return;
	dwIDMTSet *= wSetK;
	DWORD dwIDMTData = 0L;
	switch(wTypeIDMT)
	{
	case IDMT_EXTR:
		dwTemp = (DWORD)wSetI*(DWORD)wSetI;
		dwIDMTData = (DWORD)wDataI*(DWORD)wDataI - dwTemp;
		dwIDMTData *= 100L;
		dwIDMTData += dwTemp>>1;
		dwIDMTData /= dwTemp;
		break;
	case IDMT_VERY:
	case IDMT_LONG:
		dwIDMTData = (DWORD)(wDataI-wSetI);
		dwIDMTData *= 1000L;
		dwIDMTData += wSetI>>1;
		dwIDMTData /= wSetI;
		break;
	case IDMT_NORM:
		dwTemp = (10000L*(DWORD)wDataI)/(DWORD)wSetI;
		wTemp = GetLN(dwTemp);
		wTemp *= 2;
		dwIDMTData = wTemp+((DWORD)wTemp*(DWORD)wTemp+1000000L)/2000000L;
		break;
	}
	m_dwSumIDMT += dwIDMTData;
	if(m_dwSumIDMT>dwIDMTSet)
	{
		m_dwSumIDMT = dwIDMTSet;
		g_protect.SetProtectAct(wProtectIndex,wDataI,0x3333);
	}
}


//-----------------------------------------------------------------------------
void CMyProtectItemDXDT::OnInit(void)
{
	CMyProtectItem::OnInit();
	m_wCountQueue = 0;
	MemoryClear(m_wDataQueue,9);
	m_wCountLock = 100;
}

long CMyProtectItemDXDT::GetDXDT(void)
{
	WORD wAvg = GetAddSum(m_wDataQueue,9);
	wAvg = (wAvg+4)/9;
	long lSum = 0;
	for(short i=0;i<9;i++)
	{
		lSum += (i-4)*(short)(m_wDataQueue[(m_wCountQueue+i)%9]-wAvg);
	}
	if(lSum<0) lSum = -lSum;
	return lSum*5/6;
}

void CMyProtectItemDXDT::ProtectDXDT(WORD wData,BOOL bStartOK,WORD wTogDXDT,WORD wSetDXDT)
{
	if(CMyData::s_bAddFilter)
	{
		m_wDataQueue[m_wCountQueue] = wData;
		m_wCountQueue++;
		if(m_wCountQueue>=9) m_wCountQueue = 0;
	}
	if(m_wCountLock)
	{
		if(bStartOK) m_wCountLock--;
		m_wTime = 0;
		return;
	}
	if(wTogDXDT==PROTECTTOG_ON)
	{
		long lDXDT = GetDXDT();
		if(lDXDT>(long)wSetDXDT) m_wCountLock = 100;
	}
}


//-----------------------------------------------------------------------------
//电流速断:
void CMyProtectItemSD::Run(void)
{
	WORD wDataITmp,wDataIFXTmp;
	WORD wSetI = IPtoRun(SETPOINT(wSD_SetI));
	WORD wSetU = UlltoRun(SETPOINT(wSD_SetU));
	if(g_pDeviceParam->wModeProtect==MODEPROTECT_2P)
	{
		wDataITmp = s_wDataIMax2;
		wDataIFXTmp = s_wDataIMaxFX2;
	}
	else
	{
		wDataITmp = s_wDataIMax;
		wDataIFXTmp = s_wDataIMaxFX;
	}
	WORD wDataI = wDataITmp;
	BOOL bLock = FALSE;
	if(SETPOINT(wSD_TogFX)==PROTECTTOG_ON) wDataI = wDataIFXTmp;
	if(SETPOINT(wSD_TogDY)==PROTECTTOG_ON && s_wDataUllMin>=wSetU) bLock = TRUE;
	if(SETPOINT(wSD_TogAD)==PROTECTTOG_ON && s_wMotorStartTime) wSetI *= 2;
	ProtectXGE(PROTECT_SD,wDataI,wSetI,SETPOINT(wSD_SetT),bLock);
}


//-----------------------------------------------------------------------------
//限时电流速断:
void CMyProtectItemXSSD::Run(void)
{
	WORD wDataITmp,wDataIFXTmp;
	WORD wSetI = IPtoRun(SETPOINT(wXSSD_SetI));
	WORD wSetU = UlltoRun(SETPOINT(wXSSD_SetU));
	if(g_pDeviceParam->wModeProtect==MODEPROTECT_2P)
	{
		wDataITmp = s_wDataIMax2;
		wDataIFXTmp = s_wDataIMaxFX2;
	}
	else
	{
		wDataITmp = s_wDataIMax;
		wDataIFXTmp = s_wDataIMaxFX;
	}
	WORD wDataI = wDataITmp;
	BOOL bLock = FALSE;
	if(SETPOINT(wXSSD_TogFX)==PROTECTTOG_ON) wDataI = wDataIFXTmp;
	if(SETPOINT(wXSSD_TogDY)==PROTECTTOG_ON && s_wDataUllMin>=wSetU) bLock = TRUE;
	if(SETPOINT(wXSSD_TogAD)==PROTECTTOG_ON && s_wMotorStartTime) wSetI *= 2;
	ProtectXGE(PROTECT_XSSD,wDataI,wSetI,SETPOINT(wXSSD_SetT),bLock);
}


//-----------------------------------------------------------------------------
//定时限过流:
void CMyProtectItemDSXGL::Run(void)
{
	WORD wDataITmp,wDataIFXTmp;
	WORD wSetI = IPtoRun(SETPOINT(wDSXGL_SetI));
	WORD wSetU = UlltoRun(SETPOINT(wDSXGL_SetU));
	if(g_pDeviceParam->wModeProtect==MODEPROTECT_2P)
	{
		wDataITmp = s_wDataIMax2;
		wDataIFXTmp = s_wDataIMaxFX2;
	}
	else
	{
		wDataITmp = s_wDataIMax;
		wDataIFXTmp = s_wDataIMaxFX;
	}
	WORD wDataI = wDataITmp;
	BOOL bLock = FALSE;
	if(SETPOINT(wDSXGL_TogFX)==PROTECTTOG_ON) wDataI = wDataIFXTmp;
	if(SETPOINT(wDSXGL_TogDY)==PROTECTTOG_ON && s_wDataUllMin>=wSetU) bLock = TRUE;
	if(SETPOINT(wDSXGL_TogAE)==PROTECTTOG_ON && s_wMotorStartTime) m_wTime = 0;
	ProtectXGE(PROTECT_DSXGL,wDataI,wSetI,SETPOINT(wDSXGL_SetT),bLock);
}


//-----------------------------------------------------------------------------
//反时限过流:
void CMyProtectItemFSXGL::Run(void)
{
	WORD wDataI;
	WORD wSetI = IPtoRun(SETPOINT(wFSXGL_SetI));
	if(g_pDeviceParam->wModeProtect==MODEPROTECT_2P) wDataI = s_wDataIMax2;
	else wDataI = s_wDataIMax;
	ProtectIDMT(PROTECT_FSXGL,SETPOINT(wFSXGL_IDMT),SETPOINT(wFSXGL_SetK),wSetI,wDataI);
}


//-----------------------------------------------------------------------------
//后加速:
void CMyProtectItemHJS::Run(void)
{
	WORD wSetI = IPtoRun(SETPOINT(wHJS_SetI));
	if(g_breaker.m_wCountAfterClosed>0 || m_wTime>0)
	{
		ProtectXGE(PROTECT_HJS,s_wDataIMax,wSetI,SETPOINT(wHJS_SetT),FALSE);
	}
}


//-----------------------------------------------------------------------------
//过负荷:
void CMyProtectItemGFH::Run(void)
{
	WORD wSetI = IPtoRun(SETPOINT(wGFH_SetI));
	ProtectXGE(PROTECT_GFH,s_wDataIMax,wSetI,SETPOINT(wGFH_SetT),FALSE);
}


//-----------------------------------------------------------------------------
//负序电流:
void CMyProtectItemFXDL::Run(void)
{
	WORD wSetI = IPtoRun(SETPOINT(wFXDL_SetI));
	ProtectXGE(PROTECT_FXDL,g_data3I2.m_nData,wSetI,SETPOINT(wFXDL_SetT),FALSE);
}


//-----------------------------------------------------------------------------
//零序电流:
void CMyProtectItemLXDL::Run(void)
{
	WORD wSetI0 = I0toRun(SETPOINT(wLXDL_SetI));
	ProtectXGE(PROTECT_LXDL,g_data3I0.m_nData,wSetI0,SETPOINT(wLXDL_SetT),FALSE);
}


//-----------------------------------------------------------------------------
//过电压:
void CMyProtectItemGDY::Run(void)
{
	BOOL bLock = FALSE;
	WORD wSetU = UlltoRun(SETPOINT(wGDY_SetU));
	if(g_breaker.GetStatus()==BOSTATUS_OPENED) bLock = TRUE;
	ProtectXGE(PROTECT_GDY,s_wDataUllMax,wSetU,SETPOINT(wGDY_SetT),bLock);
}


//-----------------------------------------------------------------------------
//低电压:
void CMyProtectItemDDY::Run(void)
{
	BOOL bLock = FALSE;
	WORD wSetU = UlltoRun(SETPOINT(wDDY_SetU));
	if(g_breaker.GetStatus()==BOSTATUS_OPENED||g_app.IsPTBreak()) bLock = TRUE;
	ProtectXLE(PROTECT_DDY,s_wDataUllMin,wSetU,SETPOINT(wDDY_SetT),bLock);
}


//-----------------------------------------------------------------------------
//失压:
void CMyProtectItemSY::Run(void)
{
	BOOL bLock = FALSE;
	WORD wSetU = UlltoRun(SETPOINT(wSY_SetU));
	if(g_breaker.GetStatus()==BOSTATUS_OPENED||s_wDataIMax) bLock = TRUE;
	ProtectXLE(PROTECT_SY,s_wDataUllMax,wSetU,SETPOINT(wSY_SetT),bLock);
}


//-----------------------------------------------------------------------------
//负序电压:
void CMyProtectItemFXDY::Run(void)
{
	BOOL bLock = FALSE;
	WORD wSetU = UlltoRun(SETPOINT(wFXDY_SetU));
	if(g_breaker.GetStatus()==BOSTATUS_OPENED||g_app.IsPTBreak()) bLock = TRUE;
	ProtectXGE(PROTECT_FXDY,g_data3U2.m_nData,wSetU,SETPOINT(wFXDY_SetT),bLock);
}


//-----------------------------------------------------------------------------
//零序电压:
void CMyProtectItemLXDY::Run(void)
{
	BOOL bLock = FALSE;
	WORD wSetU0 = U0toRun(SETPOINT(wLXDY_SetU));
	if(g_breaker.GetStatus()==BOSTATUS_OPENED) bLock = TRUE;
#ifndef DFT_3U0
	else if(g_app.IsPTBreak()) bLock = TRUE;
#endif
	ProtectXGE(PROTECT_LXDY,g_data3U0.m_nData,wSetU0,SETPOINT(wLXDY_SetT),bLock);
}


//-----------------------------------------------------------------------------
//复合电压过流:
void CMyProtectItemFHDYGL::Run(void)
{
	WORD wLockDY = 0;
	WORD wLockFX = 0;
	if(SETPOINT(wFHDYGL_TogDY)==PROTECTTOG_ON)
	{
		wLockDY = 1;
		WORD wSetU = UlltoRun(SETPOINT(wFHDYGL_SetU));
		if(s_wDataUllMin<wSetU) wLockDY = 2;
	}
	if(SETPOINT(wFHDYGL_TogFXDY)==PROTECTTOG_ON)
	{
		wLockFX = 1;
		WORD wSetUFX = UlltoRun(SETPOINT(wFHDYGL_SetUFX));
		if(g_data3U2.m_nData>wSetUFX) wLockFX = 2;
	}
	if(wLockDY==2||wLockFX==2)
	{
		wLockDY = 0;
		wLockFX = 0;
	}
	WORD wSetI = IPtoRun(SETPOINT(wFHDYGL_SetI));
	ProtectXGE(PROTECT_FHDYGL,s_wDataIMax,wSetI,SETPOINT(wFHDYGL_SetT),(wLockDY||wLockFX));
}


//-----------------------------------------------------------------------------
//低周减载:
void CMyProtectItemDZJZ::Run(void)
{
	BOOL bStartOK = (g_dataF.m_nData>4950 && g_dataF.m_nData<5050)?TRUE:FALSE;
	ProtectDXDT((WORD)g_dataF.m_nData,bStartOK,SETPOINT(wDZJZ_TogDFDT),SETPOINT(wDZJZ_SetDFDT));
	BOOL bLock = (m_wCountLock>0)?TRUE:FALSE;
	if(g_dataF.m_nData==0||g_breaker.GetStatus()==BOSTATUS_OPENED) bLock = TRUE;
	if(SETPOINT(wDZJZ_TogDY)==PROTECTTOG_ON)
	{
		WORD wSetU = UlltoRun(SETPOINT(wDZJZ_SetU));
		if(!g_app.IsPTBreak()&&s_wDataUllMin<wSetU) bLock = TRUE;
	}
	if(SETPOINT(wDZJZ_TogDL)==PROTECTTOG_ON)
	{
		if(s_wDataIMax<15) bLock = TRUE;				//FixTo:15(=0.5A);
	}
	ProtectXLE(PROTECT_DZJZ,g_dataF.m_nData,SETPOINT(wDZJZ_SetF),SETPOINT(wDZJZ_SetT),bLock);
}


//-----------------------------------------------------------------------------
//低压解列:
void CMyProtectItemDYJL::Run(void)
{
	WORD wSetU = UlltoRun(SETPOINT(wDYJL_SetU));
	WORD wSetURst = wSetU+(wSetU+10)/20;
	BOOL bStartOK = (s_wDataUllMin>wSetURst)?TRUE:FALSE;
	WORD wSetDVDT = WORD((DWORD)3000L*SETPOINT(wDYJL_SetDVDT)/g_pDeviceParam->wScale2Uln);
	ProtectDXDT(s_wDataUllMin,bStartOK,SETPOINT(wDYJL_TogDVDT),wSetDVDT);
	BOOL bLock = (m_wCountLock>0)?TRUE:FALSE;
	if(g_breaker.GetStatus()==BOSTATUS_OPENED) bLock = TRUE;
	if(SETPOINT(wDYJL_TogDL)==PROTECTTOG_ON)
	{
		if(s_wDataIMax<15) bLock = TRUE;				//FixTo:15(=0.5A);
	}
	if(g_data3U2.m_nData>94) bLock = TRUE;				//FixTo:94(=5V);
	ProtectXLE(PROTECT_DYJL,s_wDataUllMin,wSetU,SETPOINT(wDYJL_SetT),bLock);
}


//-----------------------------------------------------------------------------
//重合闸*/
static const WORD c_wTableCosA[91] = 
{
	0x2710,0x270e,0x270a,0x2702,0x26f8,0x26ea,0x26d9,0x26c5,0x26af,0x2695,
	0x2678,0x2658,0x2635,0x2610,0x25e7,0x25bb,0x258d,0x255b,0x2527,0x24ef,
	0x24b5,0x2478,0x2438,0x23f5,0x23af,0x2367,0x231c,0x22ce,0x227d,0x222a,
	0x21d4,0x217c,0x2120,0x20c3,0x2062,0x2000,0x1f9a,0x1f32,0x1ec8,0x1e5b,
	0x1dec,0x1d7b,0x1d07,0x1c92,0x1c19,0x1b9f,0x1b23,0x1aa4,0x1a23,0x19a1,
	0x191c,0x1895,0x180d,0x1782,0x16f6,0x1668,0x15d8,0x1546,0x14b3,0x141e,
	0x1388,0x12f0,0x1257,0x11bc,0x1120,0x1082,0x0fe3,0x0f43,0x0ea2,0x0e00,
	0x0d5c,0x0cb8,0x0c12,0x0b6c,0x0ac4,0x0a1c,0x0973,0x08ca,0x081f,0x0774,
	0x06c8,0x061c,0x0570,0x04c3,0x0415,0x0368,0x02ba,0x020b,0x015d,0x00af,
	0x0000
};


void CMyProtectItemCHZ::OnInit(void)
{
	m_wTime = 0;
	m_wRunStep = RUNSTEP_CHARGING;
	m_wTimeCharge = 0;
	m_wAllowFlag = 0x0000;
}

void CMyProtectItemCHZ::Run(void)
{
	switch(m_wRunStep)
	{
	case RUNSTEP_CHARGING: RunCharging(); break;
	case RUNSTEP_CHARGED: RunCharged(); break;
	case RUNSTEP_STARTUP: RunStartup(); break;
	default: OnInit(); break;
	}
}

void CMyProtectItemCHZ::Discharge(void)
{
	OnInit();
}

WORD CMyProtectItemCHZ::GetChargeStatus(void)
{
	if(m_wTimeCharge==0) return 0;
	else if(m_wTimeCharge<2000) return 1;
	return 2;
}

void CMyProtectItemCHZ::SetAllowFlag(void)
{
	m_wAllowFlag = 0xaaaa;
}

void CMyProtectItemCHZ::RunCharging(void)
{
	if(g_breaker.GetStatus()==BOSTATUS_CLOSED)
	{
		if(m_wTimeCharge<2000) m_wTimeCharge++;
		else m_wRunStep = RUNSTEP_CHARGED;
	}
	else OnInit();
}

void CMyProtectItemCHZ::RunCharged(void)
{
	if(g_breaker.m_wCountAfterTripped && g_breaker.GetStatus()==BOSTATUS_OPENED)
	{
		if(m_wAllowFlag==0xaaaa)
		{
			m_wAllowFlag = 0x0000;
			m_wTime = 0;
			m_wRunStep = RUNSTEP_STARTUP;
		}
		else OnInit();
	}
	else RunCharging();
}

void CMyProtectItemCHZ::RunStartup(void)
{
	if(g_breaker.GetStatus()==BOSTATUS_OPENED)
	{
		m_wTime++;
		if(m_wTime>=SETPOINT(wCHZ_SetT))
		{
			if(SETPOINT(wCHZ_TogWY)==PROTECTTOG_ON)
			{
				short nmaxUx = MAX(g_dataUxab.m_nData,g_dataUxbc.m_nData);
				short nmaxU = MAX(g_dataUab.m_nData,g_dataUbc.m_nData);
				if(nmaxUx<563||nmaxU<563) g_protect.SetProtectAct(PROTECT_CHZ,0xffff,0x5555);	//FixTo:563(=30V);
			}
			else if(SETPOINT(wCHZ_TogTQ)==PROTECTTOG_ON)
			{
				WORD wUab2 = g_dataUab.GetValueSecondaryFix();
				WORD wUxab2 = g_dataUxab.GetValueSecondaryFix();
				WORD wUbc2 = g_dataUbc.GetValueSecondaryFix();
				WORD wUxbc2 = g_dataUxbc.GetValueSecondaryFix();
				WORD wF = (WORD)g_dataF.m_nData;
				WORD wFx = (WORD)g_dataFx.m_nData;
				WORD wDiffF = (wF>wFx)?(wF-wFx):(wFx-wF);
				WORD wDiffU = (wUab2>wUxab2)?(wUab2-wUxab2):(wUxab2-wUab2);
				if(wDiffF<50 && wDiffU<1000 && g_dataUxab.m_nData>1313 && g_dataUxbc.m_nData>1313)							//FixTo:1313(=70V);
				{
					long lVPab = GetVP(&g_dataUab,&g_dataUxab);
					long lVQab = GetVQ(&g_dataUab,&g_dataUxab);
					long lVPbc = GetVP(&g_dataUbc,&g_dataUxbc);
					long lVQbc = GetVQ(&g_dataUbc,&g_dataUxbc);
					lVPab /= 3000;
					lVQab /= 3000;
					lVQab = GetSqrtX((short)lVPab,(short)lVQab);
					lVPab *= 10000L;
					lVPab /= lVQab;
					lVPbc /= 3000;
					lVQbc /= 3000;
					lVQbc = GetSqrtX((short)lVPbc,(short)lVQbc);
					lVPbc *= 10000L;
					lVPbc /= lVQbc;
					if(lVPab>=(long)c_wTableCosA[SETPOINT(wCHZ_SetA)]&&lVPbc>=(long)c_wTableCosA[SETPOINT(wCHZ_SetA)])
					{
						g_protect.SetProtectAct(PROTECT_CHZ,0xffff,0x5555);
					}
				}
			}
			else g_protect.SetProtectAct(PROTECT_CHZ,0xffff,0x5555);
			OnInit();
		}
	}
	else OnInit();
}


//-----------------------------------------------------------------------------
//备自投:
void CMyProtectItemBZT::OnInit(void)
{
	m_wTime = 0;
	m_wRunStep = RUNSTEP_CHARGING;
	m_wTimeCharge = 0;
	m_wLine1LostPowerFlag = 0x0000;
	m_wLine2HavePowerFlag = 0x0000;
	m_pCloseRelay = NULL;
}

void CMyProtectItemBZT::Run(void)
{
	if((g_deviceInfo.wSwitchStatus1&SS_IN09)==0 && IsLine2HavePower()==TRUE)
	{
		switch(m_wRunStep)
		{
		case RUNSTEP_CHARGING: RunCharging(); break;
		case RUNSTEP_CHARGED: RunCharged(); break;
		case RUNSTEP_STARTUP: RunStartup(); break;
		default: OnInit(); break;
		}
	}
	else OnInit();
}

void CMyProtectItemBZT::Discharge(void)
{
	OnInit();
}

WORD CMyProtectItemBZT::GetChargeStatus(void)
{
	if(m_wTimeCharge==0) return 0;
	else if(m_wTimeCharge<2000) return 1;
	return 2;
}

void CMyProtectItemBZT::SetCloseRelay(CMyOutput* pRelay)
{
	m_pCloseRelay = pRelay;
}

void CMyProtectItemBZT::ForceLine1LostPower(BOOL bLostPower)
{
	m_wLine1LostPowerFlag = (bLostPower==TRUE)?0xaaaa:0x0000;
}

void CMyProtectItemBZT::ForceLine2HavePower(BOOL bHavePower)
{
	m_wLine2HavePowerFlag = (bHavePower==TRUE)?0xaaaa:0x0000;
}

void CMyProtectItemBZT::RunCharging(void)
{
	if(g_breaker.GetStatus()==BOSTATUS_CLOSED)
	{
		if(IsChargeAllow()==TRUE)
		{
			if(m_wTimeCharge<2000) m_wTimeCharge++;
			else
			{
				m_wTime = 0;
				m_wRunStep = RUNSTEP_CHARGED;
			}
		}
		else
		{
			if(m_wTimeCharge>=20) m_wTimeCharge -= 20;
			else OnInit();
		}
	}
	else OnInit();
}

void CMyProtectItemBZT::RunCharged(void)
{
	if(g_breaker.GetStatus()==BOSTATUS_CLOSED && IsLine1LostPower()==TRUE)
	{
		m_wTime++;
		if(m_wTime>=SETPOINT(wBZT_SetT))
		{
			m_wTime = 50;
			m_wRunStep = RUNSTEP_STARTUP;
			g_protect.SetProtectAct(PROTECT_BZT,0xffff,0x3333);
		}
	}
	else RunCharging();
}

void CMyProtectItemBZT::RunStartup(void)
{
	if(m_wTime)
	{
		m_wTime--;
		if(g_breaker.GetStatus()==BOSTATUS_OPENED)
		{
			if(SETPOINTCFG(PROTECT_BZT)==PROTECTCFG_TRP||SETPOINTCFG(PROTECT_BZT)==PROTECTCFG_TAP)
			{
				if(m_pCloseRelay!=NULL) m_pCloseRelay->SetPulse(20);
			}
			OnInit();
		}
	}
	else OnInit();
}

BOOL CMyProtectItemBZT::IsLine1LostPower(void)
{
	if(m_wLine1LostPowerFlag==0xaaaa) return TRUE;
	WORD wSetU = UlltoRun(SETPOINT(wBZT_SetU));
	if(s_wDataIMax==0 && s_wDataUllMax<wSetU) return TRUE;
	return FALSE;
}

BOOL CMyProtectItemBZT::IsLine2HavePower(void)
{
	short nmaxUx = MAX(g_dataUxab.m_nData,g_dataUxbc.m_nData);
	if(m_wLine2HavePowerFlag==0xaaaa) return TRUE;
	if(nmaxUx>1313) return TRUE;								//FixTo:1313(=70V);
	return FALSE;
}

BOOL CMyProtectItemBZT::IsChargeAllow(void)
{
	if(s_wDataUllMin>1313 && m_wLine1LostPowerFlag!=0xaaaa) return TRUE;	//FixTo:1313(=70V);
	return FALSE;
}


//-----------------------------------------------------------------------------
//过热:
void CMyProtectItemGR::OnInit(void)
{
	CMyProtectItemIDMT::OnInit();
	m_wPercentGR = 0;
}

void CMyProtectItemGR::Run(void)
{
	WORD wSetI = IPtoRun(SETPOINT(wGR_SetI));
	if(wSetI==0) return;
	WORD wDataI1 = CMyMeasure::CalculateNegSeq(&g_dataIC,&g_dataIB,&g_dataIA)/3;
	WORD wDataI2 = g_data3I2.m_nData/3;
	DWORD dwDataI12 = (DWORD)wDataI1*(DWORD)wDataI1;
	if(s_wMotorStartTime) dwDataI12 /= 2;
	DWORD dwDataI22 = (DWORD)wDataI2*(DWORD)wDataI2;
	DWORD dwDataIeq2 = dwDataI12 + dwDataI22*SETPOINT(wGR_SetK2)/100;
	DWORD dwSetI2 = (DWORD)wSetI*(DWORD)wSetI;
	dwSetI2 >>= 2;
	dwDataIeq2 >>= 2;
	WORD wDataIeq = GetSqrt(dwDataIeq2);
	m_dwSumIDMT += 100L*dwDataIeq2/dwSetI2;
	if(m_dwSumIDMT>100L) m_dwSumIDMT -= 100L;
	else m_dwSumIDMT = 0;
	dwSetI2 = 8000L*SETPOINT(wGR_SetT);
	if(m_dwSumIDMT>dwSetI2)
	{
		m_dwSumIDMT = dwSetI2;
		g_protect.SetProtectAct(PROTECT_GR,(WORD)(wDataIeq<<1),0x3333);
	}
	m_wPercentGR = (WORD)(100L*(m_dwSumIDMT>>7)/(dwSetI2>>7));
}

WORD CMyProtectItemGR::GetPercentGR(void)
{
	return m_wPercentGR;
}


//-----------------------------------------------------------------------------
//逆功率:
void CMyProtectItemNGL::Run(void)
{
	DWORD dwScale = ((DWORD)g_pDeviceParam->wScale2IP*(DWORD)g_pDeviceParam->wScale2Uln+5000)/10000;
	WORD wScale = (WORD)((9000000L + dwScale/2)/dwScale);		// 3000*3000/(173.2*100)

	long lP1,lQ1,lP2,lQ2;
	CMyData DataUcb;
	DataUcb.SetData(-g_dataUbc.m_nR,-g_dataUbc.m_nX,g_dataUbc.m_nData);
	CMyPQPhQh::CalculatePQ(&g_dataIA,&g_dataUab,&lP1,&lQ1);
	CMyPQPhQh::CalculatePQ(&g_dataIC,&DataUcb,&lP2,&lQ2);
	long lNGL_SetP = -((long)SETPOINT(wNGL_SetP)*wScale+5)/10;
	WORD wNGL = (WORD)((-(lP1+lP2)+wScale/2)/wScale);
	if(lP1+lP2<lNGL_SetP)
	{
		m_wTime++;
		if(m_wTime>=SETPOINT(wNGL_SetT))
		{
			m_wTime = SETPOINT(wNGL_SetT);
			g_protect.SetProtectAct(PROTECT_NGL,wNGL,0x3333);
		}
	}
	else if(m_wTime) m_wTime--;
}


//-----------------------------------------------------------------------------
//启动时间过长:
void CMyProtectItemQDSJGC::Run(void)
{
	WORD wSetI = IPtoRun(SETPOINT(wMotor_SetI));
	if(s_wMotorStartTime==0||s_wMotorStartTime>3) m_wTime = 0;
	else ProtectXGE(PROTECT_QDSJGC,s_wDataIMax,(WORD)(wSetI*6/5),3,FALSE);
}


//-----------------------------------------------------------------------------
//定时限Ix过流:
void CMyProtectItemIXDSX::Run(void)
{
	WORD wSetIx = IXtoRun(SETPOINT(wIXDSX_SetI));
	ProtectXGE(PROTECT_IXDSX,g_dataIx.m_nData,wSetIx,SETPOINT(wIXDSX_SetT),FALSE);
}


//-----------------------------------------------------------------------------
//反时限Ix过流:
void CMyProtectItemIXFSX::Run(void)
{
	WORD wSetIx = IXtoRun(SETPOINT(wIXFSX_SetI));
	ProtectIDMT(PROTECT_IXFSX,SETPOINT(wIXFSX_IDMT),SETPOINT(wIXFSX_SetK),wSetIx,g_dataIx.m_nData);
}


//-----------------------------------------------------------------------------
void CMyProtectiBCUX42::OnInit(void)
{
	CMyProtect::OnInit();
	g_pDeviceSetpoint = (DEVICESETPOINT_iBCUX42*)g_protect.GetSetpointArea();
	g_pDeviceSetpointConfig = (DEVICESETPOINT_iBCUX42CONFIG*)&g_deviceSetpoint.wSetpointConfig[0];
	s_wMotorStartPickupData1 = 0;
	s_wMotorStartPickupData2 = 0;
	s_wMotorStartPickupData3 = 0;
	s_wMotorStartPickupData4 = 0;
	s_wMotorStartPickupData5 = 0;
	s_wMotorStartPickupData6 = 0;
	s_wMotorStartPickupData7 = 0;
	s_wMotorStartPickupData8 = 0;
	s_wMotorStartPickupData9 = 0;
	s_wMotorStartTime = 0;
	m_piSD.OnInit();
	m_piXSSD.OnInit();
	m_piDSXGL.OnInit();
	m_piFSXGL.OnInit();
	m_piHJS.OnInit();
	m_piGFH.OnInit();
	m_piFXDL.OnInit();
	m_piLXDL.OnInit();
	m_piGDY.OnInit();
	m_piDDY.OnInit();
	m_piSY.OnInit();
	m_piFXDY.OnInit();
	m_piLXDY.OnInit();
	m_piFHDYGL.OnInit();
	m_piDZJZ.OnInit();
	m_piDYJL.OnInit();
	m_piCHZ.OnInit();
	m_piBZT.OnInit();
	m_piGR.OnInit();
	m_piNGL.OnInit();
	m_piQDSJGC.OnInit();
	m_piIXDSX.OnInit();
	m_piIXFSX.OnInit();
}

void CMyProtectiBCUX42::OnInitSetpoint(WORD* pSetpoint)
{
	*(DEVICESETPOINT_iBCUX42*)pSetpoint = c_setpointiBCUX42;
}

void CMyProtectiBCUX42::iiiOnProtectActAlarmed(WORD wProtectIndex)
{
	CMyProtect::iiiOnProtectActAlarmed(wProtectIndex);
}

void CMyProtectiBCUX42::iiiOnProtectActTripped(WORD wProtectIndex)
{
	CMyProtect::iiiOnProtectActTripped(wProtectIndex);
	if(wProtectIndex==PROTECT_SD) m_piCHZ.SetAllowFlag();
	if(wProtectIndex==PROTECT_XSSD) m_piCHZ.SetAllowFlag();
	if(wProtectIndex==PROTECT_DSXGL) m_piCHZ.SetAllowFlag();
}

void CMyProtectiBCUX42::iiiRun(void)
{
	CMyProtect::iiiRun();
	g_pDeviceSetpoint = (DEVICESETPOINT_iBCUX42*)g_protect.GetSetpointArea();
	g_pDeviceSetpointConfig = (DEVICESETPOINT_iBCUX42CONFIG*)&g_deviceSetpoint.wSetpointConfig[0];
	s_wDataIMax = GetMax(g_dataIA.m_nData,g_dataIB.m_nData,g_dataIC.m_nData);
	s_wDataIMax2 = GetMax(g_dataIA.m_nData,0,g_dataIC.m_nData);
	s_wDataUllMax = GetMax(g_dataUab.m_nData,g_dataUbc.m_nData,g_dataUca.m_nData);
	s_wDataUllMin = GetMin(g_dataUab.m_nData,g_dataUbc.m_nData,g_dataUca.m_nData);
	if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
	{
		WORD wSetIM = IPtoRun(SETPOINT(wMotor_SetI));
		WORD wSetIStart0_1 = wSetIM/10;
		if(s_wMotorStartPickupData1==0 && s_wDataIMax>wSetIStart0_1) s_wMotorStartTime = SETPOINT(wMotor_SetT);
		else if(s_wMotorStartTime) s_wMotorStartTime--;
		WORD wSetIStart1_2 = wSetIM*6/5;
		if(s_wMotorStartPickupData1<wSetIStart1_2 && s_wDataIMax<wSetIStart1_2) s_wMotorStartTime = 0;
		s_wMotorStartPickupData1 = s_wMotorStartPickupData2;
		s_wMotorStartPickupData2 = s_wMotorStartPickupData3;
		s_wMotorStartPickupData3 = s_wMotorStartPickupData4;
		s_wMotorStartPickupData4 = s_wMotorStartPickupData5;
		s_wMotorStartPickupData5 = s_wMotorStartPickupData6;
		s_wMotorStartPickupData6 = s_wMotorStartPickupData7;
		s_wMotorStartPickupData7 = s_wMotorStartPickupData8;
		s_wMotorStartPickupData8 = s_wMotorStartPickupData9;
		s_wMotorStartPickupData9 = s_wDataIMax;
	}
	else
	{
		s_wMotorStartPickupData1 = 0;
		s_wMotorStartPickupData2 = 0;
		s_wMotorStartPickupData3 = 0;
		s_wMotorStartPickupData4 = 0;
		s_wMotorStartPickupData5 = 0;
		s_wMotorStartPickupData6 = 0;
		s_wMotorStartPickupData7 = 0;
		s_wMotorStartPickupData8 = 0;
		s_wMotorStartPickupData9 = 0;
		s_wMotorStartTime = 0;
	}
	s_wDataIMaxFX = 0;
	s_wDataIMaxFX2 = 0;
	if(g_pDeviceSetpointConfig->bConfigFX==TRUE)
	{
		GetPowerDirectABC(&g_dataUbc,&g_dataIA);
		GetPowerDirectABC(&g_dataUab,&g_dataIC);
		s_wDataIMaxFX2 = s_wDataIMaxFX;
		GetPowerDirectABC(&g_dataUca,&g_dataIB);
	}

	if((g_deviceInfo.wDeviceStatus1&(DS1_ErrorAD|DS1_ErrorSetpoint))==0)
	{
		if(g_protect.m_wProtectRun[PROTECT_SD]==PROTECTTOG_ON) m_piSD.Run();
		else m_piSD.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_XSSD]==PROTECTTOG_ON) m_piXSSD.Run();
		else m_piXSSD.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_DSXGL]==PROTECTTOG_ON) m_piDSXGL.Run();
		else m_piDSXGL.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_FSXGL]==PROTECTTOG_ON) m_piFSXGL.Run();
		else m_piFSXGL.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_HJS]==PROTECTTOG_ON) m_piHJS.Run();
		else m_piHJS.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_GFH]==PROTECTTOG_ON) m_piGFH.Run();
		else m_piGFH.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_FXDL]==PROTECTTOG_ON) m_piFXDL.Run();
		else m_piFXDL.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_LXDL]==PROTECTTOG_ON) m_piLXDL.Run();
		else m_piLXDL.OnInit();
// 		if(g_protect.m_wProtectRun[PROTECT_JDSX]==PROTECTTOG_ON) m_piJDSX.Run();
// 		else m_piJDSX.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_GDY]==PROTECTTOG_ON) m_piGDY.Run();
		else m_piGDY.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_DDY]==PROTECTTOG_ON) m_piDDY.Run();
		else m_piDDY.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_SY]==PROTECTTOG_ON) m_piSY.Run();
		else m_piSY.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_FXDY]==PROTECTTOG_ON) m_piFXDY.Run();
		else m_piFXDY.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_LXDY]==PROTECTTOG_ON) m_piLXDY.Run();
		else m_piLXDY.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_FHDYGL]==PROTECTTOG_ON) m_piFHDYGL.Run();
		else m_piFHDYGL.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_DZJZ]==PROTECTTOG_ON) m_piDZJZ.Run();
		else m_piDZJZ.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_DYJL]==PROTECTTOG_ON) m_piDYJL.Run();
		else m_piDYJL.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_CHZ]==PROTECTTOG_ON) m_piCHZ.Run();
		else m_piCHZ.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_BZT]==PROTECTTOG_ON) m_piBZT.Run();
		else m_piBZT.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_GR]==PROTECTTOG_ON) m_piGR.Run();
		else m_piGR.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_NGL]==PROTECTTOG_ON) m_piNGL.Run();
		else m_piNGL.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_QDSJGC]==PROTECTTOG_ON) m_piQDSJGC.Run();
		else m_piQDSJGC.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_IXDSX]==PROTECTTOG_ON) m_piIXDSX.Run();
		else m_piIXDSX.OnInit();
		if(g_protect.m_wProtectRun[PROTECT_IXFSX]==PROTECTTOG_ON) m_piIXFSX.Run();
		else m_piIXFSX.OnInit();
	}
}

WORD CMyProtectiBCUX42::GetProtectPickupInfo(WORD wProtectIndex)
{
	switch(wProtectIndex)
	{
	case PROTECT_SD: return m_piSD.GetProtectPickupInfo();
	case PROTECT_XSSD: return m_piXSSD.GetProtectPickupInfo();
	case PROTECT_DSXGL: return m_piDSXGL.GetProtectPickupInfo();
	case PROTECT_FSXGL: return m_piFSXGL.GetProtectPickupInfo();
	case PROTECT_HJS: return m_piHJS.GetProtectPickupInfo();
	case PROTECT_GFH: return m_piGFH.GetProtectPickupInfo();
	case PROTECT_FXDL: return m_piFXDL.GetProtectPickupInfo();
	case PROTECT_LXDL: return m_piLXDL.GetProtectPickupInfo();
// 	case PROTECT_JDSX: return m_piJDSX.GetProtectPickupInfo();
	case PROTECT_GDY: return m_piGDY.GetProtectPickupInfo();
	case PROTECT_DDY: return m_piDDY.GetProtectPickupInfo();
	case PROTECT_SY: return m_piSY.GetProtectPickupInfo();
	case PROTECT_FXDY: return m_piFXDY.GetProtectPickupInfo();
	case PROTECT_LXDY: return m_piLXDY.GetProtectPickupInfo();
	case PROTECT_FHDYGL: return m_piFHDYGL.GetProtectPickupInfo();
	case PROTECT_DZJZ: return m_piDZJZ.GetProtectPickupInfo();
	case PROTECT_DYJL: return m_piDYJL.GetProtectPickupInfo();
	case PROTECT_CHZ: return m_piCHZ.GetProtectPickupInfo();
	case PROTECT_BZT: return m_piBZT.GetProtectPickupInfo();
	case PROTECT_GR: return m_piGR.GetProtectPickupInfo();
	case PROTECT_NGL: return m_piNGL.GetProtectPickupInfo();
	case PROTECT_IXDSX: return m_piIXDSX.GetProtectPickupInfo();
	case PROTECT_IXFSX: return m_piIXFSX.GetProtectPickupInfo();
	}
	return 0x0000;
}

void CMyProtectiBCUX42::OnUpdateDevice(WORD* pData)
{
	CMyProtect::OnUpdateDevice(pData);
	DEVICESETPOINT_iBCUX42CONFIG* pDeviceSetpointiBCUX42Config = (DEVICESETPOINT_iBCUX42CONFIG*)&g_deviceSetpoint.wSetpointConfig[0];
	DEVICESETPOINT_iBCUX42* pDeviceSetpointiBCUX42_1 = (DEVICESETPOINT_iBCUX42*)&g_deviceSetpoint.wSetpointArea1[0];
	DEVICESETPOINT_iBCUX42* pDeviceSetpointiBCUX42_2 = (DEVICESETPOINT_iBCUX42*)&g_deviceSetpoint.wSetpointArea2[0];
	DEVICESETPOINT_iBCUX42* pDeviceSetpointiBCUX42_3 = (DEVICESETPOINT_iBCUX42*)&g_deviceSetpoint.wSetpointArea3[0];
	if(pDeviceSetpointiBCUX42Config->bConfigMotor!=TRUE)
	{
		pDeviceSetpointiBCUX42_1->wSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_2->wSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_3->wSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_1->wXSSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_2->wXSSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_3->wXSSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_1->wDSXGL_TogAE = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_2->wDSXGL_TogAE = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_3->wDSXGL_TogAE = PROTECTTOG_OFF;
	}
	if(pDeviceSetpointiBCUX42Config->bConfigFX!=TRUE)
	{
		pDeviceSetpointiBCUX42_1->wSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_2->wSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_3->wSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_1->wXSSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_2->wXSSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_3->wXSSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_1->wDSXGL_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_2->wDSXGL_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_3->wDSXGL_TogFX = PROTECTTOG_OFF;
	}
	if(pDeviceSetpointiBCUX42Config->bConfigDY!=TRUE)
	{
		pDeviceSetpointiBCUX42_1->wSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_2->wSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_3->wSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_1->wXSSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_2->wXSSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_3->wXSSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_1->wDSXGL_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_2->wDSXGL_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointiBCUX42_3->wDSXGL_TogDY = PROTECTTOG_OFF;
	}
}

WORD CMyProtectiBCUX42::GetMotorStartTime(void)
{
	return s_wMotorStartTime;
}
