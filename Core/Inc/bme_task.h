/*
 * bme_task.h
 *
 *  Created on: Nov 12, 2021
 *      Author: Velho
 */

#ifndef INC_BME_TASK_H_
#define INC_BME_TASK_H_

#include <os.h>
//#include <cpu.h>

extern OS_TCB       BmeSensorTaskTCB;
extern CPU_STK    	BmeSensorTaskStk[128u];


/**
 * @brief Initializes the sensor task.
 *
 */
void BmeSensorTask_Init();

/**
 * @brief Describes the Sensor process.
 * This is also a kernel task.
 */
void BmeSensorTask(void *p_arg);


#endif /* INC_BME_TASK_H_ */
