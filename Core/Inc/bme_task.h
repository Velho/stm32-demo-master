/*
 * bme_task.h
 *
 *  Created on: Nov 12, 2021
 *      Author: Velho
 */

#ifndef INC_BME_TASK_H
#define INC_BME_TASK_H

#include "datastorage.h"
#include "esp_device.h"

#include <os.h>

typedef struct
{
    // EspTaskInit bmeTaskInit;     //!< Function pointer to initialize the module.
    // EspTaskHandle bmeTaskHandle; //!< Function pointer to the Task Handle.

    EspTaskHandle taskHandle;
    OS_TCB BmeSensorTaskTCB;        //!< Transmision Control Block for this Task.
    CPU_STK BmeSensorTaskStk[128u]; //!< Stack used for this Task.

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
