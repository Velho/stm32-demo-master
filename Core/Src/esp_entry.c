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

#include <app_task.h>
#include "esp_entry.h"
#include "main.h"

#include "comm_task.h"

#ifdef ESP_SLAVE
#include "bme_task.h"
#endif

#include <bsp_os.h>
#include <cpu_cfg.h>

static EspTaskHandle* espTaskHandles[] = {
#ifndef ESP_SLAVE
    &espPushButtonHandleTask.taskHandle,
    &espMainAppHandleTask.taskHandle,
#else
    &espBmeSensorHandleTask.taskHandle,
#endif

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
    UNUSED(p_arg); // Unused.
    OS_ERR os_err;
    int result = 0;

    BSP_OS_TickEnable();
    OSStatTaskCPUUsageInit(&os_err);

    result = EspStartup();

    if (result)
    {
        Error_Handler();
    }

#ifdef ESP_SLAVE

    OSTaskCreate(
    		&espBmeSensorHandleTask.bmeSensorTaskTCB,
    		"BME Sensor Task",
			espBmeSensorHandleTask.taskHandle.fnTaskHandle,
			0u, 7u, espBmeSensorHandleTask.bmeSensorTaskStk, 0u,
                 ESP_BME_STK_SIZE, 0u, 0u, 0u, (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), &os_err);

    if (os_err != OS_ERR_NONE)
    {
        Error_Handler();
    }

//    OSTaskCreate(
//    		&espCommRxTaskHandle.commRxTaskTCB,
//			"Slave RX Task",
//    		espCommRxTaskHandle.taskHandle.fnTaskHandle,
//			0u, 5u, espCommRxTaskHandle.commRxTaskStk,
//			0u, ESP_COMM_RX_STK_SIZE, 0u, 0u, 0u,
//			(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), &os_err);
//
//    if (os_err != OS_ERR_NONE)
//    {
//    	Error_Handler();
//    }

    OSTaskCreate(
    		&espCommTxTaskHandle.commTxTaskTCB,
			"Slave TX Task",
    		espCommTxTaskHandle.taskHandle.fnTaskHandle,
			0u, 5u, espCommTxTaskHandle.commTxTaskStk,
			0u, ESP_COMM_RX_STK_SIZE, 0u, 0u, 0u,
			(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), &os_err);

    if (os_err != OS_ERR_NONE)
    {
    	Error_Handler();
    }

#else

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

    OSTaskCreate(
    		&espCommRxTaskHandle.commRxTaskTCB,
			"Master RX Task",
    		espCommRxTaskHandle.taskHandle.fnTaskHandle,
			0u, 4u, espCommRxTaskHandle.commRxTaskStk,
			0u, ESP_COMM_RX_STK_SIZE, 0u, 0u, 0u,
			(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), &os_err);

    if (os_err != OS_ERR_NONE)
    {
    	Error_Handler();
    }

//    OSTaskCreate(
//    		&espCommTxTaskHandle.commTxTaskTCB,
//			"Master TX Task",
//    		espCommTxTaskHandle.taskHandle.fnTaskHandle,
//			0u, 3u, espCommTxTaskHandle.commTxTaskStk,
//			0u, ESP_COMM_RX_STK_SIZE, 0u, 0u, 0u,
//			(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), &os_err);
//
//    if (os_err != OS_ERR_NONE)
//    {
//    	Error_Handler();
//    }


#endif

}
