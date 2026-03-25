## BSP 层内部结构

### Drivers/ - 通用设备驱动
- 可复用于多个项目
- 与具体板子弱相关
- 示例：lcd.c（支持 ILI9341/NT35310/ST7789 等）

### Src/ - 板级特定驱动  
- 与当前板子强相关
- 包含硬件配置和引脚定义
- 示例：bsp_ltdc.c、fmc_sdram_init.c

## 调用关系
应用层 → Src/ (板级接口) → Drivers/ (通用驱动) → Core/ (HAL 库)

## 快速开始
1. 初始化：MX_LTDC_Init()  // 在 main.c 中已调用
2. 画点：ltdc_draw_point(x, y, color)
3. 填充：ltdc_lcd_Fill(fb, color, length)

## 移植指南
更换板子时需要修改：
- Src/bsp_ltdc.c - LTDC 时序参数
- Src/fmc_sdram_init.c - SDRAM 型号和时序
- Inc/*.h - 分辨率、引脚定义等