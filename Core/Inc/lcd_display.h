/*
 * lcd_display.h
 *
 *  Created on: Oct 27, 2021
 *      Author: Velho
 */

#ifndef INC_LCD_DISPLAY_H_
#define INC_LCD_DISPLAY_H_

#include <stdint.h>

#include "sensortype.h"

/**
 * @brief
 *
 */
void Display_Init();

/**
 * @brief
 *
 */
void Display_Update();

/**
 * @brief
 *
 */
void Display_SetMode(SensorType mode);

uint8_t Display_IsUpdating();

#endif /* INC_LCD_DISPLAY_H_ */
