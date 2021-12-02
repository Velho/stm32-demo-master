/**
 * @file esp_device.h
 * @author Velho (velho@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-11-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INC_ESP_TASKHANDLE_H_
#define INC_ESP_TASKHANDLE_H_

typedef int (*FnEspTaskInit)();
typedef void (*FnEspTaskHandle)(void* p_arg);

typedef struct
{
    const char* handleName;
    FnEspTaskInit fnTaskInit;
    FnEspTaskHandle fnTaskHandle;
} EspTaskHandle;

#endif
