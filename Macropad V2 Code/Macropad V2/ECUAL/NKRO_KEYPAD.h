/*
 * NKRO_KEYPAD.h
 *
 *  Created on: Aug 15, 2022
 *      Author: Ben Veghte
 */


#ifndef NKRO_KEYPAD_H_
#define NKRO_KEYPAD_H_

#define HAL_GPIO_MODULE_ENABLED

#include <stm32f0xx_hal.h>

//Define Pressed and Released Values
#define KEY_PRESSED 1
#define KEY_RELEASED 0

//Define Number of Rows and Columns
#define KEYPAD_ROWS 6
#define KEYPAD_COLS 5

//Define Scan Direction
//if the diodes are connected to the rows, change the following line to #define ROW_SCAN
#define COL_SCAN

typedef struct
{
	uint16_t ROW_PIN[KEYPAD_ROWS];
	uint16_t COL_PIN[KEYPAD_COLS];
}NKRO_KEYPAD_CFG;

void NKRO_KEYPAD_Init(uint16_t au16_Instance, unint8_t* au8_KeyStates);
void NKRO_KEYPAD_Scane(uint16_t au16_Instance, unint8_t* au8_KeyStates);

#endif /*NKRO_KEYPAD_H_
