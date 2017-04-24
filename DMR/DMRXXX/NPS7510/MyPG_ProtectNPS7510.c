#include <Main.h>

//-----------------------------------------------------------------------------
// void PGPRT_OutProtectSetI(WORD* pSetI)
// {
// 	PGPRT_OutProtectSetX(MULTITEXT("电流定值:","CURRENT:"),"A",pSetI);
// }
// 
// void PGPRT_OutProtectSetU(WORD* pSetU)
// {
// 	PGPRT_OutProtectSetX(MULTITEXT("电压定值:","VOLTAGE:"),"V",pSetU);
// }
// 
// void PGPRT_OutProtectSetT(WORD* pSetT)
// {
// 	PGPRT_OutProtectSetX(MULTITEXT("时间定值:","TIME DELAY:"),"s",pSetT);
// }
/*
void PGPRT_OutProtectSetF(WORD* pSetF)
{
	PGPRT_OutProtectSetX(MULTITEXT("频率定值:","FREQUENCY:"),"Hz",pSetF);
}
*/


void PGPRT_iiiOnRefreshPage(WORD* pDeviceSetpoint)
{
	DEVICESETPOINT_iBCU* pDeviceSetpointiBCU;

    pDeviceSetpointiBCU = (DEVICESETPOINT_iBCU*)pDeviceSetpoint;

    if(!g_bDisplaySetpoint)
    {
        PGPRT_OutProtectName(PROTECT_DL1);
        PGPRT_OutProtectTog("电流Ⅰ段跳闸", &g_deviceSetpoint.wConfig[PROTECT_DL1]);
        PGPRT_OutProtectName(PROTECT_DL2);
        PGPRT_OutProtectTog("电流Ⅱ段跳闸", &g_deviceSetpoint.wConfig[PROTECT_DL2]);
        PGPRT_OutProtectName(PROTECT_GY1);
        PGPRT_OutProtectTog("过压Ⅰ段跳闸", &g_deviceSetpoint.wConfig[PROTECT_GY1]);
        PGPRT_OutProtectName(PROTECT_GY2);
        PGPRT_OutProtectTog("过压Ⅱ段跳闸", &g_deviceSetpoint.wConfig[PROTECT_GY2]);
        PGPRT_OutProtectName(PROTECT_QY1);
        PGPRT_OutProtectTog("欠压Ⅰ段跳闸", &g_deviceSetpoint.wConfig[PROTECT_QY1]);
        PGPRT_OutProtectName(PROTECT_QY2);
        PGPRT_OutProtectTog("欠压Ⅱ段跳闸", &g_deviceSetpoint.wConfig[PROTECT_QY2]);
    }
    else
    {
        PGPRT_OutProtectSetX("电流Ⅰ段电流", "A", &pDeviceSetpointiBCU->wDL1_SetI);
        PGPRT_OutProtectSetX("电流Ⅰ段时间", "s", &pDeviceSetpointiBCU->wDL1_SetT);
        PGPRT_OutProtectSetX("电流Ⅱ段电流", "A", &pDeviceSetpointiBCU->wDL2_SetI);
        PGPRT_OutProtectSetX("电流Ⅱ段时间", "s", &pDeviceSetpointiBCU->wDL2_SetT);
        PGPRT_OutProtectSetX("过压Ⅰ段电压", "V", &pDeviceSetpointiBCU->wGY1_SetU);
        PGPRT_OutProtectSetX("过压Ⅰ段时间", "s", &pDeviceSetpointiBCU->wGY1_SetT);
        PGPRT_OutProtectSetX("过压Ⅱ段电压", "V", &pDeviceSetpointiBCU->wGY2_SetU);
        PGPRT_OutProtectSetX("过压Ⅱ段时间", "s", &pDeviceSetpointiBCU->wGY2_SetT);
        PGPRT_OutProtectSetX("欠压Ⅰ段电压", "V", &pDeviceSetpointiBCU->wQY1_SetU);
        PGPRT_OutProtectSetX("欠压Ⅰ段时间", "s", &pDeviceSetpointiBCU->wQY1_SetT);
        PGPRT_OutProtectSetX("欠压Ⅱ段电压", "V", &pDeviceSetpointiBCU->wQY2_SetU);
        PGPRT_OutProtectSetX("欠压Ⅱ段时间", "s", &pDeviceSetpointiBCU->wQY2_SetT);

        g_nOffset = 12;
        PGPRT_OutProtectSetX("CT变比", "", &g_pDeviceParam->wScaleCT);
        g_nOffset = 12;
        PGPRT_OutProtectSetX("PT变比", "", &g_pDeviceParam->wScalePT);
        g_nOffset = 30;
        PGPRT_OutProtectSetX("主接线类型", "", &g_pDeviceParam->wSLType);
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
	g_wPGP_LINEY = 14;							// 每行间距;
	g_wPGP_LINENUM = 10;						// 每页行数;
	g_wPGP_LINEOFFSET = MENUHEAD+1;				// 起始行Y坐标;
	g_wPGP_LINECFGX1 = 2;						// 保护配置:保护名称X坐标;
	g_wPGP_LINECFGX2 = 132;						// 保护配置:保护配置X坐标;
	g_wPGP_LINESETX1 = 2;						// 保护定值:保护名称X坐标;
	g_wPGP_LINESETX2 = 66;						// 保护定值:定值名称X坐标(右边靠齐);
	g_wPGP_LINESETX3 = 102;						// 保护定值:保护定值X坐标;
	g_wPGP_FONTWIDTH = 6;						// 字体宽度;
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

