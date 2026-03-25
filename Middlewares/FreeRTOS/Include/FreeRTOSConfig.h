/*
 * FreeRTOS Kernel V11.1.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*******************************************************************************
 * This file provides an example FreeRTOSConfig.h header file, inclusive of an
 * abbreviated explanation of each configuration item.  Online and reference
 * documentation provides more information.
 * https://www.freertos.org/a00110.html
 *
 * Constant values enclosed in square brackets ('[' and ']') must be completed
 * before this file will build.
 *
 * Use the FreeRTOSConfig.h supplied with the RTOS port in use rather than this
 * generic file, if one is available.
 ******************************************************************************/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

/* CPU主频（匹配MCU实际主频）*/
extern uint32_t SystemCoreClock;
#define configCPU_CLOCK_HZ    ( SystemCoreClock )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

/* 系统节拍频率（1000Hz=1ms中断一次，常用值）*/
#define configTICK_RATE_HZ                         1000

/* 开启抢占式调度（1=抢占式，0=协作式，几乎都用1）*/
#define configUSE_PREEMPTION                       1

/* 开启时间片调度（1=同优先级任务轮流执行，0=关闭）*/
#define configUSE_TIME_SLICING                     1

/* 开启硬件优化的任务选择（Cortex-M建议设1） */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION    1

/* 低功耗tickless模式（0-关闭，1-开启，适用低功耗场景） */
#define configUSE_TICKLESS_IDLE                    0

/* 系统调用允许的最高中断优先级 */
#define configMAX_PRIORITIES                       32

/* 最小任务栈大小 */
#define configMINIMAL_STACK_SIZE                   128

/* 定义任务名最大字符数, 默认: 16 */
#define configMAX_TASK_NAME_LEN                    16

/* 系统节拍类型位数，32位MCU=32 */
#define configTICK_TYPE_WIDTH_IN_BITS              TICK_TYPE_WIDTH_32_BITS

/* 同优先级能抢占空闲任务 */
#define configIDLE_SHOULD_YIELD                    1

/* 定义任务通知数组的大小, 默认: 1 */
#define configTASK_NOTIFICATION_ARRAY_ENTRIES      1

/* 定义可以注册的信号量和消息队列个数，默认0 */
#define configQUEUE_REGISTRY_SIZE                  10

 /* 兼容老版本使能，1-使能，默认为0 */
#define configENABLE_BACKWARD_COMPATIBILITY        0

/* 定义线程本地存储指针的个数,默认0 */
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS    0

/* 精简链表项开关，默认1 */
#define configUSE_MINI_LIST_ITEM                   1

/* 任务栈大小参数的类型，默认uint32_t */
#define configSTACK_DEPTH_TYPE                     size_t

/* 定义消息缓冲区中消息长度的数据类型, 默认: size_t */
#define configMESSAGE_BUFFER_LENGTH_TYPE           size_t

/* 内存释放时是否清零，1-清零，增加开销，默认为0-不清零 */
#define configHEAP_CLEAR_MEMORY_ON_FREE            0

 /* 统计函数（vTaskList）的缓冲区最大长度，默认为0xFFFF*/
#define configSTATS_BUFFER_MAX_LENGTH              0xFFFF

/* 1: 任务创建时分配Newlib的重入结构体, 默认: 0 */
#define configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

/* 1: 使能软件定时器, 默认: 0 */
#define configUSE_TIMERS                1

 /* 定义软件定时器任务的优先级, 无默认configUSE_TIMERS为1时需定义 */
#define configTIMER_TASK_PRIORITY       ( configMAX_PRIORITIES - 1 )

 /*定时器任务的栈大小*/
#define configTIMER_TASK_STACK_DEPTH    (configMINIMAL_STACK_SIZE * 2)

/* 定义软件定时器命令队列的长度, 无默认，configUSE_TIMERS为1时需定义 */
#define configTIMER_QUEUE_LENGTH        10

/******************************************************************************/
/* Event Group related definitions. *******************************************/
/******************************************************************************/

/* 事件组功能开关,1-开启，默认开启 */
#define configUSE_EVENT_GROUPS    1

/******************************************************************************/
/* Stream Buffer related definitions. *****************************************/
/******************************************************************************/

/* 控制流缓冲区 / 消息缓冲区功能的开关，默认为1-开启 */
#define configUSE_STREAM_BUFFERS    1

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

/* 静态内存分配开关,1-开启，0-关闭 */
#define configSUPPORT_STATIC_ALLOCATION              0

/* 动态内存分配开关,1-开启，0-关闭 */
#define configSUPPORT_DYNAMIC_ALLOCATION             1

/* FreeRTOS 堆总大小 */
#define configTOTAL_HEAP_SIZE                        ((size_t)(64 * 1024))

/* 1: 用户手动分配FreeRTOS内存堆(ucHeap), 默认: 0*/
#define configAPPLICATION_ALLOCATED_HEAP             0

/* 1: 用户自行实现任务创建时使用的内存申请与释放函数, 默认: 0 */
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP    0

/* 堆保护开关，默认为0，开启会增加开销 */
#define configENABLE_HEAP_PROTECTOR                  0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

/* 中断嵌套行为配置 */
#ifdef __NVIC_PRIO_BITS
    #define configPRIO_BITS __NVIC_PRIO_BITS
#else
    #define configPRIO_BITS 4
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

/* 内核中断（SysTick/PendSV/SVC）的优先级，默认为0-优先级最高 */
#define configKERNEL_INTERRUPT_PRIORITY          ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )   

/* 允许调用 FreeRTOS API 的最高中断优先级 */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY     ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_API_CALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/
#define configUSE_IDLE_HOOK                   0     /* 1: 使能空闲任务钩子函数, 无默认需定义  */
#define configUSE_TICK_HOOK                   0     /* 1: 使能系统时钟节拍中断钩子函数, 无默认需定义 */
#define configUSE_MALLOC_FAILED_HOOK          0     /* 1: 使能动态内存申请失败钩子函数, 默认: 0 */
#define configUSE_DAEMON_TASK_STARTUP_HOOK    0     /* 1: 使能定时器服务任务首次执行前的钩子函数, 默认: 0 */

#define configUSE_SB_COMPLETED_CALLBACK       0     /* 流缓冲区完成回调开关 */

#define configCHECK_FOR_STACK_OVERFLOW        0     /* 1: 使能栈溢出检测方法1, 2: 使能栈溢出检测方法2, 默认: 0 */

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/
#define configGENERATE_RUN_TIME_STATS           0   /* 不启用运行时间统计功能 */
#define configUSE_TRACE_FACILITY                0   /* 不启用可视化跟踪调试 */

/* 1: configUSE_TRACE_FACILITY为1时，会编译vTaskList()和vTaskGetRunTimeStats()函数, 默认: 0 */
#define configUSE_STATS_FORMATTING_FUNCTIONS    0

/******************************************************************************/
/* Co-routine related definitions. ********************************************/
/******************************************************************************/
#define configUSE_CO_ROUTINES              0    /* 1: 启用协程, 默认: 0 */
#define configMAX_CO_ROUTINE_PRIORITIES    1    /* 协程最大优先级数 */

/******************************************************************************/
/* Debugging assistance. ******************************************************/
/******************************************************************************/

/* configASSERT() has the same semantics as the standard C assert().  It can
 * either be defined to take an action when the assertion fails, or not defined
 * at all (i.e. comment out or delete the definitions) to completely remove
 * assertions.  configASSERT() can be defined to anything you want, for example
 * you can call a function if an assert fails that passes the filename and line
 * number of the failing assert (for example, "vAssertCalled( __FILE__, __LINE__ )"
 * or it can simple disable interrupts and sit in a loop to halt all execution
 * on the failing line for viewing in a debugger. */
#define configASSERT( x )         \
    if( ( x ) == 0 )              \
    {                             \
        taskDISABLE_INTERRUPTS(); \
        for( ; ; )                \
        ;                         \
    }

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/
/* Set the following configUSE_* constants to 1 to include the named feature in
 * the build, or 0 to exclude the named feature from the build. */
#define configUSE_TASK_NOTIFICATIONS           1    /*!< 开启任务通知功能，默认开启 */
#define configUSE_MUTEXES                      1    /*!< 使用互斥信号量 */
#define configUSE_RECURSIVE_MUTEXES            1    /*!< 使用递归互斥信号量 */
#define configUSE_COUNTING_SEMAPHORES          1    /*!< 为1时使用计数信号量 */
#define configUSE_QUEUE_SETS                   1    /*!< 启用队列 */
#define configUSE_APPLICATION_TASK_TAG         0

/* Set the following INCLUDE_* constants to 1 to incldue the named API function,
 * or 0 to exclude the named API function.  Most linkers will remove unused
 * functions even when the constant is 1. */
#define INCLUDE_vTaskPrioritySet               1    /* 设置任务优先级 */
#define INCLUDE_uxTaskPriorityGet              1    /* 获取任务优先级 */
#define INCLUDE_vTaskDelete                    1    /* 删除任务 */
#define INCLUDE_vTaskSuspend                   1    /* 挂起任务 */
#define INCLUDE_xResumeFromISR                 1    /* 恢复在中断中挂起的任务 */
#define INCLUDE_vTaskDelayUntil                1    /* 任务绝对延时 */
#define INCLUDE_vTaskDelay                     1    /* 任务延时 */
#define INCLUDE_xTaskGetSchedulerState         1    /* 获取任务调度器状态 */
#define INCLUDE_xTaskGetCurrentTaskHandle      1    /* 获取当前任务的任务句柄 */
#define INCLUDE_uxTaskGetStackHighWaterMark    1    /* 获取任务堆栈历史剩余最小值 */
#define INCLUDE_xTaskGetIdleTaskHandle         1    /* 获取空闲任务的任务句柄 */
#define INCLUDE_eTaskGetState                  1    /* 获取任务状态 */
#define INCLUDE_xEventGroupSetBitFromISR       1    /* 在中断中设置事件标志位 */
#define INCLUDE_xTimerPendFunctionCall         1    /* 将函数的执行挂到定时器服务任务 */
#define INCLUDE_xTaskAbortDelay                1    /* 中断任务延时 */
#define INCLUDE_xTaskGetHandle                 1    /* 通过任务名获取任务句柄 */
#define INCLUDE_xTaskResumeFromISR             1    /* 恢复在中断中挂起的任务 */

/* FreeRTOS中断服务函数相关定义 */
#define vPortSVCHandler                         SVC_Handler
#define xPortPendSVHandler                      PendSV_Handler
#endif /* FREERTOS_CONFIG_H */

