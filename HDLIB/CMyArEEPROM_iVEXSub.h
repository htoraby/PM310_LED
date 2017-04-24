#ifndef CMYAREEPROM_IVEXSUB_H
#define CMYAREEPROM_IVEXSUB_H

//-----------------------------------------------------------------------------
class CMyArEEPROM_iVEXSub:public CMyArEEPROM_iVEX
{
protected:
	virtual void GetEEPROMFileName(char* pszEEPROMFileName);
};

#endif/*CMYAREEPROM_IVEXSUB_H*/