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
#include "Tick.h"
#include <project.h>
#include <stdio.h>

#define COUNTS 12000

int* flags[5];
uint32_t counts[5];
uint32_t triggers[5];

uint32_t systick = 0;

CY_ISR(isr_systick) {
    systick++;
    
    for (int i = 0; i < 5; i++) {
        if (flags[i] != NULL) {
            counts[i]++;
            
            if (counts[i] >= triggers[i]) {
                *(flags[i]) = 1;
                counts[i] = 0;
            }
        }
    }
}

void Tick_Init() {
    CySysTickStart();
    CySysTickSetReload(COUNTS);
    CySysTickSetCallback(0, isr_systick);
}

void Tick_Reset(int index) {
    counts[index] = 0;
}

int Tick_AddFlag(int* ptr, uint32_t trigger) {
    for (int i = 0; i < 5; i++) {
        if (flags[i] == NULL) {
            flags[i] = ptr;
            counts[i] = 0;
            triggers[i] = trigger;
            return i;
        }
    }
    
    return 5; // No available position for flag
}

uint32_t Tick_GetTicks(int index) {
    if (index > 4) {
        return systick;
    }
    
    return counts[index];
}