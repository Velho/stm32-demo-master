#include "comm_task.h"
#include <os.h>

#ifdef ESP_MASTER

EspCommRxTaskHandle espCommRxTaskHandle = {
    .taskHandle = {.handleName = "Master CommRX Handle"},
};

EspCommTxTaskHandle espCommTxTaskHandle = {
    .taskHandle = {.handleName = "Master CommTX Handle"},
};

void EspCommRxTask(void* p_arg)
{
}

void EspCommTxTask(void* p_arg)
{

}

#endif
