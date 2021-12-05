/**
 * @file app_task.h
 * @author Velho (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-12-02
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifdef ESP_MASTER
#ifndef INC_APP_TASK_H_
#define INC_APP_TASK_H_

#include "esp_taskhandle.h"
#include "main.h"

#define ESP_APP_STK_SIZE 256u
#define ESP_APP_PB_STK_SIZE 256u

/**
 * TODO AppTask was used as testing bench for the poc implementation. Find new ways to utilize the module.
 */

typedef struct
{
    EspTaskHandle taskHandle;
    OS_TCB appPushButtonTCB;
    CPU_STK appPushButtonStk[ESP_APP_PB_STK_SIZE];

    SensorType selectedSensorType;
} EspPushButtonHandleTask;

extern EspPushButtonHandleTask espPushButtonHandleTask;

typedef struct
{
    EspTaskHandle taskHandle;
    OS_TCB appTaskTCB;
    CPU_STK appTaskStk[ESP_APP_STK_SIZE];
} EspMainAppHandleTask;

extern EspMainAppHandleTask espMainAppHandleTask;

/**
 * @brief
 *
 */
int App_Init();

/**
 * @brief
 *
 * @return int
 */
uint8_t App_GetUserMode();

/**
 * @brief
 *
 * @return uint8_t
 */
uint8_t App_GetSensorType();

/**
 * @brief Application Task.
 * Pops value from the Ringbuffer and updates the display.
 */
void App_Task(void* p_arg);

/**
 * @brief Poll the push button.
 *
 * @param p_arg Unused.
 */
void App_PushButtonTask(void* p_arg);

#endif /* INC_APP_TASK_H_ */
#endif /* ESP_MASTER */
