#ifndef CMYPROTECTDMRX01P_H
#define CMYPROTECTDMRX01P_H

#include "PUB\__Output.h"

enum PROTRCTCODE_X01
{
	 PROTECT_SD = 0				//�����ٶ�;			0
	,PROTECT_XSSD				//��ʱ�����ٶ�;		1
	,PROTECT_DSXGL				//��ʱ�޹���;		2
	,PROTECT_FSXGL				//��ʱ�޹���;		3
	,PROTECT_HJS				//�����;			4
	,PROTECT_GFH				//������;			5
	,PROTECT_FXDL				//�������;			6
	,PROTECT_LXDL				//�������;			7
	,PROTECT_JDSX				//����ӵ�ѡ��;		8
	,PROTECT_GDY				//����ѹ;			9
	,PROTECT_DDY				//�͵�ѹ;			10
	,PROTECT_SY					//ʧѹ;				11
	,PROTECT_FXDY				//�����ѹ;			12
	,PROTECT_LXDY				//�����ѹ;			13
	,PROTECT_FHDYGL				//���ϵ�ѹ����;		14
	,PROTECT_DZJZ				//���ܼ���;			15
	,PROTECT_DYJL				//��ѹ����;			16
	,PROTECT_CHZ				//�غ�բ;			17
	,PROTECT_BZT				//����Ͷ;			18
	,PROTECT_GR					//����;				19
	,PROTECT_NGL				//�湦��;			20
	,PROTECT_QDSJGC				//����ʱ�����;		21
	,PROTECT_IXDSX				//��ʱ��Ix����;		22
	,PROTECT_IXFSX				//��ʱ��Ix����;		23
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
	WORD bConfigMotor;				//�綯����������;
	WORD bConfigFX;					//���������������;
	WORD bConfigDY;					//��ѹ������������;
};

struct DEVICESETPOINT_DMRX01
{
	WORD wMotor_SetI;				//�綯�������;
	WORD wMotor_SetT;				//�綯������ʱ��;
	//�������ٶϡ�
	WORD wSD_SetI;					//������ֵ;
	WORD wSD_SetT;					//ʱ�䶨ֵ;
	WORD wSD_SetU;					//��ѹ��ֵ;
	WORD wSD_TogDY;					//��ѹ����Ͷ��;
	WORD wSD_TogFX;					//�������Ͷ��;
	WORD wSD_TogAD;					//����ʱ��ֵ�Զ��ӱ�Ͷ��;
	//����ʱ�����ٶϡ�
	WORD wXSSD_SetI;				//������ֵ;
	WORD wXSSD_SetT;				//ʱ�䶨ֵ;
	WORD wXSSD_SetU;				//��ѹ��ֵ;
	WORD wXSSD_TogDY;				//��ѹ����Ͷ��;
	WORD wXSSD_TogFX;				//�������Ͷ��;
	WORD wXSSD_TogAD;				//����ʱ��ֵ�Զ��ӱ�Ͷ��;
	//����ʱ�޹�����
	WORD wDSXGL_SetI;				//������ֵ;
	WORD wDSXGL_SetT;				//ʱ�䶨ֵ;
	WORD wDSXGL_SetU;				//��ѹ��ֵ;
	WORD wDSXGL_TogDY;				//��ѹ����Ͷ��;
	WORD wDSXGL_TogFX;				//�������Ͷ��;
	WORD wDSXGL_TogAE;				//����ʱ�����Զ��˳�Ͷ��;
	//����ʱ�޹�����
	WORD wFSXGL_SetI;				//������ֵ;
	WORD wFSXGL_SetK;				//ʱ��ϵ��;
	WORD wFSXGL_IDMT;				//IDMT����;
	//������١�
	WORD wHJS_SetI;					//������ֵ;
	WORD wHJS_SetT;					//ʱ�䶨ֵ;
	//�������ɡ�
	WORD wGFH_SetI;					//������ֵ;
	WORD wGFH_SetT;					//ʱ�䶨ֵ;
	//�����������
	WORD wFXDL_SetI;				//������ֵ;
	WORD wFXDL_SetT;				//ʱ�䶨ֵ;
	//�����������
	WORD wLXDL_SetI;				//������ֵ;
	WORD wLXDL_SetT;				//ʱ�䶨ֵ;
	//������ӵ�ѡ�ߡ�
	WORD wJDSX_SetI;				//������ֵ;
	WORD wJDSX_SetU;				//��ѹ��ֵ;
	WORD wJDSX_TogTHD5;				//���г���о�Ͷ��;
	//������ѹ��
	WORD wGDY_SetU;					//��ѹ��ֵ;
	WORD wGDY_SetT;					//ʱ�䶨ֵ;
	//���͵�ѹ��
	WORD wDDY_SetU;					//��ѹ��ֵ;
	WORD wDDY_SetT;					//ʱ�䶨ֵ;
	//��ʧѹ��
	WORD wSY_SetU;					//��ѹ��ֵ;
	WORD wSY_SetT;					//ʱ�䶨ֵ;
	//�������ѹ��
	WORD wFXDY_SetU;				//��ѹ��ֵ;
	WORD wFXDY_SetT;				//ʱ�䶨ֵ;
	//�������ѹ��
	WORD wLXDY_SetU;				//��ѹ��ֵ;
	WORD wLXDY_SetT;				//ʱ�䶨ֵ;
	//�����ϵ�ѹ������
	WORD wFHDYGL_SetI;				//������ֵ;
	WORD wFHDYGL_SetU;				//��ѹ��ֵ;
	WORD wFHDYGL_SetUFX;			//�����ѹ��ֵ;
	WORD wFHDYGL_SetT;				//ʱ�䶨ֵ;
	WORD wFHDYGL_TogDY;				//��ѹ����Ͷ��;
	WORD wFHDYGL_TogFXDY;			//�����ѹ����Ͷ��;
	//�����ܼ��ء�
	WORD wDZJZ_SetF;				//Ƶ�ʶ�ֵ;
	WORD wDZJZ_SetT;				//ʱ�䶨ֵ;
	WORD wDZJZ_SetU;				//��ѹ��ֵ;
	WORD wDZJZ_SetDFDT;				//���ֵ;
	WORD wDZJZ_TogDFDT;				//�������Ͷ��;
	WORD wDZJZ_TogDY;				//��ѹ����Ͷ��;
	WORD wDZJZ_TogDL;				//��������Ͷ��;
	//����ѹ���С�
	WORD wDYJL_SetU;				//��ѹ��ֵ;
	WORD wDYJL_SetT;				//ʱ�䶨ֵ;
	WORD wDYJL_SetDVDT;				//���ֵ;
	WORD wDYJL_TogDVDT;				//�������Ͷ��;
	WORD wDYJL_TogDL;				//��������Ͷ��;
	//���غ�բ��
	WORD wCHZ_SetT;					//ʱ�䶨ֵ;
	WORD wCHZ_SetA;					//ͬ�ڽǶ�ֵ;
	WORD wCHZ_TogWY;				//����ѹͶ��;
	WORD wCHZ_TogTQ;				//��ͬ��Ͷ��;
	//������Ͷ��
	WORD wBZT_SetU;					//��ѹ��ֵ;
	WORD wBZT_SetT;					//ʱ�䶨ֵ;
	//�����ȡ�
	WORD wGR_SetI;					//������ֵ;
	WORD wGR_SetT;					//ʱ�䶨ֵ;
	WORD wGR_SetK2;					//�������ϵ��;
	//���湦�ʡ�
	WORD wNGL_SetP;					//����������;
	WORD wNGL_SetT;					//ʱ�䶨ֵ;
	//����ʱ��Ix������
	WORD wIXDSX_SetI;				//������ֵ;
	WORD wIXDSX_SetT;				//ʱ�䶨ֵ;
	//����ʱ��Ix������
	WORD wIXFSX_SetI;				//������ֵ;
	WORD wIXFSX_SetK;				//ʱ��ϵ��;
	WORD wIXFSX_IDMT;				//IDMT����;
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

