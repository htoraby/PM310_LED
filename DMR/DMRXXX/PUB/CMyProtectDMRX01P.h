#ifndef CMYPROTECTDMRX01P_H
#define CMYPROTECTDMRX01P_H

#include "PUB\__Output.h"

enum PROTRCTCODE_X01
{
	 PROTECT_SD = 0				//电流速断;			0
	,PROTECT_XSSD				//限时电流速断;		1
	,PROTECT_DSXGL				//定时限过流;		2
	,PROTECT_FSXGL				//反时限过流;		3
	,PROTECT_HJS				//后加速;			4
	,PROTECT_GFH				//过负荷;			5
	,PROTECT_FXDL				//负序电流;			6
	,PROTECT_LXDL				//零序电流;			7
	,PROTECT_JDSX				//单相接地选线;		8
	,PROTECT_GDY				//过电压;			9
	,PROTECT_DDY				//低电压;			10
	,PROTECT_SY					//失压;				11
	,PROTECT_FXDY				//负序电压;			12
	,PROTECT_LXDY				//零序电压;			13
	,PROTECT_FHDYGL				//复合电压过流;		14
	,PROTECT_DZJZ				//低周减载;			15
	,PROTECT_DYJL				//低压解列;			16
	,PROTECT_CHZ				//重合闸;			17
	,PROTECT_BZT				//备自投;			18
	,PROTECT_GR					//过热;				19
	,PROTECT_NGL				//逆功率;			20
	,PROTECT_QDSJGC				//启动时间过长;		21
	,PROTECT_IXDSX				//定时限Ix过流;		22
	,PROTECT_IXFSX				//反时限Ix过流;		23
};

#define IDMT_EXTR			0
#define IDMT_VERY			1
#define IDMT_NORM			2
#define IDMT_LONG			3

#define RUNSTEP_CHARGING	0
#define RUNSTEP_CHARGED		1
#define RUNSTEP_STARTUP		2


struct DEVICESETPOINT_DMRX01CONFIG
{
	WORD bConfigMotor;				//电动机保护配置;
	WORD bConfigFX;					//方向闭锁保护配置;
	WORD bConfigDY;					//低压闭锁保护配置;
};

struct DEVICESETPOINT_DMRX01
{
	WORD wMotor_SetI;				//电动机额定电流;
	WORD wMotor_SetT;				//电动机启动时间;
	//【电流速断】
	WORD wSD_SetI;					//电流定值;
	WORD wSD_SetT;					//时间定值;
	WORD wSD_SetU;					//电压定值;
	WORD wSD_TogDY;					//低压闭锁投退;
	WORD wSD_TogFX;					//方向闭锁投退;
	WORD wSD_TogAD;					//启动时定值自动加倍投退;
	//【限时电流速断】
	WORD wXSSD_SetI;				//电流定值;
	WORD wXSSD_SetT;				//时间定值;
	WORD wXSSD_SetU;				//电压定值;
	WORD wXSSD_TogDY;				//低压闭锁投退;
	WORD wXSSD_TogFX;				//方向闭锁投退;
	WORD wXSSD_TogAD;				//启动时定值自动加倍投退;
	//【定时限过流】
	WORD wDSXGL_SetI;				//电流定值;
	WORD wDSXGL_SetT;				//时间定值;
	WORD wDSXGL_SetU;				//电压定值;
	WORD wDSXGL_TogDY;				//低压闭锁投退;
	WORD wDSXGL_TogFX;				//方向闭锁投退;
	WORD wDSXGL_TogAE;				//启动时保护自动退出投退;
	//【反时限过流】
	WORD wFSXGL_SetI;				//电流定值;
	WORD wFSXGL_SetK;				//时间系数;
	WORD wFSXGL_IDMT;				//IDMT类型;
	//【后加速】
	WORD wHJS_SetI;					//电流定值;
	WORD wHJS_SetT;					//时间定值;
	//【过负荷】
	WORD wGFH_SetI;					//电流定值;
	WORD wGFH_SetT;					//时间定值;
	//【负序电流】
	WORD wFXDL_SetI;				//电流定值;
	WORD wFXDL_SetT;				//时间定值;
	//【零序电流】
	WORD wLXDL_SetI;				//电流定值;
	WORD wLXDL_SetT;				//时间定值;
	//【单相接地选线】
	WORD wJDSX_SetI;				//电流定值;
	WORD wJDSX_SetU;				//电压定值;
	WORD wJDSX_TogTHD5;				//五次谐波判据投退;
	//【过电压】
	WORD wGDY_SetU;					//电压定值;
	WORD wGDY_SetT;					//时间定值;
	//【低电压】
	WORD wDDY_SetU;					//电压定值;
	WORD wDDY_SetT;					//时间定值;
	//【失压】
	WORD wSY_SetU;					//电压定值;
	WORD wSY_SetT;					//时间定值;
	//【负序电压】
	WORD wFXDY_SetU;				//电压定值;
	WORD wFXDY_SetT;				//时间定值;
	//【零序电压】
	WORD wLXDY_SetU;				//电压定值;
	WORD wLXDY_SetT;				//时间定值;
	//【复合电压过流】
	WORD wFHDYGL_SetI;				//电流定值;
	WORD wFHDYGL_SetU;				//电压定值;
	WORD wFHDYGL_SetUFX;			//负序电压定值;
	WORD wFHDYGL_SetT;				//时间定值;
	WORD wFHDYGL_TogDY;				//低压闭锁投退;
	WORD wFHDYGL_TogFXDY;			//负序电压闭锁投退;
	//【低周减载】
	WORD wDZJZ_SetF;				//频率定值;
	WORD wDZJZ_SetT;				//时间定值;
	WORD wDZJZ_SetU;				//电压定值;
	WORD wDZJZ_SetDFDT;				//滑差定值;
	WORD wDZJZ_TogDFDT;				//滑差闭锁投退;
	WORD wDZJZ_TogDY;				//电压闭锁投退;
	WORD wDZJZ_TogDL;				//电流闭锁投退;
	//【低压解列】
	WORD wDYJL_SetU;				//电压定值;
	WORD wDYJL_SetT;				//时间定值;
	WORD wDYJL_SetDVDT;				//滑差定值;
	WORD wDYJL_TogDVDT;				//滑差闭锁投退;
	WORD wDYJL_TogDL;				//电流闭锁投退;
	//【重合闸】
	WORD wCHZ_SetT;					//时间定值;
	WORD wCHZ_SetA;					//同期角定值;
	WORD wCHZ_TogWY;				//检无压投退;
	WORD wCHZ_TogTQ;				//检同期投退;
	//【备自投】
	WORD wBZT_SetU;					//电压定值;
	WORD wBZT_SetT;					//时间定值;
	//【过热】
	WORD wGR_SetI;					//电流定值;
	WORD wGR_SetT;					//时间定值;
	WORD wGR_SetK2;					//负序分量系数;
	//【逆功率】
	WORD wNGL_SetP;					//负功率设置;
	WORD wNGL_SetT;					//时间定值;
	//【定时限Ix过流】
	WORD wIXDSX_SetI;				//电流定值;
	WORD wIXDSX_SetT;				//时间定值;
	//【反时限Ix过流】
	WORD wIXFSX_SetI;				//电流定值;
	WORD wIXFSX_SetK;				//时间系数;
	WORD wIXFSX_IDMT;				//IDMT类型;
};


//-----------------------------------------------------------------------------
class CMyProtectItemIDMT
{
protected:
	DWORD m_dwSumIDMT;
public:
	void OnInit(void);
	WORD GetProtectPickupInfo(void);
protected:
	WORD GetLN(DWORD dwData);
	void ProtectIDMT(WORD wProtectIndex,WORD wTypeIDMT,WORD wSetK,WORD wSetI,WORD wDataI);
};


//-----------------------------------------------------------------------------
class CMyProtectItemDXDT:public CMyProtectItem
{
protected:
	WORD m_wCountQueue;
	WORD m_wDataQueue[9];
	WORD m_wCountLock;
public:
	void OnInit(void);
protected:
	long GetDXDT(void);
	void ProtectDXDT(WORD wData,BOOL bStartOK,WORD wTogDXDT,WORD wSetDXDT);
};


//-----------------------------------------------------------------------------
class CMyProtectItemSD:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemXSSD:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemDSXGL:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemFSXGL:public CMyProtectItemIDMT
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemHJS:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemGFH:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemFXDL:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemLXDL:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemJDSX:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemGDY:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemDDY:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemSY:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemFXDY:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemLXDY:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemFHDYGL:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemDZJZ:public CMyProtectItemDXDT
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemDYJL:public CMyProtectItemDXDT
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemCHZ:public CMyProtectItem
{
protected:
	WORD m_wRunStep;
	WORD m_wTimeCharge;
	WORD m_wAllowFlag;
public:
	void OnInit(void);
	void Run(void);
	void Discharge(void);
	WORD GetChargeStatus(void);
	void SetAllowFlag(void);
protected:
	void RunCharging(void);
	void RunCharged(void);
	void RunStartup(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemBZT:public CMyProtectItem
{
protected:
	WORD m_wRunStep;
	WORD m_wTimeCharge;
	WORD m_wLine1LostPowerFlag;
	WORD m_wLine2HavePowerFlag;
	CMyOutput* m_pCloseRelay;
public:
	void OnInit(void);
	void Run(void);
	void Discharge(void);
	WORD GetChargeStatus(void);
	void SetCloseRelay(CMyOutput* pRelay);
	void ForceLine1LostPower(BOOL bLostPower);
	void ForceLine2HavePower(BOOL bHavePower);
protected:
	void RunCharging(void);
	void RunCharged(void);
	void RunStartup(void);
protected:
	BOOL IsLine1LostPower(void);
	BOOL IsLine2HavePower(void);
	BOOL IsChargeAllow(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemGR:public CMyProtectItemIDMT
{
protected:
	WORD m_wPercentGR;
public:
	void OnInit(void);
	void Run(void);
public:
	WORD GetPercentGR(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemNGL:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemQDSJGC:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemIXDSX:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemIXFSX:public CMyProtectItemIDMT
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
#undef CLASSNAME_PROTECT
#define CLASSNAME_PROTECT CMyProtectDMRX01P
class CMyProtectDMRX01P:public CMyProtect
{
public:
	CMyProtectItemSD m_piSD;
	CMyProtectItemXSSD m_piXSSD;
	CMyProtectItemDSXGL m_piDSXGL;
	CMyProtectItemFSXGL m_piFSXGL;
	CMyProtectItemHJS m_piHJS;
	CMyProtectItemGFH m_piGFH;
	CMyProtectItemFXDL m_piFXDL;
	CMyProtectItemLXDL m_piLXDL;
	CMyProtectItemJDSX m_piJDSX;
	CMyProtectItemGDY m_piGDY;
	CMyProtectItemDDY m_piDDY;
	CMyProtectItemSY m_piSY;
	CMyProtectItemFXDY m_piFXDY;
	CMyProtectItemLXDY m_piLXDY;
	CMyProtectItemFHDYGL m_piFHDYGL;
	CMyProtectItemDZJZ m_piDZJZ;
	CMyProtectItemDYJL m_piDYJL;
	CMyProtectItemCHZ m_piCHZ;
	CMyProtectItemBZT m_piBZT;
	CMyProtectItemGR m_piGR;
	CMyProtectItemNGL m_piNGL;
	CMyProtectItemQDSJGC m_piQDSJGC;
	CMyProtectItemIXDSX m_piIXDSX;
	CMyProtectItemIXFSX m_piIXFSX;
public:
	void OnInit(void);
	void OnInitSetpoint(WORD* pSetpoint);
	void OnUpdateDevice(WORD* pData);
	WORD GetProtectPickupInfo(WORD wProtectIndex);
public:
	WORD GetMotorStartTime(void);
protected:
	VIRTUAL void iiiOnProtectActAlarmed(WORD wProtectIndex);
	VIRTUAL void iiiOnProtectActTripped(WORD wProtectIndex);
	VIRTUAL void iiiRun(void);
	friend class CMyProtect;
};

extern const SETPOINTCFGINFO c_setpointCfgInfo[8];
extern const PROTECTACTINFO c_protectActInfo[32];
extern const SETPOINTCFGINFO c_setpointCfgInfoW[8];
extern const PROTECTACTINFO c_protectActInfoW[32];
extern DEVICESETPOINT_DMRX01* g_pDeviceSetpoint;
extern DEVICESETPOINT_DMRX01CONFIG* g_pDeviceSetpointConfig;

#endif/*CMYPROTECTDMRX01P_H*/

