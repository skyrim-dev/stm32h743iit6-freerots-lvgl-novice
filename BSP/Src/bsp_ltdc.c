#include "bsp_ltdc.h"
#include "fmc.h"
#include <stdbool.h>

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
	HAL_Delay(100);
	  
	SCB_CleanInvalidateDCache();
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
	ltdc_lcd_Fill((uint16_t*)framebuf, (uint16_t)GREEN, (uint32_t)pHeight * pWidth * PIXSIZE);
	HAL_Delay(100);
	  
	SCB_CleanInvalidateDCache();
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
	ltdc_lcd_Fill((uint16_t*)framebuf, (uint16_t)BLUE, (uint32_t)pHeight * pWidth * PIXSIZE);
	HAL_Delay(100);
	
	SCB_CleanInvalidateDCache();
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
	ltdc_lcd_Fill((uint16_t*)framebuf, (uint16_t)YELLOW, (uint32_t)pHeight * pWidth * PIXSIZE);
	HAL_Delay(100);
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