/*
 * NKRO_KEYPAD_CFG.c
 *
 *  Created on: 8/17/2022
 *      Author: Ben Veghte
*/
#include "NKRO_KEYPAD_CFG.h"
#include "NKRO_KEYPAD.h"

const struct NKROKeypadCFG KeypadCfgParams =
    {
        {R1_PIN, R2_PIN, R3_PIN, R4_PIN, R5_PIN, R6_PIN},
        {R1_GPIO_Port, R2_GPIO_Port, R3_GPIO_Port, R4_GPIO_Port, R5_GPIO_Port, R6_GPIO_Port},
        {C1_PIN, C2_PIN, C3_PIN, C4_PIN, C5_PIN},
        {C1_GPIO_Port, C2_GPIO_Port, C3_GPIO_Port, C4_GPIO_Port, C5_GPIO_Port},

    };