#include "bsp_ltdc.h"
#include "fmc.h"


__attribute__((section (".RAM_SDRAM"))) uint16_t framebuf[pHeight][pWidth];
uint16_t* fb_addr = (uint16_t*)((uint32_t)0xC0000000);

void ltdc_lcd_Fill(uint16_t* fb, uint16_t color, uint32_t length)
{
	uint16_t* tmp_fb = fb;
	for (uint32_t i = 0; i < length; i++) {
		*(tmp_fb + i) = color;
	}
}

void ltdc_lcd_loop_color(void)
{
	SCB_CleanInvalidateDCache();
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
	ltdc_lcd_Fill((uint16_t*)framebuf, (uint16_t)RED, (uint32_t)pHeight * pWidth * PIXSIZE);
	HAL_Delay(500);
	printf("RED\r\n");

	SCB_CleanInvalidateDCache();
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
	ltdc_lcd_Fill((uint16_t*)framebuf, (uint16_t)GREEN, (uint32_t)pHeight * pWidth * PIXSIZE);
	HAL_Delay(500);
	printf("GREEN\r\n");
	
	SCB_CleanInvalidateDCache();
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
	ltdc_lcd_Fill((uint16_t*)framebuf, (uint16_t)BLUE, (uint32_t)pHeight * pWidth * PIXSIZE);
	HAL_Delay(500);
	printf("BLUE\r\n");
	
	SCB_CleanInvalidateDCache();
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
	ltdc_lcd_Fill((uint16_t*)framebuf, (uint16_t)YELLOW, (uint32_t)pHeight * pWidth * PIXSIZE);
	HAL_Delay(500);
	printf("YELLOW\r\n");
}

void ltdc_draw_point(uint16_t x, uint16_t y, uint32_t color)
{
	if (HOR) {	// 横屏
		*(uint16_t*)((uint32_t)framebuf + PIXSIZE * (pWidth * y + x)) = color;
	} else {	// 竖屏
		*(uint16_t*)((uint32_t)framebuf + PIXSIZE * (pWidth * (pHeight - x - 1) + y)) = color;
	}
}

uint32_t ltdc_read_point(uint16_t x, uint16_t y, uint32_t color)
{
	if (HOR) {	// 横屏
		return *(uint16_t*)((uint32_t)framebuf + PIXSIZE * (pWidth * y + x)) = color;
	} else {	// 竖屏
		return *(uint16_t*)((uint32_t)framebuf + PIXSIZE * (pWidth * (pHeight - x - 1) + y)) = color;
	}
}

/**
 * @brief 简洁的LCD初始化函数
 * @retval true: 初始化成功, false: 初始化失败
 */
bool ltdc_lcd_init(void)
{
    printf("\r\nLCD初始化开始...\r\n");
    
    // 1. 检查SDRAM状态
	printf("1. 检查SDRAM状态...\r\n");
    if (HAL_SDRAM_GetState(&hsdram1) != HAL_SDRAM_STATE_READY) {
        printf("SDRAM未就绪，重新初始化...\r\n");
        FMC_SDRAM_TimingTypeDef SdramTiming = {0};
        if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK) {
            printf("SDRAM初始化失败\r\n");
            return false;
        }
    } else {
		printf("SDRAM已就绪\r\n");
	}
    
    // 2. 等待LCD硬件就绪
    printf("2. 等待LCD硬件就绪...\r\n");
    uint32_t timeout = 100; // 最多等待100ms
    while (timeout-- > 0) {
        if (LTDC->CDSR & LTDC_CDSR_VSYNCS) {
            break;
        }
        HAL_Delay(1);
    }
    
    if (timeout == 0) {
        printf("LCD硬件就绪超时\r\n");
        return false;
    } else {
		printf("LCD硬件已就绪\r\n");
	}
    
    // 3. 显存读写测试
    printf("3. 显存读写测试...\r\n");
    ltdc_draw_point(100, 100, RED);
    SCB_CleanInvalidateDCache();
    HAL_Delay(1);
    
    uint32_t read_color = ltdc_read_point(100, 100, RED);
    if (read_color != RED) {
        printf("显存测试失败\r\n");
        return false;
    } else {
		printf("显存测试通过\r\n");
	}
    
    // 4. 清屏并显示初始化完成标志
    SCB_CleanInvalidateDCache();
    while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
    ltdc_lcd_Fill((uint16_t*)framebuf, BLACK, pHeight * pWidth * PIXSIZE);
    
    // 在屏幕中心显示绿色方块表示初始化成功
    for (int x = 350; x < 450; x++) {
        for (int y = 200; y < 280; y++) {
            ltdc_draw_point(x, y, GREEN);
        }
    }
    SCB_CleanInvalidateDCache();
    
    printf("4. LCD初始化完成\r\n");
    return true;
}
