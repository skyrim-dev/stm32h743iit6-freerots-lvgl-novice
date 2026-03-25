**硬件驱动层 (Driver Layer / HAL - Hardware Abstraction Layer)**

- **职责**：这是最底层，直接和硬件打交道。负责操作MCU的寄存器，初始化外设（GPIO, UART, SPI, I2C, ADC等），提供最基本的硬件读写函数。比如HAL_SPI_Transmit()，GPIO_SetPinLevel()。
- **特点**：与具体硬件型号紧密相关。很多芯片厂商会提供官方的HAL库，就属于这一层。它的目标是**屏蔽硬件细节**，向上层提供稳定、统一的硬件操作接口。
- **原则**：这一层应该尽量保持“纯粹”，只做硬件操作，不掺杂任何业务逻辑。
