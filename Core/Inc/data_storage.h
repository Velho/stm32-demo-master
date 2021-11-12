/*
 * data_storage.h
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#ifndef INC_DATA_STORAGE_H_
#define INC_DATA_STORAGE_H_

#include "bme_sensor.h"
#include "sensor_datatype.h"

#include <stdint.h>

#define STORAGE_BUFFER_LENGTH	32

typedef struct {
	struct bme280_data sensor_data;
	SensorDataType data_type;
} DataStorageType;

typedef struct {
	void * memory;

} DataStorageValue;

typedef struct {
	DataStorageType storage_list[STORAGE_BUFFER_LENGTH];
	size_t size;

	DataStorageType* head;
	DataStorageType* tail;
} DataStorageTypeList;



uint8_t* GetRxBuffer();

/**
 *
 */
void DataStorage_AppendBuffer(struct bme280_data* sdata, SensorDataType type);

/**
 *
 */
uint8_t DataStorage_GetDataStorageType(DataStorageType* type, SensorDataType sensor_datatype);

void DataStorage_Init();

void DataStorage_Write();
void DataStorage_Read();


#endif /* INC_DATA_STORAGE_H_ */
