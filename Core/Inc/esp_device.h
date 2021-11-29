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
#ifndef INC_ESP_DEVICE_H
#define INC_ESP_DEVICE_H

// TODO : Add some preprocessing logic to disable functionality in slave devices.

typedef int (*FnEspTaskInit)();
typedef void (*FnEspTaskHandle)(void* p_arg);

typedef struct
{
    FnEspTaskInit fnTaskInit;
    FnEspTaskHandle fnTaskHandle;
} EspTaskHandle;

#endif
