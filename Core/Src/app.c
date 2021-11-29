/*
 * app.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#include "app.h"

#include <os.h>
#include <stdio.h>

#include "bme_task.h"
#include "datastorage.h"
#include "lcd16x2/LCD16x2.h"
#include "lcd_display.h"
#include "main.h"
#include "sensortype.h"

#ifndef SEL_HW_PUSHBUTTON
#define APP_PUSHBUTTON_GPIO GPIO_BluePushButton1_GPIO_Port
#define APP_PUSHBUTTON_PIN GPIO_BluePushButton1_Pin
#else
#define APP_PUSHBUTTON_GPIO GPIO_PushButton1_GPIO_Port
#define APP_PUSHBUTTON_PIN GPIO_PushButton1_Pin
#endif

EspPushButtonHandleTask espPushButtonHandleTask = {
    .taskHandle = {.handleName = "Push Button Task".fnTaskInit = NULL, .fnTaskHandle = App_PushButtonTask},
};

EspMainAppHandleTask espMainAppHandleTask = {
    .taskHandle = {.handleName = "Main App Task".fnTaskInit = App_Init, .fnTaskHandle = App_Task},
};

static SensorType g_UserMode = SENSOR_TYPE_TEMP;
static uint8_t g_PushButtonCounter = 0;

static char g_text[] = "Status: %d";

static char buffer[16];

static uint8_t g_LutSensors[] = {
    BME280_PRESS,
    BME280_TEMP,
    BME280_HUM,
};

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
        DataStorageStatus status;
        struct bme280_data bmeData = {0};

        status = DataStorage_Pop(&espBmeSensorHandleTask.dsSensorList, (uint8_t*)&bmeData);

        if (status != DATASTORAGE_OK)
        {
            snprintf(buffer, 16, "Error: %d", status);
        }
        else
        {
            Display_SetMode(g_UserMode, *((double*)((struct bme280_data*)&bmeData) + g_UserMode));
            Display_Update();
        }

        OSTimeDly(200, OS_OPT_TIME_DLY, &p_err);
    }
}

uint8_t App_GetUserMode()
{
    return g_LutSensors[g_UserMode];
}

void App_PushButtonTask(void* p_arg)
{
    UNUSED(p_arg);

    OS_ERR p_err;

    while (1)
    {
        if (HAL_GPIO_ReadPin(APP_PUSHBUTTON_GPIO, APP_PUSHBUTTON_PIN) == GPIO_PIN_RESET)
        {
            g_UserMode += 1;

            if (g_UserMode >= SENSOR_TYPE_ALL)
            {
                // g_PushButtonCounter = 1;
                g_UserMode = 0;
            }
            // g_PushButtonCounter += 1;
        }

        OSTimeDly(200, OS_OPT_TIME_DLY, &p_err);
    }
}
