#ifndef CMYPG_PROTECTiBCUX42_H
#define CMYPG_PROTECTiBCUX42_H

//-----------------------------------------------------------------------------
class CMyPG_ProtectiBCUX42:public CMyPG_Protect
{
protected:
	void OutProtectSetI(WORD* pSetI);
	void OutProtectSetU(WORD* pSetU);
	void OutProtectSetT(WORD* pSetT);
	void OutProtectSetF(WORD* pSetF);
public:
	void GetEditMetrics(WORD* pData,WORD* pDeviceSetpoint);
protected:
	VIRTUAL void iiiOnRefreshPage(WORD* pDeviceSetpoint);
	friend class CMyPG_Protect;
};

#endif/*CMYPG_PROTECTiBCUX42_H*/



