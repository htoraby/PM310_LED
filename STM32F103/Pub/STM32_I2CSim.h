#ifndef _F28035_I2CSIM_H
#define _F28035_I2CSIM_H

#define I2C_WDATAADDR		0x8000

#ifdef __cplusplus
extern "C" {
#endif

extern BYTE I2CGetStatus(WORD wDevAddr);
extern void I2CReadDataByte(WORD wDevAddr,WORD wDataAddr,BYTE* pData,WORD wCountByte);
extern void I2CReadDataWord(WORD wDevAddr,WORD wDataAddr,WORD* pData,WORD wCountWord);
extern void I2CWriteDataByte(WORD wDevAddr,WORD wDataAddr,BYTE* pData,WORD wCountByte);
extern void I2CWriteDataWord(WORD wDevAddr,WORD wDataAddr,WORD* pData,WORD wCountWord);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // _F28035_I2CSIM_H

