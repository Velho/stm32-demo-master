/*
 * bme_task.c
 *
 *  Created on: Nov 12, 2021
 *      Author: Velho
 */

#include "bme_task.h"
#include "bme_sensor.h"
#include "data_storage.h"


OS_TCB       BmeSensorTaskTCB;
CPU_STK   	 BmeSensorTaskStk[128u];


void BmeSensorTask_Init()
{
    int result = 0;
    result = Bme_Init();

    (void)result; // Log the error or something.
}

void BmeSensorTask(void *p_arg)
{
    (void)p_arg;    /* Unused. */

    while (1)
    {

    // Read the Data from the Sensor.
    struct bme280_data sensor_data;
    Bme_GetData(BME280_ALL, &sensor_data);

    // Store the Data to RingBuffer.
    DataStorage_AppendBuffer(&sensor_data, SENSOR_TYPE_ALL);
    }
}
