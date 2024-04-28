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

#include "GUI.h"
#include "XPT2046.h"
#include <stdlib.h>
#include "defs.h"

#define WALL_THICKNESS 2

int column_width;
int row_height;
int num_columns;
int num_rows;

uint16 WIDTH;
uint16 HEIGHT;

int prev_selected = 7;               

#define GUI_HIGHLIGHT GUI_MAKE_COLOR(0xFCF7DE)

void Connect4Board_DrawGrid(uint16 columns, uint16 rows) {
    // Draw the Connect 4 Board
    GUI_SetColor(GUI_BLUE);
    
    column_width = (WIDTH - WALL_THICKNESS * (columns - 1)) / columns;
    row_height = (HEIGHT - WALL_THICKNESS * (rows - 1)) / rows;
    
    for (int i = 0; i < columns - 1; i++) {
        int wall_pos_x = column_width * (i+1) + WALL_THICKNESS * i;
        GUI_FillRect(wall_pos_x, 0, wall_pos_x + WALL_THICKNESS, HEIGHT);
    }
    
    for (int j = 0; j < rows - 1; j++){
        int wall_pos_y = row_height * (j+1) + WALL_THICKNESS * j;
        GUI_FillRect(0, wall_pos_y, WIDTH, wall_pos_y + WALL_THICKNESS);
    }
}

void Connect4Board_Init(uint16 columns, uint16 rows) {
    WIDTH = YSIZE_PHYS;
    HEIGHT = XSIZE_PHYS;
    
    num_columns = columns;
    num_rows = rows;
    
    // Clear the screen before we draw   
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    
    Connect4Board_DrawGrid(columns, rows);
}

int Connect4Board_GetColumnPosX(int column) {
    return column_width * (column) + WALL_THICKNESS * column;
}

int Connect4Board_GetRowPosY(int row) {
    return row_height * (row) + WALL_THICKNESS * row;
}

void Connect4Board_HighlightColumn(uint16 column) {
    
    if (prev_selected == column) return;
    
    int prev_column_pos_x = Connect4Board_GetColumnPosX(prev_selected);
    int column_pos_x = Connect4Board_GetColumnPosX(column);
    
    // To ensure highlights don't collide with walls we need offsets
    int prev_offset_x = (prev_column_pos_x == 0) ? 0 : 1;
    int offset_x = (column_pos_x == 0) ? 0 : 1;
    
    for (int i = 0; i < num_rows; i++) {
        int pos_y = Connect4Board_GetRowPosY(i);
        int offset_y = (i == num_rows - 1) ? 0 : 1;
        
        // Clear the previous highlight
        GUI_SetColor(GUI_WHITE);
        GUI_FillRect(prev_column_pos_x + prev_offset_x, pos_y + 1, prev_column_pos_x + column_width - 1, pos_y + row_height - offset_y); // -1 to ensure we don't collide with walls
    
        // Draw the new highlight
        GUI_SetColor(GUI_HIGHLIGHT);
        GUI_FillRect(column_pos_x + offset_x, pos_y + 1, column_pos_x + column_width - 1, pos_y + row_height - offset_y);
    }
   
    prev_selected = column;
}



