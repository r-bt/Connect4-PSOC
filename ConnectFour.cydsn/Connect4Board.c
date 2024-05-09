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
#include "Taunts.h"

#define WALL_THICKNESS 2

int column_width;
int row_height;
int num_columns;
int num_rows;

int placed_heights[] = {0,0,0,0,0,0,0};

uint16 WIDTH;
uint16 HEIGHT;

int prev_selected = 7;               

#define GUI_HIGHLIGHT GUI_MAKE_COLOR(0xFCF7DE)

#define TEXT_AREA_HEIGHT 30

void Connect4Board_DrawGrid(uint16 columns, uint16 rows) {
    // Draw the Connect 4 Board
    GUI_SetColor(GUI_BLUE);
    
    column_width = (WIDTH - WALL_THICKNESS * (columns - 1)) / columns;
    row_height = ((HEIGHT - TEXT_AREA_HEIGHT) - WALL_THICKNESS * (rows - 1)) / rows;
    
    for (int i = 0; i < columns - 1; i++) {
        int wall_pos_x = column_width * (i+1) + WALL_THICKNESS * i;
        GUI_FillRect(wall_pos_x, 0, wall_pos_x + WALL_THICKNESS, HEIGHT - TEXT_AREA_HEIGHT);
    }
    
    for (int j = 0; j < rows; j++){
        int wall_pos_y = row_height * (j+1) + WALL_THICKNESS * j;
        GUI_FillRect(0, wall_pos_y, WIDTH, wall_pos_y + WALL_THICKNESS);
    }
}

GUI_RECT text_box;

void Connect4Board_Init(uint16 columns, uint16 rows) {
    WIDTH = YSIZE_PHYS;
    HEIGHT = XSIZE_PHYS;
    
    num_columns = columns;
    num_rows = rows;
    
    for (int i = 0; i < columns; i++) {
        placed_heights[i] = 0;
    }
    
    // Clear the screen before we draw   
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    
    Connect4Board_DrawGrid(columns, rows);
    
    text_box.x0 = 0;
    text_box.x1 = WIDTH;
    text_box.y0 = HEIGHT - TEXT_AREA_HEIGHT;
    text_box.y1 = HEIGHT;
    
    GUI_SetColor(GUI_WHITE);
    GUI_FillRectEx(&text_box);
    
    Taunts_Init();
}

void Connect4Board_DisplayOpponentMoveTaunt() {
    char taunt[TAUNTS_LINELEN];
    
    Taunts_GetOpponentMoveTaunt(taunt);
    
    GUI_SetColor(GUI_WHITE);
    GUI_FillRectEx(&text_box);
    
    GUI_SetColor(GUI_BLACK);
    GUI_DispStringInRect(taunt, &text_box, GUI_TA_HCENTER | GUI_TA_VCENTER);
}

void Connect4Board_DisplayPlayerMoveTaunt() {
    char taunt[TAUNTS_LINELEN];
    
    Taunts_GetPlayerMoveTaunt(taunt);
    
    GUI_SetColor(GUI_WHITE);
    GUI_FillRectEx(&text_box);
    
    GUI_SetColor(GUI_BLACK);
    GUI_DispStringInRect(taunt, &text_box, GUI_TA_HCENTER | GUI_TA_VCENTER);
}

int Connect4Board_GetColumnPosX(int column) {
    return column_width * (column) + WALL_THICKNESS * column;
}

int Connect4Board_GetRowPosY(int row) {
    return row_height * (row) + WALL_THICKNESS * row;
}

void Connect4Board_ClearHighlight() {
    int prev_column_pos_x = Connect4Board_GetColumnPosX(prev_selected);
    int prev_offset_x = (prev_column_pos_x == 0) ? 0 : 1;
    
    int row_index = 5 - (placed_heights[prev_selected]);
    
    int pos_y = Connect4Board_GetRowPosY(row_index);
    int offset_y = (row_index == num_rows - 1) ? 0 : 1;
    
    // Clear the previous highlight
    GUI_SetColor(GUI_WHITE);
    GUI_FillRect(prev_column_pos_x + prev_offset_x, pos_y + 1, prev_column_pos_x + column_width - 1, pos_y + row_height - offset_y); // -1 to ensure we don't collide with walls
}

void Connect4Board_HighlightColumn(uint16 column) {
    
    Connect4Board_ClearHighlight();
    
    int column_pos_x = Connect4Board_GetColumnPosX(column);
    
    // To ensure highlights don't collide with walls we need offsets
    int offset_x = (column_pos_x == 0) ? 0 : 1;
    
    int row_index = 5 - placed_heights[column];
    int pos_y = Connect4Board_GetRowPosY(row_index);
    int offset_y = (row_index == num_rows - 1) ? 0 : 1;

    // Draw the new highlight
    GUI_SetColor(GUI_HIGHLIGHT);
    GUI_FillRect(column_pos_x + offset_x, pos_y + 1, column_pos_x + column_width - 1, pos_y + row_height - offset_y);
   
    prev_selected = column;
}

void Connect4Board_Place(uint16 column, uint16 player) {
    int center_pos_x = Connect4Board_GetColumnPosX(column) + column_width / 2;
    int center_pos_y = Connect4Board_GetRowPosY(5 - placed_heights[column]) + row_height / 2;
    
    uint16 radius = column_width > row_height ? row_height / 2 : column_width / 2;
    
    GUI_SetColor(player ? GUI_RED : GUI_YELLOW);
    
    GUI_FillCircle(center_pos_x, center_pos_y, radius);
    
    placed_heights[column]++;
}



