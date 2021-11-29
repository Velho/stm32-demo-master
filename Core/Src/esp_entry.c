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

#include "bme_task.h"

#include <bsp_os.h>
#include <cpu_cfg.h>

#include "app.h"
#include "esp_device.h"

static EspTaskHandle* espTaskHandles[] = {
    &espPushButtonHandleTask.taskHandle,
    &espMainAppHandleTask.taskHandle,
    &espBmeSensorHandleTask.taskHandle,
    NULL,
};

int EspStartup()
{
    // BmeSensorTask_Init();
    int result = 0;
    EspTaskHandle** taskHandle = espTaskHandles;

    while (taskHandle++)
    {
        if (*taskHandle == NULL)
        {
            break;
        }

        if ((*taskHandle)->fnTaskInit == NULL)
        {
            continue;
        }

        // Call the Handle Initializer.
        result = (*taskHandle)->fnTaskInit();

        if (result)
        {
            // Do something about the error.
            // (*taskHandle)->handleName;
        }
    }

    return result;
}

void EspStartupTask(void* p_arg)
{
    OS_ERR os_err;
    int result = 0;

    UNUSED(p_arg); // Unused.

    BSP_OS_TickEnable();
    OSStatTaskCPUUsageInit(&os_err);

    result = EspStartup();

    if (result)
    {
        Error_Handler();
    }

    OSTaskCreate(&espBmeSensorHandleTask.bmeSensorTaskTCB, "BME Sensor Task",
                 espBmeSensorHandleTask.taskHandle.fnTaskHandle, 0u, 7u, espBmeSensorHandleTask.bmeSensorTaskStk, 0u,
                 ESP_BME_STK_SIZE, 0u, 0u, 0u, (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), &os_err);

    if (os_err != OS_ERR_NONE)
    {
        Error_Handler();
    }

    OSTaskCreate(&espPushButtonHandleTask.appPushButtonTCB, "App Push Button Task",
                 espPushButtonHandleTask.taskHandle.fnTaskHandle, 0u, 6u, espPushButtonHandleTask.appPushButtonStk, 0u,
                 ESP_APP_PB_STK_SIZE, 0u, 0u, 0u, (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), &os_err);

    if (os_err != OS_ERR_NONE)
    {
        Error_Handler();
    }

    OSTaskCreate(&espMainAppHandleTask.appTaskTCB, "App Task", espMainAppHandleTask.taskHandle.fnTaskHandle, 0u, 5u,
                 espMainAppHandleTask.appTaskStk, 0u, ESP_APP_STK_SIZE, 0u, 0u, 0u,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), &os_err);

    if (os_err != OS_ERR_NONE)
    {
        Error_Handler();
    }
}
