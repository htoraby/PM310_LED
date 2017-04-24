#ifndef __MAIN1_H
#define __MAIN1_H

#include "PUB\__Tool.h"
#include "PUB\__Time.h"
/*
#define BAUDRATE_300		0
#define BAUDRATE_600		1
#define BAUDRATE_1200		2
#define BAUDRATE_2400		3
#define BAUDRATE_4800		4
#define BAUDRATE_9600		5
#define BAUDRATE_19200		6
#define BAUDRATE_38400		7
*/
#define BAUDRATE_2400		0
#define BAUDRATE_4800		1
#define BAUDRATE_9600		2
#define BAUDRATE_19200		3
#define BAUDRATE_38400		4
// #define BAUDRATE_57600		7

#define BAUDRATE_20k		0
#define BAUDRATE_35k		1
#define BAUDRATE_50k		2
#define BAUDRATE_75k		3
#define BAUDRATE_125k		4
#define BAUDRATE_250k		5
#define BAUDRATE_500k		6
#define BAUDRATE_1M			7

#define LINKIN_NULL			0x0000		//无效连接;
#define LINKIN_IN01			0x0001		//连接开关量输入IN01;
#define LINKIN_IN02			0x0002		//连接开关量输入IN02;
#define LINKIN_IN03			0x0003		//连接开关量输入IN03;
#define LINKIN_IN04			0x0004		//连接开关量输入IN04;
#define LINKIN_IN05			0x0005		//连接开关量输入IN05;
#define LINKIN_IN06			0x0006		//连接开关量输入IN06;
#define LINKIN_IN07			0x0007		//连接开关量输入IN07;
#define LINKIN_IN08			0x0008		//连接开关量输入IN08;
#define LINKIN_IN09			0x0009		//连接开关量输入IN09;
#define LINKIN_IN10			0x000a		//连接开关量输入IN10;
#define LINKIN_IN11			0x000b		//连接开关量输入IN11;
#define LINKIN_IN12			0x000c		//连接开关量输入IN12;
#define LINKIN_IN13			0x000d		//连接开关量输入IN13;
#define LINKIN_IN14			0x000e		//连接开关量输入IN14;
#define LINKIN_IN15			0x000f		//连接开关量输入IN15;
#define LINKIN_IN16			0x0010		//连接开关量输入IN16;

#define LINKOUT_NULL		0x0000		//无效连接;
#define LINKOUT_KH01		0x0001		//连接继电器输出KH01;
#define LINKOUT_KH02		0x0002		//连接继电器输出KH02;
#define LINKOUT_KH03		0x0003		//连接继电器输出KH03;
#define LINKOUT_KH04		0x0004		//连接继电器输出KH04;
#define LINKOUT_KH05		0x0005		//连接继电器输出KH05;
#define LINKOUT_KH06		0x0006		//连接继电器输出KH06;
#define LINKOUT_KH07		0x0007		//连接继电器输出KH07;
#define LINKOUT_KH08		0x0008		//连接继电器输出KH08;
#define LINKOUT_KH09		0x0009		//连接继电器输出KH09;
#define LINKOUT_KH10		0x000a		//连接继电器输出KH10;
#define LINKOUT_KH11		0x000b		//连接继电器输出KH11;
#define LINKOUT_KH12		0x000c		//连接继电器输出KH12;
#define LINKOUT_KH13		0x000d		//连接继电器输出KH13;
#define LINKOUT_KH14		0x000e		//连接继电器输出KH14;
#define LINKOUT_KH15		0x000f		//连接继电器输出KH15;
#define LINKOUT_KH16		0x0010		//连接继电器输出KH16;

#define MODECT_2CT			0			//CT接线模式:2CT;
#define MODECT_3CT			1			//CT接线模式:3CT;

#define MODEPT_WYE			0			//PT接线模式:Y/Y;
#define MODEPT_DEL			1			//PT接线模式:V/V;
// #define MODEPT_UAC			2			//PT接线模式:单相Uac接入;

#define MODEKPU_TRIP		0			// KPU启动模式:保护联动
#define MODEKPU_PICKUP		1			// KPU启动模式:保护启动

#define MODEPROTECT_2P		0			// 保护模式:2相保护
#define MODEPROTECT_3P		1			// 保护模式:3相保护

#define CRCINFO_TYPE_CRC16      0xFFFFFFFF
#define CRCINFO_TYPE_CRC32      0x00000000

typedef struct
{
    DWORD dwHeader0;
    DWORD dwHeader1;
    DWORD dwLen;
    DWORD dwCRC32;
    DWORD dwType;
    DWORD dwRes1;
    DWORD dwRes2;
    DWORD dwRes3;
}tCRC32INFO;

#ifdef __cplusplus
extern "C" {
#endif

extern void OnMainInit(void);
extern void OnMainTimer1ms(void);
extern void OnMainTimer10ms(void);
extern void OnMainTimer250ms(void);
extern void OnMainTimer1000ms(void);
extern void OnMainWhileLoop(void);
extern void OnMainPollingComm(void);
extern void OnMainPollingCommET(void);
extern void GetADCResult(WORD wChSel,WORD DotNum,WORD wResult);
extern void OnWaveRecord(WORD wCountAD);
extern void OnWaveRecord(WORD wCountAD);

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif/*__MAIN1_H*/

