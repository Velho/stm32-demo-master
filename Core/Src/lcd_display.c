/*
 * lcd_display.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Velho
 */

#include <lcd16x2/LCD16x2.h>

#include "datastorage.h"
#include "lcd_display.h"
#include "sensortype.h"

static SensorType g_display_mode = 0;
static uint8_t g_is_updating = 0;

typedef struct
{
    const char* text;
    SensorType type;
} TypeDisplayInfo;

TypeDisplayInfo gTypeDisplayInfo[] = {
    {"Temperature \n %0.2f C", SENSOR_TYPE_TEMP},
    {"Humidity \n %0.2f %%", SENSOR_TYPE_HUMD},
    {"Pressure \n %0.2f Pa", SENSOR_TYPE_PRESS},
};

static TypeDisplayInfo* Get_DisplayInfo(SensorType datatype)
{
    TypeDisplayInfo* display = gTypeDisplayInfo;
    while (display++ != NULL)
    {
        if (display->type == datatype)
        {
            return display;
        }
    }

    return NULL;
}

void Display_Init()
{
    // g_display_mode = DISPLAY_SENSOR_TEMP;

    LCD_Init();
}

void Display_Update()
{
}

void Display_SetMode(SensorType mode)
{
    g_display_mode = mode;
}

uint8_t Display_IsUpdating()
{
    return g_is_updating;
}
