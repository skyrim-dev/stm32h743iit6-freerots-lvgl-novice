#ifndef __BSP_LTDC_H
#define __BSP_LTDC_H

#include "stm32h7xx_hal.h"
#include <stdbool.h>

#define LTDC_ADDR	0xC0000000

/* 常用画笔颜色 */
#define WHITE           0xFFFF      /* 白色 */
#define BLACK           0x0000      /* 黑色 */
#define RED             0xF800      /* 红色 */
#define GREEN           0x07E0      /* 绿色 */
#define BLUE            0x001F      /* 蓝色 */ 
#define MAGENTA         0xF81F      /* 品红色/紫红色 = BLUE + RED */
#define YELLOW          0xFFE0      /* 黄色 = GREEN + RED */
#define CYAN            0x07FF      /* 青色 = GREEN + BLUE */  

/* 非常用颜色 */
#define BROWN           0xBC40      /* 棕色 */
#define BRRED           0xFC07      /* 棕红色 */
#define GRAY            0x8430      /* 灰色 */ 
#define DARKBLUE        0x01CF      /* 深蓝色 */
#define LIGHTBLUE       0x7D7C      /* 浅蓝色 */ 
#define GRAYBLUE        0x5458      /* 灰蓝色 */ 
#define LIGHTGREEN      0x841F      /* 浅绿色 */  
#define LGRAY           0xC618      /* 浅灰色(PANNEL),窗体背景色 */ 
#define LGRAYBLUE       0xA651      /* 浅灰蓝色(中间层颜色) */ 
#define LBBLUE          0x2B12      /* 浅棕蓝色(选择条目的反色) */ 

/* 宽度和高度 */
#define pWidth	800
#define pHeight	480

/* 横屏和竖屏 */
#define HOR	true	// 横屏
#define VER	false	// 竖屏

/* RGB类型 */
#define RGB888		1
#define RGB565		2
#define RGB_TYPE	RGB565

/* 像素大小 */
#if RGB_TYPE == RGB888
#define PIXSIZE 3	// 单个像素大小
#endif
#if RGB_TYPE == RGB565
#define PIXSIZE 2	// 单个像素大小
#endif


bool ltdc_lcd_init(void);

void ltdc_lcd_Fill(uint16_t* fb, uint16_t color, uint32_t length);
void ltdc_lcd_loop_color(void);

void ltdc_draw_point(uint16_t x, uint16_t y, uint32_t color);
uint32_t ltdc_read_point(uint16_t x, uint16_t y, uint32_t color);


#endif
