/*
 * app.h
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/**
 * TODO
 *  AppTask was used as testing bench for the poc implementation. Find new ways to utilize the module.
 */

extern OS_TCB       AppPushButtonTCB;
extern CPU_STK      AppPushButtonStk[128u];

extern OS_TCB 		AppTaskTCB;
extern CPU_STK 		AppTaskStk[128u];


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
int App_GetCounter();

/**
 * @brief
 *
 */
void App_Task(void *p_arg);


/**
 * @brief Poll the push button.
 *
 * @param p_arg Unused.
 */
void App_PushButtonTask(void *p_arg);


#ifdef __cplusplus
}
#endif

#endif /* INC_APP_H_ */
