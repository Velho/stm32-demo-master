/**
 * @file comm_task.h
 * @author Joel (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-11-29
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INC_COMM_TASK_H
#define INC_COMM_TASK_H

#include "datastorage.h"
#include "esp_taskhandle.h"

#include <os.h>

#define ESP_COMM_RX_STK_SIZE 256u
#define ESP_COMM_TX_STK_SIZE 256u


typedef struct
{
    EspTaskHandle taskHandle;
    OS_TCB commRxTaskTCB;
    CPU_STK commRxTaskStk[ESP_COMM_RX_STK_SIZE];

    DataStorageList dsCommRxList;
} EspCommRxTaskHandle;

extern EspCommRxTaskHandle espCommRxTaskHandle;

typedef struct
{
    EspTaskHandle taskHandle;

    OS_TCB commTxTaskTCB;
    CPU_STK commTxTaskStk[ESP_COMM_TX_STK_SIZE];

    DataStorageList dsCommTxList;
} EspCommTxTaskHandle;

extern EspCommTxTaskHandle espCommTxTaskHandle;

/**
 * @brief
 *
 * @return int
 */
int EspCommInit();


/**
 * @brief
 *
 * @param p_arg
 */
void EspCommRxTask(void* p_arg);

/**
 * @brief
 *
 * @param p_arg
 */
void EspCommTxTask(void* p_arg);

#endif
