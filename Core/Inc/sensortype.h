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
	SENSOR_TYPE_ERROR = -1,
    SENSOR_TYPE_PRESS,
    SENSOR_TYPE_TEMP,
    SENSOR_TYPE_HUMD,
    SENSOR_TYPE_ALL,
} SensorType;

#endif /* INC_SENSOR_DATATYPE_H_ */
