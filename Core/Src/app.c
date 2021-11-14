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


/**
#define GPIO_BluePushButton1_Pin GPIO_PIN_13
#define GPIO_BluePushButton1_GPIO_Port GPIOC
#define GPIO_PushButton1_Pin GPIO_PIN_12
#define GPIO_PushButton1_GPIO_Port GPIOB
 */

#ifndef SEL_HW_PUSHBUTTON
#define APP_PUSHBUTTON_GPIO			GPIO_BluePushButton1_GPIO_Port
#define APP_PUSHBUTTON_PIN			GPIO_BluePushButton1_Pin
#else
#define APP_PUSHBUTTON_GPIO			GPIO_PushButton1_GPIO_Port
#define APP_PUSHBUTTON_PIN			GPIO_PushButton1_Pin
#endif


OS_TCB AppPushButtonTCB;
CPU_STK AppPushButtonStk[128u];

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
//	int rslt;

	// Initialize the RX Interrupt.
	// HAL_UART_Receive_IT(&huart2, GetRXBuffer(), 2);

//	DataStorage_Init();
//	rslt = Bme_Init();

	Display_Init();

	return 0;
}

int App_Task()
{
	OS_ERR p_err;


	// float to string conversion.
	// char * str = gcvt

	snprintf(buffer, 33, g_text, g_user_pb_pressed);

	LCD_Clear();
	LCD_Set_Cursor(1, 1);
	LCD_Write_String(buffer);

	// LCD_Set_Cursor(2, 1);
	// LCD_Write_String(buffer);
	// HAL_Delay(10000);

	if (HAL_GPIO_ReadPin(APP_PUSHBUTTON_GPIO, APP_PUSHBUTTON_PIN) == GPIO_PIN_RESET)
	{
		if (g_user_pb_pressed >= 10)
		{
			g_user_pb_pressed = 0;
		}

		g_user_pb_pressed += 1;
	}



	OSTimeDlyHMSM(0, 0, 5, 0, OS_OPT_TIME_HMSM_STRICT, &p_err);

	return 0;
}

int App_GetCounter()
{
	return g_user_pb_pressed;
}

void App_PushButtonTask(void *p_arg)
{
	(void) p_arg;

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

		OS_ERR p_err;
		OSTimeDlyHMSM(0, 0, 5, 0, OS_OPT_TIME_HMSM_STRICT, &p_err);
	}
}
