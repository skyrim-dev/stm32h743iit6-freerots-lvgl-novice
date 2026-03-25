**[板级支持包层](https://zhida.zhihu.com/search?content_id=258738610&content_type=Article&match_order=1&q=板级支持包层&zhida_source=entity) (BSP - Board Support Package)**

- **职责**：这一层是可选的，但强烈推荐。它建立在驱动层之上，**关联了具体的电路板设计**。它知道哪个GPIO引脚连接到了LED灯，哪个SPI接口连接到了特定的传感器。它提供的是面向“板子上某个具体功能单元”的接口。比如BSP_LED_On(LED_ID_STATUS)，BSP_ReadTemperature()。
- **特点**：它调用驱动层的函数，但封装了板级的特定信息。换块板子，可能驱动层不用大改，但BSP层几乎肯定要改。
- **好处**：让应用层代码彻底与具体引脚、具体外设通道解耦。应用层只需要关心“状态灯”亮灭，而不需要知道这个灯接在哪个引脚。
