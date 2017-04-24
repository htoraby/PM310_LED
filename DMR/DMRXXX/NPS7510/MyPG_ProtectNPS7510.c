#include <Main.h>

//-----------------------------------------------------------------------------
// void PGPRT_OutProtectSetI(WORD* pSetI)
// {
// 	PGPRT_OutProtectSetX(MULTITEXT("������ֵ:","CURRENT:"),"A",pSetI);
// }
// 
// void PGPRT_OutProtectSetU(WORD* pSetU)
// {
// 	PGPRT_OutProtectSetX(MULTITEXT("��ѹ��ֵ:","VOLTAGE:"),"V",pSetU);
// }
// 
// void PGPRT_OutProtectSetT(WORD* pSetT)
// {
// 	PGPRT_OutProtectSetX(MULTITEXT("ʱ�䶨ֵ:","TIME DELAY:"),"s",pSetT);
// }
/*
void PGPRT_OutProtectSetF(WORD* pSetF)
{
	PGPRT_OutProtectSetX(MULTITEXT("Ƶ�ʶ�ֵ:","FREQUENCY:"),"Hz",pSetF);
}
*/


void PGPRT_iiiOnRefreshPage(WORD* pDeviceSetpoint)
{
	DEVICESETPOINT_iBCU* pDeviceSetpointiBCU;

    pDeviceSetpointiBCU = (DEVICESETPOINT_iBCU*)pDeviceSetpoint;

    if(!g_bDisplaySetpoint)
    {
        PGPRT_OutProtectName(PROTECT_DL1);
        PGPRT_OutProtectTog("���������բ", &g_deviceSetpoint.wConfig[PROTECT_DL1]);
        PGPRT_OutProtectName(PROTECT_DL2);
        PGPRT_OutProtectTog("���������բ", &g_deviceSetpoint.wConfig[PROTECT_DL2]);
        PGPRT_OutProtectName(PROTECT_GY1);
        PGPRT_OutProtectTog("��ѹ�����բ", &g_deviceSetpoint.wConfig[PROTECT_GY1]);
        PGPRT_OutProtectName(PROTECT_GY2);
        PGPRT_OutProtectTog("��ѹ�����բ", &g_deviceSetpoint.wConfig[PROTECT_GY2]);
        PGPRT_OutProtectName(PROTECT_QY1);
        PGPRT_OutProtectTog("Ƿѹ�����բ", &g_deviceSetpoint.wConfig[PROTECT_QY1]);
        PGPRT_OutProtectName(PROTECT_QY2);
        PGPRT_OutProtectTog("Ƿѹ�����բ", &g_deviceSetpoint.wConfig[PROTECT_QY2]);
    }
    else
    {
        PGPRT_OutProtectSetX("������ε���", "A", &pDeviceSetpointiBCU->wDL1_SetI);
        PGPRT_OutProtectSetX("�������ʱ��", "s", &pDeviceSetpointiBCU->wDL1_SetT);
        PGPRT_OutProtectSetX("������ε���", "A", &pDeviceSetpointiBCU->wDL2_SetI);
        PGPRT_OutProtectSetX("�������ʱ��", "s", &pDeviceSetpointiBCU->wDL2_SetT);
        PGPRT_OutProtectSetX("��ѹ��ε�ѹ", "V", &pDeviceSetpointiBCU->wGY1_SetU);
        PGPRT_OutProtectSetX("��ѹ���ʱ��", "s", &pDeviceSetpointiBCU->wGY1_SetT);
        PGPRT_OutProtectSetX("��ѹ��ε�ѹ", "V", &pDeviceSetpointiBCU->wGY2_SetU);
        PGPRT_OutProtectSetX("��ѹ���ʱ��", "s", &pDeviceSetpointiBCU->wGY2_SetT);
        PGPRT_OutProtectSetX("Ƿѹ��ε�ѹ", "V", &pDeviceSetpointiBCU->wQY1_SetU);
        PGPRT_OutProtectSetX("Ƿѹ���ʱ��", "s", &pDeviceSetpointiBCU->wQY1_SetT);
        PGPRT_OutProtectSetX("Ƿѹ��ε�ѹ", "V", &pDeviceSetpointiBCU->wQY2_SetU);
        PGPRT_OutProtectSetX("Ƿѹ���ʱ��", "s", &pDeviceSetpointiBCU->wQY2_SetT);

        g_nOffset = 12;
        PGPRT_OutProtectSetX("CT���", "", &g_pDeviceParam->wScaleCT);
        g_nOffset = 12;
        PGPRT_OutProtectSetX("PT���", "", &g_pDeviceParam->wScalePT);
        g_nOffset = 30;
        PGPRT_OutProtectSetX("����������", "", &g_pDeviceParam->wSLType);
     }
}


//-----------------------------------------------------------------------------
static void SetDataSetT(void)
{
	EditG_SetEditDataMetricsReal(0,60000,0x52);
}

static void SetDataSetIP(void)
{
	EditG_SetEditDataMetricsReal(0,10000,0x52);
}

static void SetDataSetUll(void)
{
	DWORD dwScale2Uln = ((DWORD)SCALE2ULN*1732L+500L)/1000L;
	if(dwScale2Uln>65000) dwScale2Uln = 65000;
	EditG_SetEditDataMetricsReal(0,dwScale2Uln,0x52);
}

//static void SetDataSet3I0(void)
//{
//	EditG_SetEditDataMetricsReal(0,10000,0x52);
//}

// static void SetDataSet3U0(void)
// {
// #ifndef DFT_3U0
// 	DWORD dwScale2Uln = ((DWORD)g_pDeviceParam->wScale2Uln*1732L+500L)/1000L;
// 	if(dwScale2Uln>65000) dwScale2Uln = 65000;
// 	EditG_SetEditDataMetricsReal(0,dwScale2Uln,0x52);
// #else
// 	EditG_SetEditDataMetricsReal(0,g_pDeviceParam->wScale23U0,0x52);
// #endif
// }



//-----------------------------------------------------------------------------
void PGPRT_SetMetrics(void)
{
	g_wPGP_LINEY = 14;							// ÿ�м��;
	g_wPGP_LINENUM = 10;						// ÿҳ����;
	g_wPGP_LINEOFFSET = MENUHEAD+1;				// ��ʼ��Y����;
	g_wPGP_LINECFGX1 = 2;						// ��������:��������X����;
	g_wPGP_LINECFGX2 = 132;						// ��������:��������X����;
	g_wPGP_LINESETX1 = 2;						// ������ֵ:��������X����;
	g_wPGP_LINESETX2 = 66;						// ������ֵ:��ֵ����X����(�ұ߿���);
	g_wPGP_LINESETX3 = 102;						// ������ֵ:������ֵX����;
	g_wPGP_FONTWIDTH = 6;						// ������;
}

void PGPRT_GetEditMetrics(WORD* pData,WORD* pDeviceSetpoint)
{
    DEVICESETPOINT_iBCU* pDeviceSetpointiBCU = (DEVICESETPOINT_iBCU*)pDeviceSetpoint;
    if(pData==&pDeviceSetpointiBCU->wDL1_SetI) SetDataSetIP();
    if(pData==&pDeviceSetpointiBCU->wDL1_SetT) SetDataSetT();
//     if(pData==&&g_deviceSetpoint.wConfig[PROTECT_DL1]) EditG_SetEditEnumMetricsTog();

    if(pData==&pDeviceSetpointiBCU->wDL2_SetI) SetDataSetIP();
    if(pData==&pDeviceSetpointiBCU->wDL2_SetT) SetDataSetT();
//     if(pData==&pDeviceSetpointiBCU->wDL2_TogTrip) EditG_SetEditEnumMetricsTog();

    if(pData==&pDeviceSetpointiBCU->wGY1_SetU) SetDataSetUll();
    if(pData==&pDeviceSetpointiBCU->wGY1_SetT) SetDataSetT();
//     if(pData==&pDeviceSetpointiBCU->wGY1_TogTrip) EditG_SetEditEnumMetricsTog();

    if(pData==&pDeviceSetpointiBCU->wGY2_SetU) SetDataSetUll();
    if(pData==&pDeviceSetpointiBCU->wGY2_SetT) SetDataSetT();
//     if(pData==&pDeviceSetpointiBCU->wGY2_TogTrip) EditG_SetEditEnumMetricsTog();

    if(pData==&pDeviceSetpointiBCU->wQY1_SetU) SetDataSetUll();
    if(pData==&pDeviceSetpointiBCU->wQY1_SetT) SetDataSetT();
//     if(pData==&pDeviceSetpointiBCU->wQY1_TogTrip) EditG_SetEditEnumMetricsTog();

    if(pData==&pDeviceSetpointiBCU->wQY2_SetU) SetDataSetUll();
    if(pData==&pDeviceSetpointiBCU->wQY2_SetT) SetDataSetT();
//     if(pData==&pDeviceSetpointiBCU->wQY2_TogTrip) EditG_SetEditEnumMetricsTog();
}

