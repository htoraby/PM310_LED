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

#define LINKIN_NULL			0x0000		//��Ч����;
#define LINKIN_IN01			0x0001		//���ӿ���������IN01;
#define LINKIN_IN02			0x0002		//���ӿ���������IN02;
#define LINKIN_IN03			0x0003		//���ӿ���������IN03;
#define LINKIN_IN04			0x0004		//���ӿ���������IN04;
#define LINKIN_IN05			0x0005		//���ӿ���������IN05;
#define LINKIN_IN06			0x0006		//���ӿ���������IN06;
#define LINKIN_IN07			0x0007		//���ӿ���������IN07;
#define LINKIN_IN08			0x0008		//���ӿ���������IN08;
#define LINKIN_IN09			0x0009		//���ӿ���������IN09;
#define LINKIN_IN10			0x000a		//���ӿ���������IN10;
#define LINKIN_IN11			0x000b		//���ӿ���������IN11;
#define LINKIN_IN12			0x000c		//���ӿ���������IN12;
#define LINKIN_IN13			0x000d		//���ӿ���������IN13;
#define LINKIN_IN14			0x000e		//���ӿ���������IN14;
#define LINKIN_IN15			0x000f		//���ӿ���������IN15;
#define LINKIN_IN16			0x0010		//���ӿ���������IN16;

#define LINKOUT_NULL		0x0000		//��Ч����;
#define LINKOUT_KH01		0x0001		//���Ӽ̵������KH01;
#define LINKOUT_KH02		0x0002		//���Ӽ̵������KH02;
#define LINKOUT_KH03		0x0003		//���Ӽ̵������KH03;
#define LINKOUT_KH04		0x0004		//���Ӽ̵������KH04;
#define LINKOUT_KH05		0x0005		//���Ӽ̵������KH05;
#define LINKOUT_KH06		0x0006		//���Ӽ̵������KH06;
#define LINKOUT_KH07		0x0007		//���Ӽ̵������KH07;
#define LINKOUT_KH08		0x0008		//���Ӽ̵������KH08;
#define LINKOUT_KH09		0x0009		//���Ӽ̵������KH09;
#define LINKOUT_KH10		0x000a		//���Ӽ̵������KH10;
#define LINKOUT_KH11		0x000b		//���Ӽ̵������KH11;
#define LINKOUT_KH12		0x000c		//���Ӽ̵������KH12;
#define LINKOUT_KH13		0x000d		//���Ӽ̵������KH13;
#define LINKOUT_KH14		0x000e		//���Ӽ̵������KH14;
#define LINKOUT_KH15		0x000f		//���Ӽ̵������KH15;
#define LINKOUT_KH16		0x0010		//���Ӽ̵������KH16;

#define MODECT_2CT			0			//CT����ģʽ:2CT;
#define MODECT_3CT			1			//CT����ģʽ:3CT;

#define MODEPT_WYE			0			//PT����ģʽ:Y/Y;
#define MODEPT_DEL			1			//PT����ģʽ:V/V;
// #define MODEPT_UAC			2			//PT����ģʽ:����Uac����;

#define MODEKPU_TRIP		0			// KPU����ģʽ:��������
#define MODEKPU_PICKUP		1			// KPU����ģʽ:��������

#define MODEPROTECT_2P		0			// ����ģʽ:2�ౣ��
#define MODEPROTECT_3P		1			// ����ģʽ:3�ౣ��

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

