#include <Main.h>


//-----------------------------------------------------------------------------
void DeviceSet_SetDeviceSet(DeviceSet* pthis,WORD* pDevice,WORD wDeviceLength,WORD wDeviceErrorMask,WORD wDeviceAddrEEPROM)
{
	pthis->m_pDevice = pDevice;
	pthis->m_wDeviceLength = wDeviceLength;
	pthis->m_wDeviceErrorMask = wDeviceErrorMask;
	pthis->m_wDeviceAddrEEPROM = wDeviceAddrEEPROM;
}

void DeviceSet_InitDeviceSet(DeviceSet* pthis)
{
	pthis->m_wDeviceAddSum = 0xffff;
	pthis->m_wCountOld = 0;
	pthis->m_wErrorCnt = 0;
	DeviceSet_ReadDeviceSet(pthis);
	pthis->m_wCountNew = pthis->m_wCountOld;
}

void DeviceSet_ReadDeviceSet(DeviceSet* pthis)
{
// 	if(EEPROM_ReadBlock(pthis->m_wDeviceAddrEEPROM,&pthis->m_wCountOld,pthis->m_pDevice,pthis->m_wDeviceLength))
	if(Flash_ReadBlock(pthis->m_wDeviceAddrEEPROM,&pthis->m_wCountOld,pthis->m_pDevice,pthis->m_wDeviceLength))
	{
		pthis->m_wDeviceAddSum = GetAddSum(pthis->m_pDevice,pthis->m_wDeviceLength);
		g_deviceInfo.wDeviceStatus1 &= 0xffff^pthis->m_wDeviceErrorMask;
	}
	else
	{
		pthis->m_wDeviceAddSum = 0xffff;
		g_deviceInfo.wDeviceStatus1 |= pthis->m_wDeviceErrorMask;
	}
}

BOOL DeviceSet_CheckDeviceSet(DeviceSet* pthis)
{
	if(pthis->m_wDeviceAddSum!=GetAddSum(pthis->m_pDevice,pthis->m_wDeviceLength))
	{
		if(pthis->m_wDeviceAddSum!=GetAddSum(pthis->m_pDevice,pthis->m_wDeviceLength))
		{
			g_deviceInfo.wDeviceStatus1 |= pthis->m_wDeviceErrorMask;
			if(pthis->m_wErrorCnt++<5) DeviceSet_ReadDeviceSet(pthis);
			else pthis->m_wErrorCnt = 5;
			return FALSE;
		}
	}
	pthis->m_wErrorCnt = 0;
	g_deviceInfo.wDeviceStatus1 &= 0xffff^pthis->m_wDeviceErrorMask;
	return TRUE;
}

void DeviceSet_UpdateDeviceSet(DeviceSet* pthis)
{
	if(pthis->m_wCountOld!=pthis->m_wCountNew)
	{
		pthis->m_wCountOld = pthis->m_wCountNew;
		if(pthis->m_wDeviceAddSum==GetAddSum(pthis->m_pDevice,pthis->m_wDeviceLength))
		{
			pthis->m_wErrorCnt = 0;
// 			EEPROM_WriteBlock(pthis->m_wDeviceAddrEEPROM,&pthis->m_wCountOld,pthis->m_pDevice,pthis->m_wDeviceLength);
			Flash_WriteBlock(pthis->m_wDeviceAddrEEPROM,&pthis->m_wCountOld,pthis->m_pDevice,pthis->m_wDeviceLength);
		}
	}
}

#ifdef _WIN32
void DeviceSet_ForceUpdateDeviceSet(DeviceSet* pthis)
{
 	pthis->m_wDeviceAddSum = GetAddSum(pthis->m_pDevice,pthis->m_wDeviceLength);
//  	EEPROM_WriteBlock(pthis->m_wDeviceAddrEEPROM,&pthis->m_wCountOld,pthis->m_pDevice,pthis->m_wDeviceLength);
	Flash_WriteBlock(pthis->m_wDeviceAddrEEPROM,&pthis->m_wCountOld,pthis->m_pDevice,pthis->m_wDeviceLength);
}
#endif

BOOL DeviceSet_OnUpdateDevice(DeviceSet* pthis,WORD* pData)
{
	if(pData>=pthis->m_pDevice&&pData<pthis->m_pDevice+pthis->m_wDeviceLength)
	{
		pthis->m_wDeviceAddSum = GetAddSum(pthis->m_pDevice,pthis->m_wDeviceLength);
		pthis->m_wErrorCnt = 0;
		pthis->m_wCountNew++;
		return TRUE;
	}
	return FALSE;
}
