/*
 * sensors.h
 *
 *  Created on: Nov 12, 2021
 *      Author: Velho
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

typedef enum {
    Sensor_BME280 = 0x1,

    Sensor_Count
    Sensor_Last = 0xF
} Sensors;

#endif
