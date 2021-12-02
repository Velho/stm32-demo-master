#include "comm_task.h"
#include <os.h>

#ifdef ESP_SLAVE

EspCommRxTaskHandle espCommRxTaskHandle = {
    .taskHandle = {.handleName = "Slave CommRX Handle"},
};

EspCommTxTaskHandle espCommTxTaskHandle = {
    .taskHandle = {.handleName = "Slave CommTX Handle"},
};

void EspCommRxTask(void* p_arg)
{
}

void EspCommTxTask(void* p_arg)
{

}

#endif
