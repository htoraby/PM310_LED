//-----------------------------------------------------------------------------
#undef CLASSNAME_LCD
#define CLASSNAME_LCD CMyLCD_KS0108
class CMyLCD_KS0108:public CMyLCDMem
{
protected:
	void LCDWhile(BYTE BlockSel);
	void LCDSndData(BYTE BlockSel,BYTE Data);
	void LCDSndCommand(BYTE BlockSel,BYTE Command);
protected:	
	VIRTUAL void iiiSetup(void);
	VIRTUAL void iiiFlush(void);
	friend class CMyLCD;
	friend class CMyLCDMem;
};
