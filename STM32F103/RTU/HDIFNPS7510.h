#include "stm32f10x.h"
#include "STM32F103VC.h"
#include "STM32_I2CSim1.h"
#include "STM32_I2CSim2.h"
#include "STM32_SCI.h"
#include "PUB\__LCD.h"
#include "PUB\__LCDMem.h"
#include "HDLIB\ArEEPROM_FM24CLXX.h"
#include "HDLIB\SST25VF016B.h"
#include "HDLIB\RTC_RX8025.h"
#include "HDLIB\MyLCD_UC1698U.h"

#define ADDRCRC32INFO       (0x8003000+0x130)

#define FM24CL64
#define LCD_DIRECT_0

#define HKEY_UP              0x01
#define HKEY_DOWN            0x02
#define HKEY_OK              0x04
#define HKEY_CANCEL          0x08

#ifdef __cplusplus
extern "C" {
#endif

extern void MyHDIF_OnInit1(void);
extern void MyHDIF_OnInit2(void);
extern void MyHDIF_OnTimer1ms(void);
extern void MyHDIF_OnTimer10ms(void);
extern void MyHDIF_OnTimer1000ms(void);
extern void MyHDIF_OnWhileLoop(void);
extern void MyHDIF_OnPollingComm(void);
extern void MyHDIF_OnSCIOpenTX(void);
extern void MyHDIF_OnSCICloseTX(void);
extern void LCDWrite(BYTE Data, BOOL bCmd);

//extern BOOL BIORead(WORD wAddr, BYTE* pData);
//extern BOOL BIOWrite(WORD wAddr, BYTE Data);

//extern BOOL HMIWrite(WORD wAddr, BYTE Data);
//extern BOOL HMIRead(WORD wAddr, BYTE* pData);
//extern void LCDWrite(BYTE Data,      // 
//                BOOL bCmd,      // 0:cmd;1:Data
//                BOOL blight);     // ±³¹â:0:Ãð,1:ÁÁ

#ifdef __cplusplus
}
#endif /* extern "C" */

