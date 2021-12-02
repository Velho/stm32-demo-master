#include "comm_task.h"

//
// "Master" will always request the data from the slave.
// "Slave" will never spontaneously send data, it will only respond.

EspCommRxTaskHandle espCommRxTaskHandle = {
    .taskHandle = {.handleName = "CommRX Handle"},
};

EspCommTxTaskHandle espCommTxTaskHandle = {
    .taskHandle = {.handleName = "CommTX Handle"},
};

void EspCommRxTask(void* p_arg)
{
}

void EspCommTxTask(void* p_arg)
{

}
