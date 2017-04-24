#ifndef CMYPROTOCOLMODBUSIBCU_H
#define CMYPROTOCOLMODBUSIBCU_H

//-----------------------------------------------------------------------------
#undef CLASSNAME_PROTOCOL
#define CLASSNAME_PROTOCOL CMyProtocolMODBUSiBCU
class CMyProtocolMODBUSiBCU:public CMyProtocolMODBUS
{
public:
	void OnInit(void);
};

extern BOOL g_bQuit1ms;

#endif/*CMYPROTOCOLMODBUSIBCU_H*/

