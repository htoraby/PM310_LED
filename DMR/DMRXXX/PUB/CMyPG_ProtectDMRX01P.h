#ifndef CMYPG_PROTECTDMRX01P_H
#define CMYPG_PROTECTDMRX01P_H

//-----------------------------------------------------------------------------
#undef CLASSNAME_PG_PROTECT
#define CLASSNAME_PG_PROTECT CMyPG_ProtectDMRX01P
class CMyPG_ProtectDMRX01P:public CMyPG_Protect
{
protected:
	void OutProtectSetI(WORD* pSetI);
	void OutProtectSetU(WORD* pSetU);
	void OutProtectSetT(WORD* pSetT);
	void OutProtectSetF(WORD* pSetF);
public:
	void SetMetrics(void);
	void GetEditMetrics(WORD* pData,WORD* pDeviceSetpoint);
protected:
	VIRTUAL void iiiOnRefreshPage(WORD* pDeviceSetpoint);
	friend class CMyPG_Protect;
};

#endif/*CMYPG_PROTECTDMRX01P_H*/



