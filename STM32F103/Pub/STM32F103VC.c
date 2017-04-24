#include "main.h"

static WORD s_wCountTask10ms = 0;
static WORD s_wCountTask1000ms = 0;

static WORD s_wCountTimer250ms = 0;
static BOOL s_bEventTimer250ms = FALSE;
static WORD s_wCountTimer1000ms = 0;
static WORD s_bEventTimer1000ms = FALSE;
static WORD s_wCountStartMain10ms = 8;

DWORD g_dwFsam = 60000L;
DWORD g_dwSysTimerUs = 0;
WORD g_wCountAD = 0;

const tCRC32INFO* g_pCRCInfo = (tCRC32INFO*)ADDRCRC32INFO;

void TIM3_IRQHandler(void)      // 采样
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

        ADC_SoftwareStartConvCmd(ADC1,ENABLE);

        MyApp_OnTimerSample(g_wCountAD);
        g_dwSysTimerUs -= 6000;                  // 0xffff - TIM2->CNT;

        //-------------------------------------------------------------------------	
        OnWaveRecord(g_wCountAD);
        g_wCountAD++;
        if(g_wCountAD>=DFT_DOTNUM)
        {
            g_wCountAD = 0;
//            DWORD dwTimer = SystemCoreClock/1200-1;
//            if(g_wFsam>=5518 && g_wFsam<=10417)	// 9363)
//            {
//                dwTimer = g_wFsam;
//            }
//            else
//            {
//                dwTimer = SystemCoreClock/1200-1;
//                g_wFsam = 8333;
//            }
//            TIM3->ARR = dwTimer;
        }
    }
}

WORD s_wTask1ms = 0;
void TIM6_IRQHandler(void)      // 
{
    if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
        IWDG_ReloadCounter();
        if(s_wTask1ms++&0x1) OnMainTimer1ms();
        HDIF_OnPollingComm();
        s_wCountTask10ms++;
        s_wCountTask1000ms++;
        
//        if(PWR_GetFlagStatus(PWR_FLAG_PVDO)!=RESET)
//        {
//            GPIOC->BRR = GPIO_Pin_6;
//            NVIC_SystemReset();
//            while(1){};
//        }
        if(s_wCountTask10ms>80)
        {
            while(1){};
        }
        if(s_wCountTask1000ms>5000)
        {
            while(1){};
        }
    }
}

void TIM7_IRQHandler(void)      // 10ms
{
     if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
//         GPIOC->BSRR = GPIO_Pin_7;
//        if(s_wCountResetXINT1>=5/*50*/) s_dwTimeXINT1 = 0;
//        else s_wCountResetXINT1++;
    if(s_wCountStartMain10ms)
    {
        s_wCountStartMain10ms--;
        s_wCountStartMain10ms &= 0x0007;
    }
    else OnMainTimer10ms();
    
    s_wCountTimer250ms++;
    if(s_wCountTimer250ms>=25)
    {
        s_wCountTimer250ms = 0;
        s_bEventTimer250ms = TRUE;
    }
    
    s_wCountTimer1000ms++;
    if(s_wCountTimer1000ms>=100)
    {
        s_wCountTimer1000ms = 0;
        s_bEventTimer1000ms = TRUE;
    }
    
    s_wCountTask10ms = 0;
//         GPIOC->BRR = GPIO_Pin_7;
    }
}

WORD ADC1_ConvertedValue[DFT_CHANNEL_HARD] = { 2000, 2000, 2000, 2000, 2000, 2000};

void DMA1_Channel1_IRQHandler(void)
{
    short i;
    if(DMA_GetITStatus(DMA1_IT_TC1) != RESET)
    {
        DMA_ClearITPendingBit(DMA1_IT_TC1);        
        for(i=0; i<3; i++)
        {
            g_analogWave.wData[i][g_wCountAD] = 4096 - ADC1_ConvertedValue[i];
            g_analogWave.wData[i][g_wCountAD+24] = g_analogWave.wData[i][g_wCountAD];
        }
        for(i=3; i<6; i++)
        {
            g_analogWave.wData[i][g_wCountAD] = ADC1_ConvertedValue[i];
            g_analogWave.wData[i][g_wCountAD+24] = g_analogWave.wData[i][g_wCountAD];
        }
    }
}

void DelayOnce(DWORD dwCountUS)
{
    DWORD dwCountOld;
    dwCountUS = dwCountUS*10;           // dwCountUS*1000/13.888888889;
    dwCountOld = TIM2->CNT;
    while((TIM2->CNT-dwCountOld)<=dwCountUS)
    {
    }
}

void TIM_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    
    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    /* Enable the TIM2 gloabal Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                // 采样中断
    /* Enable the TIM3 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* TIM6 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);                // 0.5ms
    /* Enable the TIM6 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* TIM7 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);                // 20ms
    /* Enable the TIM7 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = (DWORD)65535;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    /* Prescaler configuration */
    TIM_PrescalerConfig(TIM2, 9, TIM_PSCReloadMode_Immediate);
    TIM_Cmd(TIM2, ENABLE);
    
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = SystemCoreClock/1200-1;                           // 22500-1; 72M/50(60)/64-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    /* Prescaler configuration */
    TIM_PrescalerConfig(TIM3, 0, TIM_PSCReloadMode_Immediate);          // 1分频
    
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 3599;        // 7199;            // 7200-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    /* Prescaler configuration */
    TIM_PrescalerConfig(TIM6, 9, TIM_PSCReloadMode_Immediate);          // 10分频

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 7199;            // 7200-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
    /* Prescaler configuration */
    TIM_PrescalerConfig(TIM7, 99, TIM_PSCReloadMode_Immediate);         // 100分频
}

void AD_Config(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

    //配置模拟输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE; //关闭通道扫描模式  ?? 单通道：DISABLE 多通道：ENABLE OK
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //注意不要使用持续转换模式，否则只要触发一次，//后续的转换就会永不停歇（除非CONT清0），这样第一次以后的ADC，就不是由TIM2_CC2来触发了
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//配置TIM2_CC2为触发源
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = DFT_CHANNEL_HARD;
    ADC_Init(ADC1, &ADC_InitStructure);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//配置时钟(12MHz),在RCC里面还应配置APB2=AHB时钟72MHz，
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_239Cycles5);
    ADC_DMACmd(ADC1, ENABLE); //使能ADC1的DMA
    ADC_Cmd(ADC1,ENABLE);
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1))
    {
    ;
    }
    ADC_StartCalibration(ADC1);                         //Start Calibration register
    while(ADC_GetCalibrationStatus(ADC1))
    {
    ;    //waiting for finishing the calibration
    }

    {
        DMA_InitTypeDef DMA_InitStructure;//定义DMA初始化结构体
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//使能DMA时钟

        DMA_DeInit(DMA1_Channel1);//复位DMA通道1
      
        DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)( &(ADC1->DR)); //定义 DMA通道外设基地址
        DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC1_ConvertedValue; //定义DMA通道存储器地址
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//指定外设为源地址
        DMA_InitStructure.DMA_BufferSize = DFT_CHANNEL_HARD;//定义DMA缓冲区大小1
        DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//当前外设寄存器地址不变
        DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//当前存储器地址不变
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//定义外设数据宽度16位
        DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //定义存储器数据宽度16位
        DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA通道操作模式位环形缓冲模式 ??  循环接收数据不是一次 OK
        DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA通道优先级高
        DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//禁止DMA通道存储器到存储器传输  ?? 需要软件把DMA数据存放在数组而不是DMA直接把数据从内存放于内存
        DMA_Init(DMA1_Channel1, &DMA_InitStructure);//初始化DMA通

        DMA_Cmd(DMA1_Channel1, ENABLE); //使能DMA通道1
        DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);  //DMA通道1传输完成中断
    }
    {
        NVIC_InitTypeDef NVIC_InitStructure;
        NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn; //选择DMA1
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   //
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能
        NVIC_Init(&NVIC_InitStructure);
    }
}

int main(void)
{
    /* TIM Configuration */
    TIM_Config();

// ---------------------------------------------------------------------------------------------------
// 初始化系统
//    CreateMem(s_wMem, MEMSIZE);
//    CMyFilter::m_nDepth = 1;
//    APPCreate = RT_CREATE(CMyAppDMC600CT);
//    HDIFCreate = RT_CREATE(CMyHDIFCT);
//    g_Device.CreateObj();
//    g_Device.OnInit();
// 
    OnMainInit();
    AD_Config();
    
// ---------------------------------------------------------------------------------------------------
// 开中断
/* TIM Interrupts enable */
//     TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
    
//    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    /* TIM3 enable counter */
//     TIM_Cmd(TIM2, ENABLE);
    
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    /* TIM3 enable counter */

    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    /* TIM6 enable counter */
    
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
    /* TIM7 enable counter */

//    if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) != RESET)
//    {
//        /* WWDGRST flag set */
//        /* Clear reset flags */
//        RCC_ClearFlag();
//    }
    /* WWDG configuration */
    /* Enable WWDG clock */
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
    /* WWDG clock counter = (PCLK1 (36MHz)/4096)/8 = 1098Hz (~910 us)  */
//    WWDG_SetPrescaler(WWDG_Prescaler_8);
//    /* Set Window value to 80; WWDG counter should be refreshed only when the counter
//        is below 80 (and greater than 64) otherwise a reset will be generated */
//    WWDG_SetWindowValue(126);
//    /* Enable WWDG and set counter value to 127, WWDG timeout = ~910 us * 64 = 58.24 ms 
//    In this case the refresh window is: ~910 * (127-80) = 42.7ms < refresh window < ~910 * 64 = 58.2ms
//    */
//    WWDG_Enable(127);
      /* Check if the system has resumed from IWDG reset */
    if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
    {
        /* IWDGRST flag set */
        /* Clear reset flags */
        RCC_ClearFlag();
    }
      /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
     dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    /* IWDG counter clock: LSI/32 */
    IWDG_SetPrescaler(IWDG_Prescaler_32);

    /* Set counter reload value to obtain 250ms IWDG TimeOut.
     Counter Reload Value = 250ms * IWDG counter clock period
                          = 250ms * (LSI/32)
                          = 0.25s * (LsiFreq/32)
                          = LsiFreq / (32 * 4)
                          = LsiFreq / 128
   */
    IWDG_SetReload(42000/128);

    /* Reload IWDG counter */
    IWDG_ReloadCounter();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();
  
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM6, ENABLE);
    TIM_Cmd(TIM7, ENABLE);
    
    for(;;)
    {
        if(s_bEventTimer250ms)
        {
            s_bEventTimer250ms = FALSE;
            OnMainTimer250ms();
        }
        if(s_bEventTimer1000ms)
        {
            s_bEventTimer1000ms = FALSE;
            OnMainTimer1000ms();
            s_wCountTask1000ms = 0;
        }
        OnMainWhileLoop();
    }
}

