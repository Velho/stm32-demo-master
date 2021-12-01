#include "extcom_task.h"

EspExtComHandleTask espExtComHandleTask =
{
	.taskHandle = { .handleName = "Ext Comm Raspi", .fnTaskInit = ExtCom_Init, .fnTaskHandle = ExtCom_Task },
};

int ExtCom_Init()
{
	return 0;
}

void ExtCom_Task(void *p_arg)
{
	(void)p_arg;
	OS_ERR p_err;

	while (1)
	{
		// int Bme_ReadSensorData(uint8_t comp_data, struct bme280_data* data)
		// struct bme280_data data = { 0 };
		// Bme_ReadSensorData(BME280_ALL, &data);

		// Pop BME280 data from the Ringbuffer.
		// HAL_UART_Transmit(uart2, .. );

		OSTimeDly(400, OS_OPT_TIME_DLY, &p_err);
	}
}
