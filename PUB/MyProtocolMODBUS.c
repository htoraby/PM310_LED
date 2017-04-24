#include <Main.h>

//-----------------------------------------------------------------------------
void Protocol_CopyByteToWord(WORD* pDest,BYTE* pSrc,WORD wCountWord)
{
	while(wCountWord--)
	{
		*pDest++ = (*(pSrc+1)&0xff)+(*pSrc<<8);
		pSrc++;
		pSrc++;
	}
}

void Protocol_CopyWordToByte(BYTE* pDest,WORD* pSrc,WORD wCountWord)
{
	while(wCountWord--)
	{
		*pDest++ = *pSrc>>8;
		*pDest++ = *pSrc&0xff;
		pSrc++;
	}
}

void Protocol_CopyDwordToByte(BYTE* pDest,DWORD* pSrc,WORD wCountWord)
{
    while(wCountWord--)
    {
        *pDest++ = *pSrc>>24;
        *pDest++ = *pSrc>>16;
        *pDest++ = *pSrc>>8;
        *pDest++ = *pSrc&0xff;
        pSrc++;
    }    
}

// void Protocol_CopyByteToByte(BYTE* pDest,BYTE* pSrc,WORD wCountWord)
// {
// 	while(wCountWord--)
// 	{
// 		*pDest++ = *pSrc&0xff;
// 		pSrc++;
// 	}
// }

//-----------------------------------------------------------------------------
void Protocol_OnTimer10msCRC(void)
{
//	WORD wCountSndByte;
//	WORD wCRC;
//	if(g_wCommStatus!=COMMSTATUS_SNDOPEN) return;
//	switch(g_wCRCCal)
//	{
//	case 0x0000:
//		wCRC = CalculateCRCByte(g_CommBuffer,(WORD)(g_pRcvEndPointer-g_CommBuffer));
//		if(wCRC==0)
//		{
//			g_wCRCCal = 0x1111;
//			return;
//		}
//		break;
//	case 0x1111:
//		wCountSndByte = Protocol_OnTaskProcess();
//		if(wCountSndByte)
//		{
//			g_pSndPointer = g_CommBuffer;
//			g_pSndEndPointer = g_CommBuffer + wCountSndByte;
//			g_wCRCCal = 0x2222;
//			return;
//		}
//		break;
//	case 0x2222:
//		wCountSndByte = g_pSndEndPointer - g_pSndPointer;
//		wCRC = CalculateCRCByte(g_CommBuffer,wCountSndByte);
//		*g_pSndEndPointer++ = (BYTE)(wCRC&0xff);
//		*g_pSndEndPointer++ = (BYTE)(wCRC>>8);
//		g_wCountTimeout = COMM_TIMEOUT;
//		g_wCommStatus = COMMSTATUS_SNDING1;
//		g_wCRCCal = 0x0000;
//		return;
//// 		break;
//	default: break;
//	}

//	g_wCRCCal = 0x0000;
//	g_wCommStatus = COMMSTATUS_NULL;

	WORD wCountSndByte;
	WORD wCRC;
	if(g_wCommStatus!=COMMSTATUS_SNDOPEN) return;
    wCRC = CalculateCRCByte(g_CommBuffer,(WORD)(g_pRcvEndPointer-g_CommBuffer));
    if(wCRC!=0)
    {
        g_wCommStatus = COMMSTATUS_NULL;
        return;
    }

    wCountSndByte = Protocol_OnTaskProcess();
    if(wCountSndByte==0)
    {
        g_wCommStatus = COMMSTATUS_NULL;
        return;
    }

    g_pSndPointer = g_CommBuffer;
    g_pSndEndPointer = g_CommBuffer + wCountSndByte;

    wCountSndByte = g_pSndEndPointer - g_pSndPointer;
    wCRC = CalculateCRCByte(g_CommBuffer,wCountSndByte);
    *g_pSndEndPointer++ = (BYTE)(wCRC&0xff);
    *g_pSndEndPointer++ = (BYTE)(wCRC>>8);
    g_wCountTimeout = COMM_TIMEOUT;
    g_wCommStatus = COMMSTATUS_SNDING1;

//	g_wCRCCal = 0x0000;
//	g_wCommStatus = COMMSTATUS_NULL;
}
/*
void Protocol_OnTimer10ms(void)
{
	WORD wCountSndByte;
	if(g_wCommStatus!=COMMSTATUS_SNDOPEN) return;
	wCountSndByte = Protocol_OnTaskProcess();

	if(wCountSndByte)
	{
		g_pSndPointer = g_CommBuffer;
		g_pSndEndPointer = g_CommBuffer + wCountSndByte + 2;
		g_wCountTimeout = COMM_TIMEOUT;
		g_wCommStatus = COMMSTATUS_SNDING1;
		return;
	}
	g_wCommStatus = COMMSTATUS_NULL;
}
*/
void Protocol_OnRcvProcess(BYTE RcvData)
{
	WORD wTemp;
	switch(g_wCommStatus)
	{
	case COMMSTATUS_RCV_ADDR:
		if(RcvData==(BYTE)g_wModAddr||RcvData==0x00||RcvData==0xff)
		{
// 			g_wCommLight = 1;
			g_wCountTimeout = COMM_TIMEOUT;
			g_wCommStatus = COMMSTATUS_RCV_HEAD;
			g_pRcvPointer = g_CommBuffer;
			g_pRcvEndPointer = g_CommBuffer+6;
			*g_pRcvPointer++ = RcvData;
		}
		else g_wCommStatus = COMMSTATUS_NULL;
		break;
	case COMMSTATUS_RCV_HEAD:
		*g_pRcvPointer++ = RcvData;
		if(g_pRcvPointer>=g_pRcvEndPointer)
		{
			g_wCommStatus = COMMSTATUS_RCV_DATA;
			wTemp = g_CommBuffer[1];
			if(wTemp==0x03)
			{
				g_pRcvEndPointer = g_CommBuffer+8;
				break;
			}
			else if(wTemp==0x10)
			{
				wTemp = g_CommBuffer[5]+(g_CommBuffer[4]<<8);
				g_pRcvEndPointer = g_CommBuffer+9+wTemp*2;
				if(wTemp>125) g_pRcvEndPointer++;
				if(g_pRcvEndPointer<=g_CommBuffer+COMM_BUFFERSIZE) break;
			}
			else if(wTemp==0x05)
			{
				g_pRcvEndPointer = g_CommBuffer+8;
				break;
			}
			g_wCommStatus = COMMSTATUS_NULL;
		}
		break;
	case COMMSTATUS_RCV_DATA:
		*g_pRcvPointer++ = RcvData;
		if(g_pRcvPointer>=g_pRcvEndPointer)
		{
			g_wCommStatus = COMMSTATUS_SNDOPEN;
		}
		break;
	}
}

WORD Protocol_OnTaskProcess(void)
{
	WORD wCountSndByte;
	WORD wLogAddr,wLength;
	WORD* pDeviceAddr;

	wCountSndByte = 0;
	wLogAddr = g_CommBuffer[3]+(g_CommBuffer[2]<<8);
	wLength = g_CommBuffer[5]+(g_CommBuffer[4]<<8);

	if(g_CommBuffer[1]==0x03)
	{
		pDeviceAddr = Table_GetDeviceAddr(wLogAddr,wLength,0);
		if(pDeviceAddr)
		{
			wCountSndByte = wLength*2;wCountSndByte = wLength*2;
			if(wLength<=125)
			{
				g_CommBuffer[2] = (BYTE)wCountSndByte;
				Protocol_CopyWordToByte(g_CommBuffer+3,pDeviceAddr,wLength);
				wCountSndByte += 3;
			}
			else
			{
				g_CommBuffer[2] = (BYTE)(wCountSndByte&0xff);
				g_CommBuffer[3] = (BYTE)(wCountSndByte>>8);
				Protocol_CopyWordToByte(g_CommBuffer+4,pDeviceAddr,wLength);
				wCountSndByte += 4;
			}
		}
        else
        {
            wCountSndByte = Table_ReadExt(wLogAddr, wLength);
            if(wCountSndByte)
            {
//                 wCountSndByte = wLength*2;
                g_CommBuffer[2] = (BYTE)wCountSndByte;
                wCountSndByte += 3;
            }
            else
            {
                wCountSndByte = (WORD)(g_pRcvEndPointer-g_CommBuffer);
                wCountSndByte -= 2;
//                 Protocol_CopyByteToByte(g_CommBuffer,g_CommBuffer,wCountSndByte);
                g_CommBuffer[1] = (BYTE)(g_CommBuffer[1]|0x80);
            }
        }
	}
	else if(g_CommBuffer[1]==0x10)
	{
#ifdef LOGADDR_CONTROLOUT
		if((wLogAddr&0xff00)==LOGADDR_CONTROLOUT)
		{
			Table_ControlOut(wLogAddr-LOGADDR_CONTROLOUT,(WORD)(g_CommBuffer[8]+(g_CommBuffer[7]<<8)));
		}
		else
#endif
		{
			pDeviceAddr = Table_GetDeviceAddr(wLogAddr,wLength,1);
			if(pDeviceAddr)
			{
				if(wLength<=125) Protocol_CopyByteToWord(pDeviceAddr,g_CommBuffer+7,wLength);
				else Protocol_CopyByteToWord(pDeviceAddr,g_CommBuffer+8,wLength);
				MyApp_OnUpdateDevice(pDeviceAddr, TRUE);
			}
		}
		wCountSndByte = 6;
	}
	else if(g_CommBuffer[1]==0x05)
	{
		if((wLogAddr&0xff00)==LOGADDR_CONTROLOUT)
		{
			Table_RemoteControlOut(wLogAddr-LOGADDR_CONTROLOUT,(WORD)(g_CommBuffer[5]+(g_CommBuffer[4]<<8)));
		}
		pDeviceAddr = Table_GetDeviceAddr(wLogAddr,wLength,1);
		if(pDeviceAddr)
		{
			if(wLength<=125) Protocol_CopyByteToWord(pDeviceAddr,g_CommBuffer+3,wLength);
			else Protocol_CopyByteToWord(pDeviceAddr,g_CommBuffer+8,wLength);
			MyApp_OnUpdateDevice(pDeviceAddr, TRUE);
		}
		wCountSndByte = 6;
	}
	if(g_CommBuffer[0]==0x00) wCountSndByte = 0;
	return wCountSndByte;
}

