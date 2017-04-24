#ifndef __DEVICESET_H
#define __DEVICESET_H

//-----------------------------------------------------------------------------
typedef struct _DeviceSet
{
	WORD m_wCountNew;				//�豸�������¼���;
	WORD m_wCountOld;				//�豸�������¼���(���ٸ�����);
	WORD* m_pDevice;				//ָ���豸����ָ��;
	WORD m_wDeviceLength;			//�豸��������;
	WORD m_wDeviceErrorMask;		//�豸�����Լ��쳣������;
	WORD m_wDeviceAddSum;			//�豸�����ۼ�У����;
	WORD m_wDeviceAddrEEPROM;		//�豸������EEPROM�����ַ;
	WORD m_wErrorCnt;
}DeviceSet;

//˵��:�趨�豸����������ز���;
extern void DeviceSet_SetDeviceSet(DeviceSet* pthis,WORD* pDevice,WORD wDeviceLength,WORD wDeviceErrorMask,WORD wDeviceAddrEEPROM);
//˵��:��ʼ���豸����������ز���,���Զ���EEPROM�ж�ȡ�豸����;
extern void DeviceSet_InitDeviceSet(DeviceSet* pthis);
//˵��:��EEPROM�ж�ȡ�豸����;
extern void DeviceSet_ReadDeviceSet(DeviceSet* pthis);
//˵��:���豸��������У�������,����Ƿ��쳣,�����쳣��EEPROM���ض�;
extern BOOL DeviceSet_CheckDeviceSet(DeviceSet* pthis);
//˵��:����豸�������¼����Ƿ�ı�,���ı�,�����µ��豸�������浽EEPROM��;
extern void DeviceSet_UpdateDeviceSet(DeviceSet* pthis);
#ifdef _WIN32
//˵��:ǿ�����µ��豸�������浽EEPROM��;
extern void DeviceSet_ForceUpdateDeviceSet(DeviceSet* pthis);
#endif
//˵��:�����������Ƿ����ڱ��豸����,���������¼���У����,���ı���¼���;
extern BOOL DeviceSet_OnUpdateDevice(DeviceSet* pthis,WORD* pData);


#endif/*__DEVICESET_H*/


/******************************************************************************
ģ�鹦��:
��Ҫʵ�ֶ��豸��������ͳһ����,�����豸�����Ķ�ȡ,����,���¼��,�쳣���;
ʹ�ò���:
1.��g_app.OnInit()�е���SetDeviceSet()�Ը��豸���������г����趨;
2.��g_app.OnInit()�е���InitDeviceSet()���г�ʼ��,����:���¼�����ʼ��,���Զ���ȡ�豸����;
3.��g_app.OnWhileLoop()�в�ͣ�ĵ������º���:
  SetDeviceSet():�Է��趨����������Ƿ��޸�;
  CheckDeviceSet():����豸�����Ƿ��쳣,���쳣���ض�;
  UpdateDeviceSet():�����¼���,�����������Զ�����;
4.��g_app.OnUpdateDevice()�е���OnUpdateDevice(),�Լ���Ƿ�Ϊ���豸�������ݱ�����;
*/
//ThinkBoy,ShenBo,2006/04/30;
