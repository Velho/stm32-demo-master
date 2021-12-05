#include "comm_task.h"

#include "main.h"
#include "usart.h"
#include "app_task.h"
#include "datastorage.h"

#include <os.h>
#include <bme280/bme280_defs.h>

#ifdef ESP_MASTER

EspCommRxTaskHandle espCommRxTaskHandle = {
    .taskHandle = {.handleName = "Master CommRX Handle", .fnTaskHandle = EspCommRxTask, .fnTaskInit = NULL},
};

EspCommTxTaskHandle espCommTxTaskHandle = {
    .taskHandle = {.handleName = "Master CommTX Handle", .fnTaskHandle = EspCommTxTask, .fnTaskInit = NULL},
};

int EspCommInit()
{
    return 0;
}

void EspCommPrepareTx()
{
    // Prepare GPIO.
    HAL_GPIO_WritePin(RS485_NRE_GPIO_Port, RS485_NRE_Pin, 1);
    HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, 1);

    // Prepare data from the PushButton Select.
}

static void EspCommPostTx()
{
    // Prepare GPIO.
    HAL_GPIO_WritePin(RS485_NRE_GPIO_Port, RS485_NRE_Pin, 0);
    HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, 0);
}

void EspCommRxTask(void* p_arg)
{
    OS_ERR p_err;
	struct bme280_data data = { 0 };

    while (1)
    {
    	EspCommPostTx();

    	if (HAL_UART_Receive(&huart1, (uint8_t*)&data, sizeof(data), 1000) == HAL_OK)
    	{
    		DataStorage_Append(&espCommRxTaskHandle.dsCommRxList, (uint8_t*)&data);
    	}

        OSTimeDly(1000, OS_OPT_TIME_DLY, &p_err);
    }
}

void EspCommTxTask(void* p_arg)
{
    OS_ERR p_err;

    while (1)
    {
    	EspCommPrepareTx();

    	HAL_UART_Transmit(&huart1,
    			(uint8_t*)&espPushButtonHandleTask.selectedSensorType,
				sizeof(espPushButtonHandleTask.selectedSensorType), 100);

    	EspCommPostTx();
        OSTimeDly(100, OS_OPT_TIME_DLY, &p_err);
    }
}

#endif
