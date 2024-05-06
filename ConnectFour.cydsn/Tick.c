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

uint32_t systick;
int* flags[5];
CY_ISR(isr_systick) {
    systick++;
    if (systick >= 1000) {
       for (int i = 0; i < 5; i++) {
            if (flags[i] != NULL) {
                *(flags[i]) = 1;
            }
        }
        systick = 0;
    }
}

void Tick_Init() {
    CySysTickStart();
    CySysTickSetReload(COUNTS);
    CySysTickSetCallback(0, isr_systick);
}

void Tick_Reset() {
    systick = 0;
}

void Tick_AddFlag(int* ptr) {
    for (int i = 0; i < 5; i++) {
        if (flags[i] == NULL) {
            flags[i] = ptr;
            return;
        }
    }
}