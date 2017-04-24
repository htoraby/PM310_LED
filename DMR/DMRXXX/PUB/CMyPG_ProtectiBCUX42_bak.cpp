#include <Main.h>

//-----------------------------------------------------------------------------
void CMyPG_ProtectiBCUX42::OutProtectSetI(WORD* pSetI)
{
	OutProtectSetX(MULTITEXT("电流定值:","CURRENT:"),"A",pSetI);
}

void CMyPG_ProtectiBCUX42::OutProtectSetU(WORD* pSetU)
{
	OutProtectSetX(MULTITEXT("电压定值:","VOLTAGE:"),"V",pSetU);
}

void CMyPG_ProtectiBCUX42::OutProtectSetT(WORD* pSetT)
{
	OutProtectSetX(MULTITEXT("时间定值:","TIME DELAY:"),"s",pSetT);
}

void CMyPG_ProtectiBCUX42::OutProtectSetF(WORD* pSetF)
{
	OutProtectSetX(MULTITEXT("频率定值:","FREQUENCY:"),"Hz",pSetF);
}

void CMyPG_ProtectiBCUX42::iiiOnRefreshPage(WORD* pDeviceSetpoint)
{
	DEVICESETPOINT_DMRX01* pDeviceSetpointDMRX01 = (DEVICESETPOINT_DMRX01*)pDeviceSetpoint;
	if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
	{
		OutProtectText(MULTITEXT("电动机参数","MOTOR PARAMETERS"));
		OutProtectSetX(MULTITEXT("额定电流:","RATED CURRENT:"),"A",&pDeviceSetpointDMRX01->wMotor_SetI);
		OutProtectSetX(MULTITEXT("启动时间:","STARTING TIME:"),"s",&pDeviceSetpointDMRX01->wMotor_SetT);
	}
	//【电流速断】
	if(SETPOINTCFG(PROTECT_SD))
	{
		OutProtectName(PROTECT_SD);
		OutProtectSetI(&pDeviceSetpointDMRX01->wSD_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wSD_SetT);
		if(g_pDeviceSetpointConfig->bConfigDY==TRUE)
		{
			OutProtectSetU(&pDeviceSetpointDMRX01->wSD_SetU);
			m_wOffset = 3; OutProtectTog(MULTITEXT("低压闭锁:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointDMRX01->wSD_TogDY);
		}
		if(g_pDeviceSetpointConfig->bConfigFX==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("方向闭锁:","DIRECTIONAL BLOCKING:"),&pDeviceSetpointDMRX01->wSD_TogFX);
		}
		if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("定值加倍:","AUTO DOUBLE:"),&pDeviceSetpointDMRX01->wSD_TogAD);
		}
	}
	//【限时电流速断】
	if(SETPOINTCFG(PROTECT_XSSD))
	{
		OutProtectName(PROTECT_XSSD);
		OutProtectSetI(&pDeviceSetpointDMRX01->wXSSD_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wXSSD_SetT);
		if(g_pDeviceSetpointConfig->bConfigDY==TRUE)
		{
			OutProtectSetU(&pDeviceSetpointDMRX01->wXSSD_SetU);
			m_wOffset = 3; OutProtectTog(MULTITEXT("低压闭锁:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointDMRX01->wXSSD_TogDY);
		}
		if(g_pDeviceSetpointConfig->bConfigFX==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("方向闭锁:","DIRECTIONAL BLOCKING:"),&pDeviceSetpointDMRX01->wXSSD_TogFX);
		}
		if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("定值加倍:","AUTO DOUBLE:"),&pDeviceSetpointDMRX01->wXSSD_TogAD);
		}
	}
	//【定时限过流】
	if(SETPOINTCFG(PROTECT_DSXGL))
	{
		OutProtectName(PROTECT_DSXGL);
		OutProtectSetI(&pDeviceSetpointDMRX01->wDSXGL_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wDSXGL_SetT);
		if(g_pDeviceSetpointConfig->bConfigDY==TRUE)
		{
			OutProtectSetU(&pDeviceSetpointDMRX01->wDSXGL_SetU);
			m_wOffset = 3; OutProtectTog(MULTITEXT("低压闭锁:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointDMRX01->wDSXGL_TogDY);
		}
		if(g_pDeviceSetpointConfig->bConfigFX==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("方向闭锁:","DIRECTIONAL BLOCKING:"),&pDeviceSetpointDMRX01->wDSXGL_TogFX);
		}
		if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("保护退出:","AUTO EXIT:"),&pDeviceSetpointDMRX01->wDSXGL_TogAE);
		}
	}
	//【反时限过流】
	if(SETPOINTCFG(PROTECT_FSXGL))
	{
		OutProtectName(PROTECT_FSXGL);
		OutProtectSetI(&pDeviceSetpointDMRX01->wFSXGL_SetI);
		OutProtectSetX(MULTITEXT("时间系数:","TIME COEFFICIENT:"),"",&pDeviceSetpointDMRX01->wFSXGL_SetK);
// 		g_lcd.m_wAutoPosX = PGP_FONTWIDTH;
		m_wOffset = 2; OutProtectTog(MULTITEXT("特性曲线:","IDMT CURVE:"),&pDeviceSetpointDMRX01->wFSXGL_IDMT);
	}
	//【后加速】
	if(SETPOINTCFG(PROTECT_HJS))
	{
		OutProtectName(PROTECT_HJS);
		OutProtectSetI(&pDeviceSetpointDMRX01->wHJS_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wHJS_SetT);
	}
	//【过负荷】
	if(SETPOINTCFG(PROTECT_GFH))
	{
		OutProtectName(PROTECT_GFH);
		OutProtectSetI(&pDeviceSetpointDMRX01->wGFH_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wGFH_SetT);
	}
	//【负序电流】
	if(SETPOINTCFG(PROTECT_FXDL))
	{
		OutProtectName(PROTECT_FXDL);
		OutProtectSetI(&pDeviceSetpointDMRX01->wFXDL_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wFXDL_SetT);
	}
	//【零序电流】
	if(SETPOINTCFG(PROTECT_LXDL))
	{
		OutProtectName(PROTECT_LXDL);
		OutProtectSetI(&pDeviceSetpointDMRX01->wLXDL_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wLXDL_SetT);
	}
	//【单相接地选线】
	if(SETPOINTCFG(PROTECT_JDSX))
	{
		OutProtectName(PROTECT_JDSX);
		OutProtectSetI(&pDeviceSetpointDMRX01->wJDSX_SetI);
		OutProtectSetU(&pDeviceSetpointDMRX01->wJDSX_SetU);
		m_wOffset = 3; OutProtectTog(MULTITEXT("五次谐波:","FIFTH HARMONIC:"),&pDeviceSetpointDMRX01->wJDSX_TogTHD5);
	}
	//【过电压】
	if(SETPOINTCFG(PROTECT_GDY))
	{
		OutProtectName(PROTECT_GDY);
		OutProtectSetU(&pDeviceSetpointDMRX01->wGDY_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wGDY_SetT);
	}
	//【低电压】
	if(SETPOINTCFG(PROTECT_DDY))
	{
		OutProtectName(PROTECT_DDY);
		OutProtectSetU(&pDeviceSetpointDMRX01->wDDY_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wDDY_SetT);
	}
	//【失压】
	if(SETPOINTCFG(PROTECT_SY))
	{
		OutProtectName(PROTECT_SY);
		OutProtectSetU(&pDeviceSetpointDMRX01->wSY_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wSY_SetT);
	}
	//【负序电压】
	if(SETPOINTCFG(PROTECT_FXDY))
	{
		OutProtectName(PROTECT_FXDY);
		OutProtectSetU(&pDeviceSetpointDMRX01->wFXDY_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wFXDY_SetT);
	}
	//【零序电压】
	if(SETPOINTCFG(PROTECT_LXDY))
	{
		OutProtectName(PROTECT_LXDY);
		OutProtectSetU(&pDeviceSetpointDMRX01->wLXDY_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wLXDY_SetT);
	}
	//【复合电压过流】
	if(SETPOINTCFG(PROTECT_FHDYGL))
	{
		OutProtectName(PROTECT_FHDYGL);
		OutProtectSetI(&pDeviceSetpointDMRX01->wFHDYGL_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wFHDYGL_SetT);
		OutProtectSetU(&pDeviceSetpointDMRX01->wFHDYGL_SetU);
		OutProtectSetX(MULTITEXT("负序电压:","NEGATIVE VOLTAGE:"),"V",&pDeviceSetpointDMRX01->wFHDYGL_SetUFX);
		m_wOffset = 3; OutProtectTog(MULTITEXT("低压闭锁:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointDMRX01->wFHDYGL_TogDY);
		m_wOffset = 3; OutProtectTog(MULTITEXT("负序闭锁:","NEGATIVE BLOCKING:"),&pDeviceSetpointDMRX01->wFHDYGL_TogFXDY);
	}
	//【低周减载】
	if(SETPOINTCFG(PROTECT_DZJZ))
	{
		OutProtectName(PROTECT_DZJZ);
		OutProtectSetF(&pDeviceSetpointDMRX01->wDZJZ_SetF);
		OutProtectSetT(&pDeviceSetpointDMRX01->wDZJZ_SetT);
		OutProtectSetU(&pDeviceSetpointDMRX01->wDZJZ_SetU);
		OutProtectSetX(MULTITEXT("滑差定值:","DF/DT:"),"Hs",&pDeviceSetpointDMRX01->wDZJZ_SetDFDT);
		m_wOffset = 3; OutProtectTog(MULTITEXT("滑差闭锁:","DF/DT BLOCKING:"),&pDeviceSetpointDMRX01->wDZJZ_TogDFDT);
		m_wOffset = 3; OutProtectTog(MULTITEXT("低压闭锁:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointDMRX01->wDZJZ_TogDY);
		m_wOffset = 3; OutProtectTog(MULTITEXT("欠流闭锁:","UNDERCURRENT BLOCKING:"),&pDeviceSetpointDMRX01->wDZJZ_TogDL);
	}
	//【低压解列】
	if(SETPOINTCFG(PROTECT_DYJL))
	{
		OutProtectName(PROTECT_DYJL);
		OutProtectSetU(&pDeviceSetpointDMRX01->wDYJL_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wDYJL_SetT);
		OutProtectSetX(MULTITEXT("滑差定值:","DV/DT:"),"Vs",&pDeviceSetpointDMRX01->wDYJL_SetDVDT);
		m_wOffset = 3; OutProtectTog(MULTITEXT("滑差闭锁:","DV/DT BLOCKING:"),&pDeviceSetpointDMRX01->wDYJL_TogDVDT);
		m_wOffset = 3; OutProtectTog(MULTITEXT("欠流闭锁:","UNDERCURRENT BLOCKING:"),&pDeviceSetpointDMRX01->wDYJL_TogDL);
	}
	//【重合闸】
	if(SETPOINTCFG(PROTECT_CHZ))
	{
		OutProtectName(PROTECT_CHZ);
		OutProtectSetT(&pDeviceSetpointDMRX01->wCHZ_SetT);
		g_lcd.m_wAutoPosX = PGP_FONTWIDTH*4;
#ifdef DFT_Uxab
		m_wOffset = 4; OutProtectSetX(MULTITEXT("同期角度:","SYNCHRONISM ANGLE:"),"^",&pDeviceSetpointDMRX01->wCHZ_SetA);
		m_wOffset = 3; OutProtectTog(MULTITEXT("检 无 压:","VOLTAGE CHECK:"),&pDeviceSetpointDMRX01->wCHZ_TogWY);
		m_wOffset = 3; OutProtectTog(MULTITEXT("检 同 期:","SYNCHRONISM:"),&pDeviceSetpointDMRX01->wCHZ_TogTQ);
#endif
	}
	//【备自投】
	if(SETPOINTCFG(PROTECT_BZT))
	{
		OutProtectName(PROTECT_BZT);
		OutProtectSetU(&pDeviceSetpointDMRX01->wBZT_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wBZT_SetT);
	}
	//【过热】
	if(SETPOINTCFG(PROTECT_GR))
	{
		OutProtectName(PROTECT_GR);
		OutProtectSetI(&pDeviceSetpointDMRX01->wGR_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wGR_SetT);
		OutProtectSetX(MULTITEXT("负序系数:","NEGATIVE COEFFICIENT:"),"",&pDeviceSetpointDMRX01->wGR_SetK2);
	}
	//【逆功率】
	if(SETPOINTCFG(PROTECT_NGL))
	{
		OutProtectName(PROTECT_NGL);
		m_wOffset = 1; OutProtectSetX(MULTITEXT("功率定值:","ACTIVE POWER:"),"W",&pDeviceSetpointDMRX01->wNGL_SetP);
		OutProtectSetT(&pDeviceSetpointDMRX01->wNGL_SetT);
	}
	//【启动时间过长】
	if(SETPOINTCFG(PROTECT_QDSJGC))
	{
		OutProtectName(PROTECT_QDSJGC);
	}
	//【定时限Ix过流】
	if(SETPOINTCFG(PROTECT_IXDSX))
	{
		OutProtectName(PROTECT_IXDSX);
		OutProtectSetI(&pDeviceSetpointDMRX01->wIXDSX_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wIXDSX_SetT);
	}
	//【反时限Ix过流】
	if(SETPOINTCFG(PROTECT_IXFSX))
	{
		OutProtectName(PROTECT_IXFSX);
		OutProtectSetI(&pDeviceSetpointDMRX01->wIXFSX_SetI);
		OutProtectSetX(MULTITEXT("时间系数:","TIME COEFFICIENT:"),"",&pDeviceSetpointDMRX01->wIXFSX_SetK);
// 		g_lcd.m_wAutoPosX = PGP_FONTWIDTH;
		m_wOffset = 2; OutProtectTog(MULTITEXT("特性曲线:","IDMT CURVE:"),&pDeviceSetpointDMRX01->wIXFSX_IDMT);
	}
}


//-----------------------------------------------------------------------------
static void SetDataSetT(void)
{
	g_edit.SetEditDataMetricsReal(0,60000,0x52,1,1);
}

static void SetDataSetIP(void)
{
	g_edit.SetEditDataMetricsReal(0,3000,0x52,g_pDeviceParam->wScale2IP,3000);
}

static void SetDataSetUll(void)
{
	g_edit.SetEditDataMetricsReal(0,3000,0x52,g_pDeviceParam->wScale2Uln,3000);
}

static void SetDataSet3I0(void)
{
	g_edit.SetEditDataMetricsReal(0,3000,0x52,g_pDeviceParam->wScale23I0,3000);
}

static void SetDataSet3U0(void)
{
	g_edit.SetEditDataMetricsReal(0,3000,0x52,g_pDeviceParam->wScale23U0,3000);
}

static void SetDataSetIx(void)
{
	g_edit.SetEditDataMetricsReal(0,3000,0x52,g_pDeviceParam->wScale2Ix,3000);
}

static const char c_szIDMTType[4][5] = 
{
	"Extr","Very","Norm","Long"
};


//-----------------------------------------------------------------------------
void CMyPG_ProtectiBCUX42::GetEditMetrics(WORD* pData,WORD* pDeviceSetpoint)
{
	DEVICESETPOINT_DMRX01* pDeviceSetpointDMRX01 = (DEVICESETPOINT_DMRX01*)pDeviceSetpoint;
	if(pData==&g_pDeviceSetpointConfig->bConfigMotor) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceSetpointConfig->bConfigFX) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceSetpointConfig->bConfigDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wMotor_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointDMRX01->wMotor_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wSD_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointDMRX01->wSD_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wSD_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wSD_TogDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wSD_TogFX) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wSD_TogAD) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wXSSD_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointDMRX01->wXSSD_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wXSSD_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wXSSD_TogDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wXSSD_TogFX) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wXSSD_TogAD) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDSXGL_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointDMRX01->wDSXGL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wDSXGL_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wDSXGL_TogDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDSXGL_TogFX) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDSXGL_TogAE) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wFSXGL_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointDMRX01->wFSXGL_SetK) g_edit.SetEditDataMetricsReal(5,400,0x52,1,1);
	if(pData==&pDeviceSetpointDMRX01->wFSXGL_IDMT) g_edit.SetEditEnumMetricsMul(4,5,(char*)c_szIDMTType[0]);
	if(pData==&pDeviceSetpointDMRX01->wHJS_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointDMRX01->wHJS_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wGFH_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointDMRX01->wGFH_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wFXDL_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointDMRX01->wFXDL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wLXDL_SetI) SetDataSet3I0();
	if(pData==&pDeviceSetpointDMRX01->wLXDL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wJDSX_SetI) SetDataSet3I0();
	if(pData==&pDeviceSetpointDMRX01->wJDSX_SetU) SetDataSet3U0();
	if(pData==&pDeviceSetpointDMRX01->wJDSX_TogTHD5) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wGDY_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wGDY_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wDDY_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wDDY_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wSY_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wSY_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wFXDY_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wFXDY_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wLXDY_SetU) SetDataSet3U0();
	if(pData==&pDeviceSetpointDMRX01->wLXDY_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wFHDYGL_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointDMRX01->wFHDYGL_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wFHDYGL_SetUFX) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wFHDYGL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wFHDYGL_TogDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wFHDYGL_TogFXDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_SetF) g_edit.SetEditDataMetricsReal(4000,5000,0x52,1,1);
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_SetDFDT) g_edit.SetEditDataMetricsReal(0,2000,0x52,1,1);
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_TogDFDT) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_TogDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_TogDL) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDYJL_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wDYJL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wDYJL_SetDVDT) g_edit.SetEditDataMetricsReal(0,30000,0x52,1,1);
	if(pData==&pDeviceSetpointDMRX01->wDYJL_TogDVDT) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDYJL_TogDL) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wCHZ_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wCHZ_SetA) g_edit.SetEditDataMetricsReal(0,90,0x20,1,1);
	if(pData==&pDeviceSetpointDMRX01->wCHZ_TogWY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wCHZ_TogTQ) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wBZT_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wBZT_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wGR_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointDMRX01->wGR_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wGR_SetK2) g_edit.SetEditDataMetricsReal(0,1000,0x52,1,1);
	if(pData==&pDeviceSetpointDMRX01->wNGL_SetP) g_edit.SetEditDataMetricsReal(0,1000,0x41,1,1);
	if(pData==&pDeviceSetpointDMRX01->wNGL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wIXDSX_SetI) SetDataSetIx();
	if(pData==&pDeviceSetpointDMRX01->wIXDSX_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wIXFSX_SetI) SetDataSetIx();
	if(pData==&pDeviceSetpointDMRX01->wIXFSX_SetK) g_edit.SetEditDataMetricsReal(5,400,0x52,1,1);
	if(pData==&pDeviceSetpointDMRX01->wIXFSX_IDMT) g_edit.SetEditEnumMetricsMul(4,5,(char*)c_szIDMTType[0]);
}

