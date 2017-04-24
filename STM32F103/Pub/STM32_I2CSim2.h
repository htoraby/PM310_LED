#ifndef _STM32_I2CSIM2_H
#define _STM32_I2CSIM2_H

#define I2C_WDATAADDR		0x8000

#ifdef __cplusplus
extern "C" {
#endif

extern BYTE I2C2GetStatus(WORD wDevAddr);
extern void I2C2ReadDataByte(WORD wDevAddr,WORD wDataAddr,BYTE* pData,WORD wCountByte);
extern void I2C2ReadDataWord(WORD wDevAddr,WORD wDataAddr,WORD* pData,WORD wCountWord);
extern void I2C2WriteDataByte(WORD wDevAddr,WORD wDataAddr,BYTE* pData,WORD wCountByte);
extern void I2C2WriteDataWord(WORD wDevAddr,WORD wDataAddr,WORD* pData,WORD wCountWord);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // _F28035_I2CSIM_H

