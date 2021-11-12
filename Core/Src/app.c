/*
 * app.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#include "bme_sensor.h"
#include "lcd_display.h"
#include "data_storage.h"

#include "sensor_datatype.h"

#include "main.h"

#include "lcd16x2/LCD16x2.h"

#include <os.h>

#include <stdio.h>


static void Update_Sensors()
{
	struct bme280_data sensor_data;
	Bme_GetData(BME280_ALL, &sensor_data);

	DataStorage_AppendBuffer(&sensor_data, SENSOR_TYPE_ALL);
}

int App_Init()
{
	int rslt;

	// Initialize the RX Interrupt.
	// HAL_UART_Receive_IT(&huart2, GetRXBuffer(), 2);

	DataStorage_Init();
	rslt = Bme_Init();

	Display_Init();

	return rslt;
}


int App_Task()
{
	OS_ERR p_err;

	Update_Sensors();

	Display_Update();

	char buffer[33];
	struct bme280_data sensor_data;
	Bme_GetData(BME280_ALL, &sensor_data);

	// sensor_data.temperature = 1;
	snprintf(buffer, 32, "%0.2f", sensor_data.temperature);
			// sensor_data.pressure, sensor_data.humidity);

	LCD_Clear();
	LCD_Set_Cursor(1, 1);
	LCD_Write_String("Temperature");
	LCD_Set_Cursor(2, 1);
	LCD_Write_String(buffer);
//	HAL_Delay(10000);

	OSTimeDlyHMSM(0, 0, 10, 0, OS_OPT_TIME_HMSM_STRICT, &p_err);

	// Display_Update();
	return 0;
}

