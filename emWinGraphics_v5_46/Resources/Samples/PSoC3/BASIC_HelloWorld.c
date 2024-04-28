/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2009  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

emWin 8051 V4.00 - Graphical user interface for embedded applications

emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be redistri-
buted in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : BASIC_HelloWorld.c
Purpose     : Simple demo drawing "Hello world"
----------------------------------------------------------------------
*/

#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define GUI_NUMBYTES   1500 /* Available memory in bytes for emWin */
#define GUI_BLOCKSIZE    32 /* Average memory block size */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
/*
 ToDo:  Make sure hardware is initilized first!!
*/
  GUI_Init();
  GUI_DispString("Hello world!");
  while(1);
}

/*********************************************************************
*
*       GUI_X_Config
*/
void GUI_X_Config(void) {
  static U32 aMemory[GUI_NUMBYTES >> 2];                      /* Memory block for emWin, 32bit aligned */
  GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES & 0xFFFFFFFC); /* Assign it to emWin */
  GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);                    /* Set average memory block size */
}

/*************************** End of file ****************************/

