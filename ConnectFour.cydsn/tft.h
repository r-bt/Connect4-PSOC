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
#include "project.h"

void write8_a0(uint8 data);
void write8_a1(uint8 data);
void writeM8_a1(uint8 *pData, int N);
uint8 read8_a1(void);
void readM8_a1(uint8 *pData, int N);
void tftStart(void);

void t_SendCmd(uint8 data);
unsigned short t_GetResult();
char t_GetBusy();
void t_SetCS(char OnOff);
char t_GetPENIRQ();


/* [] END OF FILE */