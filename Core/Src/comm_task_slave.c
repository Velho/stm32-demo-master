#include "comm_task.h"
#include <os.h>

#include "main.h"
#include "usart.h"
#include "bme_task.h"

#ifdef ESP_SLAVE

EspCommRxTaskHandle espCommRxTaskHandle = {
    .taskHandle = {.handleName = "Slave CommRX Handle"},
};

EspCommTxTaskHandle espCommTxTaskHandle = {
    .taskHandle = {.handleName = "Slave CommTX Handle"},
};

static void EspCommPrepareTx()
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
    UNUSED(p_arg);
    OS_ERR p_err;

    while (1)
    {
    	// EspCommPostTx();
        OSTimeDly(100, OS_OPT_TIME_DLY, &p_err);
    }
}

void EspCommTxTask(void* p_arg)
{
    UNUSED(p_arg);
    OS_ERR p_err;
	// Prepare buffer.
	struct bme280_data* data = { 0 };

    while (1)
    {
    	EspCommPrepareTx();

    	DataStorage_Pop(&espBmeSensorHandleTask.dsSensorList, (uint8_t*)&data);

    	HAL_UART_Transmit(&huart1, (uint8_t*)&data, sizeof(data), 1000);

    	EspCommPostTx();

        // Prepare BME Data to be sent if requested.
        OSTimeDly(200, OS_OPT_TIME_DLY, &p_err);
    }
}

#endif
