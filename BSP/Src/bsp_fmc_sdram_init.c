#include "bsp_fmc_sdram_init.h"
#include "fmc.h"

///******************************************************************************************************
//*	函 数 名: SystemInit_ExtMemCtl
//*	入口参数: 无
//*	返 回 值: 无
//*	函数功能: 初始化外部 SDRAM 控制器
//*	说    明: 此函数用于初始化 FMC 外设，配置 GPIO 引脚，并对 SDRAM 进行初始化和参数配置。
//*             仅在定义了 DATA_IN_ExtSDRAM 时执行相关操作。
//* 作用：		在进入main函数之前就对FMC进行初始化（很重要！！！！！）
//*******************************************************************************************************/
void SystemInit_ExtMemCtl(void)
{
	#if defined (DATA_IN_ExtSDRAM)
	
	//--------------------------------------------------------------------
	// 变量定义
	//--------------------------------------------------------------------
	FMC_SDRAM_TimingTypeDef SdramTiming = {0};
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__IO uint32_t tmpmrd = 0;
	uint32_t FMC_Initialized = 0;
	if (FMC_Initialized) {
			return;
	}FMC_Initialized = 1;
	
	//--------------------------------------------------------------------
	// 时钟使能
	//--------------------------------------------------------------------
	__HAL_RCC_FMC_CLK_ENABLE();
	
	//--------------------------------------------------------------------
	// GPIO初始化
	//--------------------------------------------------------------------
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
						  |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12
						  |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4
						  |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
						  |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	//--------------------------------------------------------------------
	// FMC-SDRAM初始化
	//--------------------------------------------------------------------
	hsdram1.Instance = FMC_SDRAM_DEVICE;
	/* hsdram1.Init */
	hsdram1.Init.SDBank = FMC_SDRAM_BANK1;								// 选择BANK区
	hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;		// 行地址宽度
	hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;             // 列地址线宽度
	hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;          // 数据宽度  
	hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;     // bank数量
	hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;                  //	CAS 
	hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;  // 禁止写保护
	hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;              // 分频
	hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;                   // 突发模式  
	hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;               // 读延迟
	/* SdramTiming */                                                   
	SdramTiming.LoadToActiveDelay = 2;
	SdramTiming.ExitSelfRefreshDelay = 8;
	SdramTiming.SelfRefreshTime = 6;
	SdramTiming.RowCycleDelay = 6;
	SdramTiming.WriteRecoveryTime = 4;
	SdramTiming.RPDelay = 2;
	SdramTiming.RCDDelay = 2;
	if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
	{
		Error_Handler( );
	}
	
	SDRAM_Initialization_Sequence(&hsdram1,&command);//配置SDRAM
	
	#endif
}

FMC_SDRAM_CommandTypeDef command;// 控制指令
/******************************************************************************************************
*	函 数 名: SDRAM_Initialization_Sequence
*	入口参数: hsdram - SDRAM_HandleTypeDef定义的变量，即表示定义的sdram
*				 Command	- 控制指令
*	返 回 值: 无
*	函数功能: SDRAM 参数配置
*	说    明: 配置SDRAM相关时序和控制方式
*******************************************************************************************************/
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
	__IO uint32_t tmpmrd = 0;
   register __IO uint32_t index;
	/* Configure a clock configuration enable command 时钟配置使能*/
	Command->CommandMode 				= FMC_SDRAM_CMD_CLK_ENABLE;	// 开启SDRAM时钟 
	Command->CommandTarget 				= FMC_COMMAND_TARGET_BANK; 	// 选择要控制的区域
	Command->AutoRefreshNumber 	    	= 1;
	Command->ModeRegisterDefinition 	= 0;
 
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);	// 发送控制指令
	  /* Delay */
  for (index = 0; index<10000; index++);
 
	/* Configure a PALL (precharge all) command 对所有存储区域预充电*/ 
	Command->CommandMode 				= FMC_SDRAM_CMD_PALL;		// 预充电命令
	Command->CommandTarget 				= FMC_COMMAND_TARGET_BANK;	// 选择要控制的区域
	Command->AutoRefreshNumber 		    = 1;
	Command->ModeRegisterDefinition 	= 0;
 
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);  // 发送控制指令
 
	/* Configure a Auto-Refresh command 设置自动刷新次数*/ 
	Command->CommandMode 				= FMC_SDRAM_CMD_AUTOREFRESH_MODE;	// 使用自动刷新
	Command->CommandTarget 				= FMC_COMMAND_TARGET_BANK;          // 选择要控制的区域
	Command->AutoRefreshNumber			= 8;                                // 自动刷新次数
	Command->ModeRegisterDefinition 	= 0;
 
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);	// 发送控制指令
 
	/* Program the external memory mode register */
    //配置模式寄存器，SDRAM的bit0-bit2为指定突发访问的长度
    //bit3为指定突发访问的类型，bit4-bit6为CAS值，bit7和bit8为运行模式
    //bit9为指定的写突发模式，bit10和bit11位保留位
	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2               |//设置突发长度：2（可以是1/2/4/8）
							SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |//设置突发类型：连续（可以是连续/交错）
							SDRAM_MODEREG_CAS_LATENCY_3           |//设置CAS值：3（可以是2/3）
							SDRAM_MODEREG_OPERATING_MODE_STANDARD |//设置操作模式：0，标准模式
							SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;  //设置突发写模式：1，单点访问
 
	Command->CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;	// 加载模式寄存器命令
	Command->CommandTarget          = FMC_COMMAND_TARGET_BANK;	// 选择要控制的区域
	Command->AutoRefreshNumber 		= 1;
	Command->ModeRegisterDefinition = tmpmrd;
 
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);	// 发送控制指令
    
	//刷新频率计数器(以SDCLK频率计数),计算方法:
	//COUNT=SDRAM刷新周期/行数-20=SDRAM刷新周期(us)*SDCLK频率(Mhz)/行数
    //我们使用的SDRAM刷新周期为64ms,SDCLK=240/2=120Mhz,行数为8192(2^13).
	//所以,COUNT=64*1000*120/8192-20=918(20为刷新等待冗余)
	HAL_SDRAM_ProgramRefreshRate(hsdram, 918);  // 配置刷新率
}

//SDRAM内存测试	    
void fsmc_sdram_test(void)
{  
	Set_Current_USART(USART1_IDX);
	__IO uint32_t i=0;  	  
	__IO uint32_t temp=0;	   
	__IO uint32_t sval=0;//在地址0读到的数据	  				   
	//每隔16K字节,写入一个数据,总共写入2048个数据,刚好是32M字节
	for(i=0;i<32*1024*1024;i+=16*1024)
	{
		*(__IO uint32_t *)(SDRAM_BANK_ADDR+i)=temp; 
		temp++;
	}
	//依次读出之前写入的数据,进行校验		  
 	for(i=0;i<32*1024*1024;i+=16*1024) 
	{	
  		temp=*(__IO uint32_t *)(SDRAM_BANK_ADDR+i);
		if(i==0)sval=temp;
 		else if(temp<=sval)break;//后面读出的数据一定要比第一次读到的数据大.	   		   
		printf("SDRAM Capacity:%dKB\r\n",(uint16_t )(temp-sval+1)*16);//打印SDRAM容量
 	}					 
}

