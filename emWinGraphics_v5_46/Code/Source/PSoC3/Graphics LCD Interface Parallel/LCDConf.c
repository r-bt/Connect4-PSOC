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
File        : LCDConf.c
Purpose     : Display controller initialization
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "LCDConf.h"


/*********************************************************************
*
*       LCD_X_InitController
*
* Purpose:
*   Initializes the display controller.
*
*   For the target project this file needs to be adapted by the cus-
*   tomer. This routine is called by the display driver to get the
*   display controller initialized.
*
*/
void LCD_X_InitController(unsigned LayerIndex) {
  /* Please add here your initialization code */
  GUI_USE_PARA(LayerIndex);
}

/*************************** End of file ****************************/
