/*
 * NKRO_KEYPAD.c
 *
 *  Created on: Aug 15, 2022
 *      Author: Ben Veghte
 */

#include <NKRO_KEYPAD.h>
#include <NKRO_KEYPAD_CFG.h>

#define DEBOUNCE_MASK 4294967295 //Max value stored in uint32_t, max debounce length, if more debouncing is required,
//if a longer debounce time is required, it will be necessary to change the datatype of key_history to uint64

static KeypadInfoTypeDef KeypadInfo;

/*Function for the initialization of the keypad pins*/
//This function needs to get called after the rest of the pin initialization is called to prevent
// the settings being overridden
void NKROKeypadInit(uint8_t *b_key_states, uint32_t *u32_key_history) {
    uint8_t i = 0;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /*Make sure memory addresses to key_states and key_history are properly supplied*/
    if(u16_key_states != NULL) {
        KeypadInfo.key_states = b_key_states;
    }
    else {

        return;
    }
    if(u32_key_history != NULL) {
        KeypadInfo.key_history = u32_key_history;
    }
    else {
        //Should this throw an error? not entirely sure what this means
        return;
    }

    /*Defining pin modes*/
    #ifdef COL_SCAN
    for(i=0; i<KEYPAD_ROWS; i++) {
        GPIO_InitStruct.Pin = KeypadCfgParams.row_pin[i];
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
        HAL_GPIO_Init(KeypadCfgParams.row_pin[i], &GPIO_InitStruct);
    }
    for(i=0; i<KEYPAD_COLS; i++) {
        GPIO_InitStruct.Pin = KeypadCfgParams.col_pin[i];
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        HAL_GPIO_Init(KeypadCfgParams.col_pin[i], &GPIO_InitStruct);
    }
    #elifdef ROW_SCAN
    for(i=0; i<KEYPAD_COLS; i++) {
        GPIO_InitStruct.Pin = KeypadCfgParams.col_pin[i];
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
        HAL_GPIO_Init(KeypadCfgParams.col_pin[i], &GPIO_InitStruct);
    }
    for(i=0; i<KEYPAD_ROWS; i++) {
        GPIO_InitStruct.Pin = KeypadCfgParams.row_pin[i];
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        HAL_GPIO_Init(KeypadCfgParams.row_pin[i], &GPIO_InitStruct);
    }
    #endif

}

/*Function to scan the keypad for actively pressed keys*/
void NKROKeypadScan() {
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t read_state;
    uint8_t key_Pressed;

    /*Check to see if any key is pressed to save calculations*/
#ifdef COL_SCAN
    for(i=0;i<KEYPAD_ROWS; i++) {
        HAL_GPIO_WritePin(KeypadCfgParams.row_gpio_family[i], KeypadCfgParams.row_pin[i], 1);
    }
    for(i=0;i<KEYPAD_COLS;i++) {
        states = HAL_GPIO_ReadPin(KeypadCfgParams.col_gpio_family[i], KeypadCfgParams.col_pin[i]);
    }
    for(i=0;i<KEYPAD_ROWS; i++) {
        HAL_GPIO_WritePin(KeypadCfgParams.row_gpio_family[i], KeypadCfgParams.row_pin[i], 0);
    }
#elifdef ROW_SCAN
    for(i=0;i<KEYPAD_COLS; i++) {
        HAL_GPIO_WritePin(KeypadCfgParams.col_gpio_family[i], KeypadCfgParams.col_pin[i], 1);
    }
    for(i=0;i<KEYPAD_ROWS;i++) {
        key_pressed = keypressed + HAL_GPIO_ReadPin(KeypadCfgParams.row_gpio_family[i], KeypadCfgParams.row_pin[i]);
    }
    for(i=0;i<KEYPAD_COLS; i++) {
        HAL_GPIO_WritePin(KeypadCfgParams.col_gpio_family[i], KeypadCfgParams.col_pin[i], 0);
    }

#endif
    /*If any key is pressed*/
    if(key_pressed>=1) {
        #ifdef COL_SCAN
        for(i=0;i<KEYPAD_ROWS; i++) {
            HAL_GPIO_WritePin(KeypadCfgParams.row_gpio_family[i], KeypadCfgParams.row_pin[i], 1);

            for(j=0;j<KEYPAD_COLS;j++) {
                KeypadInfo.key_history[i][j] = KeypadInfo.key_history[i][j] << 1;

                if (HAL_GPIO_ReadPin(KeypadCfgParams.col_gpio_family[j], KeypadCfgParams.col_pin[j])) {
                    KeypadInfo.key_history[i][j]++;
                }
                // NEED Someway to track button press, and whether the button was just pressed or released, long press info necessary

            }
            HAL_GPIO_WritePin(KeypadCfgParams.row_gpio_family[i], KeypadCfgParams.row_pin[i], 0);

        }
        #elifdef ROW_SCAN
        for(j=0;j<KEYPAD_COLS; j++) {
            HAL_GPIO_WritePin(KeypadCfgParams.col_gpio_family[j], KeypadCfgParams.col_pin[j], 1);
            for(i=0;i<KEYPAD_ROWS;i++) {
                KeypadInfo.key_history[i][j] = KeypadInfo.key_history[i][j] << 1;
                if (HAL_GPIO_ReadPin(KeypadCfgParams.row_gpio_family[i], KeypadCfgParams.row_pin[i])) {
                    KeypadInfo.key_history[i][j]++;
                }
                // NEED Someway to track button press, and whether the button was just pressed or released, long press info necessary

            }
            HAL_GPIO_WritePin(KeypadCfgParams.col_gpio_family[j], KeypadCfgParams.col_pin[j], 0);
        }
        #endif

    }
}

void NKROKeypadPressReleaseCheck() {
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t states_changed = 0;

    for(i=0;i<KEYPAD_ROWS*KEYPAD_COLS;i++) {
        // Fill keypad key updates rows with an impossible value
        // this will allow for a single comparison to be made to check if the value is one that has recently changed
        KeypadInfo.key_updates[i].row = KEYPAD_ROWS;
    }



    for(i=0;i<KEYPAD_ROWS;i++) {
        for(j=0;j<KEYPAD_COLS;j++) {
            //Key passes debouncing in the high state (button pressed), and the last value in the key state is low
            if((KeypadInfo.key_history[i][j] & DEBOUNCE_MASK) == DEBOUNCE_MASK, (~KeypadInfo.key_states[i][j] & 1)==1) {
                KeypadInfo.key_states[i][j] = KeypadInfo.key_states[i][j] << 1;
                KeypadInfo.key_states[i][j]++;

                KeypadInfo.key_updates[states_changed].row = i;
                KeypadInfo.key_updates[states_changed].col = j;
                KeypadInfo.key_updates[states_changed].state = 1;
                states_changed++;
            }

            //Key passes debouncing in the low state (button released), and the last value in the key state is high
            else if ((~KeypadInfo.key_history[i][j] & DEBOUNCE_MASK) == DEBOUNCE_MASK, (KeypadInfo.key_states[i][j] & 1)==1) {
                KeypadInfo.key_states[i][j] = KeypadInfo.key_states[i][j] << 1;

                KeypadInfo.key_updates[states_changed].row = i;
                KeypadInfo.key_updates[states_changed].col = j;
                KeypadInfo.key_updates[states_changed].state = 0;
                states_changed++;
            }
        }
    }
}