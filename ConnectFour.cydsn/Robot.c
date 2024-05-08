/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

#include <project.h>
#include <stdlib.h>
#include <stdio.h>
#include "Robot.h"
#include "Tick.h"

int column_compare_values[] = {1500, 1175, 1100, 1050, 1000, 950, 900};

int hammer_open = 2570;
int hammer_closed = 1000;

uint8 intrSrc;

enum Robot_State robot_state = Robot_Idle;

int interrupter_debounce_elapsed = 1;
CY_ISR(PHOTO_INTERRUPTER_Control) {
    uint8 intrSrcTemp = PHOTO_INTERRUPTER_PINS_ClearInterrupt(); // Get the pin which caused the interrupt
    
    if (!interrupter_debounce_elapsed) return;
    
    intrSrc = intrSrcTemp;
    
    char print[100];
    sprintf(print, "Interrupt on pin %d, debounce elapsed %d\r\n", Robot_GetInterrupter(), interrupter_debounce_elapsed);
    
    USBUART_PutString(print);
    
    interrupter_debounce_elapsed = 0;
    Tick_Reset(); // Wa
}

void Robot_ClearInterrupter() {
    intrSrc = 0; // No interrupter has been triggered              0                                                ccc
}

uint8 Robot_GetInterrupter() {
    for (int i = 0; i < 7; i++) {
        if ((intrSrc >> i) & 1) {
            return i;
        }
    }
    
    return 7;
}

void Robot_Move(int column) {
    
    Robot_ClearInterrupter();
    
    SELECT_PWM_WriteCompare(column_compare_values[column]);
    
    CyDelay(500);
    
    HAMMER_PWM_WriteCompare(hammer_closed);
    
    CyDelay(500);
    
    robot_state = Robot_Moving; 
}

void Robot_Init() {
    PHOTO_INTERRUPTER_ISR_StartEx(PHOTO_INTERRUPTER_Control);
    Robot_ClearInterrupter();
    Tick_AddFlag(&interrupter_debounce_elapsed);
    
    SELECT_PWM_Start();
    HAMMER_PWM_Start();
    
    SELECT_PWM_WriteCompare(column_compare_values[0]);
    HAMMER_PWM_WriteCompare(hammer_open);
    
    CyDelay(500); // Make sure the hammer gets to open position
}

void Robot_Update()  {
    if (intrSrc != 0 && robot_state == Robot_Moving) {
        // Piece placed, move the servos back
        HAMMER_PWM_WriteCompare(hammer_open);
        SELECT_PWM_WriteCompare(column_compare_values[0]);
        
        Robot_ClearInterrupter();
        robot_state = Robot_Idle;
    }
}

enum Robot_State Robot_GetState() {
    return robot_state;
}