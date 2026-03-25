#ifndef __DELAY_H
#define __DELAY_H

#include "stm32h7xx_hal.h"

extern void delay_init(uint16_t sysclk);   	/* 初始化延迟函数 */
extern void delay_ms(uint16_t nms);        	/* 延时nms */
extern void delay_us(uint32_t nus);        	/* 延时nus */
extern void delay_tick_ms(uint32_t ms);			/* 滴答延时nms*/
extern void TimingDelay_Decrement(void);
extern void Delay_ns (unsigned char t);			/* ns延时 */
extern void Delay_1us (uint16_t t);					/* 延时时基:1us */
extern void Delay_2us (uint16_t t);					/* 延时时基:2us */
extern void Delay_10us (uint16_t t);   			/* 延时时基:10us */
extern void Delay_882us (void);							/* 延时822us */
extern void Delay_250us (unsigned char t);  /* 延时时基:250us */
extern void Delay_5ms (uint16_t t);					/* 延时时基:5ms */
extern void Delay_1ms (__IO uint32_t t);		/* 延时时基:1ms */
extern void Delay_50ms (unsigned char t);		/* 延时时基:50ms */
extern void Delay(__IO uint32_t nCount);

#endif

