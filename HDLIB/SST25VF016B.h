#ifndef _SST25VF016B_H
#define _SST25VF016B_H

// Software Driver
// 
// SST25VF016B 16 Mbit(2M x 8) Serial Flash Memory
// 
// February 19th, 2009, Rev. 1.1
// 
// ABOUT THE SOFTWARE
// This application note provides software driver examples for SST25VF016B,
// Serial Flash. Extensive comments are included in each routine to describe 
// the function of each routine.  The interface coding uses polling method 
// rather than the SPI protocol to interface with these serial devices.  The
// functions are differentiated below in terms of the communication protocols
// (uses Mode 0) and specific device operation instructions. This code has been 
// designed to compile using the Keil compiler.
// 
// 
// ABOUT THE SST25VF016B
// 
// Companion product datasheets for the SST25VF016B should be reviewed in 
// conjunction with this application note for a complete understanding 
// of the device.
// 
// 
// Device Communication Protocol(pinout related) functions:
// 
// Functions                    		Function
// ------------------------------------------------------------------
// init					Initializes clock to set up mode 0.
// Send_Byte				Sends one byte using SI pin to send and 
// 					shift out 1-bit per clock rising edge
// Get_Byte				Receives one byte using SO pin to receive and shift 
// 					in 1-bit per clock falling edge
// Poll_SO					Used in the polling for RY/BY# of SO during AAI programming
// CE_High					Sets Chip Enable pin of the serial flash to high
// CE_Low					Clears Chip Enable of the serial flash to low
// Hold_Low				Clears Hold pin to make serial flash hold
// Unhold					Unholds the serial flash
// WP_Low					Clears WP pin to make serial flash write protected
// UnWP					Disables write protection pin
// 
// Note:  The pin names of the SST25VF016B are used in this application note. The associated test code
// will not compile unless these pinouts (SCK, SI, SO, SO, CE, WP, Hold) are pre-defined on your
// software which should reflect your hardware interfaced. 	 
// 
// 
// Device Operation Instruction functions:
// 
// Functions                    		Function
// ------------------------------------------------------------------
// Read_Status_Register			Reads the status register of the serial flash
// EWSR							Enables the Write Status Register
// WRSR							Performs a write to the status register
// WREN							Write enables the serial flash
// WRDI							Write disables the serial flash
// EBSY							Enable SO to output RY/BY# status during AAI programming
// DBSY							Disable SO to output RY/BY# status during AAI programming
// Read_ID						Reads the manufacturer ID and device ID
// Jedec_ID_Read				Reads the Jedec ID
// Read							Reads one byte from the serial flash and returns byte(max of 25 MHz CLK frequency)
// Read_Cont					Reads multiple bytes(max of 25 MHz CLK frequency)
// HighSpeed_Read				Reads one byte from the serial flash and returns byte(max of 50 MHz CLK frequency)
// HighSpeed_Read_Cont			Reads multiple bytes(max of 50 MHz CLK frequency)
// Byte_Program					Program one byte to the serial flash
// Auto_Add_IncA				Initial Auto Address Increment process
// Auto_Add_IncB				Successive Auto_Address_Increment process after AAI initiation
// Auto_Add_IncA_EBSY			Initial Auto Address Increment process with EBSY
// Auto_Add_IncB_EBSY			Successive Auto_Address_Increment process after AAI initiation with EBSY
// Chip_Erase					Erases entire serial flash
// Sector_Erase					Erases one sector (4 KB) of the serial flash
// Block_Erase_32K				Erases 32 KByte block memory of the serial flash
// Block_Erase_64K				Erases 64 KByte block memory of the serial flash
// Wait_Busy					Polls status register until busy bit is low
// Wait_Busy_AAI				Polls status register until busy bit is low for AAI programming
// WREN_Check					Checks to see if WEL is set
// WREN_AAI_Check				Checks to see if WEL and AAI mode is set
// 
// 
// 
//                                                                      
// "C" LANGUAGE DRIVERS 

/********************************************************************/
/* Copyright Silicon Storage Technology, Inc. (SST), 1994-2009		*/
/* Example "C" language Driver of SST25VF016B Serial Flash			*/
/* Conrado Canio, Silicon Storage Technology, Inc.					*/
/* 																	*/
/* Revision 1.0, August 1st, 2005									*/
/* Revision 1.1, February 19th, 2009								*/
/* 		- Modified Wait_Busy() and Wait_Busy_AAI() procedures		*/
/*	 to Work for both protected and unprotected Flash				*/
/* 																	*/
/*																	*/
/********************************************************************/

/* Function Prototypes */

//-----------------------------------------------------------------------------
extern void Flash_OnInit(void);
extern void Flash_Send_Byte(BYTE data);
extern BYTE Flash_Get_Byte(void);
extern void Flash_Poll_SO(void);
//extern void Hold_Low(void) {};
//extern void Unhold(void) {};
//extern void WP_Low(void) {};
//extern void UnWP(void) {};
extern BYTE Flash_Read_Status_Register(void);
extern void Flash_EWSR(void);
extern void Flash_WRSR(BYTE data);
extern void Flash_WREN(void);
extern void Flash_WRDI(void);
//extern void EBSY(void) {};
//extern void DBSY(void) {};
extern BYTE Flash_Read_ID(BYTE ID_addr);
extern DWORD Flash_Jedec_ID_Read(void);
extern BYTE Flash_Read(DWORD dwDst);
extern void Flash_Read_Cont(DWORD dwDst, WORD* pwData, DWORD dwCountWords);
extern BYTE Flash_HighSpeed_Read(DWORD dwDst);
extern void Flash_HighSpeed_Read_Cont(DWORD dwDst, WORD* pwData, DWORD dwCountWords);
extern void Flash_Byte_Program(DWORD dwDst, BYTE Data);
extern void Flash_Auto_Add_IncA(DWORD dwDst, WORD wData);
extern void Flash_Auto_Add_IncB(WORD wData);
// extern void Auto_Add_IncA_EBSY(DWORD dwDst, WORD wData) {};
// extern void Auto_Add_IncB_EBSY(WORD wData) {};
extern void Flash_Chip_Erase(void);
extern void Flash_Sector_Erase(DWORD dwDst);
extern void Flash_Block_Erase_32K(DWORD dwDst);
extern void Flash_Block_Erase_64K(DWORD dwDst);
extern BOOL Flash_Wait_Busy(void);
extern BOOL Flash_Wait_Busy_AAI(void);
//extern void WREN_Check(void) {};
//extern void WREN_AAI_Check(void) {};
extern BOOL Flash_IsError(void);
extern BOOL Flash_ReadBlockHead(DWORD dwAddr,WORD* pCount);
extern BOOL Flash_ReadBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord);
extern void Flash_WriteBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord);
extern void Flash_EraseBlock(DWORD dwAddr,WORD wCountWord);
// 	VIRTUAL void iiiReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
extern void Flash_iiiReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
//	VIRTUAL void iiiWriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte);
extern void Flash_iiiWriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord);
// 	VIRTUAL void iiiWriteDataWord1(DWORD dwAddr,WORD* pData,WORD wCountWord);

#endif/*_SST25VF016B_H*/



