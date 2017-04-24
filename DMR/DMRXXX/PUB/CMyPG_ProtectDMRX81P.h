//-----------------------------------------------------------------------------
class CMyPG_ProtectDMRX81P:public CMyPG_Protect
{
protected:
	void OutProtectSetU(WORD* pSetU);
	void OutProtectSetT(WORD* pSetT);
public:
	void GetEditMetrics(WORD* pData,WORD* pDeviceSetpoint);
protected:
	VIRTUAL void iiiOnRefreshPage(WORD* pDeviceSetpoint);
	friend class CMyPG_Protect;
};

