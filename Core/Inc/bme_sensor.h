#ifdef ESP_SLAVE
#ifndef INC_BME_SENSOR_H_
#define INC_BME_SENSOR_H_

#include <bme280/bme280_defs.h>

#include <stdint.h>

extern struct bme280_dev bme280_device;

/**
 * @brief
 *
 * @return int
 */
int Bme_Init();

/**
 * @brief
 *
 * @return struct bme280_dev*
 */
struct bme280_dev* Bme_GetSensor();

/**
 * @brief
 *
 * @param comp_data
 * @param data
 * @return int
 */
int Bme_ReadSensorData(uint8_t comp_data, struct bme280_data* data);

#endif /* INC_BME_SENSOR_H_ */
#endif /* ESP_SLAVE */
