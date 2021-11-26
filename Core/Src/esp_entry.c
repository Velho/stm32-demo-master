/**
 * @file esp_entry.c
 * @author Joel (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-11-26
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "esp_entry.h"
#include "main.h"

#include <cpu_cfg.h>
#include <bsp_os.h>

void EspStartupTask(void* p_arg)
{
    OS_ERR os_err;

    (void)p_arg; // Unused.

    BSP_OS_TickEnable();

    OSStatTaskCPUUsageInit(&os_err);

    /*
    OSTaskCreate(&BmeSensorTaskTCB, "BME Sensor Task", BmeSensorTask, 0u, 5u, // Prio #5
            BmeSensorTaskStk, 0u, 128u, 0u, 0u, 0u,
            (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ), &os_err);
     */

    App_Init();

    OSTaskCreate(&AppPushButtonTCB, "App Push Button Task", App_PushButtonTask, 0u, 6u, AppPushButtonStk, 0u, 128u, 0u,
                 0u, 0u, (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), &os_err);

    if (os_err != OS_ERR_NONE)
    {
        Error_Handler();
    }

    OSTaskCreate(&AppTaskTCB, "App Task", App_Task, 0u, 5u, AppTaskStk, 0u, 256u, 0u, 0u, 0u,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), &os_err);

    if (os_err != OS_ERR_NONE)
    {
        Error_Handler();
    }
}
