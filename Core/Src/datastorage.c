#include "datastorage.h"

#include <assert.h>
#include <string.h>

#define STORAGE_BUFFER_MASK (STORAGE_BUFFER_LENGTH - 1)

DataStorageStatus DataStorage_Append(DataStorageList* list, uint8_t* data)
{
    DataStorageStatus ret = DATASTORAGE_OK;

    if (list == NULL || data == NULL)
    {
        ret = DATASTORAGE_INVALID;
        return ret;
    }

    size_t offset = list->write * list->element_size;

    if ((offset + list->element_size) >= STORAGE_BUFFER_MASK)
    {
        list->write = 0;
        offset = list->write * list->element_size;
        ret = DATASTORAGE_OVERFLOW;
    }

    memcpy(&list->buffer[offset], data, list->element_size);
    list->write = (list->write + 1) & STORAGE_BUFFER_MASK;

    return ret;
}

DataStorageStatus DataStorage_Pop(DataStorageList* list, uint8_t* data)
{
    DataStorageStatus ret = DATASTORAGE_OK;

    if (list == NULL || data == NULL)
    {
        ret = DATASTORAGE_INVALID;
        return ret;
    }

    size_t offset = list->read * list->element_size;

    if ((offset + list->element_size) >= STORAGE_BUFFER_MASK)
    {
        list->read = 0;
        offset = list->read * list->element_size;
        ret = DATASTORAGE_OVERFLOW;
    }

    memcpy(data, &list->buffer[offset], list->element_size);
    list->read = (list->read + 1) & STORAGE_BUFFER_MASK;

    return ret;
}

int DataStorage_Init(DataStorageList* list, size_t element_size)
{
    if (list == NULL || element_size == 0)
    {
        return 1;
    }

    list->write = 0;
    list->read = 0;

    list->element_size = element_size;

    return 0;
}

int DataStorage_IsEmpty(DataStorageType* list)
{
    assert(list != NULL);

    return list->write == list->read;
}
