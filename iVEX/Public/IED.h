typedef struct _WATCHPARAM					// watch面板参数
{
	CString strName;						// 参数名
	WORD* pwData;							// 参数起始地址
	WORD* pwDataCopy;						// 参数副本,用于判断是否需要刷新
	long lLen;								// 参数长度
	DWORD dwParam;							// 额外一个参数
	//	BOOL bValid;						// 是否可用
}WATCHPARAM;

HBITMAP MyCreateCompatibleBitmap(HBITMAP hBitmap);

typedef CTypedPtrArray<CObArray,CPropertyPage*> CMyPPageArray;

//-----------------------------------------------------------------------------
class CLASS_EXPORT CMyIED:public CObject
{
public:
	static CStringArray s_aIEDSeries;
	static CStringArray s_aIEDType;
	static CPtrArray s_aIEDClass;
	static void RegisterClass(CString strSeries,CString strType,CRuntimeClass* pRuntimeClass);
	static CRuntimeClass* s_pRuntimeClassRegister;
public:
	DECLARE_SERIAL(CMyIED);
	CMyIED();
	~CMyIED();
public:
	CString m_strType;
public:
	CScrollView* m_pView;
	CSize m_size;
	CDialog* m_pDemoPanelDlg;
	CDialog* m_pEXPanelDlg;
	HBITMAP m_hBitmap;
	CMyObjArray m_aObj;
	CMyPPageArray m_aPPage;					// 侧边栏中页面指针
	CStringArray m_astrPPage;				// 侧边栏中页面指针名称
	CMyObj* m_pObjOld;
	BOOL m_bDisplayActiveArea;
	BOOL m_bAlarmed;
	BOOL m_bTripped;
	BOOL m_bAlarmedSndPlaying;
	BOOL m_bTrippedSndPlaying;
public:
	// Watch面板参数
	CPtrArray m_ptrArrWatch;
	CStringArray m_aACLabel;
	CStringArray m_aACUnitage;
	float m_fFreqDataNormal;
	float m_fFreqDataFault;
	float m_fACDataNormal[16];
	float m_fACDataANormal[16];
	float m_fACDataFault[16];
	float m_fACDataAFault[16];
	WORD m_wFaultTime10ms;
	WORD m_wCurFaultTime10ms;
	BOOL m_bHarmonic;
	BOOL m_bHarmonicF;
	BOOL m_bFreqValid;
	BOOL m_bACValid[16];
	CStringArray m_aINLabel;
	CStringArray m_aINStatus0;
	CStringArray m_aINStatus1;
	BYTE m_INStatus[40];
	BOOL m_bINValid[40];
	CStringArray m_aOutLabel;
	BYTE m_OutStatus[39];
	BOOL m_bOutValid[39];
	BOOL m_bCBButtonUsed;
	WORD m_wSampleMax;
	WORD m_wCBStatus;
	WORD m_wCBStatusOld;
	WORD m_wCBCountCoilC;
	WORD m_wCBCountCoilT;
	BOOL m_bCBLockC;
	BOOL m_bCBLockT;
public:
	CStringArray m_aINEXLabel;
	CStringArray m_aINEXStatus0;
	CStringArray m_aINEXStatus1;
public:
	virtual void OnCreate(void);
	virtual void OnDraw(CDC* pDC);
	virtual void OnDrawRefresh(CDC* pDC);
	virtual void OnMainInit(void){};
	virtual void OnMainTimer1ms(void){};
	virtual void OnMainTimer5ms(void){};
	virtual void OnMainTimer10ms(void);
	virtual void OnMainTimer100ms(void){};
	virtual void OnMainTimer250ms(void){};
	virtual void OnMainTimer1000ms(void){};
	virtual void OnMainWhileLoop(void){};
public:
	CMyObj* GetObj(CString strLabel,CRuntimeClass* pRuntimeClass);
	CMyObjLCD* GetObjLCD(CString strLabel);
	CMyObjKey* GetObjKey(CString strLabel);
	CMyObjLight* GetObjLight(CString strLabel);
	CMyObjRelay* GetObjRelay(CString strLabel);
	CMyObjLock2* GetObjLock2(CString strLabel);
	CMyObjLEDGraph* GetObjLEDG(CString strLabel);
	CMyObjLEDDigtal* GetObjLEDD(CString strLabel);
	CMyObjLEDStatus* GetObjLEDS(CString strLabel);
	CMyObjLEDButton* GetObjLEDB(CString strLabel);
public:
	CMyObj* SetOperateCursor(CPoint point);
	virtual void OnMouseMove(UINT nFlags,CPoint point);
	virtual void OnLButtonDown(UINT nFlags,CPoint point);
	virtual void OnLButtonUp(UINT nFlags,CPoint point);
	virtual void OnRButtonDown(UINT nFlags,CPoint point);
	virtual void OnRButtonUp(UINT nFlags,CPoint point);
	virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){};
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){};
public:
	void CreateDemoPanelDlg(void);
	void CreateWatchPanel(void);
	void CreateEXPanelDlg(void);
	void SetModeToNormal(void);
	void SetModeToFault(void);
	void AddACChannel(CString strLabel,CString strUnitage,float fDataNormal,float fDataANormal,float fFaultK,BOOL bValid=TRUE);
	void AddINChannel(CString strLabel,CString strStatus0,CString strStatus1,BYTE Status,BOOL bValid=TRUE);
	void AddOutChannel(CString strLabel,BOOL bValid=TRUE);
	void AddWatchParam(CString strName,DWORD dwParam=0,WORD* pwData=NULL,long lWordCnt=0);
	WORD GetFreqData(void);
	void GetACData(int nIndex,float& fData,float& fDataA);
	void GetACWaveData(int nIndex,unsigned short* pWaveData,float f2Scale,unsigned short wDotNum);
	WORD GetINStatus(int nIndex);
	void SetINStatus(int nIndex,BYTE Status);
	void SetOutStatus(int nIndex,BYTE Status);
	unsigned short GetCBStatus(void);
	void SetCBLockC(BOOL bLock);
	void SetCBLockT(BOOL bLock);
	void SetCBCoilC(void);
	void SetCBCoilT(void);
public:
	void AddINEXChannel(CString strLabel,CString strStatus0,CString strStatus1);
	WORD GetEXID(void);
	WORD GetDCData(int nIndex,WORD wScale);
	void SetDCData(int nIndex,WORD wData,WORD wScale);
	WORD GetINEXStatus(int nIndex);
	void SetINEXStatus(int nIndex,BYTE Status);
	void SetOutEXStatus(int nIndex,BYTE Status);
};
