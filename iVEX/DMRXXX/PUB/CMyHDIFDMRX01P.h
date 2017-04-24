#ifndef CMyHDIFDMRX01P_H
#define CMyHDIFDMRX01P_H

#include "..\PUB\CMyHDIFDMR.h"

//-----------------------------------------------------------------------------
#undef CLASSNAME_HDIF
#define CLASSNAME_HDIF CMyHDIFDMRX01P
class CMyHDIFDMRX01P:public CMyHDIFDMR
{
public:
	WORD GetFreqINT1(void);
	WORD GetFreqINT2(void);
};

#endif/*CMyHDIFDMRX01P_H*/

