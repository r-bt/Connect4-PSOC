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
#include "Taunts.h"
#include "FS.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Tick.h"

#define BUFFERLEN 512

int after_ai_taunts_num = 0;
int after_human_taunts_num = 0;

/**
Counts how many lines there are in a file
**/
int Taunts_NumLines(const char* pFileName) {
    char buffer[BUFFERLEN];
    uint16_t bufferLen;
    
    int lines = 0;
    
    FS_FILE *pFile = FS_FOpen(pFileName, "r");
    
    if (pFile) {
        while ((bufferLen = FS_Read(pFile, &buffer, BUFFERLEN))) {
            for (uint16_t i = 0; i < bufferLen; i++) {
                if (buffer[i] == '\n') {
                    lines++;
                }
            }
        }
        
        if (FS_FClose(pFile)) {
            USBUART_PutString("Failed to close the file \r\n");
            CyDelay(100);
        }
    } else {
        USBUART_PutString("Failed to open the file\r\n");
        CyDelay(100);
    }
    
    return lines;
}

/**
    Returns a specified line from a file
**/
void Taunts_GetLine(const char* pFileName, int line, char *taunt) {
    char buffer[BUFFERLEN];
    uint8_t lineIndex = 0;
    char c;
    uint16_t bufferLen;
    
    int lines = 0;
    
    FS_FILE *pFile = FS_FOpen(pFileName, "r");
    
    char print[100];
    
    if (pFile) {
        while ((bufferLen = FS_Read(pFile, &buffer, BUFFERLEN))) {
            for (uint16_t i = 0; i < bufferLen; i++) {
                if (lines < line) {
                    if (buffer[i] == '\n') {
                        lines++;
                    }
                } else {
                    c = buffer[i];
                    switch (c) {
                        case '\n':
                            taunt[lineIndex] = 0;
                            FS_FClose(pFile);
                            return;
                        case '\r':
                            break;
                        default:
                            taunt[lineIndex++] = c;
                    }
                }
            }
        }
        
        if (FS_FClose(pFile)) {
            USBUART_PutString("Failed to close the file \r\n");
            CyDelay(100);
        }
    } else {
        USBUART_PutString("Failed to open the file\r\n");
        CyDelay(100);
    }
}

/**
Initalizes taunt making by getting the amount of taunts in the two files
**/
void Taunts_Init() {
    after_ai_taunts_num = Taunts_NumLines("\\taunts\\taunts1.txt");
    after_human_taunts_num = Taunts_NumLines("\\taunts\\taunts2.txt");
    
    srand(Tick_GetTicks(5));
}

/**
    Returns a taunt to be displayed after the opponent makes a move
**/
void Taunts_GetOpponentMoveTaunt(char *taunt) {
    int randomLine = rand() % after_ai_taunts_num;
    
    Taunts_GetLine("\\taunts\\taunts1.txt", randomLine, taunt);
}

/**
    Returns a taunt to be displayed after the player makes a move
**/
void Taunts_GetPlayerMoveTaunt(char *taunt) {
    int randomLine = rand() % after_ai_taunts_num;
    
    Taunts_GetLine("\\taunts\\taunts2.txt", randomLine, taunt);
}

/* [] END OF FILE */
