/*
 * File: LCD16x2.h
 * Driver Name: [[ LCD16x2 Display (GPIO 4-Bit Mode) ]]
 * SW Layer:   ECUAL
 * Created on: Jun 28, 2020
 * Ver: 1.1
 * Author:     Khaled Magdy
 * -------------------------------------------
 * For More Information, Tutorials, etc.
 * Visit Website: www.DeepBlueMbedded.com
 *
 */

#ifndef LCD16X2_H_
#define LCD16X2_H_

#include "stm32l1xx_hal.h"

typedef struct {
	GPIO_TypeDef * 	GPIO;
	uint16_t 		PIN;
} LCD16x2_PinConf;

typedef struct
{
	LCD16x2_PinConf D4_PIN;
	LCD16x2_PinConf D5_PIN;
	LCD16x2_PinConf D6_PIN;
	LCD16x2_PinConf D7_PIN;

	LCD16x2_PinConf EN_PIN;
	LCD16x2_PinConf RS_PIN;

	uint16_t LCD_EN_Delay;
}LCD16x2_CfgType;


//-----[ Prototypes For All Functions ]-----

void LCD_Init();                  // Initialize The LCD For 4-Bit Interface
void LCD_Clear();                 // Clear The LCD Display
void LCD_SL();                    // Shift The Entire Display To The Left
void LCD_SR();                    // Shift The Entire Display To The Right
void LCD_CMD(unsigned char);      // Send Command To LCD
void LCD_DATA(unsigned char);     // Send 4-Bit Data To LCD
void LCD_Set_Cursor(unsigned char, unsigned char);  // Set Cursor Position
void LCD_Write_Char(char);        // Write Character To LCD At Current Position
void LCD_Write_String(char*);     // Write A String To LCD


#endif /* LCD16X2_H_ */
