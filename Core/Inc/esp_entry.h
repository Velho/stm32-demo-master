/**
 * @file esp_entry.h
 * @author Joel e1801162
 * @brief Entry point for the Kernel Tasks.
 * @version 0.1
 * @date 2021-11-26
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef __ESP_ENTRY_H__
#define __ESP_ENTRY_H__

#include "cpu_cfg.h"

#include <cpu.h>
#include <lib_mem.h>
#include <os.h>

#include <bsp_clk.h>
#include <bsp_int.h>
#include <bsp_os.h>

#include "os_app_hooks.h"
#include "bme_task.h"

/**
 * @brief
 *
 * @param p_arg
 */
void EspStartupTask(void* p_arg);

#endif
