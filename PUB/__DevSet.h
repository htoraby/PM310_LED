#ifndef __DEVICESET_H
#define __DEVICESET_H

//-----------------------------------------------------------------------------
typedef struct _DeviceSet
{
	WORD m_wCountNew;				//设备参数更新计数;
	WORD m_wCountOld;				//设备参数更新计数(跟踪更新用);
	WORD* m_pDevice;				//指向设备参数指针;
	WORD m_wDeviceLength;			//设备参数长度;
	WORD m_wDeviceErrorMask;		//设备参数自检异常屏蔽码;
	WORD m_wDeviceAddSum;			//设备参数累加校验码;
	WORD m_wDeviceAddrEEPROM;		//设备参数在EEPROM保存地址;
	WORD m_wErrorCnt;
}DeviceSet;

//说明:设定设备参数集的相关参数;
extern void DeviceSet_SetDeviceSet(DeviceSet* pthis,WORD* pDevice,WORD wDeviceLength,WORD wDeviceErrorMask,WORD wDeviceAddrEEPROM);
//说明:初始化设备参数集的相关参数,并自动从EEPROM中读取设备参数;
extern void DeviceSet_InitDeviceSet(DeviceSet* pthis);
//说明:从EEPROM中读取设备参数;
extern void DeviceSet_ReadDeviceSet(DeviceSet* pthis);
//说明:对设备参数进行校验码测试,检测是否异常,发现异常从EEPROM中重读;
extern BOOL DeviceSet_CheckDeviceSet(DeviceSet* pthis);
//说明:检测设备参数更新计数是否改变,若改变,将最新的设备参数保存到EEPROM中;
extern void DeviceSet_UpdateDeviceSet(DeviceSet* pthis);
#ifdef _WIN32
//说明:强制最新的设备参数保存到EEPROM中;
extern void DeviceSet_ForceUpdateDeviceSet(DeviceSet* pthis);
#endif
//说明:检测更新数据是否属于本设备参数,若是则重新计算校验码,并改变更新计数;
extern BOOL DeviceSet_OnUpdateDevice(DeviceSet* pthis,WORD* pData);


#endif/*__DEVICESET_H*/


/******************************************************************************
模块功能:
主要实现对设备参数进行统一管理,包括设备参数的读取,保存,更新检测,异常检测;
使用步骤:
1.在g_app.OnInit()中调用SetDeviceSet()对各设备参数集进行场境设定;
2.在g_app.OnInit()中调用InitDeviceSet()进行初始化,包括:更新计数初始化,并自动读取设备参数;
3.在g_app.OnWhileLoop()中不停的调用以下函数:
  SetDeviceSet():以防设定场境被程序非法修改;
  CheckDeviceSet():检查设备参数是否异常,若异常则重读;
  UpdateDeviceSet():检测更新计数,若被更新则自动保存;
4.在g_app.OnUpdateDevice()中调用OnUpdateDevice(),以检测是否为本设备参数内容被更新;
*/
//ThinkBoy,ShenBo,2006/04/30;
