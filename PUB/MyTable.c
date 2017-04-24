#include <Main.h>

//-----------------------------------------------------------------------------
WORD* Table_GetDevAddr(WORD wLogAddr,WORD wLogLength,WORD wLogAddrValid,WORD wLogLengthValid,WORD* pDevAddr)
{
	if(wLogAddr>=wLogAddrValid&&(wLogAddr+wLogLength)<=(wLogAddrValid+wLogLengthValid))
	{
		return pDevAddr+(wLogAddr-wLogAddrValid);
	}
	return NULL;
}



