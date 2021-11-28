/*
 * app.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#include "app.h"

#include <os.h>
#include <stdio.h>

#include "bme_sensor.h"
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
    .taskHandle = {.fnTaskInit = NULL, .fnTaskHandle = App_PushButtonTask},
};

EspMainAppHandleTask espMainAppHandleTask = {
    .taskHandle = {.fnTaskInit = App_Init, .fnTaskHandle = App_Task},
};

static int g_user_pb_pressed = 0;
static char g_text[] = "Status: %d";

static char buffer[33];

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
        snprintf(buffer, 33, g_text, g_user_pb_pressed);

        LCD_Clear();
        LCD_Set_Cursor(1, 1);
        LCD_Write_String(buffer);

        OSTimeDly(200, OS_OPT_TIME_DLY, &p_err);
    }
}

int App_GetCounter()
{
    return g_user_pb_pressed;
}

void App_PushButtonTask(void* p_arg)
{
    UNUSED(p_arg);

    OS_ERR p_err;

    while (1)
    {
        if (HAL_GPIO_ReadPin(APP_PUSHBUTTON_GPIO, APP_PUSHBUTTON_PIN) == GPIO_PIN_RESET)
        {
            if (g_user_pb_pressed >= 10)
            {
                g_user_pb_pressed = 0;
            }

            g_user_pb_pressed += 1;
        }

        OSTimeDly(200, OS_OPT_TIME_DLY, &p_err);
    }
}
