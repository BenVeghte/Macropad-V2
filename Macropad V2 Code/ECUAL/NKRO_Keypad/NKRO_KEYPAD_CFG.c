/*
 * NKRO_KEYPAD_CFG.c
 *
 *  Created on: 8/17/2022
 *      Author: Ben Veghte
*/
#include "NKRO_KEYPAD_CFG.h"
#include "NKRO_KEYPAD.h"
#include "main.h"

const KeypadCFGType KeypadCFGParam =
    {
        {R1_Pin, R2_Pin, R3_Pin, R4_Pin, R5_Pin, R6_Pin},
        {R1_GPIO_Port, R2_GPIO_Port, R3_GPIO_Port, R4_GPIO_Port, R5_GPIO_Port, R6_GPIO_Port},
        {C1_Pin, C2_Pin, C3_Pin, C4_Pin, C5_Pin},
        {C1_GPIO_Port, C2_GPIO_Port, C3_GPIO_Port, C4_GPIO_Port, C5_GPIO_Port},
        E_Switch_Pin,
        E_Switch_GPIO_Port
    };
