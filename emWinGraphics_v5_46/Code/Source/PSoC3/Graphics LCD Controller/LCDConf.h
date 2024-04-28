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
File        : LCDConf.h
Purpose     : LCD configuration file for GraphicLCDCtrl component.
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H


/*********************************************************************
*       General configuration of LCD
*********************************************************************/
 
/* LCD Controller used by emWin */
#define LCD_CONTROLLER         -1
 
/* LCD orientation settings */ 
#define LCD_MIRROR_X            1
#define LCD_MIRROR_Y            0
#define LCD_SWAP_XY             1

/* Color depths - bits per pixel and bit order */
#define LCD_BITSPERPIXEL        16
#define LCD_SWAP_RB             1

/* Physical display size */
#define XSIZE_PHYS              240
#define YSIZE_PHYS              320

/* Virtual display size */
#define VXSIZE_PHYS             240
#define VYSIZE_PHYS             320

/* Set palette mode */
#define LCD_FIXEDPALETTE        565

/* Function call for setting the display start position */
extern void LCD_SetDisplayOrigin(int xPos, int yPos);
#define LCD_SET_ORG(x, y)       LCD_SetDisplayOrigin(x, y) 

/*********************************************************************
*       Configuration checking
*********************************************************************/

#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif

#if LCD_SWAP_XY
  #define LCD_XSIZE YSIZE_PHYS
  #define LCD_YSIZE XSIZE_PHYS
  #define LCD_VXSIZE VYSIZE_PHYS
  #define LCD_VYSIZE VXSIZE_PHYS
#else
  #define LCD_XSIZE XSIZE_PHYS
  #define LCD_YSIZE YSIZE_PHYS
  #define LCD_VXSIZE VXSIZE_PHYS
  #define LCD_VYSIZE VYSIZE_PHYS
#endif

#endif /* LCDCONF_H */
