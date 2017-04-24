#ifndef CMYDM9000__H
#define CMYDM9000__H

//
// Control and Status register offsets
//
#define DM_NCR			0x00
#define DM_NSR			0x01
#define DM_TCR			0x02
#define DM_TSRI			0x03
#define DM_TSRII		0x04
#define DM_RCR			0x05
#define DM_RSR			0x06
#define DM_ROCR			0x07
#define DM_BPTR			0x08
#define DM_FCTR			0x09
#define DM_FCR			0x0a
#define DM_EPCR			0x0b
#define DM_EPAR			0x0c
#define DM_EPDRL		0x0d
#define DM_EPDRH		0x0e
#define DM_WUCR			0x0f
#define DM_PAR			0x10
#define DM_MAR			0x16
#define DM_GPCR			0x1e
#define DM_GPR			0x1f
#define DM_TRPAL		0x22
#define DM_TRPAH		0x23
#define DM_RWPAL		0x24
#define DM_RWPAH		0x25
#define DM_VIDL			0x28
#define DM_VIDH			0x29
#define DM_PIDL			0x2a
#define DM_PIDH			0x2b
#define DM_CHIPR		0x2c
#define DM_TCR2			0x2d
#define DM_SMCR			0x2f
#define DM_ETXCSR		0x30
#define DM_MRCMDX		0xf0
#define DM_MRCMD		0xf2
#define DM_MDRAL		0xf4
#define DM_MDRAH		0xf5
#define DM_MWCMDX		0xf6
#define DM_MWCMD		0xf8
#define DM_MDWAL		0xfa
#define DM_MDWAH		0xfb
#define DM_TXPLL		0xfc
#define DM_TXPLH		0xfd
#define DM_ISR			0xfe
#define DM_IMR			0xff

// NCR (Network Control Register)
#define NCR_EXT_PHY		(1 << 7)     // 1 ==> external PHY, 0 ==> internal
#define NCR_WAKEEN		(1 << 6)     // enable wakeup events
#define NCR_FCOL		(1 << 4)     // force collision mode (test)
#define NCR_FDX			(1 << 3)     // full duplex (read-only for internal phy)
#define NCR_LBK_NOR		(0 << 1)     // loopback off
#define NCR_LBK_MAC		(1 << 1)     // MAC loopback
#define NCR_LBK_PHY		(2 << 1)     // PHY loopback
#define NCR_RST			(1 << 0)     // Reset (auto-clears after 10us)

// NSR (Network Status Register)
#define NSR_SPEED		(1 << 7)     // 0 = 100Mbps, 1 = 10Mbps
#define NSR_LINKST		(1 << 6)     // link status (1 = okay)
#define NSR_WAKEST		(1 << 5)     // wake status (clear by read)
#define NSR_TX2END		(1 << 3)     // TX packet 2 complete
#define NSR_TX1END		(1 << 2)     // TX packet 1 complete
#define NSR_RXOV		(1 << 1)     // RX overflow

// TCR (TX Control Register)
#define TCR_TJDIS		(1 << 6)     // TX jabber disable
#define TCR_EXCECM		(1 << 5)     // 0 = abort after 15 collisions
#define TCR_PAD_DIS2	(1 << 4)
#define TCR_CRC_DIS2	(1 << 3)
#define TCR_PAD_DIS1	(1 << 2)
#define TCR_CRC_DIS1	(1 << 1)
#define TCR_TXREQ		(1 << 0)

// TSR (TX Status Register)
#define TSR_TJTO		(1 << 7)
#define TSR_LC			(1 << 6)
#define TSR_NC			(1 << 5)
#define TSR_LCOL		(1 << 4)
#define TSR_COL			(1 << 3)
#define TSR_EC			(1 << 2)

// RCR (RX Control Register)
#define RCR_WTDIS		(1 << 6)
#define RCR_DIS_LONG	(1 << 5)
#define RCR_DIS_CRC		(1 << 4)
#define RCR_ALL			(1 << 3)
#define RCR_RUNT		(1 << 2)
#define RCR_PRMSC		(1 << 1)
#define RCR_RXEN		(1 << 0)

// RSR (RX Status Register)
#define RSR_RF			(1 << 7)
#define RSR_MF			(1 << 6)
#define RSR_LCS			(1 << 5)
#define RSR_RWTO		(1 << 4)
#define RSR_PLE			(1 << 3)
#define RSR_AE			(1 << 2)
#define RSR_CE			(1 << 1)
#define RSR_FOE			(1 << 0)

// FCR (Flow Control Register)
#define FCR_TXPO		(1 << 7)
#define FCR_TXPF		(1 << 6)
#define FCR_TXPEN		(1 << 5)
#define FCR_BKPA		(1 << 4)
#define FCR_BKPM		(1 << 3)
#define FCR_RXPS		(1 << 2)
#define FCR_RXPCS		(1 << 1)
#define FCR_FLCE		(1 << 0)

// EPCR (EEPROM & PHY Control Register)
#define EPCR_REEP		(1 << 5)
#define EPCR_WEP		(1 << 4)
#define EPCR_EPOS		(1 << 3)
#define EPCR_ERPRR		(1 << 2)
#define EPCR_ERPRW		(1 << 1)
#define EPCR_ERRE		(1 << 0)

// WCR (Wakeup Control Register)
#define WCR_LINKEN		(1 << 5)
#define WCR_SAMPLEEN	(1 << 4)
#define WCR_MAGICEN		(1 << 3)
#define WCR_LINKST		(1 << 2)
#define WCR_SAMPLEST	(1 << 1)
#define WCR_MAGIGST		(1 << 0)

// SMCR (Special Mode Control Register)
#define SMCR_SM_EN		(1 << 7)
#define SMCR_FLC		(1 << 2)
#define SMCR_FB1		(1 << 1)
#define SMCR_FB0		(1 << 0)

// ISR (Interrupt Status Register)
#define ISR_IOMODE_16	(0 << 6)
#define ISR_IOMODE_32	(1 << 6)
#define ISR_IOMODE_8	(2 << 6)
#define ISR_ROOS		(1 << 3)
#define ISR_ROS			(1 << 2)
#define ISR_PTS			(1 << 1)
#define ISR_PRS			(1 << 0)

// IMR (Interrupt Mask Register)
#define IMR_PAR			(1 << 7)
#define IMR_ROOM		(1 << 3)
#define IMR_ROM			(1 << 2)
#define IMR_PTM			(1 << 1)
#define IMR_PRM			(1 << 0)

#define DM_PHY			0x40

#define ETSTATUS_NULL		0x0000		// 不可用
#define ETSTATUS_IDLE		0x1111		// 空闲
#define ETSTATUS_HWREST		0x2222		// 硬件复位
#define ETSTATUS_SWREST		0x3333		// 软件复位
#define ETSTATUS_RCVDATA	0x4444		// 接收数据
#define ETSTATUS_RCVOK		0x5555		// 接收一帧数据OK
#define ETSTATUS_SNDDATA	0x6666		// 发送数据
#define ETSTATUS_SNDOK		0x7777		// 发送一帧数据OK

#define ETTIMEOUT			6000

#ifndef MAX_PACKET_SIZE
#define MAX_PACKET_SIZE		200 /* RX largest legal size packet with fcs & QoS */
#endif

// -------------------------- CMyDM9000 --------------------
class CMyDM9000
{
protected:
	DWORD m_dwBaseAddr;
	WORD m_wSpeedMode;
	WORD m_wMacAddr6;
public:
	void outW(DWORD wAddr,WORD wData);
	WORD inW(DWORD wAddr);
	BYTE ior(BYTE wReg);
	void iow(BYTE wReg, WORD wData);
	void Reset(void);
	void PHY_Write(WORD wPHY_Reg, WORD wData);
	void OnInitStatus(void);

public:
	void OnInitHardware(void);
	void OnInit(WORD wSpeedMode=1);		// 0x01,default:Auto-negotiation
										// 0x02:10M
										// 0x03:100M
	void SetProperty(DWORD dwBaseAddr,WORD wSpeedMode);
	void ModifyAddrMac(WORD* pMACAddr);
	WORD RcvFrame(WORD* pwBuff,WORD wCountByteRcv);
	WORD SndFrame(WORD* pwBuff,WORD wCountByteSnd);
	BOOL GetLinkStatus(void);			// FALSE:物理连接断开;TRUE:物理连接OK
// 	void SetStatus(WORD wStatus);
};

#endif/*CMYDM9000__H*/



