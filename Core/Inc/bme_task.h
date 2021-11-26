/*
 * bme_task.h
 *
 *  Created on: Nov 12, 2021
 *      Author: Velho
 */

#ifndef INC_BME_TASK_H_
#define INC_BME_TASK_H_

#include <os.h>
#include "datastorage.h"

typedef struct
{
    OS_TCB BmeSensorTaskTCB;        //!< Transmision Control Block for this Task.
    CPU_STK BmeSensorTaskStk[128u]; //!< Stack used for this Task.

    DataStorageList dsSensorList; //!< Ringbuffer for the internal data.
} BmeSensorHandleTask;

extern BmeSensorHandleTask bmeSensorHandleTask;

/**
 * @brief Initializes the sensor task.
 */
void BmeSensorTask_Init();

/**
 * @brief Describes the Sensor process.
 * This is also a kernel task.
 */
void BmeSensorTask(void* p_arg);

#endif /* INC_BME_TASK_H_ */
