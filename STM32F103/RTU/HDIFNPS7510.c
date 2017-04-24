#include "main.h"


void GPIO_OnInit(void)
{
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);

    {
        GPIO_InitTypeDef  GPIO_InitStructure;
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;          // PA6:LCD_CD; PA7:LCD_WR;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_9;          // PB0:LCD_BL; PB9:LCD_D0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;          // PC4:LCD_RD; PC5:LCD_CS;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |  GPIO_Pin_2 | GPIO_Pin_3
                | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;                 // PE0~PE6:LCD_D1~LCD_D07
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOE, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_8;   // PB5:SPI_CS; PB6:SPI_CLK; PB8:SPI_DI
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                               // PB7:SPI_DO;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        
        // KEY 上拉输入
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;          // PC8:TIME_SCL; PC9:TIME_SDA;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;          // PD1:FRAM_SCL; PD2:FRAM_SDA;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;          // PE7:J2; PE8:J1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOE, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;             // D6,D5,D4,D3,D2,D1
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
        GPIO_Init(GPIOE, &GPIO_InitStructure);
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

        /* USART1 GPIO config */
        /* Configure USART1 Tx (PA.09) as alternate function push-pull */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        /* Configure USART1 Rx (PA.10) as input floating */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;          // PA8:ctrl;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
}

void FlushRelays(void)
{
    if(Output_IsOutputValid(&g_relayKH[Relay_J1])) GPIOE->BSRR = GPIO_Pin_8;
    else GPIOE->BRR = GPIO_Pin_8;
    
    if(Output_IsOutputValid(&g_relayKH[Relay_J2])) GPIOE->BSRR = GPIO_Pin_7;
    else GPIOE->BRR = GPIO_Pin_7;
    
    if(g_bLCDOpened) GPIOB->BSRR = GPIO_Pin_0;
    else GPIOB->BRR = GPIO_Pin_0;
}

void MyHDIF_OnInit1(void)
{
    short i;
    GPIO_OnInit();
    for(i=0;i<1000;i++) DelayOnce(1000);
    LCD_HWRest();
    LCD_Setup();
    
//     GPIOB->BSRR = GPIO_Pin_0;           // LCD_BL
    
    Flash_OnInit();
    Time_OnInit();
}

void MyHDIF_OnInit2(void)
{
    LCD_Flush();
    Time_OnInit();
    COMM_HardWareInit();
    COMM_OnInit();
}

void MyHDIF_OnTimer1ms(void)
{
    SWITCHSetStatus(0,(GPIOE->IDR&GPIO_Pin_14)?STATUS_OFF:STATUS_ON);
    SWITCHSetStatus(1,(GPIOE->IDR&GPIO_Pin_13)?STATUS_OFF:STATUS_ON);
    SWITCHSetStatus(2,(GPIOE->IDR&GPIO_Pin_12)?STATUS_OFF:STATUS_ON);
    SWITCHSetStatus(3,(GPIOE->IDR&GPIO_Pin_11)?STATUS_OFF:STATUS_ON);
    
    FlushRelays();
}

void MyHDIF_OnTimer10ms(void)
{
    WORD wKeyCode = 0x0000;
    
    if((GPIOC->IDR&HKEY_UP)==0) wKeyCode |= KEY_UP;
    if((GPIOC->IDR&HKEY_DOWN)==0) wKeyCode |= KEY_DOWN;
    if((GPIOC->IDR&HKEY_OK)==0) wKeyCode |= KEY_OK;
    if((GPIOC->IDR&HKEY_CANCEL)==0) wKeyCode |= KEY_CANCEL;

    Key_SetKeyHardCode(wKeyCode);
}

void MyHDIF_OnTimer1000ms(void)
{
}

void MyHDIF_OnWhileLoop(void)
{
    COMM_OnTimer10ms();
}

void MyHDIF_OnPollingComm(void)
{
    g_wModAddr = g_deviceParam.wModbusAddr1;
    COMM_OnPolling();
}

void MyHDIF_OnSCIOpenTX(void)
{
    GPIOA->BRR = GPIO_Pin_8;
}

void MyHDIF_OnSCICloseTX(void)
{
    GPIOA->BSRR = GPIO_Pin_8;
}

void LCDWrite(BYTE Data, BOOL bCmd)            // 0:cmd;1:Data
{
    if(bCmd) GPIOA->BSRR = GPIO_Pin_6;
    else GPIOA->BRR = GPIO_Pin_6;
    
    GPIOC->BSRR = GPIO_Pin_4;           // LCD_RD = 1;
    GPIOA->BSRR = GPIO_Pin_7;           // LCD_WR = 1;
    GPIOC->BRR = GPIO_Pin_5;            // LCD_CS = 0;
    
    __nop();
    __nop();
    
    if(Data&0x01) GPIOB->BSRR = GPIO_Pin_9;
    else GPIOB->BRR = GPIO_Pin_9;
    if(Data&0x02) GPIOE->BSRR = GPIO_Pin_0;
    else GPIOE->BRR = GPIO_Pin_0;
    if(Data&0x04) GPIOE->BSRR = GPIO_Pin_1;
    else GPIOE->BRR = GPIO_Pin_1;
    if(Data&0x08) GPIOE->BSRR = GPIO_Pin_2;
    else GPIOE->BRR = GPIO_Pin_2;
    if(Data&0x10) GPIOE->BSRR = GPIO_Pin_3;
    else GPIOE->BRR = GPIO_Pin_3;
    if(Data&0x20) GPIOE->BSRR = GPIO_Pin_4;
    else GPIOE->BRR = GPIO_Pin_4;
    if(Data&0x40) GPIOE->BSRR = GPIO_Pin_5;
    else GPIOE->BRR = GPIO_Pin_5;
    if(Data&0x80) GPIOE->BSRR = GPIO_Pin_6;
    else GPIOE->BRR = GPIO_Pin_6;
    
    GPIOA->BRR = GPIO_Pin_7;           // LCD_WR = 0;
    
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
    
    GPIOA->BSRR = GPIO_Pin_7;           // LCD_WR = 1;
    __nop();
    __nop();
    
    GPIOC->BSRR = GPIO_Pin_4;           // LCD_RD = 1;
    GPIOA->BSRR = GPIO_Pin_7;           // LCD_WR = 1;
    GPIOC->BSRR = GPIO_Pin_5;           // LCD_CS = 1;
}

