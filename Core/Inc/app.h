/*
 * app.h
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#ifndef INC_APP_H_
#define INC_APP_H_

/* #ifdef __cplusplus
extern "C"
{
#endif */

#include "esp_device.h"
#include "main.h"

#define ESP_APP_STK_SIZE 256u
#define ESP_APP_PB_STK_SIZE 256u

/**
 * TODO
 *  AppTask was used as testing bench for the poc implementation. Find new ways to utilize the module.
 */

typedef struct
{
    EspTaskHandle taskHandle;
    OS_TCB appPushButtonTCB;
    CPU_STK appPushButtonStk[ESP_APP_PB_STK_SIZE];
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
 */
void App_Task(void* p_arg);

/**
 * @brief Poll the push button.
 *
 * @param p_arg Unused.
 */
void App_PushButtonTask(void* p_arg);

/* #ifdef __cplusplus
}
#endif */

#endif /* INC_APP_H_ */
