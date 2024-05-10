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
#ifndef Tick_H
#define Tick_H
    
#include <project.h>
    
void Tick_Init();
void Tick_Reset(int index);
int Tick_AddFlag(int *flag, uint32_t trigger);
uint32_t Tick_GetTicks(int index);
    
#endif