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
typedef struct KeypadCFGTypeDef {
    uint16_t row_pin[KEYPAD_ROWS];
    GPIO_TypeDef * row_GPIO_family[KEYPAD_ROWS];
    uint16_t col_pin[KEYPAD_COLS];
    GPIO_TypeDef * col_GPIO_family[KEYPAD_COLS]
    uint16_t encoder_pin;
    GPIO_TypeDef encoder_GPIO_family;
};


typedef struct KeypadHistoryTypeDef {
    bool *key_states[KEYPAD_ROWS*KEYPAD_COLS+1];
    uint32_t *key_history[KEYPAD_ROWS][KEYPAD_COLS];
    uint8_t *key_last[KEYPAD_ROWS][KEYPAD_COLS];
};





void NKROKeypadInit(bool *b_key_states, uint32_t *u32_key_history, uint8_t *u8_keystate);
bool NKROKeypadScan();
void NKROKeypadPressReleaseCheck();

#endif /*NKRO_KEYPAD_H_*/

