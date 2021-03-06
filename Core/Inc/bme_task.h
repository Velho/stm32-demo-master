/*
 * bme_task.h
 *
 *  Created on: Nov 12, 2021
 *      Author: Velho
 */

#ifndef INC_BME_TASK_H
#define INC_BME_TASK_H

#include <esp_taskhandle.h>
#include "datastorage.h"
#include "bme280/bme280_defs.h"

#include <os.h>

#define ESP_BME_STK_SIZE 256u

typedef struct
{
    EspTaskHandle taskHandle;                   //!< Task Handle with the function pointers for Initializer and Tasks.
    OS_TCB bmeSensorTaskTCB;                    //!< Transmision Control Block for this Task.
    CPU_STK bmeSensorTaskStk[ESP_BME_STK_SIZE]; //!< Stack used for this Task.

    DataStorageList dsSensorList; //!< Ringbuffer for the internal data.
} EspBmeSensorHandleTask;

extern EspBmeSensorHandleTask espBmeSensorHandleTask;

/**
 * @brief Initializes the sensor task.
 */
int BmeSensorTask_Init();

/**
 * @brief Describes the Sensor process.
 * This is also a kernel task.
 */
void BmeSensorTask(void* p_arg);

#endif /* INC_BME_TASK_H_ */
