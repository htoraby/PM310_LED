#include <Main.h>

DEVICEPARAM_DMR4* g_pDeviceParam;
ANALOGDATA g_analogData;
ANALOGDATAEXT g_analogDataExt;
CMyData g_dataIa;
CMyData g_dataIb;
CMyData g_dataIc;
CMyData g_dataIA;
CMyData g_dataIB;
CMyData g_dataIC;
CMyData g_dataUa;
CMyData g_dataUb;
CMyData g_dataUc;
CMyData g_dataUab;
CMyData g_dataUbc;
CMyData g_dataUca;
CMyData g_data3I0;
CMyData g_data3U0;
CMyData g_data3I2;
CMyData g_data3U2;
CMyData g_dataF;
CMyData g_dataP;
CMyData g_dataQ;
CMyData g_dataPF;
CMyData g_dataIx;
CMyData g_dataUxa;
CMyData g_dataUxb;
CMyData g_dataUxc;
CMyData g_dataUxab;
CMyData g_dataUxbc;
CMyData g_dataUxca;
CMyData g_data3Ux0;
CMyData g_data3Ux2;
CMyData g_dataFx;
#ifdef DCIN_COUNT
CMyData g_dataDC[DCIN_COUNT];
#endif/*DCIN_COUNT*/
CMyBreakerOperate g_breaker;

#ifdef _CMYDCPROCESS_H
CLASSNAME_DCPROCESS g_dcprocess;

//-----------------------------------------------------------------------------
short CMyAppDMR4::GetDataDC(WORD wIndex)
{
	if(wIndex>=DCIN_COUNT) return 0;
	long lDC4 = (long)g_dcparamTable.dcparam[wIndex].nData4mA;
	long lDC20 = (long)g_dcparamTable.dcparam[wIndex].nData20mA;
	long lData = (long)g_dcprocess.m_wDataDCIN[wIndex];
	long lTmp = (lDC4*5-lDC20)/4 + (lData*(lDC20-lDC4)+1200L)/2400L;
	if(lTmp<-32768) lTmp = -32768;
	if(lTmp>32768) lTmp = 32768;
	return (short)lTmp;
}
#endif/*_CMYDCPROCESS_H*/

//-----------------------------------------------------------------------------
typedef struct STCOMPLEX
{
	short nR;
	short nX;
}Complex;


const Complex c_stW = 
{
	-500,866
};

const Complex c_stW_1 = 
{
	-1500,866
};

Complex ComplexDiv(Complex* pData1,Complex* pData2)
{
	Complex result;
	long lR = (long)pData1->nR*(long)pData2->nR + (long)pData1->nX*(long)pData2->nX;
	long lX = -(long)pData1->nR*(long)pData2->nX + (long)pData1->nX*(long)pData2->nR;
	long lA2 = (long)pData2->nR*(long)pData2->nR + (long)pData2->nX*(long)pData2->nX;
	lA2 = (lA2+500)/1000;
	lR += (lR>0)?lA2/2:-lA2/2;
	lX += (lX>0)?lA2/2:-lA2/2;

	result.nR = (short)(lR/lA2);
	result.nX = (short)(lX/lA2);

	return result;
}

void CMyAppDMR4::OnInitParams(void)
{
	CMyAppDMR::OnInitParams();
	g_pDeviceParam = (DEVICEPARAM_DMR4*)&g_deviceParam.wReserved[0];
	MemoryClear((WORD*)&g_analogData,SIZEOFWORD(g_analogData));
	MemoryClear((WORD*)&g_analogDataExt,SIZEOFWORD(g_analogDataExt));
#ifdef BREAKERINTERFACE
	g_pDeviceParam->wToggleAlarmKM = TOGGLE_ON;
	g_pDeviceParam->wToggleAlarmClose = TOGGLE_ON;
	g_pDeviceParam->wToggleAlarmOpen = TOGGLE_ON;
#endif/*BREAKERINTERFACE*/
	g_pDeviceParam->wToggleAlarmCT = TOGGLE_ON;
	g_pDeviceParam->wToggleAlarmPT = TOGGLE_ON;
	g_pDeviceParam->wModeProtect = MODEPROTECT_3P;
	g_pDeviceParam->wModePT = MODEPT_WYE;
	g_pDeviceParam->wScaleCT = 40;
	g_pDeviceParam->wScalePT = 100;
	g_pDeviceParam->wScale2IM = 625;
	g_pDeviceParam->wScale2IP = 10000;
	g_pDeviceParam->wScale2Uln = 16000;
	g_pDeviceParam->wScale23I0 = 625;
	g_pDeviceParam->wScale23U0 = 16000;
	g_pDeviceParam->wScale2Ix = 10000;
	g_pDeviceParam->wScale2Ux = 16000;

	g_pDeviceParam->wModbusAddr1 = 1;				// 通讯地址1
	g_pDeviceParam->wCANBaud1 = BAUDRATE_500k;		// CAN1波特率
	g_pDeviceParam->wModbusAddr2 = 1;				// 通讯地址2
	g_pDeviceParam->wCANBaud2 = BAUDRATE_500k;		// CAN2波特率
	g_pDeviceParam->wSCIBaud = BAUDRATE_38400;		// SCI波特率
	g_pDeviceParam->wAddrIP1[0] = MAKEW(192,168);	// IP地址1
	g_pDeviceParam->wAddrIP1[1] = MAKEW(0,2);		// IP地址1
	g_pDeviceParam->wAddrMask1[0] = MAKEW(255,255);	// 子网掩码1
	g_pDeviceParam->wAddrMask1[1] = MAKEW(255,0);	// 子网掩码1
// 	g_pDeviceParam->wGateway[2];					// 网关1
	g_pDeviceParam->wAddrIP2[0] = MAKEW(192,168);	// IP地址2
	g_pDeviceParam->wAddrIP2[1] = MAKEW(0,3);		// IP地址2
	g_pDeviceParam->wAddrMask2[0] = MAKEW(255,255);	// 子网掩码2
	g_pDeviceParam->wAddrMask2[1] = MAKEW(255,0);	// 子网掩码2
// 	g_pDeviceParam->wGateway2[2];					// 网关2

#ifdef DCIN_COUNT
	g_pDeviceParam->wDCOUTLink[0] = DCLINK_NULL;
	g_pDeviceParam->wDCOUTLink[1] = DCLINK_NULL;
	g_pDeviceParam->wDCOUTLink[2] = DCLINK_NULL;
	g_pDeviceParam->wDCOUTLink[3] = DCLINK_NULL;
#endif/*DCIN_COUNT*/

#ifndef DFT_3I0
	g_pDeviceParam->wScale23I0 = g_pDeviceParam->wScale2IP;
#endif
#ifndef DFT_3U0
	g_pDeviceParam->wScale23U0 = g_pDeviceParam->wScale2Uln;
#endif
}

void CMyAppDMR4::OnInit(void)
{
	WORD wTmp[7];
	CMyAppDMR::OnInit();
#ifdef ANALOGDATA_EXT
	g_arEEPROMSub.ReadBlock(EEPROMADDR_ANALOGEXT,NULL,(WORD*)&g_analogDataExt,SIZEOFWORD(ANALOGDATAEXT));
#endif
#ifdef MODULE__LAD_H
	g_arEEPROMSub.ReadBlock(EPROMADDR_LADMEM,NULL,(WORD*)&g_lad.m_wMemory[0],32);
#endif
	BOOL bRead = g_arEEPROMSub.ReadBlock(EEPROMADDR_DEVICESTATUS,NULL,wTmp,7);
	if(bRead)
	{
		g_deviceInfo.wNumPwrup = wTmp[0];
		g_deviceInfo.wWrmStr = wTmp[1];
		g_deviceInfo.wDeviceStatus1 |= wTmp[2]&(DS1_Alarmed|DS1_Tripped);
// 		g_deviceInfo.wDeviceStatus2 |= wTmp[3]&(DS2_ErrorOpen|DS2_ErrorClose);
#ifdef _CMYPROTECT_H
		g_protect.m_dwProtectActed = ((DWORD)wTmp[3]<<16) | wTmp[4];
		g_protect.m_wProtectActedIN = wTmp[5];
		g_protect.m_wProtectActedUser = wTmp[6];
#endif/*_CMYPROTECT_H*/
	}
	switch(g_hdif.m_wPWRUPS)
	{
	case WRMSTARTS:
		g_deviceInfo.wWrmStr++;
		g_deviceInfo.wNumPwrup++;
		g_bDInfoChanged = TRUE;
		break;
	case POWERUPS:
		g_deviceInfo.wNumPwrup++;
		g_bDInfoChanged = TRUE;
		break;
	}
	m_alarmgroupCTM.OnInit();
	m_alarmgroupCTP.OnInit();
	m_alarmgroupPT.OnInit();
	m_wHardEnableLocal = BOM_NULL;
	m_wHardEnableRemote = BOM_NULL;
	m_wLADEnableLocal = BOM_NULL;
	m_wLADEnableRemote = BOM_NULL;
#ifdef _CMYDCPROCESS_H
	g_dcprocess.OnInit();
#endif/*_CMYDCPROCESS_H*/

	g_dataIa.OnInit();
	g_dataIb.OnInit();
	g_dataIc.OnInit();
	g_dataIA.OnInit();
	g_dataIB.OnInit();
	g_dataIC.OnInit();
	g_dataUa.OnInit();
	g_dataUb.OnInit();
	g_dataUc.OnInit();
	g_dataUab.OnInit();
	g_dataUbc.OnInit();
	g_dataUca.OnInit();
	g_data3I0.OnInit();
	g_data3U0.OnInit();
	g_data3I2.OnInit();
	g_data3U2.OnInit();
	g_dataF.OnInit();
	g_dataP.OnInit();
	g_dataQ.OnInit();
	g_dataPF.OnInit();
	g_dataIx.OnInit();
	g_dataUxa.OnInit();
	g_dataUxb.OnInit();
	g_dataUxc.OnInit();
	g_dataUxab.OnInit();
	g_dataUxbc.OnInit();
	g_dataUxca.OnInit();
	g_data3Ux0.OnInit();
	g_data3Ux2.OnInit();
	g_dataFx.OnInit();
	g_breaker.OnInit();
#ifdef DCIN_COUNT
	for(short i=0;i<DCIN_COUNT;i++)
	{
		g_dataDC[i].OnInit();
	}
#endif/*DCIN_COUNT*/
#ifdef ANALOGDATA_EXT
	g_breaker.m_boinfo = g_analogDataExt.boinfo;
#endif
}

void CMyAppDMR4::OnTimer1ms(void)
{
	CMyAppDMR::OnTimer1ms();
	g_breaker.OnTimer1ms();
}

void CMyAppDMR4::OnTimer10ms(void)
{
	m_wLADEnableLocal = BOM_NULL;
	m_wLADEnableRemote = BOM_NULL;
	g_breaker.m_wLockClose = 0x0000;
	g_app.HardEnableLocal((g_deviceInfo.wSwitchStatus1&BIT_LOCAL)?TRUE:FALSE);
	g_app.HardEnableRemote((g_deviceInfo.wSwitchStatus1&BIT_REMOTE)?TRUE:FALSE);
	CMyAppDMR::OnTimer10ms();
	WORD wDataIMax = GetMax(g_dataIA.m_nData,g_dataIB.m_nData,g_dataIC.m_nData);
	WORD wDataIMax100mA = (WORD)((g_dataIA.GetValueSecondaryFix(wDataIMax)+5)/10);
	g_breaker.SetDataIMax(wDataIMax,wDataIMax100mA);
	g_breaker.OnTimer10ms();
#ifdef DCOUT_COUNT
	for(short i=0;i<DCOUT_COUNT;i++)
	{
		WORD wData = 0;
		WORD wSacle = 3000;
		g_dcprocess.GetLinkData(g_pDeviceParam->wDCOUTLink[i],wData,wSacle);
		g_dcprocess.SetOUTData(i,wData,wSacle,EXADSCALE);
	}
#endif/*DCOUT_COUNT*/
	SETBIT(g_breaker.m_wLockClose==0xaaaa,g_deviceInfo.wDeviceStatus2,DS2_LockClose);

}

void CMyAppDMR4::OnTimer1000ms(void)
{
	CMyAppDMR::OnTimer1000ms();
	g_analogDataExt.boinfo = g_breaker.m_boinfo;
#ifdef ANALOGDATA_EXT
	g_arEEPROMSub.WriteBlock(EEPROMADDR_ANALOGEXT,NULL,(WORD*)&g_analogDataExt,SIZEOFWORD(ANALOGDATAEXT));
#endif
}

void CMyAppDMR4::OnWhileLoop(void)
{
	WORD wTmp[7];
	CMyAppDMR::OnWhileLoop();
#ifdef MODULE__LAD_H
	if(g_lad.m_bMemChanged)
	{
		g_arEEPROMSub.WriteBlock(EPROMADDR_LADMEM,NULL,(WORD*)&g_lad.m_wMemory[0],32);
		g_lad.m_bMemChanged = FALSE;
	}
#endif
	if(g_bDInfoChanged)
	{
		g_bDInfoChanged = FALSE;
		wTmp[0] = g_deviceInfo.wNumPwrup;
		wTmp[1] = g_deviceInfo.wWrmStr;
		wTmp[2] = g_deviceInfo.wDeviceStatus1;
#ifdef _CMYPROTECT_H
		wTmp[3] = g_protect.m_dwProtectActed>>16;
		wTmp[4] = g_protect.m_dwProtectActed;
		wTmp[5] = g_protect.m_wProtectActedIN;
		wTmp[6] = g_protect.m_wProtectActedUser;
#else/*_CMYPROTECT_H*/
		wTmp[3] = 0;
		wTmp[4] = 0;
		wTmp[5] = 0;
		wTmp[6] = 0;
#endif/*_CMYPROTECT_H*/
		g_arEEPROMSub.WriteBlock(EEPROMADDR_DEVICESTATUS,NULL,wTmp,7);
	}
}

void CMyAppDMR4::OnInitDevice(void)
{
	CMyAppDMR::OnInitDevice();
	MemoryClear((WORD*)&g_breaker.m_boinfo,SIZEOFWORD(g_breaker.m_boinfo));
	MemoryClear((WORD*)&g_analogDataExt,SIZEOFWORD(g_analogDataExt));
	g_deviceInfo.wNumPwrup = 0;
	g_deviceInfo.wWrmStr = 0;
	g_bDInfoChanged = TRUE;
}

void CMyAppDMR4::OnResetDevice(void)
{
	m_alarmgroupCTM.OnReset();
	m_alarmgroupCTP.OnReset();
	m_alarmgroupPT.OnReset();
	g_breaker.OnReset();
	g_deviceInfo.wDeviceStatus2 &= 0xffff^DS2_ErrorClose;
	g_deviceInfo.wDeviceStatus2 &= 0xffff^DS2_ErrorOpen;
	CMyAppDMR::OnResetDevice();
}

void CMyAppDMR4::OnUpdateDevice(WORD* pData)
{
#ifndef DFT_3I0
	g_pDeviceParam->wScale23I0 = g_pDeviceParam->wScale2IP;
#endif
#ifndef DFT_3U0
	g_pDeviceParam->wScale23U0 = g_pDeviceParam->wScale2Uln;
#endif
	CMyAppDMR::OnUpdateDevice(pData);
}

WORD CMyAppDMR4::GetBOStatus(void* pBreaker)
{
	WORD wStatus = BOSTATUS_NULL;

// 	WORD wStatus = BOSTATUS_OPENED;
	if((g_deviceInfo.wSwitchStatus1&0x0003)==0x01) wStatus = BOSTATUS_CLOSED;
	else if((g_deviceInfo.wSwitchStatus1&0x0003)==0x02) wStatus = BOSTATUS_OPENED;

	return wStatus;
}

void CMyAppDMR4::SetBOErrorCloseFlag(void* pBreaker,BOOL bError)
{
	SETBIT(bError,g_deviceInfo.wDeviceStatus2,DS2_ErrorClose);
}

void CMyAppDMR4::SetBOErrorOpenFlag(void* pBreaker,BOOL bError)
{
	SETBIT(bError,g_deviceInfo.wDeviceStatus2,DS2_ErrorOpen);
}

void CMyAppDMR4::AddBOEvent(void* pBreaker,WORD wEventType,WORD wEventCode,WORD wEventData)
{
	g_eventTable.AddEvent(wEventType,wEventCode,wEventData);
}

BOOL CMyAppDMR4::IsCTMBreak(void)
{
	return m_alarmgroupCTM.IsAlarmStarted();
}

BOOL CMyAppDMR4::IsCTPBreak(void)
{
	return m_alarmgroupCTP.IsAlarmStarted();
}

BOOL CMyAppDMR4::IsPTBreak(void)
{
	return m_alarmgroupPT.IsAlarmStarted();
}

void CMyAppDMR4::SetBreakerOperateMode(void)
{
	BOOL bEnableLocal = FALSE;
	BOOL bEnableRemote = FALSE;
	if(m_wLADEnableLocal==BOM_ENABLE||(m_wLADEnableLocal==BOM_NULL&&m_wHardEnableLocal==BOM_ENABLE)) bEnableLocal = TRUE;
	if(m_wLADEnableRemote==BOM_ENABLE||(m_wLADEnableRemote==BOM_NULL&&m_wHardEnableRemote==BOM_ENABLE)) bEnableRemote = TRUE;
	SETBIT(bEnableLocal,g_deviceInfo.wDeviceStatus2,DS2_EnableLocal);
	SETBIT(bEnableRemote,g_deviceInfo.wDeviceStatus2,DS2_EnableRemote);
}

void CMyAppDMR4::HardEnableLocal(BOOL bEnable)
{
	m_wHardEnableLocal = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMR4::HardEnableRemote(BOOL bEnable)
{
	m_wHardEnableRemote = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMR4::LADEnableLocal(BOOL bEnable)
{
	m_wLADEnableLocal = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMR4::LADEnableRemote(BOOL bEnable)
{
	m_wLADEnableRemote = (bEnable==TRUE)?BOM_ENABLE:BOM_DISABLE;
	SetBreakerOperateMode();
}

void CMyAppDMR4::iiiOnSetDataMetrics(void)
{
	CMyAppDMR::iiiOnSetDataMetrics();
	g_pDeviceParam = (DEVICEPARAM_DMR4*)&g_deviceParam.wReserved[0];
	DWORD dwScaleSecondary = (DWORD)g_pDeviceParam->wScale2IM*(DWORD)g_pDeviceParam->wScale2Uln*3/100;
	DWORD dwScale = (DWORD)g_pDeviceParam->wScaleCT*(DWORD)g_pDeviceParam->wScalePT;
	g_dataIa.SetMetrics(g_pDeviceParam->wScale2IM,g_pDeviceParam->wScaleCT,"Ia","A");
	g_dataIb.SetMetrics(g_pDeviceParam->wScale2IM,g_pDeviceParam->wScaleCT,"Ib","A");
	g_dataIc.SetMetrics(g_pDeviceParam->wScale2IM,g_pDeviceParam->wScaleCT,"Ic","A");
	g_dataIA.SetMetrics(g_pDeviceParam->wScale2IP,g_pDeviceParam->wScaleCT,"IA","A");
	g_dataIB.SetMetrics(g_pDeviceParam->wScale2IP,g_pDeviceParam->wScaleCT,"IB","A");
	g_dataIC.SetMetrics(g_pDeviceParam->wScale2IP,g_pDeviceParam->wScaleCT,"IC","A");
	g_dataUa.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Ua","V");
	g_dataUb.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Ub","V");
	g_dataUc.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Uc","V");
	g_dataUab.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Uab","V");
	g_dataUbc.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Ubc","V");
	g_dataUca.SetMetrics(g_pDeviceParam->wScale2Uln,g_pDeviceParam->wScalePT,"Uca","V");
	g_data3I2.SetMetrics(g_pDeviceParam->wScale2IP,1,"3I2","A");
	g_data3U2.SetMetrics(g_pDeviceParam->wScale2Uln,1,"3U2","V");
	g_data3I0.SetMetrics(g_pDeviceParam->wScale23I0,1,"3I0","A");
	g_data3U0.SetMetrics(g_pDeviceParam->wScale23U0,1,"3U0","V");
	g_dataF.SetMetrics(3000,1,"F","Hz");
	g_dataP.SetMetrics(dwScaleSecondary,dwScale,"P","W");
	g_dataQ.SetMetrics(dwScaleSecondary,dwScale,"Q","Var");
	g_dataPF.SetMetrics(3000,1,"PF","%");
	g_dataIx.SetMetrics(g_pDeviceParam->wScale2Ix,1,"Ix","A");
	g_dataUxa.SetMetrics(g_pDeviceParam->wScale2Ux,1,"Uxa","V");
	g_dataUxb.SetMetrics(g_pDeviceParam->wScale2Ux,1,"Uxb","V");
	g_dataUxc.SetMetrics(g_pDeviceParam->wScale2Ux,1,"Uxc","V");
	g_dataUxab.SetMetrics(g_pDeviceParam->wScale2Ux,1,"Uxab","V");
	g_dataUxbc.SetMetrics(g_pDeviceParam->wScale2Ux,1,"Uxbc","V");
	g_dataUxca.SetMetrics(g_pDeviceParam->wScale2Ux,1,"Uxca","V");
	g_data3Ux0.SetMetrics(g_pDeviceParam->wScale2Ux,1,"3Ux0","V");
	g_data3Ux2.SetMetrics(g_pDeviceParam->wScale2Ux,1,"3Ux2","V");
	g_dataFx.SetMetrics(3000,1,"Fx","Hz");
#ifdef DCIN_COUNT
	for(short i=0;i<DCIN_COUNT;i++) g_dataDC[i].SetMetrics(3000,1,NULL,NULL);
#endif/*DCIN_COUNT*/
}

void CMyAppDMR4::iiiOnCalculateData(void)
{
	CMyAppDMR::iiiOnCalculateData();
	// 硬件通道计算:
#ifdef DCIN_COUNT
	for(short i=0;i<DCIN_COUNT;i++) g_dataDC[i].SetData(GetDataDC(i));
#endif/*DCIN_COUNT*/
#ifdef DFT_IA
	g_measure.SetData(DFT_IA,g_dataIA);
#endif
#ifdef DFT_IB
	g_measure.SetData(DFT_IB,g_dataIB);
#endif
#ifdef DFT_IC
	g_measure.SetData(DFT_IC,g_dataIC);
#endif
#ifdef DFT_Ia
	g_measure.SetData(DFT_Ia,g_dataIa);
#else
	short nRa = short(long(g_dataIA.m_nR)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	short nXa = short(long(g_dataIA.m_nX)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	short nAa = short(long(g_dataIA.m_nData)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	g_dataIa.SetData(nRa,nXa,nAa);
#endif
#ifdef DFT_Ib
	g_measure.SetData(DFT_Ib,g_dataIb);
#endif
#ifdef DFT_Ic
	g_measure.SetData(DFT_Ic,g_dataIc);
#else
	short nRc = short(long(g_dataIC.m_nR)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	short nXc = short(long(g_dataIC.m_nX)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	short nAc = short(long(g_dataIC.m_nData)*g_pDeviceParam->wScale2IP/g_pDeviceParam->wScale2IM);
	g_dataIc.SetData(nRc,nXc,nAc);
#endif
// #ifdef DFT_Ua
// 	g_measure.SetData(DFT_Ua,g_dataUa);
// #endif
// // #ifdef DFT_Ub
// // 	g_measure.SetData(DFT_Ub,g_dataUb);
// // #endif
// #ifdef DFT_Uc
// 	g_measure.SetData(DFT_Uc,g_dataUc);
// #endif
// 	if(g_pDeviceParam->wModePT==MODEPT_UAC)
// 		g_dataUb.SetData(-g_dataUa.m_nR-g_dataUc.m_nR,-g_dataUa.m_nX-g_dataUc.m_nX);
// #ifdef DFT_Ub
// 	else g_measure.SetData(DFT_Ub,g_dataUb);
// #endif

	if(g_pDeviceParam->wModePT==MODEPT_UAC)
	{
#ifndef DFT_Ua
#error "Uac必须由Ua通道输入"
#endif
		g_measure.SetData(DFT_Ua,g_dataUca);
		g_dataUca.m_nR = -g_dataUca.m_nR;
		g_dataUca.m_nX = -g_dataUca.m_nX;
		Complex DataUab,DataUca;
		DataUca.nR = g_dataUca.m_nR;
		DataUca.nX = g_dataUca.m_nX;
		DataUab = ComplexDiv(&DataUca,(Complex*)&c_stW);
		g_dataUab.SetData(DataUab.nR,DataUab.nX);
		g_dataUbc.SetData(-g_dataUab.m_nR-g_dataUca.m_nR,-g_dataUab.m_nX-g_dataUca.m_nX);

		Complex DataUa;
		DataUa = ComplexDiv(&DataUca,(Complex*)&c_stW_1);
		g_dataUa.SetData(DataUa.nR,DataUa.nX);
		g_dataUc.SetData(g_dataUca.m_nR+g_dataUa.m_nR,g_dataUca.m_nX+g_dataUa.m_nX);
		g_dataUb.SetData(-g_dataUa.m_nR-g_dataUc.m_nR,-g_dataUa.m_nX-g_dataUc.m_nX);
	}
	else
	{
#ifdef DFT_Ua
		g_measure.SetData(DFT_Ua,g_dataUa);
#endif
#ifdef DFT_Ub
		g_measure.SetData(DFT_Ub,g_dataUb);
#endif
#ifdef DFT_Uc
		g_measure.SetData(DFT_Uc,g_dataUc);
#endif

#ifdef DFT_Uab
		g_measure.SetData(DFT_Uab,g_dataUab);
#else
		g_dataUab.SetData(g_dataUa.m_nR-g_dataUb.m_nR,g_dataUa.m_nX-g_dataUb.m_nX);
#endif

#ifdef DFT_Ubc
		g_measure.SetData(DFT_Ubc,g_dataUbc);
#endif
#ifdef DFT_Ucb
		g_measure.SetData(DFT_Ucb,g_dataUbc);
		g_dataUbc.m_nR = -g_dataUbc.m_nR;
		g_dataUbc.m_nX = -g_dataUbc.m_nX;
#endif

#ifndef DFT_Ubc
#ifndef DFT_Ucb
		g_dataUbc.SetData(g_dataUb.m_nR-g_dataUc.m_nR,g_dataUb.m_nX-g_dataUc.m_nX);
#endif
#endif
		g_dataUca.SetData(-g_dataUab.m_nR-g_dataUbc.m_nR,-g_dataUab.m_nX-g_dataUbc.m_nX);
	}

#ifdef DFT_3I0
	g_measure.SetData(DFT_3I0,g_data3I0);
#endif

#ifdef DFT_3U0
	g_measure.SetData(DFT_3U0,g_data3U0);
#endif
#ifdef DFT_Ix
	g_measure.SetData(DFT_Ix,g_dataIx);
#endif

#ifdef DFT_Uxa
	g_measure.SetData(DFT_Uxa,g_dataUxa);
#endif

#ifdef DFT_Uxb
	g_measure.SetData(DFT_Uxb,g_dataUxb);
#endif

#ifdef DFT_Uxc
	g_measure.SetData(DFT_Uxc,g_dataUxc);
#endif

#ifdef DFT_Uxab
	g_measure.SetData(DFT_Uxab,g_dataUxab);
#else
	g_dataUxab.SetData(g_dataUxa.m_nR-g_dataUxb.m_nR,g_dataUxa.m_nX-g_dataUxb.m_nX);
#endif

#ifdef DFT_Uxbc
	g_measure.SetData(DFT_Uxbc,g_dataUxbc);
#endif
#ifdef DFT_Uxcb
	g_measure.SetData(DFT_Uxcb,g_dataUxbc);
	g_dataUxbc.m_nR = -g_dataUxbc.m_nR;
	g_dataUxbc.m_nX = -g_dataUxbc.m_nX;
#endif

#ifndef DFT_Uxbc
#ifndef DFT_Uxcb
	g_dataUxbc.SetData(g_dataUxb.m_nR-g_dataUxc.m_nR,g_dataUxb.m_nX-g_dataUxc.m_nX);
#endif
#endif

#ifndef DFT_IB
	g_dataIB.SetData(-(g_dataIA.m_nR+g_dataIC.m_nR),-(g_dataIA.m_nX+g_dataIC.m_nX));
#endif

#ifndef DFT_Ib
	g_dataIb.SetData(-(g_dataIa.m_nR+g_dataIc.m_nR),-(g_dataIa.m_nX+g_dataIc.m_nX));
#endif


// 软件通道计算:
// 	g_dataUca.SetData(-g_dataUab.m_nR-g_dataUbc.m_nR,-g_dataUab.m_nX-g_dataUbc.m_nX);

#ifndef DFT_3I0
	g_data3I0.SetData(g_dataIA.m_nR+g_dataIB.m_nR+g_dataIC.m_nR,g_dataIA.m_nX+g_dataIB.m_nX+g_dataIC.m_nX);
#endif

#ifndef DFT_3U0
	g_data3U0.SetData(g_dataUa.m_nR+g_dataUb.m_nR+g_dataUc.m_nR,g_dataUa.m_nX+g_dataUb.m_nX+g_dataUc.m_nX);
#endif
	g_data3I2.SetData(CMyMeasure::CalculateNegSeq(&g_dataIA,&g_dataIB,&g_dataIC));

	g_data3U2.SetData(CMyMeasure::CalculateNegSeqEx(&g_dataUab,&g_dataUbc));

	g_dataUxca.SetData(-(g_dataUxab.m_nR+g_dataUxbc.m_nR),-(g_dataUxab.m_nX+g_dataUxbc.m_nX));
	g_data3Ux0.SetData(g_dataUxa.m_nR+g_dataUxb.m_nR+g_dataUxc.m_nR,g_dataUxa.m_nX+g_dataUxb.m_nX+g_dataUxc.m_nX);
	g_data3Ux2.SetData(CMyMeasure::CalculateNegSeqEx(&g_dataUxab,&g_dataUxbc));
	g_dataF.SetData(g_hdif.GetFreqINT1());
	g_dataFx.SetData(g_hdif.GetFreqINT2());
	// 功率电度计算:
#ifdef ANALOGDATA_EXT
	CMyPQPhQh pqphqh;
	pqphqh.Calculate(&g_dataIa,&g_dataIb,&g_dataIc,&g_dataUa,&g_dataUb,&g_dataUc,g_pDeviceParam->wScale2IM,g_pDeviceParam->wScale2Uln,FALSE);
	g_dataP.SetData(pqphqh.m_nPabc);
	g_dataQ.SetData(pqphqh.m_nQabc);
	g_dataPF.SetData(pqphqh.m_nPFabc);
	SETBIT(g_dataP.m_nData<0,g_deviceInfo.wDeviceStatus2,DS2_DirectP);
	SETBIT(g_dataQ.m_nData<0,g_deviceInfo.wDeviceStatus2,DS2_DirectQ);
	g_analogDataExt.dwDataPhImpW10ms += pqphqh.m_dwPhImpW10ms;
	g_analogDataExt.dwDataQhImpW10ms += pqphqh.m_dwQhImpW10ms;
	g_analogDataExt.dwDataPhExpW10ms += pqphqh.m_dwPhExpW10ms;
	g_analogDataExt.dwDataQhExpW10ms += pqphqh.m_dwQhExpW10ms;
	if(g_analogDataExt.dwDataPhImpW10ms>=36000000L)
	{
		g_analogDataExt.dwDataPhImp++;
		g_analogDataExt.dwDataPhImpW10ms -= 36000000L;
	}
	if(g_analogDataExt.dwDataQhImpW10ms>=36000000L)
	{
		g_analogDataExt.dwDataQhImp++;
		g_analogDataExt.dwDataQhImpW10ms -= 36000000L;
	}
	if(g_analogDataExt.dwDataPhExpW10ms>=36000000L)
	{
		g_analogDataExt.dwDataPhExp++;
		g_analogDataExt.dwDataPhExpW10ms -= 36000000L;
	}
	if(g_analogDataExt.dwDataQhExpW10ms>=36000000L)
	{
		g_analogDataExt.dwDataQhExp++;
		g_analogDataExt.dwDataQhExpW10ms -= 36000000L;
	}
#endif
}

void CMyAppDMR4::iiiOnRefreshData(void)
{
	CMyAppDMR::iiiOnRefreshData();
	g_analogData.wDataIa = (WORD)g_dataIa.RefreshData(FALSE);
	g_analogData.wDataIb = (WORD)g_dataIb.RefreshData(FALSE);
	g_analogData.wDataIc = (WORD)g_dataIc.RefreshData(FALSE);
	g_analogData.wDataIA = (WORD)g_dataIA.RefreshData(FALSE);
	g_analogData.wDataIB = (WORD)g_dataIB.RefreshData(FALSE);
	g_analogData.wDataIC = (WORD)g_dataIC.RefreshData(FALSE);
	g_analogData.wDataUa = (WORD)g_dataUa.RefreshData(FALSE);
	g_analogData.wDataUb = (WORD)g_dataUb.RefreshData(FALSE);
	g_analogData.wDataUc = (WORD)g_dataUc.RefreshData(FALSE);
	g_analogData.wDataUab = (WORD)g_dataUab.RefreshData(FALSE);
	g_analogData.wDataUbc = (WORD)g_dataUbc.RefreshData(FALSE);
	g_analogData.wDataUca = (WORD)g_dataUca.RefreshData(FALSE);
	g_analogData.wData3I2 = (WORD)g_data3I2.RefreshData(FALSE);
	g_analogData.wData3U2 = (WORD)g_data3U2.RefreshData(FALSE);
	g_analogData.wData3I0 = (WORD)g_data3I0.RefreshData(FALSE);
	g_analogData.wData3U0 = (WORD)g_data3U0.RefreshData(FALSE);
	g_analogData.wDataF = (WORD)g_dataF.RefreshData(FALSE);
	g_analogData.nDataP = g_dataP.RefreshData(TRUE);
	g_analogData.nDataQ = g_dataQ.RefreshData(TRUE);
	g_analogData.nDataPF = g_dataPF.RefreshData(TRUE);
	g_analogData.wDataIx = (WORD)g_dataIx.RefreshData(FALSE);
	g_analogData.wDataUxa = (WORD)g_dataUxa.RefreshData(FALSE);
	g_analogData.wDataUxb = (WORD)g_dataUxb.RefreshData(FALSE);
	g_analogData.wDataUxc = (WORD)g_dataUxc.RefreshData(FALSE);
	g_analogData.wDataUxab = (WORD)g_dataUxab.RefreshData(FALSE);
	g_analogData.wDataUxbc = (WORD)g_dataUxbc.RefreshData(FALSE);
	g_analogData.wDataUxca = (WORD)g_dataUxca.RefreshData(FALSE);
	g_analogData.wData3Ux0 = (WORD)g_data3Ux0.RefreshData(FALSE);
	g_analogData.wData3Ux2 = (WORD)g_data3Ux2.RefreshData(FALSE);
	g_analogData.wDataFx = (WORD)g_dataFx.RefreshData(FALSE);
#ifdef DCIN_COUNT
	g_analogData.wDataDC[0] = (WORD)g_dataDC[0].RefreshData(TRUE);
	g_analogData.wDataDC[1] = (WORD)g_dataDC[1].RefreshData(TRUE);
	g_analogData.wDataDC[2] = (WORD)g_dataDC[2].RefreshData(TRUE);
	g_analogData.wDataDC[3] = (WORD)g_dataDC[3].RefreshData(TRUE);
#endif/*DCIN_COUNT*/
}

void CMyAppDMR4::iiiOnAlarmDetect(void)
{
	CMyAppDMR::iiiOnAlarmDetect();
#ifndef VIRTUAL_CTM
	m_alarmgroupCTM.ExeDetect(g_dataIa,g_dataIb,g_dataIc,MODECT_3CT,g_pDeviceParam->wToggleAlarmCT,EVENTCODE_ALARMCTMA);
#endif
	m_alarmgroupCTP.ExeDetect(g_dataIA,g_dataIB,g_dataIC,MODECT_3CT,g_pDeviceParam->wToggleAlarmCT,EVENTCODE_ALARMCTPA);
	WORD wDataIMax = GetMax(g_dataIA.m_nData,g_dataIB.m_nData,g_dataIC.m_nData);
	m_alarmgroupPT.ExeDetect(g_dataUa,g_dataUb,g_dataUc,g_dataUab,g_dataUbc,g_dataUca,g_pDeviceParam->wModePT,wDataIMax,g_pDeviceParam->wToggleAlarmPT,EVENTCODE_ALARMPT3);
#ifndef VIRTUAL_CTM
	SETBIT(m_alarmgroupCTM.IsAlarmed(),g_deviceInfo.wDeviceStatus2,DS2_AlarmCTM);
#endif
	SETBIT(m_alarmgroupCTP.IsAlarmed(),g_deviceInfo.wDeviceStatus2,DS2_AlarmCTP);
	SETBIT(m_alarmgroupPT.IsAlarmed(),g_deviceInfo.wDeviceStatus2,DS2_AlarmPT);
#ifdef BREAKERINTERFACE
	g_breaker.ExeDetect(g_pDeviceParam->wToggleAlarmKM,g_pDeviceParam->wToggleAlarmClose,g_pDeviceParam->wToggleAlarmOpen);
	SETBIT(g_breaker.IsAlarmedKM(),g_deviceInfo.wDeviceStatus2,DS2_AlarmKM);
	SETBIT(g_breaker.IsAlarmedClose(),g_deviceInfo.wDeviceStatus2,DS2_AlarmClose);
	SETBIT(g_breaker.IsAlarmedOpen(),g_deviceInfo.wDeviceStatus2,DS2_AlarmOpen);
#endif/*BREAKERINTERFACE*/
}

void CMyAppDMR4::iiiOnRelayOut(void)
{
	CMyAppDMR::iiiOnRelayOut();
#ifdef _CMYPROTECT_H
	g_breaker.m_lockProtect.Unlock1();
	g_breaker.m_lockProtect.Unlock2();
	if(g_protect.m_wProtectOpenFlag==0xaaaa)
	{
		g_breaker.m_lockProtect.Unlock3();
		g_breaker.ExecuteOpen(BOMODE_PROTECT);
		g_breaker.m_lockProtect.Lock3();
	}
	else if(g_protect.m_wProtectCloseFlag==0xaaaa)
	{
		g_breaker.m_lockProtect.Unlock3();
		g_breaker.ExecuteClose(BOMODE_PROTECT);
		g_breaker.m_lockProtect.Lock3();
	}
	g_breaker.m_lockProtect.Lock2();
	g_breaker.m_lockProtect.Lock1();
#endif/*_CMYPROTECT_H*/
}

