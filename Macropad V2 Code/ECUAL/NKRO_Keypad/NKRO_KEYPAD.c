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


typedef struct {
    uint8_t* key_states;
    uint32_t* key_history;
    uint8_t* key_last;
}KeypadInfoTypeDef ;

static KeypadInfoTypeDef KeypadInfo = {0};

/*Function for the initialization of the keypad pins*/
//This function needs to get called after the rest of the pin initialization is called to prevent
// the settings being overridden
void NKROKeypadInit(uint8_t *u8_key_states, uint32_t *u32_key_history, uint8_t *u8_keystate) {
    uint8_t i = 0;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /*Make sure memory addresses to key_states and key_history are properly supplied*/
    if(u8_key_states != NULL) {
        KeypadInfo.key_states = u8_key_states;
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
        GPIO_InitStruct.Pin = KeypadCFGParam.row_pin[i];
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
        HAL_GPIO_Init(KeypadCFGParam.row_pin[i], &GPIO_InitStruct);
    }
    for(i=0; i<KEYPAD_COLS; i++) {
        GPIO_InitStruct.Pin = KeypadCFGParam.col_pin[i];
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        HAL_GPIO_Init(KeypadCFGParam.col_pin[i], &GPIO_InitStruct);
    }
    GPIO_InitStruct.Pin = KeypadCFGParam.encoder_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KeypadCFGParam.encoder_pin, &GPIO_InitStruct);
}

/*Function to scan the keypad for actively pressed keys*/
uint8_t NKROKeypadScan() {
/*
    """
    If scanning the keys is necessary, that means it is possible for the state to ahve changed
    and a stateupdate check is necessary
    """
*/
    uint8_t i = 0;
    uint8_t j = 0;

    /*Check to see if any key is pressed to save calculations*/
    uint8_t scan_needed = 0;
    for(i=0;i<KEYPAD_ROWS; i++) {
        HAL_GPIO_WritePin(KeypadCFGParam.row_GPIO_family[i], KeypadCFGParam.row_pin[i], 1);
    }
    for(i=KEYPAD_COLS-1;i>=0;i--) {
        if (HAL_GPIO_ReadPin(KeypadCFGParam.col_GPIO_family[i], KeypadCFGParam.col_pin[i]) == 1) {
           scan_needed = 1;
           break;
        }
    }
    // Lower row pins back down
    for(i=0;i<KEYPAD_ROWS; i++) {
        HAL_GPIO_WritePin(KeypadCFGParam.row_GPIO_family[i], KeypadCFGParam.row_pin[i], 0);
    }

    //Encoder status
    if(HAL_GPIO_ReadPin(KeypadCFGParam.encoder_GPIO_family, KeypadCFGParam.encoder_pin)==0) {
           scan_needed = 1;
    }

    /*Check to see if any key has non-zero history*/
    if(scan_needed == 0){
        for(i=0;i<(KEYPAD_ROWS*KEYPAD_COLS)+1;i++){
                if(KeypadInfo.key_history[i] != 0){
                    scan_needed = 1;
                    break;
                }
            }
    }



    /*If any key is pressed or history holds non-zero value*/
    if(scan_needed == 1) {
    	uint8_t index_val;
        for(i=0;i<KEYPAD_ROWS; i++) {
            //Write Current Row Pin High
            HAL_GPIO_WritePin(KeypadCFGParam.row_GPIO_family[i], KeypadCFGParam.row_pin[i], 1);

            for(j=0;j<KEYPAD_COLS;j++) {
            	index_val = (KEYPAD_COLS*i)+j;
                KeypadInfo.key_history[index_val] << 1;
                
                //If pin is add the return value to the history
                KeypadInfo.key_history[index_val]+=HAL_GPIO_ReadPin(KeypadCFGParam.col_GPIO_family[j], KeypadCFGParam.col_pin[j]);

            }

            //Return current row back to low
            HAL_GPIO_WritePin(KeypadCFGParam.row_GPIO_family[i], KeypadCFGParam.row_pin[i], 0);

        }
        
        //Handling Encoder Presses (encoder logic is reversed from the normal buttons
        KeypadInfo.key_history[KEYPAD_ROWS*KEYPAD_COLS] += HAL_GPIO_ReadPin(KeypadCFGParam.encoder_GPIO_family, KeypadCFGParam.encoder_pin)^1;

    }
    return scan_needed;
}

void NKROKeypadStateCheck() {
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t index_val;
    for(i=0;i<KEYPAD_ROWS;i++) {
        for(j=0;j<KEYPAD_COLS;j++) {
        	index_val = (KEYPAD_COLS*i)+j;
            //If current state exceeds or is equal to debounce mask and past value is low
            if(((KeypadInfo.key_history[index_val]&DEBOUNCE_MASK)>=DEBOUNCE_MASK) && (KeypadInfo.key_last[(KEYPAD_COLS*i)+j] == 0)){
            	KeypadInfo.key_states[index_val] = 1;
                KeypadInfo.key_history[index_val] = 1;
            }
            //Else if the opposite of the current state passes the debound mask and the previous value was high
            else if((((~KeypadInfo.key_history[index_val]) & DEBOUNCE_MASK) >=DEBOUNCE_MASK)&& (KeypadInfo.key_last[(KEYPAD_COLS*i)+j] == 1)) {
            	KeypadInfo.key_states[index_val] = 0;
                KeypadInfo.key_history[index_val] = 0;
            }
        }
    }
    //Handle Encoder
    if((KeypadInfo.key_history[KEYPAD_ROWS*KEYPAD_COLS]&DEBOUNCE_MASK)>=DEBOUNCE_MASK, KeypadInfo.key_last[KEYPAD_ROWS*KEYPAD_COLS] == 0){
            KeypadInfo.key_states[KEYPAD_ROWS*KEYPAD_COLS] = 1;
            KeypadInfo.key_history[KEYPAD_ROWS*KEYPAD_COLS] = 1;
        }
        //Else if the opposite of the current state passes the debound mask and the previous value was high
        else if(((~KeypadInfo.key_history[KEYPAD_ROWS*KEYPAD_COLS])&DEBOUNCE_MASK)>=DEBOUNCE_MASK, KeypadInfo.key_last[KEYPAD_ROWS*KEYPAD_COLS] == 1) {
            KeypadInfo.key_states[KEYPAD_ROWS*KEYPAD_COLS] = 0;
            KeypadInfo.key_history[KEYPAD_ROWS*KEYPAD_COLS] = 0;
        }
}
