#ifndef _STM32_I2CSIM1_H
#define _STM32_I2CSIM1_H

#define I2C_WDATAADDR		0x8000

#ifdef __cplusplus
extern "C" {
#endif

extern BYTE I2C1GetStatus(WORD wDevAddr);
extern void I2C1ReadDataByte(WORD wDevAddr,WORD wDataAddr,BYTE* pData,WORD wCountByte);
extern void I2C1ReadDataWord(WORD wDevAddr,WORD wDataAddr,WORD* pData,WORD wCountWord);
extern void I2C1WriteDataByte(WORD wDevAddr,WORD wDataAddr,BYTE* pData,WORD wCountByte);
extern void I2C1WriteDataWord(WORD wDevAddr,WORD wDataAddr,WORD* pData,WORD wCountWord);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // _F28035_I2CSIM_H

