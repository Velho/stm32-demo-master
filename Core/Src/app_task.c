#include <app_task.h>
#include <os.h>
#include <stdio.h>

#include <bme280/bme280_defs.h>

#include "bme_task.h"
#include "comm_task.h"
#include "lcd_display.h"
#include "main.h"

#ifdef ESP_MASTER

#ifndef SEL_HW_PUSHBUTTON
#define APP_PUSHBUTTON_GPIO GPIO_BluePushButton1_GPIO_Port
#define APP_PUSHBUTTON_PIN GPIO_BluePushButton1_Pin
#else
#define APP_PUSHBUTTON_GPIO GPIO_PushButton1_GPIO_Port
#define APP_PUSHBUTTON_PIN GPIO_PushButton1_Pin
#endif

EspPushButtonHandleTask espPushButtonHandleTask = {
    .selectedSensorType = 0,
    .taskHandle = {.handleName = "Push Button Task", .fnTaskInit = NULL, .fnTaskHandle = App_PushButtonTask},
};

EspMainAppHandleTask espMainAppHandleTask = {
    .taskHandle = {.handleName = "Main App Task", .fnTaskInit = App_Init, .fnTaskHandle = App_Task},
};

static char buffer[16];

static uint8_t g_LutSensors[] = {
    BME280_PRESS,
    BME280_TEMP,
    BME280_HUM,
};


/**
 * @brief Get the Bme Data Field object
 *
 * @param data Pointer to the object from the Ringbuffer.
 * @return double Field from the struct.
 */
static double GetBmeDataField(struct bme280_data* data)
{
    return *((double*)((struct bme280_data*)data) + espPushButtonHandleTask.selectedSensorType);
}

int App_Init()
{
    Display_Init();

    return 0;
}

void App_Task(void* p_arg)
{
    UNUSED(p_arg);
    OS_ERR p_err;

    while (1)
    {
        double value;
        DataStorageStatus status;
        struct bme280_data bmeData = {0};

        status = DataStorage_Pop(&espCommRxTaskHandle.dsCommRxList, (uint8_t*)&bmeData);

        if (status != DATASTORAGE_OK)
        {
            snprintf(buffer, 16, "Error: %d", status);
        }
        else
        {
            if (espPushButtonHandleTask.selectedSensorType >= SENSOR_TYPE_ALL)
            {
                // Error something error.
            }

            value = GetBmeDataField(&bmeData);
            Display_SetMode(espPushButtonHandleTask.selectedSensorType, value);
            Display_Update();
        }

        OSTimeDly(200, OS_OPT_TIME_DLY, &p_err);
    }
}

uint8_t App_GetUserMode()
{
    return g_LutSensors[espPushButtonHandleTask.selectedSensorType];
}

uint8_t App_GetSensorType()
{
    return espPushButtonHandleTask.selectedSensorType;
}

void App_PushButtonTask(void* p_arg)
{
    UNUSED(p_arg);

    OS_ERR p_err;

    while (1)
    {
        if (HAL_GPIO_ReadPin(APP_PUSHBUTTON_GPIO, APP_PUSHBUTTON_PIN) == GPIO_PIN_RESET)
        {
            espPushButtonHandleTask.selectedSensorType += 1;

            if (espPushButtonHandleTask.selectedSensorType >= SENSOR_TYPE_ALL)
            {
                espPushButtonHandleTask.selectedSensorType = 0;
            }
        }

        OSTimeDly(200, OS_OPT_TIME_DLY, &p_err);
    }
}

#endif
