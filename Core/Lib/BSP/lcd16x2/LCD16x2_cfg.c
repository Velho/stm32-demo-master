/*
 * File: LCD16x2_cfg.c
 * Driver Name: [[ LCD16x2 Display (GPIO 4-Bit Mode) ]]
 * SW Layer:   ECUAL
 * Created on: Jun 28, 2020
 * Author:     Khaled Magdy
 * -------------------------------------------
 * For More Information, Tutorials, etc.
 * Visit Website: www.DeepBlueMbedded.com
 *
 */

#include "LCD16x2.h"


const LCD16x2_CfgType LCD16x2_CfgParam =
{
		{ GPIOB, GPIO_PIN_5 }, 	//! D4_PIN
		{ GPIOB, GPIO_PIN_4 },	//! D5_PIN
		{ GPIOB, GPIO_PIN_10 },	//! D6_PIN
		{ GPIOA, GPIO_PIN_8 },	//! D7_PIN

		{ GPIOB, GPIO_PIN_6 },	//! EN_PIN
		{ GPIOA, GPIO_PIN_7 },	//! RS_PIN

		20
};
