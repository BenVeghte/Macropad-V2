/*
 * NKRO_KEYPAD.c
 *
 *  Created on: Aug 15, 2022
 *      Author: Ben Veghte
 */

#include "NKRO_KEYPAD.h"
#include "NKRO_KEYPAD_CFG.h"

#define DEBOUNCE_MASK 4294967295 //Max value stored in uint32_t, max debounce length, if more debouncing is required,
//if a longer debounce time is required, it will be necessary to change the datatype of key_history to uint64

static KeypadHistoryTypeDef KeypadInfo;

/*Function for the initialization of the keypad pins*/
//This function needs to get called after the rest of the pin initialization is called to prevent
// the settings being overridden
void NKROKeypadInit(bool *b_key_states, uint32_t *u32_key_history, uint8_t *u8_keystate) {
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
    GPIO_InitStruct.Pin = KeypadCfgParams.encoder_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_MODE_PULLUP;
    HAL_GPIO_Init(KeypadCfgParams.encoder_pin, &GPIO_InitStruct);
}

/*Function to scan the keypad for actively pressed keys*/
bool NKROKeypadScan() {

    """
    If scanning the keys is necessary, that means it is possible for the state to ahve changed
    and a stateupdate check is necessary
    """
    
    uint8_t i = 0;
    uint8_t j = 0;

    /*Check to see if any key is pressed to save calculations*/
    bool scan_needed = false;
    for(i=0;i<KEYPAD_ROWS; i++) {
        HAL_GPIO_WritePin(KeypadCfgParams.row_gpio_family[i], KeypadCfgParams.row_pin[i], 1);
    }
    for(i=KEYPAD_COLS-1;i>=0;i--) {
        if (HAL_GPIO_ReadPin(KeypadCfgParams.col_gpio_family[i], KeypadCfgParams.col_pin[i]) == 1) {
           scan_needed = true;
           break;
        }
    }
    // Lower row pins back down
    for(i=0;i<KEYPAD_ROWS; i++) {
        HAL_GPIO_WritePin(KeypadCfgParams.row_gpio_family[i], KeypadCfgParams.row_pin[i], 0);
    }

    //Encoder status
    if(!HAL_GPIO_ReadPin(KeypadCfgParams.encoder_gpio_family, KeypadCfgParams.encoder_pin)) {
           scan_needed = true;
    }

    /*Check to see if any key has non-zero history*/
    if(scan_needed == false){
        for(i=0;i<(KEYPAD_ROWS*KEYPAD_COLS)+1;i++){
                if(KeypadInfo.key_history[i] != 0){
                    scan_needed = true;
                    break;
                }
            }
    }



    /*If any key is pressed or history holds non-zero value*/
    if(scan_needed == true) {
        for(i=0;i<KEYPAD_ROWS; i++) {
            //Write Current Row Pin High
            HAL_GPIO_WritePin(KeypadCfgParams.row_gpio_family[i], KeypadCfgParams.row_pin[i], 1);

            for(j=0;j<KEYPAD_COLS;j++) {
                KeypadInfo.key_history[(KEYPAD_COLS*(i))+j)] << 1;
                
                //If pin is high
                if (HAL_GPIO_ReadPin(KeypadCfgParams.col_gpio_family[j], KeypadCfgParams.col_pin[j])) { // This method with only register identify individual presses and wont do anything about long vs short press
                    KeypadInfo.key_history[(KEYPAD_COLS*(i))+j)]++;
                }
            }

            //Return current row back to low
            HAL_GPIO_WritePin(KeypadCfgParams.row_gpio_family[i], KeypadCfgParams.row_pin[i], 0);

        }
        
        //Handling Encoder Presses
        if (!HAL_GPIO_ReadPin(KeypadCfgParams.encoder_gpio_family, KeypadCfgParams.encoder_pin)) { 
            KeypadInfo.key_history[KEYPAD_ROWS*KEYPAD_COLS]++;
        }

    }
    return scan_needed
}

void NKROKeypadStateCheck() {
    uint8_t i = 0;
    uint8_t j = 0;

    for(i=0;i<KEYPAD_ROWS;i++) {
        for(j=0;j<KEYPAD_COLS;j++) {
            //If current state exceeds or is equal to debounce mask and past value is low
            if((KeypadInfo.key_history[(KEYPAD_COLS*(i))+j)]&DEBOUNCE_MASK)>=DEBOUNCE_MASK, KeypadInfo.key_last[(KEYPAD_COLS*(i))+j)] == 0){
                KeypadInfo.key_states[(KEYPAD_COLS*(i))+j)] = true;
                KeypadInfo.state_history[(KEYPAD_COLS*(i))+j)] = 1;
            }
            //Else if the opposite of the current state passes the debound mask and the previous value was high
            else if(((~KeypadInfo.key_history[(KEYPAD_COLS*(i))+j)])&DEBOUNCE_MASK)>=DEBOUNCE_MASK, KeypadInfo.key_last[(KEYPAD_COLS*(i))+j)] == 1) {
                KeypadInfo.key_states[(KEYPAD_COLS*(i))+j)] = false;
                KeypadInfo.state_history[(KEYPAD_COLS*(i))+j)] = 0;
            }
        }
    }
    //Handle Encoder
    if((KeypadInfo.key_history[KEYPAD_ROWS*KEYPAD_COLS]&DEBOUNCE_MASK)>=DEBOUNCE_MASK, KeypadInfo.key_last[KEYPAD_ROWS*KEYPAD_COLS] == 0){
            KeypadInfo.key_states[KEYPAD_ROWS*KEYPAD_COLS] = true;
            KeypadInfo.state_history[KEYPAD_ROWS*KEYPAD_COLS] = 1;
        }
        //Else if the opposite of the current state passes the debound mask and the previous value was high
        else if(((~KeypadInfo.key_history[KEYPAD_ROWS*KEYPAD_COLS])&DEBOUNCE_MASK)>=DEBOUNCE_MASK, KeypadInfo.key_last[KEYPAD_ROWS*KEYPAD_COLS] == 1) {
            KeypadInfo.key_states[KEYPAD_ROWS*KEYPAD_COLS] = false;
            KeypadInfo.state_history[KEYPAD_ROWS*KEYPAD_COLS] = 0;
        }
}