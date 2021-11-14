/*
 * app.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#include <os.h>
#include <stdio.h>

#include "bme_sensor.h"
#include "data_storage.h"
#include "lcd16x2/LCD16x2.h"
#include "lcd_display.h"
#include "main.h"
#include "sensor_datatype.h"

#define SEL_HW_PUSHBUTTON

#ifndef SEL_HW_PUSHBUTTON
#define APP_PUSHBUTTON_GPIO			GPIO_BluePushButton1_GPIO_Port
#define APP_PUSHBUTTON_PIN			GPIO_BluePushButton1_Pin
#else
#define APP_PUSHBUTTON_GPIO			GPIO_PushButton1_GPIO_Port
#define APP_PUSHBUTTON_PIN			GPIO_PushButton1_Pin
#endif



OS_TCB AppPushButtonTCB;
CPU_STK AppPushButtonStk[128u];

OS_TCB AppTaskTCB;
CPU_STK AppTaskStk[256u];

static int g_user_pb_pressed = 0;
static float g_user_float = 1.2;
static char g_text[] = "Status: %d";

static char buffer[33];

static void Update_Sensors()
{
	struct bme280_data sensor_data;
	Bme_GetData(BME280_ALL, &sensor_data);

	DataStorage_AppendBuffer(&sensor_data, SENSOR_TYPE_ALL);
}

int App_Init()
{
	Display_Init();

	return 0;
}

void App_Task(void *p_arg)
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

void App_PushButtonTask(void *p_arg)
{
	UNUSED(p_arg);

	OS_ERR p_err;

	while (1)
	{
		if (HAL_GPIO_ReadPin(APP_PUSHBUTTON_GPIO, APP_PUSHBUTTON_PIN)
				== GPIO_PIN_RESET)
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
