#include <Main.h>

const SETPOINTCFGINFO c_setpointCfgInfoW[8] = 
{
	{"ѡ��:�綯������",	"OPT:\1MOTOR PROTECTION"},
	{"ѡ��:�������",	"OPT:\1DIRECTIONAL BLOCKING"},
	{"ѡ��:��ѹ����",	"OPT:\1UNDERVOLTAGE BLOCKING"},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL}
};

const SETPOINTCFGINFO c_setpointCfgInfo[8] = 
{
	{"ѡ��:�綯������",	"OPT:\1MOTOR PROTECT"},
	{"ѡ��:�������",	"OPT:\1DIRECT BLOCK"},
	{"ѡ��:��ѹ����",	"OPT:\1UNDERVOL BLOCK"},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL},
	{NULL,				NULL}
};

const PROTECTACTINFO c_protectActInfoW[32] = 
{
	{"�����ٶ�",	"OVERCURRENT INSTANT.",		PROTECTACT_IP},
	{"��ʱ�����ٶ�","OVERCURRENT HIGH",			PROTECTACT_IP},
	{"��ʱ�޹���",	"OVERCURRENT LOW",			PROTECTACT_IP},
	{"��ʱ�޹���",	"OVERCURRENT IDMT",			PROTECTACT_IP},
	{"�����",		"ACCELERATED TRIP",			PROTECTACT_IP},
	{"������",		"OVERLOAD",					PROTECTACT_IP},
	{"�������",	"NEGATIVE OVERCURRENT",		PROTECTACT_IP},
	{"�������",	"RESIDUAL OVERCURRENT",		PROTECTACT_3I0},
	{"����ӵ�ѡ��","EARTH-FAULT DETECTION",	PROTECTACT_3I0},
	{"����ѹ",		"OVERVOLTAGE",				PROTECTACT_U},
	{"�͵�ѹ",		"UNDERVOLTAGE",				PROTECTACT_U},
	{"ʧѹ",		"PRIMARY POWER FAULT",		PROTECTACT_U},
	{"�����ѹ",	"NEGATIVE OVERVOLTAGE",		PROTECTACT_U},
	{"�����ѹ",	"RESIDUAL OVERVOLTAGE",		PROTECTACT_3U0},
	{"���ϵ�ѹ����","COMPOUND OVERCURRENT",		PROTECTACT_IP},
	{"���ܼ���",	"UNDERFREQENCY SHEDDING",	PROTECTACT_F},
	{"��ѹ����",	"UNDERVOLTAGE DECOUPLING",	PROTECTACT_U},
	{"�غ�բ",		"AUTO-RECLOSURE",			PROTECTACT_NULL},
	{"����Ͷ",		"AUTO-SWITCHING",			PROTECTACT_NULL},
	{"����",		"THERMAL OVERLOAD",			PROTECTACT_IP},
	{"�湦��",		"REVERSE POWER",			PROTECTACT_P},
	{"����ʱ�����","MOTOR STARTING TIME",		PROTECTACT_NULL},
	{"��ʱ��Ix����","Ix OVERCURRENT ",			PROTECTACT_Ix},
	{"��ʱ��Ix����","Ix OVERCURRENT IDMT",		PROTECTACT_Ix},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL},
	{NULL,			NULL,						PROTECTACT_NULL}
};

const PROTECTACTINFO c_protectActInfo[32] = 
{
	{"�����ٶ�",		"OVERCUR INSTANT",		PROTECTACT_IP},
	{"��ʱ�����ٶ�",	"OVERCUR HIGH",			PROTECTACT_IP},
	{"��ʱ�޹���",		"OVERCUR LOW",			PROTECTACT_IP},
	{"��ʱ�޹���",		"OVERCUR IDMT",			PROTECTACT_IP},
	{"�����",			"ACC. TRIP",			PROTECTACT_IP},
	{"������",			"OVERLOAD",				PROTECTACT_IP},
	{"�������",		"NEG OVERCUR",			PROTECTACT_IP},
	{"�������",		"RES OVERCUR",			PROTECTACT_3I0},
	{"����ӵ�ѡ��",	"E-FAULT DETECT",		PROTECTACT_3I0},
	{"����ѹ",			"OVERVOLTAGE",			PROTECTACT_U},
	{"�͵�ѹ",			"UNDERVOLTAGE",			PROTECTACT_U},
	{"ʧѹ",			"PRI. PWR FAULT",		PROTECTACT_U},
	{"�����ѹ",		"NEG OVERVOLTAGE",		PROTECTACT_U},
	{"�����ѹ",		"RES OVERVOLTAGE",		PROTECTACT_3U0},
	{"���ϵ�ѹ����",	"COMP. OVERCUR",		PROTECTACT_IP},
	{"���ܼ���",		"UNDERFREQENCY",		PROTECTACT_F},
	{"��ѹ����",		"U-VOL DECOUPLING",		PROTECTACT_U},
	{"�غ�բ",			"AUTO-RECLOSURE",		PROTECTACT_NULL},
	{"����Ͷ",			"AUTO-SWITCHING",		PROTECTACT_NULL},
	{"����",			"THERMAL OVERLOAD",		PROTECTACT_IP},
	{"�湦��",			"REVERSE POWER",		PROTECTACT_P},
	{"����ʱ�����",	"MOTOR START TIME",		PROTECTACT_NULL},
	{"��ʱ��Ix����",	"Ix OVERCUR ",			PROTECTACT_Ix},
	{"��ʱ��Ix����",	"Ix OVERCUR IDMT",		PROTECTACT_Ix},
	{NULL,				NULL,					PROTECTACT_NULL},
	{NULL,				NULL,					PROTECTACT_NULL},
	{NULL,				NULL,					PROTECTACT_NULL},
	{NULL,				NULL,					PROTECTACT_NULL},
	{NULL,				NULL,					PROTECTACT_NULL},
	{NULL,				NULL,					PROTECTACT_NULL},
	{NULL,				NULL,					PROTECTACT_NULL},
	{NULL,				NULL,					PROTECTACT_NULL}
};

const DEVICESETPOINT_DMRX01 c_setpointDMRX01 = 
{
	500,						//�綯�������:5A;
	1000,						//�綯������ʱ��:10s;
	//�������ٶϡ�
	10000,						//������ֵ:100A;
	1000,						//ʱ�䶨ֵ:10s;
	12000,						//��ѹ��ֵ:120V;
	PROTECTTOG_OFF,				//��ѹ����Ͷ��:OFF;
	PROTECTTOG_OFF,				//�������Ͷ��:OFF;
	PROTECTTOG_OFF,				//����ʱ��ֵ�Զ��ӱ�Ͷ��:OFF;
	//����ʱ�����ٶϡ�
	10000,						//������ֵ:100A;
	1000,						//ʱ�䶨ֵ:10s;
	12000,						//��ѹ��ֵ:120V;
	PROTECTTOG_OFF,				//��ѹ����Ͷ��:OFF;
	PROTECTTOG_OFF,				//�������Ͷ��:OFF;
	PROTECTTOG_OFF,				//����ʱ��ֵ�Զ��ӱ�Ͷ��:OFF;
	//����ʱ�޹�����
	10000,						//������ֵ:100A;
	1000,						//ʱ�䶨ֵ:10s;
	12000,						//��ѹ��ֵ:120V;
	PROTECTTOG_OFF,				//��ѹ����Ͷ��:OFF;
	PROTECTTOG_OFF,				//�������Ͷ��:OFF;
	PROTECTTOG_OFF,				//����ʱ�����Զ��˳�Ͷ��:OFF;
	//����ʱ�޹�����
	10000,						//������ֵ:100A;
	100,						//ʱ��ϵ��:1.00;
	IDMT_EXTR,					//IDMT����:Extremely Inverse;
	//������١�
	10000,						//������ֵ100A;
	1000,						//ʱ�䶨ֵ10s;
	//�������ɡ�
	10000,						//������ֵ100A;
	1000,						//ʱ�䶨ֵ10s;
	//�����������
	10000,						//������ֵ:100A;
	1000,						//ʱ�䶨ֵ:10s;
	//�����������
	600,						//������ֵ6A;
	1000,						//ʱ�䶨ֵ10s;
	//������ӵ�ѡ�ߡ�
	600,						//������ֵ:6A;
	16000,						//��ѹ��ֵ:160V;
	PROTECTTOG_OFF,				//���г���о�Ͷ��:OFF;
	//������ѹ��
	12000,						//��ѹ��ֵ:120V;
	1000,						//ʱ�䶨ֵ:10s;
	//���͵�ѹ��
	0,							//��ѹ��ֵ:0V;
	1000,						//ʱ�䶨ֵ:10s;
	//��ʧѹ��
	0,							//��ѹ��ֵ:0V;
	1000,						//ʱ�䶨ֵ:10s;
	//�������ѹ��
	12000,						//��ѹ��ֵ:120V;
	1000,						//ʱ�䶨ֵ:10s;
	//�������ѹ��
	16000,						//��ѹ��ֵ:160V;
	1000,						//ʱ�䶨ֵ:10s;
	//�����ϵ�ѹ������
	10000,						//������ֵ:100A;
	12000,						//��ѹ��ֵ:120V;
	12000,						//�����ѹ��ֵ:120V;
	1000,						//ʱ�䶨ֵ:10s;
	PROTECTTOG_OFF,				//��ѹ����Ͷ��:OFF;
	PROTECTTOG_OFF,				//�����ѹ����Ͷ��:OFF;
	//�����ܼ��ء�
	4000,						//Ƶ�ʶ�ֵ:40Hz;
	1000,						//ʱ�䶨ֵ:10s;
	12000,						//��ѹ��ֵ:120V;
	100,						//���ֵ:1.0Hz/s;
	PROTECTTOG_OFF,				//�������Ͷ��:OFF;
	PROTECTTOG_OFF,				//��ѹ����Ͷ��:OFF;
	PROTECTTOG_OFF,				//��������Ͷ��:OFF;
	//����ѹ���С�
	0,							//��ѹ��ֵ:0V;
	1000,						//ʱ�䶨ֵ:10s;
	100,						//���ֵ:1.0V/s;
	PROTECTTOG_OFF,				//�������Ͷ��:OFF;
	PROTECTTOG_OFF,				//��������Ͷ��:OFF;
	//���غ�բ��
	1000,						//ʱ�䶨ֵ:10s;
	30,							//ͬ�ڽǶ�ֵ:30��;
	PROTECTTOG_OFF,				//����ѹͶ��:OFF;
	PROTECTTOG_OFF,				//��ͬ��Ͷ��:OFF;
	//������Ͷ��
	0,							//��ѹ��ֵ:0V;
	1000,						//ʱ�䶨ֵ:10s;
	//�����ȡ�
	10000,						//������ֵ:100A;
	1000,						//ʱ�䶨ֵ:10s;
	600,						//�������ϵ��:6.00;
	//���湦�ʡ�
	0,							//���ʶ�ֵ:0w;
	1000,						//ʱ�䶨ֵ:10s;
	//����ʱ��Ix������
	10000,						//������ֵ:100A;
	1000,						//ʱ�䶨ֵ:10s;
	//����ʱ��Ix������
	10000,						//������ֵ:100A;
	100,						//ʱ��ϵ��:1.00;
	IDMT_EXTR					//IDMT����:Extremely Inverse;
};


DEVICESETPOINT_DMRX01* g_pDeviceSetpoint;
DEVICESETPOINT_DMRX01CONFIG* g_pDeviceSetpointConfig;

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
//�����ٶ�:
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
//��ʱ�����ٶ�:
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
//��ʱ�޹���:
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
//��ʱ�޹���:
void CMyProtectItemFSXGL::Run(void)
{
	WORD wDataI;
	WORD wSetI = IPtoRun(SETPOINT(wFSXGL_SetI));
	if(g_pDeviceParam->wModeProtect==MODEPROTECT_2P) wDataI = s_wDataIMax2;
	else wDataI = s_wDataIMax;
	ProtectIDMT(PROTECT_FSXGL,SETPOINT(wFSXGL_IDMT),SETPOINT(wFSXGL_SetK),wSetI,wDataI);
}


//-----------------------------------------------------------------------------
//�����:
void CMyProtectItemHJS::Run(void)
{
	WORD wSetI = IPtoRun(SETPOINT(wHJS_SetI));
	if(g_breaker.m_wCountAfterClosed>0 || m_wTime>0)
	{
		ProtectXGE(PROTECT_HJS,s_wDataIMax,wSetI,SETPOINT(wHJS_SetT),FALSE);
	}
}


//-----------------------------------------------------------------------------
//������:
void CMyProtectItemGFH::Run(void)
{
	WORD wSetI = IPtoRun(SETPOINT(wGFH_SetI));
	ProtectXGE(PROTECT_GFH,s_wDataIMax,wSetI,SETPOINT(wGFH_SetT),FALSE);
}


//-----------------------------------------------------------------------------
//�������:
void CMyProtectItemFXDL::Run(void)
{
	WORD wSetI = IPtoRun(SETPOINT(wFXDL_SetI));
	ProtectXGE(PROTECT_FXDL,g_data3I2.m_nData,wSetI,SETPOINT(wFXDL_SetT),FALSE);
}


//-----------------------------------------------------------------------------
//�������:
void CMyProtectItemLXDL::Run(void)
{
	WORD wSetI0 = I0toRun(SETPOINT(wLXDL_SetI));
	ProtectXGE(PROTECT_LXDL,g_data3I0.m_nData,wSetI0,SETPOINT(wLXDL_SetT),FALSE);
}


//-----------------------------------------------------------------------------
//����ӵ�ѡ��:
void CMyProtectItemJDSX::Run(void)
{
	short nU_R;
	short nU_X;
	short nI_R;
	short nI_X;
	WORD wData3I0;
	WORD wData3U0;
	if(SETPOINT(wJDSX_TogTHD5)==PROTECTTOG_ON)
	{
#ifndef DFT_3I0
#error There must define DFT_3I0
#endif
		g_measure.CalculateDFTn(DFT_3I0,5,&nI_R,&nI_X);

#ifndef DFT_3U0
		short nUa_R,nUa_X;
		short nUb_R,nUb_X;
		short nUc_R,nUc_X;
		g_measure.CalculateDFTn(DFT_Ua,5,&nUa_R,&nUa_X);
		g_measure.CalculateDFTn(DFT_Ub,5,&nUb_R,&nUb_X);
		g_measure.CalculateDFTn(DFT_Uc,5,&nUc_R,&nUc_X);
		nU_R = nUa_R + nUb_R + nUc_R;
		nU_X = nUa_X + nUb_X + nUc_X;
#else
		g_measure.CalculateDFTn(DFT_3U0,5,&nU_R,&nU_X);
#endif
		wData3I0 = GetSqrtX(nI_R,nI_X);
		wData3U0 = GetSqrtX(nU_R,nU_X);
		if(wData3I0==0)
		{
			nI_R = 0;
			nI_X = 0;
		}
		if(wData3U0==0)
		{
			nU_R = 0;
			nU_X = 0;
		}
	}
	else
	{
		nI_R = g_data3I0.m_nR;
		nI_X = g_data3I0.m_nX;
		nU_R = g_data3U0.m_nR;
		nU_X = g_data3U0.m_nX;
		wData3I0 = g_data3I0.m_nData;
		wData3U0 = g_data3U0.m_nData;
	}
	long lVQ = (long)nU_X*(long)nI_R - (long)nU_R*(long)nI_X;
	BOOL bLock = FALSE;
	WORD wSetU0 = U0toRun(SETPOINT(wJDSX_SetU));
	WORD wSetI0 = I0toRun(SETPOINT(wJDSX_SetI));
	if(lVQ<0||wData3U0<=wSetU0) bLock = TRUE;
	ProtectXGE(PROTECT_JDSX,wData3I0,wSetI0,500,bLock);
}


//-----------------------------------------------------------------------------
//����ѹ:
void CMyProtectItemGDY::Run(void)
{
	BOOL bLock = FALSE;
	WORD wSetU = UlltoRun(SETPOINT(wGDY_SetU));
	if(g_breaker.GetStatus()==BOSTATUS_OPENED) bLock = TRUE;
	ProtectXGE(PROTECT_GDY,s_wDataUllMax,wSetU,SETPOINT(wGDY_SetT),bLock);
}


//-----------------------------------------------------------------------------
//�͵�ѹ:
void CMyProtectItemDDY::Run(void)
{
	BOOL bLock = FALSE;
	WORD wSetU = UlltoRun(SETPOINT(wDDY_SetU));
	if(g_breaker.GetStatus()==BOSTATUS_OPENED||g_app.IsPTBreak()) bLock = TRUE;
	ProtectXLE(PROTECT_DDY,s_wDataUllMin,wSetU,SETPOINT(wDDY_SetT),bLock);
}


//-----------------------------------------------------------------------------
//ʧѹ:
void CMyProtectItemSY::Run(void)
{
	BOOL bLock = FALSE;
	WORD wSetU = UlltoRun(SETPOINT(wSY_SetU));
	if(g_breaker.GetStatus()==BOSTATUS_OPENED||s_wDataIMax) bLock = TRUE;
	ProtectXLE(PROTECT_SY,s_wDataUllMax,wSetU,SETPOINT(wSY_SetT),bLock);
}


//-----------------------------------------------------------------------------
//�����ѹ:
void CMyProtectItemFXDY::Run(void)
{
	BOOL bLock = FALSE;
	WORD wSetU = UlltoRun(SETPOINT(wFXDY_SetU));
	if(g_breaker.GetStatus()==BOSTATUS_OPENED||g_app.IsPTBreak()) bLock = TRUE;
	ProtectXGE(PROTECT_FXDY,g_data3U2.m_nData,wSetU,SETPOINT(wFXDY_SetT),bLock);
}


//-----------------------------------------------------------------------------
//�����ѹ:
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
//���ϵ�ѹ����:
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
//���ܼ���:
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
//��ѹ����:
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
//�غ�բ
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
				short nmaxUx = GetMax(g_dataUxab.m_nData,g_dataUxbc.m_nData,g_dataUxca.m_nData);
				short nmaxU = GetMax(g_dataUab.m_nData,g_dataUbc.m_nData,g_dataUca.m_nData);
				if(nmaxUx<563||nmaxU<563) g_protect.SetProtectAct(PROTECT_CHZ,0xffff,0x5555);	//FixTo:563(=30V);
			}
			else if(SETPOINT(wCHZ_TogTQ)==PROTECTTOG_ON)
			{
				WORD wUab2 = g_dataUab.GetValueSecondaryFix();
				WORD wUxab2 = g_dataUxab.GetValueSecondaryFix();
				WORD wUbc2 = g_dataUbc.GetValueSecondaryFix();
				WORD wUxbc2 = g_dataUxbc.GetValueSecondaryFix();
				WORD wUca2 = g_dataUca.GetValueSecondaryFix();
				WORD wUxca2 = g_dataUxca.GetValueSecondaryFix();
				WORD wF = (WORD)g_dataF.m_nData;
				WORD wFx = (WORD)g_dataFx.m_nData;
				WORD wDiffF = (wF>wFx)?(wF-wFx):(wFx-wF);
				WORD wDiffUab = (wUab2>wUxab2)?(wUab2-wUxab2):(wUxab2-wUab2);
				WORD wDiffUbc = (wUbc2>wUxbc2)?(wUbc2-wUxbc2):(wUxbc2-wUbc2);
				WORD wDiffUca = (wUca2>wUxca2)?(wUca2-wUxca2):(wUxca2-wUca2);
				WORD wDiffU = GetMax(wDiffUab,wDiffUbc,wDiffUca);
				if(wDiffF<50 && wDiffU<1000 && g_dataUxab.m_nData>1313
					 && g_dataUxbc.m_nData>1313
					 && g_dataUxca.m_nData>1313)							//FixTo:1313(=70V);
				{
					long lVPab = GetVP(&g_dataUab,&g_dataUxab);
					long lVQab = GetVQ(&g_dataUab,&g_dataUxab);
					long lVPbc = GetVP(&g_dataUbc,&g_dataUxbc);
					long lVQbc = GetVQ(&g_dataUbc,&g_dataUxbc);
					long lVPca = GetVP(&g_dataUca,&g_dataUxca);
					long lVQca = GetVQ(&g_dataUca,&g_dataUxca);
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
					lVPca /= 3000;
					lVQca /= 3000;
					lVQca = GetSqrtX((short)lVPca,(short)lVQca);
					lVPca *= 10000L;
					lVPca /= lVQca;
					if(lVPab>=(long)c_wTableCosA[SETPOINT(wCHZ_SetA)]
						 && lVPbc>=(long)c_wTableCosA[SETPOINT(wCHZ_SetA)]
						 &&lVPca>=(long)c_wTableCosA[SETPOINT(wCHZ_SetA)])
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
//����Ͷ:
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
	short nminUx = GetMin(g_dataUxab.m_nData,g_dataUxbc.m_nData,g_dataUxca.m_nData);
	if(m_wLine2HavePowerFlag==0xaaaa) return TRUE;
	if(nminUx>1313) return TRUE;								//FixTo:1313(=70V);
	return FALSE;
}

BOOL CMyProtectItemBZT::IsChargeAllow(void)
{
	if(s_wDataUllMin>1313 && m_wLine1LostPowerFlag!=0xaaaa) return TRUE;	//FixTo:1313(=70V);
	return FALSE;
}


//-----------------------------------------------------------------------------
//����:
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
//�湦��:
void CMyProtectItemNGL::Run(void)
{
	DWORD dwScale = ((DWORD)g_pDeviceParam->wScale2IP*(DWORD)g_pDeviceParam->wScale2Uln+5000)/10000;
	WORD wScale = (WORD)((9000000L + dwScale/2)/dwScale);		// 3000*3000/(173.2*100)

	long lPa = GetVP(&g_dataUa,&g_dataIA);
	long lPb = GetVP(&g_dataUb,&g_dataIB);
	long lPc = GetVP(&g_dataUc,&g_dataIC);
	long lNGL_SetP = -((long)SETPOINT(wNGL_SetP)*wScale+5)/10;
	WORD wNGL = (WORD)((-(lPa+lPb+lPc)+wScale/2)/wScale);
	if(lPa+lPb+lPc<lNGL_SetP)
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
//����ʱ�����:
void CMyProtectItemQDSJGC::Run(void)
{
	WORD wSetI = IPtoRun(SETPOINT(wMotor_SetI));
	if(s_wMotorStartTime==0||s_wMotorStartTime>3) m_wTime = 0;
	else ProtectXGE(PROTECT_QDSJGC,s_wDataIMax,(WORD)(wSetI*6/5),3,FALSE);
}


//-----------------------------------------------------------------------------
//��ʱ��Ix����:
void CMyProtectItemIXDSX::Run(void)
{
	WORD wSetIx = IXtoRun(SETPOINT(wIXDSX_SetI));
	ProtectXGE(PROTECT_IXDSX,g_dataIx.m_nData,wSetIx,SETPOINT(wIXDSX_SetT),FALSE);
}


//-----------------------------------------------------------------------------
//��ʱ��Ix����:
void CMyProtectItemIXFSX::Run(void)
{
	WORD wSetIx = IXtoRun(SETPOINT(wIXFSX_SetI));
	ProtectIDMT(PROTECT_IXFSX,SETPOINT(wIXFSX_IDMT),SETPOINT(wIXFSX_SetK),wSetIx,g_dataIx.m_nData);
}


//-----------------------------------------------------------------------------
void CMyProtectDMRX01P::OnInit(void)
{
	CMyProtect::OnInit();
	g_pDeviceSetpoint = (DEVICESETPOINT_DMRX01*)g_protect.GetSetpointArea();
	g_pDeviceSetpointConfig = (DEVICESETPOINT_DMRX01CONFIG*)&g_deviceSetpoint.wSetpointConfig[0];
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
	m_piJDSX.OnInit();
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

void CMyProtectDMRX01P::OnInitSetpoint(WORD* pSetpoint)
{
	*(DEVICESETPOINT_DMRX01*)pSetpoint = c_setpointDMRX01;
}

void CMyProtectDMRX01P::iiiOnProtectActAlarmed(WORD wProtectIndex)
{
	CMyProtect::iiiOnProtectActAlarmed(wProtectIndex);
}

void CMyProtectDMRX01P::iiiOnProtectActTripped(WORD wProtectIndex)
{
	CMyProtect::iiiOnProtectActTripped(wProtectIndex);
	if(wProtectIndex==PROTECT_SD) m_piCHZ.SetAllowFlag();
	if(wProtectIndex==PROTECT_XSSD) m_piCHZ.SetAllowFlag();
	if(wProtectIndex==PROTECT_DSXGL) m_piCHZ.SetAllowFlag();
}

void CMyProtectDMRX01P::iiiRun(void)
{
	CMyProtect::iiiRun();
	g_pDeviceSetpoint = (DEVICESETPOINT_DMRX01*)g_protect.GetSetpointArea();
	g_pDeviceSetpointConfig = (DEVICESETPOINT_DMRX01CONFIG*)&g_deviceSetpoint.wSetpointConfig[0];
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
		if(g_protect.m_wProtectRun[PROTECT_JDSX]==PROTECTTOG_ON) m_piJDSX.Run();
		else m_piJDSX.OnInit();
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

WORD CMyProtectDMRX01P::GetProtectPickupInfo(WORD wProtectIndex)
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
	case PROTECT_JDSX: return m_piJDSX.GetProtectPickupInfo();
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

void CMyProtectDMRX01P::OnUpdateDevice(WORD* pData)
{
	CMyProtect::OnUpdateDevice(pData);
	DEVICESETPOINT_DMRX01CONFIG* pDeviceSetpointDMRX01Config = (DEVICESETPOINT_DMRX01CONFIG*)&g_deviceSetpoint.wSetpointConfig[0];
	DEVICESETPOINT_DMRX01* pDeviceSetpointDMRX01_1 = (DEVICESETPOINT_DMRX01*)&g_deviceSetpoint.wSetpointArea1[0];
	DEVICESETPOINT_DMRX01* pDeviceSetpointDMRX01_2 = (DEVICESETPOINT_DMRX01*)&g_deviceSetpoint.wSetpointArea2[0];
	DEVICESETPOINT_DMRX01* pDeviceSetpointDMRX01_3 = (DEVICESETPOINT_DMRX01*)&g_deviceSetpoint.wSetpointArea3[0];
	if(pDeviceSetpointDMRX01Config->bConfigMotor!=TRUE)
	{
		pDeviceSetpointDMRX01_1->wSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_2->wSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_3->wSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_1->wXSSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_2->wXSSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_3->wXSSD_TogAD = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_1->wDSXGL_TogAE = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_2->wDSXGL_TogAE = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_3->wDSXGL_TogAE = PROTECTTOG_OFF;
	}
	if(pDeviceSetpointDMRX01Config->bConfigFX!=TRUE)
	{
		pDeviceSetpointDMRX01_1->wSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_2->wSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_3->wSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_1->wXSSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_2->wXSSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_3->wXSSD_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_1->wDSXGL_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_2->wDSXGL_TogFX = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_3->wDSXGL_TogFX = PROTECTTOG_OFF;
	}
	if(pDeviceSetpointDMRX01Config->bConfigDY!=TRUE)
	{
		pDeviceSetpointDMRX01_1->wSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_2->wSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_3->wSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_1->wXSSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_2->wXSSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_3->wXSSD_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_1->wDSXGL_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_2->wDSXGL_TogDY = PROTECTTOG_OFF;
		pDeviceSetpointDMRX01_3->wDSXGL_TogDY = PROTECTTOG_OFF;
	}
}

WORD CMyProtectDMRX01P::GetMotorStartTime(void)
{
	return s_wMotorStartTime;
}
