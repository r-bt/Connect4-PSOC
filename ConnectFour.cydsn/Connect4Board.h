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

void Connect4Board_Init();

void Connect4Board_HighlightColumn(uint16 column);

int Connect4Board_GetColumnPos(int column);

void Connect4Board_DrawGrid(uint16 columns, uint16 rows);

void Connect4Board_Place(uint16 column, uint16 player);

void Connect4Board_ClearHighlight();

/* [] END OF FILE */
