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
*       Public code
*
**********************************************************************
*/
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
*/
void LCD_X_InitController(unsigned LayerIndex) {
  /* Please add here your initialization code */
  GUI_USE_PARA(LayerIndex);
}


/*********************************************************************
*
*       LCD_SetDisplayOrigin
*
* Purpose:
*   Set the display start position of the upper left corner of the display
*/
void LCD_SetDisplayOrigin(int xPos, int yPos) 
{
    int x, y;
    #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
      #define LOG2PHYS_X(x, y) x
      #define LOG2PHYS_Y(x, y) y
    #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
      #define LOG2PHYS_X(x, y) y
      #define LOG2PHYS_Y(x, y) x
    #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
      #define LOG2PHYS_X(x, y) x
      #define LOG2PHYS_Y(x, y) LCD_VYSIZE - LCD_YSIZE - (y)
    #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
      #define LOG2PHYS_X(x, y) y
      #define LOG2PHYS_Y(x, y) LCD_VXSIZE - LCD_XSIZE - (x)
    #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
      #define LOG2PHYS_X(x, y) LCD_VXSIZE - LCD_XSIZE - (x)
      #define LOG2PHYS_Y(x, y) y
    #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
      #define LOG2PHYS_X(x, y) LCD_VYSIZE - LCD_YSIZE - (y)
      #define LOG2PHYS_Y(x, y) x
    #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
      #define LOG2PHYS_X(x, y) LCD_VXSIZE - LCD_XSIZE - (x)
      #define LOG2PHYS_Y(x, y) LCD_VYSIZE - LCD_YSIZE - (y)
    #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
      #define LOG2PHYS_X(x, y) LCD_VYSIZE - LCD_YSIZE - (y)
      #define LOG2PHYS_Y(x, y) LCD_VXSIZE - LCD_XSIZE - (x)
    #endif

    x = LOG2PHYS_X(xPos, yPos);
    y = LOG2PHYS_Y(xPos, yPos);
    
    while(CYGRAPHICS_IS_VBLANKING)
    {
    /* Wait until an active period before changing the frame buffer
    *  address to be sure that the complete address will be updated
    *  before it is used.
    */    
    }
    CYGRAPHICS_WRITE_FRAME(x + y * VXSIZE_PHYS);
}

/*************************** End of file ****************************/
