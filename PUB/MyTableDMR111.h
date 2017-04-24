#ifndef CMYTABLEDMR_H
#define CMYTABLEDMR_H

#define LOGADDR_DEVICETIME		0x0000		//RW;
#define LOGADDR_DEVICEINFO		0x0007		//R;
#define LOGADDR_ANALOGDATA		0x0100		//R;
#define LOGADDR_ANALOGDATAEXT	0x0200		//R;
#define LOGADDR_ANALOGWAVE		0x0300		//R;
#define LOGADDR_DFTDATASET		0x0900		//R;
#define LOGADDR_CONTROLOUT		0x0a00		//RW;
#define LOGADDR_DEVICEPARAM		0x0b00		//RW;
#define LOGADDR_DEVICEINPARAM	0x0c00		//RW;
#define LOGADDR_DEVICEDCPARAM	0x1100		//RW;
#define LOGADDR_DEVICEREGULATE	0x1300		//RW;
#define LOGADDR_DEVICESETPOINT	0x1400		//RW;
#define LOGADDR_DEVICEDRW		0x1600		//RW;
#define LOGADDR_DEVICELAD		0x1800		//RW;
#define LOGADDR_EVENTTABLE		0x1a00		//R;
#define LOGADDR_WAVERECORD		0x1d00		//R;

// #define LOGADDR_DEVICEDCPARAM	0x0c00		//RW;
// #define LOGADDR_DEVICEREGULATE	0x1100		//RW;
// #define LOGADDR_DEVICESETPOINT	0x1200		//RW;
// #define LOGADDR_DEVICEDRW		0x1400		//RW;
// #define LOGADDR_DEVICELAD		0x1600		//RW;
// #define LOGADDR_EVENTTABLE		0x1800		//R;
// #define LOGADDR_WAVERECORD		0x1c00		//R;


#define CONTROLOUT_INITDEVICE	0x0000		//��ʼ���豸;
#define CONTROLOUT_RESETDEVICE	0x0001		//�����ź�;
#define CONTROLOUT_FREEZEWAVE	0x0002		//�������¼��;
#define CONTROLOUT_KH01			0x0010		//KH01;
#define CONTROLOUT_KH02			0x0011		//KH02;
#define CONTROLOUT_KH03			0x0012		//KH03;
#define CONTROLOUT_KH04			0x0013		//KH04;
#define CONTROLOUT_KH05			0x0014		//KH05;
#define CONTROLOUT_KH06			0x0015		//KH06;
#define CONTROLOUT_KH07			0x0016		//KH07;
#define CONTROLOUT_KH08			0x0017		//KH08;
#define CONTROLOUT_KH09			0x0018		//KH09;
#define CONTROLOUT_KH10			0x0019		//KH10;
#define CONTROLOUT_KH11			0x001a		//KH11;
#define CONTROLOUT_KH12			0x001b		//KH12;
#define CONTROLOUT_KH13			0x001c		//KH13;
#define CONTROLOUT_KH14			0x001d		//KH14;
#define CONTROLOUT_KH15			0x001e		//KH15;
#define CONTROLOUT_KH16			0x001f		//KH16;
#define CONTROLOUT_KH17			0x0020		//KH17;
#define CONTROLOUT_KH18			0x0021		//KH18;
#define CONTROLOUT_KH19			0x0022		//KH19;
#define CONTROLOUT_KH20			0x0023		//KH20;
#define CONTROLOUT_KH21			0x0024		//KH21;
#define CONTROLOUT_KH22			0x0025		//KH22;
#define CONTROLOUT_KH23			0x0026		//KH23;
#define CONTROLOUT_KH24			0x0027		//KH24;
#define CONTROLOUT_KH25			0x0028		//KH25;
#define CONTROLOUT_KH26			0x0029		//KH26;
#define CONTROLOUT_KH27			0x002a		//KH27;
#define CONTROLOUT_KH28			0x002b		//KH28;
#define CONTROLOUT_KH29			0x002c		//KH29;
#define CONTROLOUT_KH30			0x002d		//KH30;
#define CONTROLOUT_KH31			0x002e		//KH31;
#define CONTROLOUT_KH32			0x002f		//KH32;

#define CONTROLOUT_VKH1			0x0030		//VKH1;
#define CONTROLOUT_VKH2			0x0031		//VKH2;
#define CONTROLOUT_VKH3			0x0032		//VKH3;
#define CONTROLOUT_VKH4			0x0033		//VKH4;
#define CONTROLOUT_VKH5			0x0034		//VKH5;
#define CONTROLOUT_VKH6			0x0035		//VKH6;
#define CONTROLOUT_VKH7			0x0036		//VKH7;
#define CONTROLOUT_VKH8			0x0037		//VKH8;

#define CONTROLOUT_KOT01		0x0040		//KOT01;
#define CONTROLOUT_KOT02		0x0041		//KOT02;
#define CONTROLOUT_KOT03		0x0042		//KOT03;
#define CONTROLOUT_KOT04		0x0043		//KOT04;
#define CONTROLOUT_KOT05		0x0044		//KOT05;
#define CONTROLOUT_KOT06		0x0045		//KOT06;
#define CONTROLOUT_KOT07		0x0046		//KOT07;
#define CONTROLOUT_KOT08		0x0047		//KOT08;

#define CONTROLOUT_KOC			0x0080		//KOC;
#define CONTROLOUT_KOT			0x0081		//KOT;

//-------------------------------------------------------------------

extern WORD* Table_GetDeviceAddr(WORD wLogAddr,WORD wLength,BOOL bAccessWrite);
extern void Table_ControlOut(WORD wControlOutCode,WORD wCommand);


#endif/*CMYTABLEDMR_H*/

