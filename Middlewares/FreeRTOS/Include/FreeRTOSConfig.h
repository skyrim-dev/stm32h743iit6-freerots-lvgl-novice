#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

/******************************************************************************/
/* 基础配置 - 核心系统参数 *****************************************************/
/******************************************************************************/

/* 硬件相关定义 */
extern uint32_t SystemCoreClock;
#define configCPU_CLOCK_HZ                        ( SystemCoreClock )
#define configTICK_RATE_HZ                        1000        /* 系统节拍频率 (1ms中断一次) */

/* 系统核心参数 */
#define configMAX_PRIORITIES                      32          /* 最大优先级数 */
#define configMINIMAL_STACK_SIZE                  128         /* 最小任务栈大小 (字) */
#define configMAX_TASK_NAME_LEN                   16          /* 任务名最大字符数 */
#define configTICK_TYPE_WIDTH_IN_BITS             TICK_TYPE_WIDTH_32_BITS  /* 节拍计数器位数 */
#define configSTACK_DEPTH_TYPE                    size_t      /* 任务栈大小参数类型 */
#define configMESSAGE_BUFFER_LENGTH_TYPE          size_t      /* 消息缓冲区长度类型 */

/******************************************************************************/
/* 调度配置 - 任务调度相关 *****************************************************/
/******************************************************************************/

#define configUSE_PREEMPTION                      1           /* 抢占式调度 (1=开启, 0=协作式) */
#define configUSE_TIME_SLICING                    1           /* 时间片调度 (同优先级任务轮流执行) */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION   1           /* 硬件优化任务选择 (效率高但有限制) */
#define configUSE_TICKLESS_IDLE                   0           /* 低功耗tickless模式 */
#define configIDLE_SHOULD_YIELD                   1           /* 空闲任务让出CPU */
#define configUSE_MINI_LIST_ITEM                  1           /* 精简链表项开关 */

/******************************************************************************/
/* 内存管理配置 ***************************************************************/
/******************************************************************************/

#define configSUPPORT_STATIC_ALLOCATION           0           /* 静态内存分配 */
#define configSUPPORT_DYNAMIC_ALLOCATION          1           /* 动态内存分配 */
#define configTOTAL_HEAP_SIZE                     ((size_t)(64 * 1024))  /* 堆总大小 (64KB) */
#define configAPPLICATION_ALLOCATED_HEAP          0           /* 用户手动分配堆内存 */
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP 0           /* 任务栈从独立堆分配 */
#define configHEAP_CLEAR_MEMORY_ON_FREE           0           /* 内存释放时清零 */
#define configENABLE_HEAP_PROTECTOR               0           /* 堆保护开关 */

/******************************************************************************/
/* 中断配置 - 中断优先级和嵌套 ***********************************************/
/******************************************************************************/

#ifdef __NVIC_PRIO_BITS
    #define configPRIO_BITS __NVIC_PRIO_BITS
#else
    #define configPRIO_BITS 4
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   15          /* 最低中断优先级 */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5        /* 允许调用FreeRTOS API的最高中断优先级 */

#define configKERNEL_INTERRUPT_PRIORITY           ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY      ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_API_CALL_INTERRUPT_PRIORITY     ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/******************************************************************************/
/* 功能模块配置 ***************************************************************/
/******************************************************************************/

/* 软件定时器 */
#define configUSE_TIMERS                          1           /* 软件定时器开关 */
#define configTIMER_TASK_PRIORITY                 ( configMAX_PRIORITIES - 1 )  /* 定时器任务优先级 */
#define configTIMER_TASK_STACK_DEPTH              (configMINIMAL_STACK_SIZE * 2)  /* 定时器任务栈大小 */
#define configTIMER_QUEUE_LENGTH                  10          /* 定时器命令队列长度 */

/* 事件组 */
#define configUSE_EVENT_GROUPS                    1           /* 事件组功能开关 */

/* 流缓冲区 */
#define configUSE_STREAM_BUFFERS                  1           /* 流缓冲区/消息缓冲区开关 */

/* 协程 */
#define configUSE_CO_ROUTINES                     0           /* 协程开关 */
#define configMAX_CO_ROUTINE_PRIORITIES           1           /* 协程最大优先级数 */

/* 同步机制 */
#define configUSE_MUTEXES                         1           /* 互斥信号量 */
#define configUSE_RECURSIVE_MUTEXES               1           /* 递归互斥信号量 */
#define configUSE_COUNTING_SEMAPHORES             1           /* 计数信号量 */
#define configUSE_QUEUE_SETS                      1           /* 队列集 */
#define configUSE_TASK_NOTIFICATIONS              1           /* 任务通知功能 */

/* 其他功能 */
#define configQUEUE_REGISTRY_SIZE                 10          /* 注册的信号量和消息队列个数 */
#define configTASK_NOTIFICATION_ARRAY_ENTRIES     1           /* 任务通知数组大小 */
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS   0           /* 线程本地存储指针个数 */
#define configUSE_APPLICATION_TASK_TAG            0           /* 任务标签功能 */
#define configENABLE_BACKWARD_COMPATIBILITY       0           /* 向后兼容性 */
#define configUSE_NEWLIB_REENTRANT                0           /* Newlib重入结构体 */

/******************************************************************************/
/* 调试和统计功能配置 *********************************************************/
/******************************************************************************/

#define configUSE_TRACE_FACILITY                  1           /* 可视化跟踪调试 */
#define configUSE_STATS_FORMATTING_FUNCTIONS      1           /* 统计格式化函数 */
#define configGENERATE_RUN_TIME_STATS             0           /* 运行时间统计 */
#define configSTATS_BUFFER_MAX_LENGTH             0xFFFF      /* 统计函数缓冲区最大长度 */

/******************************************************************************/
/* 钩子函数配置 ***************************************************************/
/******************************************************************************/

#define configUSE_IDLE_HOOK                       0           /* 空闲任务钩子函数 */
#define configUSE_TICK_HOOK                       0           /* 系统节拍中断钩子函数 */
#define configUSE_MALLOC_FAILED_HOOK              0           /* 动态内存申请失败钩子函数 */
#define configUSE_DAEMON_TASK_STARTUP_HOOK        0           /* 定时器服务任务启动钩子函数 */
#define configUSE_SB_COMPLETED_CALLBACK           0           /* 流缓冲区完成回调 */
#define configCHECK_FOR_STACK_OVERFLOW            0           /* 栈溢出检测 (0=关闭, 1=方法1, 2=方法2) */

/******************************************************************************/
/* API函数包含控制 ***********************************************************/
/******************************************************************************/

#define INCLUDE_vTaskPrioritySet                  1           /* 设置任务优先级 */
#define INCLUDE_uxTaskPriorityGet                 1           /* 获取任务优先级 */
#define INCLUDE_vTaskDelete                       1           /* 删除任务 */
#define INCLUDE_vTaskSuspend                      1           /* 挂起任务 */
#define INCLUDE_xResumeFromISR                    1           /* 中断中恢复挂起任务 */
#define INCLUDE_vTaskDelayUntil                   1           /* 任务绝对延时 */
#define INCLUDE_vTaskDelay                        1           /* 任务延时 */
#define INCLUDE_xTaskGetSchedulerState            1           /* 获取任务调度器状态 */
#define INCLUDE_xTaskGetCurrentTaskHandle         1           /* 获取当前任务句柄 */
#define INCLUDE_uxTaskGetStackHighWaterMark       1           /* 获取任务堆栈历史剩余最小值 */
#define INCLUDE_xTaskGetIdleTaskHandle            1           /* 获取空闲任务句柄 */
#define INCLUDE_eTaskGetState                     1           /* 获取任务状态 */
#define INCLUDE_xEventGroupSetBitFromISR          1           /* 中断中设置事件标志位 */
#define INCLUDE_xTimerPendFunctionCall           1           /* 挂函数到定时器服务任务 */
#define INCLUDE_xTaskAbortDelay                   1           /* 中断任务延时 */
#define INCLUDE_xTaskGetHandle                    1           /* 通过任务名获取任务句柄 */
#define INCLUDE_xTaskResumeFromISR                1           /* 中断中恢复挂起任务 */

/******************************************************************************/
/* 断言和错误处理 ************************************************************/
/******************************************************************************/

#define vAssertCalled(char, int) printf("Error: %s, %d\r\n", char, int);
#define configASSERT( x )         \
    if( ( x ) == 0 )              \
    {                             \
        taskDISABLE_INTERRUPTS(); \
        for( ; ; )                \
        ;                         \
    }

/******************************************************************************/
/* 中断服务函数重映射 ********************************************************/
/******************************************************************************/

/* FreeRTOS中断服务函数重映射，需删除stm32h7xx_it.c中的对应函数 */
#define vPortSVCHandler                         SVC_Handler
#define xPortPendSVHandler                      PendSV_Handler

#endif /* FREERTOS_CONFIG_H */