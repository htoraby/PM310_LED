#ifndef CMYTABLEDMR_H
#define CMYTABLEDMR_H

//#define LOGADDR_DEVICETIME		0x0000		//RW;
//#define LOGADDR_DEVICEINFO		0x0007		//R;
//#define LOGADDR_ANALOGDATA		0x0100		//R;
//#define LOGADDR_ANALOGDATAEXT	0x0200		//R;
//#define LOGADDR_ANALOGWAVE		0x0300		//R;
//#define LOGADDR_DFTDATASET		0x0900		//R;
//#define LOGADDR_CONTROLOUT		0x0a00		//RW;
//#define LOGADDR_DEVICEPARAM		0x0b00		//RW;
//#define LOGADDR_DEVICEINPARAM	0x0c00		//RW;
//#define LOGADDR_DEVICEDCPARAM	0x1100		//RW;
//#define LOGADDR_DEVICEREGULATE	0x1300		//RW;
//#define LOGADDR_DEVICESETPOINT	0x1400		//RW;
//#define LOGADDR_DEVICEDRW		0x1600		//RW;
//#define LOGADDR_DEVICELAD		0x1800		//RW;
//#define LOGADDR_EVENTTABLE		0x1a00		//R;
//#define LOGADDR_WAVERECORD		0x2000		//R;

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
#define LOGADDR_WAVERECORD		0x2000		//R

#define LOGADDR_WAVE1HEAD       0x2000		//R;
#define LOGADDR_WAVE1UA1        0x2012		//R;
#define LOGADDR_WAVE1UA2        0x2062		//R;
#define LOGADDR_WAVE1UA3        0x20B2		//R;
#define LOGADDR_WAVE1UB1        0x2102		//R;
#define LOGADDR_WAVE1UB2        0x2152		//R;
#define LOGADDR_WAVE1UB3        0x21A2		//R;
#define LOGADDR_WAVE1UC1        0x21F2		//R;
#define LOGADDR_WAVE1UC2        0x2242		//R;
#define LOGADDR_WAVE1UC3        0x2292		//R;
#define LOGADDR_WAVE1IA1        0x22E2		//R;
#define LOGADDR_WAVE1IA2        0x2332		//R;
#define LOGADDR_WAVE1IA3        0x2382		//R;
#define LOGADDR_WAVE1IB1        0x23D2		//R;
#define LOGADDR_WAVE1IB2        0x2422		//R;
#define LOGADDR_WAVE1IB3        0x2472		//R;
#define LOGADDR_WAVE1IC1        0x24C2		//R;
#define LOGADDR_WAVE1IC2        0x2512		//R;
#define LOGADDR_WAVE1IC3        0x2562		//R;
#define LOGADDR_WAVE1DI1        0x25B2		//R;
#define LOGADDR_WAVE1DI2        0x2602		//R;
#define LOGADDR_WAVE1DI3        0x2652		//R;
#define LOGADDR_WAVE2HEAD       0x26A2		//R;
#define LOGADDR_WAVE2UA1        0x26B4		//R;
#define LOGADDR_WAVE2UA2        0x2704		//R;
#define LOGADDR_WAVE2UA3        0x2754		//R;
#define LOGADDR_WAVE2UB1        0x27A4		//R;
#define LOGADDR_WAVE2UB2        0x28F4		//R;
#define LOGADDR_WAVE2UB3        0x2844		//R;
#define LOGADDR_WAVE2UC1        0x2894		//R;
#define LOGADDR_WAVE2UC2        0x28E4		//R;
#define LOGADDR_WAVE2UC3        0x2934		//R;
#define LOGADDR_WAVE2IA1        0x2984		//R;
#define LOGADDR_WAVE2IA2        0x29D4		//R;
#define LOGADDR_WAVE2IA3        0x2A24		//R;
#define LOGADDR_WAVE2IB1        0x2A74		//R;
#define LOGADDR_WAVE2IB2        0x2AC4		//R;
#define LOGADDR_WAVE2IB3        0x2B14		//R;
#define LOGADDR_WAVE2IC1        0x2B64		//R;
#define LOGADDR_WAVE2IC2        0x2BB4		//R;
#define LOGADDR_WAVE2IC3        0x2C04		//R;
#define LOGADDR_WAVE2DI1        0x2C54		//R;
#define LOGADDR_WAVE2DI2        0x2CA4		//R;
#define LOGADDR_WAVE2DI3        0x2DF4		//R;
#define LOGADDR_WAVE3HEAD       0x2D44		//R;
#define LOGADDR_WAVE3UA1        0x2D56		//R;
#define LOGADDR_WAVE3UA2        0x2DA6		//R;
#define LOGADDR_WAVE3UA3        0x2DF6		//R;
#define LOGADDR_WAVE3UB1        0x2E46		//R;
#define LOGADDR_WAVE3UB2        0x2E96		//R;
#define LOGADDR_WAVE3UB3        0x2EE6		//R;
#define LOGADDR_WAVE3UC1        0x2F36		//R;
#define LOGADDR_WAVE3UC2        0x2F86		//R;
#define LOGADDR_WAVE3UC3        0x2FD6		//R;
#define LOGADDR_WAVE3IA1        0x3026		//R;
#define LOGADDR_WAVE3IA2        0x3076		//R;
#define LOGADDR_WAVE3IA3        0x30C6		//R;
#define LOGADDR_WAVE3IB1        0x3116		//R;
#define LOGADDR_WAVE3IB2        0x3166		//R;
#define LOGADDR_WAVE3IB3        0x31B6		//R;
#define LOGADDR_WAVE3IC1        0x3206		//R;
#define LOGADDR_WAVE3IC2        0x3256		//R;
#define LOGADDR_WAVE3IC3        0x32A6		//R;
#define LOGADDR_WAVE3DI1        0x32F6		//R;
#define LOGADDR_WAVE3DI2        0x3346		//R;
#define LOGADDR_WAVE3DI3        0x3396		//R;
#define LOGADDR_WAVE4HEAD       0x33E6		//R;
#define LOGADDR_WAVE4UA1        0x33F8		//R;
#define LOGADDR_WAVE4UA2        0x3448		//R;
#define LOGADDR_WAVE4UA3        0x3498		//R;
#define LOGADDR_WAVE4UB1        0x34E8		//R;
#define LOGADDR_WAVE4UB2        0x3538		//R;
#define LOGADDR_WAVE4UB3        0x3588		//R;
#define LOGADDR_WAVE4UC1        0x35D8		//R;
#define LOGADDR_WAVE4UC2        0x3628		//R;
#define LOGADDR_WAVE4UC3        0x3678		//R;
#define LOGADDR_WAVE4IA1        0x36C8		//R;
#define LOGADDR_WAVE4IA2        0x3718		//R;
#define LOGADDR_WAVE4IA3        0x3768		//R;
#define LOGADDR_WAVE4IB1        0x37B8		//R;
#define LOGADDR_WAVE4IB2        0x3808		//R;
#define LOGADDR_WAVE4IB3        0x3858		//R;
#define LOGADDR_WAVE4IC1        0x38A8		//R;
#define LOGADDR_WAVE4IC2        0x38F8		//R;
#define LOGADDR_WAVE4IC3        0x3948		//R;
#define LOGADDR_WAVE4DI1        0x3998		//R;
#define LOGADDR_WAVE4DI2        0x39E8		//R;
#define LOGADDR_WAVE4DI3        0x3A38		//R
#define LOGADDR_WAVE5HEAD       0x3A88		//R;
#define LOGADDR_WAVE5UA1        0x3A9A		//R;
#define LOGADDR_WAVE5UA2        0x3AEA		//R;
#define LOGADDR_WAVE5UA3        0x3B3A		//R;
#define LOGADDR_WAVE5UB1        0x3B8A		//R;
#define LOGADDR_WAVE5UB2        0x3BDA		//R;
#define LOGADDR_WAVE5UB3        0x3C2A		//R;
#define LOGADDR_WAVE5UC1        0x3C7A		//R;
#define LOGADDR_WAVE5UC2        0x3CCA		//R;
#define LOGADDR_WAVE5UC3        0x3D1A		//R;
#define LOGADDR_WAVE5IA1        0x3D6A		//R;
#define LOGADDR_WAVE5IA2        0x3DBA		//R;
#define LOGADDR_WAVE5IA3        0x3E0A		//R;
#define LOGADDR_WAVE5IB1        0x3E5A		//R;
#define LOGADDR_WAVE5IB2        0x3EAA		//R;
#define LOGADDR_WAVE5IB3        0x3EFA		//R;
#define LOGADDR_WAVE5IC1        0x3F4A		//R;
#define LOGADDR_WAVE5IC2        0x3F9A		//R;
#define LOGADDR_WAVE5IC3        0x3FEA		//R;
#define LOGADDR_WAVE5DI1        0x403A		//R;
#define LOGADDR_WAVE5DI2        0x408A		//R;
#define LOGADDR_WAVE5DI3        0x40DA		//R

// #define LOGADDR_DEVICEDCPARAM	0x0c00		//RW;
// #define LOGADDR_DEVICEREGULATE	0x1100		//RW;
// #define LOGADDR_DEVICESETPOINT	0x1200		//RW;
// #define LOGADDR_DEVICEDRW		0x1400		//RW;
// #define LOGADDR_DEVICELAD		0x1600		//RW;
// #define LOGADDR_EVENTTABLE		0x1800		//R;
// #define LOGADDR_WAVERECORD		0x1c00		//R;

#define CONTROLOUT_INITDEVICE	0x0000		//初始化设备;
#define CONTROLOUT_RESETDEVICE	0x0001		//复归信号;
#define CONTROLOUT_FREEZEWAVE	0x0002		//冻结故障录波;
#define CONTROLOUT_ADJUST   	0x0003		//校正;

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
extern void Table_RemoteControlOut(WORD wControlOutCode,WORD wCommand);

extern short Table_ReadWaveRecod(WORD wLogAddr, WORD wLength);
extern short Table_ReadExt(WORD wLogAddr, WORD wLength);


#endif/*CMYTABLEDMR_H*/

