#include <Main.h>

//#ifndef BASEADDR
void CMyDM9000::SetProperty(DWORD dwBaseAddr,WORD wSpeedMode)
{
	m_dwBaseAddr = dwBaseAddr;
	m_wSpeedMode = wSpeedMode;
}
//#endif

void CMyDM9000::OnTimer10ms(void)
{
	if(m_wTimeout)
	{
		m_wTimeout--;
		if(m_wTimeout<3000) m_wStatus = ETSTATUS_SWREST;
		if(m_wTimeout==0)m_wStatus = ETSTATUS_HWREST;
	}
}

WORD CMyDM9000::GetStatus(void)
{
	return m_wStatus;
}

void CMyDM9000::SetStatus(WORD wStatus)
{
	m_wStatus = wStatus;
}

void CMyDM9000::outW(DWORD dwAddr,WORD wData)
{
	(*((volatile WORD *)dwAddr)) = wData;
}

WORD CMyDM9000::inW(DWORD dwAddr)
{
	return (*((volatile WORD *)dwAddr));
}

void CMyDM9000::OnInitHardware(void)
{
	DelayOnce(1000);
	GPBSET = 0x1000;
	DelayOnce(1000);
	GPBCLEAR = 0x1000;
	DelayOnce(30000);
	GPBSET = 0x1000;
	DelayOnce(1000);
}

BYTE CMyDM9000::ior(BYTE Reg)
{
	BYTE Result;
// 	DM9K_ADDR = Reg;
	outW(m_dwBaseAddr,(WORD)Reg);
	DelayOnce(20);
// 	Result = DM9K_DATA&0x00FF;
	Result = inW(m_dwBaseAddr+1)&0x00FF;

	return Result;
}

void CMyDM9000::iow(BYTE Reg, WORD wData)
{
// 	DM9K_ADDR = Reg;
	outW(m_dwBaseAddr,(WORD)Reg);
	DelayOnce(20);
// 	DM9K_DATA = wData;
	outW(m_dwBaseAddr+1,wData);
}

void CMyDM9000::ModifyAddrMac(BYTE MACAddr6)
{
	WORD i;
	BYTE MAC_Addr[6];

	MAC_Addr[0] = 0x00;
	MAC_Addr[1] = 0xff;
	MAC_Addr[2] = 0xc0;
	MAC_Addr[3] = 0xa8;
	MAC_Addr[4] = 0x80;
	MAC_Addr[5] = MACAddr6;

	for(i = 0; i < 6; i++)
		iow(DM_PAR + i, MAC_Addr[i]);

	for(i = 0; i < 8; i++)
		iow(DM_MAR + i, 0x00);
}

void CMyDM9000::Reset(void)
{
	iow(DM_GPR,0x00);	//必须的
	DelayOnce(5000);

	iow(DM_NCR,0x03);
	DelayOnce(20);
	iow(DM_NCR,0x00);
	DelayOnce(20);
	iow(DM_NCR,0x03);
	DelayOnce(20);
	iow(DM_NCR,0x00);
}

void CMyDM9000::PHY_Write(WORD wPHY_Reg, WORD wData)
{
	iow(DM_EPAR, wPHY_Reg|DM_PHY);

	iow(DM_EPDRH, (wData>>8)&0xff);
	iow(DM_EPDRL, wData&0xff);

	iow(DM_EPCR, 0x0a);
	while(ior(DM_EPCR) & 0x01);	// 等待写操作完成
//	DelayOnce(20);
	iow(DM_EPCR, 0x08);			// 清除标志位
//	DelayOnce(50);
}

void CMyDM9000::OnInitStatus(void)
{
	if(m_wStatus!=ETSTATUS_SWREST&&
		m_wStatus!=ETSTATUS_HWREST&&
		m_wStatus!=ETSTATUS_NULL)
		m_wStatus = ETSTATUS_IDLE;
	m_wTimeout = ETTIMEOUT;
// 	m_nTXLength = 0;
// 	m_nRXLength = 0;

	switch(m_wSpeedMode)
	{
	default:
	case 1: PHY_Write(0,0x1200); break;
	case 2: PHY_Write(0,0x0000); break;
	case 3: PHY_Write(0,0x2000); break;
	}

	iow(DM_NSR,0x2C);	// 清除网络状态标志位
	iow(DM_ISR,0x3F);	// 清除中断标志位
	iow(DM_NCR,0x00);	// Normal 模
	iow(DM_RCR,0x39);	// 接收控制设置
// 	iow(DM_RCR,0x3d);	// 接收控制设置
	iow(DM_TCR,0x00);	// 发送控制
	iow(DM_BPTR,0x3F);	// 接收RAM的门限值和jam pattern时间
	iow(DM_FCTR,0x3A);
	iow(DM_FCR,0x29);
	iow(DM_WUCR,0x00);
// 	iow(DM_TCR2,0x80);
	iow(DM_TCR2,0x10);	// LED模式0

	iow(DM_ETXCSR,0x83);
	iow(DM_SMCR,0x00);//特殊功能寄存器
	ModifyAddrMac(200);
	iow(DM_IMR,0x81);
}

void CMyDM9000::OnInit(WORD wSpeedMode)
{
	m_wStatus = ETSTATUS_NULL;
	m_wSpeedMode = wSpeedMode;
// 	m_wTimeout = ETTIMEOUT;

	Reset();

	PHY_Write(0,0x8000);
	DelayOnce(50);
	PHY_Write(16,0x404);
	PHY_Write(4,0x05E1);

	OnInitStatus();

	m_wStatus = ETSTATUS_IDLE;
}

WORD CMyDM9000::RcvFrame(WORD* pwBuff,WORD wCountByteRcv)
{
	WORD wTmp,wRxStatus,i;

	WORD wRcvByte,wRcvWORD;

	wRxStatus = wRcvByte = 0;

	iow(DM_IMR,0x80);

	if(ior(DM_ISR) & 0x01) iow(DM_ISR, 0x01);

	BYTE Rx_Ready = ior(DM_MRCMDX);

	Rx_Ready = DM9K_DATA&0x03;
	DelayOnce(20);

	if(Rx_Ready == 0x01)
	{
		DM9K_ADDR = DM_MRCMD;
		DelayOnce(20);
		wRxStatus = DM9K_DATA;
		DelayOnce(20);
		wRcvByte = DM9K_DATA;

/*		if(!(wRxStatus&0xBF00)&&(wRcvByte<MAX_PACKET_SIZE))
			for(i=0;i<wRcvByte;i+=2) *pwBuff++ = DM9K_DATA;
		else
		{
			for(i=0;i<wRcvByte;i+=2) wTmp = DM9K_DATA;
			wRcvByte = 0;
		}*/
		if(wRcvByte>(CONF_WSIZE_BFR*2-20)) wRcvByte = CONF_WSIZE_BFR*2-20;
		m_wTimeout = ETTIMEOUT;
		wRcvWORD = (wRcvByte+1)/2;
		if(!(wRxStatus&0xBF00))
		{ for(i=0;i<wRcvWORD;i++) *pwBuff++ = DM9K_DATA; }
		else
		{ for(i=0;i<wRcvWORD;i++) wTmp = DM9K_DATA; return 0; }
	}
	else if(Rx_Ready)
	{
//		OnInit(2);
		m_wStatus = ETSTATUS_SWREST;
		return 0;
	}

	return (wRcvByte<wCountByteRcv)?wRcvByte:wCountByteRcv;
}


WORD CMyDM9000::SndFrame(WORD* pwBuff,WORD wCountByteSnd) 
{
//	WORD wDly;
	if(wCountByteSnd==0) return 0;

//	wDly = 20;
	iow(DM_IMR,0x80);//禁止中断
	
	WORD wLength = (wCountByteSnd+1)/2;
	iow(DM_TXPLL,wCountByteSnd&0x00FF);
	iow(DM_TXPLH,(wCountByteSnd>>8)&0x00FF);

	DM9K_ADDR = DM_MWCMD;

	for(WORD i=0;i<wLength;i++)
		DM9K_DATA = pwBuff[i];
	m_wTimeout = ETTIMEOUT;
	iow(DM_TCR,0x01);	//启动发送
// 	while((ior(DM9000_REG_NSR)&0x0c==0)||dly--==0);
// 	while(!(ior(DM_NSR)&0x0c)||wDly--==0) DelayOnce(20);

	iow(DM_NSR,0x2C);//清除中断标志
	iow(DM_IMR,0x81);
	return wCountByteSnd;
}



