/*
 * bme_task.c
 *
 *  Created on: Nov 12, 2021
 *      Author: Velho
 */

#include "bme_task.h"
#include "bme_sensor.h"
#include "datastorage.h"

EspBmeSensorHandleTask espBmeSensorHandleTask = {
    .taskHandle = {.fnTaskInit = BmeSensorTask_Init, .fnTaskHandle = BmeSensorTask},
};

int BmeSensorTask_Init()
{
    int result = 0;
    result = Bme_Init();

    (void)result; // Log the error or something.

    DataStorage_Init(&espBmeSensorHandleTask.dsSensorList, sizeof(struct bme280_data));

    return result;
}

void BmeSensorTask(void* p_arg)
{
    (void)p_arg; /* Unused. */

    while (1)
    {
        OS_ERR p_err;
        DataStorageStatus dsStatus;
        struct bme280_data sensor_data;

        // Read the Data from the Sensor.
        BmeReadSensorData(BME280_ALL, &sensor_data);

        // Store the Data to RingBuffer.
        dsStatus = DataStorage_Append(&espBmeSensorHandleTask.dsSensorList, (uint8_t*)&sensor_data);
        if (dsStatus != DATASTORAGE_OK)
        {
            // Log the error.
        }

        // Sleep for 200 ticks and give flow back to kernel.
        OSTimeDly(200, OS_OPT_TIME_DLY, &p_err);
    }
}
