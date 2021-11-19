/*
 * app_data.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Velho
 */

#ifndef INC_SENSOR_DATATYPE_H_
#define INC_SENSOR_DATATYPE_H_

typedef enum
{
    SENSOR_TYPE_TEMP = 1,
    SENSOR_TYPE_HUMD = 1 << 1,
    SENSOR_TYPE_PRESS = 1 << 2,
    SENSOR_TYPE_ALL = SENSOR_TYPE_TEMP | SENSOR_TYPE_HUMD | SENSOR_TYPE_PRESS,
} SensorType;

#endif /* INC_SENSOR_DATATYPE_H_ */
