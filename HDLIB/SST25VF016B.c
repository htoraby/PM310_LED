#include <main.h>

#define FLASH_DELAY					100
#define FLASH_EraseDELAY			10000

/************************************************************************/
/* PROCEDURE: OnInit													*/
/*																		*/
/* This procedure initializes the SCK to low. Must be called prior to 	*/
/* setting up mode 0.													*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		None															*/
/************************************************************************/

#define FLASH_ENABLE        (GPIOB->BRR = GPIO_Pin_5)
#define FLASH_DISABLE       (GPIOB->BSRR = GPIO_Pin_5)
#define SCL_L               (GPIOB->BRR = GPIO_Pin_6)
#define SCL_H               (GPIOB->BSRR = GPIO_Pin_6)
#define SO                  ((GPIOB->IDR&GPIO_Pin_7)?1:0)
#define SI_L                (GPIOB->BRR = GPIO_Pin_8)
#define SI_H                (GPIOB->BSRR = GPIO_Pin_8)

void Flash_OnInit()
{
    SCL_L;   /* set clock to low initial state */
}

/************************************************************************/
/* PROCEDURE: Send_Byte													*/
/*																		*/
/* This procedure outputs a byte shifting out 1-bit per clock rising	*/
/* edge on the the SI pin(LSB 1st).										*/
/*																		*/
/* Input:																*/
/*		Data															*/
/*																		*/
/* Output:																*/
/*		None															*/
/************************************************************************/
void Flash_Send_Byte(BYTE Data)
{
    BYTE i = 0;
    for (i = 0; i < 8; i++)
    {
        if ((Data & 0x80) == 0x80)      /* check if MSB is high */
            SI_H;
        else
            SI_L;                       /* if not, set to low */
        SCL_H;                          /* toggle clock high */
        Data = (Data << 1);             /* shift 1 place for next bit */
        SCL_L;                          /* toggle clock low */
    }
}

/************************************************************************/
/* PROCEDURE: Get_Byte													*/
/*																		*/
/* This procedure inputs a byte shifting in 1-bit per clock falling		*/
/* edge on the SO pin(LSB 1st).											*/
/*																		*/
/* Input:																*/
/*		SO																*/
/*																		*/
/* Output:																*/
/*		None															*/
/************************************************************************/
BYTE Flash_Get_Byte(void)
{
    BYTE i = 0, in = 0, temp = 0;
    for(i = 0; i < 8; i++)
    {
        in = (in << 1);             /* shift 1 place to the left or shift in 0 */
        temp = SO;                  /* save input */
        SCL_H;                      /* toggle clock high */
        if(temp == 1)               /* check to see if bit is high */
            in = in | 0x01;         /* if high, make bit high */
        SCL_L;                      /* toggle clock low */
    }
    return in;
}

/************************************************************************/
/* PROCEDURE: Poll_SO													*/
/*																		*/
/* This procedure polls for the SO line during AAI programming			*/
/* waiting for SO to transition to 1 which will indicate AAI programming*/
/* is completed															*/
/*																		*/
/* Input:																*/
/*		SO																*/
/*																		*/
/* Output:																*/
/*		None															*/
/************************************************************************/
// void Flash_Poll_SO()
// {
// 	BYTE temp = 0;
// 	FLASH_ENABLE;
// 	while(temp == 0x00)	/* waste time until not busy */
// 		temp = SO;
// 	FLASH_DISABLE;
// }

/************************************************************************/
/* PROCEDURE: Hold()													*/
/*																		*/
/* This procedure clears the Hold pin to low.							*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		Hold															*/
/************************************************************************/
// void Flash_Hold_Low(void)
// {
// 	Hold = 0;			/* clear Hold pin */
// }

/************************************************************************/
/* PROCEDURE: Unhold()													*/
/*																		*/
/* This procedure sets the Hold pin to high.							*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		Hold															*/
/************************************************************************/
// void Flash_Unhold(void)
// {
// 	Hold = 1;			/* set Hold pin */
// }

/************************************************************************/
/* PROCEDURE: WP()														*/
/*																		*/
/* This procedure clears the WP pin to low.								*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		WP																*/
/************************************************************************/
// void Flash_WP_Low(void)
// {
// 	WP = 0;				/* clear WP pin */
// }

/************************************************************************/
/* PROCEDURE: UnWP()													*/
/*																		*/
/* This procedure sets the WP pin to high.								*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		WP																*/
/************************************************************************/
// void Flash_UnWP(void)
// {
// 	WP = 1;				/* set WP pin */
// }

/************************************************************************/
/* PROCEDURE: Read_Status_Register										*/
/*																		*/
/* This procedure read the status register and returns the byte.		*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		byte															*/
/************************************************************************/
BYTE Flash_Read_Status_Register(void)
{
	BYTE data = 0;
	FLASH_ENABLE;			/* enable device */
	Flash_Send_Byte(0x05);		/* send RDSR command */
	data = Flash_Get_Byte();		/* receive byte */
	FLASH_DISABLE;			/* disable device */
	return data;
}

/************************************************************************/
/* PROCEDURE: EWSR														*/
/*																		*/
/* This procedure Enables Write Status Register.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Flash_EWSR(void)
{
	FLASH_ENABLE;			/* enable device */
	Flash_Send_Byte(0x50);		/* enable writing to the status register */
	FLASH_DISABLE;			/* disable device */
}

/************************************************************************/
/* PROCEDURE: WRSR														*/
/*																		*/
/* This procedure writes a byte to the Status Register.					*/
/*																		*/
/* Input:																*/
/*		byte															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Flash_WRSR(BYTE data)
{
	FLASH_ENABLE;			/* enable device */
	Flash_Send_Byte(0x01);		/* select write to status register */
	Flash_Send_Byte(data);		/* data that will change the status of BPx 
							or BPL (only bits 2,3,4,5,7 can be written) */
	FLASH_DISABLE;			/* disable the device */
}

/************************************************************************/
/* PROCEDURE: WREN														*/
/*																		*/
/* This procedure enables the Write Enable Latch.  It can also be used 	*/
/* to Enables Write Status Register.									*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Flash_WREN(void)
{
	FLASH_ENABLE;			/* enable device */
	Flash_Send_Byte(0x06);		/* send WREN command */
	FLASH_DISABLE;			/* disable device */
}

/************************************************************************/
/* PROCEDURE: WRDI														*/
/*																		*/
/* This procedure disables the Write Enable Latch.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Flash_WRDI(void)
{
	FLASH_ENABLE;			/* enable device */
	Flash_Send_Byte(0x04);		/* send WRDI command */
	FLASH_DISABLE;			/* disable device */
}

/************************************************************************/
/* PROCEDURE: EBSY														*/
/*																		*/
/* This procedure enable SO to output RY/BY# status during AAI			*/
/* programming.															*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
// void Flash_EBSY(void)
// {
// 	FLASH_ENABLE;			/* enable device */
// 	Send_Byte(0x70);		/* send EBSY command */
//	FLASH_DISABLE;			/* disable device */
// }

/************************************************************************/
/* PROCEDURE: DBSY														*/
/*																		*/
/* This procedure disable SO as output RY/BY# status signal during AAI	*/
/* programming.															*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
// void Flash_DBSY(void)
// {
// 	FLASH_ENABLE;			/* enable device */
// 	Send_Byte(0x80);		/* send DBSY command */
// 	FLASH_DISABLE;			/* disable device */
// }

/************************************************************************/
/* PROCEDURE: Read_ID													*/
/*																		*/
/* This procedure Reads the manufacturer's ID and device ID.  It will 	*/
/* use 90h or ABh as the command to read the ID (90h in this sample).   */
/* It is up to the user to give the last byte ID_addr to determine      */
/* whether the device outputs manufacturer's ID first, or device ID 	*/
/* first.  Please see the product datasheet for details.  Returns ID in */
/* variable byte.														*/
/*																		*/
/* Input:																*/
/*		ID_addr															*/
/*																		*/
/* Returns:																*/
/*		byte:	ID1(Manufacture's ID = BFh or Device ID = 80h)			*/
/*																		*/
/************************************************************************/
BYTE Flash_Read_ID(BYTE ID_addr)
{
	BYTE Data;
	FLASH_ENABLE;			/* enable device */
	Flash_Send_Byte(0x90);		/* send read ID command (90h or ABh) */
	Flash_Send_Byte(0x00);		/* send address */
	Flash_Send_Byte(0x00);		/* send address */
	Flash_Send_Byte(ID_addr);		/* send address - either 00H or 01H */
	Data = Flash_Get_Byte();		/* receive byte */
	FLASH_DISABLE;			/* disable device */
	return Data;
}

/************************************************************************/
/* PROCEDURE: Jedec_ID_Read												*/
/*																		*/
/* This procedure Reads the manufacturer's ID (BFh), memory type (25h)	*/
/* and device ID (41h).  It will use 9Fh as the JEDEC ID command.		*/
/* Please see the product datasheet for details.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		IDs_Read:ID1(Manufacture's ID = BFh, Memory Type (25h),			*/
/*		 and Device ID (80h)											*/
/*																		*/
/************************************************************************/
DWORD Flash_Jedec_ID_Read(void)
{
	DWORD dwtemp;
	
	dwtemp = 0;

	FLASH_ENABLE;							/* enable device */
	Flash_Send_Byte(0x9F);						/* send JEDEC ID command (9Fh) */
	dwtemp = (dwtemp | Flash_Get_Byte()) << 8;	/* receive byte */
	dwtemp = (dwtemp | Flash_Get_Byte()) << 8;	
	dwtemp = (dwtemp | Flash_Get_Byte());			/* temp value = 0xBF2541 */
	FLASH_DISABLE;							/* disable device */

	return dwtemp;
}

/************************************************************************/
/* PROCEDURE:	Read													*/
/*																		*/
/* This procedure reads one address of the device.  It will return the	*/
/* byte read in variable byte.											*/
/*																		*/
/*																		*/
/*																		*/
/* Input:																*/
/*		Dst:	Destination Address 000000H - 1FFFFFH					*/
/*																		*/
/*																		*/
/* Returns:																*/
/*		byte															*/
/*																		*/
/************************************************************************/
BYTE Flash_Read(DWORD dwDst)
{
	BYTE data = 0;

	FLASH_ENABLE;							/* enable device */
	Flash_Send_Byte(0x03);						/* read command */
	Flash_Send_Byte(((dwDst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Flash_Send_Byte(((dwDst & 0xFFFF) >> 8));
	Flash_Send_Byte(dwDst & 0xFF);
	data = Flash_Get_Byte();
	FLASH_DISABLE;							/* disable device */
	return data;							/* return one byte read */
}

/************************************************************************/
/* PROCEDURE:	Read_Cont												*/
/*																		*/
/* This procedure reads multiple addresses of the device and stores		*/
/* data into 128 byte buffer. Maximum byte that can be read is 128 bytes*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 1FFFFFH				*/
/*      	no_bytes	Number of bytes to read	(max = 128)				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Flash_Read_Cont(DWORD dwDst,WORD* pwData, DWORD wCountWords)
{
	DWORD i = 0;
	FLASH_ENABLE;									/* enable device */
	Flash_Send_Byte(0x03); 								/* read command */
	Flash_Send_Byte(((dwDst & 0xFFFFFF) >> 16));			/* send 3 address bytes */
	Flash_Send_Byte(((dwDst & 0xFFFF) >> 8));
	Flash_Send_Byte(dwDst & 0xFF);
	for(i=0;i<wCountWords;i++)						/* read until no_bytes is reached */
	{
		WORD wData = 0;
		wData = Flash_Get_Byte();				/* receive byte and store at address 80H - FFH */
		wData = wData<<8;
		wData |= Flash_Get_Byte();
		*pwData++ = wData;
	}
	FLASH_DISABLE;									/* disable device */
}

/************************************************************************/
/* PROCEDURE:	HighSpeed_Read											*/
/*																		*/
/* This procedure reads one address of the device.  It will return the	*/
/* byte read in variable byte.											*/
/*																		*/
/*																		*/
/*																		*/
/* Input:																*/
/*		Dst:	Destination Address 000000H - 1FFFFFH					*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		byte															*/
/*																		*/
/************************************************************************/
BYTE Flash_HighSpeed_Read(DWORD dwDst) 
{
	BYTE data = 0;	

	FLASH_ENABLE;									/* enable device */
	Flash_Send_Byte(0x0B);								/* read command */
	Flash_Send_Byte(((dwDst & 0xFFFFFF) >> 16));			/* send 3 address bytes */
	Flash_Send_Byte(((dwDst & 0xFFFF) >> 8));
	Flash_Send_Byte(dwDst & 0xFF);
	Flash_Send_Byte(0xFF);								/*dummy byte*/
	data = Flash_Get_Byte();
	FLASH_DISABLE;									/* disable device */
	return data;									/* return one byte read */
}

/************************************************************************/
/* PROCEDURE:	HighSpeed_Read_Cont										*/
/*																		*/
/* This procedure reads multiple addresses of the device and stores		*/
/* data into 128 byte buffer. Maximum byte that can be read is 128 bytes*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 1FFFFFH				*/
/*		no_bytes	Number of bytes to read	(max = 128)					*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Flash_HighSpeed_Read_Cont(DWORD dwDst, WORD* pwData, DWORD dwCountWord)
{
	DWORD i = 0;
	FLASH_ENABLE;										/* enable device */
	Flash_Send_Byte(0x0B);									/* read command */
	Flash_Send_Byte(((dwDst & 0xFFFFFF) >> 16));				/* send 3 address bytes */
	Flash_Send_Byte(((dwDst & 0xFFFF) >> 8));
	Flash_Send_Byte(dwDst & 0xFF);
	Flash_Send_Byte(0xFF);									/*dummy byte*/
	for(i=0;i<dwCountWord;i++)		/* read until no_bytes is reached */
	{
		WORD wData = 0;

		wData = Flash_Get_Byte();	/* receive byte and store at address 80H - FFH */
		wData = wData<<8;
		wData |= Flash_Get_Byte();
		*pwData++ = wData;
	}
	FLASH_DISABLE;										/* disable device */
}

/************************************************************************/
/* PROCEDURE:	Byte_Program											*/
/*																		*/
/* This procedure programs one address of the device.					*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.												*/
/*																		*/
/*																		*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 1FFFFFH				*/
/*		byte:		byte to be programmed								*/
/*																		*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Flash_Byte_Program(DWORD dwDst, BYTE data)
{
	FLASH_ENABLE;							/* enable device */
	Flash_Send_Byte(0x02);						/* send Byte Program command */
	Flash_Send_Byte(((dwDst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Flash_Send_Byte(((dwDst & 0xFFFF) >> 8));
	Flash_Send_Byte(dwDst & 0xFF);
	Flash_Send_Byte(data);						/* send byte to be programmed */
	FLASH_DISABLE;							/* disable device */
}

/************************************************************************/
/* PROCEDURE:	Auto_Add_IncA											*/
/*																		*/
/* This procedure programs consecutive addresses of 2 bytes of data into*/
/* the device:  1st data byte will be programmed into the initial		*/
/* address [A23-A1] and with A0 = 0.  The 2nd data byte will be be		*/
/* programmed into initial address [A23-A1] and with A0  = 1.  This		*/
/* is used to to start the AAI process.  It should be followed by 		*/
/* Auto_Add_IncB.														*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.												*/
/*																		*/
/*																		*/
/* Note: Only RDSR command can be executed once in AAI mode with SO		*/
/* 	 disable to output RY/BY# status.  Use WRDI to exit AAI mode 		*/
/*	 unless AAI is programming the last address or last address of		*/
/* 	 unprotected block, which automatically exits AAI mode.				*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 1FFFFFH				*/
/*		byte1:		1st byte to be programmed							*/
/*		byte1:		2nd byte to be programmed							*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Flash_Auto_Add_IncA(DWORD dwDst, WORD wData)
{
	FLASH_ENABLE;								/* enable device */
	Flash_Send_Byte(0xAD);							/* send AAI command */
	Flash_Send_Byte(((dwDst & 0xFFFFFF) >> 16));		/* send 3 address bytes */
	Flash_Send_Byte(((dwDst & 0xFFFF) >> 8));
	Flash_Send_Byte(dwDst & 0xFF);
	Flash_Send_Byte((wData>>8)&0xff);					/* send 1st byte to be programmed */
	Flash_Send_Byte(wData&0xff);						/* send 2nd byte to be programmed */
	FLASH_DISABLE;								/* disable device */
}

/************************************************************************/
/* PROCEDURE:	Auto_Add_IncB											*/
/*																		*/
/* This procedure programs consecutive addresses of 2 bytes of data into*/
/* the device:  1st data byte will be programmed into the initial 		*/
/* address [A23-A1] and with A0 = 0.  The 2nd data byte will be be 		*/
/* programmed into initial address [A23-A1] and with A0  = 1.    This  	*/
/* is used after Auto_Address_IncA.										*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.												*/
/*																		*/
/* Note: Only WRDI and AAI command can be executed once in AAI mode 	*/
/*	 with SO enabled as RY/BY# status.  When the device is busy 		*/
/*	 asserting CE# will output the status of RY/BY# on SO.  Use WRDI	*/
/* 	 to exit AAI mode unless AAI is programming the last address or 	*/
/*	 last address of unprotected block, which automatically exits 		*/
/*	 AAI mode.															*/
/*																		*/
/* Input:																*/
/*																		*/
/*		byte1:		1st byte to be programmed							*/
/*		byte2:		2nd byte to be programmed							*/
/*																		*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Flash_Auto_Add_IncB(WORD wData)
{
	FLASH_ENABLE;							/* enable device */
	Flash_Send_Byte(0xAD);						/* send AAI command */
	Flash_Send_Byte((wData>>8)&0xff);				/* send 1st byte to be programmed */
	Flash_Send_Byte(wData&0xff);					/* send 2nd byte to be programmed */
	FLASH_DISABLE;							/* disable device */
}

/************************************************************************/
/* PROCEDURE:	Auto_Add_IncA_EBSY										*/
/*																		*/
/* This procedure is the same as procedure Auto_Add_IncA except that it */
/* uses EBSY and Poll_SO functions to check for RY/BY. It programs 		*/
/* consecutive addresses of the device.  The 1st data byte will be 		*/
/* programmed into the initial address [A23-A1] and with A0 = 0.  The 	*/
/* 2nd data byte will be programmed into initial address [A23-A1] and 	*/
/* with A0  = 1.  This is used to to start the AAI process.  It should  */
/* be followed by Auto_Add_IncB_EBSY.									*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.												*/
/*																		*/
/*																		*/
/* Note: Only WRDI and AAI command can be executed once in AAI mode 	*/
/*	 with SO enabled as RY/BY# status.  When the device is busy 		*/
/*	 asserting CE# will output the status of RY/BY# on SO.  Use WRDI	*/
/* 	 to exit AAI mode unless AAI is programming the last address or 	*/
/*	 last address of unprotected block, which automatically exits 		*/
/*	 AAI mode.															*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 1FFFFFH				*/
/*		byte1:		1st byte to be programmed							*/
/*		byte1:		2nd byte to be programmed							*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
// void Auto_Add_IncA_EBSY(DWORD dwDst, WORD wData)
// {
// 	EBSY();										/* enable RY/BY# status for SO in AAI */
// 
// 	FLASH_ENABLE;								/* enable device */
//	Send_Byte(0xAD);							/* send AAI command */
// 	Send_Byte(((dwDst & 0xFFFFFF) >> 16));		/* send 3 address bytes */
// 	Send_Byte(((dwDst & 0xFFFF) >> 8));
// 	Send_Byte(dwDst & 0xFF);
// 	Send_Byte((wData>>8)&0xff);					/* send 1st byte to be programmed */
// 	Send_Byte(wData&0xff);						/* send 2nd byte to be programmed */
// 	FLASH_DISABLE;								/* disable device */
// 	
// 	Poll_SO();									/* polls RY/BY# using SO line */
// }

/************************************************************************/
/* PROCEDURE:	Auto_Add_IncB_EBSY										*/
/*																		*/
/* This procedure is the same as Auto_Add_IncB excpet that it uses 		*/
/* Poll_SO to poll for RY/BY#.  It demonstrate on how to use DBSY after	*/
/* AAI programmming is completed.  It programs consecutive addresses of */
/* the device.  The 1st data byte will be programmed into the initial   */
/* address [A23-A1] and with A0 = 0.  The 2nd data byte will be 		*/
/* programmed into initial address [A23-A1] and with A0  = 1.  This is 	*/
/* used after Auto_Address_IncA.										*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.												*/
/*																		*/
/* Note: Only WRDI and AAI command can be executed once in AAI mode 	*/
/*	 with SO enabled as RY/BY# status.  When the device is busy 		*/
/*	 asserting CE# will output the status of RY/BY# on SO.  Use WRDI	*/
/* 	 to exit AAI mode unless AAI is programming the last address or 	*/
/*	 last address of unprotected block, which automatically exits 		*/
/*	 AAI mode.															*/
/*																		*/
/* Input:																*/
/*																		*/
/*		byte1:		1st byte to be programmed							*/
/*		byte2:		2nd byte to be programmed							*/
/*																		*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
// void Auto_Add_IncB_EBSY(WORD wData)
// {
// 	FLASH_ENABLE;							/* enable device */
// 	Send_Byte(0xAD);						/* send AAI command */
// 	Send_Byte((wData>>8)&0xff);				/* send 1st byte to be programmed */
// 	Send_Byte(wData&0xff);					/* send 2nd byte to be programmed */
// 	FLASH_DISABLE;							/* disable device */
// 
// 	Poll_SO();								/* polls RY/BY# using SO line */
// 
// 	WRDI();									/* Exit AAI before executing DBSY */
// 	DBSY();									/* disable SO as RY/BY# output if in AAI */
// }

/************************************************************************/
/* PROCEDURE: Chip_Erase												*/
/*																		*/
/* This procedure erases the entire Chip.								*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Flash_Chip_Erase(void)
{
	FLASH_ENABLE;				/* enable device */
	Flash_Send_Byte(0x60);			/* send Chip Erase command (60h or C7h) */
	FLASH_DISABLE;				/* disable device */
}

/************************************************************************/
/* PROCEDURE: Sector_Erase												*/
/*																		*/
/* This procedure Sector Erases the Chip.								*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 1FFFFFH				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Flash_Sector_Erase(DWORD dwDst)
{
	FLASH_ENABLE;							/* enable device */
	Flash_Send_Byte(0x20);						/* send Sector Erase command */
	Flash_Send_Byte(((dwDst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Flash_Send_Byte(((dwDst & 0xFFFF) >> 8));
	Flash_Send_Byte(dwDst & 0xFF);
	FLASH_DISABLE;							/* disable device */
}

/************************************************************************/
/* PROCEDURE: Block_Erase_32K											*/
/*																		*/
/* This procedure Block Erases 32 KByte of the Chip.					*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 1FFFFFH				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Flash_Block_Erase_32K(DWORD dwDst)
{
	FLASH_ENABLE;									/* enable device */
	Flash_Send_Byte(0x52);								/* send 32 KByte Block Erase command */
	Flash_Send_Byte(((dwDst & 0xFFFFFF) >> 16));			/* send 3 address bytes */
	Flash_Send_Byte(((dwDst & 0xFFFF) >> 8));
	Flash_Send_Byte(dwDst & 0xFF);
	FLASH_DISABLE;									/* disable device */
}

/************************************************************************/
/* PROCEDURE: Block_Erase_64K											*/
/*																		*/
/* This procedure Block Erases 64 KByte of the Chip.					*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 1FFFFFH				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Flash_Block_Erase_64K(DWORD dwDst)
{
	FLASH_ENABLE;							/* enable device */
	Flash_Send_Byte(0xD8);						/* send 64KByte Block Erase command */
	Flash_Send_Byte(((dwDst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Flash_Send_Byte(((dwDst & 0xFFFF) >> 8));
	Flash_Send_Byte(dwDst & 0xFF);
	FLASH_DISABLE;							/* disable device */
}

/************************************************************************/
/* PROCEDURE: Wait_Busy													*/
/*																		*/
/* This procedure waits until device is no longer busy (can be used by	*/
/* Byte-Program, Sector-Erase, Block-Erase, Chip-Erase).				*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		BOOL															*/
/************************************************************************/
BOOL Flash_Wait_Busy(void)
{
	WORD wCount = FLASH_EraseDELAY;
	while(((Flash_Read_Status_Register() & 0x03) == 0x03) && (wCount-->1))	/* waste time until not busy */
		Flash_Read_Status_Register();
	if(wCount==0) return FALSE;
	return TRUE;
}

/************************************************************************/
/* PROCEDURE: Wait_Busy_AAI												*/
/*																		*/
/* This procedure waits until device is no longer busy for AAI mode.	*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		BOOL															*/
/************************************************************************/
BOOL Flash_Wait_Busy_AAI(void)
{
	WORD wCount = FLASH_DELAY;
	while(((Flash_Read_Status_Register()&0x43)==0x43) && (wCount-->1))	/* waste time until not busy */
		Flash_Read_Status_Register();
	if(wCount==0) return FALSE;
	return TRUE;
}

/************************************************************************/
/* PROCEDURE: WREN_Check												*/
/*																		*/
/* This procedure checks to see if WEL bit set before program/erase.	*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
// void Flash_WREN_Check(void)
// {
// 	BYTE data;
// 	data = Read_Status_Register();	/* read the status register */
// 	if(data!=0x02)					/* verify that WEL bit is set */
// 	{
// 		while(1);
// 			/* add source code or statements for this file */
// 			/* to compile   			       */
// 			/* i.e. option: insert a display to view error on LED? */
// 			/* option: insert a display to view error on LED? */
// 	}
// }

/************************************************************************/
/* PROCEDURE: WREN_AAI_Check											*/
/*																		*/
/* This procedure checks for AAI and WEL bit once in AAI mode.			*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
// void Flash_WREN_AAI_Check(void)
// {
// 	BYTE data;
// 	data = Read_Status_Register();	/* read the status register */
// 	if(data!=0x42)					/* verify that AAI and WEL bit is set */
// 	{
// 		while(1);
// 			/* add source code or statements for this file */
// 			/* to compile   			       */
// 			/* i.e. option: insert a display to view error on LED? */
// 			/* option: insert a display to view error on LED? */
// 	}
// }

//-----------------------------------------------------------------------------
BOOL Flash_IsError(void)
{
    short i;
	Flash_OnInit();
	for(i=0;i<1000;i++)
	{
		DWORD dwStatus = Flash_Jedec_ID_Read();
		if((dwStatus)==0x00BF2541) return FALSE;
	}

	return TRUE;
}

// void Flash_iiiReadDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
// {
// 
// }

void Flash_iiiReadDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
	if(wCountWord==0) return;
	Flash_Read_Cont(dwAddr,pData,wCountWord);
}

// void Flash_iiiWriteDataByte(DWORD dwAddr,BYTE* pData,WORD wCountByte)
// {
// 
// }

void Flash_iiiWriteDataWord(DWORD dwAddr,WORD* pData,WORD wCountWord)
{
    short i;
    WORD wCount;
	if(wCountWord==0) return;
	Flash_EWSR();
	Flash_WRSR(0x00);
	Flash_WREN();
	wCount = FLASH_DELAY;
	while(((Flash_Read_Status_Register()&03)!=0x02) && (wCount-->1))
		Flash_Read_Status_Register();
	if(wCount==0) return;
	Flash_Auto_Add_IncA(dwAddr,pData[0]);
	if(Flash_Wait_Busy_AAI()==FALSE) return;
	for(i=1;i<wCountWord;i++)
	{
		Flash_Auto_Add_IncB(pData[i]);
		if(Flash_Wait_Busy_AAI()==FALSE) return;
	}
	Flash_WRDI();
}

typedef struct
{
	WORD wAddSum;
	WORD wCount1;
	WORD wCount2;
}BLOCKINFO;

//-----------------------------------------------------------------------------
void Flash_EraseBlock(DWORD dwAddr,WORD wCountWord)
{
    short i;
    WORD wEraseNum;
	if(wCountWord==0) return;
	Flash_EWSR();
	Flash_WRSR(0x00);
	wEraseNum = (wCountWord + 2047) / 2048;			// 需要擦除的块数,每块4096 BYTE(2048 WORD)
	for(i=0;i<wEraseNum;i++)
	{
		WORD wCount = FLASH_DELAY;
		Flash_WREN();
		while(((Flash_Read_Status_Register()&03)!=0x02) && (wCount-->1))
			Flash_Read_Status_Register();
		if(wCount==0) return;
		Flash_Sector_Erase(dwAddr+4096L*i);
		if(Flash_Wait_Busy()==FALSE) return;
	}
	Flash_WRDI();
}

BOOL Flash_ReadBlockHead(DWORD dwAddr,WORD* pCount)
{
	WORD wDeviceType;
	BLOCKINFO blockinfo;
	Flash_iiiReadDataWord(dwAddr,&wDeviceType,1);
	if(wDeviceType==(WORD)DEVICETYPE_CODE)
	{
		Flash_iiiReadDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
		if(blockinfo.wCount1==blockinfo.wCount2)
		{
			if(pCount!=NULL) *pCount = blockinfo.wCount1;
			return TRUE;
		}
	}
	*pCount = 0;				// 读取失败
	return FALSE;
}

BOOL Flash_ReadBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord)
{
	WORD wDeviceType;
	BLOCKINFO blockinfo;
	Flash_iiiReadDataWord(dwAddr,&wDeviceType,1);
	if(wDeviceType==DEVICETYPE_CODE)
	{
		Flash_iiiReadDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
		Flash_iiiReadDataWord(dwAddr+2+SIZEOFBYTE(blockinfo),pData,wCountWord);
		if(blockinfo.wAddSum==CalculateCRCWord(pData,wCountWord)&&blockinfo.wCount1==blockinfo.wCount2)
		{
			if(pCount!=NULL) *pCount = blockinfo.wCount1;
			return TRUE;
		}
	}
	return FALSE;
}

void Flash_WriteBlock(DWORD dwAddr,WORD* pCount,WORD* pData,WORD wCountWord)
{
	WORD wDeviceType;
	BLOCKINFO blockinfo;
	blockinfo.wAddSum = CalculateCRCWord(pData,wCountWord);
	if(pCount!=NULL)
	{
		blockinfo.wCount1 = *pCount;
		blockinfo.wCount2 = *pCount;
	}
	else
	{
		blockinfo.wCount1 = 0;
		blockinfo.wCount2 = 0;
	}
	wDeviceType = (WORD)DEVICETYPE_CODE;
	Flash_EraseBlock(dwAddr,1+SIZEOFWORD(blockinfo)+wCountWord);
//     DelayOnce(5000);
	Flash_iiiWriteDataWord(dwAddr,&wDeviceType,1);
	Flash_iiiWriteDataWord(dwAddr+2,(WORD*)&blockinfo,SIZEOFWORD(blockinfo));
	Flash_iiiWriteDataWord(dwAddr+2+SIZEOFBYTE(blockinfo),pData,wCountWord);
}



