#define PROTECT_GDY1		0		//1#PT����ѹ;
#define PROTECT_DDY1		1		//1#PT�͵�ѹ;
#define PROTECT_FXDY1		2		//1#PT�����ѹ;
#define PROTECT_LXDY1		3		//1#PT�����ѹ;
#define PROTECT_GDY2		4		//2#PT����ѹ;
#define PROTECT_DDY2		5		//2#PT�͵�ѹ;
#define PROTECT_FXDY2		6		//2#PT�����ѹ;
#define PROTECT_LXDY2		7		//2#PT�����ѹ;


struct DEVICESETPOINT_DMRX81P
{
	//��1#PT����ѹ��
	WORD wGDY1_SetU;				//��ѹ��ֵ;
	WORD wGDY1_SetT;				//ʱ�䶨ֵ;
	//��1#PT�͵�ѹ��
	WORD wDDY1_SetU;				//��ѹ��ֵ;
	WORD wDDY1_SetT;				//ʱ�䶨ֵ;
	//��1#PT�����ѹ��
	WORD wFXDY1_SetU;				//��ѹ��ֵ;
	WORD wFXDY1_SetT;				//ʱ�䶨ֵ;
	//��1#PT�����ѹ��
	WORD wLXDY1_SetU;				//��ѹ��ֵ;
	WORD wLXDY1_SetT;				//ʱ�䶨ֵ;
	//��2#PT����ѹ��
	WORD wGDY2_SetU;				//��ѹ��ֵ;
	WORD wGDY2_SetT;				//ʱ�䶨ֵ;
	//��2#PT�͵�ѹ��
	WORD wDDY2_SetU;				//��ѹ��ֵ;
	WORD wDDY2_SetT;				//ʱ�䶨ֵ;
	//��2#PT�����ѹ��
	WORD wFXDY2_SetU;				//��ѹ��ֵ;
	WORD wFXDY2_SetT;				//ʱ�䶨ֵ;
	//��2#PT�����ѹ��
	WORD wLXDY2_SetU;				//��ѹ��ֵ;
	WORD wLXDY2_SetT;				//ʱ�䶨ֵ;
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

