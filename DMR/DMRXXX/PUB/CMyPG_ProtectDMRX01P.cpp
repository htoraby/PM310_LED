#include <Main.h>

//-----------------------------------------------------------------------------
void CMyPG_ProtectDMRX01P::OutProtectSetI(WORD* pSetI)
{
	OutProtectSetX(MULTITEXT("������ֵ:","CURRENT:"),"A",pSetI);
}

void CMyPG_ProtectDMRX01P::OutProtectSetU(WORD* pSetU)
{
	OutProtectSetX(MULTITEXT("��ѹ��ֵ:","VOLTAGE:"),"V",pSetU);
}

void CMyPG_ProtectDMRX01P::OutProtectSetT(WORD* pSetT)
{
	OutProtectSetX(MULTITEXT("ʱ�䶨ֵ:","TIME DELAY:"),"s",pSetT);
}

void CMyPG_ProtectDMRX01P::OutProtectSetF(WORD* pSetF)
{
	OutProtectSetX(MULTITEXT("Ƶ�ʶ�ֵ:","FREQUENCY:"),"Hz",pSetF);
}

void CMyPG_ProtectDMRX01P::iiiOnRefreshPage(WORD* pDeviceSetpoint)
{
	DEVICESETPOINT_DMRX01* pDeviceSetpointDMRX01 = (DEVICESETPOINT_DMRX01*)pDeviceSetpoint;
	if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
	{
		OutProtectText(MULTITEXT("�綯������","MOTOR PARAMETERS"));
		if(g_deviceInfo.wLCDWidth>180)
		{
			OutProtectSetX(MULTITEXT("�����:","RATED CURRENT:"),"A",&pDeviceSetpointDMRX01->wMotor_SetI);
			OutProtectSetX(MULTITEXT("����ʱ��:","STARTING TIME:"),"s",&pDeviceSetpointDMRX01->wMotor_SetT);
		}
		else
		{
			OutProtectSetX(MULTITEXT("�����:","RATED CUR:"),"A",&pDeviceSetpointDMRX01->wMotor_SetI);
			OutProtectSetX(MULTITEXT("����ʱ��:","START TIME:"),"s",&pDeviceSetpointDMRX01->wMotor_SetT);
		}
	}
	//�������ٶϡ�
	if(SETPOINTCFG(PROTECT_SD))
	{
		OutProtectName(PROTECT_SD);
		OutProtectSetI(&pDeviceSetpointDMRX01->wSD_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wSD_SetT);
		if(g_pDeviceSetpointConfig->bConfigDY==TRUE)
		{
			OutProtectSetU(&pDeviceSetpointDMRX01->wSD_SetU);
			m_wOffset = 3;
			if(g_deviceInfo.wLCDWidth>180) OutProtectTog(MULTITEXT("��ѹ����:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointDMRX01->wSD_TogDY);
			else OutProtectTog(MULTITEXT("��ѹ����:","UNDERVOL BLOCK:"),&pDeviceSetpointDMRX01->wSD_TogDY);
		}
		if(g_pDeviceSetpointConfig->bConfigFX==TRUE)
		{
			m_wOffset = 3; 
			if(g_deviceInfo.wLCDWidth>180) OutProtectTog(MULTITEXT("�������:","DIRECTIONAL BLOCKING:"),&pDeviceSetpointDMRX01->wSD_TogFX);
			else OutProtectTog(MULTITEXT("�������:","DIRECT BLOCK:"),&pDeviceSetpointDMRX01->wSD_TogFX);
		}
		if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("��ֵ�ӱ�:","AUTO DOUBLE:"),&pDeviceSetpointDMRX01->wSD_TogAD);
		}
	}
	//����ʱ�����ٶϡ�
	if(SETPOINTCFG(PROTECT_XSSD))
	{
		OutProtectName(PROTECT_XSSD);
		OutProtectSetI(&pDeviceSetpointDMRX01->wXSSD_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wXSSD_SetT);
		if(g_pDeviceSetpointConfig->bConfigDY==TRUE)
		{
			OutProtectSetU(&pDeviceSetpointDMRX01->wXSSD_SetU);
			m_wOffset = 3;
			if(g_deviceInfo.wLCDWidth>180) OutProtectTog(MULTITEXT("��ѹ����:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointDMRX01->wXSSD_TogDY);
			else OutProtectTog(MULTITEXT("��ѹ����:","UNDERVOL BLOCK:"),&pDeviceSetpointDMRX01->wXSSD_TogDY);
		}
		if(g_pDeviceSetpointConfig->bConfigFX==TRUE)
		{
			m_wOffset = 3; 
			if(g_deviceInfo.wLCDWidth>180) OutProtectTog(MULTITEXT("�������:","DIRECTIONAL BLOCKING:"),&pDeviceSetpointDMRX01->wXSSD_TogFX);
			else OutProtectTog(MULTITEXT("�������:","DIRECT BLOCK:"),&pDeviceSetpointDMRX01->wXSSD_TogFX);
		}
		if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("��ֵ�ӱ�:","AUTO DOUBLE:"),&pDeviceSetpointDMRX01->wXSSD_TogAD);
		}
	}
	//����ʱ�޹�����
	if(SETPOINTCFG(PROTECT_DSXGL))
	{
		OutProtectName(PROTECT_DSXGL);
		OutProtectSetI(&pDeviceSetpointDMRX01->wDSXGL_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wDSXGL_SetT);
		if(g_pDeviceSetpointConfig->bConfigDY==TRUE)
		{
			OutProtectSetU(&pDeviceSetpointDMRX01->wDSXGL_SetU);
			m_wOffset = 3; 
			if(g_deviceInfo.wLCDWidth>180) OutProtectTog(MULTITEXT("��ѹ����:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointDMRX01->wDSXGL_TogDY);
			else OutProtectTog(MULTITEXT("��ѹ����:","UNDERVOL BLOCK:"),&pDeviceSetpointDMRX01->wDSXGL_TogDY);
		}
		if(g_pDeviceSetpointConfig->bConfigFX==TRUE)
		{
			m_wOffset = 3;
			if(g_deviceInfo.wLCDWidth>180) OutProtectTog(MULTITEXT("�������:","DIRECTIONAL BLOCKING:"),&pDeviceSetpointDMRX01->wDSXGL_TogFX);
			else OutProtectTog(MULTITEXT("�������:","DIRECT BLOCK:"),&pDeviceSetpointDMRX01->wDSXGL_TogFX);
		}
		if(g_pDeviceSetpointConfig->bConfigMotor==TRUE)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("�����˳�:","AUTO EXIT:"),&pDeviceSetpointDMRX01->wDSXGL_TogAE);
		}
	}
	//����ʱ�޹�����
	if(SETPOINTCFG(PROTECT_FSXGL))
	{
		OutProtectName(PROTECT_FSXGL);
		OutProtectSetI(&pDeviceSetpointDMRX01->wFSXGL_SetI);
		if(g_deviceInfo.wLCDWidth>180) OutProtectSetX(MULTITEXT("ʱ��ϵ��:","TIME COEFFICIENT:"),"",&pDeviceSetpointDMRX01->wFSXGL_SetK);
		else OutProtectSetX(MULTITEXT("ʱ��ϵ��:","TIME COEFF:"),"",&pDeviceSetpointDMRX01->wFSXGL_SetK);
		m_wOffset = 2; OutProtectTog(MULTITEXT("��������:","IDMT CURVE:"),&pDeviceSetpointDMRX01->wFSXGL_IDMT);
	}
	//������١�
	if(SETPOINTCFG(PROTECT_HJS))
	{
		OutProtectName(PROTECT_HJS);
		OutProtectSetI(&pDeviceSetpointDMRX01->wHJS_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wHJS_SetT);
	}
	//�������ɡ�
	if(SETPOINTCFG(PROTECT_GFH))
	{
		OutProtectName(PROTECT_GFH);
		OutProtectSetI(&pDeviceSetpointDMRX01->wGFH_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wGFH_SetT);
	}
	//�����������
	if(SETPOINTCFG(PROTECT_FXDL))
	{
		OutProtectName(PROTECT_FXDL);
		OutProtectSetI(&pDeviceSetpointDMRX01->wFXDL_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wFXDL_SetT);
	}
	//�����������
	if(SETPOINTCFG(PROTECT_LXDL))
	{
		OutProtectName(PROTECT_LXDL);
		OutProtectSetI(&pDeviceSetpointDMRX01->wLXDL_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wLXDL_SetT);
	}
	//������ӵ�ѡ�ߡ�
	if(SETPOINTCFG(PROTECT_JDSX))
	{
		OutProtectName(PROTECT_JDSX);
		OutProtectSetI(&pDeviceSetpointDMRX01->wJDSX_SetI);
		OutProtectSetU(&pDeviceSetpointDMRX01->wJDSX_SetU);
		m_wOffset = 3;
		if(g_deviceInfo.wLCDWidth>180) OutProtectTog(MULTITEXT("���г��:","FIFTH HARMONIC:"),&pDeviceSetpointDMRX01->wJDSX_TogTHD5);
		else OutProtectTog(MULTITEXT("���г��:","FIFTH HAR:"),&pDeviceSetpointDMRX01->wJDSX_TogTHD5);
	}
	//������ѹ��
	if(SETPOINTCFG(PROTECT_GDY))
	{
		OutProtectName(PROTECT_GDY);
		OutProtectSetU(&pDeviceSetpointDMRX01->wGDY_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wGDY_SetT);
	}
	//���͵�ѹ��
	if(SETPOINTCFG(PROTECT_DDY))
	{
		OutProtectName(PROTECT_DDY);
		OutProtectSetU(&pDeviceSetpointDMRX01->wDDY_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wDDY_SetT);
	}
	//��ʧѹ��
	if(SETPOINTCFG(PROTECT_SY))
	{
		OutProtectName(PROTECT_SY);
		OutProtectSetU(&pDeviceSetpointDMRX01->wSY_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wSY_SetT);
	}
	//�������ѹ��
	if(SETPOINTCFG(PROTECT_FXDY))
	{
		OutProtectName(PROTECT_FXDY);
		OutProtectSetU(&pDeviceSetpointDMRX01->wFXDY_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wFXDY_SetT);
	}
	//�������ѹ��
	if(SETPOINTCFG(PROTECT_LXDY))
	{
		OutProtectName(PROTECT_LXDY);
		OutProtectSetU(&pDeviceSetpointDMRX01->wLXDY_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wLXDY_SetT);
	}
	//�����ϵ�ѹ������
	if(SETPOINTCFG(PROTECT_FHDYGL))
	{
		OutProtectName(PROTECT_FHDYGL);
		OutProtectSetI(&pDeviceSetpointDMRX01->wFHDYGL_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wFHDYGL_SetT);
		OutProtectSetU(&pDeviceSetpointDMRX01->wFHDYGL_SetU);
		if(g_deviceInfo.wLCDWidth>180)
		{
			OutProtectSetX(MULTITEXT("�����ѹ:","NEGATIVE VOLTAGE:"),"V",&pDeviceSetpointDMRX01->wFHDYGL_SetUFX);
			m_wOffset = 3; OutProtectTog(MULTITEXT("��ѹ����:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointDMRX01->wFHDYGL_TogDY);
			m_wOffset = 3; OutProtectTog(MULTITEXT("�������:","NEGATIVE BLOCKING:"),&pDeviceSetpointDMRX01->wFHDYGL_TogFXDY);
		}
		else
		{
			OutProtectSetX(MULTITEXT("�����ѹ:","NEG VOL:"),"V",&pDeviceSetpointDMRX01->wFHDYGL_SetUFX);
			m_wOffset = 3; OutProtectTog(MULTITEXT("��ѹ����:","UNDERVOL BLOCK:"),&pDeviceSetpointDMRX01->wFHDYGL_TogDY);
			m_wOffset = 3; OutProtectTog(MULTITEXT("�������:","NEG BLOCK:"),&pDeviceSetpointDMRX01->wFHDYGL_TogFXDY);
		}
	}
	//�����ܼ��ء�
	if(SETPOINTCFG(PROTECT_DZJZ))
	{
		OutProtectName(PROTECT_DZJZ);
		OutProtectSetF(&pDeviceSetpointDMRX01->wDZJZ_SetF);
		OutProtectSetT(&pDeviceSetpointDMRX01->wDZJZ_SetT);
		OutProtectSetU(&pDeviceSetpointDMRX01->wDZJZ_SetU);
		OutProtectSetX(MULTITEXT("���ֵ:","DF/DT:"),"Hs",&pDeviceSetpointDMRX01->wDZJZ_SetDFDT);
		if(g_deviceInfo.wLCDWidth>180)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("�������:","DF/DT BLOCKING:"),&pDeviceSetpointDMRX01->wDZJZ_TogDFDT);
			m_wOffset = 3; OutProtectTog(MULTITEXT("��ѹ����:","UNDERVOLTAGE BLOCKING:"),&pDeviceSetpointDMRX01->wDZJZ_TogDY);
			m_wOffset = 3; OutProtectTog(MULTITEXT("Ƿ������:","UNDERCURRENT BLOCKING:"),&pDeviceSetpointDMRX01->wDZJZ_TogDL);
		}
		else
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("�������:","DF/DT BLOCK:"),&pDeviceSetpointDMRX01->wDZJZ_TogDFDT);
			m_wOffset = 3; OutProtectTog(MULTITEXT("��ѹ����:","UNDERVOL BLOCK:"),&pDeviceSetpointDMRX01->wDZJZ_TogDY);
			m_wOffset = 3; OutProtectTog(MULTITEXT("Ƿ������:","UNDERCUR BLOCK:"),&pDeviceSetpointDMRX01->wDZJZ_TogDL);
		}
	}
	//����ѹ���С�
	if(SETPOINTCFG(PROTECT_DYJL))
	{
		OutProtectName(PROTECT_DYJL);
		OutProtectSetU(&pDeviceSetpointDMRX01->wDYJL_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wDYJL_SetT);
		OutProtectSetX(MULTITEXT("���ֵ:","DV/DT:"),"Vs",&pDeviceSetpointDMRX01->wDYJL_SetDVDT);
		if(g_deviceInfo.wLCDWidth>180)
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("�������:","DV/DT BLOCKING:"),&pDeviceSetpointDMRX01->wDYJL_TogDVDT);
			m_wOffset = 3; OutProtectTog(MULTITEXT("Ƿ������:","UNDERCURRENT BLOCKING:"),&pDeviceSetpointDMRX01->wDYJL_TogDL);
		}
		else
		{
			m_wOffset = 3; OutProtectTog(MULTITEXT("�������:","DV/DT BLOCK:"),&pDeviceSetpointDMRX01->wDYJL_TogDVDT);
			m_wOffset = 3; OutProtectTog(MULTITEXT("Ƿ������:","UNDERCUR BLOCK:"),&pDeviceSetpointDMRX01->wDYJL_TogDL);
		}
	}
	//���غ�բ��
	if(SETPOINTCFG(PROTECT_CHZ))
	{
		OutProtectName(PROTECT_CHZ);
		OutProtectSetT(&pDeviceSetpointDMRX01->wCHZ_SetT);
// 		g_lcd.m_wAutoPosX = PGP_FONTWIDTH*4;
#if DFT_Uxab || DFT_Uxa
		if(g_deviceInfo.wLCDWidth>180)
		{
			m_wOffset = 4; OutProtectSetX(MULTITEXT("ͬ�ڽǶ�:","SYNCHRONISM ANGLE:"),"^",&pDeviceSetpointDMRX01->wCHZ_SetA);
			m_wOffset = 3; OutProtectTog(MULTITEXT("�� �� ѹ:","VOLTAGE CHECK:"),&pDeviceSetpointDMRX01->wCHZ_TogWY);
			m_wOffset = 3; OutProtectTog(MULTITEXT("�� ͬ ��:","SYNCHRONISM:"),&pDeviceSetpointDMRX01->wCHZ_TogTQ);
		}
		else
		{
			m_wOffset = 4; OutProtectSetX(MULTITEXT("ͬ�ڽǶ�:","SYNCH ANGLE:"),"^",&pDeviceSetpointDMRX01->wCHZ_SetA);
			m_wOffset = 3; OutProtectTog(MULTITEXT("�� �� ѹ:","VOL CHECK:"),&pDeviceSetpointDMRX01->wCHZ_TogWY);
			m_wOffset = 3; OutProtectTog(MULTITEXT("�� ͬ ��:","SYNCH:"),&pDeviceSetpointDMRX01->wCHZ_TogTQ);
		}
#endif
	}
	//������Ͷ��
	if(SETPOINTCFG(PROTECT_BZT))
	{
		OutProtectName(PROTECT_BZT);
		OutProtectSetU(&pDeviceSetpointDMRX01->wBZT_SetU);
		OutProtectSetT(&pDeviceSetpointDMRX01->wBZT_SetT);
	}
	//�����ȡ�
	if(SETPOINTCFG(PROTECT_GR))
	{
		OutProtectName(PROTECT_GR);
		OutProtectSetI(&pDeviceSetpointDMRX01->wGR_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wGR_SetT);
		if(g_deviceInfo.wLCDWidth>180) OutProtectSetX(MULTITEXT("����ϵ��:","NEGATIVE COEFFICIENT:"),"",&pDeviceSetpointDMRX01->wGR_SetK2);
		else OutProtectSetX(MULTITEXT("����ϵ��:","NEG COEFF:"),"",&pDeviceSetpointDMRX01->wGR_SetK2);
	}
	//���湦�ʡ�
	if(SETPOINTCFG(PROTECT_NGL))
	{
		OutProtectName(PROTECT_NGL);
		m_wOffset = 1;
		if(g_deviceInfo.wLCDWidth>180) OutProtectSetX(MULTITEXT("���ʶ�ֵ:","ACTIVE POWER:"),"W",&pDeviceSetpointDMRX01->wNGL_SetP);
		else OutProtectSetX(MULTITEXT("���ʶ�ֵ:","ACT PWR:"),"W",&pDeviceSetpointDMRX01->wNGL_SetP);
		OutProtectSetT(&pDeviceSetpointDMRX01->wNGL_SetT);
	}
	//������ʱ�������
	if(SETPOINTCFG(PROTECT_QDSJGC))
	{
		OutProtectName(PROTECT_QDSJGC);
	}
	//����ʱ��Ix������
	if(SETPOINTCFG(PROTECT_IXDSX))
	{
		OutProtectName(PROTECT_IXDSX);
		OutProtectSetI(&pDeviceSetpointDMRX01->wIXDSX_SetI);
		OutProtectSetT(&pDeviceSetpointDMRX01->wIXDSX_SetT);
	}
	//����ʱ��Ix������
	if(SETPOINTCFG(PROTECT_IXFSX))
	{
		OutProtectName(PROTECT_IXFSX);
		OutProtectSetI(&pDeviceSetpointDMRX01->wIXFSX_SetI);
		if(g_deviceInfo.wLCDWidth>180) OutProtectSetX(MULTITEXT("ʱ��ϵ��:","TIME COEFFICIENT:"),"",&pDeviceSetpointDMRX01->wIXFSX_SetK);
		else OutProtectSetX(MULTITEXT("ʱ��ϵ��:","TIME COEFF:"),"",&pDeviceSetpointDMRX01->wIXFSX_SetK);
// 		g_lcd.m_wAutoPosX = PGP_FONTWIDTH;
		m_wOffset = 2; OutProtectTog(MULTITEXT("��������:","IDMT CURVE:"),&pDeviceSetpointDMRX01->wIXFSX_IDMT);
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
	DWORD dwScale2Uln = ((DWORD)g_pDeviceParam->wScale2Uln*1732L+500L)/1000L;
	if(dwScale2Uln>65000) dwScale2Uln = 65000;
	g_edit.SetEditDataMetricsReal(0,dwScale2Uln,0x52);
}

static void SetDataSet3I0(void)
{
	g_edit.SetEditDataMetricsReal(0,g_pDeviceParam->wScale23I0,0x52);
}

static void SetDataSet3U0(void)
{
#ifndef DFT_3U0
	DWORD dwScale2Uln = ((DWORD)g_pDeviceParam->wScale2Uln*1732L+500L)/1000L;
	if(dwScale2Uln>65000) dwScale2Uln = 65000;
	g_edit.SetEditDataMetricsReal(0,dwScale2Uln,0x52);
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
void CMyPG_ProtectDMRX01P::SetMetrics(void)
{
	switch(g_wPanelTest)
	{
	case 0x0055:
		m_wPGP_LINEY = 22;							// ÿ�м��;
		m_wPGP_LINENUM = 12;						// ÿҳ����;
		m_wPGP_LINEOFFSET = MENUHEAD + 28;			// ��ʼ��Y����;
		m_wPGP_LINECFGX1 = 6;						// ��������:��������X����;
		m_wPGP_LINECFGX2 = 200;						// ��������:��������X����;
		m_wPGP_LINESETX1 = 6;						// ������ֵ:��������X����;
		m_wPGP_LINESETX2 = 159;						// ������ֵ:��ֵ����X����(�ұ߿���);
		m_wPGP_LINESETX3 = 169;						// ������ֵ:������ֵX����;
		m_wPGP_FONTWIDTH = 8;						// ������;
		break;
	case 0x0054:
	default:
		m_wPGP_LINEY = 14;							// ÿ�м��;
		m_wPGP_LINENUM = 10;						// ÿҳ����;
		m_wPGP_LINEOFFSET = MENUHEAD+1;				// ��ʼ��Y����;
		m_wPGP_LINECFGX1 = 2;						// ��������:��������X����;
		m_wPGP_LINECFGX2 = 132;						// ��������:��������X����;
		m_wPGP_LINESETX1 = 2;						// ������ֵ:��������X����;
		m_wPGP_LINESETX2 = 66;						// ������ֵ:��ֵ����X����(�ұ߿���);
		m_wPGP_LINESETX3 = 102;						// ������ֵ:������ֵX����;
		m_wPGP_FONTWIDTH = 6;						// ������;
		break;
	}
}

void CMyPG_ProtectDMRX01P::GetEditMetrics(WORD* pData,WORD* pDeviceSetpoint)
{
	DEVICESETPOINT_DMRX01* pDeviceSetpointDMRX01 = (DEVICESETPOINT_DMRX01*)pDeviceSetpoint;
// 	DWORD dwScale = (DWORD)g_pDeviceParam->wScaleCT*(DWORD)g_pDeviceParam->wScalePT;
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
	if(pData==&pDeviceSetpointDMRX01->wFSXGL_SetK) g_edit.SetEditDataMetricsReal(5,400,0x52);
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
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_SetF) g_edit.SetEditDataMetricsReal(4000,5000,0x52);
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_SetDFDT) g_edit.SetEditDataMetricsReal(0,2000,0x52);
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_TogDFDT) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_TogDY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDZJZ_TogDL) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDYJL_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wDYJL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wDYJL_SetDVDT) g_edit.SetEditDataMetricsReal(0,30000,0x52);
	if(pData==&pDeviceSetpointDMRX01->wDYJL_TogDVDT) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wDYJL_TogDL) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wCHZ_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wCHZ_SetA) g_edit.SetEditDataMetricsReal(0,90,0x20);
	if(pData==&pDeviceSetpointDMRX01->wCHZ_TogWY) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wCHZ_TogTQ) g_edit.SetEditEnumMetricsTog();
	if(pData==&pDeviceSetpointDMRX01->wBZT_SetU) SetDataSetUll();
	if(pData==&pDeviceSetpointDMRX01->wBZT_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wGR_SetI) SetDataSetIP();
	if(pData==&pDeviceSetpointDMRX01->wGR_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wGR_SetK2) g_edit.SetEditDataMetricsReal(0,1000,0x52);
	if(pData==&pDeviceSetpointDMRX01->wNGL_SetP) g_edit.SetEditDataMetricsReal(0,1000,0x41);
	if(pData==&pDeviceSetpointDMRX01->wNGL_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wIXDSX_SetI) SetDataSetIx();
	if(pData==&pDeviceSetpointDMRX01->wIXDSX_SetT) SetDataSetT();
	if(pData==&pDeviceSetpointDMRX01->wIXFSX_SetI) SetDataSetIx();
	if(pData==&pDeviceSetpointDMRX01->wIXFSX_SetK) g_edit.SetEditDataMetricsReal(5,400,0x52);
	if(pData==&pDeviceSetpointDMRX01->wIXFSX_IDMT) g_edit.SetEditEnumMetricsMul(4,5,(char*)c_szIDMTType[0]);
}

