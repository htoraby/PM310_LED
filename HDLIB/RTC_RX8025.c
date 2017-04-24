
#include "main.h"

#define RTC_DEV_ADDR		0x64			// 时钟芯片

#define RX8025_REG_SEC      0x00
#define RX8025_REG_MIN      0x10
#define RX8025_REG_HOUR     0x20
#define RX8025_REG_WDAY     0x30
#define RX8025_REG_MDAY     0x40
#define RX8025_REG_MONTH    0x50
#define RX8025_REG_YEAR     0x60
#define RX8025_REG_DIGOFF   0x70
#define RX8025_REG_ALWMIN   0x80
#define RX8025_REG_ALWHOUR  0x90
#define RX8025_REG_ALWWDAY  0xa0
#define RX8025_REG_ALDMIN   0xb0
#define RX8025_REG_ALDHOUR  0xc0
/* 0x0d is reserved */
#define RX8025_REG_CTRL1    0xe0
#define RX8025_REG_CTRL2    0xf0

#define RX8025_BIT_CTRL1_CT     (7 << 0)
/* 1 Hz periodic level irq */
#define RX8025_BIT_CTRL1_CT_1HZ 4
#define RX8025_BIT_CTRL1_TEST   (1 << 3)
#define RX8025_BIT_CTRL1_1224   (1 << 5)
#define RX8025_BIT_CTRL1_DALE   (1 << 6)
#define RX8025_BIT_CTRL1_WALE   (1 << 7)

#define RX8025_BIT_CTRL2_DAFG   (1 << 0)
#define RX8025_BIT_CTRL2_WAFG   (1 << 1)
#define RX8025_BIT_CTRL2_CTFG   (1 << 2)
#define RX8025_BIT_CTRL2_PON    (1 << 4)
#define RX8025_BIT_CTRL2_XST    (1 << 5)
#define RX8025_BIT_CTRL2_VDET   (1 << 6)

#define RX8025_TEST         0x07

//*******************************************************************************************
//*名称: BYTE Bcd_convert_Hex(BYTE bcd_data)												*
//*功能: BCD码转16进制																		*
//*参数: Bcd_data  要转换的BCD码数据(0-100)													*
//*返回: 转换后的16进制数据																	*
//*******************************************************************************************
BYTE Bcd_convert_Hex(BYTE Bcd_data)
{
    BYTE temp;
    temp=((Bcd_data>>4)*10)+(Bcd_data&0x0f);
    return temp;
}

//*******************************************************************************************
//*名称: BYTE hex_convert_bcd(BYTE hex_dataa)												*
//*功能: 16进制转BCD码																		*
//*参数: hex_data 要转换的16进制数据(0-100)													*
//*返回: 转换后的BCD码数据																	*
//*******************************************************************************************
BYTE Hex_convert_Bcd(BYTE hex_data)
{
    BYTE temp;
    BYTE bcd_data;
    temp=hex_data%100;
    bcd_data=(temp/10<<4)|(temp%10);
    return bcd_data;
}

BOOL RTC_IsError(void)
{
    BYTE Temp[2];
//     BOOL bStatus = FALSE;

    Temp[0] = 0x5D;
    Temp[1] = 0x09;

    I2C2WriteDataByte(RTC_DEV_ADDR,RX8025_TEST,Temp,2);
//     if(!bStatus) return TRUE;
    Temp[0] = 0x00;
    Temp[1] = 0x00;
    I2C2ReadDataByte(RTC_DEV_ADDR,RX8025_TEST,Temp,2);
    if((Temp[0]&0x7f)!=0x5d || (Temp[1]&0x1f)!=0x09) return TRUE;

    I2C2ReadDataByte(RTC_DEV_ADDR,RX8025_REG_CTRL2,Temp,1);
    if(Temp[0]&RX8025_BIT_CTRL2_XST==0)
    {
        return TRUE;                // 晶振停止
    }

    return FALSE;
}

//*******************************************************************************************
//*名称: void ReadTime(DEVICETIME* pDeviceTime)												*
//*功能: 从RTC芯片获取时钟数据 并存放到指定数组												*
//*参数:																					*
//*返回:																					*
//*******************************************************************************************
void RTC_ReadTime(DEVICETIME* pDeviceTime)
{
    BYTE Temp[7];
    I2C2ReadDataByte(RTC_DEV_ADDR,RX8025_REG_SEC,Temp,7);

    pDeviceTime->wSecond = Bcd_convert_Hex(Temp[0]&0x7F);		// 秒
    pDeviceTime->wMinute = Bcd_convert_Hex(Temp[1]&0x7F);		// 分
    pDeviceTime->wHour = Bcd_convert_Hex(Temp[2]&0x3F);			// 小时
    pDeviceTime->wDay = Bcd_convert_Hex(Temp[4]&0x3F);			// 日
    pDeviceTime->wMonth = Bcd_convert_Hex(Temp[5]&0x1F);		// 月
    pDeviceTime->wYear = Bcd_convert_Hex(Temp[6]);				// 年
}

//*******************************************************************************************
//*名称: WriteTime(DEVICETIME* pDeviceTime)													*
//*功能: 将时钟数据重写入RX8025片															*
//*参数: 																					*
//*返回: 																					*
//*******************************************************************************************
void RTC_WriteTime(DEVICETIME* pDeviceTime)
{
    BYTE Temp[7];

    Temp[0] = Hex_convert_Bcd(pDeviceTime->wSecond);
    Temp[1] = Hex_convert_Bcd(pDeviceTime->wMinute);
    Temp[2] = Hex_convert_Bcd(pDeviceTime->wHour);
    Temp[3] = 0;
    Temp[4] = Hex_convert_Bcd(pDeviceTime->wDay);
    Temp[5] = Hex_convert_Bcd(pDeviceTime->wMonth);
    Temp[6] = Hex_convert_Bcd(pDeviceTime->wYear);

    I2C2WriteDataByte(RTC_DEV_ADDR,RX8025_REG_SEC,Temp,7);		// 将设置时间写入RX8025
//     I2CResetHW(&g_i2c);
//    DEVICETIME Time;
//     ReadTime(pDeviceTime);
}

//*******************************************************************************************
//*名称: void OnInit(void)																	*
//*功能: 如果时钟数据不对则写入初始值														*
//*参数:																					*
//*返回:																					*
//*******************************************************************************************
void RTC_OnInit(const DEVICETIME* pDeviceTime)
{
    BYTE Tmp[2];
    DEVICETIME Time;
    RTC_ReadTime(&Time);

// ------------------清低电压标志------------------------
    Tmp[0] = 0x20;              // 24小时制
    Tmp[1] = 0x20;              // 清除低电压标志
    I2C2WriteDataByte(RTC_DEV_ADDR,RX8025_REG_CTRL1,Tmp,2);
// -------------------------------------------------------

    if(Time.wSecond>=60||Time.wMinute>=60||Time.wHour>=24||
    Time.wDay>=32||Time.wMonth>=13||Time.wYear>=100)
    {
        Time = *pDeviceTime;
        RTC_WriteTime(&Time);
    }
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------
