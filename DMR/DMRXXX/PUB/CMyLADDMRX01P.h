#ifndef CMYLADDMRX01P_H
#define CMYLADDMRX01P_H

//-----------------------------------------------------------------------------
#undef CLASSNAME_LAD
#define CLASSNAME_LAD CMyLADDMRX01P
class CMyLADDMRX01P:public CMyLADDMRUnit
{
protected:
	VIRTUAL void iiiSetStatusLAD(WORD wBitID,WORD wStatus);
	friend class CMyLAD;
	friend class CMyLADDMR;
	friend class CMyLADDMRUnit;
};

#endif/*CMYLADDMRX01P_H*/