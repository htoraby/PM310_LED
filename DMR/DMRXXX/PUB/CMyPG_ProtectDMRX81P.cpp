#include <Main.h>


//-----------------------------------------------------------------------------
void CMyPG_ProtectDMRX81P::OutProtectSetU(WORD* pSetU)
{
	OutProtectSetX(MULTITEXT("电压定值:","VOLTAGE:"),"V",pSetU);
}

void CMyPG_ProtectDMRX81P::OutProtectSetT(WORD* pSetT)
{
	OutProtectSetX(MULTITEXT("时间定值:","TIME DELAY:"),"s",pSetT);
}

void CMyPG_ProtectDMRX81P::iiiOnRefreshPage(WORD* pDeviceSetpoint)
{
	DEVICESETPOINT_DMRX81P* pDeviceSetpointDMRX81P = (DEVICESETPOINT_DMRX81P*)pDeviceSetpoint;
	//【1#PT过电压】
	if(SETPOINTCFG(PROTECT_GDY1))
	{
		OutProtectName(PROTECT_GDY1);
		OutProtectSetU(&pDeviceSetpointDMRX81P->wGDY1_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX81P->wGDY1_SetT);
	}
	//【1#PT低电压】
	if(SETPOINTCFG(PROTECT_DDY1))
	{
		OutProtectName(PROTECT_DDY1);
		OutProtectSetU(&pDeviceSetpointDMRX81P->wDDY1_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX81P->wDDY1_SetT);
	}
	//【1#PT负序电压】
	if(SETPOINTCFG(PROTECT_FXDY1))
	{
		OutProtectName(PROTECT_FXDY1);
		OutProtectSetU(&pDeviceSetpointDMRX81P->wFXDY1_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX81P->wFXDY1_SetT);
	}
	//【1#PT零序电压】
	if(SETPOINTCFG(PROTECT_LXDY1))
	{
		OutProtectName(PROTECT_LXDY1);
		OutProtectSetU(&pDeviceSetpointDMRX81P->wLXDY1_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX81P->wLXDY1_SetT);
	}
	//【2#PT过电压】
	if(SETPOINTCFG(PROTECT_GDY2))
	{
		OutProtectName(PROTECT_GDY2);
		OutProtectSetU(&pDeviceSetpointDMRX81P->wGDY2_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX81P->wGDY2_SetT);
	}
	//【2#PT低电压】
	if(SETPOINTCFG(PROTECT_DDY2))
	{
		OutProtectName(PROTECT_DDY2);
		OutProtectSetU(&pDeviceSetpointDMRX81P->wDDY2_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX81P->wDDY2_SetT);
	}
	//【2#PT负序电压】
	if(SETPOINTCFG(PROTECT_FXDY2))
	{
		OutProtectName(PROTECT_FXDY2);
		OutProtectSetU(&pDeviceSetpointDMRX81P->wFXDY2_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX81P->wFXDY2_SetT);
	}
	//【2#PT零序电压】
	if(SETPOINTCFG(PROTECT_LXDY2))
	{
		OutProtectName(PROTECT_LXDY2);
		OutProtectSetU(&pDeviceSetpointDMRX81P->wLXDY2_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX81P->wLXDY2_SetT);
	}
}


//-----------------------------------------------------------------------------
static void SetDataSetT(void)
{
	g_edit.SetEditDataMetricsReal(0,60000,0x52,1,1);
}

static void SetDataSetUll(void)
{
	g_edit.SetEditDataMetricsReal(0,5196,0x52,g_pDeviceParam->wScale2Uln,3000);
}

static void SetDataSet3U0(void)
{
	g_edit.SetEditDataMetricsReal(0,3000,0x52,g_pDeviceParam->wScale23U0,3000);
}


//-----------------------------------------------------------------------------
void CMyPG_ProtectDMRX81P::GetEditMetrics(WORD* pData,WORD* pDeviceSetpoint)
{
	DEVICESETPOINT_DMRX81P* pDeviceSetpointDMRX81P = (DEVICESETPOINT_DMRX81P*)pDeviceSetpoint;
	if(pData==&pDeviceSetpointDMRX81P->wGDY1_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX81P->wGDY1_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX81P->wDDY1_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX81P->wDDY1_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX81P->wFXDY1_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX81P->wFXDY1_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX81P->wLXDY1_SetU) SetDataSet3U0();
	if(pData==&pDeviceSetpointDMRX81P->wLXDY1_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX81P->wGDY2_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX81P->wGDY2_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX81P->wDDY2_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX81P->wDDY2_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX81P->wFXDY2_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX81P->wFXDY2_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX81P->wLXDY2_SetU) SetDataSet3U0();
	if(pData==&pDeviceSetpointDMRX81P->wLXDY2_SetT) SetDataSetT();
}

