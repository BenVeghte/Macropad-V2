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

/*Define Pressed and Released Values*/
#define KEY_PRESSED 1
#define KEY_RELEASED 0

/*Define Number of Rows and Columns*/
#define KEYPAD_ROWS 6
#define KEYPAD_COLS 5


/*Define Scan Direction*/
//if the diodes are connected to the rows, change the following line to #define ROW_SCAN
#define COL_SCAN

/*Keypad Configuration struct*/
typedef struct NKROKeypadCFGTypeDef {
    uint16_t row_pin[KEYPAD_ROWS];
    GPIO_TypeDef * row_GPIO_family[KEYPAD_ROWS];
    uint16_t col_pin[KEYPAD_COLS];
    GPIO_TypeDef * col_GPIO_family[KEYPAD_COLS]
};

typedef struct KeyStateChangeTypeDef {
    uint8_t row;
    uint8_t col;
    uint8_t state;
};

typedef struct KeypadInfoTypeDef {
    uint8_t *key_states[KEYPAD_ROWS][KEYPAD_COLS];
    uint32_t *key_history[KEYPAD_ROWS][KEYPAD_COLS];
    KeyStateChangeTypeDef *key_updates[KEYPAD_COLS*KEYPAD_ROWS];
};





void NKROKeypadInit(unint16_t *au16_key_states);
void NKROKeypadScan();
void NKROKeypadPressReleaseCheck();

#endif /*NKRO_KEYPAD_H_*/

