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
#include <project.h>
#include "tft.h"
#include "GUI.h"
#include "Connect4Board.h"
#include "XPT2046.h"
//#include <stdlib.h>
#include "defs.h"
#include "Connect4.h"
//#include "Robot.h"
#include "Tick.h"
#include "FS.h"
//#include "stdio.h"

//=================
// System Settings Defintions and variables
//=================
enum SystemState {
    IDLE,
    SETUP_SETTINGS,
    SETTINGS,
    SETUP_GAME,
    GAME
};

enum SystemState state;

#define WIDTH YSIZE_PHYS
#define HEIGHT XSIZE_PHYS

#define ELEMENT_MARGIN 6

#define NUM_LEVELS 3
#define NUM_PLAY_STYLES 2
#define NUM_OPPONENT_OPTIONS 2
#define NUM_BUTTON_ROWS 4
#define NUM_BUTTONS 8

struct Button {
    char* label;
    int value;
};

struct Button buttons[] = {
    {"Easy", 1},
    {"Medium", 3},
    {"Hard", 7},
    {"Screen", 0},
    {"Robot", 1},
    {"Local", 0},
    {"Remote", 1},
    {"Play", 0}
};

GUI_RECT easy_button, medium_button, hard_button, tft_button, robot_button, local_button, remote_button, play_button;
GUI_RECT* button_rects[NUM_BUTTONS] = {&easy_button, &medium_button, &hard_button, &tft_button, &robot_button, &local_button, &remote_button, &play_button};

int selectedDifficulty = 0;
int selectedPlayStyle = 3;
int selectedOpponent = 5;

int columns_for_row[NUM_BUTTON_ROWS] = {NUM_LEVELS, NUM_PLAY_STYLES, NUM_OPPONENT_OPTIONS, 1};

//===================
// Connect 4 Game Definitions and variables
//===================
#define COLUMNS 7 
#define ROWS 6

/**
Initalizes all the setting information
**/

void Settings_Init() {
    int button_spacing_y = HEIGHT / NUM_BUTTON_ROWS;
    int button_spacing_x = 0;
    
    // Setup all the buttons
    int btn_index = 0;
    
    for (int j = 0; j < NUM_BUTTON_ROWS; j++) {
        button_spacing_x = WIDTH / columns_for_row[j];
        
        for (int i = 0; i < columns_for_row[j]; i++) {
            button_rects[btn_index]->x0 = (button_spacing_x * i) + ELEMENT_MARGIN;
            button_rects[btn_index]->x1 = (button_spacing_x * (i + 1)) - ELEMENT_MARGIN;
            button_rects[btn_index]->y0 = (button_spacing_y * j) + ELEMENT_MARGIN;
            button_rects[btn_index]->y1 = (button_spacing_y * (j + 1)) - ELEMENT_MARGIN;
            
            btn_index++;
        }
    } 
    
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetFont(GUI_FONT_16_ASCII);
}

/**
Initalizes all the modules and interrupts
**/
void Init() {
    CyGlobalIntEnable;                      // Enable global interrupt
    
    SPIM_1_Start();                         // Init SPI for TFT screen
    USBUART_Start(0, USBUART_5V_OPERATION); // Use USB Serial for debugging
    //FS_Init();                              // Init Filesystem to read TFT SD card
    GUI_Init();                             // initilize graphics library
    //Tick_Init();                            // Start timer interrupts
    
    Settings_Init();
}

/**
Fills button with specific color
**/
void Settings_FillButton(int btn_index, GUI_COLOR color) {
    GUI_SetColor(color);
    GUI_FillRectEx(button_rects[btn_index]);
            
    GUI_SetColor(GUI_WHITE);
    GUI_DispStringInRect(buttons[btn_index].label, button_rects[btn_index], GUI_TA_HCENTER | GUI_TA_VCENTER);
}

/**
Setups setting display on the TFT screen
**/
void Setup_Settings() {
    // Clear the screen before we draw   
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    
    int btn_index = 0;
    
    for (int j = 0; j < NUM_BUTTON_ROWS; j++) {
        for (int i = 0; i < columns_for_row[j]; i++) {
            Settings_FillButton(btn_index, i == 0 ? GUI_BLUE : GUI_CYAN);
            
            btn_index++;
        }
    } 
    
}

/**
Checks for user input to change the game settings
**/
void Handle_Settings() {
    uint16 PosX;
    uint16 PoxY;
    uint16 prevXPTState = 0;
    
    for (;;) {
        if (prevXPTState != XPT2046_IRQ) { // Stop multiple events for one touch
            prevXPTState = XPT2046_IRQ;
            if (XPT2046_IRQ == 0) { // Touch event!
                if (XPT2046_ReadXY(&PosX, &PosY)) {
                    
                    int button_clicked = NUM_BUTTONS; // Default to no button clicked
                    
                    for (int i = 0; i < NUM_BUTTONS; i++) {
                        if (PosX >= button_rects[i]->x0 && PosX <= button_rects[i]->x1 && PosY >= button_rects[i]->y0 && PosY <= button_rects[i]->y1) {
                            button_clicked = i;
                        } 
                    }
                    
                    int *previouslySelected;
                    
                    switch (button_clicked) {
                        case 0 ... 2:
                            previouslySelected = &selectedDifficulty;
                            break;
                        case 3 ... 4:
                            previouslySelected = &selectedPlayStyle;
                            break;
                        case 5 ... 6:
                            previouslySelected = &selectedOpponent;
                            break;
                        case 7:
                            state = SETUP_GAME;
                            return; // Handle play
                        default:
                            continue;
                    }
                    
                    if (previouslySelected != NULL && *previouslySelected != button_clicked) {
                        Settings_FillButton(*previouslySelected, GUI_CYAN);
                        *previouslySelected = button_clicked;
                        Settings_FillButton(*previouslySelected, GUI_BLUE);
                    }       
                }
            }
        }
    }
}

/**
Setups the Connect 4 Game
**/
void Setup_Game() {
    Connect4Board_Init(COLUMNS, ROWS); // Setup the Connect 4 Board
    Connect4_Init(); // Start the connect 4 game
    
    state = GAME;
}

/**
Handles Playing Connect 4
**/
void Handle_Game() {
    uint16 PosX;
    uint16 PoxY;
    uint16 prevXPTState = 0;
    uint16 prev_selected_column = COLUMNS;
    
    for (;;) {
        //Robot_Update();
        
        if (Connect4_GetCurrentPlayer() == 0) {
            // AI turn
            struct Move bestMove = Connect4_NegaMax(5, -INF, INF);
            Connect4_Move(bestMove.column);
            
            Connect4Board_Place(bestMove.column, 0);
            //Robot_ClearInterrupter();
            //Robot_Move(bestMove.column); 
        } else {
            if (prevXPTState != XPT2046_IRQ) { // Stop multiple events for one touch
                prevXPTState = XPT2046_IRQ;
                if (XPT2046_IRQ == 0) {
                    if (XPT2046_ReadXY(&PosX, &PosY)) {
                        uint16 selected_column = PosX / (YSIZE_PHYS / COLUMNS);
                        if (selected_column > COLUMNS - 1) continue;
                        
                        if (prev_selected_column != selected_column) {
                            Connect4Board_HighlightColumn(selected_column);
                            prev_selected_column = selected_column;
                            CyDelay(250);
                        } else {
                            Connect4Board_ClearHighlight();
                            Connect4_Move(selected_column);
                            Connect4Board_Place(selected_column, 1);
                            
                            CyDelay(1000); // let user think the board is thinking...
                            prev_selected_column = COLUMNS;
                        }
                    }
                }
            }
        }
//        else if (Robot_GetState() == Robot_Idle) {
//            
//            if (Robot_GetInterrupter() != 7) {
//                uint8 column = Robot_GetInterrupter();
//                
//                Connect4_Move(column);
//                Connect4Board_Place(column, 1);
//                
//                Robot_ClearInterrupter();
//                
//                CyDelay(1000); // Pretend robot is thinking
//            }
//            
//            continue;
//            

//        }
    }
}

/**
Main Program
**/
void MainTask()
{
    for(;;) {
        switch (state) {
            case IDLE: // Handle reset case
                state = SETUP_SETTINGS;
                break;
            case SETUP_SETTINGS:
                Setup_Settings();
                state = SETTINGS;
                break;
            case SETTINGS:
                Handle_Settings();
                break;
            case SETUP_GAME:
                Setup_Game();
                break;
            case GAME:
                Handle_Game();
                break;
        }
    }
}

int main()
{
    Init();
    
    MainTask();                             
    for(;;) {}                              // loop
}


//
///* [] END OF FILE */
//