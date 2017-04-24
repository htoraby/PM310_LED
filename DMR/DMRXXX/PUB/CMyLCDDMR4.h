#ifndef CMYLCDIBCU3_H
#define CMYLCDIBCU3_H

//-----------------------------------------------------------------------------
#undef CLASSNAME_LCD
#define CLASSNAME_LCD CMyLCDiBCU3
class CMyLCDiBCU3:public CMyLCDMem
{
public:
	void HWRest(void);
protected:
	void LCDSndData(BYTE Data);
	void LCDSndCommand(BYTE Command);
protected:	
	VIRTUAL void iiiSetup(void);
	VIRTUAL void iiiFlush(void);
	friend class CMyLCD;
	friend class CMyLCDMem;
};

#endif/*CMYLCDIBCU3_H*/

