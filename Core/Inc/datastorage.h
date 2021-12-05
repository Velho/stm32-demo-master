/*
 * data_storage.h
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#ifndef INC_DATA_STORAGE_H_
#define INC_DATA_STORAGE_H_

#include <stddef.h>
#include <stdint.h>

#include "SensorType.h"

#define STORAGE_BUFFER_LENGTH 128

typedef enum
{
    DATASTORAGE_OK,
    DATASTORAGE_NOMEM,
    DATASTORAGE_INVALID,
    DATASTORAGE_FULL,
    DATASTORAGE_EMPTY,
    DATASTORAGE_OVERFLOW
} DataStorageStatus;

typedef uint8_t DataStorageType;
typedef uint16_t DataStorageIndex;

/**
 * @brief Ringbuffer handle struct.
 *
 */
typedef struct
{
    DataStorageType buffer[STORAGE_BUFFER_LENGTH]; //!< Array of the elements.

    uint32_t element_size; //!< Size of the element.

    DataStorageIndex write; //!< Write index.
    DataStorageIndex read;  //!< Read index.
} DataStorageList;

/**
 * @brief Initializes the DataStorage ringbuffer.
 *
 * @param list Pointer to the ringbuffer list.
 * @param element_size Size of the data structure stored in the buffer.
 * @return 0 in case of success, otherwise true.
 */
int DataStorage_Init(DataStorageList* list, size_t element_size);

/**
 * @brief Appends to the ring buffer.
 *
 * @param list Pointer to the ringbuffer.
 * @param data Pointer to the data.
 * @return DataStorageStatus Returns the status.
 */
DataStorageStatus DataStorage_Append(DataStorageList* list, uint8_t* data);

/**
 * @brief Pops from the ring buffer.
 *
 * @param list Pointer to the ringbuffer.
 * @param data Pointer to the data.
 * @return DataStorageStatus Returns the status.
 */
DataStorageStatus DataStorage_Pop(DataStorageList* list, uint8_t* data);

/**
 * @brief If the write and read index are equal the ringbuffer is considered empty.
 *
 * @param list Pointer to the ringbuffer.
 * @return Returns boolean if read and write index are equal.
 */
int DataStorage_IsEmpty(DataStorageType* list)

#endif /* INC_DATA_STORAGE_H_ */
