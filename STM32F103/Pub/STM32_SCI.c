#include <Main.h>

static WORD GetBaudrate(void)
{
	WORD wBaudrate;
	switch(g_deviceParam.wBaudrate1)
	{
	case BAUDRATE_2400:  wBaudrate = 2400; break;
	case BAUDRATE_4800:  wBaudrate = 4800; break;
	case BAUDRATE_9600:  wBaudrate = 9600; break;
	default: wBaudrate = 9600; break;
	}
	return wBaudrate;
}

static WORD s_wCountPreRcv = 0;

// BOOL g_bComInit = FALSE;
//WORD s_wBaud = BAUDRATE_9600;

//-----------------------------------------------------------------------------
void COMM_HardWareInit(void)
{
    USART_InitTypeDef USART_InitStructure;
    MyHDIF_OnSCICloseTX();
    
    USART_Cmd(USART1, DISABLE);
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = GetBaudrate();
//    s_wBaud = g_deviceParam.wBaudrate1;
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

void COMM_OnInit(void)
{
    MyHDIF_OnSCICloseTX();
    Protocol_OnInit();
    g_wCommStatus = COMMSTATUS_INIT;
    s_wCountPreRcv = DFT_DOTNUM/(g_deviceParam.wBaudrate1+1);
}

void COMM_OnPolling(void)
{
    BOOL bReceivedData = FALSE;
    Protocol_OnPolling();
    
//    if(s_wBaud!=g_deviceParam.wBaudrate1)
//    {
//        COMM_HardWareInit();
//    }
//    
//    if(USART_GetFlagStatus(USART1, USART_FLAG_ORE)!=RESET)
//    {
////         USART_ClearFlag(USART1, USART_FLAG_ORE);
//        COMM_HardWareInit();
//    }
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)!=RESET)
    {
        BYTE Data;
        USART_ClearFlag(USART1, USART_FLAG_RXNE);
        Data = USART_ReceiveData(USART1);
        Protocol_OnRcvProcess(Data);
        bReceivedData = TRUE;
    }
    switch(g_wCommStatus)
    {
    case COMMSTATUS_NULL:
            COMM_HardWareInit();
            COMM_OnInit();
            break;
    case COMMSTATUS_INIT:
        if(bReceivedData) 
        {
            COMM_HardWareInit();
            COMM_OnInit();
        }
        else 
        {
            if(s_wCountPreRcv>0) s_wCountPreRcv--;
            else Protocol_OnInit();
        }
        break;
    case COMMSTATUS_SNDING1:
        MyHDIF_OnSCIOpenTX();
        while(g_wCommStatus==COMMSTATUS_SNDING1)
        {
            if(USART_GetFlagStatus(USART1, USART_FLAG_TXE)!=RESET)
            {
                BYTE Data;
                USART_ClearFlag(USART1, USART_FLAG_TXE);
                Data = Protocol_GetSndData();
                USART_SendData(USART1, Data);
            }
            else break;
        }
        break;
    case COMMSTATUS_SNDOPEN:
        MyHDIF_OnSCIOpenTX();
        break;
    case COMMSTATUS_SNDING2:
    case COMMSTATUS_SNDCLOSE:
        if(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=RESET)
        {
            USART_ClearFlag(USART1, USART_FLAG_TC);
            g_wCommStatus = COMMSTATUS_NULL;
            MyHDIF_OnSCICloseTX();
        }
        break;
    }
}

void COMM_OnTimer10ms(void)
{
    Protocol_OnTimer10msCRC();
}
