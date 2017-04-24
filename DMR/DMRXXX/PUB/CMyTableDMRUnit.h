#ifndef CMYTABLEDMRUNIT_H
#define CMYTABLEDMRUNIT_H

//-----------------------------------------------------------------------------
#undef CLASSNAME_TABLE
#define CLASSNAME_TABLE CMyTableDMRUnit
class CMyTableDMRUnit:public CMyTableDMR
{
public:
	void ControlOut(WORD wControlOutCode,WORD wCommand);
};

#endif/*CMYTABLEDMRUNIT_H*/

