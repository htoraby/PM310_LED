#define PROTECT_GDY1		0		//1#PT过电压;
#define PROTECT_DDY1		1		//1#PT低电压;
#define PROTECT_FXDY1		2		//1#PT负序电压;
#define PROTECT_LXDY1		3		//1#PT零序电压;
#define PROTECT_GDY2		4		//2#PT过电压;
#define PROTECT_DDY2		5		//2#PT低电压;
#define PROTECT_FXDY2		6		//2#PT负序电压;
#define PROTECT_LXDY2		7		//2#PT零序电压;


struct DEVICESETPOINT_DMRX81P
{
	//【1#PT过电压】
	WORD wGDY1_SetU;				//电压定值;
	WORD wGDY1_SetT;				//时间定值;
	//【1#PT低电压】
	WORD wDDY1_SetU;				//电压定值;
	WORD wDDY1_SetT;				//时间定值;
	//【1#PT负序电压】
	WORD wFXDY1_SetU;				//电压定值;
	WORD wFXDY1_SetT;				//时间定值;
	//【1#PT零序电压】
	WORD wLXDY1_SetU;				//电压定值;
	WORD wLXDY1_SetT;				//时间定值;
	//【2#PT过电压】
	WORD wGDY2_SetU;				//电压定值;
	WORD wGDY2_SetT;				//时间定值;
	//【2#PT低电压】
	WORD wDDY2_SetU;				//电压定值;
	WORD wDDY2_SetT;				//时间定值;
	//【2#PT负序电压】
	WORD wFXDY2_SetU;				//电压定值;
	WORD wFXDY2_SetT;				//时间定值;
	//【2#PT零序电压】
	WORD wLXDY2_SetU;				//电压定值;
	WORD wLXDY2_SetT;				//时间定值;
};


//-----------------------------------------------------------------------------
class CMyProtectItemGDY1:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemDDY1:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemFXDY1:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemLXDY1:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemGDY2:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemDDY2:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemFXDY2:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
class CMyProtectItemLXDY2:public CMyProtectItem
{
public:
	void Run(void);
};


//-----------------------------------------------------------------------------
#undef CLASSNAME_PROTECT
#define CLASSNAME_PROTECT CMyProtectDMRX81P
class CMyProtectDMRX81P:public CMyProtect
{
public:
	CMyProtectItemGDY1 m_piGDY1;
	CMyProtectItemDDY1 m_piDDY1;
	CMyProtectItemFXDY1 m_piFXDY1;
	CMyProtectItemLXDY1 m_piLXDY1;
	CMyProtectItemGDY2 m_piGDY2;
	CMyProtectItemDDY2 m_piDDY2;
	CMyProtectItemFXDY2 m_piFXDY2;
	CMyProtectItemLXDY2 m_piLXDY2;
public:
	void OnInit(void);
	void OnInitSetpoint(WORD* pSetpoint);
	WORD GetProtectPickupInfo(WORD wProtectIndex);
	void OnUpdateDevice(WORD* pData);
protected:
	VIRTUAL void iiiRun(void);
	friend class CMyProtect;
};

extern const SETPOINTCFGINFO c_setpointCfgInfo[8];
extern const PROTECTACTINFO c_protectActInfo[32];
extern DEVICESETPOINT_DMRX81P* g_pDeviceSetpoint;

