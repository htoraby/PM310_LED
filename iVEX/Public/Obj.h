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
	COLORREF m_clrMask;			// ͼƬҪ��ȥ������ɫ
protected:
	BOOL m_bHide;
public:
	void SetHide(BOOL bHide);
};


//-----------------------------------------------------------------------------
// ������ʾ2״̬LED��(��/��)
// �����ļ���������Ϣ��
// LEDG:50,200,41,40,\\DMC\\DMC230\\fan1.bmp,\\DMC\\DMC230\\fan0.bmp,16777215,LEDG
// �����:left,top,width,heigth,m_strGraphON,m_strGraphOFF,m_clrMask,ʵ����
class CLASS_EXPORT CMyObjLEDGraph:public CMyObjLED
{
public:
	DECLARE_SERIAL(CMyObjLEDGraph);
	CMyObjLEDGraph();
	~CMyObjLEDGraph();
public:
	CString m_strGraphON;		// LED��ʱͼƬ����(�������iVEX·��)
	CString m_strGraphOFF;		// LED��ʱͼƬ����(�������iVEX·��)
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
// ������ʾ7�������(��1��n״̬LED��1��2״̬LED)
// �����ļ���������Ϣ��
// LEDD:155,50,52,71,43,60,10,10,\\DMC\\DMC230\\Graph,0,LEDD1
// �����:m_nNumStatus,left,top,width,heigth,m_DotOffsetX,m_DotOffsetY,m_DotWidth,m_DotHeigth,m_strGraph,m_clrMask,ʵ����
// ͼƬ��:0.bmp...n.bmp(��Ӧ����0��n),Dot0.bmp,Dot1.bmp(��ӦС����״̬)
class CLASS_EXPORT CMyObjLEDDigtal:public CMyObjLED
{
public:
	DECLARE_SERIAL(CMyObjLEDDigtal);
	CMyObjLEDDigtal();
	CMyObjLEDDigtal(short nNumStatus);
	~CMyObjLEDDigtal();
public:
	short m_nNumStatus;			// ״̬��
	CString m_strGraph;		// ͼƬ�洢�ļ���(���iVEX·��)
	int m_DotOffsetX;		// С�����ƫ��λ��
	int m_DotOffsetY;
	int m_DotWidth;			// С�����С
	int m_DotHeigth;
protected:
	HBITMAP* m_phBitmap;
	HBITMAP m_hBitmapDOT0;
	HBITMAP m_hBitmapDOT1;
	short m_nStatusNew;
	short m_nStatusOld;
	BOOL m_bStatusDOTNew;
	BOOL m_bStatusDOTOld;
	BOOL m_bDispalyDOT;		// �Ƿ���ʾС����
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
// ������ʾ��״̬LED
// �����ļ���������Ϣ��
// LEDS:10,250,200,100,102,\\DMC\\DMC230\\pro,0,LEDS
// �����:m_nNumStatus,left,top,width,heigth,m_strGraph,m_clrMask,ʵ����
// ͼƬ��Ϊ:0.bmp,1.bmp,2.bmp.....n.bmp,��Ӧ��״̬
// һ����״̬LED��һ��2״̬LED�������ʾһ����С�����7�������
class CLASS_EXPORT CMyObjLEDStatus:public CMyObjLED
{
public:
	DECLARE_SERIAL(CMyObjLEDStatus);
	CMyObjLEDStatus();			// Ĭ�Ϲ��캯��,���л�����
	CMyObjLEDStatus(short nNumStatus);
	~CMyObjLEDStatus();
public:
	short m_nNumStatus;			// ״̬��
	CString m_strGraph;			// ͼƬ�洢�ļ���(���iVEX·��)
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
// ������ʾ��״̬LED
// �����ļ���������Ϣ��
// LEDS:10,250,200,100,102,\\DMC\\DMC230\\pro,0,LEDS
// �����:m_nNumStatus,left,top,width,heigth,m_strGraph,m_clrMask,ʵ����
// ͼƬ��Ϊ:0.bmp,1.bmp,2.bmp.....n.bmp,cursor.bmp,��Ӧ��״̬
class CLASS_EXPORT CMyObjLEDButton:public CMyObjLEDStatus
{
public:
	HCURSOR m_hCursor;
public:
	DECLARE_SERIAL(CMyObjLEDButton);
	CMyObjLEDButton();			// Ĭ�Ϲ��캯��,���л�����
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




