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
#include <stdlib.h>
#include "defs.h"

#define COLUMNS 7 
#define ROWS 6

enum GameState {
    WAITING_FOR_HIGHLIGHT,
    HIGHLIGHTED,
};

enum GameState state;

void MainTask(void);

int main()
{
    CyGlobalIntEnable;                      // Enable global interrupts
    SPIM_1_Start();                         // initialize SPIM component 
    MainTask();                             // all of the emWin exmples use MainTask() as the entry point
    for(;;) {}                              // loop
}

void MainTask()
{
    USBUART_Start(0, USBUART_5V_OPERATION); // Use USB Serial for debugging                                          
    
    GUI_Init();                             // initilize graphics library
    Connect4Board_Init(COLUMNS, ROWS); // Setup the Connect 4 Board
     
    uint16 PosX;
    uint16 PoxY;
    uint16 prevXPTState = 0;
    uint16 prev_selected_column = 7;
  
    for (;;) {
        if (prevXPTState != XPT2046_IRQ) { // Stop multiple events for one touch
            prevXPTState = XPT2046_IRQ;
            if (XPT2046_IRQ == 0) {
                if (XPT2046_ReadXY(&PosX, &PosY)) {
                   
                    uint16 selected_column = PosX / (YSIZE_PHYS / COLUMNS);
                    if (selected_column > COLUMNS - 1) continue;
                    
                    switch (state) {
                        case WAITING_FOR_HIGHLIGHT:
                            Connect4Board_HighlightColumn(selected_column);
                            prev_selected_column = selected_column;
                            state = HIGHLIGHTED;
                            break;
                        case HIGHLIGHTED:
                            if (selected_column == prev_selected_column) {
                                
                            };
                        default:
                            break;
                    }
//                    char xnum[8];
//                    itoa(selected_column, xnum, 10);
//                    USBUART_PutString(xnum);
//                    CyDelay(10);
//                    USBUART_PutString("\r\n");
                }
            }
        }
    }
}

/* [] END OF FILE */
