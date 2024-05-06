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

#ifndef Robot_H
#define Robot_H
    
#include <project.h>

void Robot_Init();
void Robot_Move(int column);
void Robot_ClearInterrupter();
void Robot_Update();
uint8 Robot_GetInterrupter();

enum Robot_State {
    Robot_Idle,
    Robot_Moving
};
enum Robot_State Robot_GetState();

#endif