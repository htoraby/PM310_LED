//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyObj:public CObject
{
public:
	DECLARE_SERIAL(CMyObj);
	CMyObj();
public:
	CRect m_rect;
	CString m_strLabel;
	BOOL m_bButtonDown;
public:
	virtual void OnCreate(void){};
	virtual void OnDraw(CDC* pDC){};
	virtual void OnDrawRefresh(CDC* pDC){};
	virtual void OnLButtonDown(void){};
	virtual void OnLButtonUp(void){};
	virtual void OnRButtonDown(void){};
	virtual void OnRButtonUp(void){};
	virtual BOOL IsSupportOperate(void){ return FALSE; };
	virtual void SetOperateCursor(void);
};

typedef CTypedPtrArray<CObArray,CMyObj*> CMyObjArray;

//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyObjLCD:public CMyObj
{
public:
	DECLARE_SERIAL(CMyObjLCD);
	CMyObjLCD();
public:
	int m_nLCD_CXDOT;
	int m_nLCD_CYDOT;
	BYTE* m_pLCDBuffer;
	BOOL m_bLCDColor;
	COLORREF m_clrLine;
	COLORREF m_clrBack;
	BOOL m_bLCDRefresh;
	BOOL m_bLCDOpened;
protected:
	void OnDrawM(int nPosLCDX,int nPosLCDY,CDC* pDC);
	void OnDrawC(int nPosLCDX,int nPosLCDY,CDC* pDC);
	COLORREF GetLCDColor(BYTE LCDData);
public:
	void SetLCDMetrics(int nLCD_CXDOT,int nLCD_CYDOT,BYTE* pLCDBuffer,BOOL bLCDColor);
	void SetLCDColor(COLORREF clrLine,COLORREF clrBack);
	void SetLCDRefresh(void);
	void SetLCDOpened(BOOL bLCDOpened);
	virtual void OnDraw(CDC* pDC);
	virtual void OnDrawRefresh(CDC* pDC);
};

//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyObjOLED:public CMyObjLCD
{
public:
	DECLARE_SERIAL(CMyObjOLED);
	CMyObjOLED();
protected:
	virtual void OnDrawM(int nPosLCDX,int nPosLCDY,CDC* pDC);
};


//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyObjKey:public CMyObj
{
public:
	DECLARE_SERIAL(CMyObjKey);
	CMyObjKey();
public:
	virtual BOOL IsSupportOperate(void){ return TRUE; };
};


//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyObjLight:public CMyObj
{
public:
	DECLARE_SERIAL(CMyObjLight);
	CMyObjLight();
public:
	BOOL m_bRectangle;
	COLORREF m_clrStatusOld;
	COLORREF m_clrStatusNew;
public:
	virtual void OnDraw(CDC* pDC);
	virtual void OnDrawRefresh(CDC* pDC);
public:
	void SetStatus(COLORREF clrStatusNew);
};


//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyObjRelay:public CMyObj
{
public:
	DECLARE_SERIAL(CMyObjRelay);
	CMyObjRelay();
};


//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyObjLock2:public CMyObj
{
public:
	DECLARE_SERIAL(CMyObjLock2);
	CMyObjLock2();
	~CMyObjLock2();
public:
	BYTE m_LockStatusOld;
	BYTE m_LockStatusNew;
	CString m_strBMPFileStatus0;
	CString m_strBMPFileStatus1;
	HBITMAP m_hBitmapStatus0;
	HBITMAP m_hBitmapStatus1;
public:
	virtual void OnCreate(void);
	virtual void OnDraw(CDC* pDC);
	virtual void OnDrawRefresh(CDC* pDC);
	virtual void OnLButtonDown(void);
	virtual BOOL IsSupportOperate(void){ return TRUE; };
};


//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyObjLED:public CMyObj
{
public:
	DECLARE_SERIAL(CMyObjLED);
	CMyObjLED();
	~CMyObjLED();
public:
	COLORREF m_clrMask;			// 图片要扣去部分颜色
protected:
	BOOL m_bHide;
public:
	void SetHide(BOOL bHide);
};


//-----------------------------------------------------------------------------
// 用于显示2状态LED灯(亮/灭)
// 配置文件中描述信息：
// LEDG:50,200,41,40,\\DMC\\DMC230\\fan1.bmp,\\DMC\\DMC230\\fan0.bmp,16777215,LEDG
// 组件名:left,top,width,heigth,m_strGraphON,m_strGraphOFF,m_clrMask,实例名
class CLASS_EXPORT CMyObjLEDGraph:public CMyObjLED
{
public:
	DECLARE_SERIAL(CMyObjLEDGraph);
	CMyObjLEDGraph();
	~CMyObjLEDGraph();
public:
	CString m_strGraphON;		// LED亮时图片名称(包含相对iVEX路径)
	CString m_strGraphOFF;		// LED灭时图片名称(包含相对iVEX路径)
protected:
	HBITMAP m_hBitmapON;
	HBITMAP m_hBitmapOFF;
	BOOL m_bStatusNew;
	BOOL m_bStatusOld;
public:
	void SetStatus(BOOL bStatus);
	virtual void OnCreate(void);
	virtual void OnDraw(CDC* pDC);
	virtual void OnDrawRefresh(CDC* pDC);
};


//-----------------------------------------------------------------------------
// 用于显示7段数码管(或1个n状态LED和1个2状态LED)
// 配置文件中描述信息：
// LEDD:155,50,52,71,43,60,10,10,\\DMC\\DMC230\\Graph,0,LEDD1
// 组件名:m_nNumStatus,left,top,width,heigth,m_DotOffsetX,m_DotOffsetY,m_DotWidth,m_DotHeigth,m_strGraph,m_clrMask,实例名
// 图片名:0.bmp...n.bmp(对应数字0～n),Dot0.bmp,Dot1.bmp(对应小数点状态)
class CLASS_EXPORT CMyObjLEDDigtal:public CMyObjLED
{
public:
	DECLARE_SERIAL(CMyObjLEDDigtal);
	CMyObjLEDDigtal();
	CMyObjLEDDigtal(short nNumStatus);
	~CMyObjLEDDigtal();
public:
	short m_nNumStatus;			// 状态数
	CString m_strGraph;		// 图片存储文件夹(相对iVEX路径)
	int m_DotOffsetX;		// 小数点的偏移位置
	int m_DotOffsetY;
	int m_DotWidth;			// 小数点大小
	int m_DotHeigth;
protected:
	HBITMAP* m_phBitmap;
	HBITMAP m_hBitmapDOT0;
	HBITMAP m_hBitmapDOT1;
	short m_nStatusNew;
	short m_nStatusOld;
	BOOL m_bStatusDOTNew;
	BOOL m_bStatusDOTOld;
	BOOL m_bDispalyDOT;		// 是否显示小数点
	BOOL m_bModify;
public:
	void DisplayDOT(BOOL bDisplay);
	void SetDOTStatus(BOOL bStatus);
	void SetStatus(short nStatus);
	virtual void OnCreate(void);
	virtual void OnDraw(CDC* pDC);
	virtual void OnDrawRefresh(CDC* pDC);
};


//-----------------------------------------------------------------------------
// 用于显示多状态LED
// 配置文件中描述信息：
// LEDS:10,250,200,100,102,\\DMC\\DMC230\\pro,0,LEDS
// 组件名:m_nNumStatus,left,top,width,heigth,m_strGraph,m_clrMask,实例名
// 图片名为:0.bmp,1.bmp,2.bmp.....n.bmp,对应各状态
// 一个多状态LED和一个2状态LED可配合显示一个带小数点的7段数码管
class CLASS_EXPORT CMyObjLEDStatus:public CMyObjLED
{
public:
	DECLARE_SERIAL(CMyObjLEDStatus);
	CMyObjLEDStatus();			// 默认构造函数,串行化必须
	CMyObjLEDStatus(short nNumStatus);
	~CMyObjLEDStatus();
public:
	short m_nNumStatus;			// 状态数
	CString m_strGraph;			// 图片存储文件夹(相对iVEX路径)
// private:
protected:
	HBITMAP* m_phBitmap;
	short m_nStatusNew;
	short m_nStatusOld;
public:
	void SetStatus(short nStatus);
	virtual void OnCreate(void);
	virtual void OnDraw(CDC* pDC);
	virtual void OnDrawRefresh(CDC* pDC);
};


//-----------------------------------------------------------------------------
// 用于显示多状态LED
// 配置文件中描述信息：
// LEDS:10,250,200,100,102,\\DMC\\DMC230\\pro,0,LEDS
// 组件名:m_nNumStatus,left,top,width,heigth,m_strGraph,m_clrMask,实例名
// 图片名为:0.bmp,1.bmp,2.bmp.....n.bmp,cursor.bmp,对应各状态
class CLASS_EXPORT CMyObjLEDButton:public CMyObjLEDStatus
{
public:
	HCURSOR m_hCursor;
public:
	DECLARE_SERIAL(CMyObjLEDButton);
	CMyObjLEDButton();			// 默认构造函数,串行化必须
	CMyObjLEDButton(short nNumStatus);
	~CMyObjLEDButton();
public:
	virtual void OnCreate(void);
	virtual void OnLButtonDown(void);
	virtual void OnRButtonDown(void);
	virtual BOOL IsSupportOperate(void){ return TRUE; };
	short GetStatus(void);
	virtual void SetOperateCursor(void);
};




