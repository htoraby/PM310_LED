//-----------------------------------------------------------------------------
#undef CLASSNAME_LAD
#define CLASSNAME_LAD CMyLADDMRX81P
class CMyLADDMRX81P:public CMyLADDMR
{
protected:
	VIRTUAL void iiiSetStatusLAD(WORD wBitID,WORD wStatus);
public:
	VIRTUAL CMyData* iiiGetAnalogData(WORD wIndex);
	friend class CMyLAD;
	friend class CMyLADDMR;
};
