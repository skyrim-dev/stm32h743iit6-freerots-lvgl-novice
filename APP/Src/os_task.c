#include "os_task.h"
#include "freeRTOS.h"
#include "task.h"

void os_task_demo(void)
{
    while(1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
