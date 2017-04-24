#ifndef CMYLADDMRUNIT_H
#define CMYLADDMRUNIT_H

//-----------------------------------------------------------------------------
#undef CLASSNAME_LAD
#define CLASSNAME_LAD CMyLADDMRUnit
class CMyLADDMRUnit:public CMyLADDMR
{
protected:
	VIRTUAL void iiiSetStatusLAD(WORD wBitID,WORD wStatus);
public:
	VIRTUAL CMyData* iiiGetAnalogData(WORD wIndex);
	friend class CMyLAD;
	friend class CMyLADDMR;
};

#endif/*CMYLADDMRUNIT_H*/
