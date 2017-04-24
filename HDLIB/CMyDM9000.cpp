#include <Main.h>

// #ifndef BASEADDR
void CMyDM9000::SetProperty(DWORD dwBaseAddr,WORD wSpeedMode)
{
	m_dwBaseAddr = dwBaseAddr;
	m_wSpeedMode = wSpeedMode;
}
// #endif

void CMyDM9000::outW(DWORD dwAddr,WORD wData)
{
// 	asm(" RPT #12 || NOP");
	(*((volatile WORD *)dwAddr)) = wData;
}

WORD CMyDM9000::inW(DWORD dwAddr)
{
// 	asm(" RPT #12 || NOP");
	return (*((volatile WORD *)dwAddr));
}

void CMyDM9000::OnInitHardware(void)
{
	DelayOnce(1000);
	g_hdif.ETRestH(this);
	DelayOnce(1000);
	g_hdif.ETRestL(this);
	DelayOnce(30000);
	g_hdif.ETRestH(this);
	DelayOnce(1000);
}

BYTE CMyDM9000::ior(BYTE Reg)
{
	BYTE Result;
	outW(m_dwBaseAddr,(WORD)Reg);
	Result = inW(m_dwBaseAddr+1)&0x00FF;

	return Result;
}

void CMyDM9000::iow(BYTE Reg, WORD wData)
{
	outW(m_dwBaseAddr,(WORD)Reg);
	outW(m_dwBaseAddr+1,wData);
}

void CMyDM9000::ModifyAddrMac(WORD* pMACAddr)
{
	WORD i;
	for(i = 0; i < 6; i++) iow(DM_PAR + i, pMACAddr[i]&0xff);
	for(i = 0; i < 8; i++) iow(DM_MAR + i, 0x00);
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
	iow(DM_EPCR, 0x08);			// 清除标志位
}

void CMyDM9000::OnInitStatus(void)
{
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
	iow(DM_TCR2,0x90);
// 	iow(DM_TCR2,0x10);	// LED模式0

	iow(DM_ETXCSR,0x83);
	iow(DM_SMCR,0x00);//特殊功能寄存器
// 	ModifyAddrMac(g_hdif.GetMacAddr6(this));
	iow(DM_IMR,0x81);
}

void CMyDM9000::OnInit(WORD wSpeedMode)
{
	m_wSpeedMode = wSpeedMode;
	Reset();
	PHY_Write(0,0x8000);
	DelayOnce(50);
	PHY_Write(16,0x404);
	PHY_Write(4,0x05E1);
	OnInitStatus();
}

WORD CMyDM9000::RcvFrame(WORD* pwBuff,WORD wCountByteRcv)
{
	WORD i;

	WORD wRcvByte = 0,wRcvWORD;

	iow(DM_IMR,0x80);
	if(ior(DM_ISR) & 0x01) iow(DM_ISR, 0x01);
	BYTE Rx_Ready = ior(DM_MRCMDX);
	Rx_Ready = inW(m_dwBaseAddr+1)&0x03;
	DelayOnce(20);

	if(Rx_Ready == 0x01)
	{
		outW(m_dwBaseAddr,DM_MRCMD);
		DelayOnce(20);
		WORD wRxStatus = inW(m_dwBaseAddr+1);
		DelayOnce(20);
		wRcvByte = inW(m_dwBaseAddr+1);

		wRcvWORD = (wRcvByte+1)/2;
		if(!(wRxStatus&0xBF00))
		{ for(i=0;i<wRcvWORD;i++) *pwBuff++ = inW(m_dwBaseAddr+1); }
		else
		{ for(i=0;i<wRcvWORD;i++) inW(m_dwBaseAddr+1); return 0; }
	}
	else if(Rx_Ready)
	{
		iow(DM_NCR, 0x03);	/* NCR REG. 00 RST Bit [0] = 1 reset on, and LBK Bit [2:1] = 01b MAC loopback on */
		DelayOnce(20);		/* wait > 10us for a software-RESET ok */
		iow(DM_NCR, 0x00);	/* normalize */
		iow(DM_NCR, 0x03);
		DelayOnce(20);
		iow(DM_NCR, 0x00);
		/* program operating registers~ */
		iow(DM_NCR,0x00);   /* NCR REG. 00 enable the chip functions (and disable this MAC loopback mode back to normal) */
		iow(DM_BPTR,0x3F);
		iow(DM_FCTR,0x3A);
		iow(DM_FCR,0x29);
		iow(DM_WUCR,0x00);
		iow(DM_TCR2,0x90);
		iow(DM_ETXCSR,0x83);
		iow(DM_IMR,0x81);
		iow(DM_RCR,0x39);
	}

	return (wRcvByte<wCountByteRcv)?wRcvByte:wCountByteRcv;
}

WORD CMyDM9000::SndFrame(WORD* pwBuff,WORD wCountByteSnd)
{
	WORD wLength;
	if(wCountByteSnd==0) return 0;

	iow(DM_IMR,0x80);							//禁止中断
	wLength = (wCountByteSnd+1)/2;
	iow(DM_TXPLL,wCountByteSnd&0x00FF);
	iow(DM_TXPLH,(wCountByteSnd>>8)&0x00FF);
	
	outW(m_dwBaseAddr,DM_MWCMD);
	
	for(WORD i=0;i<wLength;i++) outW(m_dwBaseAddr+1,pwBuff[i]);

	iow(DM_TCR,0x01);	//启动发送

// 	while((ior(DM_NSR)&0x0c)==0x00) DelayOnce(20);
// 	while((ior(DM_NSR)&0x0c)!=0x00) ;
	DelayOnce(100);
	iow(DM_NSR,0x2C);	//清除中断标志
	iow(DM_IMR,0x81);

	return wCountByteSnd;
}

BOOL CMyDM9000::GetLinkStatus(void)
{
	BYTE LinkStatus = ior(DM_NSR);
	return (LinkStatus&0x40)?TRUE:FALSE;
}

