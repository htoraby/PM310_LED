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
	DEVICESETPOINT_iBCUX42* pDeviceSetpointiBCUX42 = (DEVICESETPOINT_iBCUX42*)pDeviceSetpoint;
	if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
	{
		OutProtectText(MULTITEXT("电动机参数","MOTOR PARAMETERS"));
		OutProtectSetX(MULTITEXT("额定电流:","RATED CURRENT:"),"A",&pDeviceSetpointiBCUX42->wMotor_SetI);
		OutProtectSetX(MULTITEXT("启动时间:","STARTING TIME:"),"s",&pDeviceSetpointiBCUX42->wMotor_SetT);
	}
	//【电流速断】
	if(SETPOINTCFG(PROTECT_SD))
	{
		OutProtectName(PROTECT_SD);
		OutProtectSetI(&pDeviceSetpointiBCUX42->wSD_SetI);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wSD_SetT);
		if(g_pDeviceSetpointConfig->bConfigDY==TRUE)
		{
			OutProtectSetU(&pDeviceSetpointiBCUX42->wSD_SetU);
			m_wOffset = 3; OutProtectTog(MULTITEXT("低压闭锁:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointiBCUX42->wSD_TogDY);
		}
		if(g_pDeviceSetpointConfig->bConfigFX==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("方向闭锁:","DIRECTIONAL BLOCKING:"),&pDeviceSetpointiBCUX42->wSD_TogFX);
		}
		if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("定值加倍:","AUTO DOUBLE:"),&pDeviceSetpointiBCUX42->wSD_TogAD);
		}
	}
	//【限时电流速断】
	if(SETPOINTCFG(PROTECT_XSSD))
	{
		OutProtectName(PROTECT_XSSD);
		OutProtectSetI(&pDeviceSetpointiBCUX42->wXSSD_SetI);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wXSSD_SetT);
		if(g_pDeviceSetpointConfig->bConfigDY==TRUE)
		{
			OutProtectSetU(&pDeviceSetpointiBCUX42->wXSSD_SetU);
			m_wOffset = 3; OutProtectTog(MULTITEXT("低压闭锁:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointiBCUX42->wXSSD_TogDY);
		}
		if(g_pDeviceSetpointConfig->bConfigFX==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("方向闭锁:","DIRECTIONAL BLOCKING:"),&pDeviceSetpointiBCUX42->wXSSD_TogFX);
		}
		if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("定值加倍:","AUTO DOUBLE:"),&pDeviceSetpointiBCUX42->wXSSD_TogAD);
		}
	}
	//【定时限过流】
	if(SETPOINTCFG(PROTECT_DSXGL))
	{
		OutProtectName(PROTECT_DSXGL);
		OutProtectSetI(&pDeviceSetpointiBCUX42->wDSXGL_SetI);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wDSXGL_SetT);
		if(g_pDeviceSetpointConfig->bConfigDY==TRUE)
		{
			OutProtectSetU(&pDeviceSetpointiBCUX42->wDSXGL_SetU);
			m_wOffset = 3; OutProtectTog(MULTITEXT("低压闭锁:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointiBCUX42->wDSXGL_TogDY);
		}
		if(g_pDeviceSetpointConfig->bConfigFX==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("方向闭锁:","DIRECTIONAL BLOCKING:"),&pDeviceSetpointiBCUX42->wDSXGL_TogFX);
		}
		if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("保护退出:","AUTO EXIT:"),&pDeviceSetpointiBCUX42->wDSXGL_TogAE);
		}
	}
	//【反时限过流】
	if(SETPOINTCFG(PROTECT_FSXGL))
	{
		OutProtectName(PROTECT_FSXGL);
		OutProtectSetI(&pDeviceSetpointiBCUX42->wFSXGL_SetI);
		OutProtectSetX(MULTITEXT("时间系数:","TIME COEFFICIENT:"),"",&pDeviceSetpointiBCUX42->wFSXGL_SetK);
//		g_lcd.m_wAutoPosX = PGP_FONTWIDTH;
		m_wOffset = 2; OutProtectTog(MULTITEXT("特性曲线:","IDMT CURVE:"),&pDeviceSetpointiBCUX42->wFSXGL_IDMT);
	}
	//【后加速】
	if(SETPOINTCFG(PROTECT_HJS))
	{
		OutProtectName(PROTECT_HJS);
		OutProtectSetI(&pDeviceSetpointiBCUX42->wHJS_SetI);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wHJS_SetT);
	}
	//【过负荷】
	if(SETPOINTCFG(PROTECT_GFH))
	{
		OutProtectName(PROTECT_GFH);
		OutProtectSetI(&pDeviceSetpointiBCUX42->wGFH_SetI);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wGFH_SetT);
	}
	//【负序电流】
	if(SETPOINTCFG(PROTECT_FXDL))
	{
		OutProtectName(PROTECT_FXDL);
		OutProtectSetI(&pDeviceSetpointiBCUX42->wFXDL_SetI);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wFXDL_SetT);
	}
	//【零序电流】
	if(SETPOINTCFG(PROTECT_LXDL))
	{
		OutProtectName(PROTECT_LXDL);
		OutProtectSetI(&pDeviceSetpointiBCUX42->wLXDL_SetI);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wLXDL_SetT);
	}
// 	//【单相接地选线】
// 	if(SETPOINTCFG(PROTECT_JDSX))
// 	{
// 		OutProtectName(PROTECT_JDSX);
// 		OutProtectSetI(&pDeviceSetpointiBCUX42->wJDSX_SetI);
// 		OutProtectSetU(&pDeviceSetpointiBCUX42->wJDSX_SetU);
// 		m_wOffset = 3; OutProtectTog(MULTITEXT("五次谐波:","FIFTH HARMONIC:"),&pDeviceSetpointiBCUX42->wJDSX_TogTHD5);
// 	}
	//【过电压】
	if(SETPOINTCFG(PROTECT_GDY))
	{
		OutProtectName(PROTECT_GDY);
		OutProtectSetU(&pDeviceSetpointiBCUX42->wGDY_SetU);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wGDY_SetT);
	}
	//【低电压】
	if(SETPOINTCFG(PROTECT_DDY))
	{
		OutProtectName(PROTECT_DDY);
		OutProtectSetU(&pDeviceSetpointiBCUX42->wDDY_SetU);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wDDY_SetT);
	}
	//【失压】
	if(SETPOINTCFG(PROTECT_SY))
	{
		OutProtectName(PROTECT_SY);
		OutProtectSetU(&pDeviceSetpointiBCUX42->wSY_SetU);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wSY_SetT);
	}
	//【负序电压】
	if(SETPOINTCFG(PROTECT_FXDY))
	{
		OutProtectName(PROTECT_FXDY);
		OutProtectSetU(&pDeviceSetpointiBCUX42->wFXDY_SetU);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wFXDY_SetT);
	}
	//【零序电压】
	if(SETPOINTCFG(PROTECT_LXDY))
	{
		OutProtectName(PROTECT_LXDY);
		OutProtectSetU(&pDeviceSetpointiBCUX42->wLXDY_SetU);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wLXDY_SetT);
	}
	//【复合电压过流】
	if(SETPOINTCFG(PROTECT_FHDYGL))
	{
		OutProtectName(PROTECT_FHDYGL);
		OutProtectSetI(&pDeviceSetpointiBCUX42->wFHDYGL_SetI);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wFHDYGL_SetT);
		OutProtectSetU(&pDeviceSetpointiBCUX42->wFHDYGL_SetU);
		OutProtectSetX(MULTITEXT("负序电压:","NEGATIVE VOLTAGE:"),"V",&pDeviceSetpointiBCUX42->wFHDYGL_SetUFX);
		m_wOffset = 3; OutProtectTog(MULTITEXT("低压闭锁:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointiBCUX42->wFHDYGL_TogDY);
		m_wOffset = 3; OutProtectTog(MULTITEXT("负序闭锁:","NEGATIVE BLOCKING:"),&pDeviceSetpointiBCUX42->wFHDYGL_TogFXDY);
	}
	//【低周减载】
	if(SETPOINTCFG(PROTECT_DZJZ))
	{
		OutProtectName(PROTECT_DZJZ);
		OutProtectSetF(&pDeviceSetpointiBCUX42->wDZJZ_SetF);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wDZJZ_SetT);
		OutProtectSetU(&pDeviceSetpointiBCUX42->wDZJZ_SetU);
		OutProtectSetX(MULTITEXT("滑差定值:","DF/DT:"),"Hs",&pDeviceSetpointiBCUX42->wDZJZ_SetDFDT);
		m_wOffset = 3; OutProtectTog(MULTITEXT("滑差闭锁:","DF/DT BLOCKING:"),&pDeviceSetpointiBCUX42->wDZJZ_TogDFDT);
		m_wOffset = 3; OutProtectTog(MULTITEXT("低压闭锁:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointiBCUX42->wDZJZ_TogDY);
		m_wOffset = 3; OutProtectTog(MULTITEXT("欠流闭锁:","UNDERCURRENT BLOCKING:"),&pDeviceSetpointiBCUX42->wDZJZ_TogDL);
	}
	//【低压解列】
	if(SETPOINTCFG(PROTECT_DYJL))
	{
		OutProtectName(PROTECT_DYJL);
		OutProtectSetU(&pDeviceSetpointiBCUX42->wDYJL_SetU);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wDYJL_SetT);
		OutProtectSetX(MULTITEXT("滑差定值:","DV/DT:"),"Vs",&pDeviceSetpointiBCUX42->wDYJL_SetDVDT);
		m_wOffset = 3; OutProtectTog(MULTITEXT("滑差闭锁:","DV/DT BLOCKING:"),&pDeviceSetpointiBCUX42->wDYJL_TogDVDT);
		m_wOffset = 3; OutProtectTog(MULTITEXT("欠流闭锁:","UNDERCURRENT BLOCKING:"),&pDeviceSetpointiBCUX42->wDYJL_TogDL);
	}
	//【重合闸】
	if(SETPOINTCFG(PROTECT_CHZ))
	{
		OutProtectName(PROTECT_CHZ);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wCHZ_SetT);
// 		g_lcd.m_wAutoPosX = PGP_FONTWIDTH*4;
#ifdef DFT_Uxab
		m_wOffset = 4; OutProtectSetX(MULTITEXT("同期角度:","SYNCHRONISM ANGLE:"),"^",&pDeviceSetpointiBCUX42->wCHZ_SetA);
		m_wOffset = 3; OutProtectTog(MULTITEXT("检 无 压:","VOLTAGE CHECK:"),&pDeviceSetpointiBCUX42->wCHZ_TogWY);
		m_wOffset = 3; OutProtectTog(MULTITEXT("检 同 期:","SYNCHRONISM:"),&pDeviceSetpointiBCUX42->wCHZ_TogTQ);
#endif
	}
	//【备自投】
	if(SETPOINTCFG(PROTECT_BZT))
	{
		OutProtectName(PROTECT_BZT);
		OutProtectSetU(&pDeviceSetpointiBCUX42->wBZT_SetU);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wBZT_SetT);
	}
	//【过热】
	if(SETPOINTCFG(PROTECT_GR))
	{
		OutProtectName(PROTECT_GR);
		OutProtectSetI(&pDeviceSetpointiBCUX42->wGR_SetI);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wGR_SetT);
		OutProtectSetX(MULTITEXT("负序系数:","NEGATIVE COEFFICIENT:"),"",&pDeviceSetpointiBCUX42->wGR_SetK2);
	}
	//【逆功率】
	if(SETPOINTCFG(PROTECT_NGL))
	{
		OutProtectName(PROTECT_NGL);
		m_wOffset = 1; OutProtectSetX(MULTITEXT("功率定值:","ACTIVE POWER:"),"W",&pDeviceSetpointiBCUX42->wNGL_SetP);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wNGL_SetT);
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
		OutProtectSetI(&pDeviceSetpointiBCUX42->wIXDSX_SetI);
		OutProtectSetT(&pDeviceSetpointiBCUX42->wIXDSX_SetT);
	}
	//【反时限Ix过流】
	if(SETPOINTCFG(PROTECT_IXFSX))
	{
		OutProtectName(PROTECT_IXFSX);
		OutProtectSetI(&pDeviceSetpointiBCUX42->wIXFSX_SetI);
		OutProtectSetX(MULTITEXT("时间系数:","TIME COEFFICIENT:"),"",&pDeviceSetpointiBCUX42->wIXFSX_SetK);
// 		g_lcd.m_wAutoPosX = PGP_FONTWIDTH;
		m_wOffset = 2; OutProtectTog(MULTITEXT("特性曲线:","IDMT CURVE:"),&pDeviceSetpointiBCUX42->wIXFSX_IDMT);
	}
}


//-----------------------------------------------------------------------------
static void SetDataSetT(void)
{
	g_edit.SetEditDataMetricsReal(0,60000,0x52);
}

static void SetDataSetIP(void)
{
	g_edit.SetEditDataMetricsReal(0,g_pDeviceParam->wScale2IP,0x52);
}

static void SetDataSetUll(void)
{
	g_edit.SetEditDataMetricsReal(0,17320,0x52);
}

static void SetDataSet3I0(void)
{
	g_edit.SetEditDataMetricsReal(0,g_pDeviceParam->wScale23I0,0x52);
}

static void SetDataSet3U0(void)
{
#ifndef DFT_3U0
	g_edit.SetEditDataMetricsReal(0,17320,0x52);
#else
	g_edit.SetEditDataMetricsReal(0,g_pDeviceParam->wScale23U0,0x52);
#endif
}

static void SetDataSetIx(void)
{
	g_edit.SetEditDataMetricsReal(0,g_pDeviceParam->wScale2Ix,0x52);
}

static const char c_szIDMTType[4][5] = 
{
	"Extr","Very","Norm","Long"
};


//-----------------------------------------------------------------------------
void CMyPG_ProtectiBCUX42::GetEditMetrics(WORD* pData,WORD* pDeviceSetpoint)
{
	DEVICESETPOINT_iBCUX42* pDeviceSetpointiBCUX42 = (DEVICESETPOINT_iBCUX42*)pDeviceSetpoint;
// 	DWORD dwScale = (DWORD)g_pDeviceParam->wScaleCT*(DWORD)g_pDeviceParam->wScalePT;
	if(pData==&g_pDeviceSetpointConfig->bConfigMotor) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceSetpointConfig->bConfigFX) g_edit.SetEditEnumMetricsTog();
	if(pData==&g_pDeviceSetpointConfig->bConfigDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wMotor_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointiBCUX42->wMotor_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wSD_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointiBCUX42->wSD_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wSD_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wSD_TogDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wSD_TogFX) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wSD_TogAD) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wXSSD_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointiBCUX42->wXSSD_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wXSSD_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wXSSD_TogDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wXSSD_TogFX) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wXSSD_TogAD) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wDSXGL_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointiBCUX42->wDSXGL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wDSXGL_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wDSXGL_TogDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wDSXGL_TogFX) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wDSXGL_TogAE) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wFSXGL_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointiBCUX42->wFSXGL_SetK) g_edit.SetEditDataMetricsReal(5,400,0x52);
	if(pData==&pDeviceSetpointiBCUX42->wFSXGL_IDMT) g_edit.SetEditEnumMetricsMul(4,5,(char*)c_szIDMTType[0]);
	if(pData==&pDeviceSetpointiBCUX42->wHJS_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointiBCUX42->wHJS_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wGFH_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointiBCUX42->wGFH_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wFXDL_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointiBCUX42->wFXDL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wLXDL_SetI) SetDataSet3I0();
	if(pData==&pDeviceSetpointiBCUX42->wLXDL_SetT) SetDataSetT();
// 	if(pData==&pDeviceSetpointiBCUX42->wJDSX_SetI) SetDataSet3I0();
// 	if(pData==&pDeviceSetpointiBCUX42->wJDSX_SetU) SetDataSet3U0();
// 	if(pData==&pDeviceSetpointiBCUX42->wJDSX_TogTHD5) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wGDY_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wGDY_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wDDY_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wDDY_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wSY_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wSY_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wFXDY_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wFXDY_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wLXDY_SetU) SetDataSet3U0();
	if(pData==&pDeviceSetpointiBCUX42->wLXDY_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wFHDYGL_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointiBCUX42->wFHDYGL_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wFHDYGL_SetUFX) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wFHDYGL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wFHDYGL_TogDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wFHDYGL_TogFXDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wDZJZ_SetF) g_edit.SetEditDataMetricsReal(4000,5000,0x52);
	if(pData==&pDeviceSetpointiBCUX42->wDZJZ_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wDZJZ_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wDZJZ_SetDFDT) g_edit.SetEditDataMetricsReal(0,2000,0x52);
	if(pData==&pDeviceSetpointiBCUX42->wDZJZ_TogDFDT) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wDZJZ_TogDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wDZJZ_TogDL) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wDYJL_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wDYJL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wDYJL_SetDVDT) g_edit.SetEditDataMetricsReal(0,30000,0x52);
	if(pData==&pDeviceSetpointiBCUX42->wDYJL_TogDVDT) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wDYJL_TogDL) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wCHZ_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wCHZ_SetA) g_edit.SetEditDataMetricsReal(0,90,0x20);
	if(pData==&pDeviceSetpointiBCUX42->wCHZ_TogWY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wCHZ_TogTQ) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointiBCUX42->wBZT_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointiBCUX42->wBZT_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wGR_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointiBCUX42->wGR_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wGR_SetK2) g_edit.SetEditDataMetricsReal(0,1000,0x52);
	if(pData==&pDeviceSetpointiBCUX42->wNGL_SetP) g_edit.SetEditDataMetricsReal(0,1000,0x41);
	if(pData==&pDeviceSetpointiBCUX42->wNGL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wIXDSX_SetI) SetDataSetIx();
	if(pData==&pDeviceSetpointiBCUX42->wIXDSX_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointiBCUX42->wIXFSX_SetI) SetDataSetIx();
	if(pData==&pDeviceSetpointiBCUX42->wIXFSX_SetK) g_edit.SetEditDataMetricsReal(5,400,0x52);
	if(pData==&pDeviceSetpointiBCUX42->wIXFSX_IDMT) g_edit.SetEditEnumMetricsMul(4,5,(char*)c_szIDMTType[0]);
}

