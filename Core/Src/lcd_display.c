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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FB_LINE_DELIM '\n'

static SensorType g_display_mode = 0;
static float g_data = 0.0f;

static uint8_t g_is_updating = 0;

typedef struct DisplayInfo
{
    char* text;
    SensorType type;
} TypeDisplayInfo;

TypeDisplayInfo gTypeDisplayInfo[] = {
    {"Pressure\n%0.2f Pa\0", SENSOR_TYPE_PRESS},
    {"Temperature\n%0.2f C\0", SENSOR_TYPE_TEMP},
    {"Humidity\n%0.2f rH\0", SENSOR_TYPE_HUMD},
};

TypeDisplayInfo* Get_DisplayInfo(SensorType datatype)
{
    if (datatype < SENSOR_TYPE_ALL)
    {
        return &gTypeDisplayInfo[datatype];
    }
    return NULL;
}

int Display_Init()
{
    LCD_Init();

    return 0;
}

void Display_Update()
{
    TypeDisplayInfo* displayInfo;
    char buffer[16] = {0};
    char* cursor;

    LCD_Clear();
    LCD_Set_Cursor(1, 1);

    displayInfo = Get_DisplayInfo(g_display_mode);

    if (displayInfo != NULL)
    {
        cursor = strchr(displayInfo->text, FB_LINE_DELIM); // Add one to skip the newline character.
        char* source = displayInfo->text;
        char* dest = buffer;

        while (source != cursor)
        {
            *dest++ = *source++;
        }

        LCD_Write_String(buffer);
        LCD_Set_Cursor(2, 1);

        memset(buffer, 0, 16); // Set the buffer back to 0.
        // Cursor + 1, as the pointer points to the newline which we want to skip.
        snprintf(buffer, 16, (const char*)(cursor + 1), g_data);

        LCD_Write_String(buffer);
    }
}

void Display_SetMode(SensorType mode, double data)
{
    g_display_mode = mode;
    g_data = data;
}

uint8_t Display_IsUpdating()
{
    return g_is_updating;
}
