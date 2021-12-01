#ifndef INC_EXTCOM_TASK
#define INC_EXTCOM_TASK

#include "esp_taskhandle.h"
#include <os.h>

#define EXTCOM_TASK_STK_SIZE	128u

typedef struct
{
    EspTaskHandle taskHandle;                   //!< Task Handle with the function pointers for Initializer and Tasks.
    OS_TCB extcomTaskTCB;                    //!< Transmision Control Block for this Task.
    CPU_STK extcomTaskStk[EXTCOM_TASK_STK_SIZE]; //!< Stack used for this Task.
} EspExtComHandleTask;

extern EspExtComHandleTask espExtComHandleTask;

int ExtCom_Init();

void ExtCom_Task(void *p_arg);

#endif
